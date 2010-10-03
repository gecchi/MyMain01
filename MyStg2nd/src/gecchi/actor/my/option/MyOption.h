#ifndef MYDUMMYOPTION_H_
#define MYDUMMYOPTION_H_
namespace MyStg2nd {


//class MyOption : public GgafDx9LibStg::DefaultMorphMeshActor {
class MyOption : public GgafDx9LibStg::DefaultMeshSetActor {

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


    /** [r]親アクター */
    MyOptionController* _pMyOptionController;
    /** [r]自身のオプション番号(０～・・・) */
    int _no;
    /** [r]１オプション当たりの最大可能ロックオン数 */
    static int _max_lockon_num;
    /** [r]ロックオンコントローラー */
    MyOptionLockonController* _pLockonController;
    /** [r]魚雷コントローラー */
    MyOptionTorpedoController* _pTorpedoController;
    /** [r]発射するレーザーチップのディスパッチャー */
    GgafDx9LibStg::LaserChipDispatcher* _pLaserChipDispatcher;
    /** [r]発射するショットのディスパッチャー */
    GgafCore::GgafActorDispatcher* _pDispatcher_MyShots001;
    /** [r]レーザー発射中のエフェクト */
    GgafDx9Core::GgafDx9DrawableActor* _pEffect_LaserIrradiate;


    /** [r]計算された現在の旋廻円周移動角速度（読み出し専用） */
    angvelo _angveloMove;
    /** [r]円周上初期位置角度（周囲角）（initialize()までに変更可／デフォルト=0） */
    angle _angPosition;
    /** [r]旋廻円周半径（initialize()までに変更可／デフォルト=200000） */
    int _radiusPosition;
    /** [r/w]旋廻円周移動速度（随時変更可／デフォルト=1000） */
    velo _veloMv;
    /** [r/w]オプションの広がり回転角（随時変更可／デフォルト=0 MyOptionControllerと同じ方向（前方）を向いている） */
    angle _angExpanse;

    /** [r]初期円周上初期位置角度 */
    angle _angPosition_base;
    /** [r]初期旋廻円周半径 */
    int _radiusPosition_base;
    /** [r]初期旋廻円周移動速度 */
    velo _veloMv_base;
    /** [r]初期オプションの広がり回転角 */
    angle _angExpanse_default;

    /** オプションの広がり回転角速度（通常時） */
    angvelo _angveloExpanseNomal;
    /** オプションの広がり回転角速度（微調整時） */
    angvelo _angveloExpanseSlow;

    /** オプションの初期位置に自動戻りを行っている最中は true */
    bool _return_to_base_radiusPosition_seq;
    /** オプションの初期円周半径に自動戻りを行っている最中は true */
    bool _return_to_base_angExpanse_seq;



    bool _adjust_angPosition_seq;

    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_no オプション番号（0～...)
     * @param prm_pMyOptionController 親アクター
     * @return
     */
    MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pMyOptionController);

    /**
     * 初期設定パラメーター .
     * 生成直後からinitialize()までに設定することができる、
     * オブジェクト固有パラメータです。
     * @param prm_radiusPosition 自機からの半径を指定
     * @param prm_angPosition 上記半径の円周上においての位置を円周角で指定
     * @param prm_angExpanse 上記の位置でのオプションの「前方」向きを指定。0で正面
     * @param prm_veloMv 旋回移動速度を指定
     */
    void config(
            angle prm_radiusPosition,
            angle prm_angPosition,
            angle prm_angExpanse,
            velo prm_veloMv)
    {
        _angPosition = prm_angPosition;
        _radiusPosition = prm_radiusPosition;
        _angExpanse = prm_angExpanse;
        _veloMv = prm_veloMv;

        _angPosition_base = prm_angPosition;
        _radiusPosition_base = prm_radiusPosition;
        _angExpanse_default = prm_angExpanse;
        _veloMv_base = prm_veloMv;
    }
    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processFinal() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyOption();


    void adjustAngPosition(angle prm_new_angPosition_base);

};

}
#endif /*MYDUMMYOPTION_H_*/

