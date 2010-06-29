#ifndef ENEMYMETIS_H_
#define ENEMYMETIS_H_
namespace MyStg2nd {

/**
 * 敵機メティス .
 * バキュラ～・・・
 * @version 1.00
 * @since 2010/04/21
 * @author Masatoshi Tsuge
 */
class EnemyMetis : public GgafDx9LibStg::DefaultMeshSetActor {

public:
    int _iMovePatternNo;

    int _width_X;
    int _height_Z;
    int _depth_Y;

    EnemyMetis(const char* prm_name);


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

