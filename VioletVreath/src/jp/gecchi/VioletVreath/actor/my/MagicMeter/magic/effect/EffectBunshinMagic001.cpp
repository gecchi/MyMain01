#include "EffectBunshinMagic001.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxTrucker.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectBunshinMagic001::EffectBunshinMagic001(const char* prm_name)
               : EffectBlink(prm_name, "EffectBunshinMagic001") {
    _class_name = "EffectBunshinMagic001";
    effectBlendOne(); //加算合成するTechnique指定
    setZEnableDraw(true);        //描画時、Zバッファ値は考慮される
    setZWriteEnable(false);  //自身のZバッファを書き込みしない
    setCullingDraw(false);
    getKuroko()->setRollPitchYawFaceAngVelo(PX_C(3), PX_C(5), PX_C(7));
}

void EffectBunshinMagic001::processBehavior() {
    EffectBlink::processBehavior();
    getKuroko()->behave();
    getTrucker()->behave();
}

void EffectBunshinMagic001::blink(frame prm_scale_in_frames, frame prm_duration_frames, frame prm_scale_out_frames,
           const GgafDxCore::GgafDxGeometricActor* prm_pFollowTarget, bool prm_sayonara_end) {
    getScaler()->setRange(0, R_SC(4.0));
    EffectBlink::blink(prm_scale_in_frames, prm_duration_frames, prm_scale_out_frames, prm_pFollowTarget, prm_sayonara_end);
}

void EffectBunshinMagic001::blink2(frame prm_scale_in_frames, frame prm_duration_frames, frame prm_scale_out_frames,
            const GgafDxCore::GgafDxGeometricActor* prm_pFollowTarget, bool prm_sayonara_end) {
    getScaler()->setRange(0, R_SC(6.0));
    EffectBlink::blink2(prm_scale_in_frames, prm_duration_frames, prm_scale_out_frames, prm_pFollowTarget, prm_sayonara_end);
}

EffectBunshinMagic001::~EffectBunshinMagic001() {
}
