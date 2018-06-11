#ifndef ENEMYERELMANCONTROLLER001_H_
#define ENEMYERELMANCONTROLLER001_H_
#include "VioletVreath.h"
#include "EnemyErelmanController.h"

namespace VioletVreath {

/**
 * �G�r�E�X�̃R�A�ƁA�G�r�E�X�ґ����Ǘ����̂P .
 * �V�[���ɒǉ�����A�N�^�[�͂��̃A�N�^�[�ł��B
 * @version 1.00
 * @since 2015/01/21
 * @author Masatoshi Tsuge
 */
class EnemyErelmanController001 : public EnemyErelmanController {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyErelmanController001(const char* prm_name);

    virtual ~EnemyErelmanController001();
};

}
#endif /*ENEMYERELMANCONTROLLER001_H_*/

