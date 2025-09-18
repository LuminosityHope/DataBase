#include "ps.h"

const std::string mainDataPath="DataBaseFs";
PS::PS():connected(false),mainDataBasePath(mainDataPath){}
PS::~PS() {
    if (connected) {
    PS::disconnect();
    }
}
bool PS::connect() {
    connected=true;
    std::filesystem::create_directories(mainDataBasePath);
    return true;
}
bool PS::disconnect() {
    connected=false;
    return true;
}
bool PS::isconnected()  {
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
        std::filesystem::path destPath=folderName/sourcePath.filename();
        std::filesystem::copy_file(sourcePath, destPath,std::filesystem::copy_options::overwrite_existing);
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
    return absolutePath.string();
}