#ifndef MYDUMMYOPTION_H_
#define MYDUMMYOPTION_H_
namespace MyStg2nd {

class MyDummyOption : public GgafDx9LibStg::DefaultMorphMeshActor {
//class MyDummyOption : public GgafDx9LibStg::DefaultMeshSetActor {

    /** 親アクター */
    MyOptionParent* _pMyOptionParent;

    /** オプション番号 */
    int _no;

    //一時変数達
    int _Xorg,_Yorg,_Zorg;
    GgafDx9Core::angle _RXorg,_RYorg,_RZorg;
    float _vXwk,_vYwk,_vZwk;
    GgafDx9Core::GgafDx9Quaternion _Q;

public:
    LaserChipDispatcher* _pLaserChipDispatcher;
    GgafDx9Core::GgafDx9SeConnection* _pSeCon_Laser;


    /** 現在の最終的な座標（読み出し専用） */
    int _X2, _Y2, _Z2;
    /** 現在の最終的な軸回転角度（読み出し専用） */
    GgafDx9Core::angle _RZ2, _RY2;
    /** 現在の旋廻円周移動角速度（読み出し専用） */
    GgafDx9Core::angvelo _angveloMove;

    /** 円周上初期位置角度（周囲角）（initialize()までに変更可／デフォルト=0） */
    GgafDx9Core::angle _angPosition;
    /** 旋廻円周半径（initialize()までに変更可／デフォルト=200000） */
    int _radiusPosition;
    /** 旋廻円周移動速度（随時変更可／デフォルト=1000） */
    GgafDx9Core::velo _veloMove;
    /** オプションの広がり回転角（随時変更可／デフォルト=0 中心を向いている） */
    GgafDx9Core::angle _angExpanse;
    /** オプションの広がり回転角速度 （随時変更可／デフォルト=100）*/
    GgafDx9Core::angvelo _angveloExpanse;

    MyDummyOption(const char* prm_name, int prm_no, MyOptionParent* prm_pMyOptionParent);

    void initialize();

    void processBehavior();

    void processJudgement();

    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    virtual ~MyDummyOption();
};

}
#endif /*MYDUMMYOPTION_H_*/

