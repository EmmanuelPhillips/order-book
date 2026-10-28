#include <cstdint>
#include <cwchar>

#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <optional>
#include <stdexcept>

class Order {
public:
  enum class Side { buy, sell };

private:
  std::int64_t id_; // Always positive
  Side side_;
  std::uint64_t price_;   // As a tick
  std::int64_t quantity_; // Quantity will always be whole positive integer
  std::uint64_t
      timestamp_ns_; // Storing timestamps using std::chrono eventually

public:
  Order(std::int64_t id, Side side, std::uint64_t price, std::int64_t quantity,
        std::uint64_t timestamp)
      : id_{id}, side_{side}, price_{price}, quantity_{quantity},
        timestamp_ns_{timestamp} {}

  std::int64_t get_id() const { return id_; }
  Side get_side() const { return side_; }
  std::uint64_t get_price() const { return price_; }
  std::int64_t get_quantity() const { return quantity_; }
  std::uint64_t get_timestamp() const { return timestamp_ns_; }

  void set_quantity(std::int64_t new_quantity) { quantity_ = new_quantity; }
};

class OrderBook {
private:
  std::map<std::uint64_t, std::deque<Order>, std::greater<std::uint64_t>>
      buy_side_;
  std::map<std::uint64_t, std::deque<Order>, std::less<std::uint64_t>>
      sell_side_;

  template <typename T>
  std::optional<Order> get_best_order(const T &side) const {
    if (side.empty()) {
      return std::nullopt;
    }
    return side.begin()->second.front();
  }

  template <typename T>
  std::optional<std::uint64_t> get_best_price(const T &side) const {
    if (side.empty()) {
      return std::nullopt;
    }
    return side.begin()->first;
  }

  void fill_order() {
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

public:
  void add_order(const Order &order) {
    if (order.get_side() == Order::Side::buy) {
      buy_side_[order.get_price()].push_back(order);
    } else {
      sell_side_[order.get_price()].push_back(order);
    }
    fill_order();
  }

  std::optional<Order> get_best_ask() const {
    return get_best_order(sell_side_);
  }

  std::optional<std::uint64_t> get_best_ask_price() const {
    return get_best_price(sell_side_);
  }

  std::optional<Order> get_best_bid() const {
    return get_best_order(buy_side_);
  }

  std::optional<std::uint64_t> get_best_bid_price() const {
    return get_best_price(buy_side_);
  }
};

int main() { return 0; }
