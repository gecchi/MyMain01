#ifndef FORMATIONAIDA001_H_
#define FORMATIONAIDA001_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Aida/FormationAida.h"

namespace VioletVreath {

/**
 * 敵機ヘーベ用フォーメーション001グループ .
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class FormationAida001 : public FormationAida {

public:

    FormationAida001(const char* prm_name);

    void onCallUpAida(EnemyAida* pEnemyAida) override;

    virtual void processBehavior() override;

    virtual ~FormationAida001();
};

}
#endif /*FORMATIONAIDA001_H_*/
