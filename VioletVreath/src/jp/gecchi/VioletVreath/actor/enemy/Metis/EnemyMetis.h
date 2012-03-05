#ifndef ENEMYMETIS_H_
#define ENEMYMETIS_H_
namespace VioletVreath {

/**
 * �G�@���e�B�X .
 * �o�L�����`�E�E�E
 * @version 1.00
 * @since 2010/04/21
 * @author Masatoshi Tsuge
 */
class EnemyMetis : public GgafLib::DefaultMeshSetActor {

public:
    int iMovePatternNo_;

    int width_X_;
    int height_Z_;
    int depth_Y_;

    EnemyMetis(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyMetis();
};

}
#endif /*ENEMYMETIS_H_*/

