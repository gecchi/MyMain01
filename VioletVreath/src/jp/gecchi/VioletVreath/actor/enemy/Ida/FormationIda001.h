#ifndef FORMATIONIDA001_H_
#define FORMATIONIDA001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ida/FormationIda.h"

namespace VioletVreath {

/**
 * 敵機イーダ用フォーメーション001 .
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class FormationIda001 : public FormationIda {

public:
    FormationIda001(const char* prm_name);

    void onSummonIda(EnemyIda* pEnemyIda) override;

    virtual void processBehavior() override;

    virtual ~FormationIda001();
};

}
#endif /*FORMATIONIDA001_H_*/
