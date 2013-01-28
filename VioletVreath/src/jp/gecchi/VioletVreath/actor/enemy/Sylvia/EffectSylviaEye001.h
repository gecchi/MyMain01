#ifndef EFFECTSYLVIAEYE001_H_
#define EFFECTSYLVIAEYE001_H_
namespace VioletVreath {

/**
 * �g�[���X�ڋʃ��[�U�[���ˑO�`���[�W�G�t�F�N�g
 * @version 1.00
 * @since 2012/10/19
 * @author Masatoshi Tsuge
 */
class EffectSylviaEye001 : public GgafLib::DefaultSpriteActor {

public:
    int cnt_;

public:
    EffectSylviaEye001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectSylviaEye001();
};

}
#endif /*EFFECTSYLVIAEYE001_H_*/

