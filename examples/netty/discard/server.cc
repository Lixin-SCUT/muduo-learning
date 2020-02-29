// server.cc
// Created by Lixin on 2020.02.29

#include "muduo/net/TcpServer.h"

#include "muduo/base/Atomic.h"
#include "muduo/base/Logging.h"
#include "muduo/base/Thread.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/InetAddress.h"

#include <utility>

#include <stdio.h>
#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

int numThreads = 0;

class DiscardServer
{
public:
	DiscardServer(EventLoop* loop, const InetAddress& listenAddr)
		: server_(loop, listenAddr, "DiscardServer"),
		  oldCounter_(0),
		  startTimer_(Timestamp::now())
	{
		server_.setConnectionCallback(
				std::bind(&DiscardServer::onConnection, this, _1));
		server_.setMessageCallback(
				std::bind(&DiscardServer::onMessage,this,_1,_2,_3));
		server_.setThreadNum(numThreads);
		loop->runEvery(3.0,std::bind(&DiscardServer::printThroughtput,this));
	}

	void start();
	{
		LOG_INFO << "starting " << numThreads << " threads.";
		server_.start();
	}

private:
	void onConnection(const TcpConnetionPtr& conn)
	{
		LOG_TRACE << conn->peerAddress().toIpPort() << " -> "
              << conn->localAddress().toIpPort() << " is "
              << (conn->connected() ? "UP" : "DOWN");
	}

	void onMessage(const TcoConnectionPtr& conn, Buffer* buf, Timestamp)
	{
		size_t len = buf->readableBytes();
		transferred_.add(len);
		recerivedMessages_.incrementAndGet();
		buf->retrieveAll();
	}

	void printThroughput()
	{
		Timestamp endTime = Timestamp::now();
		int64_t newCounter = transferred_.get();
		int64_t bytes = newCounter - oldCounter_;
		int64_t msgs = receievedMessages_.getAndSet(0);
		double time = timeDifference(endTime,startTime_);
		printf("%4.3f MiB/s %4.3f Ki Msgs/s %6.2f bytes per msg\n",
        		static_cast<double>(bytes)/time/1024/1024,
      		  	static_cast<double>(msgs)/time/1024,
        		static_cast<double>(bytes)/static_cast<double>(msgs));
	
		oldCounter_ = newCounter;
		startTime_ = endTime;
	}

private:
	TcpServer server_;

	AtomicInt64 transferred_;
	AtomicInt64 receieveMessages_;
	int64_t oldCounter_;
	Timestamp startTime_;
};

int main(int argc, char* argv[])
{
  LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
  if (argc > 1)
  {
    numThreads = atoi(argv[1]);
  }
  EventLoop loop;
  InetAddress listenAddr(2009);
  DiscardServer server(&loop, listenAddr);

  server.start();

  loop.loop();
}
