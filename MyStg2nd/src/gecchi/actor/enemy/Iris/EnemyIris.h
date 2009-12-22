#ifndef ENEMYIRIS_H_
#define ENEMYIRIS_H_
namespace MyStg2nd {

/**
 * �C���X
 * 2009/12/22
 */
class EnemyIris : public GgafDx9LibStg::DefaultMeshActor {

public:
    int _iMovePatternNo;

    /** Iris���ʃX�v���C��A */
    static GgafDx9Core::GgafDx9Spline3D _spIris_A;
    /** Iris���ʃX�v���C��B */
    static GgafDx9Core::GgafDx9Spline3D _spIris_B;
    /** �X�v���C���v���O����A */
    GgafDx9Core::GgafDx9SplineProgram* _pProgram_IrisMoveA;
    /** �X�v���C���v���O����B */
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

