// finger01.cc
// Created by Lixin on 2020.02.19

#include "muduo/net/EventLoop.h"

using namespace muduo;
using namespace muduo::net;

int main()
{
	EventLoop loop;
	loop.loop();
}
