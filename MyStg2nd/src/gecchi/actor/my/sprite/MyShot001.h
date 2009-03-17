#ifndef MYSHOT001_H_
#define MYSHOT001_H_
namespace MyStg2nd {

class MyShot001 : public DefaultSpriteMyActor {

public:

    GgafDx9Core::GgafDx9UntransformedActor* _pActor_Radical;

    MyShot001(const char* prm_name);

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
    void onInact();

    /**
     * �e���ΏۃA�N�^�[
     * @param prm_pActor
     */
    void setRadicalActor(GgafDx9Core::GgafDx9UntransformedActor* prm_pActor) {
        _pActor_Radical = prm_pActor;
    }

    virtual ~MyShot001();
};

}
#endif /*MYSHOT001_H_*/

