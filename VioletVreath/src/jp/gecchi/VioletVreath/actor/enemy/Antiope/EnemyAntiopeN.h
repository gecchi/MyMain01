#ifndef ENEMYANTIOPEN_H_
#define ENEMYANTIOPEN_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Antiope/EnemyAntiope.h"

namespace VioletVreath {

/**
 * �G�@�A���e�B�I�y(�l�K) .
 * @version 1.00
 * @since 2013/04/08
 * @author Masatoshi Tsuge
 */
class EnemyAntiopeN : public EnemyAntiope {

public:

    EnemyAntiopeN(const char* prm_name);

    virtual ~EnemyAntiopeN();
};

}
#endif /*ENEMYANTIOPEN_H_*/

