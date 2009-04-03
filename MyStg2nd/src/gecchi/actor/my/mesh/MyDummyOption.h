#ifndef MYDUMMYOPTION_H_
#define MYDUMMYOPTION_H_
namespace MyStg2nd {

class MyDummyOption : public GgafDx9LibStg::DefaultMeshActor {

public:

    int _X_ParentPrev;
    int _Y_ParentPrev;
    int _Z_ParentPrev;

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

    void processDrawMain();

    virtual ~MyDummyOption();


    static void getWorldTransformRxRyRzScMvRzRy(
                     GgafDx9Core::GgafDx9UntransformedActor* prm_pActor,
                     GgafDx9Core::angle prm_RZ2,
                     GgafDx9Core::angle prm_RY2,
                     D3DXMATRIX& out_matWorld
                );

    static void getWorldTransformRxRyRzMvRyRzRy(
                     GgafDx9Core::GgafDx9UntransformedActor* prm_pActor,
                     GgafDx9Core::angle prm_RY2,
                     GgafDx9Core::angle prm_RZ2,
                     GgafDx9Core::angle prm_RY3,
                     D3DXMATRIX& out_matWorld
                );

};

}
#endif /*MYDUMMYOPTION_H_*/

