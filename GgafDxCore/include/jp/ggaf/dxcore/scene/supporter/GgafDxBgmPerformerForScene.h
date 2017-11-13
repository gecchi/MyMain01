#ifndef GGAFDXCORE_GGAFDXBGMPERFORMERFORSCENE_H_
#define GGAFDXCORE_GGAFDXBGMPERFORMERFORSCENE_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgmPerformer.h"

namespace GgafDxCore {

/**
 * BGM���t�x���N���X .
 * �V�[���I�u�W�F�N�g�ɁA�ێ�����鎖�ɂ���āA
 * BGM�t�F�[�h�C���A�t�F�[�h�A�E�g�@�\��t���B
 * GgafDxScene::processSettlementBehavior() �ŁA�{�N���X��
 * behave() ���\�b�h���R�[�������d�l�B<BR>
 * GgafDxBgmPerformer ���番��
 * @version 1.00
 * @since 2012/03/22
 * @author Masatoshi Tsuge
 */
class GgafDxBgmPerformerForScene : public GgafDxBgmPerformer {
public:
    /** [r]BGM�Ɗ֘A�t���V�[�� */
    GgafDxScene* _pDxScene;
    /** [r]�t�F�[�h�^�[�Q�b�g�{�����[���̔z��(�Y���̓`�����l��) */
    std::vector<double> _vec_target_volume;
    /** [r]�{�����[�����Z�l�̔z��(�Y���̓`�����l��) */
    std::vector<double> _vec_inc_volume;
    /** [r]���݃t�F�[�h�����ۂ��̔z��(�Y���̓`�����l��) */
    std::vector<bool> _vec_is_fade;
    /** [r]�t�F�[�h���~������̂��ǂ����̔z��(�Y���̓`�����l��) */
    std::vector<bool> _vec_is_fadeout_stop;
    /** [r/w]�f�t�H���g�̃t�F�[�h�C���E�t�F�[�h�A�E�g�̔�₷�t���[������ */
    frame _default_fade;

public:
    /**
     * �R���X�g���N�^
     * @param prm_pDxScene �V�[��
     */
    GgafDxBgmPerformerForScene(GgafDxScene* prm_pDxScene);

    /**
     * BGM��ݒ肷��B
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     * @param prm_bgm_name �v���p�e�B�t�@�C����key������
     */
    virtual void ready(int prm_bgm_no, const char* prm_bgm_name) override;

    /**
     * BGM�̐U�镑�� .
     * ��Ƀ{�����[����ω������A�t�F�[�h�C���E�A�E�g���ʂ���������������B
     */
    void behave();

    /**
     * ���t����BGM�Ƀt�F�[�h���ʂ����s����B
     * @param prm_bgm_no              BGM�ԍ�(0 �` )
     * @param prm_frame           �t�F�[�h�ɔ�₷�t���[������
     * @param prm_target_volume   ���B�ڕW�{�����[��(0 �` 100)
     */
    void fade(int prm_bgm_no, frame prm_frame, int prm_target_volume);

    /**
     * ���t����BGM�Ƀt�F�[�h�C�����ʂ����s����B
     * �t�F�[�h�C�����Ԃ� setDefaultFadeFrames() �w��̃t���[�����B
     * @param prm_bgm_no  BGM�ԍ�(0 �` )
     */
    void fadein(int prm_bgm_no);

    /**
     * ���t����BGM�Ƀt�F�[�h�C�����ʂ����s����B
     * @param prm_bgm_no  BGM�ԍ�(0 �` )
     * @param prm_frame �t�F�[�h�C���t���[����
     */
    void fadein_f(int prm_bgm_no, frame prm_frame);

    /**
     * BGM���A�t�F�[�h�C���ɂ��Đ����J�n����B
     * �t�F�[�h�C�����Ԃ� setDefaultFadeFrames() �w��̃t���[�����B
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     */
    void play_fadein(int prm_bgm_no);

    /**
     * BGM���A�t�F�[�h�C���ɂ��Đ����J�n����B
     * @param prm_bgm_no  BGM�ԍ�(0 �` )
     * @param prm_frame �t�F�[�h�C���t���[����
     */
    void play_fadein_f(int prm_bgm_no, frame prm_frame);

    /**
     * ���t����BGM�Ƀt�F�[�h�A�E�g���ʂ����s����B
     * �t�F�[�h�A�E�g���Ԃ� setDefaultFadeFrames() �w��̃t���[�����B
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     */
    void fadeout(int prm_bgm_no);

    /**
     * ���t����BGM�Ƀt�F�[�h�A�E�g���ʂ����s����B
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     * @param prm_frame �t�F�[�h�A�E�g�t���[����
     */
    void fadeout_f(int prm_bgm_no, frame prm_frame);

    /**
     * ���t����BGM�Ƀt�F�[�h�A�E�g���ʂ����s���A�t�F�[�h�A�E�g�㉉�t���~����B
     * �t�F�[�h�A�E�g���Ԃ� setDefaultFadeFrames() �w��̃t���[�����B
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     */
    void fadeout_stop(int prm_bgm_no);

    /**
     * ���t����BGM�Ƀt�F�[�h�A�E�g���ʂ����s���A�t�F�[�h�A�E�g�㉉�t���~����B
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     * @param prm_frame �t�F�[�h�A�E�g�t���[����
     */
    void fadeout_stop_f(int prm_bgm_no, frame prm_frame);

    /**
     * BGM�̉��t���J�n����(�t�F�[�h���ʖ���)�B
     * @param prm_bgm_no   BGM�ԍ�(0 �` )
     * @param prm_is_loop  ���[�v���邩�ǂ����itrue:���[�v�Đ�����^false:���[�v�Đ����Ȃ��j
     */
    virtual void play(int prm_bgm_no, bool prm_is_loop = true) override;

    /**
     * �SBGM�ԍ��̉��t����BGM�Ƀt�F�[�h�A�E�g���ʂ����s���A�t�F�[�h�A�E�g�㉉�t���~����B
     * �t�F�[�h�A�E�g���Ԃ� setDefaultFadeFrames() �w��̃t���[�����B
     */
    void fadeout_stop();

    /**
     * �SBGM�ԍ��̃t�F�[�h�C���t�F�[�h�A�E�g���̃f�t�H���g�t���[�����Ԃ�ݒ� .
     * �����ݒ�l��360�t���[���B
     * @param prm_default_fade �t�F�[�h�ɔ�₷�t���[������
     */
    void setDefaultFadeFrames(frame prm_default_fade) {
        _default_fade = prm_default_fade;
    }

    virtual ~GgafDxBgmPerformerForScene();
};

}
#endif /*GGAFDXCORE_GGAFDXBGMPERFORMERFORSCENE_H_*/
