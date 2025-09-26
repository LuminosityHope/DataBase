#include "sql.h"

#include <iostream>

const std::string mainDataPath="DataBaseSql.db";
SQL::SQL() :connected(false),db(nullptr),dbPath(mainDataPath){}
SQL::~SQL() {
        SQL::disconnect();
};
Error SQL::connect() {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия базы данных: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    } else {
        connected = true;
        createDataBase();
        return Error::successConnect;
    }
    return Error::failedToConnect;
}
Error SQL::disconnect() {
    if (db) {
        connected=false;
        sqlite3_close(db);
        return Error::successDisconnect;
    }
    return Error::failed;
}
[[nodiscard]] bool SQL::isconnected() {
    return connected;
}
Error SQL::writeUserFile(const std::string &name, const std::string &fileName) {
    std::ifstream file(fileName);
    if (std::filesystem::exists(fileName)) {
        if (file.is_open()) {
            std::ifstream file(fileName, std::ios::binary);
        }
    }
    else {
        return Error::failedWrite;
    }
    std::string content{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
    const char* sql="INSERT INTO Users (Name, File,Content) VALUES (?, ?,?);";
    sqlite3_stmt *stmt;
    int rc=sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return Error::failedWrite;
    }
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, NULL);
    sqlite3_bind_text(stmt, 2, fileName.c_str(), -1, NULL);
    sqlite3_bind_blob(stmt,3,content.c_str(),content.size(),NULL);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return Error::successWriteToFile;
}
std::string SQL::readUserFile(const std::string &name) {
    std::filesystem::path absolutePath=std::filesystem::absolute(mainDataPath.c_str());
    return absolutePath/name;
}
Error SQL::createDataBase() {
    if (!db) {
        return Error::failedToConnect;
    }

    std::string sql = "CREATE TABLE IF NOT EXISTS Users ("
                      "Name TEXT NOT NULL,"
                      "File BLOB NOT NULL,"
                      "Content TEXT NOT NULL);";

    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr,nullptr);

    if (rc != SQLITE_OK) {
        return Error::failedCreateDB;
    } else {
        return Error::successCreateDB;
    }
}
extern "C"
{
DataBase* createDataBaseFunc() {
        return new SQL();
    }
}
