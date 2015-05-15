#ifndef MYLOCKONCONTROLLER_H_
#define MYLOCKONCONTROLLER_H_
#include "VioletVreath.h"
#include "jp/ggaf/core/actor/ex/GgafDestructActor.h"

#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

namespace VioletVreath {


/**
 * ロックオンコントローラー .
 * @version 1.00
 * @since 2010/09/08
 * @author Masatoshi Tsuge
 */
class MyLockonController : public GgafCore::GgafDestructActor {

public:
    /** [r]１オプション当たりの最大可能ロックオン数 */
    static int max_lockon_num_;
    /** [r]１オプション当たりの現在可能ロックオン数 */
    static int lockon_num_;

    /** メインロックオンエフェクト */
    EffectLockon001_Main* pMainLockonEffect_;
    /** ロックオンターゲットリストリング */
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeometricActor>* pRingTarget_;

public:
    MyLockonController(const char* prm_name);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void releaseAllLockon();

    void lockon(GgafDxCore::GgafDxGeometricActor* prm_pTarget);

    virtual ~MyLockonController();
    /**
     * pRingTarget_内容表示(デバッグ用) .
     * @param pMain
     */
    void dumpTarget(GgafDxCore::GgafDxGeometricActor* pMain);

};

}
#endif /*MYLOCKONCONTROLLER_H_*/

