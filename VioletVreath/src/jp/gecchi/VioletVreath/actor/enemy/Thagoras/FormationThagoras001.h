#ifndef FORMATIONTHAGORAS001_H_
#define FORMATIONTHAGORAS001_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/FormationThagoras.h"

namespace VioletVreath {

/**
 * 敵機タゴラス用フォーメーションその001 .
 * @version 1.00
 * @since 2013/07/10
 * @author Masatoshi Tsuge
 */
class FormationThagoras001 : public FormationThagoras {

public:
    FormationThagoras001(const char* prm_name);

    virtual void onCallUpThagoras(EnemyThagoras* prm_pThagoras, int prm_index) override;

    virtual ~FormationThagoras001();
};

}
#endif /*FORMATIONTHAGORAS001_H_*/
