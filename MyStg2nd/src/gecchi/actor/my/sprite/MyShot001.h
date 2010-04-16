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
    void initialize() override;

    /**
     * ＜OverRide です＞
     */
    void processBehavior() override;

    /**
     * ＜OverRide です＞
     */
    void processJudgement() override;

    /**
     * ＜OverRide です＞
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    /**
     * ＜OverRide です＞
     */
    void onInactive() override;

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

