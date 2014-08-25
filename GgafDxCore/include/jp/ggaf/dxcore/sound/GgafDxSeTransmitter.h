#ifndef GGAFDXCORE_GGAFDXSEREFLECTOR_H_
#define GGAFDXCORE_GGAFDXSEREFLECTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

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

public:
    /** [r]SE資源接続の配列 */
    GgafDxSeConnection** _papSeConnection;
    /** [r]SEの数 */
    int _se_num;

public:
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
     * 但し、SEの再生時間は GGAF_END_DELAY+(最大距離遅延) フレーム以内でなければいけない。
     * 上書き再設定可能。
     * @param prm_id SEのID ( 0 ～ SE数-1 )
     * @param prm_se_key SE定義名(プロパティファイルのキー)
     * @param prm_cannel 再生チャンネル番号
     */
    virtual void set(int prm_id, const char* prm_se_key, int prm_cannel);

    /**
     * 再生 .
     * @param prm_id  SEのID ( 0 ～ SE数-1 )
     */
    virtual void play(int prm_id);

    /**
     * 再生停止 .
     * @param prm_id  SEのID ( 0 ～ SE数-1 )
     */
    virtual void stop(int prm_id);

    virtual void setLooping(int prm_id, bool prm_can_looping);

    /**
     * GgafDxSe を取得。
     * @param prm_id SEのID ( 0 ～ SE数-1 )
     */
    virtual GgafDxSe* get(int prm_id);

    /**
     * デストラクタ
     */
    virtual ~GgafDxSeTransmitter();
};

}
#endif /*GGAFDXCORE_GGAFDXSEREFLECTOR_H_*/
