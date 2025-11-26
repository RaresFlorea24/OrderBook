#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

enum class OrderType {
	GoodTillCancel,
	FillAndKill
};

enum class Side {
	Buy,
	Sell
};

using Price = std::int32_t;
using Quantity = std::uint32_t;
using OrderId = std::uint64_t;

struct LevelInfo {
	Price price_;
	Quantity quantity_;
};

using LevelInfos = std::vector<LevelInfo>;

class OrderBookLevelInfos {
public:
	OrderBookLevelInfos(const LevelInfos& bids, const LevelInfos& asks)
		: bids_{bids}
		, asks_{asks}
	{ }

	const LevelInfos& GetBids() const { return bids_; }
	const LevelInfos& GetAsks() const { return asks_; }

private:
	LevelInfos bids_;
	LevelInfos asks_;
};

class Order {
	public:
		Order(OrderType orderType,OrderId orderId,Side side,Price price, Quantity quantity)
			:orderType_{orderType}
			,orderId_{orderId}
			,side_{side}
			,price_{price}
			,initialQuantity_{quantity}
			,remainingQuantity_{quantity}
		{ }

		OrderId GetOrderId() const { return orderId_; }
		OrderType GetOrderType() const { return orderType_; }
		Side GetSide() const { return side_; }
		Price GetPrice() const { return price_; }
		Quantity GetInitialQuantity() const{ return initialQuantity_; }
		Quantity GetRemainingQuantity() const { return remainingQuantity_; }
		Quantity GetFilledQuantity() const { return initialQuantity_ - remainingQuantity_; }

		void Fill(Quantity quantity) {
			if (quantity > GetRemainingQuantity())
				//throw std::logic_error("Order ({}) cannot be filled more than its remaining quantity. ", GetOrderId());
				return;

			remainingQuantity_ -= quantity;
		}
private:
	OrderType orderType_;
	OrderId orderId_;
	Side side_; 
	Price price_;
	Quantity remainingQuantity_;
	Quantity initialQuantity_;

};

int main() {

}