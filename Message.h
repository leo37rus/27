#pragma once
#include <string>
#include <iostream>

class Message
{
public:
    Message(const std::string& sender, const std::string& receiver, const std::string& text)
        : _sender(sender), _receiver(receiver), _text(text) {}

    friend std::ostream& operator <<(std::ostream& os, const Message& message_obj)
    {
        os << message_obj._sender;
        os << '\t';
        os << message_obj._receiver;
        os << '\t';
        os << message_obj._text;
        return os;
    }

private:
    std::string _sender;
    std::string _receiver;
    std::string _text;
};
