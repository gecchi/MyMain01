#ifndef GGAF_CORE_SCENE_H_
#define GGAF_CORE_SCENE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Element.hpp"

namespace GgafCore {

/**
 * �V�[���i��ʁj�N���X .
 * �{�v���O�����ł́w�V�[���x�Ƃ́A�A�v����ł́u��ʁv�Ƃ����T�O���u����Z�܂������́v�ƍl���A<BR>
 * �؂蕪����ꂽ�I�u�W�F�N�g�̎��ł��B�������������ƁA�Q�[���i�A�v���j�Ƃ������̂́A<BR>
 * �u�l�X�ȁw��ʁA�V�[��(Scene)�x�ɂ����āw�L�����A�A�N�^�[(Actor)�x���������􂷂���̂ł���B�v<BR>
 * �Ƃ����T�O�̕����͋��ʉ��ł���͂����ƐM���Đ݌v���s���܂����B�ȒP�Ɍ����Ɖ�������ł��ˁB<BR>
 * �A�v���S�̂����ɃA�j�����Đ����Ă�����̂ƍl�����ꍇ�A�V�[���I�u�W�F�N�g�Ƃ́A<BR>
 * ���C���[�i�Z���j�̂悤�ȕ��ɂ�����܂��B<BR>
 * �@�\�Ƃ��āA�V�[���I�u�W�F�N�g���m���|�C���^�ڍ����A�c���[�K�w�\�����̂鎖���ł��܂��B�i���̃c���[�\���̓N���X�̌p���Ɗ֌W����܂���B�j<BR>
 * �V�[���Ɏ�������Ă��郁�\�b�h�S�̂قƂ�ǂ́A�������g�Ǝ����z���̃V�[���i���c���[�V�[���j�S�Ăɉe������d�l�ɂȂ��Ă��܂��B<BR>
 * �e�V�[���́A�K���P�̃V�[������҃A�N�^�[(SceneMediator)�������o�Ƃ��ĕێ����Ă��܂��B<BR>
 * �V�[������҃A�N�^�[�Ƃ͊e�V�[���̃A�N�^�[�̑�e���̂悤�Ȃ��̂ŁASceneMediator �̃R�����g���Q�Ƃ��ĉ������B<BR>
 *
 * <B>�y�p��⑫�z</B>
 * <TABLE border='1'>
 * <TR>
 * <TD>�u�V�[���v</TD>
 * <TD>�V�[���N���X�̃C���X�^���X�i�ւ̃|�C���^�j���ȗ����āA�P�ɃV�[���ƌĂԂ��Ƃɂ��܂��B</TD>
 * </TR><TR>
 * <TD>�u���V�[���v�u���v</TD>
 * <TD>�������g�̃C���X�^���X(this����)�B�����́A�����̘b��̒��S�ƂȂ��Ă���V�[�������V�[���ɂȂ鎞������܂��B</TD>
 * </TR><TR>
 * <TD>�u�q�V�[���v�u�q�v�u�q�v</TD>
 * <TD>�V�[�����m�̃c���[�K�w�\����ɂ����āA���V�[����<B>����</B>�Ԃ牺����P�K�w���̃V�[���B���w���Ă��܂��B<BR>
 * �V�[���N���X���p�������N���X�Ƃ����Ӗ��ł͖������ƂƂ��܂��B</TD>
 * </TR><TR>
 * <TD>�u�V�[���z���v�u�z���v</TD>
 * <TD>�V�[�����m�̃c���[�K�w�\����ɂ����āA���V�[��<B>��</B>�Ԃ牺����S�ẴV�[���B���w���Ă��܂��B�q�V�[�������R�܂܂�܂��B<BR>
 * �V�[���N���X���p�����N���X�Ƃ����Ӗ��ł͖������ƂƂ��܂��B</TD>
 * </TR><TR>
 * <TD>�u�e�V�[���v�u�e�v</TD>
 * <TD>�V�[�����m�̃c���[�K�w�\����ɂ����āA���V�[��<B>��</B>���ڈ����͊ԐړI�ɂԂ牺�����Ă���V�[�����w���Ă��܂��B</TD>
 * </TR><TR>
 * <TD>�u���V�[���v�u���v</TD>
 * <TD>���V�[���ȊO�̃V�[�����w���Ă��܂��B</TD>
 * </TR><TR>
 * <TD>�u�c���[�v</TD>
 * <TD>�V�[�����m���c���[�K�w�\���ɂ���ĘA������Ă���1�̂܂Ƃ܂��\�����錾�t�B</TD>
 * </TR><TR>
 * <TD>�u�������c���[�v</TD>
 * <TD>���V�[�����܂܂�Ă��镔���c���[(�����̓c���[�S��)�̊K�w�\�����w���܂��B</TD>
 * </TR><TR>
 * <TD>�u���c���[�v</TD>
 * <TD>���V�[���𒸓_�Ƃ���A���V�[���{���V�[���z���̃c���[�K�w�\�����w���܂��B</TD>
 * </TR><TR>
 * <TD>�u���c���[�V�[���v</TD>
 * <TD>���c���[�̃V�[���B�܂莩�V�[���{���V�[���z���̃V�[���S�Ă��w���܂��B���V�[�����c���[�̒��_�i�ł��e�j�Ɉʒu���Ă��邱�Ƃ��Ӗ����Ă��܂�</TD>
 * </TR><TR>
 * <TD>�u�V�[���N���X�v</TD>
 * <TD>Actor�N���X�𒼐ځE�Ԑڌp�����Ă���N���X�S�ʂ��w���܂��B</TD>
 * </TR><TR>
 * <TD>�u��ʃN���X�v�u���ʃN���X�v</TD>
 * <TD>�V�[���N���X�̃N���X�̌p���֌W��\���Ă��܂��B
 * �N���X�p���֌W�̕\���́u�X�[�p�[�v�u�q�v���́u�e�v�u�q�v�͎g�킸��<B>�u��ʁv�u���ʁv</B>�œ��ꂷ�邱�Ƃɂ��܂��B<BR>
 * �u�X�[�p�[�v�u�q�v���́u�e�v�u�q�v�ƌ������ꍇ�̓c���[�K�w�\���̂��Ƃ������Ă��܂��B</TD>
 * </TR>
 * </TABLE>
 * <BR>
 * �{�N���X�͒��ۃN���X�ł��̂܂� new �ł��܂���B<BR>
 * �S�ẴV�[���N���X�́A�{�N���X�𒼐ځE�Ԑڌp�������Ȃ��Ƃ��ȉ��̉��z�֐����������Ȃ���΂Ȃ�܂���B<BR>
 * <BR>
 * void initialize() �E�E�E�������� <BR>
 * void processBehavior() �E�E�E�t���[�����̐U�镑������ <BR>
 * void processSettlementBehavior() �E�E�E�t���[�����̗l�X�Ȕ��菈���̎��O���������i�S�V�[���U�镑������������̏����j <BR>
 * void processJudgement() �E�E�E�t���[�����̗l�X�Ȕ��菈���̖{���� <BR>
 * void processPreDraw() �E�E�E�t���[�����̕`�掖�O���� <BR>
 * void processDraw() �E�E�E�t���[�����̕`��{���� <BR>
 * void processAfterDraw() �E�E�E�t���[�����̕`�掖�㏈�� <BR>
 * void processFinal() �E�E�E�t���[�����̏I�[���� <BR>
 * void onCatchEvent(hashval prm_no, void* prm_pSource) �E�E�E���̑��̃C�x���g������ <BR>
 * <BR>
 * @version 1.00
 * @since 2006/06/27
 * @author Masatoshi Tsuge
 */
class Scene : public Element<Scene> {

