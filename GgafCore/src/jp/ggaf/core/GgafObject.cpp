#include "stdafx.h"
using namespace std;
using namespace GgafCore;

int GgafObject::_iSeq = 0;
GgafObject::GgafObject(const char* prm_name) {
    _obj_class = 0;
    _id = (_iSeq++);
    _name = NEW char[51];
    if (prm_name) {
        strcpy(_name, prm_name);
    } else {
        strcpy(_name, "?NANASHISAN?");
    }
    TRACE("GgafObject::GgafObject(" << _name << ")");
}
char* GgafObject::getName() {
       return _name;
}
string GgafObject::toString() {
    //TODO:java‚Ì‚æ‚¤‚É‚µ‚½‚¢‚Ì‚©
    return "‚¿‚å‚Á‚Æ‚Ü‚Á‚Ä‚æ";
}

GgafObject::~GgafObject() {
    DELETEARR_IMPOSSIBLE_NULL(_name);
}
