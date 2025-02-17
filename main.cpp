#include "wrapper.h"
#include <iostream>
#include <thread>
#include <chrono>



int main()
{
	ILogger* logger = CreateLogger();
	PerformanceTest(logger, "DefaultLogger");
	DestroyLogger(logger);
	
	logger = CreateLogger();
	AsyncLogger asyncLogger(logger, 4);
	PerformanceTest(&asyncLogger, "AsyncLogger");

	return 0;
}

