#include "mockupmoneyserver.h"

#include "logfile.h"

namespace quark {

void MockupMoneyService::start() {
	if (workerThread == nullptr)
		workerThread = std::unique_ptr<std::thread>(new std::thread([=]{worker();}));
}

void MockupMoneyService::requestBudgetOnServer(json::Value user,
						OrderBudget total, Callback callback) {
	std::lock_guard<std::mutex> _(queueLock);
	if (workerThread == nullptr) {
		start();
	}
	queue.push(QueueItem(user,total,callback));
	runBackend.notify_all();
}

void MockupMoneyService::stop() {
	if (workerThread != nullptr) {
		finish = true;
		runBackend.notify_all();
		workerThread->join();
	}
}

void MockupMoneyService::worker() {
	while (!finish) {

		std::queue<QueueItem> cpyq;
		{
			std::unique_lock<std::mutex> _(queueLock);
			runBackend.wait(_, [&]{return !queue.empty()||finish;});
			logInfo({"Moneyserver processing batch", queue.size()});
			std::swap(cpyq, queue);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(serverLatency));

		while (!cpyq.empty()) {
			QueueItem itm = cpyq.front();
			cpyq.pop();

			bool res = allocBudget(itm.user,itm.budget);
			if (itm.callBack) itm.callBack(res);
		}
	}
}

bool MockupMoneyService::allocBudget(json::Value user, const OrderBudget& b) {
	switch (b.type) {
	case OrderBudget::currency: return b.value < maxCurrency;
	case OrderBudget::asset: return b.value < maxAssets;
	}
}

}
