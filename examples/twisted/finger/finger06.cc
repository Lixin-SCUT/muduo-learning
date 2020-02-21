// finger06.cc
// Created by Lixin on 2020.02.19

#include "muduo/net/EventLoop.h"
#include "muduo/net/TcpServer.h"

#include <map>

using namespace muduo;
using namespace muduo::net;

typedef std::map<string,string> UserMap;
UserMap users;

void onMessage(TcpConnectionPtr&,
		Buffer*,
		Timestamp);

string getUser(const string&);

int main()
{
	EventLoop loop;
	TcpServer server(&loop,InetAdddress(1079),"Finger");
	server.setMessageCallback(onMessage);
	server.start();
	loop.loop();
}

void onMessage(TcpConnectionPtr& conn,
		Buffer* buf,
		Timestamp receiveTime)
{
	const char* crlf = buf->findCRLF();
	if(crlf)
	{
		string user(buf->peek(),crlf);//read a string crlf from buf,but not delete
		conn->send(getUser(user) + "\r\n");
		buf->retriveUntil(crlf + 2);
		conn->shutdown()
	}
}

string getUser(const string& user)
{
	string result = "No such user";
	UserMap::iterator it = users.find(user);
	if(it != users.end())
	{
		result = it->second;
	}
	return result;
}

