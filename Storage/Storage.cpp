//
// Created by developer_stag on 07.12.2020.
//

#include "Storage.h"
#include <utility>

void Storage::updateMaps(orders_by_id_t &sortedById, orders_by_price_t &sortedByPrice, Command &cmd)
{
    sortedById.insert(std::make_pair(cmd.order.id, &orders.back().data));

    std::vector<OrderData*> pOrders;
    if (!sortedByPrice.empty()) {
        auto i = sortedByPrice.find(std::make_pair(cmd.order.price, cmd.order.data.symbol));
        if (i != sortedByPrice.end()) {
            pOrders = i->second;
        }
    }
    pOrders.push_back(&orders.back().data);
    sortedByPrice.insert_or_assign(std::make_pair(cmd.order.price, cmd.order.data.symbol), std::move(pOrders));
}
bool Storage::insertOrder(Command &cmd)
{
    if (!buysSortedById.empty() && buysSortedById.find(cmd.order.id) != buysSortedById.end() ||
        !sellsSortedById.empty() && sellsSortedById.find(cmd.order.id) != sellsSortedById.end()){
        std::cout << "already has order with given order id" << std::endl;
        return false;
    }
    try {
        orders.push_back(cmd.order);
        if (cmd.order.side == OrderAction::BUY)
            updateMaps(buysSortedById, buysSortedByPrice, cmd);
        else
            updateMaps(sellsSortedById, sellsSortedByPrice, cmd);
    }
    catch (...)
    {
        std::cout << "error while insert new order" << std::endl;
        return false;
    }
    return true;
}

orders_by_price_t::const_iterator Storage::getBuysByPriceBegin()
{
    return buysSortedByPrice.cbegin();
}

orders_by_price_t::const_iterator Storage::getBuysByPriceEnd()
{
    return buysSortedByPrice.cend();
}

bool Storage::getDataForPrint(orders_by_price_t::const_iterator it, Order &order, size_t &ordersCount,
                              const std::string &pattern) {
    auto a = it->second.front()->symbol;
    if (a == pattern) {
        ordersCount = 1;
        order.data.symbol = it->second.front()->symbol;
        order.price = it->first.first;
        if (it->second.size() > 1)
            for (auto i : it->second) {
                ordersCount++;
                order.data.quantity += i->quantity;
            }
        return true;
    }
    return false;
}
