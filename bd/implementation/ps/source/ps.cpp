#include "ps.h"

#include <iostream>

const std::string mainDataPath="DataBaseFs";
PS::PS():connected(false),mainDataBasePath(mainDataPath){}
PS::~PS() {
    PS::disconnect();
}
Error PS::connect() {
    connected=true;
    std::filesystem::create_directories(mainDataBasePath);
    return Error::successConnect;
}
Error PS::disconnect() {
    connected=false;
    return Error::successDisconnect;
}
[[nodiscard]] bool PS::isconnected()
{
    return connected;
}
Error PS::writeUserFile(const std::string &name, const std::string &fileName) {
        std::filesystem::path folderName=mainDataBasePath/name;
        std::filesystem::create_directories(folderName);
        std::filesystem::path sourcePath=fileName;
        if (std::filesystem::exists(sourcePath)) {
        std::filesystem::path destPath=folderName/sourcePath.filename();
        if (std::filesystem::copy_file(sourcePath, destPath,std::filesystem::copy_options::overwrite_existing)) {
            return Error::successWriteToFile;
        }
        }
    return Error::failedWrite;

}
std::string PS::readUserFile(const std::string &name) {
    if (!connected) {
        return "";
    }
    std::filesystem::path absolutePath=std::filesystem::absolute(mainDataBasePath/name);
    if (!std::filesystem::exists(absolutePath)) {
        std::cerr<<"File does not exist"<<std::endl;
    }
    return absolutePath.string();
}
extern "C"
{
DataBase * createDataBaseFunc() {
        return new PS();
    }
}