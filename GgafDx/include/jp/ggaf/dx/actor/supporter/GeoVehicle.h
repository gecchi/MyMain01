#ifndef GGAF_DX_GEOVEHICLE_H_
#define GGAF_DX_GEOVEHICLE_H_
#include "GgafDxCommonHeader.h"
#include "ActorVehicle.h"

#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * 作成中 .
 * GeometricActor のメンバの<BR>
 * _x, _y, _z  ・・・ アクターの座標<BR>
 * を、各成分毎に簡単に操作するために作成。<BR>
 * @version 1.00
 * @since 2022/05/09
 * @author Masatoshi Tsuge
 */
class GeoVehicle : public ActorVehicle {

public:

    velo _velo;
    acce _acce;

    /** [r/w]X軸方向移動速度 */
    velo _velo_x;
    /** [r/w]Y軸方向移動速度 */
    velo _velo_y;
    /** [r/w]Z軸方向移動速度 */
    velo _velo_z;
    /** [r/w]移動速度上限 */
    velo _top_velo;
    /** [r/w]移動速度下限 */
    velo _bottom_velo;

    /** [r/w]X軸方向移動加速度 */
    acce _acce_x;
    /** [r/w]Y軸方向移動加速度 */
    acce _acce_y;
    /** [r/w]Z軸方向移動加速度 */
    acce _acce_z;
    /** [r/w]移動加速度上限*/
    acce _top_acce;
    /** [r/w]移動加速度下限*/
    acce _bottom_acce;


public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  駕籠に乗るActor
     */
    explicit GeoVehicle(GeometricActor* prm_pActor);

    /**
     * 移動速度の上限下限を強制 .
     * @param prm_velo01 速度１
     * @param prm_velo02 速度２
     */
    void forceVeloRange(velo prm_velo01, velo prm_velo02);

    /**
     * 移動加速度の上限下限を強制 .
     * @param prm_acce01 加速度１
     * @param prm_acce02 加速度２
     */
    void forceAcceRange(acce prm_acce01, acce prm_acce02);

    /**
     * X軸Y軸Z軸方向の移動速度を目標座標と移動速度で設定する。
     * @param prm_tx 目標X座標
     * @param prm_ty 目標Y座標
     * @param prm_tz 目標Z座標
     * @param prm_velo 移動速度
     */
    void setVeloTwd(coord prm_tx, coord prm_ty, coord prm_tz, velo prm_velo);

    void setVeloTwd(angle prm_rz, angle prm_ry, velo prm_velo);

    void setVelo(velo prm_velo_x, velo prm_velo_y, velo prm_velo_z);

    void setVeloZero();

    void setAcceTwd(coord prm_tx, coord prm_ty, coord prm_tz, acce prm_acce);

    void setAcce(acce prm_acce_x, acce prm_acce_y, acce prm_acce_z);

    void setAcceZero();

    /**
     * 速度、加速度をリセット、各上限下限を初期設定。
     */
    void reset();

    /**
     * 駕籠(平行移動支援)が振る舞う .
     * 駕籠(平行移動支援)機能を利用する場合は、このメソッドを毎フレーム呼び出し実行してください。<BR>
     * 逆に駕籠(平行移動支援)を必要としない場合は、このメソッドを呼び出さないことで、パフォーマンスに影響を与えません。<BR>
     */
    virtual void behave();

    virtual ~GeoVehicle();
};

}
#endif /*GGAF_DX_GEOVEHICLE_H_*/

