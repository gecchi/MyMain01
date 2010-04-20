#ifndef EFFECTLOCKON001_H_
#define EFFECTLOCKON001_H_
namespace MyStg2nd {

/**
 * ÉçÉbÉNÉIÉì
 * @version 1.00
 * @since 2010/01/28
 * @author Masatoshi Tsuge
 */
class EffectLockOn001 : public GgafDx9LibStg::DefaultSpriteSetActor {

public:
    EffectLockOn001(const char* prm_name);

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void initialize() override;

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processBehavior() override;

    void onActive() override;

    void onInactive() override;
    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processJudgement() override;

    virtual ~EffectLockOn001();
};

}
#endif /*EFFECTLOCKON001_H_*/

