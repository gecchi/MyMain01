#ifndef LASERCHIPDISPATCHER_H_
#define LASERCHIPDISPATCHER_H_
namespace MyStg2nd {

/**
 * レーザーチップ使いまわし管理クラス .
 * new した後 addSubLast メソッドで LaserChipインスタンスを好きな個数登録してください。<BR>
 * new から initialize()まで、又は随時変更が有効なパラメータ<BR>
 * ・_num_chip_interval ･･･弾切れフレーム数（デフォルト:20）<BR>
 * ・_pSeCon_Laser ･･･ レーザーチップ発射時SE（デフォルト:NULL）<BR>
 */
class LaserChipDispatcher : public GgafDx9LibStg::ActorDispatcher {
    friend class LaserChip;
public:
    /** 保持するレーザーチップ数(読み取り専用) */
    int _num_chip_max;
    /** 活動中レーザーチップ数(読み取り専用) */
    int _num_chip_active;
    /** レーザーチップ切断されたフラグ(読み取り専用、true=連続発射状態は遮断されている/false=連続発射状態) */
    bool _is_tear_laser;
    /** 前回（前フレーム）取得されたレーザーチップ(読み取り専用) */
    LaserChip* _pChip_prev_employ;
    /** 前回（前フレーム）取得されたレーザーチップの取得された時点の活動フレーム(読み取り専用) */
    DWORD _frame_of_active_prev_employ;
    /** レーザーチップ連続取得カウント(読み取り専用) */
    int _num_continual_employ_count;
    /** レーザーチップ連続未取得カウント(読み取り専用) */
    int _num_interval_frame_count;


    /** 弾切れフレーム数（読み書き可／デフォルト=20） */
    int _num_chip_interval;
    /** レーザーチップ発射時SE（読み書き可／デフォルト=NULL） */
    GgafDx9Core::GgafDx9SeConnection* _pSeConnection;

    LaserChipDispatcher(const char* prm_name);

    virtual void processBehavior() override;

    /**
     * レーザーチップの借り入れを試みる .
     * ストック切れの場合は NULL が返る。必ずチェックすること。
     * 使い終われば inactivate() を実行してください。自動的にストックに戻ります。
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
