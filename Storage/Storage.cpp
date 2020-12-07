//
// Created by developer_stag on 07.12.2020.
//

#include "Storage.h"

void Storage::updateMaps(std::map<uint64_t, OrderData*> &sortedById, std::map<double, std::vector<OrderData*>> &sortedByPrice, Command &cmd)
{
    sortedById.insert(std::make_pair(cmd.order.id, &orders.back().data));

    std::vector<OrderData*> pOrders;
    if (!sortedByPrice.empty()) {
        auto i = sortedByPrice.find(cmd.order.price);
        if (i != sortedByPrice.end()) {
            pOrders = i->second;
        }
    }
    pOrders.push_back(&orders.back().data);
    sortedByPrice.insert(std::make_pair(cmd.order.price, pOrders));
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

auto Storage::getBuysByPriceIterator()
{
    return buysSortedByPrice.cbegin();
}

//    size_t getOrdersCount()
//    {
//        return orders.size();
//    }
//
//    size_t getOrderCount(const std::string& symbol)
//    {
//        size_t count = 0;
//        for (const auto& order : orders)
//        {
//            if (order.symbol == symbol)
//                count++;
//        }
//        return count;
//    }
//
//    void getOrder(const std::string& symbol, uint64_t& price, Order& order) const
//    {
//        while (sortedByPriceIterator != buysSortedByPrice.end())
//        {
//            if (sortedByPriceIterator->second.front()->symbol == symbol) {
//                order.symbol = sortedByPriceIterator->second.front()->symbol;
//                price = sortedByPriceIterator->first;
//                if (sortedByPriceIterator->second.size() > 1)
//                    for (auto i : sortedByPriceIterator->second) {
//                        order.quantity += i->quantity;
//                    }
//            }
//            std::next(sortedByPriceIterator);
//        }
//    }

size_t print(const std::string& symbol, uint64_t& price, Order& order)
{
    storage.getOrder(symbol, price, order);
    return 0;
}