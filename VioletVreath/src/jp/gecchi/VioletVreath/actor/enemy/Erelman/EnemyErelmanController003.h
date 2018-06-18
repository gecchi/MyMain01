#ifndef ENEMYERELMANCONTROLLER003_H_
#define ENEMYERELMANCONTROLLER003_H_
#include "VioletVreath.h"
#include "EnemyErelmanController.h"

namespace VioletVreath {

/**
 * �G�����}���̃R�A�ƁA�G�����}���ґ����Ǘ����̂P .
 * �V�[���ɒǉ�����A�N�^�[�͂��̃A�N�^�[�ł��B
 * @version 1.00
 * @since 2018/06/11
 * @author Masatoshi Tsuge
 */
class EnemyErelmanController003 : public EnemyErelmanController {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyErelmanController003(const char* prm_name);

    virtual void onCoreHit() override;

    virtual ~EnemyErelmanController003();
};

}
#endif /*ENEMYERELMANCONTROLLER003_H_*/

