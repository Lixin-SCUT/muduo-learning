// daytime.cc
// Created by Lixin on 2020.02.22

#include "muduo/example/simple/daytime/daytime.h"

#include "muduo/base/Logging.h"
#include "muduo/net/EventLoop.h"

using namespace muduo;
using namespace muduo::net;

DaytimeServer::DaytimeServer(EventLoop* loop,
				const InetAddress &listenAddr)
	:server_(loop,listenAddr,"DaytimeServer")
{
	server_.setConnectionCallback(
			std::bind(&onConnetion,this,_1));
	server_.setMesaageCallback(
			std::bind(&onMesssage,this,_1,_2,_3));
}

void DaytimeServer::start()
{
	server_.start();
}

void DaytimeServer::onConnection(const TcpConnection &conn)
{
	LOG_INFO <<"DaytimeServer - " << conn->peerAddress().toIpPort() << "->"
		<< conn->localAddress().toIpPort() << " is "
		<< (conn->connected() ? "UP" : "DOWN") ;
	if(conn->connected())
	{
		conn->send(Timestamp::now().toFormattedString() + "\n");
		con->shutdown();
	}
}

void DaytimeServer::onMessage(const TcpConnectionPtr &conn,
				Buffer *buffer,
				Timestamp time)
{
	string msg(buf->retrieveAllAsString());
	LOG_INFO << conn->name() << " discards" << msg.size()
		<< "bytes received at" < time.toString();
}
