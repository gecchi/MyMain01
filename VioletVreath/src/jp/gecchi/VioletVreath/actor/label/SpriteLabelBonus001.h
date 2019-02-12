#ifndef SPRITELABELBONUS001_H_
#define SPRITELABELBONUS001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/FontSpriteActor.h"

namespace VioletVreath {

/**
 * �ґ��S�Ŏ��̃{�[�i�X�|�C���g�\���p�t�H���g .
 * @version 1.00
 * @since 2012/11/02
 * @author Masatoshi Tsuge
 */
class SpriteLabelBonus001 : public GgafLib::FontSpriteActor {

public:
    SpriteLabelBonus001(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;
    /**
     * �f�|�W�g������擾���ꂽ���̃R�[���o�b�N .
     * SpriteLabelBonus001 �̊������J�n�T����ɂ͖{���\�b�h���Ăяo���Ă��������B
     * @param prm_pOrgActor
     */
    void onDispatched(GgafDx::GeometricActor* prm_pOrgActor);

    virtual ~SpriteLabelBonus001();

};

}
#endif /*SPRITELABELBONUS001_H_*/
