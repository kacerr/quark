#pragma once
#include <couchit/couchDB.h>
#include <couchit/document.h>
#include <memory>


#include "imoneysrvclient.h"

namespace quark {

typedef std::shared_ptr<couchit::CouchDB> PCouchDB;

///extract information from trade to TradeData need by MoneyServer
void extractTrade(const couchit::Value &tradeDoc, IMoneySrvClient::TradeData &tdata);
///extract BalanceChange from the trade and the orders need by MoneyServer
void extractBalanceChange(const couchit::Value& order, const couchit::Value &tradeDoc, IMoneySrvClient::BalanceChange &tdata, OrderDir::Type dir,const MarketConfig &mcfg);
///perform resync of money server from fromTrade (excluded) to toTrade (included)
void resync(couchit::CouchDB &orderDB, couchit::CouchDB &tradeDB, PMoneySrvClient target, const Value fromTrade, const Value toTrade,const MarketConfig &mcfg);
///Fetch last trade by its internal counter. This is called on beginning of mainloop to sync with the database
Value fetchLastTrade(couchit::CouchDB &tradeDB);


typedef std::function<void()> Action;
typedef std::function<void(Action)> Dispatcher;


class MoneySvcSupport: public IMoneySvcSupport {
public:
	MoneySvcSupport(PCouchDB orderDB, PCouchDB tradeDB,PMarketConfig mcfg, Dispatcher dispatcher);

	virtual void resync(PMoneySrvClient target, const Value fromTrade, const Value toTrade);
	virtual void dispatch(Action fn);
protected:
	PCouchDB orderDB;
	PCouchDB tradeDB;
	PMarketConfig mcfg;
	Dispatcher dispatcher;
};





}
