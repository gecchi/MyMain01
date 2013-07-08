#ifndef FORMATIONUNOMIA002B_H_
#define FORMATIONUNOMIA002B_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Unomia/FormationUnomia002.h"

namespace VioletVreath {

/**
 * �G�@�E�[�m�~�A�p�t�H�[���[�V��������002-b .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationUnomia002b : public FormationUnomia002 {

public:
    FormationUnomia002b(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    void onCallUpUnomia(EnemyUnomia* pEnemyUnomia, int col) override;

    virtual ~FormationUnomia002b();
};

}
#endif /*FORMATIONUNOMIA002B_H_*/
