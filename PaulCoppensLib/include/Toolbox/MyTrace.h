#ifndef MYTRACE_H
#define MYTRACE_H

#include "..\framework\Frm_TBuff.h"

#include <stdio.h>
#include <fstream>
#include <sstream>

using namespace std;

namespace ToolBox {

static std::string temp;

static const char* GetLastError()
{
	TBuff* _Buff = TBuff::GetInstance();
	temp = _Buff->Get();
/*   memcpy(temp, _Buff->Get(), 512);
   temp[strlen(_Buff->Get())] = '\0';*/
   _Buff->Reset();
   return temp.c_str();
};/**/

static void RemTrace(void)
{
	TBuff* _Buff = TBuff::GetInstance();
	ofstream fout(_Buff->_TraceName);
   fout << "Debug file ..." << "\n";
   fout << flush;
   fout.close();/**/
};

template<typename T1>
   void Trace( T1 par1 )
	{
   	TBuff* _Buff = TBuff::GetInstance();
   	stringstream ss;
      ss << par1 << ends;
      _Buff->Set(ss.str().c_str());
      ofstream fout(_Buff->_TraceName, ios::app);
		fout << par1 << "\n";
      fout << flush;
      fout.close();/**/
	};

template<typename T1, typename T2>
	void Trace( T1 par1, T2 par2 )
	{
		stringstream ss;

		ss << par1 << " " << par2 << ends;
		Trace( ss.str() );
	};

template<typename T1, typename T2, typename T3>
	void Trace( T1 par1, T2 par2, T3 par3 )
	{
		stringstream ss;

		ss << par1 << " " << par2 << " " << par3 << ends;
		Trace( ss.str() );
	};

template<class T1, typename T2, typename T3, typename T4>
	void Trace( T1 par1, T2 par2, T3 par3, T4 par4 )	{
		stringstream ss;

		ss << par1 << " " << par2 << " " << par3 << " " << par4 << ends;
		Trace( ss.str() );
	};

template<typename T1, typename T2, typename T3, typename T4, typename T5>
	void Trace( T1 par1, T2 par2, T3 par3, T4 par4, T5 par5 )
	{
		stringstream ss;

		ss << par1 << " " << par2 << " " << par3 << " " << par4 << " " << par5 << ends;
		Trace( ss.str() );
	};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	void Trace( T1 par1, T2 par2, T3 par3, T4 par4, T5 par5, T6 par6 )
	{
		stringstream ss;

		ss << par1 << " " << par2 << " " << par3 << " " << par4 << " " << par5 << " " << par6 << ends;
		Trace( ss.str() );
	};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	void Trace( T1 par1, T2 par2, T3 par3, T4 par4, T5 par5, T6 par6, T7 par7 )
	{
		stringstream ss;

		ss << par1 << " " << par2 << " " << par3 << " " << par4 << " " << par5 << " " << par6 << " " << par7 << ends;
		Trace( ss.str() );
	};
};

//#ifdef DEBUG
	#define GETLASTERROR ToolBox::GetLastError()
//#else
//	#define GETLASTERROR "No reporting enabled...\n"
//#endif


//#ifdef DEBUG
	#define MYTRACE ToolBox::Trace
//#else
//	#define MYTRACE //
//#endif

//#ifdef DEBUG
	#define START_TRACE _Buff = TBuff::GetInstance();GetCurrentDirectory(512, _Buff->_TraceName);memcpy(&_Buff->_TraceName[strlen(_Buff->_TraceName)], "\\Debug\\Trace.txt\0",17);ToolBox::RemTrace()
//#else
//	#define START_TRACE //
//#endif

//#ifdef DEBUG
	#define END_TRACE delete _Buff
//#else
//	#define END_TRACE //
//#endif

//#ifdef DEBUG
	#define DECLARE_TRACE TBuff* TBuff::_Instance = 0; TBuff* _Buff
//#else
//	#define END_TRACE //
//#endif

#endif
