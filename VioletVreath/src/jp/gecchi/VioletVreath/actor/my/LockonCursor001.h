#ifndef LOCKONCURSOR001_H_
#define LOCKONCURSOR001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMassSpriteActor.h"

namespace VioletVreath {



/**
 * ロックオン
 * @version 1.00
 * @since 2010/01/28
 * @author Masatoshi Tsuge
 */
class LockonCursor001 : public GgafLib::DefaultMassSpriteActor {

public:
    enum {
        LOCKON001_PHASE_FIRST_LOCK ,
        LOCKON001_PHASE_LOCK       ,
        LOCKON001_PHASE_RELEASE    ,
        PHASE_BANPEI,
    };


    GgafDx::GeometricActor* pTarget_;
    GgafDx::GeometricActor* pTarget_prev_;
public:
    LockonCursor001(const char* prm_name, const char* prm_model);

    virtual void initialize() override;

    virtual void onCreateModel() override;

    virtual void processBehavior() override;

    virtual void onActive() override;

    virtual void onReset() override;

    virtual void onInactive() override;

    virtual void processJudgement() override;

    virtual void releaseLockon() = 0;

    virtual void lockon(GgafDx::GeometricActor* prm_pTarget) = 0;


    bool hasJustLockon() {
        if (pTarget_prev_ != pTarget_ && pTarget_ != nullptr) {
            return true;
        } else {
            return false;
        }
    }

    bool hasJustReleaseLockon() {
        if (pTarget_prev_ && pTarget_ == nullptr) {
            return true;
        } else {
            return false;
        }
    }

    virtual ~LockonCursor001();


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
#endif /*LOCKONCURSOR001_H_*/

