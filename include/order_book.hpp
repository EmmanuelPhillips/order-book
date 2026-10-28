#pragma once

#include <cstdint>

#include <deque>
#include <functional>
#include <map>
#include <optional>

#include "order.hpp"

class OrderBook {
private:
  std::map<std::uint64_t, std::deque<Order>, std::greater<std::uint64_t>>
      buy_side_;
  std::map<std::uint64_t, std::deque<Order>, std::less<std::uint64_t>>
      sell_side_;

  void fill_order();

public:
  void add_order(const Order &order);

  std::optional<Order> get_best_ask() const;
  std::optional<std::uint64_t> get_best_ask_price() const;

  std::optional<Order> get_best_bid() const;
  std::optional<std::uint64_t> get_best_bid_price() const;
};
