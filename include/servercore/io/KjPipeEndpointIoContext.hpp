#pragma once
//------------------------------------------------------------------------------
/**
	@class KjPipeEndpointIoContext

	(C) 2016 n.lee
*/
#include "../UsingCapnp.h"

class KjPipeEndpointIoContext : public kj::Refcounted {
public:
	KjPipeEndpointIoContext(kj::AsyncIoProvider& provider, kj::AsyncIoStream& stream, kj::WaitScope& waitScope);
	~KjPipeEndpointIoContext() = default;

	kj::AsyncIoStream&			GetEndpoint() {
		return _refStream;
	}

	kj::WaitScope&				GetWaitScope() {
		return _refWaitScope;
	}

	kj::Network&				GetNetwork() {
		return _refProvider.getNetwork();
	}

	kj::Timer&					GetTimer() {
		return _refProvider.getTimer();
	}

	kj::Promise<void>			AfterDelay(kj::Duration delay) {
		return GetTimer().afterDelay(delay);
	}

	template <typename T>
	kj::Promise<T>				TimeoutAfter(kj::Duration delay, kj::Promise<T>&& p) {
		return GetTimer().timeoutAfter(delay, kj::mv(p));
	}

private:
	kj::AsyncIoProvider& _refProvider;
	kj::AsyncIoStream&   _refStream;
	kj::WaitScope&       _refWaitScope;

};

/*EOF*/