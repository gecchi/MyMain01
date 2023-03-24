#ifndef STAGEDEBUGPARTCLIMAX_H_
#define STAGEDEBUGPARTCLIMAX_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "StageDebugPart.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * ステージデバッグ－最後 .
 * @version 1.00
 * @since 2018/09/18
 * @author Masatoshi Tsuge
 */
class StageDebugPartClimax : public StageDebugPart<GgafLib::DefaultScene> {


public:
    bool waiting_;

    EnemyStraea* pBoss_;

public:
    StageDebugPartClimax(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~StageDebugPartClimax();
};

}
#endif /*STAGEDEBUGPARTCLIMAX_H_*/
