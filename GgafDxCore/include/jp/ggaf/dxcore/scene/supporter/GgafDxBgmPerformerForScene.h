#ifndef GGAFDXBGMPERFORMERFORSCENE_H_
#define GGAFDXBGMPERFORMERFORSCENE_H_
namespace GgafDxCore {

/**
 * BGM演奏支援クラス .
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
    GgafDxScene* _pDxScene;
    double* _paDouble_target_volume;
    double* _paDouble_inc_volume;
    bool* _paBool_is_fade;
    bool* _paBool_is_fadeout_stop;
    frame _default_fade;

    GgafDxBgmPerformerForScene(GgafDxScene* prm_pDxScene);

    /**
     * BGM数を宣言 .
     * @param prm_bgm_num       演奏するBGM数
     * @param prm_default_fade  フェードインフェードアウト時のフレーム時間
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

    virtual void behave();
    virtual void fade(int prm_id, frame prm_frame, int prm_target_volume);

    virtual void fadein(int prm_id);
    virtual void play_fadein(int prm_id);
    virtual void fadeout(int prm_id);
    virtual void fadeout_stop(int prm_id);

    virtual void play(int prm_id, int prm_volume, bool prm_is_loop) override;

    virtual void fadeout_stop();
    virtual ~GgafDxBgmPerformerForScene();
};

}
#endif /*GGAFDXBGMPERFORMERFORSCENE_H_*/
