#include "base-interface.h"
#include "thread-pool.h"

#include <vector>
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>
#include <atomic>

class AsyncLogger : public ILogger
{
public:
	AsyncLogger(ILogger* logger, size_t numThreads);
	~AsyncLogger() override;

	void Log(std::string_view message) override;
	//void Flush();

private:
	ILogger* logger;

	// order is important
	std::mutex mutex;
	ThreadPool threadPool;
	//
	std::queue<std::string> logQueue;
	std::atomic<bool> stop;
};

void PerformanceTest(ILogger* logger, const std::string& loggerType);