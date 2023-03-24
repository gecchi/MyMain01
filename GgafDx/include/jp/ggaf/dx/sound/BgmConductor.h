#ifndef GGAF_DX_BGMCONDUCTOR_H_
#define GGAF_DX_BGMCONDUCTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <vector>

namespace GgafDx {

/**
 * BGM演奏指揮者クラス .
 * BGMとそれに紐つく音量、パンの値を保持
 * BGMマスターボリュームを考慮
 * @version 1.00
 * @since 2010/04/19
 * @author Masatoshi Tsuge
 */
class BgmConductor : public GgafCore::Object {

public:
//    static int _active_bgm_bpm;
    /** [r]BGM番号数 */
    int _bgm_num;
    /** [r]Bgm資源接続 */
    std::vector<BgmConnection*>  _vecBgmConnection;
    /** [r]BGMのボリューム配列(添字はBGM番号) */
    std::vector<double> _vec_volume;
    /** [r]BGMのパン値(添字はBGM番号) */
    std::vector<float> _vec_pan;
    /** [r]フェードターゲットボリュームの配列(添字はチャンネル) */
    std::vector<double> _vec_target_volume;
    /** [r]ボリューム加算値の配列(添字はチャンネル) */
    std::vector<double> _vec_inc_volume;
    /** [r]現在フェード中か否かの配列(添字はチャンネル) */
    std::vector<bool> _vec_is_fade;
    /** [r]フェード後停止させるのかどうかの配列(添字はチャンネル) */
    std::vector<bool> _vec_is_fadeafter_stop;

public:
    BgmConductor();

    /**
     * BGMを準備する .
     * 演奏前に必ず実行しておく必要があります。
     * @param prm_bgm_no BGM番号(0 ～ )
     * @param prm_bgm_name プロパティファイルkey文字列
     */
    virtual void ready(int prm_bgm_no, const char* prm_bgm_name);

    /**
     * BGMを演奏する準備が整っているか .
     * @param prm_bgm_no  BGM番号(0 ～ )
     * @return true:演奏できる／false:演奏できない
     */
    virtual bool isReady(int prm_bgm_no);

    /**
     * ボリューム値を設定する .
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
     * 演奏する .
     * 一時停止してい他場合は、続きから演奏される。曲の最初からとは限らない。
     * @param prm_bgm_no  BGM番号(0 ～ )
     * @param prm_is_loop  ループするかどうか（true:ループ再生する／false:ループ再生しない）
     */
    virtual void perform(int prm_bgm_no, bool prm_is_loop = true);

    /**
     * 曲の最初から演奏する .
     * @param prm_bgm_no  BGM番号(0 ～ )
     * @param prm_is_loop ループするかどうか（true:ループ再生する／false:ループ再生しない）
     */
    virtual void performFromTheBegining(int prm_bgm_no, bool prm_is_loop = true);

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

    virtual bool isPerforming(int prm_bgm_no);
    /**
     * BGMの一時停止中か判断する .
     * @param prm_bgm_no BGM番号(0 ～ )
     * @return true:一時停止中／false:一時停止中では無い
     */
    virtual bool isPause(int prm_bgm_no);

    virtual bool isStopping(int prm_bgm_no);

    virtual Bgm* getBgm(int prm_bgm_no);

    /**
     * BGMの振る舞い .
     * 主にボリュームを変化させ、フェードイン・アウト効果を持続処理させる。
     */
    virtual void behave();

    /**
     * 演奏中のBGMにフェード効果を実行する。
     * @param prm_bgm_no              BGM番号(0 ～ )
     * @param prm_frame           フェードに費やすフレーム時間
     * @param prm_target_volume   到達目標ボリューム(0 ～ 100)
     */
    virtual void fade(int prm_bgm_no, frame prm_frame, int prm_target_volume);

    /**
     * BGMを、フェードインによる再生を開始する。
     * @param prm_bgm_no  BGM番号(0 ～ )
     * @param prm_frame フェードインフレーム数
     */
    virtual void performFadein(int prm_bgm_no, frame prm_frame);

    /**
     * 演奏中のBGMにフェードアウト効果を実行し、フェードアウト後演奏を停止する。
     * @param prm_bgm_no BGM番号(0 ～ )
     * @param prm_frame フェードアウトフレーム数
     */
    virtual void fadeoutStop(int prm_bgm_no, frame prm_frame);

    /**
     * 全BGM番号の演奏中のBGMにフェードアウト効果を実行し、フェードアウト後演奏を停止する。
     * フェードアウト時間は setDefaultFadeFrames() 指定のフレーム数。
     */
    virtual void fadeoutStopAll(frame prm_frame);


    virtual ~BgmConductor();
};

}
#endif /*GGAF_DX_BGMCONDUCTOR_H_*/
