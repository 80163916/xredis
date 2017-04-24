#pragma once

#include "all.h"
#include "xEventLoop.h"
#include "xCallback.h"


class xTcpClient
{
public:
	xTcpClient();
	xTcpClient(xEventLoop *loop,std::string ip,int port,void *data);
	~xTcpClient();


	void connect();
	void disconnect();
	void stop();

	void setConnectionErrorCallBack(ConnectionErrorCallback &&cb) { connectionErrorCallBack = std::move(cb);}
	void setConnectionCallback(ConnectionCallback&& cb) { connectionCallback = std::move(cb); }
	void setMessageCallback(MessageCallback&&  cb){ messageCallback = std::move(cb); }
	void setWriteCompleteCallback(WriteCompleteCallback&& cb) { writeCompleteCallback = std::move(cb); }


private:

	void errorConnection();
	void newConnection(int sockfd);
	void removeConnection(const xTcpconnectionPtr& conn);

	xConnectorPtr connector;
	xEventLoop *loop;
	std::string ip;
	int port;

	bool isconnect;
	int nextConnId;
	mutable std::mutex mutex;
	ConnectionErrorCallback connectionErrorCallBack;
	ConnectionCallback connectionCallback;
	MessageCallback messageCallback;
	WriteCompleteCallback writeCompleteCallback;


	xTcpconnectionPtr connection;
	void *data;


};
