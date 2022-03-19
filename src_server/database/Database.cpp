#include "Database.h"
#include "SqlRec.h"

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
    if (!exec("CREATE TABLE IF NOT EXISTS users ("
             "id INTEGER PRIMARY KEY AUTOINCREMENT, "
             "login VARCHAR(255), "
             "password VARCHAR(255));"))
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

int SqliteDatabase::insertUser(const std::string &login, const std::string &password)
{
    std::string query = "INSERT INTO users (login, password) VALUES (\""
                 + login + "\", \"" + password + "\");";
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
    if (!value(query, id))
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
    if (!value(query, result))
    {
        std::cout << "DB_ERR: " << query << std::endl;
        return false;
    }
    return true;
}

bool SqliteDatabase::getUserData(const std::string &ids, std::string &result)
{
    std::string query = "SELECT * FROM users WHERE id IN (" + ids + ");";
    std::cout << "query: " << query << std::endl;
    std::unique_ptr<std::string> context_str(new std::string());
    if (!exec(query, &callback, context_str.get()))
    {
        return false;
    }
    result = (*context_str);
    std::cout << "result: " << result << std::endl;
    return true;
}

bool SqliteDatabase::getAllUsersData(std::vector<std::tuple<std::string, std::string> > &result)
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
        result.push_back(std::make_tuple(rec.value("id"), rec.value("login")));
    }
    return true;
}

//std::string Database::truncate(const std::string &table)
//{
//    if (table.empty())
//    {
//        return "DB_ERR: invalid query\n";
//    }
//    std::string query = "DELETE FROM " + table + ";";
//    return exec(query);
//}

//std::string Database::intersection()
//{
//    std::string query = "SELECT A.id, A.name, B.name FROM A INNER JOIN B ON A.id = B.id;";
//    std::string *context_str = new std::string();
//    auto result = exec(query, &callback, context_str);
//    std::string response;
//    if (result == _ok)
//    {
//        response = (*context_str) + _ok;
//    }
//    else
//    {
//        response = result;
//    }
//    delete context_str;
//    return response;
//}

//std::string Database::symmetricDifference()
//{
//    std::string query = "SELECT A.*, B.name FROM A LEFT JOIN B ON A.id = B.id WHERE B.id IS NULL "
//                        "UNION "
//                        "SELECT B.id, A.name, B.name FROM B LEFT JOIN A ON B.id = A.id WHERE A.id IS NULL;";

//    std::string *context_str = new std::string();
//    auto result = exec(query, &callback, context_str);
//    std::string response;
//    if (result == _ok)
//    {
//        response = (*context_str) + _ok;
//    }
//    else
//    {
//        response = result;
//    }
//    delete context_str;
//    return response;
//}

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

int SqliteDatabase::callback(void *context, int columns, char **data, char **)
{
    if (!columns || !data)
    {
        return 0;
    }
    auto result = reinterpret_cast<std::string *>(context);
    for (int i = 0; i < columns; ++i)
    {
        if (data[i] != nullptr)
        {
            (*result) += data[i];
        }
        if (i != columns - 1)
        {
            (*result) += ',';
        }
    }
    return 0;
}

int SqliteDatabase::callback_2(void *context, int columns, char **data, char **names)
{
    if (!columns || !data)
    {
        return 0;
    }
    auto result = reinterpret_cast<std::vector<SqlRec> *>(context);
    SqlRec rec;
    for (int i = 0; i < columns; ++i)
    {
        if (data[i] != nullptr)
        {
            rec.insert(names[i], data[i]);
        }
    }
    result->push_back(rec);
    return 0;
}

int SqliteDatabase::maxId(const std::string &table, const std::string &id)
{
    std::unique_ptr<std::string> context_str(new std::string());
    std::string query = "SELECT MAX(" + id+ ") FROM " + table + ";";
    if (!exec(query, &callback, context_str.get()))
    {
        return invalidId();
    }
    std::string response = (*context_str);
    if (response.empty())
    {
        return invalidId();
    }
    return std::stoi(response);
}

bool SqliteDatabase::value(const std::string &query, std::string &value)
{
    std::unique_ptr<std::string> context_str(new std::string());
    if (!exec(query, &callback, context_str.get()))
    {
        return false;
    }
    value = (*context_str);
    return true;
}

bool SqliteDatabase::sqlTable(const std::string &query, std::vector<SqlRec> &recs)
{
    if (!exec(query, &callback_2, &recs))
    {
        return false;
    }
//    for (const auto &rec : recs)
//    {
//        std::cout << "id=\"" << rec.value("id") <<  "\" login=\"" << rec.value("login") << "\"" << std::endl;
//    }
    return true;
}