    friend class God;
    friend class Spacetime;
    friend class Actor;
    friend class GroupHead;
    friend class SceneMediator;
    friend class GarbageBox;


protected:
    /** ���̃V�[���̒���� */
    SceneMediator* _pSceneMediator;

    /** ���t���[���ɂP�񓮍삷�邩 */
    frame _once_in_n_time;
    bool _is_next_frame;

public:
    /**
     * �R���X�g���N�^ .
     * �����F prm_name �V�[����<BR>
     */
    Scene(const char* prm_name, SceneMediator* prm_pSceneMediator = nullptr);

    /**
     * �f�X�g���N�^ .
     * ���V�[���̒���҂̃c���[�A�N�^�[�̉�����s���Ă���B<BR>
     * ���c���[�V�[���̉�����s���܂�<BR>
     */
    virtual ~Scene();

    /**
     * ���t���[���ɂP����s���邩���w�� .
     * �X���[�ɂ��������Ɏg�p���邱�Ƃ�z��B<BR>
     * �K���1�B���{�i�s�B��ʃV�[����1�t���[���ŁA���g��1�t���[���i�ށB<BR>
     * 2 ��ݒ肷��� 1/2�{���i�s�B��ʃV�[����2�t���[����1�t���[���i�ށB<BR>
     * 3 ��ݒ肷��� 1/3�{���i�s�B��ʃV�[����3�t���[����1�t���[���i�ށB<BR>
     * 4 ��ݒ肷��� 1/4�{���i�s�B��ʃV�[����4�t���[����1�t���[���i�ށB<BR>
     * @param prm_once_in_n_time ���t���[���ɂP����s���邩
     */
    virtual void setRunFrameOnce(int prm_once_in_n_time);
    virtual void addRunFrameOnce(int prm_once_in_n_time);

