//
// Created by Astan on 12.12.2020.
//

#include "Menu.h"
#include <iostream>
#include <string>
#include <Print.h>
#include <PrintFull.h>
#include "vector"
#include "sstream"
#include <SubscribesView.h>
#include <Subscribes.h>

void getInputArgs(const std::string& str, std::vector<std::string>& args)
{
    std::stringstream sstr(str);
    std::string item;
    char d = 0x20;
    while (std::getline(sstr, item, d)) {
        args.push_back(item);
    }
}

namespace view {
    void menu() {
        while (true) {
            std::cout << "Enter: " << std::endl;
            std::cout << "'Print 'symbol'' to execute Print command " << std::endl;
            std::cout << "'Print Full' to execute Print Full command " << std::endl;
            std::cout << "'Subscribe BBO 'symbol' to execute Subscribe BBO" << std::endl;
            std::cout << "'Unsubscribe BBO 'symbol' to execute Unsubscribe BBO" << std::endl;
            std::cout << "'Exit' to close application" << std::endl;

            std::string s;
            std::getline(std::cin, s);
            std::vector<std::string> args;
            getInputArgs(s, args);

            if (args.empty())
                std::cout << "Erroneous input" << std::endl;
            else if (args.size() > 1 && args[0] == "Print" && args[1] == "Full")
                view::printFull();
            else if (args.size() > 1 && args[0] == "Print") {
                if (args.size() == 2)
                    view::print(args[1]);
                else
                    std::cout << "Erroneous input" << std::endl;
            }
            else if (args.size() > 1 && args[0] == "Subscribe" && args[1] == "BBO") {
                if (args.size() == 3)
                    commands::bboSubscribe(args[2]);
                else
                    std::cout << "Erroneous input" << std::endl;
            }
            else if (args.size() > 1 && args[0] == "Unsubscribe" && args[1] == "BBO") {
                if (args.size() == 3)
                    commands::bboUnsubscribe(args[2]);
                else
                    std::cout << "Erroneous input" << std::endl;
            }
            else if (args[0] == "Exit")
                return;
            else
                std::cout << "Erroneous input" << std::endl;

            view::printSubscribes();
        }
    }
}