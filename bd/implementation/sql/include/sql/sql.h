#ifndef SQL_H
#define SQL_H
#include "interface.h"

#include "sqlite3.h"

class SQL:public DataBase {
public:
    SQL();
    ~SQL() override;
    Error connect() override;
    Error disconnect() override;
    bool isconnected() override;
    Error writeUserFile(const std::string& name, const std::string& fileName) override;
    Error createDataBase();
    Error readUserFile(const std::string& name) override;
private:
    bool connected=false;
    sqlite3* db;
    std::string dbPath;
};

#endif