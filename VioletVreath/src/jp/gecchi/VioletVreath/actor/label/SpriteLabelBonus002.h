#ifndef SPRITELABELBONUS002_H_
#define SPRITELABELBONUS002_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/FontSpriteActor.h"

namespace VioletVreath {

/**
 * �ґ��S�Ŏ��̃{�[�i�X�|�C���g�\���p�t�H���g .
 * @version 1.00
 * @since 2023/08/15
 * @author Masatoshi Tsuge
 */
class SpriteLabelBonus002 : public GgafLib::FontSpriteActor {

public:
    SpriteLabelBonus002(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;
    /**
     * �f�|�W�g������擾���ꂽ���̃R�[���o�b�N .
     * SpriteLabelBonus002 �̊������J�n�T����ɂ͖{���\�b�h���Ăяo���Ă��������B
     * @param prm_pOrgActor
     */
    void onDispatched(GgafDx::GeometricActor* prm_pOrgActor);

    virtual ~SpriteLabelBonus002();

};

}
#endif /*SPRITELABELBONUS002_H_*/
