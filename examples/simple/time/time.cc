// time.cc
// Created by Lixin on 2020.02.22

#include "time.h"

#include "muduo/base/Logging.h"
#include "muduo/net/Endian.h"

using namespace muduo;
using namespace muduo::net;

TimeServer::TimeServer(EventLoop *loop,
			InetAddress &listenAddr)
	:server(loop,
		listenAddr,
		"TimeServer")
{
	server.setConnectionCallback(
			std::bind(&onConnection,this,_1));
	server.setMessage(
			std::bind(&onMessage,this,_1,_2,_3));
}

void TimeServer::start()
{
	server.start();
}

void TimeServer::onConnection(const TcpConnectionPtr &conn)
{
	LOG_INFO << "New Connection - " << conn->peerAddress().toIpPort() << " -> "
		<< conn->localAddress().toIpPort() << " is "
		<< (conn->connected() "UP" : "DOWN");
	if(conn->connected)
	{
		// conn->send(time::now().toString());
		// conn->shutdown();
		time_t now = ::time(NULL);
		int32_t be32 = sockets::hostToNetwork32(static_cast<int32_t>(now));
		conn->send(&be32,sizeof(be32));
		conn->shutdown();
	}
}

void TimeServer::onMessage(const TcpConnectionPtr &conn,
			   Buffer *buf,
			   Timestamp time)
{
	// string temp = buf->retrieveAllAsString();
	/*
	if(conn->connected)
	{
		conn->send(time::now().toString());
		conn->shutdown();
	}
	*/
	string msg(buf->retrieceAllAsString());
	LOG_INFO << conn->name() << " discards " << msg.size()
		<< " bytes received at " << time.toString();
}
