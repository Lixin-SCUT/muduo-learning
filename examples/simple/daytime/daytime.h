// daytime.h
// Created by Lixin on 2020.02.22

#ifndef MUDUO_EXAMPLES_SIMPLE_DAYTIME_DAYTIME_H
#define MUDUO_EXAMPLES_SIMPLE_DAYTIME_DAYTIME_H

#include "muduo/net/TcpServer.h"

class DaytimeServer
{
public:
	DaytimeServer(muduo::net::EventLoop *loop,
			const muduo::net::InetAddress& listenAddr);
	
	void start();

private:
	void onConnection(const muduo::net::TcpConnectionPtr &conn);
	
	void onMessage(const muduo::net::TcpConnectionPtr &conn,
			muduo::net::Buffer *buf,
			muduo::Timestamp time);

private:
	muduo::net::TcpServer server_;
};

#endif // MUDUO_EXAMPLES_SIMPLE_DAYTIME_DAYTIME_H
