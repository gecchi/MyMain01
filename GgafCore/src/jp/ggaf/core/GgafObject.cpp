#include "stdafx.h"
using namespace std;
using namespace GgafCore;

//int GgafObject::_iSeq = 0;

GgafObject::GgafObject() {
    _obj_class = 0;
}

string GgafObject::toString() {
    //TODO:javaのようにしたいのか
    return "ちょっとまってよ";
}

GgafObject::~GgafObject() {
}
