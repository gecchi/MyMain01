#ifndef FORMATIONALLAS001D_H_
#define FORMATIONALLAS001D_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Allas/FormationAllas001.h"

namespace VioletVreath {

/**
 * 敵機アラス用フォーメーションその001-d .
 * @version 1.00
 * @since 2010/06/27
 * @author Masatoshi Tsuge
 */
class FormationAllas001d : public FormationAllas001 {

public:
    FormationAllas001d(const char* prm_name);

    virtual void onCalledUpAllas(EnemyAllas* prm_pAllas) override;

    virtual ~FormationAllas001d();
};

}
#endif /*FORMATIONALLAS001D_H_*/
