#ifndef MYOPTION_H_
#define MYOPTION_H_
namespace VioletVreath {

//class MyOption : public GgafLib::DefaultMorphMeshActor {
class MyOption : public GgafLib::DefaultMeshSetActor {


    GgafDxCore::GgafDxQuaternion Q_;

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
     * @param prm_min_radius 最低半径距離
     */
    void addRadiusPosition(int prm_radius_offset, int prm_min_radius = 30000, int prm_max_radius = 1000000);


public:
    //一時変数達
    int Xorg_,Yorg_,Zorg_;

    /** [r]親アクター */
    MyOptionController* pMyOptionController_;
    /** [r]自身のオプション番号(０～・・・) */
    int no_;
    /** [r]１オプション当たりの最大可能ロックオン数 */
    static int max_lockon_num_;
    /** [r]１オプション当たりの現在可能ロックオン数 */
    static int lockon_num_;
    /** [r]ロックオンコントローラー */
    MyOptionLockonController* pLockonController_;
    /** [r]魚雷コントローラー */
    MyOptionTorpedoController* pTorpedoController_;
    /** [r]発射するレーザーチップのデポジトリ */
    GgafLib::LaserChipDepository* pLaserChipDepo_;
    /** [r]発射するショットのデポジトリ */
    GgafCore::GgafActorDepository* pDepo_MyShots001_;
    /** [r]レーザー発射中のエフェクト */
    GgafDxCore::GgafDxDrawableActor* pEffect_LaserIrradiate_;

    int velo_radius_;

    /** [r]計算された現在の旋廻円周移動角速度（読み出し専用） */
    ang_velo ang_veloMove_;
    /** [r]円周上初期位置角度（周囲角）（initialize()までに変更可／デフォルト=0） */
    angle angPosition_;
    /** [r]旋廻円周半径（initialize()までに変更可／デフォルト=200000） */
    int radiusPosition_;
    /** [r/w]旋廻円周移動速度（随時変更可／デフォルト=1000） */
    velo veloMv_;
    /** [r/w]オプションの広がり回転角（随時変更可／デフォルト=0 MyOptionControllerと同じ方向（前方）を向いている） */
    angle angExpanse_;

    /** [r]初期円周上初期位置角度 */
    angle angPosition_base_;
    /** [r]初期旋廻円周半径 */
    int radiusPosition_base_;
    int radiusPosition_stopping_;

    /** [r]初期旋廻円周移動速度 */
    velo veloMv_base_;
    /** [r]初期オプションの広がり回転角 */
    angle angExpanse_default_;

    /** オプションの広がり回転角速度（通常時） */
    ang_velo ang_veloExpanseNomal_;
    /** オプションの広がり回転角速度（微調整時） */
    ang_velo ang_veloExpanseSlow_;

    /** オプションの初期位置に自動戻りを行っている最中は true */
    bool return_to_base_radiusPosition_seq_;
    /** オプションの初期円周半径に自動戻りを行っている最中は true */
    bool return_to_base_angExpanse_seq_;



    int adjust_angPos_seq_progress_;
    angle adjust_angPos_seq_new_angPosition_base_;
    frame adjust_angPos_seq_spent_frame_;
    angle adjust_angPos_seq_angPosition_;

    //GgafDxCore::GgafDxQuaternion Q_;
    EffectMyOption* pEffect_;

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
        angPosition_ = prm_angPosition;
        radiusPosition_ = prm_radiusPosition;
        angExpanse_ = prm_angExpanse;
        veloMv_ = prm_veloMv;
        angPosition_base_ = prm_angPosition;
        radiusPosition_base_ = prm_radiusPosition;
        radiusPosition_stopping_ = radiusPosition_base_;
        velo_radius_ = 0;
        angExpanse_default_ = prm_angExpanse;
        veloMv_base_ = prm_veloMv;
    }
    void onCreateModel() override;

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyOption();


    void adjustAngPosition(angle prm_new_angPosition_base, frame prm_spent_frame);

};

}
#endif /*MYOPTION_H_*/

