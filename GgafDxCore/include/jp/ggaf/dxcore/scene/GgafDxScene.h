#ifndef GGAFDXCORE_GGAFDXSCENE_H_
#define GGAFDXCORE_GGAFDXSCENE_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/scene/GgafMainScene.h"

#include "jp/ggaf/core/util/GgafCurtain.hpp"

namespace GgafDxCore {

/**
 * GgafDxCore���O��ԁA���V�[���N���X.
 * ���̋@�\���V�[���N���X�ɒǉ����Ă��܂��B<BR>
 * �EBGM���t<BR>
 * �EBGM�t�F�[�h�C���E�t�F�[�h�A�E�g<BR>
 * �E�V�[�������̕`��I�u�W�F�N�g�̃t�F�[�h�C���E�t�F�[�h�A�E�g<BR>
 * GgafDxCore���O��ԓ��ł́A���̃N���X�����V�[���Ƃ��܂��B<BR>
 * @version 1.00
 * @since 2008/01/24
 * @author Masatoshi Tsuge
 */
class GgafDxScene : public GgafCore::GgafMainScene {
private :

    /**
     * draw() �̃I�[�o�[���C�h�֎~ .
     * ���E(GgafDxSpacetime)���S�Ă̕`����s���d�g�݂ɂȂ�܂����B<BR>
     * ���������āA�I�[�o�[���C�h���Ă��t���[�����[�N���Ăяo����邱�Ƃ͂���܂���B<BR>
     * ����ăI�[�o�[���C�h���Ȃ����߂� private �Ŏ����B<BR>
     * GgafDxSpacetime::draw() ���Q�Ƃ���B<BR>
     */
    void draw() override {
    }

public :
    /** [r]�V�[���̃t�F�[�h�C���E�A�E�g�p�J�[�e���i�f�t�H���g�ł̓��J�[�e���j */
    GgafDxSceneCurtain* _pCurtain;
    /** [r]BGM���t�� */
    GgafDxBgmConductor* _pConductor;
    /** [r]�V�[���̃� */
    float _scene_alpha;
    float _scene_alpha_from_top;
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @return
     */
    GgafDxScene(const char* prm_name, GgafCore::GgafSceneMediator* prm_pSceneMediator = nullptr);

    void setSceneAlpha(float prm_scene_alpha);
    float getSceneAlpha();
    void addSceneAlpha(float prm_scene_alpha);

    void setSceneAlphaFromTop(float prm_scene_alpha_from_top);
    float getSceneAlphaFromTop();

    /**
     * �J�[�e����t���ւ��� .
     * @param prm_pCurtain_new �V�����J�[�e��
     */
    void chengeCurtain(GgafDxSceneCurtain* prm_pCurtain_new);

    GgafDxSceneCurtain* getSceneCurtain() {
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
     * BGM�́A�V�[�������o�[�� _pConductor(GgafDxBgmConductor�I�u�W�F�N�g) ��
     * ���t����Ă��邱�Ƃ��O��B
     * @param prm_frame_fade �t�F�[�h�A�E�g�t���[����
     */
    void fadeoutSceneWithBgm(int prm_frame_fade);

    /**
     * ���c���[�V�[���̃A�N�^�[���t�F�[�h�A�E�g������Ɠ����ɁABGM���t�F�[�h�A�E�g������ .
     * BGM�́A�V�[�������o�[�� _pConductor(GgafDxBgmConductor�I�u�W�F�N�g) ��
     * ���t����Ă��邱�Ƃ��O��B
     * @param prm_frame_fade �t�F�[�h�A�E�g�t���[����
     */
    void fadeoutSceneWithBgmTree(int prm_frame_fade);


    inline GgafDxBgmConductor* getBgmConductor() {
        return _pConductor;
    }

    virtual void onEnd() override;

    virtual ~GgafDxScene();
};

}
#endif /*GGAFDXCORE_GGAFDXSCENE_H_*/
