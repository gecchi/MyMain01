#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9CriticalException::GgafDx9CriticalException(string prm_message, HRESULT prm_hr) : GgafCriticalException(prm_message) {
	_hr = prm_hr;
}
string GgafDx9CriticalException::getMsg() {
    char buff[1000];
    ZeroMemory(buff, sizeof(buff));

    sprintf(buff, "\nHRESULT=0x%08X(%d) is %s. ErrStr=%s Desc=%s", _hr,_hr, ( (FAILED(_hr)) ? "FAILED" : "SUCCEEDED") , DXGetErrorString9(_hr), DXGetErrorDescription9(_hr));
    string hrstr = buff;
	return _message + hrstr;
}
GgafDx9CriticalException::~GgafDx9CriticalException() {
}

