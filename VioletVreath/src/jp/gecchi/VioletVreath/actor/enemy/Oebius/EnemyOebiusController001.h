#ifndef ENEMYOEBIUSCONTROLLER001_H_
#define ENEMYOEBIUSCONTROLLER001_H_
#include "VioletVreath.h"
#include "EnemyOebiusController.h"

namespace VioletVreath {

/**
 * �G�r�E�X�̃R�A�ƁA�G�r�E�X�ґ����Ǘ����̂P .
 * �V�[���ɒǉ�����A�N�^�[�͂��̃A�N�^�[�ł��B
 * @version 1.00
 * @since 2015/01/21
 * @author Masatoshi Tsuge
 */
class EnemyOebiusController001 : public EnemyOebiusController {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyOebiusController001(const char* prm_name);

    virtual ~EnemyOebiusController001();
};

}
#endif /*ENEMYOEBIUSCONTROLLER001_H_*/

