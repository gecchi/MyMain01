#ifndef MYSHOT001_H_
#define MYSHOT001_H_
namespace MyStg2nd {

class MyShot001 : public DefaultSpriteMyActor {

public:

    GgafDx9Core::GgafDx9UntransformedActor* _pActor_Radical;

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
    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    /**
     * ＜OverRide です＞
     */
    void onInact();

    /**
     * 親元対象アクター
     * @param prm_pActor
     */
    void setRadicalActor(GgafDx9Core::GgafDx9UntransformedActor* prm_pActor) {
        _pActor_Radical = prm_pActor;
    }

    virtual ~MyShot001();
};

}
#endif /*MYSHOT001_H_*/

