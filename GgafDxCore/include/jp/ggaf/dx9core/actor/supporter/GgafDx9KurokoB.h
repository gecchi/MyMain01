#ifndef GGAFDX9MVTRANSPORTER_H_
#define GGAFDX9MVTRANSPORTER_H_
namespace GgafDx9Core {


/**
 * 黒子B(黒衣B)  .
 * 黒子Bは舞台には見えないですが、演者(アクター)を持ち上げ、「平行移動」を行わせる世話人です。<BR>
 * 「平行移動」に特化しており、黒子Aの「方向移動」「向きの回転」とは専門分野が違います。<BR>
 * 黒子Aと黒子Bが協力すれば、かなり複雑な動きを演者に行わせることができます。
 * 演者一人につき、黒子Bが標準で一人付属しています。<BR>
 * <BR>
 * それはさて置き、つまり座標計算支援（共通化）クラスその２です。<BR>
 * GgafDx9GeometricActor のメンバの<BR>
 *  _X, _Y, _Z  ・・・ アクターの座標<BR>
 * を、各成分毎に簡単に操作するために作成。<BR>
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class GgafDx9KurokoB : public GgafCore::GgafObject {

public:
    /** 対象アクター */
    GgafDx9GeometricActor* _pActor;

    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用Actor
     */
    GgafDx9KurokoB(GgafDx9GeometricActor* prm_pActor);


    /** X軸方向移動速度 */
    velo _veloVxMv;
    /** X軸方向移動速度上限 */
    velo _veloTopVxMv;
    /** X軸方向移動速度下限 */
    velo _veloBottomVxMv;
    /** X軸方向移動加速度 */
    acce _acceVxMv;
    /** X軸方向移動加速度上限*/
    acce _acceTopVxMv;
    /** X軸方向移動加速度下限*/
    acce _acceBottomVxMv;
    /** Y軸方向移動速度 */
    velo _veloVyMv;
    /** Y軸方向移動速度上限 */
    velo _veloTopVyMv;
    /** Y軸方向移動速度下限 */
    velo _veloBottomVyMv;
    /** Y軸方向移動加速度 */
    acce _acceVyMv;
    /** Y軸方向移動加速度上限*/
    acce _acceTopVyMv;
    /** Y軸方向移動加速度下限*/
    acce _acceBottomVyMv;
    /** Z軸方向移動速度 */
    velo _veloVzMv;
    /** Z軸方向移動速度上限 */
    velo _veloTopVzMv;
    /** Z軸方向移動速度下限 */
    velo _veloBottomVzMv;
    /** Z軸方向移動加速度 */
    acce _acceVzMv;
    /** Z軸方向移動加速度上限*/
    acce _acceTopVzMv;
    /** Z軸方向移動加速度下限*/
    acce _acceBottomVzMv;


    int _gravitation_mv_seq_target_X;
    int _gravitation_mv_seq_target_Y;
    int _gravitation_mv_seq_target_Z;
    GgafDx9GeometricActor* _gravitation_mv_seq_pActor_target;
    velo _gravitation_mv_seq_max_velo;
    acce _gravitation_mv_seq_acce;
    int _gravitation_mv_seq_stop_renge;
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
     * X軸Y軸Z軸方向の移動加速度を 0 に設定する。
     */
    void setZeroVxyzMvVelo() {
        _veloVxMv = _veloVyMv = _veloVzMv = 0;
    }

    void setZeroVxyzMvAcce() {
        _acceVxMv = _acceVyMv = _acceVzMv = 0;
    }


    void stopGravitationVxyzMvSequence() {
        _gravitation_mv_seq_flg = false;
    }

    /**
     *
     * @param prm_tX
     * @param prm_tY
     * @param prm_tZ
     * @param prm_max_velo
     * @param prm_acce
     * @param prm_stop_renge
     */
    void execGravitationVxyzMvSequence(
            coord prm_tX, coord prm_tY, coord prm_tZ,
            velo prm_max_velo,
            acce prm_acce,
            int prm_stop_renge
            );


    void execGravitationVxyzMvSequence(
            GgafDx9GeometricActor* prm_pActor_target,
            velo prm_max_velo,
            acce prm_acce,
            int prm_stop_renge
            );

    /**
     * 黒子Bの仕事を引継ぐ .
     * 他の GgafDx9KurokoB オブジェクトを状態を自身に引継ぐ .
     * @param prm_pKurokoB 引継元
     */
    void takeoverMvFrom(GgafDx9KurokoB* prm_pKurokoB);


    void resetMv();

    /**
     * 黒子Bが動く .
     * 黒子B機能を利用する場合は、このメソッドを毎フレーム呼び出し実行してください。<BR>
     * 逆に黒子Bを必要としない場合は、このメソッドを呼び出さないことで、パフォーマンスに影響を与えません。<BR>
     */
    virtual void behave();

    virtual ~GgafDx9KurokoB();
};

}
#endif /*GGAFDX9MVTRANSPORTER_H_*/

