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
    /**
     * 旋廻円周半径を再設定する .
     * 特定の条件下でのみ呼び出し可能。
     * @param prm_radius 半径
     */
    void setRadiusPosition(int prm_radius);

    /**
     * 旋廻円周半径を差分で再設定する .
     * 特定の条件下でのみ呼び出し可能。
     * @param prm_radius_offset 半径差分
     */
    void addRadiusPosition(int prm_radius_offset);

public:

    /** ロックオン中アクター */
    GgafDx9Core::GgafDx9GeometricActor* _pLockonTarget;


    EffectLockon001* _pEffectLockon;

    GgafDx9LibStg::LaserChipDispatcher* _pLaserChipDispatcher;
    GgafCore::GgafActorDispatcher* _pDispatcher_MyShots001;

    /** レーザー発射時エフェクト */
    GgafDx9Core::GgafDx9DrawableActor* _pEffect_LaserIrradiate;


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


    bool _return_to_default_radiusPosition_seq;
    bool _return_to_default_angExpanse_seq;


    MyOption(const char* prm_name, UINT32 prm_no, MyOptionParent* prm_pMyOptionParent);

    /**
     * 初期設定パラメーター .
     * 生成直後からinitialize()までに設定することができる、
     * オブジェクト固有パラメータです。
     * @param prm_radiusPosition 自機からの半径を指定
     * @param prm_angPosition 上記半径の円周上においての位置を円周角で指定
     * @param prm_angExpanse 上記の位置でのオプションの「前方」向きを指定。0で正面
     * @param prm_veloMv 旋回移動速度を指定
     */
    void setInitializeProperty(
            angle prm_radiusPosition,
            angle prm_angPosition,
            angle prm_angExpanse,
            velo prm_veloMv)
    {
        _angPosition = prm_angPosition;
        _radiusPosition = prm_radiusPosition;
        _angExpanse = prm_angExpanse;
        _veloMv = prm_veloMv;

        _angPosition_default = prm_angPosition;
        _radiusPosition_default = prm_radiusPosition;
        _angExpanse_default = prm_angExpanse;
        _veloMv_default = prm_veloMv;
    }
    void onCreateModel() override;

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void processFinal() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyOption();


};

}
#endif /*MYDUMMYOPTION_H_*/

