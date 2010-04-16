#ifndef EFFECTLOCKON001_H_
#define EFFECTLOCKON001_H_
namespace MyStg2nd {

/**
 * ロックオン
 * @version 1.00
 * @since 2010/01/28
 * @author Masatoshi Tsuge
 */
class EffectLockOn001 : public GgafDx9LibStg::DefaultSpriteSetActor {

public:
    EffectLockOn001(const char* prm_name);

    /**
     * ＜OverRide です＞
     */
    void initialize() override;

    /**
     * ＜OverRide です＞
     */
    void processBehavior() override;

    void onActive() override;

    void onInactive() override;
    /**
     * ＜OverRide です＞
     */
    void processJudgement() override;

    virtual ~EffectLockOn001();
};

}
#endif /*EFFECTLOCKON001_H_*/

