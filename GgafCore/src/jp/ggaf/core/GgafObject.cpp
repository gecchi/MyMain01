#include "stdafx.h"
using namespace std;
using namespace GgafCore;

int GgafObject::_iSeq = 0;

GgafObject::GgafObject() {
    _obj_class = 0;
    _id = (_iSeq++);
}

string GgafObject::toString() {
    //TODO:java�̂悤�ɂ������̂�
    return "������Ƃ܂��Ă�";
}

GgafObject::~GgafObject() {
}
