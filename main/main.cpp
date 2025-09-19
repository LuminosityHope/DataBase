#include <iostream>
#include <fstream>
#include "dlfcn.h"
#include "interface.h"
#include "nlohmann/json.hpp"
int main() {
    DataType type;
    std::string jsonPath="/home/saveliy/Рабочий стол/BD/main/package.json";
    std::ifstream ifs(jsonPath);
    if (!ifs.is_open()) {
        std::cerr << "Не удалось открыть файл: " << jsonPath << std::endl;
        return 1;
    }
    std::string json_string(std::istreambuf_iterator<char>(ifs), {});
    try {
        nlohmann::json j = nlohmann::json::parse(json_string);

        // 4. Получаем нужную строку из JSON (предполагая, что у вас есть поле "my_string")
        DataType my_value = j["DataType"];
        type=my_value;
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "Ошибка парсинга JSON: " << e.what() << std::endl;
        return 1;
    }
    void* libraryHandle=dlopen("libsql.so", RTLD_LAZY);
    if (!libraryHandle) {
        fprintf(stderr, "dlopen() error: %s\n", dlerror());
        exit(1);
    }
    return 0;
}