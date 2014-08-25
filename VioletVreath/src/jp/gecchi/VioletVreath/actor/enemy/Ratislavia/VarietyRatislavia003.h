#ifndef VARIETYRATISLAVIA003_H_
#define VARIETYRATISLAVIA003_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislavia.h"

namespace VioletVreath {

/**
 * �n�`�g�[���X�̃o���G�[�V����003 .
 * @version 1.00
 * @since 2010/05/26
 * @author Masatoshi Tsuge
 */
class VarietyRatislavia003 : public EnemyRatislavia {

public:
    VarietyRatislavia003(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    virtual ~VarietyRatislavia003();
};

}
#endif /*VARIETYRATISLAVIA003_H_*/

