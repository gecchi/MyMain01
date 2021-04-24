#ifndef GGAF_DX_GEODRIVER_H_
#define GGAF_DX_GEODRIVER_H_
#include "GgafDxCommonHeader.h"
#include "ActorDriver.h"

#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * アクターを乗せる駕籠（アクターの平行移動支援） .
 * GeometricActor のメンバの<BR>
 *  _x, _y, _z  ・・・ アクターの座標<BR>
 * を、各成分毎に簡単に操作するために作成。<BR>
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class GeoDriver : public ActorDriver {

public:
    /** [r]対象アクター */
    //GeometricActor* const _pActor;
    /** [r/w]X軸方向移動速度 */
    velo _velo_vx_mv;
    /** [r/w]X軸方向移動速度上限 */
    velo _top_velo_vx_mv;
    /** [r/w]X軸方向移動速度下限 */
    velo _bottom_velo_vx_mv;
    /** [r/w]X軸方向移動加速度 */
    acce _acce_vx_mv;
    /** [r/w]X軸方向移動加速度上限*/
    acce _top_acce_vx_mv;
    /** [r/w]X軸方向移動加速度下限*/
    acce _bottom_acce_vx_mv;
    /** [r/w]Y軸方向移動速度 */
    velo _velo_vy_mv;
    /** [r/w]Y軸方向移動速度上限 */
    velo _top_velo_vy_mv;
    /** [r/w]Y軸方向移動速度下限 */
    velo _bottom_velo_vy_mv;
    /** [r/w]Y軸方向移動加速度 */
    acce _acce_vy_mv;
    /** [r/w]Y軸方向移動加速度上限*/
    acce _top_acce_vy_mv;
    /** [r/w]Y軸方向移動加速度下限*/
    acce _bottom_acce_vy_mv;
    /** [r/w]Z軸方向移動速度 */
    velo _velo_vz_mv;
    /** [r/w]Z軸方向移動速度上限 */
    velo _top_velo_vz_mv;
    /** [r/w]Z軸方向移動速度下限 */
    velo _bottom_velo_vz_mv;
    /** [r/w]Z軸方向移動加速度 */
    acce _acce_vz_mv;
    /** [r/w]Z軸方向移動加速度上限*/
    acce _top_acce_vz_mv;
    /** [r/w]Z軸方向移動加速度下限*/
    acce _bottom_acce_vz_mv;

    coord _grv_mv_target_x;
    coord _grv_mv_target_y;
    coord _grv_mv_target_z;
    const GeometricActor* _grv_mv_pActor_target;
    velo _grv_mv_max_velo;
    acce _grv_mv_acce;
    coord _grv_mv_stop_renge;
    bool _grv_mv_flg;
    /** [r]駕籠の助手A */
    GeoDriverAssistantA* _pAsstMv;

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  駕籠に乗るActor
     */
    explicit GeoDriver(GeometricActor* prm_pActor);

    /**
     * 駕籠の助手(滑らか移動担当)を取得 .
     * @return 駕籠の助手
     */
    GeoDriverAssistantA* asst();

    int dot(int prm_vX, int prm_vY, int prm_vZ);
    /**
     * X軸方向移動速度設定 .
     * @param prm_velo_vx_mv X軸方向移動速度
     */
    void setVxMvVelo(velo prm_velo_vx_mv);

    /**
     * X軸方向移動速度加算 .
     * @param prm_velo_vx_mv X軸方向移動速度差分
     */
    void addVxMvVelo(velo prm_velo_vx_mv);

    /**
     * X軸方向移動速度の上限下限を強制 .
     * @param prm_velo_vx_mv01 速度１
     * @param prm_velo_vx_mv02 速度２
     */
    void forceVxMvVeloRange(velo prm_velo_vx_mv01, velo prm_velo_vx_mv02);

    /**
     * X軸方向移動加速度設定 .
     * @param prm_acce_vx_mv X軸方向移動加速度
     */
    void setVxMvAcce(acce prm_acce_vx_mv);

    /**
     * X軸方向移動加速度加算 .
     * @param prm_acce_vx_mv X軸方向移動加速度差分
     */
    void addVxMvAcce(acce prm_acce_vx_mv);

    /**
     * X軸方向移動加速度の上限下限を強制 .
     * @param prm_acce_vx_mv01 加速度１
     * @param prm_acce_vx_mv02 加速度２
     */
    void forceVxMvAcceRange(acce prm_acce_vx_mv01, acce prm_acce_vx_mv02);

    /**
     * Y軸方向移動速度設定 .
     * @param prm_velo_vy_mv Y軸方向移動速度
     */
    void setVyMvVelo(velo prm_velo_vy_mv);

    /**
     * Y軸方向移動速度加算 .
     * @param prm_velo_vy_mv Y軸方向移動速度差分
     */
    void addVyMvVelo(velo prm_velo_vy_mv);

    /**
     * Y軸方向移動速度の上限下限を強制 .
     * @param prm_velo_vy_mv01 速度１
     * @param prm_velo_vy_mv02 速度２
     */
    void forceVyMvVeloRange(velo prm_velo_vy_mv01, velo prm_velo_vy_mv02);

    /**
     * Y軸方向移動加速度設定 .
     * @param prm_acce_vy_mv Y軸方向移動加速度
     */
    void setVyMvAcce(acce prm_acce_vy_mv);

    /**
     * Y軸方向移動加速度加算 .
     * @param prm_acce_vy_mv Y軸方向移動加速度差分
     */
    void addVyMvAcce(acce prm_acce_vy_mv);

    /**
     * Y軸方向移動加速度の上限下限を強制 .
     * @param prm_acce_vy_mv01 加速度１
     * @param prm_acce_vy_mv02 加速度２
     */
    void forceVyMvAcceRange(acce prm_acce_vy_mv01, acce prm_acce_vy_mv02);

    /**
     * Z軸方向移動速度設定 .
     * @param prm_velo_vz_mv Z軸方向移動速度
     */
    void setVzMvVelo(velo prm_velo_vz_mv);

    /**
     * Z軸方向移動速度加算 .
     * @param prm_velo_vz_mv Z軸方向移動速度差分
     */
    void addVzMvVelo(velo prm_velo_vz_mv);

    /**
     * Z軸方向移動速度の上限下限を強制 .
     * @param prm_velo_vz_mv01 速度１
     * @param prm_velo_vz_mv02 速度２
     */
    void forceVzMvVeloRange(velo prm_velo_vz_mv01, velo prm_velo_vz_mv02);

    /**
     * Z軸方向移動加速度設定 .
     * @param prm_acce_vz_mv Z軸方向移動加速度
     */
    void setVzMvAcce(acce prm_acce_vz_mv);

    /**
     * Z軸方向移動加速度加算 .
     * @param prm_acce_vz_mv Z軸方向移動加速度差分
     */
    void addVzMvAcce(acce prm_acce_vz_mv);

    /**
     * Z軸方向移動加速度の上限下限を強制 .
     * @param prm_acce_vz_mv01 加速度１
     * @param prm_acce_vz_mv02 加速度２
     */
    void forceVzMvAcceRange(acce prm_acce_vz_mv01, acce prm_acce_vz_mv02);

    /**
     * X軸Y軸Z軸方向の移動速度の上限下限を強制 .
     * @param prm_velo_vxyz_mv01 速度1
     * @param prm_velo_vxyz_mv02 速度2
     */
    void forceVxyzMvVeloRange(velo prm_velo_vxyz_mv01, velo prm_velo_vxyz_mv02);

    /**
     * X軸Y軸Z軸方向の移動加速度の上限下限を強制 .
     * @param prm_acce_vxyz_mv01 加速度１
     * @param prm_acce_vxyz_mv02 加速度２
     */
    void forceVxyzMvAcceRange(acce prm_acce_vxyz_mv01, acce prm_acce_vxyz_mv02);

    /**
     * X軸Y軸Z軸方向の移動速度を設定する。
     * @param prm_velo_vx_mv X軸方向移動速度
     * @param prm_velo_vy_mv Y軸方向移動速度
     * @param prm_velo_vz_mv Z軸方向移動速度
     */
    void setVxyzMvVelo(velo prm_velo_vx_mv, velo prm_velo_vy_mv, velo prm_velo_vz_mv);

    /**
     * X軸Y軸Z軸方向の移動速度を目標角度と移動速度で設定する。
     * @param prm_rz 目標Z軸回転アングル値
     * @param prm_ry 目標Y軸回転アングル値
     * @param prm_velo 移動速度
     */
    void setVxyzMvVeloTwd(angle prm_rz, angle prm_ry, velo prm_velo);

    /**
     * X軸Y軸Z軸方向の移動速度を目標座標と移動速度で設定する。
     * @param prm_tx 目標X座標
     * @param prm_ty 目標Y座標
     * @param prm_tz 目標Z座標
     * @param prm_velo 移動速度
     */
    void setVxyzMvVeloTwd(coord prm_tx, coord prm_ty, coord prm_tz, velo prm_velo);

    /**
     * X軸Y軸Z軸方向の移動速度を目標アクターと移動速度で設定する。
     * @param prm_pTargetActor 目標アクター
     * @param prm_velo 移動速度
     */
    void setVxyzMvVeloTwd(const GeometricActor* prm_pTargetActor, velo prm_velo) {
        setVxyzMvVeloTwd(prm_pTargetActor->_x, prm_pTargetActor->_y, prm_pTargetActor->_z, prm_velo);
    }

    /**
     * X軸Y軸Z軸方向の移動加速度を設定する。
     * @param prm_acce_vx_mv X軸方向移動加速度
     * @param prm_acce_vy_mv Y軸方向移動加速度
     * @param prm_acce_vz_mv Z軸方向移動加速度
     */
    void setVxyzMvAcce(acce prm_acce_vx_mv, acce prm_acce_vy_mv, acce prm_acce_vz_mv);



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
    coord setVxAcceByT(frame prm_target_frames, velo prm_target_velo);
    coord setVyAcceByT(frame prm_target_frames, velo prm_target_velo);
    coord setVzAcceByT(frame prm_target_frames, velo prm_target_velo);
    void setVxyzAcceByT(frame prm_target_frames, velo prm_target_velo) {
        setVxAcceByT(prm_target_frames, prm_target_velo);
        setVyAcceByT(prm_target_frames, prm_target_velo);
        setVzAcceByT(prm_target_frames, prm_target_velo);
    }


    /**
     * X軸Y軸Z軸方向の移動速度を 0 に設定する。
     */
    void setZeroVxyzMvVelo() {
        _velo_vx_mv = _velo_vy_mv = _velo_vz_mv = 0;
    }

    /**
     * X軸Y軸Z軸方向の移動加速度を 0 に設定する。
     */
    void setZeroVxyzMvAcce() {
        _acce_vx_mv = _acce_vy_mv = _acce_vz_mv = 0;
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
     * 他の GeoDriver オブジェクトを状態を自身に引継ぐ .
     * @param prm_pAxsMver 引継元
     */
    void takeoverMvFrom(GeoDriver* const prm_pAxsMver);

    /**
     * GeoDriverによるアクター移動を停止する。
     */
    void stopMv();

    /**
     * 速度、加速度をリセット、各上限下限を初期設定。
     */
    void resetMv();

    /**
     * 駕籠(平行移動支援)が振る舞う .
     * 駕籠(平行移動支援)機能を利用する場合は、このメソッドを毎フレーム呼び出し実行してください。<BR>
     * 逆に駕籠(平行移動支援)を必要としない場合は、このメソッドを呼び出さないことで、パフォーマンスに影響を与えません。<BR>
     */
    virtual void behave();

    virtual ~GeoDriver();
};

}
#endif /*GGAF_DX_GEODRIVER_H_*/

