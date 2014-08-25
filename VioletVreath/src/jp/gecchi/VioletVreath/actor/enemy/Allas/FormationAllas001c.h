#ifndef FORMATIONALLAS001C_H_
#define FORMATIONALLAS001C_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Allas/FormationAllas001.h"

namespace VioletVreath {

/**
 * �G�@���X�p�t�H�[���[�V��������1-a .
 * @version 1.00
 * @since 2010/06/27
 * @author Masatoshi Tsuge
 */
class FormationAllas001c : public FormationAllas001 {

public:
    FormationAllas001c(const char* prm_name);

    virtual void onCallUpAllas(EnemyAllas* prm_pAllas) override;

    virtual ~FormationAllas001c();
};

}
#endif /*FORMATIONALLAS001C_H_*/
