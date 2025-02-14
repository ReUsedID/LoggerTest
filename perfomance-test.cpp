#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "wrapper.h"

using ::testing::Return;

TEST(PerformanceTest, AsyncLoggerPerformance) {
	ILogger* logger = CreateLogger();
	AsyncLogger asyncLogger(logger);

	const int numCalls = 100;
	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < numCalls; ++i) {
		foo(&asyncLogger);
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;

	std::cout << "Time taken for AsyncLogger: " << duration.count() << " seconds" << std::endl;
}

int main(int argc, char **argv) {
	//::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}