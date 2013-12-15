#ifndef GGAFDXCORE_GGAFDXAXESMOVER_H_
#define GGAFDXCORE_GGAFDXAXESMOVER_H_
#include "jp/ggaf/core/GgafObject.h"

namespace GgafDxCore {

/**
 * 平行移動支援 .
 * GgafDxGeometricActor のメンバの<BR>
 *  _x, _y, _z  ・・・ アクターの座標<BR>
 * を、各成分毎に簡単に操作するために作成。<BR>
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class GgafDxAxesMover : public GgafCore::GgafObject {

public:
    /** [r]対象アクター */
    GgafDxGeometricActor* const _pActor;
    /** [r/w]X軸方向移動速度 */
    velo _veloVxMv;
    /** [r/w]X軸方向移動速度上限 */
    velo _veloTopVxMv;
    /** [r/w]X軸方向移動速度下限 */
    velo _veloBottomVxMv;
    /** [r/w]X軸方向移動加速度 */
    acce _acceVxMv;
    /** [r/w]X軸方向移動加速度上限*/
    acce _acceTopVxMv;
    /** [r/w]X軸方向移動加速度下限*/
    acce _acceBottomVxMv;
    /** [r/w]Y軸方向移動速度 */
    velo _veloVyMv;
    /** [r/w]Y軸方向移動速度上限 */
    velo _veloTopVyMv;
    /** [r/w]Y軸方向移動速度下限 */
    velo _veloBottomVyMv;
    /** [r/w]Y軸方向移動加速度 */
    acce _acceVyMv;
    /** [r/w]Y軸方向移動加速度上限*/
    acce _acceTopVyMv;
    /** [r/w]Y軸方向移動加速度下限*/
    acce _acceBottomVyMv;
    /** [r/w]Z軸方向移動速度 */
    velo _veloVzMv;
    /** [r/w]Z軸方向移動速度上限 */
    velo _veloTopVzMv;
    /** [r/w]Z軸方向移動速度下限 */
    velo _veloBottomVzMv;
    /** [r/w]Z軸方向移動加速度 */
    acce _acceVzMv;
    /** [r/w]Z軸方向移動加速度上限*/
    acce _acceTopVzMv;
    /** [r/w]Z軸方向移動加速度下限*/
    acce _acceBottomVzMv;

    coord _gravitation_mv_seq_target_x;
    coord _gravitation_mv_seq_target_y;
    coord _gravitation_mv_seq_target_z;
    GgafDxGeometricActor* _gravitation_mv_seq_pActor_target;
    velo _gravitation_mv_seq_max_velo;
    acce _gravitation_mv_seq_acce;
    coord _gravitation_mv_seq_stop_renge;
    bool _gravitation_mv_seq_flg;

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用Actor
     */
    GgafDxAxesMover(GgafDxGeometricActor* prm_pActor);

    int dot(int prm_vX, int prm_vY, int prm_vZ);
    /**
     * X軸方向移動速度設定 .
     * @param prm_veloVxMv X軸方向移動速度
     */
    void setVxMvVelo(velo prm_veloVxMv);

    /**
     * X軸方向移動速度加算 .
     * @param prm_veloVxMv X軸方向移動速度差分
     */
    void addVxMvVelo(velo prm_veloVxMv);

    /**
     * X軸方向移動速度の上限下限を強制 .
     * @param prm_veloVxMv01 速度１
     * @param prm_veloVxMv02 速度２
     */
    void forceVxMvVeloRange(velo prm_veloVxMv01, velo prm_veloVxMv02);

    /**
     * X軸方向移動加速度設定 .
     * @param prm_acceVxMv X軸方向移動加速度
     */
    void setVxMvAcce(acce prm_acceVxMv);

    /**
     * X軸方向移動加速度加算 .
     * @param prm_acceVxMv X軸方向移動加速度差分
     */
    void addVxMvAcce(acce prm_acceVxMv);

    /**
     * X軸方向移動加速度の上限下限を強制 .
     * @param prm_acceVxMv01 加速度１
     * @param prm_acceVxMv02 加速度２
     */
    void forceVxMvAcceRange(acce prm_acceVxMv01, acce prm_acceVxMv02);

    /**
     * Y軸方向移動速度設定 .
     * @param prm_veloVyMv Y軸方向移動速度
     */
    void setVyMvVelo(velo prm_veloVyMv);

    /**
     * Y軸方向移動速度加算 .
     * @param prm_veloVyMv Y軸方向移動速度差分
     */
    void addVyMvVelo(velo prm_veloVyMv);

    /**
     * Y軸方向移動速度の上限下限を強制 .
     * @param prm_veloVyMv01 速度１
     * @param prm_veloVyMv02 速度２
     */
    void forceVyMvVeloRange(velo prm_veloVyMv01, velo prm_veloVyMv02);

    /**
     * Y軸方向移動加速度設定 .
     * @param prm_acceVyMv Y軸方向移動加速度
     */
    void setVyMvAcce(acce prm_acceVyMv);

    /**
     * Y軸方向移動加速度加算 .
     * @param prm_acceVyMv Y軸方向移動加速度差分
     */
    void addVyMvAcce(acce prm_acceVyMv);

    /**
     * Y軸方向移動加速度の上限下限を強制 .
     * @param prm_acceVyMv01 加速度１
     * @param prm_acceVyMv02 加速度２
     */
    void forceVyMvAcceRange(acce prm_acceVyMv01, acce prm_acceVyMv02);

