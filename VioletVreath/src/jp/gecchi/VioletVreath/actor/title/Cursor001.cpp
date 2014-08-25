#include "Cursor001.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


Cursor001::Cursor001(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "Cursor001";

}
void Cursor001::initialize() {
    getUvFlipper()->exec(FLIP_OSCILLATE_LOOP, 10);
}

void Cursor001::onActive() {

}

void Cursor001::processBehavior() {
    getKuroko()->behave();
    getUvFlipper()->behave();
}

void Cursor001::processJudgement() {
}

void Cursor001::moveTo(coord tx, coord ty) {
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setMvAngTwd(tx, ty);
    pKuroko->asstA()->slideMvByDt(UTIL::getDistance(_x, _y, tx, ty),
                                  8, 0.2, 0.3, 0, true);
}

Cursor001::~Cursor001() {

}
