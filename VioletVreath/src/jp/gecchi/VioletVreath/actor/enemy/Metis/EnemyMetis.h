#ifndef ENEMYMETIS_H_
#define ENEMYMETIS_H_
namespace VioletVreath {

/**
 * 敵機メティス .
 * バキュラ～・・・
 * @version 1.00
 * @since 2010/04/21
 * @author Masatoshi Tsuge
 */
class EnemyMetis : public GgafLib::DefaultMeshSetActor {

public:
    int _iMovePatternNo;

    int _width_X;
    int _height_Z;
    int _depth_Y;

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

