#include <iostream>

#include "trade.hpp"

Trade::Trade(std::int64_t buy_order_id, std::int64_t sell_order_id,
             std::uint64_t price, std::int64_t quantity)
    : buy_order_id_{buy_order_id}, sell_order_id_{sell_order_id}, price_{price},
      quantity_{quantity} {}

std::int64_t Trade::get_buy_order_id() const { return buy_order_id_; }
std::int64_t Trade::get_sell_order_id() const { return sell_order_id_; }
std::uint64_t Trade::get_price() const { return price_; }
std::int64_t Trade::get_quantity() const { return quantity_; }
