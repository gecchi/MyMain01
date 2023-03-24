#ifndef STAGEDEBUGPARTWALLSCENE_H_
#define STAGEDEBUGPARTWALLSCENE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "StageDebugPart.hpp"
#include "jp/ggaf/lib/scene/WallScene.h"

namespace VioletVreath {

/**
 * ステージデバッグの壁 .
 * @version 1.00
 * @since 2018/09/18
 * @author Masatoshi Tsuge
 */
class StageDebugPartWall : public StageDebugPart<GgafLib::WallScene> {

public:
    StageDebugPartWall(const char* prm_name);

    /**
     * 初期処理
     */
    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void onFinishedAllSection() override;

    virtual ~StageDebugPartWall();
};

}
#endif /*STAGEDEBUGPARTWALLSCENE_H_*/
