#ifndef SCENEPROGRESS_H_
#define SCENEPROGRESS_H_
namespace GgafLib {

typedef std::map<progress, GgafLib::DefaultScene*> ProgSceneMap;

/**
 * ��ԑJ�ڐi���Ǘ�(�V�[���p)�N���X .
 * ����GgafProgress�N���X�ɁA�V�[���ɂ܂��֗��ȋ@�\��ǉ�����
 * �V�[����p�̏�ԑJ�ڐi���Ǘ��N���X�ł��B
 * @version 1.00
 * @since 2011/07/15
 * @author Masatoshi Tsuge
 */
class SceneProgress : public GgafCore::GgafProgress {

public:
    /** [r]�i���Ǘ��ΏۃV�[�� */
    DefaultScene* _pScene;
    /** [r]�i���ԍ� �� �T�u�V�[�� */
    ProgSceneMap _mapProg2Scene;

    progress _progress_next_promise;
    frame _count_next_promise;

public:
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
     * changeWithSceneFlipping(progress)
     * changeWithSceneCrossfading(progress, frame);
     * changeWithSceneOverlapping(progress, frame);
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
     * changeWithSceneFlipping(progress)
     * changeWithSceneCrossfading(progress, frame);
     * changeWithSceneOverlapping(progress, frame);
     * </code>
     * @param prm_FirstProgress �擪�̐i�����
     * @param prm_EndProgress   �����̐i�����
     * @param prm_pFirstSubScene �擪�̐i�����(prm_FirstProgress)�ɑΉ�����T�u�V�[��
     */
    void relatSubScene(progress prm_FirstProgress, progress prm_EndProgress, DefaultScene* prm_pFirstSubScene);

    /**
     * �V�����i����Ԃ�؂�ւ���Ɠ����ɁA�֘A�t�����T�u�V�[����������Ԃɂ��� .
     * ���݂̐i����ԂɕR�t���T�u�V�[���͂��̂܂܁i�񊈓��ɂ��܂���j .
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relatSubScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @param prm_progress �V�����i�����
     */
    void changeWithScene(progress prm_progress);

    /**
     * �V�����i����Ԃ�؂�ւ���Ɠ����ɁA�֘A�t�����T�u�V�[���ɐ؂�ւ� .
     * ���݂̐i����ԂɕR�t���T�u�V�[���͔񊈓���Ԃɂ��A�����̐i����ԂɕR�t���T�u�V�[����������Ԃɂ��܂��B
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relatSubScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @param prm_progress �V�����i�����
     */
    void changeWithSceneFlipping(progress prm_progress);

    /**
     * �V�����i����Ԃ�؂�ւ���Ɠ����ɁA�֘A�t�����T�u�V�[����������Ԃɐ؂�ւ��A
     * ������ԃT�u�V�[���͔񊈓���Ԃɂ���B���̍ہA�t�F�[�h�A�E�g�E�t�F�[�h�C�����ʂ��s�� .
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relatSubScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @param prm_progress �V�����i�����
     * @param prm_cross_fade_frames �t�F�[�h�C�� & �t�F�[�h�A�E�g���s������
     */
    void changeWithSceneCrossfading(progress prm_progress, frame prm_cross_fade_frames = 300);

    /**
     * ���i����ԂɕR�t���T�u�V�[���̓t�F�[�h�A�E�g���񊈓���Ԃɂ��A
     * ���̌㒼���Ɏ��̐V�����i����ԂɕR�t���T�u�V�[�����A�t�F�[�h�C����������Ԃɂ���B .
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relatSubScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @param prm_progress �V�����i�����
     * @param prm_fade_out �t�F�[�h�A�E�g����
     * @param prm_fade_in �t�F�[�h�C������
     */
    void changeWithSceneFadeoutFadein(progress prm_progress, frame prm_fade_out=120, frame prm_fade_in = 120);

    /**
     * �V�����i����Ԃ�؂�ւ���Ɠ����ɁA�֘A�t�����T�u�V�[����������Ԃɐ؂�ւ��A
     * ������ԃT�u�V�[���͔񊈓���Ԃɂ���B���̍ہA�w��t���[���ԁA�����i�s�i�I�[�o�[���b�s���O�j������ .
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relatSubScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @param prm_progress �V�����i�����
     * @param prm_overlapping_frames �����i�s������t���[����
     */
    void changeWithSceneOverlapping(progress prm_progress, frame prm_overlapping_frames);

    /**
     * ���݂̐i����ԂɊ֘A�Â��Ă���V�[�����擾 .
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relatSubScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @return
     */
    DefaultScene* getGazedScene();

    /**
     * �i����ԂɊ֘A�Â��Ă���V�[�����擾 .
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relatSubScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @param prm_progress �i�����
     * @return
     */
    DefaultScene* getScene(progress prm_progress);

    virtual void changeDelay(progress prm_progress, frame prm_delay);
    virtual void update() override;

    /**
     * �f�X�g���N�^ .
     */
    virtual ~SceneProgress();
};

}
#endif /*SCENEPROGRESS_H_*/
