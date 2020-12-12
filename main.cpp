#include <iostream>
#include <CommandsParser.h>
#include <iomanip>
#include <fstream>
#include <Menu.h>

int main() {

    std::cout << "Order list" << std::endl;


    std::ifstream f(R"(C:\Users\Astan\Downloads\1.csv)");

    std::string str;
    std::vector<Command> commands;
    while(std::getline(f, str))
        commands.push_back(parser(str));

    Storage& storage = Storage::instance();
    for (auto command : commands)
    {
        storage.insertOrder(command);
    }

    view::menu();

    return 0;
}
