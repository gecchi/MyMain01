#ifndef EFFECTLOCKON001_RELEASE_H_
#define EFFECTLOCKON001_RELEASE_H_
namespace MyStg2nd {

/**
 * ロックオン解放エフェクト
 * @version 1.00
 * @since 2010/02/22
 * @author Masatoshi Tsuge
 */
class EffectLockOn001_Release : public GgafDx9LibStg::DefaultSpriteSetActor {

    EffectLockOn001* _pEffectLockOn001;

public:
    EffectLockOn001_Release(const char* prm_name, EffectLockOn001* prm_pEffectLockOn001);

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

    virtual ~EffectLockOn001_Release();
};

}
#endif /*EFFECTLOCKON001_Release_H_*/

