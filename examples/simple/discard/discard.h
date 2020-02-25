// discard.h
// Created by Lixin on 2020.02.22

#ifndef MUDUO_EXAMPLES_SIMPLE_DISCARD_DISCARD_H
#define MUDUO_EXAMPLES_SIMPLE_DISCARD_DISCARD_H

#include "muduo/net/TcpServer.h"

class DiscardServer
{
public:
	DiscardServer(muduo::net::EventLoop *loop,
			const muduo::net::InetAddress& listenAddr);

	void start();
priveta:
	void onConnection(const muduo::net::TcpConnectionPtr& conn);
	
	void onMessage(const muduo::net::TcpConnectionPtr& conn,
			muduo::net::Buffer* buf,
			muduo::Timestamp time);

	TcpServer server_;
};

#endif // MUDUO_EXAMPLES_SIMPLE_DISCARD_DISCARD_H
