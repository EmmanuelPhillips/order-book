
#include <algorithm>

#include "order_book.hpp"

void OrderBook::fill_order() {
  while (!buy_side_.empty() && !sell_side_.empty()) {
    auto buy_level = buy_side_.begin();
    auto sell_level = sell_side_.begin();

    if (sell_level->first > buy_level->first) {
      break;
    }

    auto &buy_order{buy_level->second.front()};
    auto &sell_order{sell_level->second.front()};

    auto fill_quantity{
        std::min(buy_order.get_quantity(), sell_order.get_quantity())};

    buy_order.set_quantity(buy_order.get_quantity() - fill_quantity);
    sell_order.set_quantity(sell_order.get_quantity() - fill_quantity);

    if (buy_order.get_quantity() == 0) {
      buy_level->second.pop_front();
    }

    if (sell_order.get_quantity() == 0) {
      sell_level->second.pop_front();
    }

    if (buy_level->second.empty()) {
      buy_side_.erase(buy_level);
    }

    if (sell_level->second.empty()) {
      sell_side_.erase(sell_level);
    }
  }
}

void OrderBook::add_order(const Order &order) {
  if (order.get_side() == Order::Side::buy) {
    buy_side_[order.get_price()].push_back(order);
  } else {
    sell_side_[order.get_price()].push_back(order);
  }

  fill_order();
}

std::optional<Order> OrderBook::get_best_ask() const {
  if (sell_side_.empty()) {
    return std::nullopt;
  }

  return sell_side_.begin()->second.front();
}

std::optional<std::uint64_t> OrderBook::get_best_ask_price() const {
  if (sell_side_.empty()) {
    return std::nullopt;
  }

  return sell_side_.begin()->first;
}

std::optional<Order> OrderBook::get_best_bid() const {
  if (buy_side_.empty()) {
    return std::nullopt;
  }

  return buy_side_.begin()->second.front();
}

std::optional<std::uint64_t> OrderBook::get_best_bid_price() const {
  if (buy_side_.empty()) {
    return std::nullopt;
  }

  return buy_side_.begin()->first;
}
