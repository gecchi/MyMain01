#ifndef EFFECTBUNSHINMAGIC001_H_
#define EFFECTBUNSHINMAGIC001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 分身魔法エフェクトその１ .
 * @version 1.00
 * @since 2013/07/31
 * @author Masatoshi Tsuge
 */
class EffectBunshinMagic001 : public GgafLib::DefaultMeshSetActor {

public:
    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

public:
    EffectBunshinMagic001(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    int isOutOfView() override {
        //画面外判定無し
        return 0;
    }

    bool isOutOfSpacetime() const override {
        //ゲーム座標範囲外判定無し
        return false;
    }

    virtual ~EffectBunshinMagic001();
};

}
#endif /*EFFECTBUNSHINMAGIC001_H_*/

