#pragma once
#include <queue>
#include "IEvent.h"

class EventQueue:public std::queue<IEvent*>
{
public:
	EventQueue();
	~EventQueue();
};

