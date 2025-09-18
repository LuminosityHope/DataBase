#include <iostream>
#include "interface.h"
class PS:public DataBase
{
public:
    PS();
    ~PS() override;
    bool connect() override;
    bool disconnect() override;
    bool isconnected() override;
    bool writeUserFile(const std::string& name, const std::string& fileName) override;
    std::string readUserFile(const std::string& name) override;
private:
    bool connected=false;
    std::filesystem::path mainDataBasePath;
};