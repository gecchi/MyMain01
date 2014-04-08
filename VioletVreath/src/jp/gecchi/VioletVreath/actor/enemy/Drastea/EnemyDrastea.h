#ifndef ENEMYDRASTEA_H_
#define ENEMYDRASTEA_H_
#include "jp/ggaf/lib/actor/CubeMapMeshSetActor.h"

namespace VioletVreath {

/**
 * 敵機ドラステア .
 * 横回転も自由にできるバキュラ～・・・
 * @version 1.00
 * @since 2012/08/06
 * @author Masatoshi Tsuge
 */
class EnemyDrastea : public GgafLib::CubeMapMeshSetActor {

public:
    enum {
        PROG_MOVE01_1   ,
        PROG_SPLINE_MOVE,
        PROG_MOVE02_1   ,
        PROG_MOVE02_2   ,
        PROG_BANPEI,
    };

    enum {
        SE_DAMAGED   ,
        SE_EXPLOSION ,
    };
    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    coord colli_box_dx_;
    coord colli_box_dy_;
    coord colli_box_dz_;
    int box_num_x_;
    int box_num_y_;
    int box_num_z_;

public:
    EnemyDrastea(const char* prm_name);

    void config(coord prm_colli_box_dx,
                coord prm_colli_box_dy,
                coord prm_colli_box_dz,
                int prm_box_num_x,
                int prm_box_num_y,
                int prm_box_num_z );

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyDrastea();
};

}
#endif /*ENEMYDRASTEA_H_*/

