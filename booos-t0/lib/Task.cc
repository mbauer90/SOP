#include "Task.h"

namespace BOOOS
{

volatile Task * Task::__running;

	Task::Task(void (*entry_point)(void *), int nargs, void * arg){
		getcontext(&_context);
		_stack = (char*)malloc(STACK_SIZE);
			if(_stack) {
				_context.uc_stack.ss_sp = _stack ;
				_context.uc_stack.ss_size = STACK_SIZE;
				_context.uc_stack.ss_flags = 0;
				_context.uc_link = 0;
			}
			else {
				perror("Erro na criação da pilha: ");
				this->exit(1);
			}
		makecontext(&_context,(void (*)())entry_point, nargs, arg);
	}

	Task::~Task(){}

	void Task::pass_to(Task * t, State s){
		//if(s==READY){
			t->_state = RUNNING;
			this->_state = WAITING;
			swapcontext(&this->_context,&t->_context);
		//}
	}

	void Task::exit(int code){

	}

	void Task::init(){
		//ucontext_t auxiliar;
		//getcontext(&auxiliar);
		//__main->_context = auxiliar;
		//__running=__main;
	}

} /* namespace BOOOS */
