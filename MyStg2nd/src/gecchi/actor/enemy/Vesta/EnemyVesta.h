#ifndef ENEMYVESTA_H_
#define ENEMYVESTA_H_
namespace MyStg2nd {

//ƒ”ƒFƒXƒ^
class EnemyVesta : public GgafDx9LibStg::DefaultMeshActor {

public:
    int _iMovePatternNo;

    int _width_X;
    int _height_Z;
    int _depth_Y;

    EnemyVesta(const char* prm_name);


    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processOnHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyVesta();
};

}
#endif /*ENEMYVESTA_H_*/

