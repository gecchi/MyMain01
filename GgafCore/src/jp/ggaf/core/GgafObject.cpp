#include "jp/ggaf/core/GgafObject.h"

using namespace GgafCore;

uint64_t GgafObject::_obj_seq = 0;

GgafObject::GgafObject() :
    _id(GgafObject::_obj_seq++),
    _obj_class(0)
{
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
