#include <iostream>
#include <CommandsParser.h>
#include <iomanip>
#include <fstream>
#include <Print.h>

int main() {

    std::cout << "Order list" << std::endl;


    std::ifstream f(R"(C:\Users\developer_stag\Downloads\1.csv)");

    std::string str;
    std::vector<Command> commands;
    while(std::getline(f, str))
        commands.push_back(parser(str));

    Storage storage;
    for (auto command : commands)
    {
        storage.insertOrder(command);
    }

    print(storage, "AAPL");

    return 0;
}
