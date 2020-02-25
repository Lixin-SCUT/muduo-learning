// main.cc
// Created by Lixin on 2020.02.22

#inlcude "muduo/examples/simple/daytime/daytime.h"

#include "muduo/net/EventLoop.h"
#include "muduo/base/Logging.h"

using namespace muduo;
using namespace muduo::net;

int main()
{
	LOG_INFO << "pid = " << getpid();
	EventLoop loop;
	InetAddress listenAddr(2013);
        //DaytimeServer(loop,InetAddress());
	//loop.loop();
	//DaytimeServer.start();
	DaytimeServer server_(&loop,listenAddr);
	server_.start();
	loop.loop();
}
