#ifndef MYSHOT001_H_
#define MYSHOT001_H_
namespace MyStg2nd {

class MyShot001 : public GgafDx9LibStg::DefaultSpriteSetActor {
//class MyShot001 : public DefaultSpriteMyActor {

public:

    GgafDx9Core::GgafDx9GeometricActor* _pActor_Radical;

    MyShot001(const char* prm_name);

    /**
     * ＜OverRide です＞
     */
    void initialize();

    /**
     * ＜OverRide です＞
     */
    void processBehavior();

    /**
     * ＜OverRide です＞
     */
    void processJudgement();

    /**
     * ＜OverRide です＞
     */
    void processOnHit(GgafCore::GgafActor* prm_pOtherActor);

    /**
     * ＜OverRide です＞
     */
    void onInactive();

    /**
     * 親元対象アクター
     * @param prm_pActor
     */
    void setRadicalActor(GgafDx9Core::GgafDx9GeometricActor* prm_pActor) {
        _pActor_Radical = prm_pActor;
    }

    virtual ~MyShot001();
};

}
#endif /*MYSHOT001_H_*/

