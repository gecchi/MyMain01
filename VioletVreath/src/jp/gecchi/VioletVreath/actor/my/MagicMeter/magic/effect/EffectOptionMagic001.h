#ifndef EFFECTOPTIONMAGIC001_H_
#define EFFECTOPTIONMAGIC001_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * オプション魔法エフェクトその１ .
 * @version 1.00
 * @since 2013/07/31
 * @author Masatoshi Tsuge
 */
class EffectOptionMagic001 : public GgafLib::DefaultMeshSetActor {

public:
    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

public:
    EffectOptionMagic001(const char* prm_name);

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

    bool isOutOfUniverse() override {
        //ゲーム座標範囲外判定無し
        return false;
    }

    virtual ~EffectOptionMagic001();
};

}
#endif /*EFFECTOPTIONMAGIC001_H_*/

