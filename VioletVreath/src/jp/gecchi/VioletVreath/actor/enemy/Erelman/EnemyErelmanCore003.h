#ifndef ENEMYERELMANCORE003_H_
#define ENEMYERELMANCORE003_H_
#include "VioletVreath.h"
#include "EnemyErelmanCore.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * �G�����}���̃R�A .
 * @version 1.00
 * @since 2018/06/11
 * @author Masatoshi Tsuge
 */
class EnemyErelmanCore003 : public EnemyErelmanCore {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyErelmanCore003(const char* prm_name, EnemyErelmanController* prm_pController);


    /**
     * �G�����}���̐U�镑�� .
     */
    void processBehavior() override;


    virtual ~EnemyErelmanCore003();
};

}
#endif /*ENEMYERELMANCORE003_H_*/

