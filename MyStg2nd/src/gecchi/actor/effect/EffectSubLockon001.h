#ifndef EFFECTSUBLOCKON001_H_
#define EFFECTSUBLOCKON001_H_
namespace MyStg2nd {

#define EffectSubLockon001_PROG_NOTHING  1
#define EffectSubLockon001_PROG_LOCK     2
#define EffectSubLockon001_PROG_RELEASE  3

/**
 * ÉçÉbÉNÉIÉì
 * @version 1.00
 * @since 2010/01/28
 * @author Masatoshi Tsuge
 */
class EffectSubLockon001 : public GgafDx9LibStg::DefaultSpriteSetActor {

public:
    //GgafDx9GeometricActor* _pTarget;
    //int _max_lock_num;
    //GgafCore::GgafLinkedListRing<GgafDx9Core::GgafDx9GeometricActor> _ringTarget;
//    EffectSubLockon001_Release* _pEffectLockon_Release;

    EffectSubLockon001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    void releaseLockon();

    void lockOn(GgafDx9GeometricActor* prm_pTarget);


    virtual ~EffectSubLockon001();
};

}
#endif /*EFFECTSUBLOCKON001_H_*/

