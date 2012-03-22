#ifndef GGAFDXBGMPERFORMERFORSCENE_H_
#define GGAFDXBGMPERFORMERFORSCENE_H_
namespace GgafDxCore {

/**
 * BGM‰‰‘tŽx‰‡ƒNƒ‰ƒX .
 * GgafDxBgmPerformer ‚©‚ç•ª—£
 * @version 1.00
 * @since 2012/03/22
 * @author Masatoshi Tsuge
 */
class GgafDxBgmPerformerForScene : public GgafDxBgmPerformer {
private:


public:
    GgafDxScene* _pDxScene;
    double* _pa_target_volume;
    double* _pa_inc_volume;
    bool* _pa_is_fade;
    bool* _pa_is_fadeout_stop;
    frame _default_fade;

    GgafDxBgmPerformerForScene(GgafDxScene* prm_pDxScene);

    virtual void useBgm(int prm_bgm_num, frame prm_default_fade);
    virtual void useBgm(int prm_bgm_num) override {
        useBgm(prm_bgm_num, 360);
    }

    virtual void behave();
    virtual void fade(int prm_id, frame prm_frame, int prm_target_volume);

    virtual void fadein(int prm_id, frame prm_frame);
    virtual void play_fadein(int prm_id, frame prm_frame);
    virtual void fadeout(int prm_id, frame prm_frame);
    virtual void fadeout_stop(int prm_id, frame prm_frame);

    virtual void fadein(int prm_id);
    virtual void play_fadein(int prm_id);
    virtual void fadeout(int prm_id);
    virtual void fadeout_stop(int prm_id);

    virtual void play(int prm_id, int prm_volume, bool prm_is_loop) override;


    virtual ~GgafDxBgmPerformerForScene();
};

}
#endif /*GGAFDXBGMPERFORMERFORSCENE_H_*/
