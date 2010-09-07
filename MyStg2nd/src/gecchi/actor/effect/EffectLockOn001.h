#ifndef EFFECTLOCKON001_H_
#define EFFECTLOCKON001_H_
namespace MyStg2nd {

#define EffectLockOn001_PROG_NOTHING  1
#define EffectLockOn001_PROG_LOCK     2
#define EffectLockOn001_PROG_RELEASE  3

/**
 * ÉçÉbÉNÉIÉì
 * @version 1.00
 * @since 2010/01/28
 * @author Masatoshi Tsuge
 */
class EffectLockOn001 : public GgafDx9LibStg::DefaultSpriteSetActor {

public:
    GgafDx9GeometricActor* _pTarget;

//    EffectLockOn001_Release* _pEffectLockOn_Release;

    EffectLockOn001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    void releaseLockOn();

    void lockOn(GgafDx9GeometricActor* prm_pTarget);


    virtual ~EffectLockOn001();
};

}
#endif /*EFFECTLOCKON001_H_*/

