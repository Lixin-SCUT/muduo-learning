// discard.cc
// Created by Lixin on 2020.02.22

#include "muduo/examples/simple/discard/discard.h"

#include "muduo/base/Logging.h"

using namespace muduo;
using namespace muduo::net;

DisCardServer::DiscardServer(Eventoop* loop,
				const InetAddress& listendAddr)
	:server_(loop,listendAddr,"DiscardServer")
{
	setConnectionCallback(
			std::bind(&DiscardServer::onConnection,this,_1));
	setMessageCallback(
			std::bind(&DiscardServer::onMessage,this,_1,_2,_3));
}

void DiscardServer::start()
{
	server_.start();
}

void DiscardServer::onConnection(const TcpConnectionPtr& conn)
{
	LOG_INFO << "DiscardServer - " << conn->peerAddress.toIpPort() << " -> "
		<< conn->localAddress().toIpPort() << " is "
	       << (conn->connected() ? "UP" : "DOWN");	
}

void DiscardServer::onMessage(const TcpConnectionPtr& conn,
				Buffer* buf,
				Timestamp time)
{
	string msg(buf->retriveAllAsString());
	LOG_INFO << conn -> name() << " discards " << msg.size()
		<< " bytes received at " << time.toString();
}
