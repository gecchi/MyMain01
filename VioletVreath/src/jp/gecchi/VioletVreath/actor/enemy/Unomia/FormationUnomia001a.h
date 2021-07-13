#ifndef FORMATIONUNOMIA001A_H_
#define FORMATIONUNOMIA001A_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Unomia/FormationUnomia001.h"

namespace VioletVreath {

/**
 * �G�@�E�[�m�~�A�p�t�H�[���[�V��������001-a .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationUnomia001a : public FormationUnomia001 {

public:
    FormationUnomia001a(const char* prm_name);

    /**
     * ���� .
     */
    void onCalledUpUnomia(EnemyUnomia* pEnemyUnomia, int col) override;

    virtual ~FormationUnomia001a();
};

}
#endif /*FORMATIONUNOMIA001A_H_*/
