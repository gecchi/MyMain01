#ifndef GGAFDXSETRANSMITTERFORACTOR_H_
#define GGAFDXSETRANSMITTERFORACTOR_H_
namespace GgafDxCore {

/**
 * アクター用サウンドエフェクト出力支援クラス .
 * 簡易3D効果音機能の追加。
 * GgafDxSeTransmitter から分離
 * @version 1.00
 * @since 2012/03/22
 * @author Masatoshi Tsuge
 */
class GgafDxSeTransmitterForActor : public GgafDxSeTransmitter {

private:
    /**
     * パンとボリュームを更新する。
     * play3Dの効果を継続するために毎フレーム呼び出す必要がある。
     */
    void updatePanVolume3D();

public:
    /** [r/w]各SE（配列）は、擬似３D再生かどうかを保持 */
    bool* _pa_is3D;
    /** [r]SE発生元アクター */
    GgafDxGeometricActor* _pActor;

    /**
     * コンストラクタ .
     */
    GgafDxSeTransmitterForActor(GgafDxGeometricActor* prm_pActor);

    /**
     * SE使用数を宣言する .
     * 本オブジェクトの機能を利用するには、必須。
     * @param prm_se_num SE数（種類数）
     */
    void useSe(int prm_se_num) override;

    /**
     * 即座にSEを再生する(擬似３D無し)。
     * @param prm_id SEのID ( 0 ～ SE数-1 )
     */
    void play(int prm_id) override;

    /**
     * SEの擬似３D再生 .
     * オブジェクトの座標とカメラの座標から、左右のパン。
     * 距離に応じてのボリューム減少と、遅延再生を行う。
     * @param prm_id SEのID ( 0 ～ SE数-1 )
     */
    void play3D(int prm_id);

    /**
     * 毎フレームの処理 .
     * updatePanVolume3D() を呼び出しを行っている。
     * play3D()を使用していないのであれば、呼び出す必要はない。
     */
    void behave();

    /**
     * デストラクタ
     */
    virtual ~GgafDxSeTransmitterForActor();
};

}
#endif /*GGAFDXSETRANSMITTERFORACTOR_H_*/
