#ifndef ENEMYVESTA_H_
#define ENEMYVESTA_H_
namespace MyStg2nd {

//���F�X�^
class EnemyVesta : public DefaultMeshEnemyActor {

public:
    int _iMovePatternNo;

    EnemyVesta(const char* prm_name);

    void initialize();

    void processBehavior();

    void processJudgement();

    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    int isGone();

    virtual ~EnemyVesta();
};

}
#endif /*ENEMYVESTA_H_*/

