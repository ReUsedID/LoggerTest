#include "base-interface.h"

ILogger * CreateLogger()
{
	return new FileLogger("out.txt");
}

void DestroyLogger(ILogger * logger)
{
	delete logger;
}


void bar(ILogger* logger)
{
	for (int i = 0; i < 100; ++i)
	{
		logger->Log("bar: Processing " + std::to_string(i));
	}
}

void foo(ILogger* logger)
{
	logger->Log("foo: Enter");
	bar(logger);
	logger->Log("foo: Exit");
}