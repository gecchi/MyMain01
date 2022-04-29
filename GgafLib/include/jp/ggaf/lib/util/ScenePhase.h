#ifndef GGAF_LIB_SCENEPHASE_H_
#define GGAF_LIB_SCENEPHASE_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/Phase.h"

#include <map>
namespace GgafLib {

typedef std::map<phase, GgafLib::DefaultScene*> PhaseSceneMap;

/**
 * �t�F�[�Y�i���Ǘ�(�V�[���p)�N���X .
 * ����GgafCore::Progress�N���X�ɁA�V�[���ɂ܂��֗��ȋ@�\��ǉ�����
 * �V�[����p�̃t�F�[�Y�i���Ǘ��N���X�ł��B
 * @version 1.00
 * @since 2011/07/15
 * @author Masatoshi Tsuge
 */
class ScenePhase : public GgafCore::Phase {

public:
    /** [r]�i���Ǘ��ΏۃV�[�� */
    DefaultScene* _pScene;
    /** [r]�i���ԍ� �� �q�V�[�� */
    PhaseSceneMap _mapPhase2Scene;

    phase _phase_next_promise;
    frame _count_next_promise;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_pScene       �i�����Ǘ��������ΏۃV�[��
     */
    ScenePhase(DefaultScene* prm_pScene);

    /**
     * �i����ԂƎq�V�[�����֘A�t���A��������.
     * ���̃��\�b�h�ɂ��A�֘A�t�����s���ƁA�ȉ��̃��\�b�h���g�p�\�i���ʂ���j�ƂȂ�܂��B<BR>
     * <code>
     * changeWithSceneFlipping(phase)
     * changeWithSceneCrossfading(phase, frame);
     * changeWithSceneOverlapping(phase, frame);
     * </code>
     * @param prm_FirstProgress �擪�̐i�����
     * @param prm_EndProgress �����̐i�����
     * @param prm_FirstChildSceneName �擪�̐i�����(prm_FirstProgress)�ɑΉ�����q�V�[���̖���
     */
    void relateChildScene(phase prm_FirstProgress, phase prm_EndProgress, const char* prm_FirstChildSceneName);


    /**
     * �i����ԂƎq�V�[�����֘A�t���A��������.
     * ���̃��\�b�h�ɂ��A�֘A�t�����s���ƁA�ȉ��̃��\�b�h���g�p�\�i���ʂ���j�ƂȂ�܂��B<BR>
     * <code>
     * changeWithSceneFlipping(phase)
     * changeWithSceneCrossfading(phase, frame);
     * changeWithSceneOverlapping(phase, frame);
     * </code>
     * @param prm_FirstProgress �擪�̐i�����
     * @param prm_EndProgress   �����̐i�����
     * @param prm_pFirstChildScene �擪�̐i�����(prm_FirstProgress)�ɑΉ�����q�V�[��
     */
    void relateChildScene(phase prm_FirstProgress, phase prm_EndProgress, DefaultScene* prm_pFirstChildScene);

    /**
     * �V�����i����Ԃ�؂�ւ���Ɠ����ɁA�֘A�t�����q�V�[����������Ԃɂ��� .
     * ���݂̐i����ԂɕR�t���q�V�[���͂��̂܂܁i�񊈓��ɂ��܂���j .
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relateChildScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @param prm_phase �V�����i�����
     */
    void changeWithSceneFadein(phase prm_phase, frame prm_fade_in = 120);

    /**
     * �V�����i����Ԃ�؂�ւ���Ɠ����ɁA�֘A�t�����q�V�[���ɐ؂�ւ� .
     * ���݂̐i����ԂɕR�t���q�V�[���͔񊈓���Ԃɂ��A�����̐i����ԂɕR�t���q�V�[����������Ԃɂ��܂��B
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relateChildScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @param prm_phase �V�����i�����
     */
    void changeWithSceneFlipping(phase prm_phase);

    /**
     * �V�����i����Ԃ�؂�ւ���Ɠ����ɁA�֘A�t�����q�V�[����������Ԃɐ؂�ւ� .
     * ������Ԏq�V�[���͔񊈓���Ԃɂ���ہA�w��t���[���ԓ����i�s�i�I�[�o�[���b�s���O�j���Ȃ���t�F�[�h�A�E�g�E�t�F�[�h�C�����ʂ��s�� .
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relateChildScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @param prm_phase �V�����i�����
     * @param prm_cross_fade_frames �t�F�[�h�C�� & �t�F�[�h�A�E�g���s������
     */
    void changeWithSceneCrossfading(phase prm_phase, frame prm_cross_fade_frames = 300);

    /**
     * ���i����ԂɕR�t���q�V�[���̓t�F�[�h�A�E�g���񊈓���Ԃɂ��A
     * ���̌㒼���Ɏ��̐V�����i����ԂɕR�t���q�V�[�����A�t�F�[�h�C����������Ԃɂ���B .
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relateChildScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @param prm_phase �V�����i�����
     * @param prm_fade_out �t�F�[�h�A�E�g����
     * @param prm_fade_in �t�F�[�h�C������
     */
    void changeWithSceneFadeoutFadein(phase prm_phase, frame prm_fade_out=120, frame prm_fade_in = 120);

    /**
     * �V�����i����Ԃ�؂�ւ���Ɠ����ɁA�֘A�t�����q�V�[����������Ԃɐ؂�ւ��A
     * ������Ԏq�V�[���͔񊈓���Ԃɂ���B���̍ہA�w��t���[���ԁA�����i�s�i�I�[�o�[���b�s���O�j������ .
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relateChildScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @param prm_phase �V�����i�����
     * @param prm_overlapping_frames �����i�s������t���[����
     */
    void changeWithSceneOverlapping(phase prm_phase, frame prm_overlapping_frames);

    /**
     * ���݂̃A�N�e�B�u�Ȑi����ԂɊ֘A�Â��Ă���V�[�����擾 .
     * �擾�ł��Ȃ��ꍇ�� nullptr
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relateChildScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @return
     */
    DefaultScene* getGazedScene();

    /**
     * �����̐i����ԂɊ֘A�Â��Ă���V�[�����擾 .
     * �擾�ł��Ȃ��ꍇ�� nullptr
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relateChildScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @param prm_phase �i�����
     * @return
     */
    DefaultScene* getScene(phase prm_phase);

    /**
     * �i���ԍ���ύX���AchangeDelay �͖����������Ƃɂ��� .
     * �A���A����ɂ͔��f���ꂸ update() ���ɔ��f�����B
     * GGAF_PHASE_NOTHING(-1) �͐ݒ�s�B
     * reset(phase) �Ǝg�������邱�ƁB
     * @param prm_phase �i���ԍ�(0�`)
     */
    virtual void change(phase prm_phase) override;

    /**
     * �i���ԍ��𖳂� GGAF_PHASE_NOTHING(-1) �ɕύX���AchangeDelay �͖����������Ƃɂ��� .
     * �A���A����ɂ͔��f���ꂸ update() ���ɔ��f�����B
     */
    virtual void changeNothing() override;

    /**
     * �i���ԍ���+1���AchangeDelay �͖����������Ƃɂ��� .
     * �A���A����ɂ͔��f���ꂸ update() ���ɔ��f�����B
     * change(_phase+1) �Ɠ����Ӗ��ł���B
     */
    virtual void changeNext() override;

    /**
     * �i���ԍ��̕ύX�\�������B .
     * @param prm_phase �\��i���ԍ�(0�`)
     * @param prm_delay �x���t���[��
     */
    virtual void changeDelay(phase prm_phase, frame prm_delay);
    virtual void update() override;

    /**
     * �f�X�g���N�^ .
     */
    virtual ~ScenePhase();
};

}
#endif /*GGAF_LIB_SCENEPHASE_H_*/
