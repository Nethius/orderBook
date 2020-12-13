//
// Created by Astan on 13.12.2020.
//

#ifndef ORDERBOOK_MODIFYORDER_H
#define ORDERBOOK_MODIFYORDER_H
#include <Storage.h>

namespace commands {
    bool orderAdd(Command&& cmd);

    bool orderModify(Command&& cmd);

    bool orderCancel(Command&& cmd);
}
#endif //ORDERBOOK_MODIFYORDER_H
