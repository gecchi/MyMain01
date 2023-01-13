#ifndef VARIETYRATISLAVIA001_H_
#define VARIETYRATISLAVIA001_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislavia.h"

namespace VioletVreath {

/**
 * 地形トーラスのバリエーション001 .
 * @version 1.00
 * @since 2010/05/23
 * @author Masatoshi Tsuge
 */
class VarietyRatislavia001 : public EnemyRatislavia {

public:
    EnemyRatislaviaEye* pEnemyRatislaviaEye_;

public:
    VarietyRatislavia001(const char* prm_name);

    void initialize() override;
    void processBehavior() override;
    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;

    virtual ~VarietyRatislavia001();
};

}
#endif /*VARIETYRATISLAVIA001_H_*/

