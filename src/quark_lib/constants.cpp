#include "constants.h"

namespace quark {


#define ENUMDEF(x) { x, #x }
#define STRCONST(x) json::StrViewA x(#x)

namespace OrderDir {

json::NamedEnum<Type> str(
		{
	ENUMDEF(buy),
	ENUMDEF(sell)
		}
);

}

namespace OrderType {


json::NamedEnum<Type> str(
		{
		ENUMDEF(market),
		ENUMDEF(limit),
		ENUMDEF(maker),
		ENUMDEF(stop),
		ENUMDEF(stoplimit),
		ENUMDEF(fok),
		ENUMDEF(ioc),
		ENUMDEF(oco_limitstop)
		}
);
}

namespace OrderFields {

StrViewA orderId("_id");
StrViewA vendorId("id");
STRCONST(dir);
STRCONST(type);
STRCONST(size);
STRCONST(origSize);
STRCONST(limitPrice);
STRCONST(stopPrice);
STRCONST(trailingDistance);
STRCONST(domPriority);
STRCONST(queuePriority);
STRCONST(budget);
STRCONST(context);
STRCONST(user);
STRCONST(status);
STRCONST(error);
STRCONST(cancelReq);
STRCONST(finished);
STRCONST(fees);
STRCONST(updateReq);
STRCONST(updateStatus);
STRCONST(timeCreated);
STRCONST(timeModified);
STRCONST(queue);
STRCONST(nextOrder);
STRCONST(prevOrder);
STRCONST(data);
STRCONST(expireTime);
STRCONST(expireAction);
STRCONST(expired);
STRCONST(fs);
STRCONST(fp);

}

namespace NextOrderFields {

StrViewA orderId("id");
STRCONST(target);
STRCONST(stoploss);
STRCONST(size);
STRCONST(absolute);

}

namespace Status {

StrViewA strValidating("validating");
StrViewA strActive("active");
StrViewA strFinished("finished");
StrViewA strExecuted("executed");
StrViewA strRejected("rejected");
StrViewA strAccepted("accepted");
StrViewA strCanceled("canceled");


json::NamedEnum<Type> str({
	{validating, strValidating},
	{active, strActive},
	{finished, strFinished},
	{executed, strExecuted},
	{rejected, strRejected},
	{canceled, strCanceled},
	{accepted, strAccepted}}
);
}

namespace OrderContext {
json::NamedEnum<Type> str({
		ENUMDEF(exchange),
		ENUMDEF(margin)
	});
}

}


