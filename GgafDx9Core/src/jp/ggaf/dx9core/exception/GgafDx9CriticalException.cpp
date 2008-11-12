#include "stdafx.h"

GgafDx9CriticalException::GgafDx9CriticalException(string prm_message, HRESULT prm_hr) : GgafCriticalException(prm_message) {
	_hr = prm_hr;
}
string GgafDx9CriticalException::getMsg() {
    char buff[1000];
    sprintf(buff, "\nHRESULT=%08X (%s) ErrStr=%s Desc=%s", _hr, ( (FAILED(_hr)) ? "FAILED" : "SUCCEEDED") , DXGetErrorString9(_hr), DXGetErrorDescription9(_hr));
    string hrstr = buff;
	return _message + hrstr;
}
GgafDx9CriticalException::~GgafDx9CriticalException() {
}

