#ifndef FORMATIONAIDA001_H_
#define FORMATIONAIDA001_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Aida/FormationAida.h"

namespace VioletVreath {

/**
 * 敵機アイーダ用フォーメーション001 .
 * @version 1.00
 * @since 2013/06/18
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
