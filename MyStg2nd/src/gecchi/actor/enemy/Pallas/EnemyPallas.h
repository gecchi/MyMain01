#ifndef ENEMYPALLAS_H_
#define ENEMYPALLAS_H_
namespace MyStg2nd {

//ƒpƒ‰ƒX
class EnemyPallas : public DefaultMeshEnemyActor {

public:
    int _iMovePatternNo;

    EnemyPallas(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    int isOutOfGameSpace() override;

    virtual ~EnemyPallas();
};

}
#endif /*ENEMYPALLAS_H_*/

