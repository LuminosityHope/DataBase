#include "ps.h"

const std::string mainDataPath="DataBaseFs";
PS::PS():connected(false),mainDataBasePath(mainDataPath){}
PS::~PS() {
    PS::disconnect();
    std::cout << "База данных \"" << mainDataPath << "\" закрыта." << std::endl;
}
bool PS::connect() {
    connected=true;
    std::filesystem::create_directories(mainDataBasePath);
    std::cout << "База данных \"" << mainDataPath << "\" успешно открыта/создана." << std::endl;
    return true;
}
bool PS::disconnect() {
    connected=false;
    std::cout<<"You are disconnected";
    return true;
}
bool PS::isconnected()  {
    if(connected)
        std::cout<<"You are signed"<<std::endl;
    else
        std::cout<<"You are not signed"<<std::endl;
    return connected;
}
bool PS::writeUserFile(const std::string &name, const std::string &fileName) {
    if (!isconnected()) {
        return false;
    }
    try {
        std::filesystem::path folderName=mainDataBasePath/name;
        std::filesystem::create_directories(folderName);
        std::filesystem::path sourcePath=fileName;
        if (std::filesystem::exists(sourcePath)) {
        std::filesystem::path destPath=folderName/sourcePath.filename();
        if (std::filesystem::copy_file(sourcePath, destPath,std::filesystem::copy_options::overwrite_existing)) {
            std::cout << "Файл "<<sourcePath.filename()<<" был успешно добавлен в базу данных"<< std::endl;
        }
        }
        return true;

    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return false;
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