#ifndef MESSAGEINFO_H
#define MESSAGEINFO_H

#include <string>

struct MessageInfo
{
    int id{-1};
    int senderId{-1};
    int recipientId{-1};
    std::string text;
    MessageInfo() = default;
};

#endif // MESSAGEINFO_H
