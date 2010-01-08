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


    void initialize();

    void onActive();

    void processBehavior();

    void processJudgement();

    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);



    virtual ~EnemyVesta();
};

}
#endif /*ENEMYVESTA_H_*/

