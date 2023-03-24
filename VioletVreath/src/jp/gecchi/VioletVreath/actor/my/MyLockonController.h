#ifndef MYLOCKONCONTROLLER_H_
#define MYLOCKONCONTROLLER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/core/actor/ex/DestructActor.h"

#include "jp/ggaf/core/util/RingLinkedList.hpp"
#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace VioletVreath {

/**
 * ロックオンコントローラー .
 * @version 1.00
 * @since 2010/09/08
 * @author Masatoshi Tsuge
 */
class MyLockonController : public GgafCore::DestructActor {

public:
    /** [r]１オプション当たりの現在可能ロックオン数 */
    static int lockon_num_;

    /** メインロックオンエフェクト */
    LockonCursor001_Main* pMainLockonCursor_;
    /** ロックオンターゲットリストリング */
    GgafCore::RingLinkedList<GgafDx::GeometricActor> listTarget_;

public:
    MyLockonController(const char* prm_name);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void releaseAllLockon();

    void lockon(GgafDx::GeometricActor* prm_pTarget);

    virtual ~MyLockonController();
    /**
     * pRingTarget_内容表示(デバッグ用) .
     * @param pMain
     */
    void dumpTarget(GgafDx::GeometricActor* pMain);

};

}
#endif /*MYLOCKONCONTROLLER_H_*/

