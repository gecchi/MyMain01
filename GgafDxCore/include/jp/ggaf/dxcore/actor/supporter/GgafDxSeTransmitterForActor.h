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
    bool* _paBool_is_playing_3d;
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
    void declareSeNum(int prm_se_num) override;
    /**
     * SEの設定を行う .
     * 但し、SEの再生時間は GGAF_SAYONARA_DELAY+(最大距離遅延) フレーム以内でなければいけない。
     * @param prm_id SEのID ( 0 〜 SE数-1 )
     * @param prm_se_name SE定義名 prm_se_name+".wave"
     * @param prm_cannel 再生チャンネル番号
     */
    void set(int prm_id, const char* prm_se_name, int prm_cannel = 1) override;

    /**
     * 即座にSEを再生する(擬似３D無し)。
     * @param prm_id SEのID ( 0 〜 SE数-1 )
     */
    void play(int prm_id) override;

    /**
     * SEの擬似３D再生 .
     * オブジェクトの座標とカメラの座標から、左右のパン。
     * 距離に応じてのボリューム減少と、遅延再生を行う。
     * behave() を毎フレーム呼び出しておくと、SE再生中も擬似３D効果を得る。
     * @param prm_id SEのID ( 0 〜 SE数-1 )
     */
    void play3D(int prm_id);

    /**
     * 毎フレームの処理 .
     * updatePanVolume3D() を呼び出しを行っている。
     * play3D()を使用していないのであれば、呼び出す必要はない。
     * あるSE再生中に、フレーム期間にまたがって擬似３D効果を得る場合は、呼び出す必要がある。
     * SE再生が、再生開始時点での擬似３D効果で良ければ、呼び出す必要がない。
     */
    void behave();

    /**
     * デストラクタ
     */
    virtual ~GgafDxSeTransmitterForActor();
};

}
#endif /*GGAFDXSETRANSMITTERFORACTOR_H_*/
