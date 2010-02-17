#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafException::GgafException(string prm_message) : GgafObject() {
    _message = prm_message;
    MessageBox(NULL, prm_message.c_str(),"致命的な例外", MB_OK|MB_ICONSTOP);
    _TRACE_("例外発生！ GgafException::GgafException "<<prm_message);
}

string GgafException::getMsg() {
    return _message;
}

GgafException::~GgafException() {
}

