#pragma once
#include "all.h"
#include "xChannel.h"
#include "xEventLoop.h"
#include "xSocket.h"

class xAcceptor : boost::noncopyable
{
public:

	 typedef std::function<void (int sockfd)> NewConnectionCallback;

	 xAcceptor(xEventLoop* loop,std::string ip,int32_t port);
	 ~xAcceptor();


	void setNewConnectionCallback(const NewConnectionCallback& cb){ newConnectionCallback = cb; }

	bool getlistenning() const { return listenning; }
	void listen();

private:
	void handleRead();

private:
	xEventLoop *loop;
	xSocket    socket;
	xChannel   channel;
	int        listenfd;

	NewConnectionCallback newConnectionCallback;
	bool listenning;
	bool protocol;
	void *data;

};
