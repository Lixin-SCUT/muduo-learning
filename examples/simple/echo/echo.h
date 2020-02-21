// echo.h
// Created by Lixin on 2020.02.18

#ifdef MUDUO_EXAMPLES_SIMPLE_ECHO_H
#define MUDUO_EXAMPLES_SIMPLE_ECHO_H

#include "muduo/net/TcpServer.h"

class EchoServer
{
public:
	EchoServer(muduo::net::EventLoop* loop,
			const muduo::net::InetAddress& listenAddr);

	void start(); // calls server_.start();

private:
	void onConnection(const muduo::net::TcpConnectionPtr& conn);

	void onMessage(const muduo::net::TcpConnectionPtr& conn,
			muduo::net::Buffer* buf,
			muduo::Timestamp time);

	// muduo::net::EventLoop* loop_;
	muduo::net::TcpServer server_;
};

#endif // MUDUO_EXMAPLES_SIMPLE_ECHO_H
