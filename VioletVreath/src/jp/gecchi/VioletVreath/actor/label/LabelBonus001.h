#ifndef LABELBONUS001_H_
#define LABELBONUS001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/FontBoardActor.h"

namespace VioletVreath {

/**
 * �ґ��S�Ŏ��̃{�[�i�X�|�C���g�\���p�t�H���g .
 * @version 1.00
 * @since 2023/08/04
 * @author Masatoshi Tsuge
 */
class LabelBonus001 : public GgafLib::FontBoardActor {

    GgafDx::GeometricActor* pOrgActor_;
public:
    LabelBonus001(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;
    /**
     * �f�|�W�g������擾���ꂽ���̃R�[���o�b�N .
     * LabelBonus001 �̊������J�n�T����ɂ͖{���\�b�h���Ăяo���Ă��������B
     * @param prm_pOrgActor
     */
    void onDispatched(GgafDx::GeometricActor* prm_pOrgActor);

    virtual ~LabelBonus001();

};

}
#endif /*LABELBONUS001_H_*/
