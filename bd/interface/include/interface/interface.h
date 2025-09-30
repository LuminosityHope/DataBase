#ifndef BD_INTERFACE_H
#define BD_INTERFACE_H

#include <filesystem>
#include <fstream>

enum class Error{failedToConnect,successConnect,successDisconnect,failed,successWriteToFile,failedWrite,successCreateDB,failedCreateDB,successRead,errorRead};
class DataBase {
public:
    DataBase()=default;
    virtual ~DataBase() = default;
    virtual Error disconnect()=0;
    virtual Error connect()=0;
    virtual bool isconnected()=0;
    virtual Error writeUserFile(const std::string& name, const std::string& fileName)=0;
    virtual Error readUserFile(const std::string& name)=0;

};
#endif //BD_INTERFACE_H