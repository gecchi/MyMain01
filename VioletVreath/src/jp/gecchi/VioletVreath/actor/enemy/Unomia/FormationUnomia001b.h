#ifndef FORMATIONUNOMIA001B_H_
#define FORMATIONUNOMIA001B_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Unomia/FormationUnomia001.h"

namespace VioletVreath {

/**
 * �G�@�E�[�m�~�A�p�t�H�[���[�V��������001-b .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationUnomia001b : public FormationUnomia001 {

public:
    FormationUnomia001b(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    void onCallUpUnomia(EnemyUnomia* pEnemyUnomia, int col) override;

    virtual ~FormationUnomia001b();
};

}
#endif /*FORMATIONUNOMIA001B_H_*/
