#ifndef FORMATIONEUNOMIA002B_H_
#define FORMATIONEUNOMIA002B_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/FormationEunomia002.h"

namespace VioletVreath {

/**
 * �G�@�G�E�m�~�A�p�t�H�[���[�V��������002-b .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia002b : public FormationEunomia002 {

public:
    FormationEunomia002b(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    void onCallUpEunomia(EnemyEunomia* pEnemyEunomia, int col) override;

    virtual ~FormationEunomia002b();
};

}
#endif /*FORMATIONEUNOMIA002B_H_*/
