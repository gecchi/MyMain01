#ifndef VARIETYRATISLAVIA002_H_
#define VARIETYRATISLAVIA002_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislavia.h"

namespace VioletVreath {

/**
 * �n�`�g�[���X�̃o���G�[�V����002 .
 * @version 1.00
 * @since 2010/05/26
 * @author Masatoshi Tsuge
 */
class VarietyRatislavia002 : public EnemyRatislavia {

public:
    VarietyRatislavia002(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    virtual ~VarietyRatislavia002();
};

}
#endif /*VARIETYRATISLAVIA002_H_*/

