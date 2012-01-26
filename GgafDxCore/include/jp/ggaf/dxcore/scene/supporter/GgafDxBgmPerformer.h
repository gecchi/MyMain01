#ifndef GGAFDXBGMPERFORMER_H_
#define GGAFDXBGMPERFORMER_H_
namespace GgafDxCore {

/**
 * BGM演奏支援クラス .
 * @version 1.00
 * @since 2010/04/19
 * @author Masatoshi Tsuge
 */
class GgafDxBgmPerformer : public GgafCore::GgafObject {
private:


public:
    static int _active_bgm_bpm;

    bool* _pa_is_fade;
    bool* _pa_is_fadeout_stop;
    double* _pa_now_volume;
    double* _pa_target_volume;
    double* _pa_inc_volume;
    int _bgm_num;
    /** Bgm資源接続 */
    GgafDxBgmConnection** _papBgmCon;

    GgafDxBgmPerformer();
    void useBgm(int prm_bgm_num);
    /**
     *
     * @param prm_id 番号ID
     * @param prm_bgm_name プロパティファイルの_OGG, _BPM, _TITLE のプレフィックスとなっているkey文字列
     *
     */
    void set(int prm_id, const char* prm_bgm_name);
    void behave();
    void fade(int prm_id, frame prm_frame, int prm_target_volume);

    void fadein(int prm_id, int prm_frame) {
        fade(prm_id, prm_frame, GGAF_MAX_VOLUME);
    }
    void fadeout(int prm_id, int prm_frame) {
        fade(prm_id, prm_frame, GGAF_MIN_VOLUME);
        _pa_is_fadeout_stop[prm_id] = false;
    }
    void fadeout_stop(int prm_id, int prm_frame) {
        fade(prm_id, prm_frame, GGAF_MIN_VOLUME);
        _pa_is_fadeout_stop[prm_id] = true;
    }

//    void prepare(int prm_id, const char* prm_se_name) ;
    void setVolume(int prm_id, int prm_volume);
    void play(int prm_id, bool prm_is_loop) {
        play(prm_id, GGAF_MAX_VOLUME, prm_is_loop);
    }

    void play(int prm_id, int prm_volume, bool prm_is_loop);

    void stop(int prm_id);

    void pause(int prm_id);
    virtual ~GgafDxBgmPerformer();
};

}
#endif /*GGAFDXBGMPERFORMER_H_*/
