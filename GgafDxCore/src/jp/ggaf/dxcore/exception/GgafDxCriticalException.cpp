#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCriticalException::GgafDxCriticalException(string prm_message, HRESULT prm_hr) : GgafCriticalException(prm_message) {
    _hr = prm_hr;
	char buff[1000];
    ZeroMemory(buff, sizeof(buff));

    sprintf(buff, "\nHRESULT=0x%08X(%d) is %s. ErrStr=%s Desc=%s", (UINT)_hr, (int)_hr, ((FAILED(_hr)) ? "FAILED" : "SUCCEEDED"),
            DXGetErrorString(_hr), DXGetErrorDescription(_hr));
    string hrstr = buff;
	_TRACE_("GgafDxCriticalException" +(_message + hrstr));
}
string GgafDxCriticalException::getMsg() {
    char buff[1000];
    ZeroMemory(buff, sizeof(buff));

    sprintf(buff, "\nHRESULT=0x%08X(%d) is %s. ErrStr=%s Desc=%s", (UINT)_hr, (int)_hr, ((FAILED(_hr)) ? "FAILED" : "SUCCEEDED"),
            DXGetErrorString(_hr), DXGetErrorDescription(_hr));
    string hrstr = buff;
    return _message + hrstr;
}

std::string GgafDxCriticalException::getHresultMsg(HRESULT prm_hr) {
    char buff[1000];
    ZeroMemory(buff, sizeof(buff));

    sprintf(buff, "\nHRESULT=0x%08X(%d) is %s. ErrStr=%s Desc=%s", (UINT)prm_hr, (int)prm_hr, ((FAILED(prm_hr)) ? "FAILED" : "SUCCEEDED"),
            DXGetErrorString(prm_hr), DXGetErrorDescription(prm_hr));
    string hrstr = buff;
    return hrstr;
}

GgafDxCriticalException::~GgafDxCriticalException() {
}

