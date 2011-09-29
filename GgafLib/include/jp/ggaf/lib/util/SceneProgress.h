#ifndef SCENEPROGRESS_H_
#define SCENEPROGRESS_H_
namespace GgafLib {

/**
 * �i���Ǘ�(�V�[���p)�N���X .
 * @version 1.00
 * @since 2011/07/15
 * @author Masatoshi Tsuge
 */
class SceneProgress : public GgafCore::GgafProgress {
public:
    /** �i���Ǘ��ΏۃV�[�� */
    DefaultScene* _pScene;
    /** �i���ԍ� �� �T�u�V�[�� */
    std::map<progress, DefaultScene*> _mapProg2Scene;

    /**
     * �R���X�g���N�^ .
     * @param prm_pScene       �i�����Ǘ��������ΏۃV�[��
     * @param prm_num_progress �ő�i���ԍ���(10��ݒ肷��� 0�ԁ`10�Ԃ�11�̐i����Ԃ��g�p�\�ƂȂ�)
     */
    SceneProgress(DefaultScene* prm_pScene, int prm_num_progress);

    /**
     * �i����ԂƃT�u�V�[�����֘A�t���A��������.
     * ���̃��\�b�h�ɂ��A�֘A�t�����s���ƁA�ȉ��̃��\�b�h���g�p�\�i���ʂ���j�ƂȂ�܂��B<BR>
     * <code>
     * changeWithScene_Flipping(progress)
     * changeWithScene_Crossfading(progress, frame);
     * changeWithScene_Overlapping(progress, frame);
     * </code>
     * @param prm_FirstProgress �擪�̐i�����
     * @param prm_EndProgress �����̐i�����
     * @param prm_FirstSubSceneName �擪�̐i�����(prm_FirstProgress)�ɑΉ�����T�u�V�[���̖���
     */
    void relatSubScene(progress prm_FirstProgress, progress prm_EndProgress, const char* prm_FirstSubSceneName);

    /**
     * �i����ԂƃT�u�V�[�����֘A�t���A��������.
     * ���̃��\�b�h�ɂ��A�֘A�t�����s���ƁA�ȉ��̃��\�b�h���g�p�\�i���ʂ���j�ƂȂ�܂��B<BR>
     * <code>
     * changeWithScene_Flipping(progress)
     * changeWithScene_Crossfading(progress, frame);
     * changeWithScene_Overlapping(progress, frame);
     * </code>
     * @param prm_FirstProgress �擪�̐i�����
     * @param prm_EndProgress �����̐i�����
     * @param prm_FirstSubSceneName �擪�̐i�����(prm_FirstProgress)�ɑΉ�����T�u�V�[��
     */
    void relatSubScene(progress prm_FirstProgress, progress prm_EndProgress, DefaultScene* prm_pFirstSubScene);

    /**
     * �V�����i����Ԃ�؂�ւ���Ɠ����ɁA�֘A�t�����T�u�V�[����������Ԃɂ��� .
     * @param prm_progress
     */
    void changeWithScene(progress prm_progress);

    /**
     * �V�����i����Ԃ�؂�ւ���Ɠ����ɁA�֘A�t�����T�u�V�[����������Ԃɐ؂�ւ��A
     * ������ԃT�u�V�[���͔񊈓���Ԃɂ��� .
     * @param prm_progress �V�����i�����
     */
    void changeWithScene_Flipping(progress prm_progress);

    /**
     * �V�����i����Ԃ�؂�ւ���Ɠ����ɁA�֘A�t�����T�u�V�[����������Ԃɐ؂�ւ��A
     * ������ԃT�u�V�[���͔񊈓���Ԃɂ���B���̍ہA�t�F�[�h�A�E�g�E�t�F�[�h�C�����ʂ��s�� .
     * @param prm_progress �V�����i�����
     * @param prm_fade_frames �t�F�[�h�C���E�t�F�[�h�A�E�g���s������
     */
    void changeWithScene_Crossfading(progress prm_progress, frame prm_fade_frames = 300);

    //������
    void changeWithScene_FadeoutFadin(progress prm_progress, frame prm_fade_frames = 300);
    /**
     * �V�����i����Ԃ�؂�ւ���Ɠ����ɁA�֘A�t�����T�u�V�[����������Ԃɐ؂�ւ��A
     * ������ԃT�u�V�[���͔񊈓���Ԃɂ���B���̍ہA�w��t���[���ԁA�����i�s�i�I�[�o�[���b�s���O�j������ .
     * @param prm_progress �V�����i�����
     * @param prm_frames �����i�s������t���[����
     */
    void changeWithScene_Overlapping(progress prm_progress, frame prm_frames);

    /**
     * ���݂̐i����ԂɊ֘A�Â��Ă���V�[�����擾 .
     * @return
     */
    DefaultScene* getGazeScene();

    /**
     * �f�X�g���N�^ .
     */
    virtual ~SceneProgress();
};

}
#endif /*SCENEPROGRESS_H_*/
