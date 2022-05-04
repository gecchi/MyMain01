#ifndef GGAF_LIB_SCENEPHASE_H_
#define GGAF_LIB_SCENEPHASE_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/Phase.h"

#include <map>
namespace GgafLib {

typedef std::map<int, GgafLib::DefaultScene*> PhaseSceneMap;

/**
 * �t�F�[�Y�Ǘ�(�V�[���p)�N���X .
 * ����GgafCore::Phase�N���X�ɁA�V�[���ɂ܂��֗��ȋ@�\��ǉ�����
 * �V�[����p�̃t�F�[�Y�Ǘ��N���X�ł��B
 * @version 1.00
 * @since 2011/07/15
 * @author Masatoshi Tsuge
 */
class ScenePhase : public GgafCore::Phase {

public:
    /** [r]�t�F�[�Y�Ǘ��ΏۃV�[�� */
    DefaultScene* _pScene;
    /** [r]�t�F�[�Y�ԍ� �� �q�V�[�� */
    PhaseSceneMap _mapPhase2Scene;

    int _phase_no_next_promise;
    frame _count_next_promise;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_pScene       �t�F�[�Y���Ǘ��������ΏۃV�[��
     */
    ScenePhase(DefaultScene* prm_pScene);

    /**
     * �t�F�[�Y�Ǝq�V�[�����֘A�t���A��������.
     * ���̃��\�b�h�ɂ��A�֘A�t�����s���ƁA�ȉ��̃��\�b�h���g�p�\�i���ʂ���j�ƂȂ�܂��B<BR>
     * <code>
     * changeWithSceneFlipping(int)
     * changeWithSceneCrossfading(int, frame);
     * changeWithSceneOverlapping(int, frame);
     * </code>
     * @param prm_FirstPhase �擪�̃t�F�[�Y
     * @param prm_EndPhase �����̃t�F�[�Y
     * @param prm_FirstChildSceneName �擪�̃t�F�[�Y(prm_FirstPhase)�ɑΉ�����q�V�[���̖���
     */
    void relateChildScene(int prm_FirstPhase, int prm_EndPhase, const char* prm_FirstChildSceneName);


    /**
     * �t�F�[�Y�Ǝq�V�[�����֘A�t���A��������.
     * ���̃��\�b�h�ɂ��A�֘A�t�����s���ƁA�ȉ��̃��\�b�h���g�p�\�i���ʂ���j�ƂȂ�܂��B<BR>
     * <code>
     * changeWithSceneFlipping(int)
     * changeWithSceneCrossfading(int, frame);
     * changeWithSceneOverlapping(int, frame);
     * </code>
     * @param prm_FirstPhase �擪�̃t�F�[�Y
     * @param prm_EndPhase   �����̃t�F�[�Y
     * @param prm_pFirstChildScene �擪�̃t�F�[�Y(prm_FirstPhase)�ɑΉ�����q�V�[��
     */
    void relateChildScene(int prm_FirstPhase, int prm_EndPhase, DefaultScene* prm_pFirstChildScene);

    /**
     * �V�����t�F�[�Y��؂�ւ���Ɠ����ɁA�֘A�t�����q�V�[����������Ԃɂ��� .
     * ���݂̃t�F�[�Y�ɕR�t���q�V�[���͂��̂܂܁i�񊈓��ɂ��܂���j .
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relateChildScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @param prm_phase_no �V�����t�F�[�Y
     */
    void changeWithSceneFadein(int prm_phase_no, frame prm_fade_in = 120);

    /**
     * �V�����t�F�[�Y��؂�ւ���Ɠ����ɁA�֘A�t�����q�V�[���ɐ؂�ւ� .
     * ���݂̃t�F�[�Y�ɕR�t���q�V�[���͔񊈓���Ԃɂ��A�����̃t�F�[�Y�ɕR�t���q�V�[����������Ԃɂ��܂��B
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relateChildScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @param prm_phase_no �V�����t�F�[�Y
     */
    void changeWithSceneFlipping(int prm_phase_no);

    /**
     * �V�����t�F�[�Y��؂�ւ���Ɠ����ɁA�֘A�t�����q�V�[����������Ԃɐ؂�ւ� .
     * ������Ԏq�V�[���͔񊈓���Ԃɂ���ہA�w��t���[���ԓ����i�s�i�I�[�o�[���b�s���O�j���Ȃ���t�F�[�h�A�E�g�E�t�F�[�h�C�����ʂ��s�� .
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relateChildScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @param prm_phase_no �V�����t�F�[�Y
     * @param prm_cross_fade_frames �t�F�[�h�C�� & �t�F�[�h�A�E�g���s������
     */
    void changeWithSceneCrossfading(int prm_phase_no, frame prm_cross_fade_frames = 300);

    /**
     * ���t�F�[�Y�ɕR�t���q�V�[���̓t�F�[�h�A�E�g���񊈓���Ԃɂ��A
     * ���̌㒼���Ɏ��̐V�����t�F�[�Y�ɕR�t���q�V�[�����A�t�F�[�h�C����������Ԃɂ���B .
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relateChildScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @param prm_phase_no �V�����t�F�[�Y
     * @param prm_fade_out �t�F�[�h�A�E�g����
     * @param prm_fade_in �t�F�[�h�C������
     */
    void changeWithSceneFadeoutFadein(int prm_phase_no, frame prm_fade_out=120, frame prm_fade_in = 120);

    /**
     * �V�����t�F�[�Y��؂�ւ���Ɠ����ɁA�֘A�t�����q�V�[����������Ԃɐ؂�ւ��A
     * ������Ԏq�V�[���͔񊈓���Ԃɂ���B���̍ہA�w��t���[���ԁA�����i�s�i�I�[�o�[���b�s���O�j������ .
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relateChildScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @param prm_phase_no �V�����t�F�[�Y
     * @param prm_overlapping_frames �����i�s������t���[����
     */
    void changeWithSceneOverlapping(int prm_phase_no, frame prm_overlapping_frames);

    /**
     * ���݂̃A�N�e�B�u�ȃt�F�[�Y�Ɋ֘A�Â��Ă���V�[�����擾 .
     * �擾�ł��Ȃ��ꍇ�� nullptr
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relateChildScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @return
     */
    DefaultScene* getGazedScene();

    /**
     * �����̃t�F�[�Y�Ɋ֘A�Â��Ă���V�[�����擾 .
     * �擾�ł��Ȃ��ꍇ�� nullptr
     * ���{���\�b�h�̌��ʂ𓾂�ɂ� relateChildScene() ��\�ߎ��s���A�V�[�����֘A�t����K�v������܂��B
     * @param prm_phase_no �t�F�[�Y
     * @return
     */
    DefaultScene* getScene(int prm_phase_no);

    /**
     * �t�F�[�Y�ԍ���ύX���AchangeDelay �͖����������Ƃɂ��� .
     * �A���A����ɂ͔��f���ꂸ update() ���ɔ��f�����B
     * GGAF_PHASE_NOTHING(-1) �͐ݒ�s�B
     * reset(int) �Ǝg�������邱�ƁB
     * @param prm_phase_no �t�F�[�Y�ԍ�(0�`)
     */
    virtual void change(int prm_phase_no) override;

    /**
     * �t�F�[�Y�ԍ��𖳂� GGAF_PHASE_NOTHING(-1) �ɕύX���AchangeDelay �͖����������Ƃɂ��� .
     * �A���A����ɂ͔��f���ꂸ update() ���ɔ��f�����B
     */
    virtual void changeNothing() override;

    /**
     * �t�F�[�Y�ԍ���+1���AchangeDelay �͖����������Ƃɂ��� .
     * �A���A����ɂ͔��f���ꂸ update() ���ɔ��f�����B
     * change(_phase_no+1) �Ɠ����Ӗ��ł���B
     */
    virtual void changeNext() override;

    /**
     * �t�F�[�Y�ԍ��̕ύX�\�������B .
     * @param prm_phase_no �\��t�F�[�Y�ԍ�(0�`)
     * @param prm_delay �x���t���[��
     */
    virtual void changeDelay(int prm_phase_no, frame prm_delay);

    virtual void update() override;

    /**
     * �f�X�g���N�^ .
     */
    virtual ~ScenePhase();
};

}
#endif /*GGAF_LIB_SCENEPHASE_H_*/
