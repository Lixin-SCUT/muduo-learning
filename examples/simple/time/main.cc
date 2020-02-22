// main.cc
// Created by Lixin on 2020.02.22

#include "muduo/examples/simple/time/time.h"

#include "muduo/net/EventLoop.h"
#include "muduo/base/Logging.h"

#include <unistd.h> // for getpid()

using namespace muduo;
using namespace muduo::net;

int main()
{
	LOG_INFO << "pid = " << getpid();
	EventLoop loop_;
	InetAdder listenAddr2037();
	TimeServer server_(&loop,listenAddr);
	server_.start();
	loop_.loop();
}
