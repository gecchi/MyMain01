#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


Cursor001::Cursor001(const char* prm_name) : DefaultBoardActor(prm_name, "cursor001") {
    _class_name = "Cursor001";
    //_z = 0.99;//���Ԃ�Ŕw�� �i0 <= _z < 1.0�jZ=(0�`+1)
    _z = 0.9999999f;
}
void Cursor001::initialize() {
}

void Cursor001::onActive() {
}

void Cursor001::processBehavior() {
}

void Cursor001::processJudgement() {
}


Cursor001::~Cursor001() {
}
