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
#include <ModifyOrder.h>

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
            std::cout << "'Subscribe BBO 'symbol' to execute Subscribe BBO command" << std::endl;
            std::cout << "'Unsubscribe BBO 'symbol' to execute Unsubscribe BBO command" << std::endl;
            std::cout << "'Subscribe VWAP 'symbol' 'quantity' to execute Subscribe BBO command" << std::endl;
            std::cout << "'Unsubscribe VWAP 'symbol' 'quantity' to execute Unsubscribe BBO command" << std::endl;
            std::cout << "'Order Modify 'id' 'quantity' 'price' to execute Order Modify command" << std::endl;
            std::cout << "'Order Cancel 'id' to execute Order Modify command" << std::endl;
            std::cout << "'Exit' to close application" << std::endl;

            std::string s;
            std::getline(std::cin, s);
            std::vector<std::string> args;
            getInputArgs(s, args);

            if (args.empty()) //Nothing
                std::cout << "Erroneous input" << std::endl;
            else if (args.size() > 1 && args[0] == "Print" && args[1] == "Full") //Print Full
                view::printFull();
            else if (args.size() > 1 && args[0] == "Print") { // Print
                if (args.size() == 2)
                    view::print(args[1]);
                else
                    std::cout << "Erroneous input" << std::endl;
            }
            else if (args.size() > 1 && args[0] == "Subscribe" && args[1] == "BBO") { //Subscribe BBO
                if (args.size() == 3)
                    if(!commands::bboSubscribe(args[2]))
                        std::cout << "Already subscribed" << std::endl;
                else
                    std::cout << "Erroneous input" << std::endl;
            }
            else if (args.size() > 1 && args[0] == "Unsubscribe" && args[1] == "BBO") { //Unsubscribe BBO
                if (args.size() == 3)
                    if(!commands::bboUnsubscribe(args[2]))
                        std::cout << "Not subscribed" << std::endl;
                else
                    std::cout << "Erroneous input" << std::endl;
            }
            else if (args.size() > 1 && args[0] == "Subscribe" && args[1] == "VWAP") { //Subscribe VWAP
                if (args.size() == 4) {
                    if (!commands::vwapSubscribe(args[2], std::stoull(args[3])))
                        std::cout << "Already subscribed" << std::endl;
                    else
                        std::cout << "Erroneous input" << std::endl;
                }
            }
            else if (args.size() > 1 && args[0] == "Unsubscribe" && args[1] == "VWAP") { //Unsubscribe VWAP
                if (args.size() == 4) {
                    if (!commands::vwapUnsubscribe(args[2], std::stoull(args[3])))
                        std::cout << "Not subscribed" << std::endl;
                    else
                        std::cout << "Erroneous input" << std::endl;
                }
            }
            else if (args.size() > 1 && args[0] == "Order" && args[1] == "Modify") { //Order Modify
                if (args.size() == 5)
                    if(!commands::orderModify(Command{"ORDER MODIFY", std::stoull(args[2]), std::stod(args[3]), std::stoull(args[4]), "",
                                                      OrderAction::BUY}))
                        std::cout << "Erroneous input" << std::endl;
            }
            else if (args.size() > 1 && args[0] == "Order" && args[1] == "Cancel") { //Order Cancel
                if (args.size() == 3)
                    if(!commands::orderCancel(Command{"ORDER CANCEL", std::stoull(args[2]), 0, 0, "",
                                                      OrderAction::BUY}))
                        std::cout << "Erroneous input" << std::endl;
            }
            else if (args[0] == "Exit") //Exit
                return;
            else //Nothing
                std::cout << "Erroneous input" << std::endl;

            view::printSubscribes(); //Print all subscribed positions
        }
    }
}