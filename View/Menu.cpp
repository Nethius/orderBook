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
#include <CommandsParser.h>

void getInputArgs(const std::string &str, std::vector<std::string> &args) {
    std::stringstream sstr(str);
    std::string item;
    char d = 0x2C;
    while (std::getline(sstr, item, d)) {
        args.push_back(item);
    }
}

std::string fillCmd(const std::string name, Order order) {
    std::string temp;
    temp.append(name);
    temp.append(",");
    temp.append(std::to_string(order.id));
    temp.append(",");
    temp.append(order.data.symbol);
    temp.append(",");
    temp.append((order.side == OrderAction::BUY) ? "Buy," : "Sell,");
    temp.append(std::to_string(order.data.quantity));
    temp.append(",");
    temp.append(std::to_string(order.price));
    return temp;
}

namespace view {
    void menu() {
        while (true) {
            std::cout << "Enter: " << std::endl;
            std::cout << "'PRINT','symbol' to execute Print command " << std::endl;
            std::cout << "'PRINT FULL' to execute Print Full command " << std::endl;
            std::cout << "'SUBSCRIBE BBO','symbol' to execute Subscribe BBO command" << std::endl;
            std::cout << "'UNSUBSCRIBE BBO','symbol' to execute Unsubscribe BBO command" << std::endl;
            std::cout << "'SUBSCRIBE VWAP','symbol','quantity' to execute Subscribe BBO command" << std::endl;
            std::cout << "'UNSUBSCRIBE VWAP','symbol','quantity' to execute Unsubscribe BBO command" << std::endl;
            std::cout << "'ORDER ADD','id','symbol','side','quantity','price' to execute Order Add command"
                      << std::endl;
            std::cout << "'ORDER MODIFY','id','quantity','price' to execute Order Modify command" << std::endl;
            std::cout << "'ORDER CANCEL','id' to execute Order Cancel command" << std::endl;
            std::cout << "'EXIT' to close application" << std::endl;

            std::string s;
            std::getline(std::cin, s);
            std::vector<std::string> args;
            getInputArgs(s, args);


            if (args.empty()) //Nothing
                std::cout << "Erroneous input" << std::endl;
            else if (args[0] == "PRINT FULL") //Print Full
                view::printFull(commandParser::parser(fillCmd(args[0], Order{0, 0, 0, "", OrderAction::BUY})));
            else if (args[0] == "PRINT" && args.size() == 2) { // Print
                view::print(commandParser::parser(fillCmd(args[0], Order{0, 0, 0, args[1], OrderAction::BUY})));
            } else if (args[0] == "SUBSCRIBE BBO") { //Subscribe BBO
                commands::bboSubscribe(
                        commandParser::parser(fillCmd(args[0], Order{0, 0, 0, args[1], OrderAction::BUY})));
            } else if (args[0] == "UNSUBSCRIBE BBO") { //Unsubscribe BBO
                commands::bboUnsubscribe(
                        commandParser::parser(fillCmd(args[0], Order{0, 0, 0, args[1], OrderAction::BUY})));
            } else if (args[0] == "SUBSCRIBE VWAP") { //Subscribe VWAP
                commands::vwapSubscribe(commandParser::parser(
                        fillCmd(args[0], Order{0, 0, std::stoull(args[2]), args[1], OrderAction::BUY})));
            } else if (args[0] == "UNSUBSCRIBE VWAP") { //Unsubscribe VWAP
                commands::vwapUnsubscribe(commandParser::parser(
                        fillCmd(args[0], Order{0, 0, std::stoull(args[2]), args[1], OrderAction::BUY})));
            } else if (args[0] == "ORDER ADD") { //Order Add
                commands::orderAdd(commandParser::parser(
                        fillCmd(args[0], Order{std::stoull(args[1]), std::stod(args[5]), std::stoull(args[4]), args[2],
                                               static_cast<OrderAction>(std::stoi(
                                                       args[3]))})));
            } else if (args[0] == "ORDER MODIFY") { //Order Modify
                commands::orderModify(commandParser::parser(fillCmd(args[0],
                                                                    Order{std::stoull(args[1]), std::stod(args[3]),
                                                                          std::stoull(args[2]), "",
                                                                          OrderAction::BUY})));
            } else if (args[0] == "ORDER CANCEL") { //Order Cancel
                commands::orderCancel(commandParser::parser(
                        fillCmd(args[0], Order{std::stoull(args[1]), 0, 0, "", OrderAction::BUY})));
            } else if (args[0] == "EXIT") //Exit
                return;
            else //Nothing
                std::cout << "Erroneous input" << std::endl;

            view::printSubscribes(); //Print all subscribed positions
        }
    }
}