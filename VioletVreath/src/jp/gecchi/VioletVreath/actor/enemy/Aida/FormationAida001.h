#ifndef FORMATIONHEBE001_H_
#define FORMATIONHEBE001_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Aida/FormationAida.h"

namespace VioletVreath {

/**
 * �G�@�w�[�x�p�t�H�[���[�V����001�O���[�v .
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class FormationAida001 : public FormationAida {
    /** �X�v���C����`�����ւ̐ڑ� */
    GgafLib::SplineManufactureConnection* pSplManufConnection_;
public:

    FormationAida001(const char* prm_name);

    void onCallUpAida(EnemyAida* pEnemyAida) override;

    virtual void processBehavior() override;

    GgafLib::SplineManufacture* getSplManuf() override;

    virtual ~FormationAida001();
};

}
#endif /*FORMATIONEUNOMIA001_H_*/
