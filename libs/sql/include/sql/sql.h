#ifndef SQL_H
#define SQL_H
#include "interface.h"

#include "sqlite3.h"

class SQL:public DataBase {
public:
    SQL();
    ~SQL() override;
    bool connect() override;
    bool disconnect() override;
    bool isconnected() override;
    bool writeUserFile(const std::string& name, const std::string& fileName) override;
    bool createDataBase();
    std::string readUserFile(const std::string& name) override;
private:
    bool connected=false;
    sqlite3* db;
    std::string dbPath;
};

#endif