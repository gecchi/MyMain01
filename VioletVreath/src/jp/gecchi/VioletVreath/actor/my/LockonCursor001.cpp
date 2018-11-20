#include "LockonCursor001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

LockonCursor001::LockonCursor001(const char* prm_name, const char* prm_model_id) :
        DefaultMassSpriteActor(prm_name, prm_model_id, nullptr) {
    _class_name = "LockonCursor001";
    pTarget_ = nullptr;
    inactivate();
    defineRotMvWorldMatrix_Billboard(); //ワールド変換はビルボードでRz回転に強制
    effectBlendOne(); //エフェクトテクニックは加算合成に強制
    setZEnableDraw(false);      //Zバッファは考慮無しに強制
    setZWriteEnable(false); //自身のZバッファを書き込みしないに強制
    setSpecialRenderDepthIndex(1); //描画順序を最前面描画に強制。ロックオンエフェクトが隠れないようにするため。
    setCullingDraw(false);  //α部分があるため、カリングをOFFするため透明オブジェクト扱いにする。

    setHitAble(false); //当たり判定無し
    GgafDxSeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(0, "WAVE_LOCKON_001"); //効果音定義
    useProgress(PROG_BANPEI);
}

void LockonCursor001::initialize() {
}


void LockonCursor001::onReset() {
    getProgress()->reset(LOCKON001_PROG_RELEASE);
}

void LockonCursor001::onActive() {
    if (pTarget_ == nullptr) {
        inactivateImmed();
        return;
    }
}

void LockonCursor001::processBehavior() {

}

void LockonCursor001::processJudgement() {
}

void LockonCursor001::onInactive() {
}


LockonCursor001::~LockonCursor001() {
}

