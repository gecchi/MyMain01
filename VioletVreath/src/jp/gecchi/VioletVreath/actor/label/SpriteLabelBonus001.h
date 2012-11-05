#ifndef SPRITELABELBONUS001_H_
#define SPRITELABELBONUS001_H_
namespace VioletVreath {

/**
 * �ґ��S�Ŏ��̃{�[�i�X�|�C���g�\���p�t�H���g .
 * @version 1.00
 * @since 2012/11/02
 * @author Masatoshi Tsuge
 */
class SpriteLabelBonus001 : public GgafLib::StringSpriteActor {

public:
    SpriteLabelBonus001(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual ~SpriteLabelBonus001();

};

}
#endif /*SPRITELABELBONUS001_H_*/
