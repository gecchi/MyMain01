#ifndef GGAFDXMVTRANSPORTER_H_
#define GGAFDXMVTRANSPORTER_H_
namespace GgafDxCore {


/**
 * 黒子B(黒衣B)  .
 * 黒子Bは舞台には見えないですが、演者(アクター)を持ち上げ、「平行移動」を行わせる世話人です。<BR>
 * 「平行移動」に特化しており、黒子Aの「方向移動」「向きの回転」とは専門分野が違います。<BR>
 * 黒子Aと黒子Bが協力すれば、かなり複雑な動きを演者に行わせることができます。
 * 演者一人につき、黒子Bが標準で一人付属しています。<BR>
 * <BR>
 * それはさて置き、つまり座標計算支援（共通化）クラスその２です。<BR>
 * GgafDxGeometricActor のメンバの<BR>
 *  _X, _Y, _Z  ・・・ アクターの座標<BR>
 * を、各成分毎に簡単に操作するために作成。<BR>
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class GgafDxKurokoB : public GgafCore::GgafObject {

public:
    /** 対象アクター */
    GgafDxGeometricActor* _pActor;

    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用Actor
     */
    GgafDxKurokoB(GgafDxGeometricActor* prm_pActor);

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


    coord _gravitation_mv_seq_target_X;
    coord _gravitation_mv_seq_target_Y;
    coord _gravitation_mv_seq_target_Z;
    GgafDxGeometricActor* _gravitation_mv_seq_pActor_target;
    velo _gravitation_mv_seq_max_velo;
    acce _gravitation_mv_seq_acce;
    coord _gravitation_mv_seq_stop_renge;
    bool _gravitation_mv_seq_flg;


    int dot(int prm_vX, int prm_vY, int prm_vZ);
    //virtual void behave();
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
     * @param prm_veloVxyzMv01 速度１
     * @param prm_veloVxyzMv02 速度１
     */
    void forceVxyzMvVeloRange(velo prm_veloVxyzMv01, velo prm_veloVxyzMv02);
    /**
     * X軸Y軸Z軸方向の移動加速度の上限下限を強制 .
     * @param prm_acceVxyzMv01 加速度１
     * @param prm_acceVxyzMv02 加速度２
     */
    void forceVxyzMvAcceRange(acce prm_acceVxyzMv01, acce prm_acceVxyzMv02);

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
     * 重力により物体が引き寄せられるかような感じの動きみたいな感じをやめる .
     */
    void stopGravitationMvSequence() {
        _gravitation_mv_seq_flg = false;
    }

    /**
     * 重力により物体が引き寄せられるかような感じの動きみたいな感じの最中かどうか
     * @return true:重力により物体が引き寄せられるかような感じの動きみたいな感じ中/false:そうでない
     */
    bool isGravitationMvSequence() {
        return _gravitation_mv_seq_flg;
    }

    /**
     * 重力により物体が引き寄せられるかような感じの動きみたいな感じを実行 .
     * 【アルゴリズム概要】<BR>
     * X,Y,Zの各軸の座標それぞれに、目標の座標とアクターの座標差分を取り、<BR>
     * その正負により、加速度を加算減算させて目標に近づこうとします。<BR>
     * 但し、このままであると、衛生が旋回するが如く、永遠に目標の座標に到達しません。<BR>
     * そこで、目標の座標X,Y,Zの各軸と、アクターの座標差が<BR>
     * -1*prm_stop_renge ～ prm_stop_renge<BR>
     * の範囲内になった場合、速度を緩和(減速)し、目標の座標に更に近づこうします。<BR>
     * 各軸それぞれ、目標に近づくと軸速度は0に近づく、という訳で重力とは根本的に動きが異なります。<BR>
     * 数学的には、目標の座標に限りなく近づくだけで、目標座標と一致することはありません。<BR>
     * @param prm_tX 引き寄せられて到達する目標のX座標
     * @param prm_tY 引き寄せられて到達する目標のY座標
     * @param prm_tZ 引き寄せられて到達する目標のZ座標
     * @param prm_max_velo 引き寄せられている最中の各軸(XYZ)の軸移動速度上限値
     * @param prm_acce 引き寄せられている最中の各軸(XYZ)の軸移動加速度上限値
     * @param prm_stop_renge 速度が抑えられる目標座標からの各軸の距離
     */
    void execGravitationMvSequence(coord prm_tX, coord prm_tY, coord prm_tZ,
                                   velo prm_max_velo,
                                   acce prm_acce,
                                   coord prm_stop_renge);

    /**
     * 重力により物体が引き寄せられるかような感じの動きみたいな感じを実行 .
     * 説明は、
     * execGravitationMvSequence(coord,coord,coord,velo,acce,int)
     * を参照。
     * @param prm_pActor_target 引き寄せられて到達する目標座標となるアクター
     * @param prm_max_velo 引き寄せられている最中の各軸(XYZ)の軸移動速度上限値
     * @param prm_acce 引き寄せられている最中の各軸(XYZ)の軸移動加速度上限値
     * @param prm_stop_renge 速度が抑えられる目標座標からの各軸の距離
     */
    void execGravitationMvSequence(GgafDxGeometricActor* prm_pActor_target,
                                   velo prm_max_velo,
                                   acce prm_acce,
                                   coord prm_stop_renge);

    /**
     * 黒子Bの仕事を引継ぐ .
     * 他の GgafDxKurokoB オブジェクトを状態を自身に引継ぐ .
     * @param prm_pKurokoB 引継元
     */
    void takeoverMvFrom(GgafDxKurokoB* prm_pKurokoB);


    void resetMv();

    /**
     * 黒子Bが振る舞う .
     * 黒子B機能を利用する場合は、このメソッドを毎フレーム呼び出し実行してください。<BR>
     * 逆に黒子Bを必要としない場合は、このメソッドを呼び出さないことで、パフォーマンスに影響を与えません。<BR>
     */
    virtual void behave();

    virtual ~GgafDxKurokoB();
};

}
#endif /*GGAFDXMVTRANSPORTER_H_*/

