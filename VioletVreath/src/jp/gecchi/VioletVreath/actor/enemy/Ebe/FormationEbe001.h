#ifndef FORMATIONEBE001_H_
#define FORMATIONEBE001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ebe/FormationEbe.h"

namespace VioletVreath {

/**
 * �G�@�G�[�x�p�t�H�[���[�V����001�O���[�v .
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class FormationEbe001 : public FormationEbe {
    /** �Ȑ��ړ��̏�񎑌��ւ̐ڑ� */
    GgafDx::CurveManufactureConnection* pConn_pCurveManuf_;
public:

    FormationEbe001(const char* prm_name);

    void onCalledUpEbe(EnemyEbe* pEnemyEbe) override;

    virtual void processBehavior() override;

    GgafDx::CurveManufacture* getSplManuf() override;

    virtual ~FormationEbe001();
};

}
#endif /*FORMATIONUNOMIA001_H_*/
