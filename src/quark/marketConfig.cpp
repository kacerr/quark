/*
 * markedConfig.cpp
 *
 *  Created on: Jun 3, 2017
 *      Author: ondra
 */

#include "marketConfig.h"

#include <imtjson/json.h>

#include <stdexcept>

namespace quark {

using namespace json;

static Value mandatory(json::Value v, StrViewA name) {
	Value x = v[name];
	if (x.defined()) return x;
	else throw std::runtime_error(String({"Config value: ", name, " is mandatory, but missing"}).c_str());
}

MarketConfig::MarketConfig(json::Value v)
:pipSize(mandatory(v,"pipSize").getNumber())
/// order size granuality
,granuality(mandatory(v,"granuality").getNumber())

///minimum price allowed as limit/stop price
,minPrice(mandatory(v,"minPrice").getNumber())
///maximum price allowed as limit/stop price
,maxPrice(mandatory(v,"maxPrice").getNumber())
///minimum order size
,minSize(mandatory(v,"minSize").getNumber())
///maximum order size
,maxSize(mandatory(v,"maxSize").getNumber())
///maximum total budget for the order (maxPrice * maxSize)
,maxBudget(mandatory(v,"maxBudget").getNumber())

///maximum allowed spread in per cents, if spread is larger, market orders are paused
,maxSpreadPct(mandatory(v,"maxSpreadPct").getNumber())
///maximum allowed spread in per cents, if spread is larger, market orders are paused
,maxSlippagePct(mandatory(v,"maxSlippagePct").getNumber())

,currencySign(mandatory(v,"currencySign"))
,assetSign(mandatory(v,"assetSign"))
,moneyService(mandatory(v,"moneyService"))
,updateUrl(String(v["updateUrl"]))
,updateLastModified(String(v["updateLastModified"]))
,updateETag(String(v["updateETag"]))
,rev(v["_rev"])
{

	double maxSize = pow(2,sizeof(std::size_t)*8);
	double reqSize = std::min(maxPrice * maxSize, maxBudget) / pipSize / granuality;
	if (reqSize >= maxSize) throw std::runtime_error("maxPrice * maxSize or maxBudget is out of range to map to the numbers");

}


std::size_t quark::MarketConfig::priceToPip(double price) const {
	return (std::size_t)floor(price / pipSize+0.5);
}

double quark::MarketConfig::pipToPrice(std::size_t pip) const {
	return pip * pipSize;
}

std::size_t quark::MarketConfig::amountToSize(double amount) const {
	return (std::size_t)floor(amount / granuality+0.5);
}

double quark::MarketConfig::sizeToAmount(std::size_t size) const {
	return size * granuality;
}

std::size_t MarketConfig::budgetToPip(double budget) const {
	return (std::size_t)floor(budget / pipSize / granuality+0.5);
}

double MarketConfig::pipToBudget(std::size_t pip) const {
	return pip * pipSize * granuality;
}

double quark::MarketConfig::adjustSize(double size) const {
	return floor(size/granuality+0.5)*granuality;
}

double quark::MarketConfig::adjustPrice(double price) const {
	return floor(price/pipSize+0.5)*pipSize;
}
double quark::MarketConfig::adjustTotal(double price) const {
	double comb = pipSize * granuality;
	return floor(price/comb+0.5)*comb;
}


} /* namespace quark */

