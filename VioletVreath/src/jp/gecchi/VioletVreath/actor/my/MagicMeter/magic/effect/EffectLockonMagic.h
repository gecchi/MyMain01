#ifndef EFFECTLOCKONMAGIC_H_
#define EFFECTLOCKONMAGIC_H_
namespace VioletVreath {

/**
 * ���b�N�I�����@�������̃G�t�F�N�g .
 * @version 1.00
 * @since 2012/07/30
 * @author Masatoshi Tsuge
 */
class EffectLockonMagic : public GgafLib::DefaultSpriteActor {

public:
    EffectLockonMagic(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectLockonMagic();
};

}
#endif /*EFFECTLOCKONMAGIC_H_*/
