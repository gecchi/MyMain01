#ifndef GGAFDX9SCENE_H_
#define GGAFDX9SCENE_H_
namespace GgafDx9Core {

#define MAX_BGM_PER_ACTOR 3

/**
 * GgafDx9Core���O��ԁA���V�[���N���X.
 * GgafMainScene ���p�����������ł��B<BR>
 * GgafDx9Core���O��ԓ��ł́A���̃N���X�����V�[���Ƃ��܂��B<BR>
 * @version 1.00
 * @since 2008/01/24
 * @author Masatoshi Tsuge
 */
class GgafDx9Scene : public GgafCore::GgafMainScene {
private:
    void processPreJudgement() override;

public:
    /** Bgm�����ڑ� */
    GgafDx9BgmConnection** _papBgmCon;

    GgafDx9Scene(const char* prm_name);
    void fadeinBgm(int prm_id, int prm_frame);
    void fadeoutBgm(int prm_id, int prm_frame);
    void prepareBgm(int prm_id, const char* prm_se_name, int prm_cannel = 1) ;
    void playBgm(int prm_id, bool prm_is_loop) {
        playBgm(prm_id, DSBVOLUME_MAX, prm_is_loop);
    }
    void playBgm(int prm_id, int prm_volume, bool prm_is_loop);
    virtual ~GgafDx9Scene();
};

}
#endif /*GGAFDX9SCENE_H_*/
