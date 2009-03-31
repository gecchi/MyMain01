#ifndef MYOPTION_H_
#define MYOPTION_H_
namespace MyStg2nd {

class MyOption : public GgafDx9LibStg::DefaultMeshActor {

public:
    /** 自機へのポインタ */
    MyShip* _pMyShip;
    MyOptionParent* _pMyOptionParent;
    /** オプション番号 */
    int _no;

    /** MyShipからの距離 */
    int _distR;
    /** 位置（周囲角） */
    GgafDx9Core::angle _angPosRotX;

    GgafDx9Core::angle _sangvelo;
    MyOption(const char* prm_name, int prm_no, MyOptionParent* prm_pMyOptionParent);

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


    virtual ~MyOption();
};

}
#endif /*MYOPTION_H_*/

