#ifndef EFFECTLOCKON001_H_
#define EFFECTLOCKON001_H_
namespace MyStg2nd {

#define EffectLockon001_PROG_LOCK     2
#define EffectLockon001_PROG_RELEASE  3

/**
 * ÉçÉbÉNÉIÉì
 * @version 1.00
 * @since 2010/01/28
 * @author Masatoshi Tsuge
 */
class EffectLockon001 : public GgafDx9LibStg::DefaultSpriteSetActor {

public:
    GgafDx9Core::GgafDx9GeometricActor* _pTarget;
    //int _max_lock_num;
    //GgafCore::GgafLinkedListRing<GgafDx9Core::GgafDx9GeometricActor> _ringTarget;
//    EffectLockon001_Release* _pEffectLockon001_Release;

    EffectLockon001(const char* prm_name, const char* prm_model_id);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    void releaseLockon();

    void lockon(GgafDx9GeometricActor* prm_pTarget);


    virtual ~EffectLockon001();
};

}
#endif /*EFFECTLOCKON001_H_*/

