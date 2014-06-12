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

public:
    EnemyDrastea(const char* prm_name);

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

