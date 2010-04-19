#ifndef GGAFDX9BGMPERFORMER_H_
#define GGAFDX9BGMPERFORMER_H_
namespace GgafDx9Core {

#define MAX_BGM_PER_ACTOR 3

/**
 * GgafDx9Core名前空間、基底シーンクラス.
 * GgafMainScene を継承しただけです。<BR>
 * GgafDx9Core名前空間内では、このクラスを基底シーンとします。<BR>
 * @version 1.00
 * @since 2008/01/24
 * @author Masatoshi Tsuge
 */
class GgafDx9BgmPerformer : public GgafCore::GgafObject {
private:


public:
    bool* _pa_is_fade;
    double* _pa_now_volume;
    double* _pa_target_volume;
    double* _pa_inc_volume;
    int _bgm_num;
    /** Bgm資源接続 */
    GgafDx9BgmConnection** _papBgmCon;

    GgafDx9BgmPerformer();
    void useBgm(int prm_bgm_num);
	void set(int prm_id, const char* prm_bgm_name);
    void behave();
    void fade(int prm_id, DWORD prm_frame, int prm_target_volume);

    void fadein(int prm_id, int prm_frame) {
        fade(prm_id, prm_frame, DSBVOLUME_MAX);
    }
    void fadeout(int prm_id, int prm_frame) {
        fade(prm_id, prm_frame, DSBVOLUME_MIN);
    }

    void prepare(int prm_id, const char* prm_se_name) ;
    void setVolume(int prm_id, int prm_volume);
    void play(int prm_id, bool prm_is_loop) {
        play(prm_id, DSBVOLUME_MAX, prm_is_loop);
    }

    void play(int prm_id, int prm_volume, bool prm_is_loop);
    virtual ~GgafDx9BgmPerformer();
};

}
#endif /*GGAFDX9BGMPERFORMER_H_*/
