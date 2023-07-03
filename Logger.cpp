#include <sstream>
#include <thread>
#include <chrono>

#include "Logger.h"


Logger::Logger(const std::string& filename) : _filename(filename)
{
	_logfile.open(filename, std::ios::out | std::ios::in | std::ios::trunc);
	if (!_logfile.is_open())
		std::cout << "Could not open file Log.txt\n";
}

Logger::~Logger()
{
	_logfile.close();
}

void Logger::writeLog(const Message& msg)
{
	_shared_mutex.lock();
	_logfile.seekp(0, std::ios::end);
	_logfile << msg << "\n";
	_shared_mutex.unlock();
}

std::string Logger::readLog(int rowCount)
{
	std::lock_guard<std::shared_mutex> lock(_shared_mutex);
	_logfile.seekg(0, std::ios::beg);
	std::string row;
	int count = 1;
	while (!_logfile.eof())
	{
		getline(_logfile, row);
		if (count == rowCount)
		{
			return row;
		}
		count++;
	}
	return "";
}

void Logger::writer(int id, const Message& msg) {
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	writeLog(msg);
	std::lock_guard<std::mutex> lock(mtx);
	std::cout << "Thread ID " << id << "\tWrite Log: " << msg << "\n";
}

void Logger::reader(int rowCount) {
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::string row = readLog(rowCount);
	std::lock_guard<std::mutex> lock(mtx);
	if (!row.empty()) {
		std::istringstream input{ row };
		std::string sender, receiver, text;
		getline(input, sender, '\t');
		getline(input, receiver, '\t');
		getline(input, text);
		std::cout << "Read Log: Row " << rowCount << "\tSender: " << sender << "\tReceiver : " << receiver << "\tText : " << text << "\n";
	}
	else
		std::cout << "Row " << rowCount << " not found\n";
}