#ifndef FORMATIONALLAS001B_H_
#define FORMATIONALLAS001B_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Allas/FormationAllas001.h"

namespace VioletVreath {

/**
 * 敵機アラス用フォーメーションその001-b .
 * @version 1.00
 * @since 2010/06/27
 * @author Masatoshi Tsuge
 */
class FormationAllas001b : public FormationAllas001 {

public:
    FormationAllas001b(const char* prm_name);

    virtual void onCalledUpAllas(EnemyAllas* prm_pAllas) override;

    virtual ~FormationAllas001b();
};

}
#endif /*FORMATIONALLAS001B_H_*/
