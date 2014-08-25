#ifndef VARIETYRATISLAVIA004_H_
#define VARIETYRATISLAVIA004_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislavia.h"

namespace VioletVreath {

/**
 * �n�`�g�[���X�̃o���G�[�V����004 .
 * @version 1.00
 * @since 2010/05/26
 * @author Masatoshi Tsuge
 */
class VarietyRatislavia004 : public EnemyRatislavia {

public:
    VarietyRatislavia004(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    virtual ~VarietyRatislavia004();
};

}
#endif /*VARIETYRATISLAVIA004_H_*/

