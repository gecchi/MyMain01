#ifndef ENEMYADRASTEA_H_
#define ENEMYADRASTEA_H_
namespace VioletVreath {

/**
 * 敵機アドラステア .
 * 横回転も自由にできるバキュラ～・・・
 * @version 1.00
 * @since 2012/08/06
 * @author Masatoshi Tsuge
 */
class EnemyAdrastea : public GgafLib::CubeMapMeshSetActor {

public:
    enum {
        PROG_MOVE01_1 = 1  ,
        PROG_SPLINE_MOVE   ,
        PROG_MOVE02_1      ,
        PROG_MOVE02_2      ,
    };

    enum {
        SE_DAMAGED   = 0,
        SE_EXPLOSION ,
    };

    coord colli_box_dX_;
    coord colli_box_dY_;
    coord colli_box_dZ_;
    int box_num_X_;
    int box_num_Y_;
    int box_num_Z_;

    EnemyAdrastea(const char* prm_name);

    void config(
            coord prm_colli_box_dx,
            coord prm_colli_box_dY,
            coord prm_colli_box_dZ,
            int prm_box_num_X,
            int prm_box_num_Y,
            int prm_box_num_Z
        );
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

