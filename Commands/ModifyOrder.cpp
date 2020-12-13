//
// Created by Astan on 13.12.2020.
//

#include "ModifyOrder.h"

namespace commands {
    bool orderAdd(Command &cmd)
    {
        if (cmd.commandName != "ORDER ADD") {
            std::cout << "Wrong command signature: " << cmd.commandName << std::endl;
            return false;
        }
        Storage &storage = Storage::instance();
        return storage.insertOrder(cmd.order);
    }

    bool orderModify(Command cmd){
        if (cmd.commandName != "ORDER MODIFY")
        {
            std::cout << "Wrong command signature: " << cmd.commandName << std::endl;
            return false;
        }
        Storage &storage = Storage::instance();
        return storage.modifyOrder(cmd.order);
    }

//    bool orderCancel(Command &cmd){
//        if (cmd.commandName != "ORDER CANCEL")
//        {
//            std::cout << "Wrong command signature: " << cmd.commandName << std::endl;
//            return false;
//        }
//        return true;
//    }
}