#ifndef ENEMYANTIOPEP_H_
#define ENEMYANTIOPEP_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Antiope/EnemyAntiope.h"

namespace VioletVreath {

/**
 * 敵機アンティオペ(ポジ) .
 * @version 1.00
 * @since 2013/04/08
 * @author Masatoshi Tsuge
 */
class EnemyAntiopeP : public EnemyAntiope {

public:
    EnemyAntiopeP(const char* prm_name);

    virtual ~EnemyAntiopeP();
};

}
#endif /*ENEMYANTIOPEP_H_*/

