#include "stdafx.h"
using namespace GgafCore;

int GgafObject::_obj_seq = 0;
GgafObject::GgafObject() {
    _obj_class = 0;
    _id = (_obj_seq++);
//    TRACE("GgafObject::GgafObject(" << _name << ")");
}
//char* GgafObject::getName() {
//       return _name;
//}
char* GgafObject::toString() {
    //TODO:javaのようにしたいのか
    return "ちょっとまってよ";
}

GgafObject::~GgafObject() {
//    GGAF_DELETEARR(_name);
}
