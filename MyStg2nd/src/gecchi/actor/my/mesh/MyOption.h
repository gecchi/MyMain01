#ifndef MYDUMMYOPTION_H_
#define MYDUMMYOPTION_H_
namespace MyStg2nd {

//class MyOption : public GgafDx9LibStg::DefaultMorphMeshActor {
class MyOption : public GgafDx9LibStg::DefaultMeshSetActor {


    /** 親アクター */
    MyOptionParent* _pMyOptionParent;

    /** オプション番号 */
    int _no;

    //一時変数達
    int _Xorg,_Yorg,_Zorg;
    //angle _RXorg,_RYorg,_RZorg;
    float _vXwk,_vYwk,_vZwk;
    GgafDx9Core::GgafDx9Quaternion _Q;

private:
    void addRadiusPosition(int prm_len);

public:
    GgafDx9Core::GgafDx9GeometricActor* _pLockOnTarget;
    EffectLockOn001* _pEffectLockOn;
    EffectLockOn001_Release* _pEffectLockOn_Release;

    LaserChipDispatcher* _pLaserChipDispatcher;
    GgafDx9Core::GgafDx9SeConnection* _pSeCon_Laser;

    /** 計算された現在の旋廻円周移動角速度（読み出し専用） */
    angvelo _angveloMove;
    /** 円周上初期位置角度（周囲角）（initialize()までに変更可／デフォルト=0） */
    angle _angPosition;
    /** 旋廻円周半径（initialize()までに変更可／デフォルト=200000） */
    int _radiusPosition;
    /** 旋廻円周移動速度（随時変更可／デフォルト=1000） */
    velo _veloMv;
    /** オプションの広がり回転角（随時変更可／デフォルト=0 MyOptionParentと同じ方向（前方）を向いている） */
    angle _angExpanse;

    /** 初期円周上初期位置角度 */
    angle _angPosition_default;
    /** 初期旋廻円周半径 */
    int _radiusPosition_default;
    /** 初期旋廻円周移動速度 */
    velo _veloMv_default;
    /** 初期オプションの広がり回転角 */
    angle _angExpanse_default;

    /** オプションの広がり回転角速度（通常時） */
    angvelo _angveloExpanseNomal;
    /** オプションの広がり回転角速度（微調整時） */
    angvelo _angveloExpanseSlow;


    MyOption(const char* prm_name, int prm_no, MyOptionParent* prm_pMyOptionParent);

    void setProperty(angle prm_radiusPosition, angle prm_angPosition, angle prm_angExpanse, velo prm_veloMv) {
        _angPosition = prm_angPosition;
        _radiusPosition = prm_radiusPosition;
        _angExpanse = prm_angExpanse;
        _veloMv = prm_veloMv;

        _angPosition_default = prm_angPosition;
        _radiusPosition_default = prm_radiusPosition;
        _angExpanse_default = prm_angExpanse;
        _veloMv_default = prm_veloMv;
    }

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyOption();


};

}
#endif /*MYDUMMYOPTION_H_*/

