#ifndef GGAFDXSEREFLECTOR_H_
#define GGAFDXSEREFLECTOR_H_
namespace GgafDxCore {

/**
 * サウンドエフェクト出力支援クラス .
 * 内部で GgafDxSeManager 利用。
 * 再生チャンネルの機能を実装。
 * @version 1.00
 * @since 2010/04/19
 * @author Masatoshi Tsuge
 */
class GgafDxSeTransmitter : public GgafCore::GgafObject {

private:

public:
    /** [r]SE資源接続の配列 */
    GgafDxSeConnection** _papSeCon;
    /** [r]SEの数 */
    int _se_num;

    /**
     * コンストラクタ .
     */
    GgafDxSeTransmitter();

    /**
     * SE使用数を宣言し、初期化を行う .
     * 本オブジェクトの機能を利用するには、必須。
     * @param prm_se_num SE数（種類数）
     */
    virtual void declareSeNum(int prm_se_num);

    /**
     * SEの設定を行う .
     * 但し、SEの再生時間は GGAF_SAYONARA_DELAY+(最大距離遅延) フレーム以内でなければいけない。
     * 上書き再設定可能。
     * @param prm_id SEのID ( 0 〜 SE数-1 )
     * @param prm_se_key SE定義名(プロパティファイルのキー)
     * @param prm_cannel 再生チャンネル番号
     */
    virtual void set(int prm_id, const char* prm_se_key, int prm_cannel);


    /**
     * 再生 .
     * @param prm_id  SEのID ( 0 〜 SE数-1 )
     */
    virtual void play(int prm_id);

    /**
     * GgafDxSe を取得。
     * @param prm_id SEのID ( 0 〜 SE数-1 )
     */
    virtual GgafDxSe* get(int prm_id);

    /**
     * デストラクタ
     */
    virtual ~GgafDxSeTransmitter();
};

}
#endif /*GGAFDXSEREFLECTOR_H_*/
