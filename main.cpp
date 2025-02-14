#include "wrapper.h"

int main()
{
    std::cout << "okok" << std::endl;


    return 0;
}

/*
int main()
{
	ILogger* logger = CreateLogger();
	PerformanceTest(logger, "DefaultLogger");
	DestroyLogger(logger);

	logger = CreateLogger();
	AsyncLogger asyncLogger(logger);
	PerformanceTest(&asyncLogger, "AsyncLogger");

	return 0;
}
*/