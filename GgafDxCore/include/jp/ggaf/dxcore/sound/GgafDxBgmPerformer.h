#ifndef GGAFDXCORE_GGAFDXBGMPERFORMER_H_
#define GGAFDXCORE_GGAFDXBGMPERFORMER_H_
#include "jp/ggaf/core/GgafObject.h"

namespace GgafDxCore {

/**
 * BGM演奏支援クラス .
 * @version 1.00
 * @since 2010/04/19
 * @author Masatoshi Tsuge
 */
class GgafDxBgmPerformer : public GgafCore::GgafObject {

public:
//    static int _active_bgm_bpm;
    /** [r]BGMチャンネル数 */
    int _bgm_num;
    /** [r]BGMのボリューム配列(添字はBGMチャンネル番号) */
    double* _paDouble_volume;
    /** [r]Bgm資源接続 */
    GgafDxBgmConnection** _papBgmConnection;

public:
    GgafDxBgmPerformer();

    /**
     * BGMを設定する。
     * @param prm_id BGMチャンネル番号(0 ～ )
     * @param prm_bgm_name プロパティファイルの_OGG, _BPM, _TITLE のプレフィックスとなっているkey文字列
     */
    virtual void ready(int prm_id, const char* prm_bgm_name);

    /**
     * ボリュームを設定する。
     * @param prm_id     BGMチャンネル番号(0 ～ )
     * @param prm_volume ボリューム値(0 ～ 100)
     */
    virtual void setVolume(int prm_id, int prm_volume);

    /**
     * BGMを再生する。
     * @param prm_id       BGMチャンネル番号(0 ～ )
     * @param prm_volume   ボリューム値(0 ～ 100)
     * @param prm_is_loop  ループするかどうか（true:ループ再生する／false:ループ再生しない）
     */
    virtual void play(int prm_id, int prm_volume, bool prm_is_loop);

    /**
     * BGMを再生する(ループ再生)。
     * @param prm_id     BGMチャンネル番号(0 ～ )
     * @param prm_volume ボリューム値(0 ～ 100)
     */
    virtual void play(int prm_id, int prm_volume) {
        play(prm_id, prm_volume, true);
    }

    /**
     * BGMを再生する(ループ再生, ボリュームGGAF_MAX_VOLUME)。
     * @param prm_id BGMチャンネル番号(0 ～ )
     */
    virtual void play(int prm_id) {
        play(prm_id, GGAF_MAX_VOLUME);
    }

    /**
     * BGMを停止する .
     * @param prm_id BGMチャンネル番号(0 ～ )
     */
    virtual void stop(int prm_id);

    /**
     * BGMを一時停止する .
     * @param prm_id BGMチャンネル番号(0 ～ )
     */
    virtual void pause(int prm_id);

    /**
     * BGMの一時停止を解除する .
     * @param prm_id  BGMチャンネル番号(0 ～ )
     */
    virtual void unpause(int prm_id);

    /**
     * 全BGMチャンネル番号のBGMを停止 .
     */
    virtual void stop();

    /**
     * 全BGMチャンネル番号のBGMを一時停止 .
     */
    virtual void pause();

    /**
     * 全BGMチャンネル番号のBGMの一時停止を解除する .
     */
    virtual void unpause();

    virtual ~GgafDxBgmPerformer();
};

}
#endif /*GGAFDXCORE_GGAFDXBGMPERFORMER_H_*/
