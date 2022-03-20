#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include "IDatabase.h"
#include "sqlite/sqlite3.h"

#include <mutex>
#include <functional>


class SqlRec;

/**
 * @brief база sqlite
 */
class SqliteDatabase : public IDatabase
{
    const char *_dbName {nullptr};
    sqlite3 *_handler {nullptr};
    std::mutex _mtx;

public:

    SqliteDatabase(const char *dbName);
    ~SqliteDatabase();

    ///создать таблицы
    bool create() override;
    ///brief открыть базу
    bool open() override;

    int invalidId() const override {return -1;}

    /**
     * @brief добавить пользователя в таблицу
     * @return id нового пользователя
     */
    int insertUser(const std::pair<std::string, std::string> &values) override;
    bool getUserId(const std::string &login, int &result) override;
    bool getUserPassword(const int id, std::string &result) override;
    bool getUsername(const int id, std::string &result) override;
    bool getAllUsers(std::vector<UserInfo> &result) override;
    int insertMessage(int sender, int recipient, const std::string &text) override;
    bool getMessages(int user_1, int user_2, int lastId, std::vector<MessageInfo> &result) override;

private:
    ///выполнить запрос в базу
    bool exec(const std::string &query, sqlite3_callback callback = nullptr, void *context = nullptr);
    ///последний id (если автоинкремент)
    int maxId(const std::string &table, const std::string &id = "id");
    ///получить одно значение
    bool sqlValue(const std::string &query, const std::string &target, std::string &result);
    ///получить запись
    bool sqlRecord(const std::string &query, SqlRec &result);
    ///получить набор записей
    bool sqlTable(const std::string &query, std::vector<SqlRec> &result);
};

#endif // SQLITEDATABASE_H
