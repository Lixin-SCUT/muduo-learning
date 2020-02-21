// finger02.cc
// Created by Lixin on 2020 

#include "muduo/net/EventLoop.h"
#include "muduo/net/TcpServer.h"

using namespace muduo;
using namespace muduo::net;

int main()
{
	EventLoop loop;
	//InetAddress listenAddr(1079);
	//TcpServer server(&loop,listenAddr,"Finger");
	TcpServer server(&loop,InetAddress(1079),"Finger");
	server.start();
	loop.loop();
}
