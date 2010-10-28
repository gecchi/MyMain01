#include "stdafx.h"
using namespace std;
using namespace GgafCore;

int GgafObject::_iSeq = 0;

GgafObject::GgafObject() {
    _obj_class = 0;
    _id = (_iSeq++);
}

string GgafObject::toString() {
    //TODO:java‚Ì‚æ‚¤‚É‚µ‚½‚¢‚Ì‚©
    return "‚¿‚å‚Á‚Æ‚Ü‚Á‚Ä‚æ";
}

GgafObject::~GgafObject() {
}
