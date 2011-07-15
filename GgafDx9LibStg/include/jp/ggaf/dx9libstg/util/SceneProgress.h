#ifndef SCENETRANSITIONER_H_
#define SCENETRANSITIONER_H_
namespace GgafDx9LibStg {


class SceneProgress : public GgafCore::GgafProgress {
public:
    DefaultScene* _pScene;
    /** 進捗番号 対 サブシーン */
    std::map<progress, DefaultScene*> _mapProg2Scene;

    SceneProgress(DefaultScene* prm_pScene, int prm_num_progress);
    void affectSubScene(progress prm_FirstProgress, const char* prm_FirstSubSceneName);
    void affectSubScene(progress prm_FirstProgress, DefaultScene* prm_pFirstSubScene);
    void changeWithFlippingSubScene(progress prm_progress);
    void changeWithCrossfadingSubScene(progress prm_progress, frame prm_fade_frames = 60);
    DefaultScene* getAffect(progress prm_progress);
    virtual ~SceneProgress();
};

}
#endif /*SCENETRANSITIONER_H_*/
