#ifndef EFFECTBUNSHINMAGIC001_H_
#define EFFECTBUNSHINMAGIC001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

namespace VioletVreath {

/**
 * 分身魔法エフェクトその１ .
 * @version 1.00
 * @since 2013/07/31
 * @author Masatoshi Tsuge
 */
class EffectBunshinMagic001 : public EffectBlink {

public:
    EffectBunshinMagic001(const char* prm_name);

    void processBehavior() override;

    int isOutOfView() override {
        //画面外判定無し
        return 0;
    }

    bool isOutOfSpacetime() const override {
        //ゲーム座標範囲外判定無し
        return false;
    }

    void blink(frame prm_scale_in_frames, frame prm_duration_frames, frame prm_scale_out_frames,
               const GgafDx::GeometricActor* prm_pFollowTarget, bool prm_sayonara_end = true) override;

    void blink2(frame prm_scale_in_frames, frame prm_duration_frames, frame prm_scale_out_frames,
                const GgafDx::GeometricActor* prm_pFollowTarget, bool prm_sayonara_end = true) override;

    virtual ~EffectBunshinMagic001();
};

}
#endif /*EFFECTBUNSHINMAGIC001_H_*/

