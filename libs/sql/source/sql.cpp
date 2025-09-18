#include "sql.h"
#include <iostream>
const std::string mainDataPath="DataBaseSql";
SQL::SQL() :connected(false),db(nullptr),dbPath(mainDataPath){}
SQL::~SQL() {
    if(connected) {
        SQL::disconnect();
    }
};
bool SQL::connect() {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия базы данных: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    } else {
        connected = true;
        std::cout << "База данных \"" << dbPath << "\" успешно открыта/создана." << std::endl;
        return true;
    }
    return false;
}
bool SQL::disconnect() {
    if (db) {
        sqlite3_close(db);
        std::cout << "База данных \"" << dbPath << "\" закрыта." << std::endl;
        return true;
    }
    return false;
}
bool SQL::isconnected() {
    return connected;
}
bool SQL::writeUserFile(const std::string &name, const std::string &fileName) {
        if (!db) {
            std::cerr << "База данных не подключена." << std::endl;
            return false;
        }

        std::string sql = "CREATE TABLE IF NOT EXISTS Users ("
                          "Name TEXT NOT NULL,"
                          "File BLOB NOT NULL);";

        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

        if (rc != SQLITE_OK) {
            std::cerr << "Ошибка создания таблицы: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            return false;
        } else {
            std::cout << "Таблица 'Users' успешно создана (или уже существовала)." << std::endl;
            return true;
        }
}
std::string SQL::readUserFile(const std::string &name) {
    return "";
}

