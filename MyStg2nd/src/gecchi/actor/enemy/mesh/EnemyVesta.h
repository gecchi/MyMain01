#ifndef ENEMYVESTA_H_
#define ENEMYVESTA_H_
namespace MyStg2nd {

//ƒ”ƒFƒXƒ^
class EnemyVesta : public DefaultMeshEnemyActor {

public:
    int _iMovePatternNo;

    EnemyVesta(const char* prm_name, const char* prm_model);

    void initialize();

    void processBehavior();

    void processJudgement();

    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    bool isOffScreen();

    virtual ~EnemyVesta();
};

}
#endif /*ENEMYVESTA_H_*/

