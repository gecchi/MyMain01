#ifndef EFFECTLOCKON001_H_
#define EFFECTLOCKON001_H_
namespace MyStg2nd {

#define EffectLockon001_PROG_NOTHING  1
#define EffectLockon001_PROG_LOCK     2
#define EffectLockon001_PROG_RELEASE  3

/**
 * ロックオン
 * @version 1.00
 * @since 2010/01/28
 * @author Masatoshi Tsuge
 */
class EffectLockon001 : public GgafDx9LibStg::DefaultSpriteSetActor {

public:
    //GgafDx9GeometricActor* _pTarget;
    //int _max_lock_num;
    //GgafCore::GgafLinkedListRing<GgafDx9Core::GgafDx9GeometricActor> _ringTarget;
//    EffectLockon001_Release* _pEffectLockon_Release;

    EffectLockon001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    void releaseLockon();

    void lockOn(GgafDx9GeometricActor* prm_pTarget);


    virtual ~EffectLockon001();
};

}
#endif /*EFFECTLOCKON001_H_*/

