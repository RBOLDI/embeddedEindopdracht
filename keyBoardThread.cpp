// w3.1.3hwlayer

#include "keyBoardThread.hpp"

using namespace std;

bool bExit = false;
bool bSwitch = false;

keyBoardThread::keyBoardThread(void) {
	// Initialiseer de thread instellingen
	pthread_attr_init(&keyBoardAttr_);
	pthread_attr_setdetachstate(&keyBoardAttr_, PTHREAD_CREATE_JOINABLE);
	// Maak de thread zelf en koppel de class instantie via het dataveld
	int nRet = pthread_create(&keyBoardThread_, &keyBoardAttr_, thread, NULL); 
	if (nRet > 0) {
		printf("keyBoardThread kon niet gemaakt worden!\n");
		return;
	};
};

keyBoardThread::~keyBoardThread() {
  // Vrijgeven thread instellingen
  pthread_attr_destroy(&keyBoardAttr_);
};

void keyBoardThread::join() {

  void *pStatus;

  // Wacht tot de thread klaar is
  pthread_join(keyBoardThread_, &pStatus); 
};

void keyBoardThread::delay(long nMSec) {
	
  struct timespec oTime, oTimeLeft;
  // Handige delay-functie in msec
  oTime.tv_sec = 0; 
  oTime.tv_nsec = nMSec * 1000000L;
  nanosleep(&oTime, &oTimeLeft);
};

void *keyBoardThread::thread(void *pThreadData) {	
	keyBoardThread *pThis;
	pThis = (keyBoardThread*)pThreadData;
	int nKey;
	while(!bExit){
		pthread_mutex_lock(&oLockKeyboard);
		nKey = getch();
		if (nKey == ESC) {
			bExit = true;
		};
		if(nKey == SHIFT_RIGHT){
			bSwitch = true;
		}
		pthread_mutex_unlock(&oLockKeyboard);
		pThis->delay(40);
	}
	// Thread vrijgeven
	pthread_exit(NULL);
};

