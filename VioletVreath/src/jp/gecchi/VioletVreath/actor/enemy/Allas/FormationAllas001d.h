#ifndef FORMATIONALLAS001D_H_
#define FORMATIONALLAS001D_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Allas/FormationAllas001.h"

namespace VioletVreath {

/**
 * �G�@�A���X�p�t�H�[���[�V��������001-d .
 * @version 1.00
 * @since 2010/06/27
 * @author Masatoshi Tsuge
 */
class FormationAllas001d : public FormationAllas001 {

public:
    FormationAllas001d(const char* prm_name);

    virtual void onCallUpAllas(EnemyAllas* prm_pAllas) override;

    virtual ~FormationAllas001d();
};

}
#endif /*FORMATIONALLAS001D_H_*/
