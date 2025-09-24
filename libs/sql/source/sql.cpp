#include "sql.h"

#include <iostream>

const std::string mainDataPath="DataBaseSql.db";
SQL::SQL() :connected(false),db(nullptr),dbPath(mainDataPath){}
SQL::~SQL() {
        SQL::disconnect();
};
bool SQL::connect() {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия базы данных: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    } else {
        connected = true;
        std::cout << "База данных \"" << dbPath << "\" успешно открыта/создана." << std::endl;
        createDataBase();
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
    std::ifstream file(fileName);
    if (std::filesystem::exists(fileName)) {
        if (file.is_open()) {
            std::ifstream file(fileName, std::ios::binary);
        }
    }
    std::string content{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
    const char* sql="INSERT INTO Users (Name, File,Content) VALUES (?, ?,?);";
    sqlite3_stmt *stmt;
    int rc=sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr<<"Error"<<std::endl;
    }
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, NULL);
    sqlite3_bind_text(stmt, 2, fileName.c_str(), -1, NULL);
    sqlite3_bind_blob(stmt,3,content.c_str(),content.size(),NULL);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}
std::string SQL::readUserFile(const std::string &name) {
    std::filesystem::path absolutePath=std::filesystem::absolute(mainDataPath.c_str());
    return absolutePath/name;
}
bool SQL::createDataBase() {
    if (!db) {
        std::cerr << "База данных не подключена." << std::endl;
        return false;
    }

    std::string sql = "CREATE TABLE IF NOT EXISTS Users ("
                      "Name TEXT NOT NULL,"
                      "File BLOB NOT NULL,"
                      "Content TEXT NOT NULL);";

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
extern "C"
{
DataBase* createDataBaseFunc() {
        return new SQL();
    }
}

