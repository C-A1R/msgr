#include "SqliteDatabase.h"
#include "SqlRec.h"
#include "../../src_shared/UserInfo.h"
#include "../../src_shared/MessageInfo.h"

#include <iostream>
#include <memory>

SqliteDatabase::SqliteDatabase(const char *dbName) : _dbName{dbName}
{
}

SqliteDatabase::~SqliteDatabase()
{
    sqlite3_close(_handler);
}

bool SqliteDatabase::create()
{
    if (!exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                                 "login VARCHAR(255), "
                                                 "password VARCHAR(255), "
                                                 "name VARCHAR(255));"
              "CREATE TABLE IF NOT EXISTS messages (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                                   "id_sender INTEGER, "
                                                   "id_recipient INTEGER, "
                                                   "text TEXT, "
                                                   "delivered BOOL);"))
    {
        std::cout << "DB_ERR: tables are not created " << sqlite3_errmsg(_handler) << std::endl;
        return false;

    }
    return true;
}

bool SqliteDatabase::open()
{
    if (sqlite3_open(_dbName, &_handler))
    {
        std::cout << "DB_ERR: database is not opened " << sqlite3_errmsg(_handler) << std::endl;
        return false;
    }
    return true;
}

int SqliteDatabase::insertUser(const std::pair<std::string, std::string> &values)
{
    if (values.first.empty() || values.second.empty())
    {
        return invalidId();
    }
    std::string query = "INSERT INTO users (login, password) VALUES (\""
                        + values.first + "\", \"" + values.second + "\");";
    if (!exec(query))
    {
        std::cout << "DB_ERR: " << query << std::endl;
        return invalidId();
    }
    return maxId("users");
}

bool SqliteDatabase::getUserId(const std::string &login, int &result)
{
    std::string query = "SELECT id FROM users WHERE login = '" + login + "';";
    std::string id;
    if (!sqlValue(query, "id", id))
    {
        std::cout << "DB_ERR: " << query << std::endl;
        return false;
    }
    if (!id.empty())
        result = stoi(id);
    return true;
}

bool SqliteDatabase::getUserPassword(const int id, std::string &result)
{
    std::string query = "SELECT password FROM users WHERE id = " + std::to_string(id) + ";";
    if (!sqlValue(query, "password", result))
    {
        std::cout << "DB_ERR: " << query << std::endl;
        return false;
    }
    return true;
}

bool SqliteDatabase::getUsername(const int id, std::string &result)
{
    std::string query = "SELECT name FROM users WHERE id = " + std::to_string(id) + ";";
    if (!sqlValue(query, "name", result))
    {
        std::cout << "DB_ERR: " << query << std::endl;
        return false;
    }
    return true;
}

bool SqliteDatabase::getAllUsers(std::vector<UserInfo> &result)
{
    std::string query = "SELECT * FROM users;";
    std::vector<SqlRec> recs;
    if (!sqlTable(query, recs))
    {
        std::cout << "DB_ERR: " << query << std::endl;
        return false;
    }
    result.reserve(recs.size());
    for (const auto &rec : recs)
    {
        UserInfo user;
        user.id = std::stoi(rec.value("id"));
        user.login = rec.value("login");
        user.name = rec.value("name");
        result.emplace_back(std::move(user));
    }
    return true;
}

int SqliteDatabase::insertMessage(int sender, int recipient, const std::string &text)
{
    if (text.empty())
    {
        return invalidId();
    }
    std::string query = "INSERT INTO messages (id_sender, id_recipient, text) VALUES (\""
                        + std::to_string(sender) + "\", \"" + std::to_string(recipient) + "\", \"" + text + "\");";
    if (!exec(query))
    {
        std::cout << "DB_ERR: " << query << std::endl;
        return invalidId();
    }
    return maxId("messages");
}

