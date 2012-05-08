#ifndef EFFECTVREATHMAGIC001_H_
#define EFFECTVREATHMAGIC001_H_
namespace VioletVreath {

/**
 * �X�s�[�h�A�b�v�̃G�t�F�N�g .
 * @version 1.00
 * @since 2012/05/08
 * @author Masatoshi Tsuge
 */
class EffectVreathMagic001 : public GgafLib::DefaultSpriteActor {

public:
    EffectVreathMagic001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectVreathMagic001();
};

}
#endif /*EFFECTVREATHMAGIC001_H_*/

