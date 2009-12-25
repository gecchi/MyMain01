#ifndef ENEMYIRIS_H_
#define ENEMYIRIS_H_
namespace MyStg2nd {

/**
 * 敵機イリス .
 * @version 1.00
 * @since 2009/12/22
 * @author Masatoshi Tsuge
 */
class EnemyIris : public GgafDx9LibStg::DefaultMeshSetActor {

public:
    int _iMovePatternNo;

    /** スプラインプログラム */
    GgafDx9Core::GgafDx9SplineProgram* _pProgram_IrisMove;

    EnemyIris(const char* prm_name);

    void initialize();

    void onActive();

    void processBehavior();

    void processJudgement();

    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    virtual ~EnemyIris();
};

}
#endif /*ENEMYIRIS_H_*/

