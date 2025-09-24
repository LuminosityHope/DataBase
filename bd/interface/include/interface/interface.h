#ifndef BD_INTERFACE_H
#define BD_INTERFACE_H

#include <filesystem>
#include <fstream>

enum class DataType {
    SQL,FileSystem
};
class DataBase {
public:
    DataBase()=default;
    virtual ~DataBase() = default;
    virtual bool disconnect()=0;
    virtual bool connect()=0;
    virtual bool isconnected()=0;
    virtual bool writeUserFile(const std::string& name, const std::string& fileName)=0;
    virtual std::string readUserFile(const std::string& name)=0;
    std::unique_ptr<DataBase> create(DataType type);

};
#endif //BD_INTERFACE_H