#ifndef MYOPTIONLOCKONCONTROLLER_H_
#define MYOPTIONLOCKONCONTROLLER_H_
namespace MyStg2nd {

#define MyOptionLockonController_PROG_NOTHING  1
#define MyOptionLockonController_PROG_LOCK     2
#define MyOptionLockonController_PROG_RELEASE  3

/**
 * ÉçÉbÉNÉIÉì
 * @version 1.00
 * @since 2010/01/28
 * @author Masatoshi Tsuge
 */
class MyOptionLockonController : public GgafCore::GgafDummyActor {

public:

    static int _max_lockon_num;
    int _now_lockon_num;
    EffectLockon001_Main* _pMainLockonEffect;
    GgafDx9Core::GgafDx9GeometricActor* _pMainTarget;
    GgafCore::GgafLinkedListRing<GgafDx9Core::GgafDx9GeometricActor>* _pRingTarget;

    MyOptionLockonController(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void releaseAllLockon();

    void lockon(GgafDx9Core::GgafDx9GeometricActor* prm_pTarget);

    virtual ~MyOptionLockonController();

    void dumpTarget();
};

}
#endif /*MYOPTIONLOCKONCONTROLLER_H_*/

