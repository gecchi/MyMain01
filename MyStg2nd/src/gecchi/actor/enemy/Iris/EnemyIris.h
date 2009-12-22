#ifndef ENEMYIRIS_H_
#define ENEMYIRIS_H_
namespace MyStg2nd {

/**
 * ÉCÉäÉX
 * 2009/12/22
 */
class EnemyIris : public GgafDx9LibStg::DefaultMeshActor {

public:
    int _iMovePatternNo;

    int _width_X;
    int _height_Z;
    int _depth_Y;

    EnemyIris(const char* prm_name);

    void initialize();

    void processBehavior();

    void processJudgement();

    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);



    virtual ~EnemyIris();
};

}
#endif /*ENEMYIRIS_H_*/

