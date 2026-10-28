#pragma once

#include <cstdint>

class Order {
public:
  enum class Side { buy, sell };

private:
  std::int64_t id_;
  Side side_;
  std::uint64_t price_;
  std::int64_t quantity_;
  std::uint64_t timestamp_ns_;

public:
  Order(std::int64_t id, Side side, std::uint64_t price, std::int64_t quantity,
        std::uint64_t timestamp);

  std::int64_t get_id() const;
  Side get_side() const;
  std::uint64_t get_price() const;
  std::int64_t get_quantity() const;
  std::uint64_t get_timestamp() const;

  void set_quantity(std::int64_t new_quantity);
};
