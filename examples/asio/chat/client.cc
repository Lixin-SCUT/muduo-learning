// client.cc
// Created by Lixin on 2020.02.26

#include "examples/asio/chat/codec.h"

#include "muduo/base/Logging.h"
#include "muduo/base/Mutex.h"
#include "muduo/net/EventLoopThread.h"
#include "muduo/net/TcpClient.h"

#include <iostream>
#include <stdio.h>
#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

class ChatClient : noncopyable
{
public:
	ChatClient(EventLoop* loop, const InetAddress& serverAddr)
		: client(loop, serverAddr,"ChatClient"),
		  codec_(std::bind(&onStringMessage,this,_1,_2,_3))
	{
		client_.setConnectionCallback(
				std::bind(&onConnection,this,_1));
		client_.setMessageCallback(
				std::bind(&LengthHeaderCodec::onMessgage,&codec_,_1,_2,_3));
		client_.enableRetry();
	}

	void connect()
	{
		client_.connect();
	}

	void disconnect()
	{
		client_.disconnect();
	}

	void write(const StringPiece& message)
	{
		MutexLockGuard lock(mutex_);
		if(connection_)
		{
			codec_.send(connection_.get(),message);
		}
	}

private:
	void onConnection(const TcpConnectionPtr& conn)
	{
		LOG_INFO << conn->localAddress().toIpPort() << " -> "
             		<< conn->peerAddress().toIpPort() << " is "
             		<< (conn->connected() ? "UP" : "DOWN");
		
		MutexLockGuard lock(mutex_);
		if(conn->connected())
		{
			connection_ = conn;
		}
		else
		{
			connection_.reset();
		}
	}

	void onStringMessage(const TcpConnectionPtr&,
				const string& message,
				Timestamp)
	{
		pring("<<< %s\n",message.c_str());
	}

private:
	TcpClient clent_;
	LengthHeaderCodec codec_;
	MutexLock mutex_;
	TcpConnectionPtr connection_ GUARDED_BY(mutex_);
};

int main(int argc, char* argv[])
{
	LOG_INFO << "pid = " << getpid();
	if(argc >2)
	{
		EventLoopThread loopThread;
		unit16_t port = static_cast<unit16_t>(atoi(argv[2]));
		InetAddress serverAddr(argv[1],port);

		ChatClient client(&loopThread.startLoop(),serverAddr);
		client.connect();
		std::string line;
		while(std::getline(std::cin,line))
		{
			client.write(line);
		}
		client.disconnect();
		CurrentThread::sleepUsec(1000*1000); // wait for disconnect
	}
	else 
	{
		printf("Usage: %s host_ip,port\n",argv[0]);
	}
}
