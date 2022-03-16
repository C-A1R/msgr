#include "Database.h"

#include <iostream>

Database::Database(const char *dbName) : _dbName{dbName}
{
}

Database::~Database()
{
    sqlite3_close(_handler);
    remove(_dbName);
}

bool Database::create()
{
    bool result{true};
    if (exec("CREATE TABLE IF NOT EXISTS users ("
             "id INTEGER PRIMARY KEY AUTOINCREMENT, "
             "login VARCHAR(255), "
             "password VARCHAR(255));") != _ok)
    {
        result = false;
    }

    if (!result)
    {
        std::cout << "DB_ERR: tables are not created " << sqlite3_errmsg(_handler) << std::endl;
    }
    return result;
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
    auto a = exec(query);
    std::cout << query << std::endl;
    std::cout << a << std::endl;
    if (a != _ok)
    {
        return invalidId();
    }
    return maxId("users");
}

std::string Database::truncate(const std::string &table)
{
    if (table.empty())
    {
        return "DB_ERR: invalid query\n";
    }
    std::string query = "DELETE FROM " + table + ";";
    return exec(query);
}

std::string Database::intersection()
{
    std::string query = "SELECT A.id, A.name, B.name FROM A INNER JOIN B ON A.id = B.id;";
    std::string *context_str = new std::string();
    auto result = exec(query, &callback, context_str);
    std::string response;
    if (result == _ok)
    {
        response = (*context_str) + _ok;
    }
    else
    {
        response = result;
    }
    delete context_str;
    return response;
}

std::string Database::symmetricDifference()
{
    std::string query = "SELECT A.*, B.name FROM A LEFT JOIN B ON A.id = B.id WHERE B.id IS NULL "
                        "UNION "
                        "SELECT B.id, A.name, B.name FROM B LEFT JOIN A ON B.id = A.id WHERE A.id IS NULL;";

    std::string *context_str = new std::string();
    auto result = exec(query, &callback, context_str);
    std::string response;
    if (result == _ok)
    {
        response = (*context_str) + _ok;
    }
    else
    {
        response = result;
    }
    delete context_str;
    return response;
}

std::string Database::exec(const std::string &query, sqlite3_callback callback, void *context)
{
    if (!_handler)
    {
        return "DB_ERR: fail exec\n";
    }
    if (query.empty())
    {
        return "DB_ERR: query is empty\n";
    }

    char *errMsg {nullptr};
    if (std::lock_guard<std::mutex> lock(_mtx);
        sqlite3_exec(_handler, query.c_str(), callback, context, &errMsg))
    {
        auto result = std::string("DB_ERR: ") + errMsg +'\n';
        sqlite3_free(errMsg);
        return result;
    }
    return _ok;
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
    (*result) += '\n';
    return 0;
}

int Database::maxId(const std::string &table, const std::string &id)
{
    std::string *context_str = new std::string();
    std::string query = "SELECT MAX(" + id+ ") FROM " + table + ";";
    auto result = exec(query, &callback, context_str);
    std::string response;
    if (result == _ok)
    {
        response = (*context_str) + _ok;
    }
    else
    {
        response = result;
    }
    delete context_str;
    return std::stoi(response);
}
