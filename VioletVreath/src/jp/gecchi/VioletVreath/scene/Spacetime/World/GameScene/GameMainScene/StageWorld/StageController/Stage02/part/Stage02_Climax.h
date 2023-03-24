#ifndef STAGE02_CLIMAX_H_
#define STAGE02_CLIMAX_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * ステージ１－最後 .
 * @version 1.00
 * @since 2010/08/23
 * @author Masatoshi Tsuge
 */
class Stage02_Climax : public VvScene<GgafLib::DefaultScene> {

public:
    bool waiting_;

    EnemyStraea* pBoss_;

public:
    Stage02_Climax(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~Stage02_Climax();
};

}
#endif /*STAGE02_CLIMAX_H_*/
