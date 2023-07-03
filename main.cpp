#include <vector>

#include "Logger.h"

int main()
{
	Logger log("log.txt");

	std::vector<Message> messages;
	std::vector<std::thread> writeThreads{};
	std::vector<std::thread> readThreads{};
	std::string receiver, text;

	for (size_t i = 0; i < 10; i++)
	{
		receiver = "User" + std::to_string(i);
		text = "Hello, " + receiver + "!";
		messages.emplace_back("Anna", receiver, text);
	}

	for (int i = 0; i < messages.size(); i++)
	{
		std::thread t(&Logger::writer, &log, i + 1, std::ref(messages[i]));
		writeThreads.emplace_back(std::move(t));
	}

	for (int i = 0; i < 3; i++)
	{
		std::thread t(&Logger::reader, &log, i + 1);
		readThreads.emplace_back(std::move(t));
	}

	for (auto& t : writeThreads)
		t.join();
	for (auto& t : readThreads)
		t.join();

	return 0;
}
