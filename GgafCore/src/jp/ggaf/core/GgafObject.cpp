#include "stdafx.h"
#include "jp/ggaf/core/GgafObject.h"

using namespace GgafCore;

uint64_t GgafObject::_obj_seq = 0;
GgafObject::GgafObject() {
    _obj_class = 0;
    _id = (_obj_seq++);
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
