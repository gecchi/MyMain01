#ifndef GGAFDXBGMPERFORMERFORSCENE_H_
#define GGAFDXBGMPERFORMERFORSCENE_H_
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
private:

    void fadein_f(int prm_id, frame prm_frame);
    void play_fadein_f(int prm_id, frame prm_frame);
    void fadeout_f(int prm_id, frame prm_frame);
    void fadeout_stop_f(int prm_id, frame prm_frame);

public:
    /** [r]BGM�Ɗ֘A�t���V�[�� */
    GgafDxScene* _pDxScene;
    /** [r]�t�F�[�h�^�[�Q�b�g�{�����[���̔z��(�Y���̓`�����l��) */
    double* _paDouble_target_volume;
    /** [r]�{�����[�����Z�l�̔z��(�Y���̓`�����l��) */
    double* _paDouble_inc_volume;
    /** [r]���݃t�F�[�h�����ۂ��̔z��(�Y���̓`�����l��) */
    bool* _paBool_is_fade;
    /** [r]�t�F�[�h���~������̂��ǂ����̔z��(�Y���̓`�����l��) */
    bool* _paBool_is_fadeout_stop;
    /** [r/w]�f�t�H���g�̃t�F�[�h�C���E�t�F�[�h�A�E�g�̔�₷�t���[������ */
    frame _default_fade;

public:
    /**
     * �R���X�g���N�^
     * @param prm_pDxScene �V�[��
     */
    GgafDxBgmPerformerForScene(GgafDxScene* prm_pDxScene);

    /**
     * BGM����錾 .
     * @param prm_bgm_num       ���t����BGM��
     * @param prm_default_fade  �t�F�[�h�C���t�F�[�h�A�E�g���̃f�t�H���g�t���[������
     */
    virtual void useBgm(int prm_bgm_num, frame prm_default_fade);

    /**
     * BGM����錾 .
     * �t�F�[�h�C���t�F�[�h�A�E�g���̃t���[�����Ԃ�360(6�b)�ɐݒ肳���B
     * @param prm_bgm_num ���t����BGM��
     */
    virtual void useBgm(int prm_bgm_num) override {
        useBgm(prm_bgm_num, 360);
    }

    /**
     * BGM�̐U�镑�� .
     * ��Ƀ{�����[����ω������A�t�F�[�h�C���E�A�E�g���ʂ���������������B
     */
    virtual void behave();

    /**
     * �Đ�����BGM�Ƀt�F�[�h���ʂ����s����B
     * @param prm_id              BGM�`�����l���ԍ�(0 �` )
     * @param prm_frame           �t�F�[�h�ɔ�₷�t���[������
     * @param prm_target_volume   ���B�ڕW�{�����[��(0 �` 100)
     */
    virtual void fade(int prm_id, frame prm_frame, int prm_target_volume);

    /**
     * �Đ�����BGM�Ƀt�F�[�h�C�����ʂ����s����B
     * @param prm_id  BGM�`�����l���ԍ�(0 �` )
     */
    virtual void fadein(int prm_id);

    /**
     * BGM���A�t�F�[�h�C���ɂ��Đ����J�n����B
     * @param prm_id BGM�`�����l���ԍ�(0 �` )
     */
    virtual void play_fadein(int prm_id);

    /**
     * �Đ�����BGM�Ƀt�F�[�h�A�E�g���ʂ����s����B
     * @param prm_id BGM�`�����l���ԍ�(0 �` )
     */
    virtual void fadeout(int prm_id);

    /**
     * �Đ�����BGM�Ƀt�F�[�h�A�E�g���ʂ����s���A�t�F�[�h�A�E�g�㉉�t���~����B
     * @param prm_id BGM�`�����l���ԍ�(0 �` )
     */
    virtual void fadeout_stop(int prm_id);

    /**
     * BGM���A�t�F�[�h���ʖ����ŁA���ʂɍĐ����J�n����B
     * @param prm_id       BGM�`�����l���ԍ�(0 �` )
     * @param prm_volume   �{�����[��(0�`100)
     * @param prm_is_loop  ���[�v���邩�ǂ����itrue:���[�v�Đ�����^false:���[�v�Đ����Ȃ��j
     */
    virtual void play(int prm_id, int prm_volume, bool prm_is_loop) override;

    /**
     * �S�`�����l���ԍ��̍Đ�����BGM�Ƀt�F�[�h�A�E�g���ʂ����s���A�t�F�[�h�A�E�g�㉉�t���~����B
     */
    virtual void fadeout_stop();

    /**
     * �t�F�[�h�C���t�F�[�h�A�E�g���̃f�t�H���g�t���[�����Ԃ�ݒ� .
     * @param prm_default_fade �t�F�[�h�ɔ�₷�t���[������
     */
    void setDefaultFadeFrames(frame prm_default_fade) {
        _default_fade = prm_default_fade;
    }

    virtual ~GgafDxBgmPerformerForScene();
};

}
#endif /*GGAFDXBGMPERFORMERFORSCENE_H_*/
