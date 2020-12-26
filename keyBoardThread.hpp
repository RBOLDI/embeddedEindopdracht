// w3.1.3hwlayer

//TODO: zorg voor de juiste # commando's
#ifndef _KEYBOARDTHREAD_HPP_
#define _KEYBOARDTHREAD_HPP_


#include <curses.h> 
#include <stdint.h>
#include <bcm2835.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <iostream>
#include <fstream>

#define ESC 27
#define ENTER 10
#define SHIFT_RIGHT 402
#define SHIFT_LEFT	393

//Shared values
extern pthread_mutex_t oLockKeyboard;
extern bool bExit;
extern bool bSwitch;

// De keyboard thread hardware laag class
class keyBoardThread {
	public:
		keyBoardThread(void);
		~keyBoardThread();
		void join();

	private:
		pthread_t keyBoardThread_;
		pthread_attr_t keyBoardAttr_;
		void delay(long nMSec);
		static void *thread(void *pThreadData);
};

#endif // _KEYBOARDTHREAD_HPP_