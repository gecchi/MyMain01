#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafException::GgafException(string prm_message) : GgafObject() {
    _message = prm_message;
    _TRACE_("通常例外発生！ GgafException::GgafException "<<prm_message);
    MessageBox(NULL, prm_message.c_str(), "予期せぬ事態", MB_OK|MB_ICONQUESTION);
}

string GgafException::getMsg() {
    return _message;
}

GgafException::~GgafException() {
}

