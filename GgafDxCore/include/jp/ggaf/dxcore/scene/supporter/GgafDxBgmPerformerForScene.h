#ifndef GGAFDXCORE_GGAFDXBGMPERFORMERFORSCENE_H_
#define GGAFDXCORE_GGAFDXBGMPERFORMERFORSCENE_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgmPerformer.h"

namespace GgafDxCore {

/**
 * BGM演奏支援クラス .
 * シーンオブジェクトに、保持される事によって、
 * BGMフェードイン、フェードアウト機能を付加。
 * GgafDxScene::processSettlementBehavior() で、本クラスの
 * behave() メソッドがコールされる仕様。<BR>
 * GgafDxBgmPerformer から分離
 * @version 1.00
 * @since 2012/03/22
 * @author Masatoshi Tsuge
 */
class GgafDxBgmPerformerForScene : public GgafDxBgmPerformer {
public:
    /** [r]BGMと関連付くシーン */
    GgafDxScene* _pDxScene;
    /** [r]フェードターゲットボリュームの配列(添字はチャンネル) */
    std::vector<double> _vec_target_volume;
    /** [r]ボリューム加算値の配列(添字はチャンネル) */
    std::vector<double> _vec_inc_volume;
    /** [r]現在フェード中か否かの配列(添字はチャンネル) */
    std::vector<bool> _vec_is_fade;
    /** [r]フェード後停止させるのかどうかの配列(添字はチャンネル) */
    std::vector<bool> _vec_is_fadeout_stop;
    /** [r/w]デフォルトのフェードイン・フェードアウトの費やすフレーム時間 */
    frame _default_fade;

public:
    /**
     * コンストラクタ
     * @param prm_pDxScene シーン
     */
    GgafDxBgmPerformerForScene(GgafDxScene* prm_pDxScene);

    /**
     * BGMを設定する。
     * @param prm_bgm_no BGM番号(0 ～ )
     * @param prm_bgm_name プロパティファイルのkey文字列
     */
    virtual void ready(int prm_bgm_no, const char* prm_bgm_name) override;

    /**
     * BGMの振る舞い .
     * 主にボリュームを変化させ、フェードイン・アウト効果を持続処理させる。
     */
    void behave();

    /**
     * 演奏中のBGMにフェード効果を実行する。
     * @param prm_bgm_no              BGM番号(0 ～ )
     * @param prm_frame           フェードに費やすフレーム時間
     * @param prm_target_volume   到達目標ボリューム(0 ～ 100)
     */
    void fade(int prm_bgm_no, frame prm_frame, int prm_target_volume);

    /**
     * 演奏中のBGMにフェードイン効果を実行する。
     * フェードイン時間は setDefaultFadeFrames() 指定のフレーム数。
     * @param prm_bgm_no  BGM番号(0 ～ )
     */
    void fadein(int prm_bgm_no);

    /**
     * 演奏中のBGMにフェードイン効果を実行する。
     * @param prm_bgm_no  BGM番号(0 ～ )
     * @param prm_frame フェードインフレーム数
     */
    void fadein_f(int prm_bgm_no, frame prm_frame);

    /**
     * BGMを、フェードインによる再生を開始する。
     * フェードイン時間は setDefaultFadeFrames() 指定のフレーム数。
     * @param prm_bgm_no BGM番号(0 ～ )
     */
    void play_fadein(int prm_bgm_no);

    /**
     * BGMを、フェードインによる再生を開始する。
     * @param prm_bgm_no  BGM番号(0 ～ )
     * @param prm_frame フェードインフレーム数
     */
    void play_fadein_f(int prm_bgm_no, frame prm_frame);

    /**
     * 演奏中のBGMにフェードアウト効果を実行する。
     * フェードアウト時間は setDefaultFadeFrames() 指定のフレーム数。
     * @param prm_bgm_no BGM番号(0 ～ )
     */
    void fadeout(int prm_bgm_no);

    /**
     * 演奏中のBGMにフェードアウト効果を実行する。
     * @param prm_bgm_no BGM番号(0 ～ )
     * @param prm_frame フェードアウトフレーム数
     */
    void fadeout_f(int prm_bgm_no, frame prm_frame);

    /**
     * 演奏中のBGMにフェードアウト効果を実行し、フェードアウト後演奏を停止する。
     * フェードアウト時間は setDefaultFadeFrames() 指定のフレーム数。
     * @param prm_bgm_no BGM番号(0 ～ )
     */
    void fadeout_stop(int prm_bgm_no);

    /**
     * 演奏中のBGMにフェードアウト効果を実行し、フェードアウト後演奏を停止する。
     * @param prm_bgm_no BGM番号(0 ～ )
     * @param prm_frame フェードアウトフレーム数
     */
    void fadeout_stop_f(int prm_bgm_no, frame prm_frame);

    /**
     * BGMの演奏を開始する(フェード効果無し)。
     * @param prm_bgm_no   BGM番号(0 ～ )
     * @param prm_is_loop  ループするかどうか（true:ループ再生する／false:ループ再生しない）
     */
    virtual void play(int prm_bgm_no, bool prm_is_loop = true) override;

    /**
     * 全BGM番号の演奏中のBGMにフェードアウト効果を実行し、フェードアウト後演奏を停止する。
     * フェードアウト時間は setDefaultFadeFrames() 指定のフレーム数。
     */
    void fadeout_stop();

    /**
     * 全BGM番号のフェードインフェードアウト時のデフォルトフレーム時間を設定 .
     * 初期設定値は360フレーム。
     * @param prm_default_fade フェードに費やすフレーム時間
     */
    void setDefaultFadeFrames(frame prm_default_fade) {
        _default_fade = prm_default_fade;
    }

    virtual ~GgafDxBgmPerformerForScene();
};

}
#endif /*GGAFDXCORE_GGAFDXBGMPERFORMERFORSCENE_H_*/
