#include "examples/asio/chat/codec.h"

#include "muduo/base/Logging.h"
#include "muduo/base/Mutex.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/TcpServer.h"

#include <set>
#include <stdio.h>
#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

class ChatServer : noncopyable
{
public:
	ChatServer(EventLoop* loop,
		   const InetAddr& listenAddr)
		: Server_(&loop,listenAddr,"ChatServer")
		  codec_(std::bind(&onStringMessage,this,_1,_2,_3))
	{
		server_.setConnectionCallback_(
				std::bind(&onConnection,this,_1));
		server_.setMessageCallback_(
				std::bind(&LengthHeaderCodec::onMessage,&codec_,_1,_2,_3));
	}
	
	void start()
	{
		server_.start();
	}

privete:		
	void onConnection(const TcpConnectionPtr& conn)
	{
		LOG_INFO << conn->localAddress().toIpPort() << " -> "
             		<< conn->peerAddress().toIpPort() << "is "
             		<< (conn->connected() ? "UP" : "DOWN");

		if(conn->connected())
		{ connections_.insert(conn); }
		else
		{ connection_.erase(conn); }
	}

	void onStringMessage(const TcpConnectionPtr&,
				const string& message,
				Timestamp )
	{
		for(ConnectionList::iterator it = connections_.begin();
				it != connections_.end();
				++it)
		{
			codec_send((*it).get(),message);
		}
	}

private:
	typedef std::set<TcpConnectionPtr> ConnectionList;
	TcpServer server_;
	LengthHeaderCodec codec_;
	ConnectionList connections_;
};

int main(int argc, char* argv[])
{
	LOG_INFO << "pid = " << getpid();
	if(argc > 1)
	{
		EventLoop loop;
		uint16_t port = static_cast<unit16_t>(atoi(argv[1]));
		InetAddress serverAddr(port);
		ChatServer server(&loop,serverAddr);
		server.start();
		loop.loop();
	}
	else
	{
		printf("Usage: %s port\n", argv[0]);
	}
}
