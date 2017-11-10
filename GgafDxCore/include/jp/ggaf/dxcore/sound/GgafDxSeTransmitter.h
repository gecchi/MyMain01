#ifndef GGAFDXCORE_GGAFDXSEREFLECTOR_H_
#define GGAFDXCORE_GGAFDXSEREFLECTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

namespace GgafDxCore {

/**
 * サウンドエフェクト出力支援クラス .
 * 内部で GgafDxSeManager 利用し、必要最低限のSE資源で
 * 再生チャンネルの機能を実装。
 * @version 1.00
 * @since 2010/04/19
 * @author Masatoshi Tsuge
 */
class GgafDxSeTransmitter : public GgafCore::GgafObject {

public:
    /** [r]SE資源接続の配列 */
    GgafDxSeConnection** _papSeConnection;
    /** [r]扱うSEの数 */
    int _se_num;
    /** [r]扱うSEのボリューム配列 */
    double* _pa_volume;
    /** [r]扱うSEのパン値 */
    float* _pa_pan;

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
     * @param prm_se_no SEの番号 ( 0 ～ SE数-1 )
     * @param prm_se_key SE定義名(プロパティファイルのキー)
     * @param prm_cannel 再生チャンネル番号
     */
    virtual void set(int prm_se_no, const char* prm_se_key, int prm_cannel);

    /**
     * 再生 .
     * @param prm_se_no  SEの番号 ( 0 ～ SE数-1 )
     * @param prm_can_looping  true:ループ再生／false:1回再生
     */
    virtual void play(int prm_se_no, bool prm_can_looping = false);


    /**
     * ボリューム値を設定する。
     * SEマスターボリュームも考慮された音量に設定される。
     * @param prm_se_no SEの番号(0 ～ )
     * @param prm_volume ボリューム値(0 ～ 1000)
     */
    virtual void setVolume(int prm_se_no, double prm_volume);

    /**
     * ボリューム値を取得する .
     * SEマスターボリュームも考慮されていないsetVolume()で設定された音量を取得。
     * @param prm_se_no SEの番号(0 ～ )
     * @return ボリューム値(0 ～ 1000)
     */
    virtual int getVolume(int prm_se_no) {
        return _pa_volume[prm_se_no];
    }

    /**
     * ボリューム値を加算する .
     * SEマスターボリュームも考慮された音量に設定される。
     * @param prm_se_no SEの番号(0 ～ )
     * @param prm_volume 加算ボリューム値(0 ～ 1000)
     * @return
     */
    virtual void addVolume(int prm_se_no, double prm_volume) {
        setVolume(prm_se_no, _pa_volume[prm_se_no] + prm_volume);
    }

    /**
     * パン値を設定 .
     * SEマスターパンは未作成のため、そのまま反映
     * @param prm_pan パン値(left:-1.0 ～ center:0 ～ right:1.0)
     */
    virtual void setPan(int prm_se_no, float prm_pan);

    /**
     * パン値を取得する .
     * @param prm_se_no
     * @return
     */
    virtual float getPan(int prm_se_no) {
        return _pa_pan[prm_se_no];
    }


    /**
     * 再生停止 .
     * @param prm_se_no  SEの番号 ( 0 ～ SE数-1 )
     */
    virtual void stop(int prm_se_no);


    /**
     * GgafDxSe を取得。
     * @param prm_se_no SEの番号 ( 0 ～ SE数-1 )
     */
    virtual GgafDxSe* getSe(int prm_se_no) const;

    /**
     * デストラクタ
     */
    virtual ~GgafDxSeTransmitter();
};

}
#endif /*GGAFDXCORE_GGAFDXSEREFLECTOR_H_*/
