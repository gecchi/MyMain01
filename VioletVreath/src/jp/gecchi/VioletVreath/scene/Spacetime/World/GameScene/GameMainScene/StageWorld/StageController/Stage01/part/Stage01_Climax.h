#ifndef STAGE01_CLIMAX_H_
#define STAGE01_CLIMAX_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * ステージ１－最後 .
 * @version 1.00
 * @since 2010/08/23
 * @author Masatoshi Tsuge
 */
class Stage01_Climax : public GgafLib::DefaultScene {


public:
    bool waiting_;

    EnemyStraea* pBoss_;

public:
    Stage01_Climax(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~Stage01_Climax();
};

}
#endif /*STAGE01_CLIMAX_H_*/
