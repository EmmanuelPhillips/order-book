#include <iostream>

#include "order.hpp"
#include "order_book.hpp"

int main() {
  OrderBook book;

  // Add a resting sell order.
  Order sell{1, Order::Side::sell, 100, 5, 1};
  book.add_order(sell);

  // Add a crossing buy order.
  Order buy{2, Order::Side::buy, 105, 3, 2};
  book.add_order(buy);

  // Print completed trades.
  for (const auto &trade : book.get_trades()) {
    std::cout << "Trade executed:\n";
    std::cout << "Buy order: " << trade.get_buy_order_id() << '\n';
    std::cout << "Sell order: " << trade.get_sell_order_id() << '\n';
    std::cout << "Price: " << trade.get_price() << '\n';
    std::cout << "Quantity: " << trade.get_quantity() << '\n';
  }

  // Check remaining ask.
  auto best_ask = book.get_best_ask();

  if (best_ask) {
    std::cout << "\nRemaining ask quantity: " << best_ask->get_quantity()
              << '\n';
  }

  return 0;
}
