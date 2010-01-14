#ifndef MYSHOT001_H_
#define MYSHOT001_H_
namespace MyStg2nd {

class MyShot001 : public GgafDx9LibStg::DefaultSpriteSetActor {
//class MyShot001 : public DefaultSpriteMyActor {

public:

    GgafDx9Core::GgafDx9GeometricActor* _pActor_Radical;

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
    void processOnHit(GgafCore::GgafActor* prm_pOtherActor);

    /**
     * ��OverRide �ł���
     */
    void onInactive();

    /**
     * �e���ΏۃA�N�^�[
     * @param prm_pActor
     */
    void setRadicalActor(GgafDx9Core::GgafDx9GeometricActor* prm_pActor) {
        _pActor_Radical = prm_pActor;
    }

    virtual ~MyShot001();
};

}
#endif /*MYSHOT001_H_*/

