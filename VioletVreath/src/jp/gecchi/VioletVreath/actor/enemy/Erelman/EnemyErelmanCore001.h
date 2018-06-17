#ifndef ENEMYERELMANCORE001_H_
#define ENEMYERELMANCORE001_H_
#include "VioletVreath.h"
#include "EnemyErelmanCore.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * �G�����}���̃R�A .
 * @version 1.00
 * @since 2018/06/11
 * @author Masatoshi Tsuge
 */
class EnemyErelmanCore001 : public EnemyErelmanCore {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyErelmanCore001(const char* prm_name, EnemyErelmanController* prm_pController);


    /**
     * �G�����}���̐U�镑�� .
     */
    void processBehavior() override;


    virtual ~EnemyErelmanCore001();
};

}
#endif /*ENEMYERELMANCORE001_H_*/

