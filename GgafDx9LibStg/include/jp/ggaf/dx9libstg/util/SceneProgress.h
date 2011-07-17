#ifndef SCENETRANSITIONER_H_
#define SCENETRANSITIONER_H_
namespace GgafDx9LibStg {


class SceneProgress : public GgafCore::GgafProgress {
public:
    DefaultScene* _pScene;
    /** �i���ԍ� �� �T�u�V�[�� */
    std::map<progress, DefaultScene*> _mapProg2Scene;

    SceneProgress(DefaultScene* prm_pScene, int prm_num_progress);
    void affectSubScene(progress prm_FirstProgress, progress prm_EndProgress, const char* prm_FirstSubSceneName);
    void affectSubScene(progress prm_FirstProgress, progress prm_EndProgress, DefaultScene* prm_pFirstSubScene);
    void changeWithFlippingSubScene(progress prm_progress);
    void changeWithCrossfadingSubScene(progress prm_progress, frame prm_fade_frames = 60);
    void changeWithOverlappingSubScene(progress prm_progress, frame prm_fade_frames);
    DefaultScene* getSubScene();
    virtual ~SceneProgress();
};

}
#endif /*SCENETRANSITIONER_H_*/
