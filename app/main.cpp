#include <cstdint>

#include <deque>
#include <iostream>
#include <map>

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
  double get_price() const { return price_; }
  std::int32_t get_quanity() const { return quantity_; }
  std::uint64_t get_timestamp() const { return timestamp_ns_; }
};

class OrderBook {
private:
  std::map<std::int64_t, std::deque<Order>, std::greater<std::uint64_t>>
      buy_side_;
  std::map<std::int64_t, std::deque<Order>, std::less<std::uint64_t>>
      sell_side_;

public:
  void add_order(const Order &order) {
    if (order.get_side() == Order::Side::buy) {
      buy_side_[order.get_price()].push_back(order);
    } else {
      sell_side_[order.get_price()].push_back(order);
    }
  }
};

int main() { return 0; }
