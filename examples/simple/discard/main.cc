// main.cc
// Created by Lixin on 2020.02.22

#include "muduo/examples/simple/discard/discard.h"

#include "muduo/net/EventLoop.h"
#include "muduo/base/Logging.h"

#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

int main()
{
	LOG_INFO << "pid = " << getpid();
	EventLoop loop;
	InetAddress listenAddr(2009);
	DiscardServer server(&loop,listenAddr);
	server.start();
	loop.loop();
}
