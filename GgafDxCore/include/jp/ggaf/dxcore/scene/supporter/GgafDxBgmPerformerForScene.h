#ifndef GGAFDXBGMPERFORMERFORSCENE_H_
#define GGAFDXBGMPERFORMERFORSCENE_H_
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
private:

    void fadein_f(int prm_id, frame prm_frame);
    void play_fadein_f(int prm_id, frame prm_frame);
    void fadeout_f(int prm_id, frame prm_frame);
    void fadeout_stop_f(int prm_id, frame prm_frame);

public:
    /** [r]BGMと関連付くシーン */
    GgafDxScene* _pDxScene;
    /** [r]フェードターゲットボリュームの配列(添字はチャンネル) */
    double* _paDouble_target_volume;
    /** [r]ボリューム加算値の配列(添字はチャンネル) */
    double* _paDouble_inc_volume;
    /** [r]現在フェード中か否かの配列(添字はチャンネル) */
    bool* _paBool_is_fade;
    /** [r]フェード後停止させるのかどうかの配列(添字はチャンネル) */
    bool* _paBool_is_fadeout_stop;
    /** [r/w]デフォルトのフェードイン・フェードアウトの費やすフレーム時間 */
    frame _default_fade;

public:
    /**
     * コンストラクタ
     * @param prm_pDxScene シーン
     */
    GgafDxBgmPerformerForScene(GgafDxScene* prm_pDxScene);

    /**
     * BGM数を宣言 .
     * @param prm_bgm_num       演奏するBGM数
     * @param prm_default_fade  フェードインフェードアウト時のデフォルトフレーム時間
     */
    virtual void useBgm(int prm_bgm_num, frame prm_default_fade);

    /**
     * BGM数を宣言 .
     * フェードインフェードアウト時のフレーム時間は360(6秒)に設定される。
     * @param prm_bgm_num 演奏するBGM数
     */
    virtual void useBgm(int prm_bgm_num) override {
        useBgm(prm_bgm_num, 360);
    }

    /**
     * BGMの振る舞い .
     * 主にボリュームを変化させ、フェードイン・アウト効果を持続処理させる。
     */
    virtual void behave();

    /**
     * 再生中のBGMにフェード効果を実行する。
     * @param prm_id              BGMチャンネル番号(0 ～ )
     * @param prm_frame           フェードに費やすフレーム時間
     * @param prm_target_volume   到達目標ボリューム(0 ～ 100)
     */
    virtual void fade(int prm_id, frame prm_frame, int prm_target_volume);

    /**
     * 再生中のBGMにフェードイン効果を実行する。
     * @param prm_id  BGMチャンネル番号(0 ～ )
     */
    virtual void fadein(int prm_id);

    /**
     * BGMを、フェードインによる再生を開始する。
     * @param prm_id BGMチャンネル番号(0 ～ )
     */
    virtual void play_fadein(int prm_id);

    /**
     * 再生中のBGMにフェードアウト効果を実行する。
     * @param prm_id BGMチャンネル番号(0 ～ )
     */
    virtual void fadeout(int prm_id);

    /**
     * 再生中のBGMにフェードアウト効果を実行し、フェードアウト後演奏を停止する。
     * @param prm_id BGMチャンネル番号(0 ～ )
     */
    virtual void fadeout_stop(int prm_id);

    /**
     * BGMを、フェード効果無しで、普通に再生を開始する。
     * @param prm_id       BGMチャンネル番号(0 ～ )
     * @param prm_volume   ボリューム(0～100)
     * @param prm_is_loop  ループするかどうか（true:ループ再生する／false:ループ再生しない）
     */
    virtual void play(int prm_id, int prm_volume, bool prm_is_loop) override;

    /**
     * 全チャンネル番号の再生中のBGMにフェードアウト効果を実行し、フェードアウト後演奏を停止する。
     */
    virtual void fadeout_stop();

    /**
     * フェードインフェードアウト時のデフォルトフレーム時間を設定 .
     * @param prm_default_fade フェードに費やすフレーム時間
     */
    void setDefaultFadeFrames(frame prm_default_fade) {
        _default_fade = prm_default_fade;
    }

    virtual ~GgafDxBgmPerformerForScene();
};

}
#endif /*GGAFDXBGMPERFORMERFORSCENE_H_*/
