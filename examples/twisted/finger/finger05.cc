// finger05.cc
// Created by Lixin on 2020.02.19

#include "muduo/net/EventLoop.h"
#include "muduo/net/TcpServer.h"

using namespace muduo;
using namespace muduo::net;

void onMessage(TcpConnectionPtr&,
		Buffer*,
		Timestamp);

int main()
{
	EventLoop loop;
	TcpServer server(&loop,InetAddress(1079),"Finger");
	server.setMessageCallback(onMessage);
	server.start();
	loop.loop();
}

void onMessage(TcpConnectionPtr& conn,
		Buffer* buf,
		Timestamp receiveTime)
{
	if(buf->findCRLF())
	{
		//conn->send();
		conn->send("No such user\r\n");
		conn->shutdown();
	}
}


