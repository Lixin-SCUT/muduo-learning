// finger03.cc
// Created by Lixin on 2020.02.19

#include "muduo/net/EventLoop.h"
#include "muduo/net/TcpServer.h"

using namespace muduo;
using namespace muduo::net;

void onConnection()
int main()
{
	EventLoop loop;
	TcpServer server(&loop,InetAddress(1079),"finger");
	server.setonConnection(&bind(onConnection,_1));
	server.start();
	loop.loop();
}
