//
// Created by Astan on 13.12.2020.
//

#include <MdReplay.h>
#include <fstream>
#include <vector>
#include <Storage/Storage.h>
#include <View/SubscribesView.h>
#include <Subscribes.h>
#include <ModifyOrder.h>
#include <Parser/CommandsParser.h>
#include <View/Print.h>
#include <View/PrintFull.h>

namespace commands {
    void execCommandsFromFile(std::string path, std::string symbol)
    {
        std::ifstream f(path);
        if (!f.good()) {
            std::cout << "file does not exist" << std::endl;
            return;
        }
        std::string str;
        std::vector<Command> commands;
        while(std::getline(f, str))
            commands.push_back(commandParser::parser(str));

        for (auto command : commands)
        {
            if (command.commandName.empty()) //Nothing
                std::cout << "Erroneous input" << std::endl;
            else if (command.commandName == "PRINT FULL" && (symbol.empty() ? true : command.order.data.symbol == symbol)) //Print Full
                view::printFull(std::move(command));
            else if (command.commandName == "PRINT" && (symbol.empty() ? true : command.order.data.symbol == symbol)) { // Print
                view::print(std::move(command));
            } else if (command.commandName == "SUBSCRIBE BBO") { //Subscribe BBO
                commands::bboSubscribe(std::move(command));
            } else if (command.commandName == "UNSUBSCRIBE BBO") { //Unsubscribe BBO
                commands::bboUnsubscribe(std::move(command));
            } else if (command.commandName == "SUBSCRIBE VWAP") { //Subscribe VWAP
                commands::vwapSubscribe(std::move(command));
            } else if (command.commandName == "UNSUBSCRIBE VWAP") { //Unsubscribe VWAP
                commands::vwapUnsubscribe(std::move(command));
            } else if (command.commandName == "ORDER ADD") { //Order Add
                commands::orderAdd(std::move(command));
            } else if (command.commandName == "ORDER MODIFY") { //Order Modify
                commands::orderModify(std::move(command));
            } else if (command.commandName == "ORDER CANCEL") { //Order Cancel
                commands::orderCancel(std::move(command));
            } else if (command.commandName == "EXIT") //Exit
                return;
            else //Nothing
                std::cout << "Erroneous input" << std::endl;

            view::printSubscribes(symbol); //Print all subscribed positions
        }
    }
}