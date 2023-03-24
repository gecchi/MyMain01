#ifndef STAGE03_H_
#define STAGE03_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController/Stage.h"

namespace VioletVreath {

/**
 * ステージ03 .
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class Stage03 : public Stage {

public:
    Stage03(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~Stage03();
};

}
#endif /*STAGE03_H_*/