bool SqliteDatabase::getMessages(int user_1, int user_2, int lastId, std::vector<MessageInfo> &result)
{
    std::string query = "SELECT * FROM messages WHERE " + (lastId != -1 ? ("id > " + std::to_string(lastId) + " AND " ): "") +
                        "((id_sender = " + std::to_string(user_1) + " AND id_recipient = " + std::to_string(user_2) + ") "
                        "OR (id_sender = " + std::to_string(user_2) + " AND id_recipient = " + std::to_string(user_1) + "));";
    std::vector<SqlRec> recs;
    if (!sqlTable(query, recs))
    {
        std::cout << "DB_ERR: " << query << std::endl;
        return false;
    }
    result.reserve(recs.size());
    for (const auto &rec : recs)
    {
        MessageInfo msg;
        msg.id = std::stoi(rec.value("id"));
        msg.senderId = std::stoi(rec.value("id_sender"));
        msg.recipientId = std::stoi(rec.value("id_recipient"));
        msg.text = rec.value("text");
        result.emplace_back(std::move(msg));
    }
    return true;
}

bool SqliteDatabase::exec(const std::string &query, sqlite3_callback callback, void *context)
{
    if (!_handler)
    {
        std::cout << "DB_ERR: fail exec " << query << std::endl;
        return false;
    }
    if (query.empty())
    {
        std::cout << "DB_ERR: query is empty" << std::endl;
        return false;
    }

    char *errMsg {nullptr};
    if (std::lock_guard<std::mutex> lock(_mtx);
        sqlite3_exec(_handler, query.c_str(), callback, context, &errMsg))
    {
        sqlite3_free(errMsg);
        std::cout << "DB_ERR: " << errMsg << " "<< query << std::endl;
        return false;
    }
    return true;
}

int SqliteDatabase::maxId(const std::string &table, const std::string &id)
{
    std::string query = "SELECT MAX(" + id + ") FROM " + table + ";";
    std::string result;
    if (!sqlValue(query, "MAX(" + id + ")", result))
    {
        std::cout << "DB_ERR: " << query << std::endl;
        return false;
    }
    if (result.empty())
    {
        return invalidId();
    }
    return std::stoi(result);
}

bool SqliteDatabase::sqlValue(const std::string &query, const std::string &target, std::string &result)
{
    auto callback = [](void *context, int columns, char **data, char **names)
    {
        if (!columns || !data)
        {
            return 0;
        }
        auto result = reinterpret_cast<std::pair<std::string, std::string> *>(context);
        for (int i = 0; i < columns; ++i)
        {
            if (data[i] != nullptr && names[i] != nullptr)
            {
                if (names[i] == (*result).first && (*result).second.empty())
                {
                    (*result).second = data[i];
                    break;
                }
            }
        }
        return 0;
    };

    auto context = std::make_pair(target, std::string());
    if (!exec(query, callback, &context))
    {
        return false;
    }
    result = context.second;
    return true;
}

bool SqliteDatabase::sqlRecord(const std::string &query, SqlRec &result)
{
    auto callback = [](void *context, int columns, char **data, char **names)
    {
        if (!columns || !data)
        {
            return 0;
        }
        auto result = reinterpret_cast<SqlRec *>(context);
        for (int i = 0; i < columns; ++i)
        {
            if (data[i] != nullptr && names[i] != nullptr)
            {
                result->insert(names[i], data[i]);
            }
        }
        return 0;
    };

    if (!exec(query, callback, &result))
    {
        return false;
    }
    return true;
}

bool SqliteDatabase::sqlTable(const std::string &query, std::vector<SqlRec> &result)
{
    auto callback = [](void *context, int columns, char **data, char **names)
    {
        if (!columns || !data)
        {
            return 0;
        }
        auto result = reinterpret_cast<std::vector<SqlRec> *>(context);
        SqlRec rec;
        for (int i = 0; i < columns; ++i)
        {
            if (data[i] != nullptr && names[i] != nullptr)
            {
                rec.insert(names[i], data[i]);
            }
        }
        result->push_back(rec);
        return 0;
    };

    if (!exec(query, callback, &result))
    {
        return false;
    }
    return true;
}
