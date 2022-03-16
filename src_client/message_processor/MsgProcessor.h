#ifndef MSGPROCESSOR_H
#define MSGPROCESSOR_H

#include "IMsgProcessor.h"
#include <memory>

class ClientThread;

class MsgProcessor : public IMsgProcessor
{
//    Q_OBJECT
    std::unique_ptr<ClientThread> _clientThread;
public:
    MsgProcessor();
    ~MsgProcessor();

    void start() override;
    void sendMsg(const QString &msg) override;

    void signUp_request(const QString &login, const QString &password) override;

private slots:
    void slot_getMsg(const QString &msg);
};

#endif // MSGPROCESSOR_H
