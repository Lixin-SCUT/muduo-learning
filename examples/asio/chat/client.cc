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
				std::bind(&LengthHeaderCodec::onMessgage,&code_,_1,_2,_3));
		client_.enableRetry();
	}
private:
	TcpClient clent_;
	LengthHeaderCodec codec_;
	MutexLock mutex_;
	TcpConnectionPtr connection_ GUARDED_BY(mutex_);
};
