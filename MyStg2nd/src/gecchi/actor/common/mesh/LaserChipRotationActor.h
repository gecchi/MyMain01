#ifndef LASERCHIPROTATIONACTOR_H_
#define LASERCHIPROTATIONACTOR_H_
namespace MyStg2nd {

/**
 * レーザーチップ使いまわし管理クラス .
 * new から initialize()まで、又は随時変更が有効なパラメータ<BR>
 * ・_num_chip_interval ･･･弾切れフレーム数（デフォルト:3）<BR>
 * ・_pSeCon_Laser ･･･ レーザーチップ発射時SE（デフォルト:NULL）<BR>
 */
class LaserChipRotationActor : public GgafDx9LibStg::RotationActor {
    friend class LaserChip;
private:
    /** 保持するレーザーチップ数 */
    int _num_chip_max;
    /** 活動中レーザーチップ数 */
    int _num_chip_active;
    /** レーザーチップ切断されたフラグ(true=連続発射状態は遮断されている/false=連続発射状態) */
    bool _is_tear_laser;
    /** 前回（前フレーム）取得されたレーザーチップ */
    LaserChip* _pChip_prev_obtain;
    /** 前回（前フレーム）取得されたレーザーチップの取得された時点の活動フレーム */
    DWORD _lifeframe_prev_obtain;
    /** レーザーチップ連続取得カウント */
    int _num_continual_obtain_count;
    /** レーザーチップ連続未取得カウント */
    int _num_interval_frame_count;

public:
    /** 弾切れフレーム数（随時変更可／デフォルト=3） */
    int _num_chip_interval;
    /** レーザーチップ発射時SE（随時変更可／デフォルト=NULL） */
    GgafDx9Core::GgafDx9SeConnection* _pSeConnection;

    LaserChipRotationActor(const char* prm_name);

	virtual void processBehavior();

	virtual LaserChip* obtain();

	void addLaserChip(LaserChip* prm_pLaserChip);

 	virtual ~LaserChipRotationActor();

};

}
#endif /*LASERCHIPROTATIONACTOR_H_*/
