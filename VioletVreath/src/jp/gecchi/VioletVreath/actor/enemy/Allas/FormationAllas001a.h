#ifndef FORMATIONALLAS001A_H_
#define FORMATIONALLAS001A_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Allas/FormationAllas001.h"

namespace VioletVreath {

/**
 * 敵機アラス用フォーメーションその001-a .
 * @version 1.00
 * @since 2010/06/27
 * @author Masatoshi Tsuge
 */
class FormationAllas001a : public FormationAllas001 {

public:
    FormationAllas001a(const char* prm_name);

    virtual void onSummonAllas(EnemyAllas* prm_pAllas) override;

    virtual ~FormationAllas001a();
};

}
#endif /*FORMATIONALLAS001A_H_*/
