#include "stdafx.h"
using namespace std;
using namespace GgafCore;

int GgafObject::_iSeq = 0;
GgafObject::GgafObject() {
    _obj_class = 0;
    _id = (_iSeq++);
//    TRACE("GgafObject::GgafObject(" << _name << ")");
}
//char* GgafObject::getName() {
//       return _name;
//}
char* GgafObject::toString() {
    //TODO:java�̂悤�ɂ������̂�
    return "������Ƃ܂��Ă�";
}

GgafObject::~GgafObject() {
//    DELETEARR_IMPOSSIBLE_NULL(_name);
}
