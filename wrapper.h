#include "base-interface.h"

#include <vector>
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>
#include <atomic>

class AsyncLogger : public ILogger
{
public:
	AsyncLogger(ILogger* logger);
	~AsyncLogger() override;

	void Log(std::string_view message) override;

private:
	void ProcessLogs();

	ILogger* logger_;
	std::queue<std::string_view> logQueue_;
	std::mutex mutex_;
	std::condition_variable condition_;
	std::thread workerThread_;
	std::atomic<bool> stop_;
};

