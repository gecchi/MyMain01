#ifndef ENEMYPALLAS_H_
#define ENEMYPALLAS_H_
namespace MyStg2nd {

//パラス
class EnemyPallas : public GgafDx9LibStg::DefaultMeshSetActor {

public:
    int _iMovePatternNo;

    EnemyPallas(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    bool isOutOfGameSpace() override;

    virtual ~EnemyPallas();
};

}
#endif /*ENEMYPALLAS_H_*/

