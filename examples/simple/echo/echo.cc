// echo.cc
// Created by Lixin on 2020.02.18

#include "echo.h"

#include "muduo/base/Logging.h"

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

//using namespace muduo;
//using namespace muduo::net;

EchoServer::EchoServer(muduo::net::EventLoop* loop,
		const muduo::net::InetAddress& listenAddr)
	: server_(loop,listenAddr,"EchoServer")
{
	server_setConnectionCallback(
			(&EchoServer::onConnection,this,_1));
	server_setMessageCallback(
			(&EchoServer::onMessage,_1,_2,_3));
}

void EchoServer::start()
{
	server_.start();
}

void EchoServer::onConnection(const muduo::net::TcpConnectionPtr& conn)
{
	LOG_INFO << "EchoServer - " << conn->peerAdderss().toIpPort() << " -> "
		<< conn->localAdderss().toIpPort() << " is "
		<< (conn->connected() ? "UP " : " DOWN");
}

void EchoServer::onMessage(const muduo::net::TcpConnectionPtr& conn,
			   muduo::net::Buffer* buf,
			   muduo::Timestamp time)
{
	muduo::string msg(buf->retriveAllAsString());
	LOG_INFO << conn->name() << " echo " << msg.size() << " bytes, "
		<< "data received at " << timer.toString();
	conn->send(msg);
}

