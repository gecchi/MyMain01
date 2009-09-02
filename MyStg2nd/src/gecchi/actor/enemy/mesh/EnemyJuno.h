#ifndef ENEMYJUNO_H_
#define ENEMYJUNO_H_
namespace MyStg2nd {

//ÉWÉÖÉmÅ[
class EnemyJuno : public DefaultMeshEnemyActor {

public:
    int _iMovePatternNo;

    EnemyJuno(const char* prm_name);

    void initialize();

    void processBehavior();

    void processJudgement();

    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    int isGone();

    virtual ~EnemyJuno();
};

}
#endif /*ENEMYJUNO_H_*/

