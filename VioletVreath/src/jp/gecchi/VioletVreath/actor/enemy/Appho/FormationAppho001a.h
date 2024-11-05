#ifndef FORMATIONAPPHO001A_H_
#define FORMATIONAPPHO001A_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Appho/FormationAppho001.h"

namespace VioletVreath {

/**
 * 敵機アッポー用フォーメーションその001-a .
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class FormationAppho001a : public FormationAppho001 {

public:
    FormationAppho001a(const char* prm_name);

    virtual void onSummonAppho(EnemyAppho* prm_pAppho, int prm_index) override;

    virtual ~FormationAppho001a();
};

}
#endif /*FORMATIONAPPHO001A_H_*/
