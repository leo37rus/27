#pragma once

#include <string>
#include <fstream>
#include <shared_mutex>
#include <mutex>

#include "Message.h"

class Logger
{
public:
	Logger(const std::string& filename);
	~Logger();
	void writeLog(const Message& msg);
	std::string readLog(int rowCount);

	void writer(int id, const Message& msg);
	void reader(int rowCount);

private:
	std::fstream _logfile;
	std::string _filename;
	std::shared_mutex _shared_mutex;
	std::mutex mtx;
};


