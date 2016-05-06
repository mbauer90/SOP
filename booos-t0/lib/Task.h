/*
 * Task.h
 *
 *  Created on: Aug 15, 2014
 *      Author: arliones
 */

#ifndef TASK_H_
#define TASK_H_

//#include <Queue.h>
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

namespace BOOOS {

class Task {
public:
	enum State {
		READY,
		WAITING,
		RUNNING,
		FINISHING
	};

	Task(void (*entry_point)(void*), int nargs, void * arg);
	virtual ~Task();

	int tid() { return _tid; }
	State state() { return _state; }

	void pass_to(Task * t, State s = READY);

	void exit(int code);

	static Task * self() { return (Task*)__running; }
	static void init();

private:
	static volatile Task * __running;

	State _state;
	int _tid; // task ID
	int __tid_counter;
	const int STACK_SIZE = 32768;
	Task* __main;
	//Queue __ready;
	ucontext_t _context;
	char* _stack;
};

} /* namespace BOOOS */

#endif /* TASK_H_ */
