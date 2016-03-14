#ifndef STAGE01WALLSECTION001_H_
#define STAGE01WALLSECTION001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/WallSectionScene.h"

namespace VioletVreath {

/**
 * ステージ01の壁セクション(種別001) .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class Stage01WallSection001 : public GgafLib::WallSectionScene {

public:
    float bound_alpha_;

public:
    Stage01WallSection001(const char* prm_name,  GgafLib::WallScene* prm_pWallScene, const char* prm_data_filename);

    void processBehavior() override;

    virtual void onBlockLaunch(int prm_loop_count, int prm_wall_count, coord prm_wall_x) override;

    virtual ~Stage01WallSection001();
};

}
#endif /*STAGE01WALLSECTION001_H_*/
