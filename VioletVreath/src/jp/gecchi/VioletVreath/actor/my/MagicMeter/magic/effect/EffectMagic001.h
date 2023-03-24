#ifndef EFFECTMAGIC001_H_
#define EFFECTMAGIC001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 魔法エフェクトその１ .
 * @version 1.00
 * @since 2011/01/18
 * @author Masatoshi Tsuge
 */
class EffectMagic001 : public GgafLib::DefaultMeshSetActor {

public:
    EffectMagic001(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

//    int isOutOfView() override {
//        //画面外判定無し
//        return 0;
//    }
//
//    bool isOutOfSpacetime() const override {
//        //ゲーム座標範囲外判定無し
//        return false;
//    }

    virtual ~EffectMagic001();
};

}
#endif /*EFFECTMAGIC001_H_*/

