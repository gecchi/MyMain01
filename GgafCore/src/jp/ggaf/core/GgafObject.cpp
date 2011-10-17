#include "stdafx.h"
using namespace std;
using namespace GgafCore;

int GgafObject::_iSeq = 0;
const char* GgafObject::NANASHI = "NANASHI";
GgafObject::GgafObject(const char* prm_name) :
_id(GgafObject::_iSeq++),
_obj_class(0) {
    _name = NEW char[51];
    strcpy(_name, prm_name);
    TRACE("GgafObject::GgafObject(" << _name << ")");
}

string GgafObject::toString() {
    //TODO:java‚Ì‚æ‚¤‚É‚µ‚½‚¢‚Ì‚©
    return "‚¿‚å‚Á‚Æ‚Ü‚Á‚Ä‚æ";
}

GgafObject::~GgafObject() {
    DELETEARR_IMPOSSIBLE_NULL(_name);
}
