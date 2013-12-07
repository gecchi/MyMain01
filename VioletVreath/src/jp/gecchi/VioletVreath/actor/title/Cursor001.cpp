#include "stdafx.h"
#include "Cursor001.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAsstA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


Cursor001::Cursor001(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "Cursor001";
    pKurokoAsstA_ = NEW GgafDxKurokoAsstA(_pKuroko);

}
void Cursor001::initialize() {
    _pUvFlipper->exec(FLIP_OSCILLATE_LOOP, 10);
}

void Cursor001::onActive() {

}

void Cursor001::processBehavior() {
    pKurokoAsstA_->behave();
    _pKuroko->behave();
    _pUvFlipper->behave();
}

void Cursor001::processJudgement() {
}

void Cursor001::moveTo(int X, int Y) {
    _pKuroko->setMvAngTwd(X, Y);
    pKurokoAsstA_->slideMvByDt(UTIL::getDistance(_x, _y, (coord)X, (coord)Y), 8, 0.2, 0.3, 0);
}

Cursor001::~Cursor001() {
    GGAF_DELETE(pKurokoAsstA_);

}
