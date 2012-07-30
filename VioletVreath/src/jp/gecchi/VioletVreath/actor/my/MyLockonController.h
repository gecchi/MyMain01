#ifndef MYOPTIONLOCKONCONTROLLER_H_
#define MYOPTIONLOCKONCONTROLLER_H_
namespace VioletVreath {


/**
 * ロックオンコントローラー .
 * @version 1.00
 * @since 2010/09/08
 * @author Masatoshi Tsuge
 */
class MyLockonController : public GgafCore::GgafDummyActor {

public:
    /** メインロックオンエフェクト */
    EffectLockon001_Main* pMainLockonEffect_;
    /** ロックオンターゲットリストリング */
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeometricActor>* pRingTarget_;

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
#endif /*MYOPTIONLOCKONCONTROLLER_H_*/

