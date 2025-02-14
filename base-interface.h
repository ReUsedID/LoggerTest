#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <memory>

#include <fstream>
#include <string_view>

struct ILogger
{
	virtual ~ILogger() = default;
	virtual void Log(std::string_view message) = 0;
};

ILogger * CreateLogger();
void DestroyLogger(ILogger * logger);
void foo(ILogger* logger);
void bar(ILogger* logger);

class FileLogger : public ILogger 
{
public:

	FileLogger(const std::string & filename) 
	{
		file.open(filename, std::ios::app);
	}
	virtual ~FileLogger() override
	{
		if(file.is_open())
		{
			file.close();
		}
	}

	void Log(std::string_view message) override
	{
		if(file.is_open())
		{
			file << message << std::endl;
		}
	}

private:
	std::ofstream file;
};
