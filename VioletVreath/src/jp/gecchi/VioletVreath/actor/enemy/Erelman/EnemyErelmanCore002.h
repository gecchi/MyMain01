#ifndef ENEMYERELMANCORE002_H_
#define ENEMYERELMANCORE002_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "EnemyErelmanCore.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * �G�����}���̃R�A .
 * @version 1.00
 * @since 2018/06/11
 * @author Masatoshi Tsuge
 */
class EnemyErelmanCore002 : public EnemyErelmanCore {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyErelmanCore002(const char* prm_name, EnemyErelmanController* prm_pController);


    /**
     * �G�����}���̐U�镑�� .
     */
    void processBehavior() override;


    virtual ~EnemyErelmanCore002();
};

}
#endif /*ENEMYERELMANCORE002_H_*/

