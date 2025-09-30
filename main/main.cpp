#include "interface.h"

#include "dlfcn.h"
#include "nlohmann/json.hpp"

#include <iostream>
#include <string>
std::map<Error, std::string> errorDescription = {
    {Error::successConnect, "Success connect"}, {Error::failedToConnect, "You are not signed"},
    {Error::successDisconnect,"Success disconnect"},{Error::failed,"Ошибка"},
    {Error::successWriteToFile,"Your file added to dataBase"},{Error::failedWrite,"File has not been added "},
    {Error::successCreateDB,"BD successfuly created"},{Error::failedCreateDB,"Fail created BD"}
};
typedef DataBase*(*CreateDataBase)();
int main() {

    std::string type;
    std::string jsonPath="package.json";
    std::ifstream ifs(jsonPath);
    if (!ifs.is_open()) {
        std::cerr << "Не удалось открыть файл: " << jsonPath << std::endl;
        return 1;
    }
    std::string json_string(std::istreambuf_iterator<char>(ifs), {});
    try {
        nlohmann::json j = nlohmann::json::parse(json_string);
        std::string my_value = j["DataType"];
        type=my_value;
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "Ошибка парсинга JSON: " << e.what() << std::endl;
        return 1;
    }
     std::string libraryPath="lib"+type+".so";

    void *libraryHandle= dlopen(libraryPath.c_str(), RTLD_LAZY);
    if (!libraryHandle) {
        fprintf(stderr, "dlopen() error: %s\n", dlerror());
        exit(1);
    }
    auto createDataBaseFunc = (CreateDataBase)dlsym(libraryHandle,"createDataBaseFunc");

    if (!createDataBaseFunc) {
        std::cerr << "Ошибка при поиске символа: " << dlerror() << std::endl;
        dlclose(libraryHandle);
        return {};
    }
     auto db=createDataBaseFunc();
    size_t number;
    std::cout<<"Actions with DB "<<std::endl;
    int helpAction;
    do {
        std::cout<<"Enter 1: Connect to DataBase"<<std::endl;
        std::cout<<"Enter 2: Write to DataBase"<<std::endl;
        std::cout<<"Enter 3: Read from DataBase"<<std::endl;
        std::cout<<"Enter 4: Disconnect from DataBase"<<std::endl;
        std::cout<<"Enter 5: Exit"<<std::endl;
        std::cin>>helpAction;
        switch(helpAction) {
            case 1: {
                Error message=db->connect();
                std::cerr<<errorDescription.at(message)<<std::endl;
                break;
            }
            case 2: {
                if (!db->isconnected()) {
                    Error message=Error::failedToConnect;
                    std::cerr<<errorDescription.at(message)<<std::endl;
                    break ;
                }
                std::string name;
                std::cout<<"Enter your name:";
                std::cin>>name;
                std::string filename;
                std::cout<<"Enter your file path:";
                std::cin.ignore();
                std::getline(std::cin,filename);
                Error message1=db->writeUserFile(name, filename);
                    std::cerr<<errorDescription.at(message1)<<std::endl;
                break;
            }
            case 3: {
                if (!db->isconnected()) {
                    Error message=Error::failedToConnect;
                    std::cerr<<errorDescription.at(message)<<std::endl;
                    break;
                }
                std::string name;
                std::cout<<"Enter your name:";
                std::cin>>name;
                db->readUserFile(name);
                break;
            }
            case 4: {
                Error error=db->disconnect();
                std::cerr<<errorDescription.at(error)<<std::endl;
                break;
            }
                case 5: {
                std::cout<<"Exit"<<std::endl;
                break;
            }
        }
    }while(helpAction!=5);
    return 0;
}