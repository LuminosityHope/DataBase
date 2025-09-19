#include "iostream"
#include "ps/ps.h"
#include "sql/sql.h"
int main() {
    size_t help;
    std::cout<<"---------DataBase Management-------------"<<std::endl;
    std::cout<<"Enter 1-Choose DataBase type"<<std::endl;
    std::cout<<"Enter 2-Exit"<<std::endl;
    std::cin>>help;
    switch(help) {
        case 1:
            size_t helpDb;
            std::cout<<"------Choose DataBase type------"<<std::endl;
            std::cout<<"Enter 1-FileSystem DataBase"<<std::endl;
            std::cout<<"Enter 2-SQL DataBase"<<std::endl;
            std::cin>>helpDb;
            switch(helpDb) {
                case 1: {
                    auto dbPs=PS();
                    std::cout<<"Actions with DB"<<std::endl;
                    int helpAction;
                    do {
                        std::cout<<"Enter 1-Connect to DataBase"<<std::endl;
                        std::cout<<"Enter 2-Write to DataBase"<<std::endl;
                        std::cout<<"Enter 3-Read from DataBase"<<std::endl;
                        std::cout<<"Enter 4-Disconnect from DataBase"<<std::endl;
                        std::cin>>helpAction;
                        switch(helpAction) {
                            case 1: {
                                dbPs.connect();
                                break;
                            }
                            case 2: {
                                std::string name;
                                std::cout<<"Enter your name:";
                                std::cin>>name;
                                std::string filename;
                                std::cout<<"Enter your file name:";
                                std::cin>>filename;
                                dbPs.writeUserFile(name, filename);
                                break;
                            }
                            case 3: {
                                std::string name;
                                std::cout<<"Enter your name:";
                                std::cin>>name;
                                std::cout<<dbPs.readUserFile(name)<<std::endl;
                                break;
                            }
                            case 4: {
                                dbPs.disconnect();
                                break;
                            }
                        }
                    }while(helpAction!=4);
                }
                case 2: {
                    auto dbSql=SQL();
                    std::cout<<"Actions with DB"<<std::endl;
                    int helpAction;
                    do {
                        std::cout<<"Enter 1-Connect to DataBase"<<std::endl;
                        std::cout<<"Enter 2-Write to DataBase"<<std::endl;
                        std::cout<<"Enter 3-Read from DataBase"<<std::endl;
                        std::cout<<"Enter 4-Disconnect from DataBase"<<std::endl;
                        std::cin>>helpAction;
                        switch(helpAction) {
                            case 1: {
                                dbSql.connect();
                                break;
                            }
                            case 2: {
                                std::string name;
                                std::cout<<"Enter your name:";
                                std::cin>>name;
                                std::string filename;
                                std::cout<<"Enter your file name:";
                                std::cin>>filename;
                                dbSql.writeUserFile(name, filename);
                                break;
                            }
                            case 3: {
                                std::string name;
                                std::cout<<"Enter your name:";
                                std::cin>>name;
                                std::cout<<"Путь до вашей папки: "<<dbSql.readUserFile(name)<<std::endl;
                                break;
                            }
                            case 4: {
                                return 0;
                            }
                        }
                    }while(helpAction!=4);
                }
            }
        case 2: {
                return 0;
            }
    }
    return 0;
}