#ifndef STAGE01PARTWALLSECTION001_H_
#define STAGE01PARTWALLSECTION001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/scene/WallSectionScene.h"

namespace VioletVreath {

/**
 * ステージデバッグの壁セクション(種別001) .
 * @version 1.00
 * @since 2018/09/18
 * @author Masatoshi Tsuge
 */
class Stage01PartWallSection001 : public GgafLib::WallSectionScene {

public:
    float bound_alpha_;

public:
    Stage01PartWallSection001(const char* prm_name,  GgafLib::WallScene* prm_pWallScene, const char* prm_data_filename);

    void processBehavior() override;

    void processPreDraw() override;

    virtual void onBlockLaunch(int prm_loop_count, int prm_wall_count, coord prm_wall_x) override;

    virtual ~Stage01PartWallSection001();
};

}
#endif /*STAGE01PARTWALLSECTION001_H_*/
