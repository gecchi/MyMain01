#ifndef LASER001PACTOR_H_
#define LASER001PACTOR_H_
namespace MyStg2nd {

class MyLaser001 : public DefaultSpriteMyActor {

    int _X_prevFrame;
    int _Y_prevFrame;
    int _Z_prevFrame;

    /** �ΏۃA�N�^�[ */
    GgafDx9Core::GgafDx9UntransformedActor* _pActor_Radical;

public:
    MyLaser001(const char* prm_name, const char* prm_model);

    /**
     * ��OverRide �ł���
     */
    void initialize();

    /**
     * ��OverRide �ł���
     */
    void processBehavior();

    /**
     * ��OverRide �ł���
     */
    void processJudgement();

    /**
     * ��OverRide �ł���
     */
    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    /**
     * ��OverRide �ł���
     */
    void onRefrain();

    void setRadicalActor(GgafDx9Core::GgafDx9UntransformedActor* prm_pActor) {
        _pActor_Radical = prm_pActor;
    }

    virtual ~MyLaser001();
};

}
#endif /*LASER001PACTOR_H_*/

