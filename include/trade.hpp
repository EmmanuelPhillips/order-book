#pragma once

#include <cstdint>

#include <iostream>

class Trade {
private:
  std::int64_t buy_order_id_;
  std::int64_t sell_order_id_;
  std::uint64_t price_;
  std::int64_t quantity_;

public:
  Trade(std::int64_t buy_order_id, std::int64_t sell_order_id,
        std::uint64_t price, std::int64_t quantity);

  std::int64_t get_buy_order_id() const;
  std::int64_t get_sell_order_id() const;
  std::uint64_t get_price() const;
  std::int64_t get_quantity() const;
};
