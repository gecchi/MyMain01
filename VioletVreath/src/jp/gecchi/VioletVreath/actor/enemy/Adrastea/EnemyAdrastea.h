#ifndef ENEMYADRASTEA_H_
#define ENEMYADRASTEA_H_
#include "jp/ggaf/lib/actor/CubeMapMeshSetActor.h"

namespace VioletVreath {

/**
 * �G�@�A�h���X�e�A .
 * ����]�����R�ɂł���o�L�����`�E�E�E
 * @version 1.00
 * @since 2012/08/06
 * @author Masatoshi Tsuge
 */
class EnemyAdrastea : public GgafLib::CubeMapMeshSetActor {

public:
    enum {
        PROG_MOVE01_1   ,
        PROG_SPLINE_MOVE,
        PROG_MOVE02_1   ,
        PROG_MOVE02_2   ,
    };

    enum {
        SE_DAMAGED   ,
        SE_EXPLOSION ,
    };

    coord colli_box_dX_;
    coord colli_box_dY_;
    coord colli_box_dZ_;
    int box_num_X_;
    int box_num_Y_;
    int box_num_Z_;

public:
    EnemyAdrastea(const char* prm_name);

    void config(coord prm_colli_box_dx,
                coord prm_colli_box_dY,
                coord prm_colli_box_dZ,
                int prm_box_num_X,
                int prm_box_num_Y,
                int prm_box_num_Z );

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyAdrastea();
};

}
#endif /*ENEMYADRASTEA_H_*/

