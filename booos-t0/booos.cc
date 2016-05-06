/*
 * Queue_Test.cc
 *
 *  Created on: Feb 21, 2014
 *      Author: arliones
 */

#include <iostream>
#include <BOOOS.h>
#include <Task.h>


using namespace std;
using namespace BOOOS;

Task *ping, *pong, *Main;

void f_ping(void * arg) {
	int i ;
	cout << (char *) arg << " Start" << endl;

	for (i=0; i<4; i++)
	{
		cout << "\t" << (char*) arg << " " << i << endl;
		ping->pass_to(pong);
	}
	cout << (char *) arg << " End" << endl;

	ping->pass_to(Main);
}

void f_pong(void * arg) {
	int i ;

	cout << (char *) arg << " Start" << endl;

	for (i=0; i<4; i++)
	{
		cout << "\t" << (char*) arg << " " << i << endl;
		pong->pass_to(ping);
	}
	cout << (char *) arg << " End" << endl;

	pong->pass_to(Main);
}

int main() {

	BOOOS::BOOOS booos;

	cout << "Main Start" << endl;

	ping = new Task(f_ping, 1, (char*)"\tPing");
	pong = new Task(f_pong, 1, (char*)"\tPong");
	Main = Task::self();

	Main->pass_to(ping);
    Main->pass_to(pong);

	cout << "Main End" << endl;

	Main->exit(0);
}
