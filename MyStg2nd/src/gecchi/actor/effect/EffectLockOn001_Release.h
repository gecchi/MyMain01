#ifndef EFFECTLOCKON001_RELEASE_H_
#define EFFECTLOCKON001_RELEASE_H_
namespace MyStg2nd {

/**
 * ���b�N�I������G�t�F�N�g
 * @version 1.00
 * @since 2010/02/22
 * @author Masatoshi Tsuge
 */
class EffectLockon001_Release : public GgafDx9LibStg::DefaultSpriteSetActor {

    EffectLockon001* _pEffectLockon001;

public:
    EffectLockon001_Release(const char* prm_name, EffectLockon001* prm_pEffectLockon001);

    /**
     * ��OverRide �ł���
     */
    void initialize() override;

    /**
     * ��OverRide �ł���
     */
    void processBehavior() override;

    void onActive() override;

    void onInactive() override;
    /**
     * ��OverRide �ł���
     */
    void processJudgement() override;

    virtual ~EffectLockon001_Release();
};

}
#endif /*EFFECTLOCKON001_Release_H_*/

