// time.cc
// Created by Lixin on 2020.02.28

#include "muduo/net/EventLoop.h"

#include <iostream>

void print()
{
	std::cout << "Hallo World!\n";
}

int main()
{
	muduo::net::EventLoop loop;
	loop.runAfter(5,print)l
	loop.loop();
}

