#ifndef FORMATIONAPPHO001B_H_
#define FORMATIONAPPHO001B_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Appho/FormationAppho001.h"

namespace VioletVreath {

/**
 * 敵機アッポー用フォーメーションその001-b .
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class FormationAppho001b : public FormationAppho001 {

public:
    FormationAppho001b(const char* prm_name);

    virtual void onSummonAppho(EnemyAppho* prm_pAppho, int prm_index) override;

    virtual ~FormationAppho001b();
};

}
#endif /*FORMATIONAPPHO001B_H_*/
