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
    int _max_lock_num;
    GgafCore::GgafLinkedListRing<GgafDx9Core::GgafDx9GeometricActor> _ringTarget;

    MyOptionLockonController(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void releaseLockOn();

    void lockOn(GgafDx9GeometricActor* prm_pTarget);

    virtual ~MyOptionLockonController();
};

}
#endif /*MYOPTIONLOCKONCONTROLLER_H_*/

