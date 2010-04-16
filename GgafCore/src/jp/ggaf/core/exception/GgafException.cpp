#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafException::GgafException(string prm_message) : GgafObject() {
    _message = prm_message;
    _TRACE_("通常例外発生！ GgafException::GgafException "<<prm_message);
}

string GgafException::getMsg() {
    return _message;
}

GgafException::~GgafException() {
}

