#ifndef ENEMYMETIS_H_
#define ENEMYMETIS_H_
namespace MyStg2nd {

//ƒ”ƒFƒXƒ^
class EnemyMetis : public GgafDx9LibStg::DefaultMeshActor {

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

    void processOnHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyMetis();
};

}
#endif /*ENEMYMETIS_H_*/

