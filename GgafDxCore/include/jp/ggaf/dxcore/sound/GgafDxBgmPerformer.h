#ifndef GGAFDXCORE_GGAFDXBGMPERFORMER_H_
#define GGAFDXCORE_GGAFDXBGMPERFORMER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include <vector>

namespace GgafDxCore {

/**
 * BGM演奏支援クラス .
 * BGMとそれに紐つく音量、パンの値を保持
 * BGMマスターボリュームを考慮
 * @version 1.00
 * @since 2010/04/19
 * @author Masatoshi Tsuge
 */
class GgafDxBgmPerformer : public GgafCore::GgafObject {

public:
//    static int _active_bgm_bpm;
    /** [r]BGM番号数 */
    int _bgm_num;
    /** [r]Bgm資源接続 */
    std::vector<GgafDxBgmConnection*>  _vecBgmConnection;
    /** [r]BGMのボリューム配列(添字はBGM番号) */
    std::vector<double> _vec_volume;
    /** [r]BGMのパン値(添字はBGM番号) */
    std::vector<float> _vec_pan;


public:
    GgafDxBgmPerformer();

    /**
     * BGMを設定する。
     * @param prm_bgm_no BGM番号(0 ～ )
     * @param prm_bgm_name プロパティファイルkey文字列
     */
    virtual void ready(int prm_bgm_no, const char* prm_bgm_name);

    /**
     * ボリューム値を設定する。
     * BGMマスターボリュームも考慮された音量に設定される。
     * @param prm_bgm_no BGM番号(0 ～ )
     * @param prm_volume ボリューム値(0 ～ 1000)
     */
    virtual void setVolume(int prm_bgm_no, double prm_volume);

    /**
     * ボリューム値を取得する .
     * BGMマスターボリュームも考慮されていないsetVolume()で設定された音量を取得。
     * @param prm_bgm_no BGM番号(0 ～ )
     * @return ボリューム値(0 ～ 1000)
     */
    virtual int getVolume(int prm_bgm_no) {
        return _vec_volume[prm_bgm_no];
    }

    /**
     * ボリューム値を加算する .
     * BGMマスターボリュームも考慮された音量に設定される。
     * @param prm_bgm_no BGM番号(0 ～ )
     * @param prm_volume 加算ボリューム値(0 ～ 1000)
     * @return
     */
    virtual void addVolume(int prm_bgm_no, double prm_volume) {
        setVolume(prm_bgm_no, _vec_volume[prm_bgm_no] + prm_volume);
    }

    /**
     * パン値を設定 .
     * BGMマスターパンは未作成のため、そのまま反映
     * @param prm_pan パン値(left:-1.0 ～ center:0 ～ right:1.0)
     */
    virtual void setPan(int prm_bgm_no, float prm_pan);

    /**
     * パン値を取得する .
     * @param prm_bgm_no
     * @return
     */
    virtual float getPan(int prm_bgm_no) {
        return _vec_pan[prm_bgm_no];
    }

    /**
     * BGMを再生する。
     * @param prm_bgm_no  BGM番号(0 ～ )
     * @param prm_is_loop  ループするかどうか（true:ループ再生する／false:ループ再生しない）
     */
    virtual void play(int prm_bgm_no, bool prm_is_loop = true);

    /**
     * BGMを停止する .
     * @param prm_bgm_no BGM番号(0 ～ )
     */
    virtual void stop(int prm_bgm_no);

    /**
     * BGMを一時停止する .
     * @param prm_bgm_no BGM番号(0 ～ )
     */
    virtual void pause(int prm_bgm_no);

    /**
     * BGMの一時停止を解除する .
     * @param prm_bgm_no  BGM番号(0 ～ )
     */
    virtual void unpause(int prm_bgm_no);

    /**
     * 全BGM番号のBGMを停止 .
     */
    virtual void stop();

    /**
     * 全BGM番号のBGMを一時停止 .
     */
    virtual void pause();

    /**
     * 全BGM番号のBGMの一時停止を解除する .
     */
    virtual void unpause();

    virtual GgafDxBgm* getBgm(int prm_bgm_no);

    virtual ~GgafDxBgmPerformer();
};

}
#endif /*GGAFDXCORE_GGAFDXBGMPERFORMER_H_*/
