#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafException::GgafException(string prm_message) : GgafObject() {
    _message = prm_message;
    _TRACE_("í èÌó·äOî≠ê∂ÅI GgafException::GgafException "<<prm_message);
    MessageBox(NULL, prm_message.c_str(), "ó\ä˙ÇπÇ éñë‘", MB_OK|MB_ICONQUESTION);
}

string GgafException::getMsg() {
    return _message;
}

GgafException::~GgafException() {
}