    virtual void appendChild(Scene* prm_pScene) override;

    virtual void nextFrame() override;
//    virtual void update_last_frame_of_god() override;
    virtual void behave() override;
    virtual void settleBehavior() override;
    virtual void preJudge() override;
    virtual void judge() override;
    virtual void preDraw() override;
    virtual void draw() override;
    virtual void afterDraw() override;
    /**
     * doFinally()��_once_in_n_time�̉e�����󂯂Ȃ��B
     */
    virtual void doFinally() override;
    virtual void throwEventLowerTree(hashval prm_no, void* prm_pSource) override;
    virtual void throwEventLowerTree(hashval prm_no) override;
    virtual void throwEventUpperTree(hashval prm_no, void* prm_pSource) override;
    virtual void throwEventUpperTree(hashval prm_no) override;
    virtual void activateTree() override;
    virtual void activateDelay(frame prm_offset_frames = 1) override;
    virtual void activate() override;
    virtual void activateTreeImmed() override;
    virtual void activateImmed() override;
    virtual void inactivateTree() override;
    virtual void inactivateDelay(frame prm_offset_frames = 1) override;
    virtual void inactivate() override;
    virtual void inactivateTreeImmed() override;
    virtual void inactivateImmed() override;

    virtual void pauseTree() override;
    virtual void pause() override;

    virtual void unpauseTree() override;
    virtual void unpause() override;

    virtual void reset() override;
    virtual void resetTree() override;

    /**
     * �z���S�ẴV�[���ƁA���̊e�V�[���̒����(SceneMediator)�A���̔z���S�A�N�^�[�ɑ΂��Ďw��̊֐������s������ .
     * @param pFunc �I�u�W�F�N�g�Ɏ��s���������֐�
     * @param prm1 �n�������������̂P
     * @param prm2 �n�������������̂Q
     * @param prm3 �n�������������̂R
     */
    virtual void executeFuncLowerTree(void (*pFunc)(Object*, void*, void*, void*), void* prm1, void* prm2, void* prm3) override;

    /**
     * �z���S�ẴV�[���ɑ΂��Ďw��̊֐������s������ .
     * @param pFunc �I�u�W�F�N�g�Ɏ��s���������֐�
     * @param prm1 �n�������������̂P
     * @param prm2 �n�������������̂Q
     * @param prm3 �n�������������̂R
     */
    virtual void executeFuncLowerSceneTree(void (*pFunc)(Object*, void*, void*, void*), void* prm1, void* prm2, void* prm3);

    /**
     * ���c���[�V�[����n�t���[����ɃS�~���ֈړ����܂� .
     * @param prm_offset_frames �S�~���ֈړ��^�C�~���O�c��t���[����(�f�t�H���g=1)
     */
    virtual void end(frame prm_offset_frames = 1) override;

    /**
     * ����Ȃ炵�܂� .
     * ��������A�N�^�[�ɂ́Asayonara() �����s���A���g(�V�[��)�ɂ� end() �����s���܂��B<BR>
     * �V�[����������������ꍇ�͂��̃��\�b�h�����s���邱�ƁB
     * @param prm_offset_frames �P�\�t���[��(1�`)
     */
    virtual void sayonara(frame prm_offset_frames = 60);

    /**
     * �z���m�[�h�𖖒[����J������B .
     * @param prm_num_cleaning �J���C���X�^���X��(�A���A�V�[���͂P������clean()�o���Ȃ����Ƃ���)
     */
    virtual void clean(int prm_num_cleaning) override;

    /**
     * �_�ɉy�� .
     * @return	�Ă΂�ďo�Ă����_
     */
    virtual God* askGod() override;

    /**
     * ���V�[���̒���҂��擾 .
     * @return �V�[�������
     */
    virtual SceneMediator* bringSceneMediator() const {
        return _pSceneMediator;
    }

    /**
     * �f�o�b�O�p�F�c���[�\����\�� .
     */
    virtual void dump();

    /**
     * �f�o�b�O�p�Fdump()����g�p����� .
     */
    virtual void dump(std::string prm_parent);
};

}
#endif /*GGAF_CORE_SCENE_H_*/
