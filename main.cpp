#include <iostream>
#include <CommandsParser.h>
#include <iomanip>
#include <fstream>
#include <Menu.h>
#include <ModifyOrder.h>

int main() {

    std::cout << "Order list" << std::endl;


    std::ifstream f(R"(C:\Users\Astan\Downloads\1.csv)");

    std::string str;
    std::vector<Command> commands;
    while(std::getline(f, str))
        commands.push_back(parser(str));

    for (auto command : commands)
    {
        commands::orderAdd(command);
    }

    view::menu();

    return 0;
}
