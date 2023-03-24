#ifndef STAGEDEBUGPARTWALLSECTION001_H_
#define STAGEDEBUGPARTWALLSECTION001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/WallSectionScene.h"

namespace VioletVreath {

/**
 * ステージデバッグの壁セクション(種別001) .
 * @version 1.00
 * @since 2018/09/18
 * @author Masatoshi Tsuge
 */
class StageDebugPartWallSection001 : public GgafLib::WallSectionScene {

public:
    float bound_alpha_;

public:
    StageDebugPartWallSection001(const char* prm_name,  GgafLib::WallScene* prm_pWallScene, const char* prm_data_filename);

    void processBehavior() override;

    void processPreDraw() override;

    virtual void onBlockLaunch(int prm_loop_count, int prm_wall_count, coord prm_wall_x) override;

    virtual ~StageDebugPartWallSection001();
};

}
#endif /*STAGEDEBUGPARTWALLSECTION001_H_*/
