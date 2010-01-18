#ifndef ENEMYJUNO_H_
#define ENEMYJUNO_H_
namespace MyStg2nd {

//ÉWÉÖÉmÅ[
class EnemyJuno : public DefaultMeshEnemyActor {

public:
    int _iMovePatternNo;

    EnemyJuno(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void processOnHit(GgafCore::GgafActor* prm_pOtherActor) override;

    int isOutOfGameSpace() override;

    virtual ~EnemyJuno();
};

}
#endif /*ENEMYJUNO_H_*/

