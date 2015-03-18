#ifndef MYOPTION_H_
#define MYOPTION_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"


#define OPT_RADIUS_POS_MIN (PX_C(30))
#define OPT_RADIUS_POS_MAX (PX_C(1000))

namespace VioletVreath {

//class MyOption : public GgafLib::DefaultMorphMeshActor {
class MyOption : public GgafLib::DefaultMeshSetActor {


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
    void addRadiusPosition(int prm_radius_offset, int prm_min_radius = OPT_RADIUS_POS_MIN, int prm_max_radius = OPT_RADIUS_POS_MAX);

public:
    enum {
        SE_FIRE_LASER  ,
        SE_FIRE_SHOT   ,
        SE_FIRE_TORPEDO,
    };

    //一時変数達
    coord x_org_,y_org_,z_org_;

    /** [r]親アクター */
    MyOptionController* pOptionCtrler_;
    /** [r]自身のオプション番号(０～・・・) */
    int no_;

    /** [r]ロックオンコントローラー */
    MyLockonController* pLockonCtrler_;
    /** [r]魚雷コントローラー */
    MyTorpedoController* pTorpedoCtrler_;
    /** [r]レーザーチップのデポジトリ */
    GgafLib::LaserChipDepository* pLaserChipDepo_;
    /** [r]ショットのデポジトリ */
    GgafCore::GgafActorDepository* pDepo_MyOptionShot_;
    /** [r]スナイプショットのデポジトリ */
    GgafCore::GgafActorDepository* pDepo_MySnipeOptionShot_;
    /** [r]レーザー発射中のエフェクト */
    GgafDxCore::GgafDxFigureActor* pEffect_LaserIrradiate_;

    /** [r]計算された現在の旋廻円周移動角速度（読み出し専用） */
    angvelo angveloMove_;
    /** [r]円周上初期位置角度（周囲角）（initialize()までに変更可／デフォルト=0） */
    angle angPosition_;
    /** [r]現在の旋廻円周半径（initialize()までに変更可／デフォルト=200000） */
    int radiusPosition_;
    /** [r/w]旋廻円周移動速度（随時変更可／デフォルト=1000） */
    velo veloMv_;
    /** [r/w]オプションの広がり回転角（随時変更可／デフォルト=0 MyOptionControllerと同じ方向（前方）を向いている） */
    angle angExpanse_;

    /** [r]初期円周上角度位置 */
    angle angPosition_base_;
    /** [r]初期旋廻円周半径 */
    int radiusPosition_base_;
    /** [r]停止時に戻るべき廻円周半径 */
    int radiusPosition_stopping_;
    /** [r]半径移動速度(OPTION操作時) */
    int radiusPosition_velo_;

    /** [r]初期旋廻円周移動速度 */
    velo veloMv_base_;
    /** [r]初期オプションの広がり回転角 */
    angle angExpanse_default_;

    /** オプションの広がり回転角速度（通常時） */
    angvelo angveloExpanseNomal_;
    /** オプションの広がり回転角速度（微調整時） */
    angvelo angveloExpanseSlow_;

    /** オプションの初期位置に自動戻りを行っている最中は true */
    bool return_to_base_radiusPosition_seq_;
    /** オプションの初期円周半径に自動戻りを行っている最中は true */
    bool return_to_base_angExpanse_seq_;


    /** [r]初期円周上角度位置へ自動戻りシークエンス進捗番号 */
    int adjust_angPos_seq_progress_;
    /** [r]初期円周上角度位置へ自動戻りシークエンス時、ターゲット円周上角度位置 */
    angle adjust_angPos_seq_new_angPosition_base_;
    /** [r]初期円周上角度位置へ自動戻りシークエンス時、ターゲット円周上角度位置に到達するまでに費やされるフレーム数 */
    frame adjust_angPos_seq_spent_frame_;

    //GgafDxCore::GgafDxQuaternion Q_;
    EffectMyOption* pEffect_;

    /** [r]停止時、初期円周上角度位置へ自動戻りシークエンスの実行が必要かどうかフラグ */
    bool need_adjust_pos_flg_;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_no オプション番号（0～...)
     * @param prm_pOptCtrler 親アクター
     * @return
     */
    MyOption(const char* prm_name, uint32_t prm_no, MyOptionController* prm_pOptCtrler);

    /**
     * 初期設定パラメーター .
     * 生成直後からinitialize()までに設定することができる、
     * オブジェクト固有パラメータです。
     * @param prm_radiusPosition 自機からの半径を指定
     * @param prm_angPosition 上記半径の円周上においての位置を円周角で指定
     * @param prm_angExpanse 上記の位置でのオプションの「前方」向きを指定。0で正面
     * @param prm_velo_mv 旋回移動速度を指定
     */
    void config(
            angle prm_radiusPosition,
            angle prm_angPosition,
            angle prm_angExpanse,
            velo prm_velo_mv)
    {
        angPosition_ = prm_angPosition;
        angExpanse_ = prm_angExpanse;
        veloMv_ = prm_velo_mv;
        angPosition_base_ = prm_angPosition;
        radiusPosition_base_ = prm_radiusPosition;
        radiusPosition_ = radiusPosition_base_;
        radiusPosition_stopping_ = radiusPosition_base_;
        radiusPosition_velo_ = 3000 * (radiusPosition_base_/60000);
        angExpanse_default_ = prm_angExpanse;
        veloMv_base_ = prm_velo_mv;
        reset();
    }
    void onCreateModel() override;

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyOption();


    void adjustAngPosition(angle prm_new_angPosition_base, frame prm_spent_frame);

};

}
#endif /*MYOPTION_H_*/

