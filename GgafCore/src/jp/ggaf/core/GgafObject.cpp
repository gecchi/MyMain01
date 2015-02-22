#include "jp/ggaf/core/GgafObject.h"

using namespace GgafCore;

#ifdef _MSC_VER
uint64_t GgafObject::_obj_seq = 0;
#else
std::atomic<uint64_t> GgafObject::_obj_seq(0);
#endif

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
