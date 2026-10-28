#include "order.hpp"

Order::Order(std::int64_t id, Order::Side side, std::uint64_t price,
             std::int64_t quantity, std::uint64_t timestamp)
    : id_{id}, side_{side}, price_{price}, quantity_{quantity},
      timestamp_ns_{timestamp} {}

std::int64_t Order::get_id() const { return id_; }

Order::Side Order::get_side() const { return side_; }

std::uint64_t Order::get_price() const { return price_; }

std::int64_t Order::get_quantity() const { return quantity_; }

std::uint64_t Order::get_timestamp() const { return timestamp_ns_; }

void Order::set_quantity(std::int64_t new_quantity) {
  quantity_ = new_quantity;
}
