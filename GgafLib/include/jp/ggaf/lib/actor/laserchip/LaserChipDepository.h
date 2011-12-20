#ifndef LASERCHIPDEPOSITORY_H_
#define LASERCHIPDEPOSITORY_H_
namespace GgafLib {

/**
 * レーザ１本分(レーザーチップ使いまわし管理クラス。) .
 * new した後 addSubLast メソッドで LaserChipインスタンスを好きな個数登録してください。<BR>
 * new から initialize()まで、又は随時変更が有効なパラメータ<BR>
 * ・_num_chip_interval ・・・弾切れフレーム数（デフォルト:20）<BR>
 * ・_pSeCon_Laser ・・・ レーザーチップ発射時SE（デフォルト:NULL）<BR>
 * <使用例><BR>
 * <code><pre>
 *
 * ----- 事前準備（コンストラクタで１本分作成例） --------------
 *
 * LaserChipDepository* pLaserDepo = new LaserChipDepository("MyLaserDp");  //本デポジトリクラスを生成する
 * MyStraightLaserChip* pChip;                    //MyStraightLaserChip は LaserChip 継承クラス。
 * for (int i = 0; i < 60; i++) {                 //1本を60個のチップで構成
 *     pChip = new MyStraightLaserChip("chip");   //LaserChip クラスを継承・実装したオブジェクト作成
 *     pChip->setSource(this);                    //継承 LaserChip 固有の設定を施す。左の例はワインダーのための発射元設定。
 *     pLaserDepo->addSubLast(pChip);             //本デポジトリに LaserChip オブジェクトを登録(サブに所属させる)
 * }
 * pLaserDepo->config(40, 25);                    //LaserChip の最大連結数、弾切れフレーム数を設定。
 * addSubGroup(_pLaserChipDepo);                  //デポジトリ自体を活動可能にさせるため、何処かに所属させる。
 *
 *
 * ----- 発射処理（Zキー押しっぱなしで発射例） --------------
 *
 * if (GgafDxInput::isBeingPressedKey(DIK_Z)) {   //Zキー判定
 *     pLaserDepo->dispatch();                    //dispatch()することで、登録されたMyStraightLaserChip達が活動する。
 * }
 *
 * </pre></code>
 */
class LaserChipDepository : public GgafCore::GgafActorDepository {
    friend class LaserChip;
public:
    /** [r]保持するレーザーチップ数(読み取り専用) */
    int _num_chip_max;
    /** [r]活動中レーザーチップ数(読み取り専用) */
    int _num_chip_active;
    /** [r]レーザーチップ切断されたフラグ(読み取り専用、true=連続発射状態は遮断されている/false=連続発射状態) */
    bool _is_tear_laser;
    /** [r]前回（前フレーム）取得されたレーザーチップ(読み取り専用) */
    LaserChip* _pChip_prev_employ;
    /** [r]前回（前フレーム）取得されたレーザーチップの取得された時点の活動フレーム(読み取り専用) */
    frame _frame_of_behaving_prev_employ;
    /** [r]レーザーチップ連続取得カウント(読み取り専用) */
    int _num_continual_employ_count;
    /** [r]レーザーチップ連続未取得カウント(読み取り専用) */
    int _num_interval_frame_count;

    /** [r/w]弾切れに移行するチップの連続取得数。（読み書き可／デフォルト：addSubLast()完了後 _num_chip_max と同じになっている。 */
    int _num_continual_employ_max;
    /** [r/w]弾切れフレーム数（読み書き可／デフォルト=20） */
    int _num_chip_interval;
    /** [r/w]レーザー発射時エフェクト。不要の場合はNULLを設定する */
    GgafDxCore::GgafDxDrawableActor* _pEffectActor_Irradiate;

    LaserChipDepository(const char* prm_name, GgafCore::GgafStatus* prm_pStat = NULL);

    /**
     * LaserChipDepositoryを設定する。
     * @param prm_num_continual_employ_max 強制的に弾切れに移行するチップの連続取得数。
     * @param prm_num_chip_interval 弾切れフレーム数
     * @param prm_pEffectActor_Irradiate シーン所属済み発射中エフェクト(不要時はNULL)。解放は呼び元で。
     */
    virtual void config(int prm_num_continual_employ_max,
                        UINT32 prm_num_chip_interval,
                        GgafDxCore::GgafDxDrawableActor* prm_pEffectActor_Irradiate = NULL);

    virtual void processBehavior() override {
    }

    virtual void processFinal() override;

    /**
     * レーザーチップの借り入れを試み、借り入れできれば取得し活動状態にする。 .
     * ストック切れ、或いは弾切れ中の場合は戻りに NULL が返る。
     * 取得したチップの利用を終了する場合は sayonara() (或いはinactivate()) を実行してください。
     * 自動的にストックに戻ります。
     * @return 借り入れしたレーザーチップ。借り入れできない場合はNULL
     */
    virtual LaserChip* dispatch() override;

    /**
     * レーザーチップストックの追加 .
     * 好きなだけ追加して下さい。
     * 追加すればするほど玉切れがおきにくい
     * @param prm_pLaserChip レーザーチップ
     */
    void addSubLast(LaserChip* prm_pLaserChip);

    /**
     * リセット時の処理 .
     * メンバーを全てinactivateImmediately()します。
     */
    virtual void onReset() override;


     virtual ~LaserChipDepository();

};

}
#endif /*LASERCHIPDEPOSITORY_H_*/
