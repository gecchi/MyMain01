#ifndef ENEMYOEBIUSCONTROLLER002_H_
#define ENEMYOEBIUSCONTROLLER002_H_
#include "VioletVreath.h"
#include "EnemyOebiusController.h"

namespace VioletVreath {

/**
 * �G�r�E�X�̃R�A�ƁA�G�r�E�X�ґ����Ǘ����̂Q .
 * �V�[���ɒǉ�����A�N�^�[�͂��̃A�N�^�[�ł��B
 * @version 1.00
 * @since 2015/01/21
 * @author Masatoshi Tsuge
 */
class EnemyOebiusController002 : public EnemyOebiusController {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyOebiusController002(const char* prm_name);

    virtual ~EnemyOebiusController002();
};

}
#endif /*ENEMYOEBIUSCONTROLLER002_H_*/

