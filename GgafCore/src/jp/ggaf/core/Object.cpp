#include "jp/ggaf/core/Object.h"

using namespace GgafCore;

#ifdef _MSC_VER
uint64_t Object::_obj_seq = 0;
#else
std::atomic<uint64_t> Object::_obj_seq(0);
#endif

Object::Object() :
    _id(Object::_obj_seq++),
    _obj_class(0)
{
}
std::string Object::toString() {
    //TODO:java‚Ì‚æ‚¤‚É‚µ‚½‚¢‚Ì‚©
    return "Object";
}
Object::~Object() {
}
