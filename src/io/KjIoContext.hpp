#pragma once
//------------------------------------------------------------------------------
/**
	@class CKjIoContext

	(C) 2016 n.lee
*/
#include "../UsingCapnp.h"

class KjIoContext : public kj::Refcounted {
public:
	KjIoContext() : _ioContext(kj::setupAsyncIo()) {}
	~KjIoContext() = default;

	kj::WaitScope&				GetWaitScope() {
		return _ioContext.waitScope;
	}

	kj::Network&				GetNetwork() {
		return _ioContext.provider->getNetwork();
	}

	kj::Timer&					GetTimer() {
		return _ioContext.provider->getTimer();
	}

	kj::Promise<void>			AfterDelay(kj::Duration delay) {
		return GetTimer().afterDelay(delay);
	}

	template <typename T>
	kj::Promise<T>				TimeoutAfter(kj::Duration delay, kj::Promise<T>&& p) {
		return GetTimer().timeoutAfter(delay, kj::mv(p));
	}

	kj::AsyncIoProvider::PipeThread NewPipeThread(kj::Function<void(kj::AsyncIoProvider&, kj::AsyncIoStream&, kj::WaitScope&)>&& startFunc) {
		return _ioContext.provider->newPipeThread(kj::mv(startFunc));
	}

private:
	kj::AsyncIoContext _ioContext;
};

/*EOF*/