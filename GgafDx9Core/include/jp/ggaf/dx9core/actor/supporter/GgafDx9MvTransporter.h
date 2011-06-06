#ifndef GGAFDX9MVTRANSPORTER_H_
#define GGAFDX9MVTRANSPORTER_H_
namespace GgafDx9Core {


/**
 * ナビゲーター .
 * ナビゲーターは舞台には見えないですが、演者(アクター)を持ち上げて、移動、回転させる人々です。<BR>
 * 演者は自らは特に動作せずとも、ナビゲーターのおかげで舞台を飛び回まわることもできます。<BR>
 * 基本的な動作はナビゲーターでほとんどカバーできますが、万能ではありません。<BR>
 * ナビゲーターが頑張っても対応できない複雑な動作は、演者(アクター)自身も協力して移動、回転擦る必要があります。<BR>
 * 演者一人ににつき、ナビゲーターが一人付いています。<BR>
 * <BR>
 * それはさて置き、つまり座標計算支援（共通化）クラスです。<BR>
 * GgafDx9GeometricActor のメンバの<BR>
 *  _X ,  _Y,  _Z  ・・・ アクターの座標<BR>
 * _RX , _RY, _RZ  ・・・ アクターの軸回転角度<BR>
 * を、簡単に操作するために作成。<BR>
 * 基本的な移動、回転はナビゲーターに任せ、<BR>
 * 特殊な移動、回転のみ直接アクターの processBehave() に実装。という設計思想。<BR>
 * TODO:いつの間にか肥大化。分割せよ。
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class GgafDx9MvTransporter : public GgafCore::GgafObject {
    float _dummy1, _dummy2, _dummy3;

public:
    /** 対象アクター */
    GgafDx9GeometricActor* _pActor;
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用Actor
     */
    GgafDx9MvTransporter(GgafDx9GeometricActor* prm_pActor);




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



    //virtual void behave();

    void setVxMvVelo(velo prm_veloVxMv);
    void addVxMvVelo(velo prm_veloVxMv);
    void forceVxMvVeloRange(velo prm_veloVxMv01, velo prm_veloVxMv02);
    void setVxMvAcce(acce prm_acceVxMv);
    void addVxMvAcce(acce prm_acceVxMv);
    void forceVxMvAcceRange(acce prm_acceVxMv01, acce prm_acceVxMv02);
    void setVyMvVelo(velo prm_veloVyMv);
    void addVyMvVelo(velo prm_veloVyMv);
    void forceVyMvVeloRange(velo prm_veloVyMv01, velo prm_veloVyMv02);
    void setVyMvAcce(acce prm_acceVyMv);
    void addVyMvAcce(acce prm_acceVyMv);
    void forceVyMvAcceRange(acce prm_acceVyMv01, acce prm_acceVyMv02);
    void setVzMvVelo(velo prm_veloVzMv);
    void addVzMvVelo(velo prm_veloVzMv);
    void forceVzMvVeloRange(velo prm_veloVzMv01, velo prm_veloVzMv02);
    void setVzMvAcce(acce prm_acceVzMv);
    void addVzMvAcce(acce prm_acceVzMv);
    void forceVzMvAcceRange(acce prm_acceVzMv01, acce prm_acceVzMv02);

    void forceVxyzMvVeloRange(velo prm_veloVxyzMv01, velo prm_veloVxyzMv02);
    void forceVxyzMvAcceRange(acce prm_acceVxyzMv01, acce prm_acceVxyzMv02);

    void setZeroVxyzMvVelo() {
        _veloVxMv = _veloVyMv = _veloVzMv = 0;
    }

    void setZeroVxyzMvAcce() {
        _acceVxMv = _acceVyMv = _acceVzMv = 0;
    }


    void stopGravitationVxyzMvSequence() {
        _gravitation_mv_seq_flg = false;
    }

    void execGravitationVxyzMvSequence(
            int prm_tX, int prm_tY, int prm_tZ,
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
     * ナビゲーターの仕事を引継ぐ .
     * 他の GgafDx9MvTransporter オブジェクトを状態を自身に引継ぐ .
     * @param prm_pMvTransporter 引継元
     */
    void takeoverMvFrom(GgafDx9MvTransporter* prm_pMvTransporter);


    void resetMv();

    /**
     * ナビゲーターが動く .
     * ナビゲーター機能を利用する場合は、このメソッドを毎フレーム呼び出し実行してください。<BR>
     * 逆にナビゲーターを必要としない場合は、このメソッドを呼び出さないことで、パフォーマンスに影響を与えません。<BR>
     */
    virtual void behave();

    virtual ~GgafDx9MvTransporter();
};

}
#endif /*GGAFDX9MVTRANSPORTER_H_*/

