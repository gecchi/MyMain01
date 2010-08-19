#ifndef LASERCHIPDISPATCHER_H_
#define LASERCHIPDISPATCHER_H_
namespace GgafDx9LibStg {

/**
 * レーザーチップ使いまわし管理クラス .
 * new した後 addSubLast メソッドで LaserChipインスタンスを好きな個数登録してください。<BR>
 * new から initialize()まで、又は随時変更が有効なパラメータ<BR>
 * ・_num_chip_interval ・・・弾切れフレーム数（デフォルト:20）<BR>
 * ・_pSeCon_Laser ・・・ レーザーチップ発射時SE（デフォルト:NULL）<BR>
 */
class LaserChipDispatcher : public GgafCore::GgafActorDispatcher {
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
    GgafDx9Core::GgafDx9DrawableActor* _pEffectActor_Irradiate;

    LaserChipDispatcher(const char* prm_name);

    /**
     * LaserChipDispatcherを設定する。
     * @param prm_num_continual_employ_max 強制的に弾切れに移行するチップの連続取得数。
     * @param prm_num_chip_interval 弾切れフレーム数
     * @param prm_pEffectActor_Irradiate シーン所属済み発射中エフェクト(不要時はNULL)。解放は呼び元で。
     */
    virtual void config(int prm_num_continual_employ_max,
                        UINT32 prm_num_chip_interval,
                        GgafDx9Core::GgafDx9DrawableActor* prm_pEffectActor_Irradiate = NULL);

    virtual void processBehavior() override {
    }

    virtual void processFinal() override;

    /**
     * レーザーチップの借り入れを試みる .
     * ストック切れの場合は NULL が返る。必ずチェックすること。
     * 使い終われば sayonara() か、inactivate() を実行してください。自動的にストックに戻ります。
     * @return 借り入れしたレーザーチップ。借り入れできない場合はNULL
     */
    virtual LaserChip* employ() override;

    /**
     * レーザーチップストックの追加 .
     * 好きなだけ追加して下さい。
     * 追加すればするほど玉切れがおきにくい
     * @param prm_pLaserChip レーザーチップ
     */
    void addSubLast(LaserChip* prm_pLaserChip);

     virtual ~LaserChipDispatcher();

};

}
#endif /*LASERCHIPDISPATCHER_H_*/
