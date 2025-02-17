#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <condition_variable>
#include <atomic>

class ThreadPool 
{
public:
	ThreadPool(size_t numThreads);
	~ThreadPool();

	void enqueue(std::function<void()> f);

private:
	std::vector<std::thread> workers;
	std::queue<std::function<void()>> tasks;

	std::mutex queueMutex;
	std::condition_variable condition;
	std::atomic<bool> stop;
};