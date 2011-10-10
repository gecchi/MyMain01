#ifndef MYOPTIONLOCKONCONTROLLER_H_
#define MYOPTIONLOCKONCONTROLLER_H_
namespace MyStg2nd {


/**
 * ロックオンコントローラー .
 * @version 1.00
 * @since 2010/09/08
 * @author Masatoshi Tsuge
 */
class MyOptionLockonController : public GgafCore::GgafDummyActor {

public:
    /** メインロックオンエフェクト */
    EffectLockon001_Main* _pMainLockonEffect;
    /** ロックオンターゲットリストリング */
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeometricActor>* _pRingTarget;

    MyOptionLockonController(const char* prm_name);

    void initialize() override;

    void onReset() override;

    void processBehavior() override;

    void processJudgement() override;

    void releaseAllLockon();

    void lockon(GgafDxCore::GgafDxGeometricActor* prm_pTarget);

    virtual ~MyOptionLockonController();
    /**
     * _pRingTarget内容表示(デバッグ用) .
     * @param pMain
     */
    void dumpTarget(GgafDxCore::GgafDxGeometricActor* pMain);


};

}
#endif /*MYOPTIONLOCKONCONTROLLER_H_*/

