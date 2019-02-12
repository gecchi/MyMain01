#ifndef GGAF_DX_SCENE_H_
#define GGAF_DX_SCENE_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/scene/MainScene.h"

#include "jp/ggaf/core/util/Curtain.hpp"

namespace GgafDx {

/**
 * Core���O��ԁA���V�[���N���X.
 * ���̋@�\���V�[���N���X�ɒǉ����Ă��܂��B<BR>
 * �EBGM���t<BR>
 * �EBGM�t�F�[�h�C���E�t�F�[�h�A�E�g<BR>
 * �E�V�[�������̕`��I�u�W�F�N�g�̃t�F�[�h�C���E�t�F�[�h�A�E�g<BR>
 * Core���O��ԓ��ł́A���̃N���X�����V�[���Ƃ��܂��B<BR>
 * @version 1.00
 * @since 2008/01/24
 * @author Masatoshi Tsuge
 */
class Scene : public GgafCore::MainScene {
private :

    /**
     * draw() �̃I�[�o�[���C�h�֎~ .
     * ���E(Spacetime)���S�Ă̕`����s���d�g�݂ɂȂ�܂����B<BR>
     * ���������āA�I�[�o�[���C�h���Ă��t���[�����[�N���Ăяo����邱�Ƃ͂���܂���B<BR>
     * ����ăI�[�o�[���C�h���Ȃ����߂� private �Ŏ����B<BR>
     * Spacetime::draw() ���Q�Ƃ���B<BR>
     */
    void draw() override {
    }

public :
    /** [r]�V�[���̃t�F�[�h�C���E�A�E�g�p�J�[�e���i�f�t�H���g�ł̓��J�[�e���j */
    SceneCurtain* _pCurtain;
    /** [r]BGM���t�� */
    BgmConductor* _pConductor;
    /** [r]�V�[���̃� */
    float _scene_alpha;
    float _scene_alpha_from_top;
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @return
     */
    Scene(const char* prm_name, GgafCore::SceneMediator* prm_pSceneMediator = nullptr);

    void setSceneAlpha(float prm_scene_alpha);
    float getSceneAlpha();
    void addSceneAlpha(float prm_scene_alpha);

    void setSceneAlphaFromTop(float prm_scene_alpha_from_top);
    float getSceneAlphaFromTop();

    /**
     * �J�[�e����t���ւ��� .
     * @param prm_pCurtain_new �V�����J�[�e��
     */
    void chengeCurtain(SceneCurtain* prm_pCurtain_new);

    SceneCurtain* getSceneCurtain() {
        return _pCurtain;
    }

    virtual void processPreJudgement() override;

    virtual void pauseTree() override;
    virtual void pause() override;

    virtual void unpauseTree() override;
    virtual void unpause() override;

    /**
     * ���V�[���̃A�N�^�[���t�F�[�h�C�������� .
     * @param prm_frame_fade �A���t�@�l�� 1.0 �ɂȂ�܂ł̎��s�t���[����(0�`)
     */
    void fadeinScene(int prm_frame_fade);

    /**
      * ���V�[���̃A�N�^�[���t�F�[�h�A�E�g������ .
     * @param prm_frame_fade �A���t�@�l�� 0.0 �ɂȂ�܂ł̎��s�t���[����(0�`)
     */
    void fadeoutScene(int prm_frame_fade);


    void fadeoutBgm(int prm_frame_fade);
    void fadeoutBgmTree(int prm_frame_fade);

    /**
     * ���V�[���̃A�N�^�[���t�F�[�h�A�E�g������Ɠ����ɁABGM���t�F�[�h�A�E�g������ .
     * BGM�́A�V�[�������o�[�� _pConductor(BgmConductor�I�u�W�F�N�g) ��
     * ���t����Ă��邱�Ƃ��O��B
     * @param prm_frame_fade �t�F�[�h�A�E�g�t���[����
     */
    void fadeoutSceneWithBgm(int prm_frame_fade);

    /**
     * ���c���[�V�[���̃A�N�^�[���t�F�[�h�A�E�g������Ɠ����ɁABGM���t�F�[�h�A�E�g������ .
     * BGM�́A�V�[�������o�[�� _pConductor(BgmConductor�I�u�W�F�N�g) ��
     * ���t����Ă��邱�Ƃ��O��B
     * @param prm_frame_fade �t�F�[�h�A�E�g�t���[����
     */
    void fadeoutSceneWithBgmTree(int prm_frame_fade);


    inline BgmConductor* getBgmConductor() {
        return _pConductor;
    }

    virtual void onEnd() override;

    virtual ~Scene();
};

}
#endif /*GGAF_DX_SCENE_H_*/