    /**
     * Z軸方向移動速度設定 .
     * @param prm_veloVzMv Z軸方向移動速度
     */
    void setVzMvVelo(velo prm_veloVzMv);

    /**
     * Z軸方向移動速度加算 .
     * @param prm_veloVzMv Z軸方向移動速度差分
     */
    void addVzMvVelo(velo prm_veloVzMv);

    /**
     * Z軸方向移動速度の上限下限を強制 .
     * @param prm_veloVzMv01 速度１
     * @param prm_veloVzMv02 速度２
     */
    void forceVzMvVeloRange(velo prm_veloVzMv01, velo prm_veloVzMv02);

    /**
     * Z軸方向移動加速度設定 .
     * @param prm_acceVzMv Z軸方向移動加速度
     */
    void setVzMvAcce(acce prm_acceVzMv);

    /**
     * Z軸方向移動加速度加算 .
     * @param prm_acceVzMv Z軸方向移動加速度差分
     */
    void addVzMvAcce(acce prm_acceVzMv);

    /**
     * Z軸方向移動加速度の上限下限を強制 .
     * @param prm_acceVzMv01 加速度１
     * @param prm_acceVzMv02 加速度２
     */
    void forceVzMvAcceRange(acce prm_acceVzMv01, acce prm_acceVzMv02);

    /**
     * X軸Y軸Z軸方向の移動速度の上限下限を強制 .
     * @param prm_veloVxyzMv01 速度1
     * @param prm_veloVxyzMv02 速度2
     */
    void forceVxyzMvVeloRange(velo prm_veloVxyzMv01, velo prm_veloVxyzMv02);

    /**
     * X軸Y軸Z軸方向の移動加速度の上限下限を強制 .
     * @param prm_acceVxyzMv01 加速度１
     * @param prm_acceVxyzMv02 加速度２
     */
    void forceVxyzMvAcceRange(acce prm_acceVxyzMv01, acce prm_acceVxyzMv02);

    /**
     * X軸Y軸Z軸方向の移動速度を設定する。
     * @param prm_veloVxMv X軸方向移動速度
     * @param prm_veloVyMv Y軸方向移動速度
     * @param prm_veloVzMv Z軸方向移動速度
     */
    void setVxyzMvVelo(velo prm_veloVxMv, velo prm_veloVyMv, velo prm_veloVzMv);

    /**
     * X軸Y軸Z軸方向の移動加速度を設定する。
     * @param prm_acceVxMv X軸方向移動加速度
     * @param prm_acceVyMv Y軸方向移動加速度
     * @param prm_acceVzMv Z軸方向移動加速度
     */
    void setVxyzMvAcce(acce prm_acceVxMv, acce prm_acceVyMv, acce prm_acceVzMv);

    /**
     * X軸Y軸Z軸方向の移動速度を 0 に設定する。
     */
    void setZeroVxyzMvVelo() {
        _veloVxMv = _veloVyMv = _veloVzMv = 0;
    }

    /**
     * X軸Y軸Z軸方向の移動加速度を 0 に設定する。
     */
    void setZeroVxyzMvAcce() {
        _acceVxMv = _acceVyMv = _acceVzMv = 0;
    }

    /**
     * 重力により物体が引き寄せられるかような感じの動きみたいな感じっぽいのをやめる .
     */
    void stopGravitationMvSequence() {
        _gravitation_mv_seq_flg = false;
    }

    /**
     * 重力により物体が引き寄せられるかような感じの動きみたいな感じっぽいの最中かどうか
     * @return true:最中/false:そうでない
     */
    bool isGravitationMvSequence() {
        return _gravitation_mv_seq_flg;
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
     * @param prm_tx 引き寄せられて到達する目標のX座標
     * @param prm_ty 引き寄せられて到達する目標のY座標
     * @param prm_tz 引き寄せられて到達する目標のZ座標
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
        _gravitation_mv_seq_target_x = prm_tx;
        _gravitation_mv_seq_target_y = prm_ty;
        _gravitation_mv_seq_target_z = prm_tz;
        _gravitation_mv_seq_pActor_target = nullptr;
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
    void execGravitationMvSequenceTwd(GgafDxGeometricActor* prm_pActor_target,
                                      velo prm_max_velo,
                                      acce prm_acce,
                                      coord prm_stop_renge);

    /**
     * 重力により物体が引き寄せられるかような感じの動きみたいな感じっぽいの目標座標を更新設定 .
     * @param prm_pActor_target 引き寄せられて到達する目標座標となるアクター
     */
    void setGravitationTwd(GgafDxGeometricActor* prm_pActor_target) {
        _gravitation_mv_seq_target_x = 0;
        _gravitation_mv_seq_target_y = 0;
        _gravitation_mv_seq_target_z = 0;
        _gravitation_mv_seq_pActor_target = prm_pActor_target;
    }

    /**
     * 平行移動支援の仕事を引継ぐ .
     * 他の GgafDxAxesMover オブジェクトを状態を自身に引継ぐ .
     * @param prmpAxsMver_ 引継元
     */
    void takeoverMvFrom(GgafDxAxesMover* const prmpAxsMver_);

    void resetMv();

    /**
     * 平行移動支援が振る舞う .
     * 平行移動支援機能を利用する場合は、このメソッドを毎フレーム呼び出し実行してください。<BR>
     * 逆に平行移動支援を必要としない場合は、このメソッドを呼び出さないことで、パフォーマンスに影響を与えません。<BR>
     */
    virtual void behave();

    virtual ~GgafDxAxesMover();
};

}
#endif /*GGAFDXCORE_GGAFDXAXESMOVER_H_*/

