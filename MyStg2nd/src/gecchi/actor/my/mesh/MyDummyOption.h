#ifndef MYDUMMYOPTION_H_
#define MYDUMMYOPTION_H_
namespace MyStg2nd {

//class MyDummyOption : public GgafDx9LibStg::DefaultMorphMeshActor {
class MyDummyOption : public GgafDx9LibStg::DefaultMeshSetActor {


    /** 親アクター */
    MyOptionParent* _pMyOptionParent;

    /** オプション番号 */
    int _no;

    //一時変数達
    int _Xorg,_Yorg,_Zorg;
    //angle _RXorg,_RYorg,_RZorg;
    float _vXwk,_vYwk,_vZwk;
    GgafDx9Core::GgafDx9Quaternion _Q;

public:



    LaserChipDispatcher* _pLaserChipDispatcher;
    GgafDx9Core::GgafDx9SeConnection* _pSeCon_Laser;


    /** 現在の最終的な座標（読み出し専用） */
    //int _X2, _Y2, _Z2;
    /** 現在の最終的な軸回転角度（読み出し専用） */
    //angle _RZ2, _RY2;
    /** 現在の旋廻円周移動角速度（読み出し専用） */
    angvelo _angveloMove;

    /** 円周上初期位置角度（周囲角）（initialize()までに変更可／デフォルト=0） */
    angle _angPosition;
    /** 旋廻円周半径（initialize()までに変更可／デフォルト=200000） */
    int _radiusPosition;
    /** 旋廻円周移動速度（随時変更可／デフォルト=1000） */
    velo _veloMove;
    /** オプションの広がり回転角（随時変更可／デフォルト=0 MyOptionParentと同じ方向（前方）を向いている） */
    angle _angExpanse;
    /** オプションの広がり回転角速度 （随時変更可／デフォルト=100）*/
    angvelo _angveloExpanse;

    /** オプションの広がり回転角加速度 */
    angacce _angacceExpanse;


    angvelo _range_angveloExpanse;

    bool _is_flapping;
    bool _iflappingSeq;

    MyDummyOption(const char* prm_name, int prm_no, MyOptionParent* prm_pMyOptionParent);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyDummyOption();
};

}
#endif /*MYDUMMYOPTION_H_*/

