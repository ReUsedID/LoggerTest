#include "wrapper.h"

AsyncLogger::AsyncLogger(ILogger* logger) : logger_(logger), stop_(false)
{
	workerThread_ = std::thread(&AsyncLogger::ProcessLogs, this);
}

AsyncLogger::~AsyncLogger()
{
	{
		std::lock_guard<std::mutex> lock(mutex_);
		stop_ = true;
	}
	condition_.notify_all();
	workerThread_.join();

	delete logger_;
}

void AsyncLogger::Log(std::string_view message)
{
	{
		std::lock_guard<std::mutex> lock(mutex_);
		logQueue_.push(message);
	}
	condition_.notify_one();
}

void AsyncLogger::ProcessLogs()
{
	while (true)
	{
		std::string_view message;
		{
			std::unique_lock<std::mutex> lock(mutex_);
			condition_.wait(lock, [this] { return !logQueue_.empty() || stop_; });

			if (stop_ && logQueue_.empty())
				return;

			if (!logQueue_.empty())
			{
				message = logQueue_.front();
				logQueue_.pop();
			}
		}
		if (!message.empty())
		{
			logger_->Log(message);
		}
	}
}

void PerformanceTest(ILogger* logger, const std::string& loggerType)
{
	const int numCalls = 10000;
	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < numCalls; ++i)
	{
		foo(logger);
		//logger->Log("Log message " + std::to_string(i));
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;

	std::cout << "Time taken for " << loggerType << ": " << duration.count() << " seconds" << std::endl;
}
