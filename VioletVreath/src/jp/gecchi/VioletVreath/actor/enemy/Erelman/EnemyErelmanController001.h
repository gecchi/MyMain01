#ifndef ENEMYERELMANCONTROLLER001_H_
#define ENEMYERELMANCONTROLLER001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "EnemyErelmanController.h"

namespace VioletVreath {

/**
 * �G�����}���̃R�A�ƁA�G�����}���ґ����Ǘ����̂P .
 * �V�[���ɒǉ�����A�N�^�[�͂��̃A�N�^�[�ł��B
 * @version 1.00
 * @since 2018/06/11
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

