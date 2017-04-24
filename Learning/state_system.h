#ifndef STATE_SYSTEM_H
#define STATE_SYSTEM_H

class State
{
public:
	State() : Set(false) {}
	~State() {}

	int Words[2] = {};
	int Numbers[3] = {};
	bool Set;

private:
};

#endif