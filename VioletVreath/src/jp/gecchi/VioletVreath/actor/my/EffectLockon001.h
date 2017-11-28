#ifndef EFFECTLOCKON001_H_
#define EFFECTLOCKON001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMassSpriteActor.h"

namespace VioletVreath {



/**
 * ロックオン
 * @version 1.00
 * @since 2010/01/28
 * @author Masatoshi Tsuge
 */
class EffectLockon001 : public GgafLib::DefaultMassSpriteActor {

public:
    enum {
        LOCKON001_PROG_FIRST_LOCK ,
        LOCKON001_PROG_LOCK       ,
        LOCKON001_PROG_RELEASE    ,
        PROG_BANPEI,
    };


    GgafDxCore::GgafDxGeometricActor* pTarget_;

public:
    EffectLockon001(const char* prm_name, const char* prm_model_id);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void onActive() override;

    virtual void onReset() override;

    virtual void onInactive() override;

    virtual void processJudgement() override;

    virtual void releaseLockon() = 0;

    virtual void lockon(GgafDxGeometricActor* prm_pTarget) = 0;

    virtual ~EffectLockon001();


//DEBUGモードアプリ終了時のツリー表示時、
//pTarget_が不正になる場合等、必要なときにコメントを外して使用。
//
//    /**
//     * ターゲットも表示するダンプ(デバッグ用) .
//     */
//    void dump();
//
//    /**
//     * ターゲットも表示するダンプ(デバッグ用) .
//     */
//    void dump(std::string prm_parent);

};

}
#endif /*EFFECTLOCKON001_H_*/

