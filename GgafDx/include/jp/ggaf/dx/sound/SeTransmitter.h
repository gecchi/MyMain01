#ifndef GGAF_DX_SEREFLECTOR_H_
#define GGAF_DX_SEREFLECTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <map>


typedef uint64_t t_se_id;

namespace GgafDx {

/**
 * サウンドエフェクト出力支援クラス .
 * 内部で SeManager 利用し、必要最低限のSE資源で
 * 再生チャンネルの機能を実装。
 * @version 1.00
 * @since 2010/04/19
 * @author Masatoshi Tsuge
 */
class SeTransmitter : public GgafCore::Object {

public:
    /** [r]扱うSEの数 */
//    int _se_num;
    /** [r]SE資源接続の配列 */
    std::map<t_se_id, SeConnection*> _mapSeConnection;
    /** [r]扱うSEのボリューム配列 */
    std::map<t_se_id, double> _map_volume;
    /** [r]扱うSEのパン値 */
    std::map<t_se_id, float> _map_pan;

public:
    /**
     * コンストラクタ .
     */
    SeTransmitter();

    /**
     * SEの設定を行う .
     * 引数のチャンネル番号が異なれば、同じSE定義名のWaveでも、複数同時発声ができる。
     * 引数のチャンネル番号が同じであれば、一つの発声しかできない。
     * 但し、SEの再生時間は CONFIG::END_DELAY_FRAME+(最大距離遅延) フレーム以内でなければいけない。
     * 上書き再設定可能。
     * @param prm_se_id SE登録ID
     * @param prm_se_key SE定義名(プロパティファイルのwaveファイル指定のキー)
     * @param prm_cannel 再生チャンネル番号
     */
    virtual void set(t_se_id prm_se_id, const char* prm_se_key, int prm_cannel);

    /**
     * 再生 .
     * @param prm_se_id  SE登録ID
     * @param prm_can_looping  true:ループ再生／false:1回再生
     */
    virtual void play(t_se_id prm_se_id, bool prm_can_looping = false);


    /**
     * ボリューム値を設定する。
     * SEマスターボリュームも考慮された音量に設定される。
     * @param prm_se_id SE登録ID(0 ～ )
     * @param prm_volume ボリューム値(0 ～ 1000)
     */
    virtual void setVolume(t_se_id prm_se_id, double prm_volume);

    /**
     * ボリューム値を取得する .
     * SEマスターボリュームも考慮されていないsetVolume()で設定された音量を取得。
     * @param prm_se_id SE登録ID(0 ～ )
     * @return ボリューム値(0 ～ 1000)
     */
    virtual int getVolume(t_se_id prm_se_id) {
        return _map_volume[prm_se_id];
    }

    /**
     * ボリューム値を加算する .
     * SEマスターボリュームも考慮された音量に設定される。
     * @param prm_se_id SE登録ID(0 ～ )
     * @param prm_volume 加算ボリューム値(0 ～ 1000)
     * @return
     */
    virtual void addVolume(t_se_id prm_se_id, double prm_volume) {
        setVolume(prm_se_id, _map_volume[prm_se_id] + prm_volume);
    }

    /**
     * パン値を設定 .
     * SEマスターパンは未作成のため、そのまま反映
     * @param prm_pan パン値(left:-1.0 ～ center:0 ～ right:1.0)
     */
    virtual void setPan(t_se_id prm_se_id, float prm_pan);

    /**
     * パン値を取得する .
     * @param prm_se_id
     * @return
     */
    virtual float getPan(t_se_id prm_se_id) {
        return _map_pan[prm_se_id];
    }


    /**
     * 再生停止 .
     * @param prm_se_id  SE登録ID
     */
    virtual void stop(t_se_id prm_se_id);


    /**
     * Se を取得。
     * @param prm_se_id SE登録ID
     */
    virtual Se* getSe(t_se_id prm_se_id) ;

    /**
     * デストラクタ
     */
    virtual ~SeTransmitter();
};

}
#endif /*GGAF_DX_SEREFLECTOR_H_*/
