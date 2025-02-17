#include "wrapper.h"
#include <iostream>

AsyncLogger::AsyncLogger(ILogger* logger, size_t numThreads)
	: logger(logger), threadPool(numThreads), stop(false)
{

}

AsyncLogger::~AsyncLogger()
{
	//stop = true;
	//Flush();
	//
	//
}

void AsyncLogger::Log(std::string_view message) 
{
	{
		std::lock_guard<std::mutex> lock(mutex);
		logQueue.emplace(message);
	}
	
	threadPool.enqueue([this]
	{
		std::string message;
		{
			std::lock_guard<std::mutex> lock(mutex);
			if (!logQueue.empty()) {
				message = std::move(logQueue.front());
				logQueue.pop();
			}
		}
		if (!message.empty()) {
			try {
				logger->Log(message);
			} catch (const std::exception& e) {
				std::cerr << "Logging error: " << e.what() << std::endl;
			}
		}
	});
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

// again, remove this shit
/*
void AsyncLogger::Flush() 
{
	std::lock_guard<std::mutex> lock(mutex);
	while (!logQueue.empty())
	{
		std::string message = std::move(logQueue.front());
		logQueue.pop();
		logger->Log(message);
	}
}
*/