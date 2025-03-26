#include "wrapper.h"


int main()
{
	ILogger * logger = CreateLogger();
	PerformanceTest(logger, "default");
	logger -> Log("\n\n End of default logger \n\n");

	logger = CreateLogger();
	AsyncLogger async_logger = AsyncLogger(logger);
	PerformanceTest(&async_logger, "async");

	async_logger.Log("\n\n End of async logger \n\n");

	return 0;
}
