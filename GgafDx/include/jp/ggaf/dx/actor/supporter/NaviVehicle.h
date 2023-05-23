#ifndef GGAF_DX_NAVIVEHICLE_H_
#define GGAF_DX_NAVIVEHICLE_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "ActorVehicle.h"

#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * アクターの移動支援(ホーミング) .
 * 分身光牙レーザーのホーミング計算を、汎用的に切り出し。<BR>
 * setAcceByVc() がやりたかった事<BR>
 * @version 1.00
 * @since 2022/05/09
 * @author Masatoshi Tsuge
 */
class NaviVehicle : public ActorVehicle {

public:
    /** [r]移動速度 */
    velo _velo;
    /** [r]移動速度上限 */
    velo _top_velo;
    /** [r]移動速度下限 */
    velo _bottom_velo;
    /** [r]移動速度X軸成分(単位ベクトルではありません) */
    velo _velo_vc_x;
    /** [r]移動速度Y軸成分(単位ベクトルではありません) */
    velo _velo_vc_y;
    /** [r]移動速度Z軸成分(単位ベクトルではありません) */
    velo _velo_vc_z;

    /** [r]移動加速度 */
    acce _acce;
    /** [r]移動加速度上限*/
    acce _top_acce;
    /** [r]移動加速度下限*/
    acce _bottom_acce;
    /** [r]移動加速度X軸成分(単位ベクトルではありません) */
    acce _acce_vc_x;
    /** [r]移動加速度Y軸成分(単位ベクトルではありません) */
    acce _acce_vc_y;
    /** [r]移動加速度Z軸成分(単位ベクトルではありません) */
    acce _acce_vc_z;

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  駕籠に乗るActor
     */
    explicit NaviVehicle(GeometricActor* prm_pActor);

    /**
     * 移動速度の上限下限を強制強制する .
     * @param prm_velo01 速度１
     * @param prm_velo02 速度２
     */
    void forceVeloRange(velo prm_velo01, velo prm_velo02);

    /**
     * 移動加速度の上限下限を強制する .
     * @param prm_acce01 加速度１
     * @param prm_acce02 加速度２
     */
    void forceAcceRange(acce prm_acce01, acce prm_acce02);

    /**
     * 移動方向を座標、移動速度を値で設定する .
     * 移動速度下限～ 移動速度上限 の範囲外を設定した場合、
     * 方向はそのままで、直近の範囲内に納められて設定される。
     * @param prm_tx 移動方向X座標
     * @param prm_ty 移動方向Y座標
     * @param prm_tz 移動方向Z座標
     * @param prm_velo 移動速度
     */
    void setVeloTwd(coord prm_tx, coord prm_ty, coord prm_tz, velo prm_velo);

    /**
     * 移動方向を軸回転(Rz, Ry)、移動速度を値で設定する .
     * 移動速度下限～ 移動速度上限 の範囲外を設定した場合、
     * 方向はそのままで、直近の範囲内に納められて設定される。
     * @param prm_rz 移動方向z軸回転値
     * @param prm_ry 移動方向y軸回転値
     * @param prm_velo 移動速度
     */
    void setVeloTwd(angle prm_rz, angle prm_ry, velo prm_velo);

    /**
     * XYZ軸ベクトル成分で、移動速度を設定する .
     * 移動速度下限～ 移動速度上限 の範囲外を設定した場合、
     * 方向はそのままで、直近の範囲内に納められて設定される。
     * @param prm_velo_vc_x
     * @param prm_velo_vc_y
     * @param prm_velo_vc_z
     */
    void setVeloByVc(velo prm_velo_vc_x, velo prm_velo_vc_y, velo prm_velo_vc_z);

    /**
     * 移動速度を 0 に設定する .
     * 但し、移動速度下限 が 0 より大きい場合、
     * 無理やり移動速度下限の速度がX軸方向に設定される。
     */
    void setVeloZero();

    /**
     * 移動方向を座標、移動加速度を値で設定する .
     * 移動加速度下限～ 移動加速度上限 の範囲外を設定した場合、
     * 方向はそのままで、直近の範囲内に納められて設定される。
     * @param prm_tx 移動方向X座標(または、ターゲットの方向ベクトルX座標)
     * @param prm_ty 移動方向Y座標(または、ターゲットの方向ベクトルY座標)
     * @param prm_tz 移動方向Z座標(または、ターゲットの方向ベクトルZ座標)
     * @param prm_acce 移動加速度
     */
    void setAcceTwd(coord prm_tx, coord prm_ty, coord prm_tz, acce prm_acce);

    /**
     * XYZ軸ベクトル成分で、移動加速度を設定する .
     * 移動加速度下限～ 移動加速度上限 の範囲外を設定した場合、
     * 方向はそのままで、直近の範囲内に納められて設定される。
     * したがって、自身から目標物への方向ベクトルを渡すと、うまい具合にホーミング軌道になります。
     * @param prm_acce_vc_x 移動加速度X軸成分(または、ターゲットの方向ベクトルX成分)
     * @param prm_acce_vc_y 移動加速度Y軸成分(または、ターゲットの方向ベクトルY成分)
     * @param prm_acce_vc_z 移動加速度Z軸成分(または、ターゲットの方向ベクトルZ成分)
     */
    void setAcceByVc(acce prm_acce_vc_x, acce prm_acce_vc_y, acce prm_acce_vc_z);

    /**
     * 移動加速度を 0 に設定する .
     * 但し、移動加速度下限 が 0 より大きい場合、
     * 無理やり移動加速度下限の速度がX軸方向に設定される。
     */
    void setAcceZero();

    /**
     * 駕籠(平行移動支援)が振る舞う .
     * 駕籠(平行移動支援)機能を利用する場合は、このメソッドを毎フレーム呼び出し実行してください。<BR>
     * 逆に駕籠(平行移動支援)を必要としない場合は、このメソッドを呼び出さないことで、パフォーマンスに影響を与えません。<BR>
     */
    virtual void behave();

    virtual ~NaviVehicle();
};

}
#endif /*GGAF_DX_NAVIVEHICLE_H_*/

