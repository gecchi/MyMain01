#ifndef VVWORLD_H_
#define VVWORLD_H_
#include "VioletVrain.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/gecchi/VioletVrain/scene/VvSpacetime.h"
#include "jp/ggaf/core/util/lineartree/LinearTreeRounder.hpp"
#include "jp/ggaf/lib/util/Quantity.hpp"
#include "jp/ggaf/lib/util/VirtualButton.h"

namespace VioletVrain {

/**
 * 世界シーン .
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class World : public GgafLib::DefaultScene {

public:
    /** 入力受付 */
    GgafLib::VirtualButton vb_;

    TrialAndErrScene* pTrialAndErrScene_;

    GgafLib::QuadtreeRounder* pHitCheckRounder_;
    /**
     * コンストラクタ .
     * @param prm_name 名称
     */
    World(const char* prm_name);

    /**
     * 世界シーンの初期処理 .
     */
    void initialize() override;

    /**
     * 世界シーンの振る舞い処理 .
     */
    void processBehavior() override;

    void processJudgement() override;

    virtual ~World();
};

}

#endif /*VVWORLD_H_*/
