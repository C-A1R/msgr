#include "Database.h"

#include <iostream>
#include <memory>

Database::Database(const char *dbName) : _dbName{dbName}
{
}

Database::~Database()
{
    sqlite3_close(_handler);
}

bool Database::create()
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

bool Database::open()
{
    if (sqlite3_open(_dbName, &_handler))
    {
        std::cout << "DB_ERR: database is not opened " << sqlite3_errmsg(_handler) << std::endl;
        return false;
    }
    return true;
}

int Database::insertUser(const std::string &login, const std::string &password)
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

bool Database::getUserId(const std::string &login, int &id)
{
    std::string query = "SELECT id FROM users WHERE login = '" + login + "';";
    std::string result;
    if (!value(query, result))
    {
        std::cout << "DB_ERR: " << query << std::endl;
        return false;
    }
    if (!result.empty())
        id = stoi(result);
    return true;
}

bool Database::getUserPassword(const int id, std::string &result)
{
    std::string query = "SELECT password FROM users WHERE id = " + std::to_string(id) + ";";
    if (!value(query, result))
    {
        std::cout << "DB_ERR: " << query << std::endl;
        return false;
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

bool Database::exec(const std::string &query, sqlite3_callback callback, void *context)
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

int Database::callback(void *context, int columns, char **data, char **)
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

int Database::maxId(const std::string &table, const std::string &id)
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

bool Database::value(const std::string &query, std::string &value)
{
    std::unique_ptr<std::string> context_str(new std::string());
    if (!exec(query, &callback, context_str.get()))
    {
        return false;
    }
    value = (*context_str);
    return true;
}
