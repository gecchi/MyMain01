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
    /** １オプション当たりの最大可能ロックオン数（メイン＋サブ） */
    static int _max_lockon_num;
    /** メインロックオンエフェクト */
    EffectLockon001_Main* _pMainLockonEffect;
    /** ロックオンターゲットリストリング */
    GgafCore::GgafLinkedListRing<GgafDx9Core::GgafDx9GeometricActor>* _pRingTarget;

    MyOptionLockonController(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void releaseAllLockon();

    void lockon(GgafDx9Core::GgafDx9GeometricActor* prm_pTarget);

    virtual ~MyOptionLockonController();
    /**
     * _pRingTarget内容表示(デバッグ用) .
     * @param pMain
     */
    void dumpTarget(GgafDx9Core::GgafDx9GeometricActor* pMain);


};

}
#endif /*MYOPTIONLOCKONCONTROLLER_H_*/

