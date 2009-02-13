/////////////////////////////////////////////////////////
// Frm_Tbuff.h
//
//
/////////////////////////////////////////////////////////

#ifndef FRM_TBUFF_H
#define FRM_TBUFF_H

#include <mem.h>
#include <string.h>
TBuff* TBuff::_Instance = NULL;

//??????

class TBuff {
private:
public:
 static TBuff* _Instance;
   char _Info[512];
   TBuff(void){Reset();memset(_TraceName, '\0', 512);};

   	static TBuff* GetInstance(void){if (_Instance == 0) _Instance = new TBuff; return _Instance;};
      void Set(const char* pText){memcpy(_Info, pText, strlen(pText));};
      const char* Get(void){return _Info;};
      void Reset(void){memset(_Info, '\0', 512);};
      char _TraceName[512];

};


#endif
