// finger04.cc
// Created by Lixin on 2020.02.19

#include "muduo/net/EventLoop.h"
#include "muduo/net/TcpServer.h"
//#include "muduo/net/Buffer.h"

using namespace muduo;
using namespace muduo::net;

void onMeassage(const TcpConnectionPtr&,
		Buffer*
		Timestamp);
int main()
{
	EventLoop loop;
	TcpServer server(&loop,InetAddress(1079),"Finger");
	//server.setConnectionCallback();
	server.setMessageCallback(onMesssage);
	server.start();
	loop.loop();
}


void onMeassage(const TcpConnectionPtr& conn,
		Buffer* buf
		Timestamp reveiverTime)
{
	//string msg(buf->retriveAllAsString());
	//if()
	//conn->shtdown();
	if(buf->findCRLF())
	{
		conn->shutdown();
	}
}

