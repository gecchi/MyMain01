#ifndef STAGE05_H_
#define STAGE05_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage.h"

namespace VioletVreath {

/**
 * ステージ04 .
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class Stage05 : public Stage {

public:
    Stage05(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~Stage05();
};

}
#endif /*STAGE05_H_*/
