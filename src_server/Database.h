#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite/sqlite3.h"

#include <string>
#include <vector>
#include <mutex>
#include <functional>

/**
 * @brief через этот класс происходит работа с базой
 */
class Database
{
    const char *_dbName {nullptr};
    sqlite3 *_handler {nullptr};
    std::mutex _mtx;
public:
    const std::string _ok {"OK\n"};

    Database(const char *dbName);
    ~Database();

    int invalidId() const {return -1;}

    /**
     * @brief создать таблицы
     */
    bool create();

    /**
     * @brief открыть базу и создать пустые таблицы
     */
    bool open();

    /**
     * @brief добавить пользователя в таблицу
     */
    int insertUser(const std::string &login, const std::string &password);




    /**
     * @brief очистить таблицу
     */
    std::string truncate(const std::string &table);

    /**
     * @brief пересечение таблиц А и В
     */
    std::string intersection();

    /**
     * @brief симметричная разница таблиц А и В
     */
    std::string symmetricDifference();

private:
    /**
     * @brief выполнить запрос в базу
     */
    std::string exec(const std::string &query, sqlite3_callback callback = nullptr, void *context = nullptr);

    /**
     * @brief заполняет context результатом выборки
     */
    static int callback(void *context, int columns, char **data, char **);

private:
    int maxId(const std::string &table, const std::string &id = "id");
};

#endif // DATABASE_H
