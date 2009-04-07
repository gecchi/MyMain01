#ifndef MYDUMMYOPTION_H_
#define MYDUMMYOPTION_H_
namespace MyStg2nd {

class MyDummyOption : public GgafDx9LibStg::DefaultMeshActor {



public:
    GgafDx9Core::angle _angRot_ParentPrev[3];

    int _X_ParentPrev;
    int _Y_ParentPrev;
    int _Z_ParentPrev;
    int _Xorg,_Yorg,_Zorg;
    float _RXorg,_RYorg,_RZorg;
    float _vXwk,_vYwk,_vZwk;
    float _Xwk,_Ywk,_Zwk;


    int _TX, _TY, _TZ;
    /** 自機へのポインタ */
    MyShip* _pMyShip;
    MyOptionParent* _pMyOptionParent;
    /** オプション番号 */
    int _no;

    /** オプションの広がり具合 */
    GgafDx9Core::angle _angExpanse;
    /** MyShipからの距離 */
    int _distR;
    /** 位置（周囲角） */
    GgafDx9Core::angle _angPosRotX;

    GgafDx9Core::angle _sangvelo;


    GgafDx9Core::angvelo _angvelo;
    MyDummyOption(const char* prm_name, int prm_no, MyOptionParent* prm_pMyOptionParent);

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

    virtual ~MyDummyOption();

};

}
#endif /*MYDUMMYOPTION_H_*/

