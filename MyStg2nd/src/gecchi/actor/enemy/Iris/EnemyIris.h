#ifndef ENEMYIRIS_H_
#define ENEMYIRIS_H_
namespace MyStg2nd {

/**
 * イリス
 * 2009/12/22
 */
class EnemyIris : public GgafDx9LibStg::DefaultMeshActor {

public:
    int _iMovePatternNo;

    /** Iris共通スプラインA */
    static GgafDx9Core::GgafDx9Spline3D _spIris_A;
    /** Iris共通スプラインB */
    static GgafDx9Core::GgafDx9Spline3D _spIris_B;
    /** スプラインプログラムA */
    GgafDx9Core::GgafDx9SplineProgram* _pProgram_IrisMoveA;
    /** スプラインプログラムB */
    GgafDx9Core::GgafDx9SplineProgram* _pProgram_IrisMoveB;

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

