#ifndef GGAF_DX_COORDVEHICLE_H_
#define GGAF_DX_COORDVEHICLE_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "ActorVehicle.h"

#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * アクターの移動支援、平行移動車両((X,Y,Z軸のプロッタ的な動作) .
 * GeometricActor のメンバの<BR>
 *  _x, _y, _z  ・・・ アクターの座標<BR>
 * を、各成分毎に簡単に操作するために作成。<BR>
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class CoordVehicle : public ActorVehicle {

public:
    /** [r/w]X軸方向移動速度 */
    velo _velo_x;
    /** [r/w]X軸方向移動速度上限 */
    velo _top_velo_x;
    /** [r/w]X軸方向移動速度下限 */
    velo _bottom_velo_x;
    /** [r/w]X軸方向移動加速度 */
    acce _acce_x;
    /** [r/w]X軸方向移動加速度上限*/
    acce _top_acce_x;
    /** [r/w]X軸方向移動加速度下限*/
    acce _bottom_acce_x;
    /** [r/w]Y軸方向移動速度 */
    velo _velo_y;
    /** [r/w]Y軸方向移動速度上限 */
    velo _top_velo_y;
    /** [r/w]Y軸方向移動速度下限 */
    velo _bottom_velo_y;
    /** [r/w]Y軸方向移動加速度 */
    acce _acce_y;
    /** [r/w]Y軸方向移動加速度上限*/
    acce _top_acce_y;
    /** [r/w]Y軸方向移動加速度下限*/
    acce _bottom_acce_y;
    /** [r/w]Z軸方向移動速度 */
    velo _velo_z;
    /** [r/w]Z軸方向移動速度上限 */
    velo _top_velo_z;
    /** [r/w]Z軸方向移動速度下限 */
    velo _bottom_velo_z;
    /** [r/w]Z軸方向移動加速度 */
    acce _acce_z;
    /** [r/w]Z軸方向移動加速度上限*/
    acce _top_acce_z;
    /** [r/w]Z軸方向移動加速度下限*/
    acce _bottom_acce_z;

    coord _grv_mv_target_x;
    coord _grv_mv_target_y;
    coord _grv_mv_target_z;
    const GeometricActor* _grv_mv_pActor_target;
    velo _grv_mv_max_velo;
    acce _grv_mv_acce;
    coord _grv_mv_stop_renge;
    bool _grv_mv_flg;
    /** [r]駕籠の助手 */
    CoordVehicleAssistant* _pAsstMv;

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  駕籠に乗るActor
     */
    explicit CoordVehicle(GeometricActor* prm_pActor);

    /**
     * 駕籠の助手(滑らか移動担当)を取得 .
     * @return 駕籠の助手
     */
    CoordVehicleAssistant* asst();

    int dot(int prm_vX, int prm_vY, int prm_vZ);

    /**
     * X軸方向移動速度設定 .
     * @param prm_velo_x X軸方向移動速度
     */
    void setVeloX(velo prm_velo_x);

    /**
     * X軸方向移動速度加算 .
     * @param prm_velo_x X軸方向移動速度差分
     */
    void addVeloX(velo prm_velo_x);

    /**
     * X軸方向移動速度の上限下限を強制 .
     * @param prm_velo_x01 速度１
     * @param prm_velo_x02 速度２
     */
    void forceVeloXRange(velo prm_velo_x01, velo prm_velo_x02);

    /**
     * X軸方向移動加速度設定 .
     * @param prm_acce_x X軸方向移動加速度
     */
    void setAcceX(acce prm_acce_x);

    /**
     * X軸方向移動加速度加算 .
     * @param prm_acce_x X軸方向移動加速度差分
     */
    void addAcceX(acce prm_acce_x);

    /**
     * X軸方向移動加速度の上限下限を強制 .
     * @param prm_acce_x01 加速度１
     * @param prm_acce_x02 加速度２
     */
    void forceAcceXRange(acce prm_acce_x01, acce prm_acce_x02);

    /**
     * Y軸方向移動速度設定 .
     * @param prm_velo_y Y軸方向移動速度
     */
    void setVeloY(velo prm_velo_y);

    /**
     * Y軸方向移動速度加算 .
     * @param prm_velo_y Y軸方向移動速度差分
     */
    void addVeloY(velo prm_velo_y);

    /**
     * Y軸方向移動速度の上限下限を強制 .
     * @param prm_velo_y01 速度１
     * @param prm_velo_y02 速度２
     */
    void forceVeloYRange(velo prm_velo_y01, velo prm_velo_y02);

    /**
     * Y軸方向移動加速度設定 .
     * @param prm_acce_y Y軸方向移動加速度
     */
    void setAcceY(acce prm_acce_y);

    /**
     * Y軸方向移動加速度加算 .
     * @param prm_acce_y Y軸方向移動加速度差分
     */
    void addAcceY(acce prm_acce_y);

    /**
     * Y軸方向移動加速度の上限下限を強制 .
     * @param prm_acce_y01 加速度１
     * @param prm_acce_y02 加速度２
     */
    void forceAcceYRange(acce prm_acce_y01, acce prm_acce_y02);

    /**
     * Z軸方向移動速度設定 .
     * @param prm_velo_z Z軸方向移動速度
     */
    void setVeloZ(velo prm_velo_z);

    /**
     * Z軸方向移動速度加算 .
     * @param prm_velo_z Z軸方向移動速度差分
     */
    void addVeloZ(velo prm_velo_z);

    /**
     * Z軸方向移動速度の上限下限を強制 .
     * @param prm_velo_z01 速度１
     * @param prm_velo_z02 速度２
     */
    void forceVeloZRange(velo prm_velo_z01, velo prm_velo_z02);

    /**
     * Z軸方向移動加速度設定 .
     * @param prm_acce_z Z軸方向移動加速度
     */
    void setAcceZ(acce prm_acce_z);

    /**
     * Z軸方向移動加速度加算 .
     * @param prm_acce_z Z軸方向移動加速度差分
     */
    void addAcceZ(acce prm_acce_z);

    /**
     * Z軸方向移動加速度の上限下限を強制 .
     * @param prm_acce_z01 加速度１
     * @param prm_acce_z02 加速度２
     */
    void forceAcceZRange(acce prm_acce_z01, acce prm_acce_z02);

    /**
     * X軸Y軸Z軸方向の移動速度の上限下限を強制 .
     * @param prm_velo_vxyz_mv01 速度1
     * @param prm_velo_vxyz_mv02 速度2
     */
    void forceVeloXYZRange(velo prm_velo_vxyz_mv01, velo prm_velo_vxyz_mv02);

    /**
     * X軸Y軸Z軸方向の移動加速度の上限下限を強制 .
     * @param prm_acce_vxyz_mv01 加速度１
     * @param prm_acce_vxyz_mv02 加速度２
     */
    void forceAcceXYZRange(acce prm_acce_vxyz_mv01, acce prm_acce_vxyz_mv02);

    /**
     * X軸Y軸Z軸方向の移動速度を設定する。
     * @param prm_velo_x X軸方向移動速度
     * @param prm_velo_y Y軸方向移動速度
     * @param prm_velo_z Z軸方向移動速度
     */
    void setVeloXYZ(velo prm_velo_x, velo prm_velo_y, velo prm_velo_z);

    /**
     * X軸Y軸Z軸方向の移動速度を目標角度と移動速度で設定する。
     * @param prm_rz 目標Z軸回転アングル値
     * @param prm_ry 目標Y軸回転アングル値
     * @param prm_velo 移動速度
     */
    void setVeloXYZTwd(angle prm_rz, angle prm_ry, velo prm_velo);

    /**
     * X軸Y軸Z軸方向の移動速度を目標座標と移動速度で設定する。
     * @param prm_tx 目標X座標
     * @param prm_ty 目標Y座標
     * @param prm_tz 目標Z座標
     * @param prm_velo 移動速度
     */
    void setVeloXYZTwd(coord prm_tx, coord prm_ty, coord prm_tz, velo prm_velo);

    /**
     * X軸Y軸Z軸方向の移動速度を目標アクターと移動速度で設定する。
     * @param prm_pTargetActor 目標アクター
     * @param prm_velo 移動速度
     */
    void setVeloXYZTwd(const GeometricActor* prm_pTargetActor, velo prm_velo) {
        setVeloXYZTwd(prm_pTargetActor->_x, prm_pTargetActor->_y, prm_pTargetActor->_z, prm_velo);
    }

    /**
     * X軸Y軸Z軸方向の移動加速度を設定する。
     * @param prm_acce_x X軸方向移動加速度
     * @param prm_acce_y Y軸方向移動加速度
     * @param prm_acce_z Z軸方向移動加速度
     */
    void setAcceXYZ(acce prm_acce_x, acce prm_acce_y, acce prm_acce_z);

    /**
     * 移動加速度を、「目標到達速度」「費やす時間」により設定 .
     * <pre><code>
     *
     *    速度(v)
     *     ^        a:加速度（_acc_mv に設定される)
     *     |        D:移動距離 （戻り値）
     *     |       V0:現時点の速度（= 現在の _velo_mv が使用される）
     *     |       Vt:目標到達速度（引数）
     *     |       Te:目標到達速度に達した時の時間（引数）
     *   Vt|........
     *     |      ／|
     *     |    ／  |
     *     |  ／    |   斜辺の傾きa
     *     |／      |
     *   V0|    D   |
     *     |        |
     *   --+--------+---> 時間(tフレーム)
     *   0 |        Te
     *
     *    a = (Vt-V0) / Te
     * </code></pre>
     * 上図のような状態を想定し、目標到達速度(Vt)と、その到達時間(Te) から、加速度(a)を計算し設定している。<BR>
     * 移動距離(D)は、パラメータにより変化するため指定不可。<BR>
     * @param prm_target_frames 費やす時間(Te)
     * @param prm_target_velo   目標到達速度(Vt)
     * @return 移動距離(D)
     */
    coord setAcceXByT(frame prm_target_frames, velo prm_target_velo);
    coord setAcceYByT(frame prm_target_frames, velo prm_target_velo);
    coord setAcceZByT(frame prm_target_frames, velo prm_target_velo);
    void setAcceXYZByT(frame prm_target_frames, velo prm_target_velo) {
        setAcceXByT(prm_target_frames, prm_target_velo);
        setAcceYByT(prm_target_frames, prm_target_velo);
        setAcceZByT(prm_target_frames, prm_target_velo);
    }


    /**
     * X軸Y軸Z軸方向の移動速度を 0 に設定する。
     */
    void setXYZZero() {
        _velo_x = _velo_y = _velo_z = 0;
    }

    /**
     * X軸Y軸Z軸方向の移動加速度を 0 に設定する。
     */
    void setAcceXYZZero() {
        _acce_x = _acce_y = _acce_z = 0;
    }

    /**
     * 重力により物体が引き寄せられるかような感じの動きみたいな感じっぽいのをやめる .
     */
    void stopGravitationMvSequence() {
        _grv_mv_flg = false;
    }

    /**
     * 重力により物体が引き寄せられるかような感じの動きみたいな感じっぽいの最中かどうか
     * @return true:最中/false:そうでない
     */
    bool isGravitationMvSequence() {
        return _grv_mv_flg;
    }

    /**
     * 重力により物体が引き寄せられるかような感じの動きみたいな感じっぽいのを実行 .
     * 【アルゴリズム概要】<BR>
     * X,Y,Zの各軸の座標それぞれに、目標の座標とアクターの座標差分を取り、<BR>
     * その正負により、加速度を加算減算させて目標に近づこうとします。<BR>
     * 但し、このままであると、衛生が旋回するが如く、永遠に目標の座標に到達しません。<BR>
     * そこで、目標の座標X,Y,Zの各軸と、アクターの座標差が<BR>
     * -1*prm_stop_renge ～ prm_stop_renge<BR>
     * の範囲内になった場合、速度を緩和(減速)し、目標の座標に更に近づこうします。<BR>
     * 各軸それぞれ、目標に近づくと軸速度は0に近づく、という訳で重力とは物理的に動きが異なります。<BR>
     * でも、重力で引き付けるかのような効果を期待出来ます。<BR>
     * 数学的には、目標の座標に限りなく近づくだけで、目標座標と一致することはありません。<BR>
     * @param prm_tx 引き寄せられて到達する目標のX座標(絶対座標)
     * @param prm_ty 引き寄せられて到達する目標のY座標(絶対座標)
     * @param prm_tz 引き寄せられて到達する目標のZ座標(絶対座標)
     * @param prm_max_velo 引き寄せられている最中の各軸(XYZ)の軸移動速度上限値
     * @param prm_acce 引き寄せられている最中の各軸(XYZ)の軸移動加速度上限値
     * @param prm_stop_renge 速度が抑えられる目標座標からの各軸の距離
     */
    void execGravitationMvSequenceTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                                      velo prm_max_velo,
                                      acce prm_acce,
                                      coord prm_stop_renge);

    /**
     * 重力により物体が引き寄せられるかような感じの動きみたいな感じっぽいの目標座標を更新設定 .
     * @param prm_tx 引き寄せられて到達する目標のX座標
     * @param prm_ty 引き寄せられて到達する目標のY座標
     * @param prm_tz 引き寄せられて到達する目標のZ座標
     */
    void setGravitationTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
        _grv_mv_target_x = prm_tx;
        _grv_mv_target_y = prm_ty;
        _grv_mv_target_z = prm_tz;
        _grv_mv_pActor_target = nullptr;
    }

    /**
     * 重力により物体が引き寄せられるかような感じの動きみたいな感じっぽいのを実行 .
     * 説明は、
     * execGravitationMvSequenceTwd(coord,coord,coord,velo,acce,int)
     * を参照。
     * @param prm_pActor_target 引き寄せられて到達する目標座標となるアクター
     * @param prm_max_velo 引き寄せられている最中の各軸(XYZ)の軸移動速度上限値
     * @param prm_acce 引き寄せられている最中の各軸(XYZ)の軸移動加速度上限値
     * @param prm_stop_renge 速度が抑えられる目標座標からの各軸の距離
     */
    void execGravitationMvSequenceTwd(const GeometricActor* prm_pActor_target,
                                      velo prm_max_velo,
                                      acce prm_acce,
                                      coord prm_stop_renge);
    /**
     * 重力により物体が引き寄せられるかような感じの動きみたいな感じっぽいのを実行 .
     * 説明は、
     * execGravitationMvSequenceTwd(coord,coord,coord,velo,acce,int)
     * を参照。
     * @param prm_pActor_target 引き寄せられて到達する目標座標となるアクター
     * @param prm_local_offset_tx 目標X座標位置の補正。prm_pActor_targetからの相対座標を設定する。
     * @param prm_local_offset_ty 目標Y座標位置の補正。prm_pActor_targetからの相対座標を設定する。
     * @param prm_local_offset_tz 目標Z座標位置の補正。prm_pActor_targetからの相対座標を設定する。
     * @param prm_max_velo 引き寄せられている最中の各軸(XYZ)の軸移動速度上限値
     * @param prm_acce 引き寄せられている最中の各軸(XYZ)の軸移動加速度上限値
     * @param prm_stop_renge 速度が抑えられる目標座標からの各軸の距離
     */
    void execGravitationMvSequenceTwd(const GeometricActor* prm_pActor_target,
                                      coord prm_local_offset_tx, coord prm_local_offset_ty, coord prm_local_offset_tz,
                                      velo prm_max_velo,
                                      acce prm_acce,
                                      coord prm_stop_renge);


    /**
     * 重力により物体が引き寄せられるかような感じの動きみたいな感じっぽいの目標座標を更新設定 .
     * @param prm_pActor_target 引き寄せられて到達する目標座標となるアクター
     */
    void setGravitationTwd(const GeometricActor* prm_pActor_target) {
        _grv_mv_target_x = 0;
        _grv_mv_target_y = 0;
        _grv_mv_target_z = 0;
        _grv_mv_pActor_target = prm_pActor_target;
    }

    /**
     * 駕籠(平行移動支援)の仕事を引継ぐ .
     * 他の CoordVehicle オブジェクトを状態を自身に引継ぐ .
     * @param prm_pAxsMver 引継元
     */
    void takeoverFrom(CoordVehicle* const prm_pAxsMver);

    /**
     * CoordVehicleによるアクター移動を停止する。
     */
    void stop();

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

    virtual ~CoordVehicle();
};

}
#endif /*GGAF_DX_COORDVEHICLE_H_*/

