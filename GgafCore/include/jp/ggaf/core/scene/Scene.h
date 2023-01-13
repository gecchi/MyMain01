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
 * void onCatchEvent(eventval prm_event_val, void* prm_pSource) �E�E�E���̑��̃C�x���g������ <BR>
 * <BR>
 * @version 1.00
 * @since 2006/06/27
 * @author Masatoshi Tsuge
 */
class Scene : public Element<Scene> {

    friend class Caretaker;
    friend class Spacetime;
    friend class Actor;
    friend class GroupHead;
    friend class SceneMediator;
    friend class GarbageBox;

public:
    /** ���̃V�[���̒���� */
    SceneMediator* _pSceneMediator;
    /** [r]�ꎞ��~�t���O */
    bool _was_paused_flg;
    /** [r]���t���[���̈ꎞ��~�t���O�A���t���[���̃t���[�����Z�� _was_paused_flg �ɔ��f����� */
    bool _was_paused_flg_in_next_frame;

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
    virtual void throwEventLowerTree(eventval prm_event_val, void* prm_pSource) override;
    virtual void throwEventLowerTree(eventval prm_event_val) override;
    virtual void throwEventUpperTree(eventval prm_event_val, void* prm_pSource) override;
    virtual void throwEventUpperTree(eventval prm_event_val) override;
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



//    /**
//     * ���c���[�̔z���m�[�h�S�ĂɁA�ċA�Ăяo�����s���B
//     * @param pFunc �ċA�Ăяo�����郁�\�b�h
//     */
//    inline void callRecursive(void (Scene::*pFunc)()) const {
//        Scene* pElementTemp = _pChildFirst;
//        while (pElementTemp) {
//            (pElementTemp->*pFunc)(); //���s
//            if (pElementTemp->_is_last_flg) {
//                break;
//            } else {
//                pElementTemp = pElementTemp->_pNext;
//            }
//        }
//    }

    /**
    * �ꎞ��~��Ԃ��ǂ������f
    * @return true:�ꎞ��~��ԁ^false:�ꎞ��~��Ԃł͖���
    */
    inline bool wasPaused() const {
        return _was_paused_flg;
    }


    /**
    * �ꎞ��~��Ԃɂ���(���s�ΏہF���c���[�S��) .
    * ���m�ɂ́A���m�[�h�������t���[������ꎞ��~�ɂ���\��t���O�𗧂Ă�B<BR>
    * �����āA���t���[���擪����(nextFrame())���ŁA�߂ł����ꎞ��~���(_was_paused_flg = true)�ɂȂ�B<BR>
    * ���������āA�{���\�b�h�����s���Ă��w����t���[�����x�͈ꎞ��~��Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
    * �z���m�[�h�ɂ͉����e��������܂���B<BR>
    */
    virtual void pause() {
        if (_can_live_flg) {
            _was_paused_flg_in_next_frame = true;
//            callRecursive(&Scene::pause); //�ċA
            //�ċA
            Scene* pElementTemp = _pChildFirst;
            while (pElementTemp) {
                pElementTemp->pause(); //���s
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->_pNext;
                }
            }
        }
    }

    /**
    * �ꎞ��~��Ԃ���������(���s�ΏہF���c���[�S��) .
    * ���m�ɂ́A���m�[�h�������t���[������ꎞ��~��Ԃ���������\��t���O�𗧂Ă�B<BR>
    * �����āA���t���[���擪����(nextFrame())���ŁA�߂ł����ꎞ��~��ԉ���(_was_paused_flg = false)�ɂȂ�B<BR>
    * ���������āA�{���\�b�h�����s���Ă��w����t���[�����x�͈ꎞ��~��Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
    * �z���m�[�h�ɂ͉����e��������܂���B<BR>
    */
    virtual void unpause() {
        if (_can_live_flg) {
            _was_paused_flg_in_next_frame = false;
//            callRecursive(&Scene::unpause); //�ċA
            //�ċA
            Scene* pElementTemp = _pChildFirst;
            while (pElementTemp) {
                pElementTemp->unpause(); //���s
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->_pNext;
                }
            }
        }
    }

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
     * �Ǘ��҂ɉy�� .
     * @return	�Ă΂�ďo�Ă����Ǘ���
     */
    virtual Caretaker* askCaretaker() override;

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
