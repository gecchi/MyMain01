#include "Test01.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Hogera;

Test01::Test01(const char* prm_name) :
        DefaultSpriteActor(prm_name, "Lockon001", nullptr) {
    _class_name = "Test01";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ワールド変換はビルボードでRz回転に強制

    setAlpha(0.9);          //α部分があるため、カリングをOFFするため透明オブジェクト扱いにする。

    setHitAble(false); //当たり判定無し
//    GgafDxSeTransmitterForActor* pSe = getSeTransmitter();
//    pSe->set(0, "WAVE_LOCKON_001"); //効果音定義
    useProgress(PROG_BANPEI);
}

void Test01::initialize() {
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);   //アニメ範囲を０～１５
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //アニメ順序
}


void Test01::onReset() {
    getProgress()->reset(LOCKON001_PROG_RELEASE);
}

void Test01::onActive() {
    getUvFlipper()->setActivePtnToTop();
    getKuroko()->setFaceAngVelo(AXIS_Z, 1000);        //回転

}

void Test01::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();


    getUvFlipper()->behave();
    pKuroko->behave();

}

void Test01::processJudgement() {
}

void Test01::onInactive() {
}


Test01::~Test01() {
}

