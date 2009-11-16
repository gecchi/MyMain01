#ifndef ENEMYPALLAS_H_
#define ENEMYPALLAS_H_
namespace MyStg2nd {

//ƒpƒ‰ƒX
class EnemyPallas : public DefaultMeshEnemyActor {

public:
    int _iMovePatternNo;

    EnemyPallas(const char* prm_name);

    void initialize();

    void processBehavior();

    void processJudgement();

    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    int wasGone();

    virtual ~EnemyPallas();
};

}
#endif /*ENEMYPALLAS_H_*/

