
#include <algorithm>

#include "order_book.hpp"

void OrderBook::fill_order(Order::Side incoming_side) {
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

    // The resting order determines the execution price.
    auto execution_price{incoming_side == Order::Side::buy
                             ? sell_order.get_price()
                             : buy_order.get_price()};

    // Record the completed execution.
    trade_log_.emplace_back(buy_order.get_id(), sell_order.get_id(),
                            execution_price, fill_quantity);

    // Update remaining quantities.
    buy_order.set_quantity(buy_order.get_quantity() - fill_quantity);
    sell_order.set_quantity(sell_order.get_quantity() - fill_quantity);

    // Remove fully filled orders.
    if (buy_order.get_quantity() == 0) {
      buy_level->second.pop_front();
    }

    if (sell_order.get_quantity() == 0) {
      sell_level->second.pop_front();
    }

    // Remove empty price levels.
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

  fill_order(order.get_side());
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

const std::vector<Trade> &OrderBook::get_trades() const { return trade_log_; }
