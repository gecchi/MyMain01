#ifndef EFFECTLOCKON001_SUB_H_
#define EFFECTLOCKON001_SUB_H_
namespace MyStg2nd {

/**
 * ÉçÉbÉNÉIÉì
 * @version 1.00
 * @since 2010/01/28
 * @author Masatoshi Tsuge
 */
class EffectLockon001_Sub : public EffectLockon001 {

public:

    EffectLockon001_Main* _pEffectLockon001_Main;

    EffectLockon001_Sub(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    void releaseLockon() override;

    void lockon(GgafDx9GeometricActor* prm_pTarget)  override;

    virtual ~EffectLockon001_Sub();
};

}
#endif /*EFFECTLOCKON001_SUB_H_*/

