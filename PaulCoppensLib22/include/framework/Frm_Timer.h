/////////////////////////////////////////////////////////
// Frm_Timer
// The timer is responsible for calculating the elapsed
// time.
/////////////////////////////////////////////////////////

#ifndef FRM_TIMER_H
#define FRM_TIMER_H

#include "framework\frm_types.h"

#define MAX_TIMERS 10

namespace Frm {
class Timer {
	public:
      //derive the function static Timer* GetInstance(void);
		~Timer(void){};
      virtual void InitTimer(uint16 index=0){};
      virtual uint32 GetTime(uint16 index=0){return 0;};

   protected:
   	Timer(void) {for(int i= 0; i<MAX_TIMERS; i++) {_old[i] = 0; _new[i] = 0;}};
      uint32 _old[MAX_TIMERS], _new[MAX_TIMERS];
   	static Timer* _Instance;
};

};
#endif
