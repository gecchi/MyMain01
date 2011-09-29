#ifndef GGAFDXSEREFLECTOR_H_
#define GGAFDXSEREFLECTOR_H_
namespace GgafDxCore {

/**
 * サウンドエフェクト出力支援クラス .
 * @version 1.00
 * @since 2010/04/19
 * @author Masatoshi Tsuge
 */
class GgafDxSeTransmitter : public GgafCore::GgafObject {

private:
    /**
     * パンとボリュームを更新する。
     * play3Dの効果を継続するために毎フレーム呼び出す必要がある。
     */
    void updatePanVolume3D();

public:
    /** SE資源接続 */
    GgafDxSeConnection** _papSeCon;
    /** 擬似３D再生か否か */
    bool* _pa_is3D;

    int _se_num;
    GgafDxGeometricActor* _pActor;
    /**
     * コンストラクタ .
     */
    GgafDxSeTransmitter(GgafDxGeometricActor* prm_pActor);

    /**
     * SE使用数を宣言する .
     * 本オブジェクトの機能を利用するには、必須。
     * @param prm_se_num SE数
     */
    void useSe(int prm_se_num);

    /**
     * SEの設定を行う .
     * 但し、SEの再生時間は GGAF_SAYONARA_DELAY+(最大距離遅延) フレーム以内でなければいけない。
     * @param prm_id SEのID ( 0 ～ SE数-1 )
     * @param prm_se_name SE定義名
     * @param prm_cannel チャンネル
     */
    void set(int prm_id, const char* prm_se_name, int prm_cannel = 1);

    /**
     * 即座にSEを再生する(擬似３D無し)。
     * @param prm_id SEのID ( 0 ～ SE数-1 )
     */
    void playImmediately(int prm_id);

    /**
     * SEを再生する(擬似３D無し)。
     * playImmediately(int) と違い、次フレームに再生される予定リストに追加される。
     * もし、同一フレームに、同一種類のSEが多数登録された場合、音の跳ね上がりを抑えるため、
     * 最大８フレーム遅延し、ばらけて再生される機能を持っている。
     * @param prm_id SEのID ( 0 ～ SE数-1 )
     */
    void play(int prm_id);

    /**
     * SEの擬似３D再生 .
     * オブジェクトの座標とカメラの座標から、
     * 左右のパン、距離に応じてのボリューム減少と、遅延再生。
     * を行う。
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
    virtual ~GgafDxSeTransmitter();
};

}
#endif /*GGAFDXSEREFLECTOR_H_*/
