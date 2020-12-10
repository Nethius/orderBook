//
// Created by developer_stag on 08.12.2020.
//

#include <Print.h>
#include <iomanip>

struct PrintData
{
    size_t count;
    Order order;
};

void formatPrint(std::vector<PrintData>& buys, std::vector<PrintData>& sells)
{
    for (size_t i = 0; i < std::max(buys.size(), sells.size()); i++)
        std::cout << std::setw(20) << std::left << buys[i].order.data.symbol << std::setw(20) << std::left << buys[i].count
                  << std::setw(20) << std::left << buys[i].order.price << std::setw(20) <<  std::endl;
}



void print(Storage &storage, const std::string &symbol) {
    std::vector<PrintData> buys;
    std::vector<PrintData> sells;
    auto buysByPriceIterator = storage.getBuysByPriceBegin();

    std::cout << std::setw(20) << std::left << "orders" << std::setw(20) << std::left << "volume"
              << std::setw(20) << std::left << "bid" << std::setw(20) << std::left << "ask" << std::setw(20)
              << std::left << "volume" << std::setw(20) << std::left << "orders" << std::endl;

    while(true)
    {
        if (buysByPriceIterator != storage.getBuysByPriceEnd())
        {
            size_t buysCount;
            Order buysData;
            if(storage.getDataForPrint(buysByPriceIterator, buysData, buysCount, symbol))
            {
                buys.push_back(PrintData{buysCount, buysData});
            }
            buysByPriceIterator = std::next(buysByPriceIterator);
        }
//        if (sellsByPriceIterator != storage.getSellsByPriceEnd())
//        {
//            size_t sellsCount;
//            Order sellsData;
//            if(storage.getDataForPrint(sellsByPriceIterator, sellsData, sellsCount, symbol))
//            {
//                buys.push_back(PrintData{sellsCount, sellsData});
//                sellsByPriceIterator = std::next(sellsByPriceIterator);
//            }
//
//        }
//        if (buys.size() == 10 || sells.size() == 10)
            formatPrint(buys, sells);
    }
}