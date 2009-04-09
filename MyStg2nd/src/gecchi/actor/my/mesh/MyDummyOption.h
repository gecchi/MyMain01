#ifndef MYDUMMYOPTION_H_
#define MYDUMMYOPTION_H_
namespace MyStg2nd {

class MyDummyOption : public GgafDx9LibStg::DefaultMeshActor {
    /** 親アクター */
    MyOptionParent* _pMyOptionParent;

    /** オプション番号 */
    int _no;

    //一時変数達
    int _Xorg,_Yorg,_Zorg;
    float _RXorg,_RYorg,_RZorg;
    float _vXwk,_vYwk,_vZwk;
    float _Xwk,_Ywk,_Zwk;

public:
    /** 現在の最終的な座標 */
    int _X2, _Y2, _Z2;
    /** 現在の最終的な軸回転角度 */
    GgafDx9Core::angle _RZ2, _RY2;
    /** 旋廻移動角速度（読み出し専用） */
    GgafDx9Core::angvelo _angveloMove;

    /** 円周上初期位置角度（周囲角）（上書き初期設定可） */
    GgafDx9Core::angle _angPosition;
    /** 旋廻半径距離（上書き初期設定可） */
    int _radius;

    /** 旋廻移動速度（読み書き可） */
    GgafDx9Core::velo _veloMove;
    /** オプションの広がり回転角（読み書き可） */
    GgafDx9Core::angle _angExpanse;
    /** オプションの広がり回転角速度 （読み書き可）*/
    GgafDx9Core::angvelo _angveloExpanse;


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

