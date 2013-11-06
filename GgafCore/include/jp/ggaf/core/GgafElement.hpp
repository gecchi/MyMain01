#ifndef GGAFCORE_GGAFELEMENT_H_
#define GGAFCORE_GGAFELEMENT_H_
#include "jp/ggaf/core/GgafNode.hpp"

#include "jp/ggaf/core/GgafProgress.h"
#include "jp/ggaf/core/GgafGarbageBox.h"
#include "jp/ggaf/core/exception/GgafCriticalException.h"

namespace GgafCore {

/**
 * �m�[�h(GgafNode<T>)�ɁA�l�X�ȏ�ԊǗ��@�\��ǉ������N���X .
 * �����^�X�N�V�X�e���ɕK�v�ȏ�ԑJ�ڋ@�\����������Ă���B<BR>
 * ���t���[���A�_(GgafGod)�́A���̐�(GgafUniverse)�ɁA���̃��\�b�h�����ɌĂяo���d�g�݂ɂȂ��Ă���B<BR>
 * nextFrame() > behave() > settleBehavior() > judge() > [preDraw() > draw() > afterDraw()] > doFinally() <BR>
 * �A�v���P�[�V�����ɓo�ꂷ��m�[�h�͑S�āA�u���̐��v�̃c���[�ɏ������邽�߁A�S�m�[�h�ɑ΂��ď�L�̏������s����B
 * ��L�̓��AnextFrame() �̂ݖ��t���[���K�����s�����B<BR>
 * behave(), settleBehavior(), judge(), doFinally() �́A������ԃt���O(_is_active_in_the_tree_flg)�� true�A���A
 * �ꎞ��~�t���O(_was_paused_flg)�� false �̏ꍇ���s�����B<BR>
 * preDraw(), draw(), afterDraw() �́A���t���[���܂ł̎c���Ԃɗ]�T������ꍇ�A���s�����B<BR>
 * ���t���[���܂ł̎c���Ԃɗ]�T�������ꍇ�A�_�͂���3���\�b�h���X�L�b�v����B
 * �A���A�X�L�b�v����Ƃ����Ă��AMAX_SKIP_FRAME �t���[���ɂP��͕K�����s����B<BR>
 * ��L�� nextFrame() �` doFinally() �̏��������ʂŃI�[�o�[���C�h����΁A�^�X�N�V�X�e���̊����ł���B<BR>
 * �������A���\�b�h�̒��ڃI�[�o�[���C�h�͔񐄏��ł���B�I�[�o�[���C�h�p�Ɋe���\�b�h���ŃR�[���o�b�N�����<BR>
 * �������z�֐�(processXxxxxx()) ��p�ӂ��Ă���̂ŁA���̃��\�b�h���I�[�o�[���C�h���ĉ������B<BR>
 * initialize() �́A��L�� nextFrame() �` doFinally() �����ꂩ���Ăяo���O�ɃC���X�^���X���ƂɂP�񂾂��Ă΂��d�g�݂ɂȂ��Ă���B<BR>
 * �����t���O(_can_live_flg)��false�̏ꍇ�́AnextFrame() �` doFinally() �͑S�Ď��s����Ȃ��B<BR>
 * (�����N���X����GgafFactor)
 * @version 1.00
 * @since 2008/08/21
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafElement : public GgafNode<T> {

private:

    /**
     * �c���[�\���ɂ����āA�ċA�Ăяo�����s���B
     * @param pFunc �ċA�Ăяo�����郁�\�b�h
     */
    inline void callRecursive(void (GgafElement<T>::*pFunc)()) {
        T* pElementTemp = GgafNode<T>::_pSubFirst;
        if (pElementTemp) {
            while(true) {
                (pElementTemp->*pFunc)(); //���s
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->_pNext;
                }
            }
        }
    }

    /**
     * �c���[�\���ɂ����āA�ċA�Ăяo�����s���B
     * @param pFunc �ċA�Ăяo�����郁�\�b�h(frame �����L��)
     * @param prm_frame pFunc�̈����ł���frame
     */
    inline void callRecursive(void (GgafElement<T>::*pFunc)(frame), frame prm_frame) {
        T* pElementTemp = GgafNode<T>::_pSubFirst;
        if (pElementTemp) {
            while(true) {
                (pElementTemp->*pFunc)(prm_frame); //���s
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->_pNext;
                }
            }
        }
    }


public:
    /** [r]�_�ւ̋ߓ� */
    GgafGod* _pGod;
    /** [r]initialize���s��ꂽ�ǂ����̃t���O(true=�s��ꂽ) */
    bool _was_initialize_flg;
    /** [r]�m�[�h���a��(addSub���ꂽ�j������̃t���[�������v(�A���A_was_paused_flg = true ���͉��Z���ꖳ��) */
    frame _frame_of_life;
    /** [r]�m�[�h���a��(addSub���ꂽ�j������A�U�������t���[�������v(�A���A_was_paused_flg = true ���� _is_active_flg = false ���͉��Z���ꖳ��) */
    frame _frame_of_behaving;
    /** [r]�m�[�h�������J�n(onActive())������̐U�������t���[�������v(�A���A_was_paused_flg = true ���� _is_active_flg = false ���͉��Z���ꖳ��) */
    frame _frame_of_behaving_since_onActive;

    /** [r]�m�[�h�����t���O */
    bool _is_active_flg;
    /** [r]�m�[�h�����t���O(���c���[���l������) */
    bool _is_active_in_the_tree_flg;
    /** [r]�ꎞ��~�t���O */
    bool _was_paused_flg;
    /** [r]�m�[�h�����t���O */
    bool _can_live_flg;

    /** [r]���t���[���̈ꎞ��~�t���O�A���t���[���̃t���[�����Z�� _was_paused_flg �ɔ��f����� */
    bool _was_paused_flg_in_next_frame;
    /** [r]�I���t���O */
    bool _will_end_after_flg;
    /** [r]�I������\��� _frame_of_life */
    frame _frame_of_life_when_end;


    /** [r]���ƂŊ����\��t���O */
    bool _will_activate_after_flg;
    /** [r]�����J�n����\��� _frame_of_life */
    frame _frame_of_life_when_activation;

    /** [r]���ƂŔ񊈓��\��t���O */
    bool _will_inactivate_after_flg;
    /** [r]�����I������\��� _frame_of_life */
    frame _frame_of_life_when_inactivation;

    /** [r]�m�[�h�������ɐ؂�ւ����(_is_active_flg �� false �� true)�u�ԂɂP�t���[�������Z�b�g�����t���O */
    bool _on_change_to_active_flg;
    /** [r]�m�[�h����~�ɐ؂�ւ����(_is_active_flg �� true �� false)�u�ԂɂP�t���[�������Z�b�g�����t���O */
    bool _on_change_to_inactive_flg;

    /** [r]�擪�m�[�h�Ɉړ��\��t���O�A���t���[���̃t���[�����Z���ɁA���m�[�h���擪�m�[�h�Ɉړ����� */
    bool _will_mv_first_in_next_frame_flg;
    /** [r]�����m�[�h�Ɉړ��\��t���O�A���t���[���̃t���[�����Z���ɁA���m�[�h�������m�[�h�Ɉړ����� */
    bool _will_mv_last_in_next_frame_flg;
    /** [r]�J�����g�t���[�����ň�x�ł����Z�b�g�����s������true�B���t���[�� false �ɍX�V����� */
    bool _is_already_reset;
    /** [r]��Ԑi���Ǘ��I�u�W�F�N�g */
    GgafProgress* _pProg;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name �m�[�h���́i���j�[�N�ɂ��ĉ������j
     */
    GgafElement(const char* prm_name);

    /**
     * �f�X�g���N�^�B���c���[�m�[�h���������B .
     */
    virtual ~GgafElement();

    /**
     * �|��(���s�ΏہF�z���m�[�h�S�āA�������g��delete����܂���) .
     * �_���������Ԃɗ]�T���ł��Ƃ����ɁA�_���Ăт����B<BR>
     * �z���m�[�h�̒��Ƀm�[�h�����t���O(_can_live_flg)�� false �ɂȂ��Ă���m�[�h�������
     * prm_num_cleaning ���� delete ����B<BR>
     * @param prm_num_cleaning �������I�u�W�F�N�g��
     */
    virtual void clean(int prm_num_cleaning);

    /**
     * �m�[�h��������(���s�ΏہFthis�̂�) .
     * �C���X�^���X������A���ꂩ���Ăяo�����O�ɁA�ŏ��ɕK���P�񂾂��Ăяo�����B<BR>
     * �⑫�Finitialize()���Ăяo���ꂽ��Areset() ���Ăяo�����B
     */
    virtual void initialize() = 0;

    /**
     * �m�[�h�̃t���[�������Z�ƁA�t���[���J�n�ɂ������Ă̂��낢��ȏ�������(���s�ΏہF���c���[�S��) .
     * ���t���[���K�����s����A��ɗl�X�ȏ�ԃt���O�̍X�V���s���B <BR>
     * _is_active_flg_in_next_frame _was_paused_flg_in_next_frame _can_live_flg_in_next_frame ��<BR>
     * _is_active_flg _was_paused_flg _can_live_flg �ɔ��f�i�R�s�[�j����B<BR>
     * �܂��A_will_mv_first_in_next_frame_flg, _will_mv_last_in_next_frame_flg �� true �̏ꍇ�́A<BR>
     * ���ꂼ��A���m�[�h�̐擪�m�[�h�ւ̈ړ��A�����m�[�h�ւ̈ړ����������s�����B<BR>
     * ���̌�A�z���m�[�h�S�Ă� nextFrame() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� nextFrame() ���s��A���� behave() �����s���邱�ƂɂȂ�B<BR>
     * ���̂悤�ȍ\���̏ꍇ�A���s���͇@�`�L�̏����ƂȂ�B<BR>
     * �m�[�h�ԂŎQ�Ɗ֌W������ꍇ�́A���ӂ��K�v�B<BR>
     * <pre>
     * (�o)�̇@�o��(�o)
     *         ��
     * (�d)�̇A�`�̇E�a�̇J�b�̇K�c�̇L�d��(�`)
     *         ��    ����������������������������
     *         ��                              ��
     * (�g)�̇B�e�̇C�f�̇D�g��(�e)    (�k)�̇F�h�̇G�i�̇H�j�̇I�k��(�h)
     *
     * ����{�͐擪�������̏��A�A���T�u�����݂���ΐ�Ɏ��s�A���݂��Ȃ���Ύ�(��)�����s�B
     * </pre>
     * ���\�b�h�����Ɂw(���s�ΏہF���c���[�S��)�x�ƋL�q����Ă���ꍇ�́A�S�ď�L�̏����Ŏ��s�����B
     */
    virtual void nextFrame();

    /**
     * �m�[�h�̃t���[�����̐U�镑������(���s�ΏہF���c���[�S��) .
     * ���̏����ł́A�S�m�[�h���W�ړ��������s�����ƂƂ���B<BR>
     * �����p�� processBehavior() ���R�[���o�b�N����邽�߂̃t���O�̏����́A<BR>
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �i _is_active_in_the_tree_flg && !_was_paused_flg && _can_live_flg �j�̏ꍇ�ł���B <BR>
     * behave() �� ���z�֐� processBehavior() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� behave() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�Ŗ{���\�b�h�𒼐ڌĂяo�����s��Ȃ����ƂƂ���B<BR>
     * ���ʃN���X�ł̓R�[������� processBehavior() ���I�[�o�[���C�h���ċ�̓I�ȍ��W�ړ����W�b�N����������B <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� behave() ���s��A���� settleBehavior() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void behave();

    /**
     * �m�[�h�̃t���[�����̐U�镑�����㏈��(���s�ΏہF���c���[�S��) .
     * ���̏����ł́A�S�m�[�h���W�ړ����������Ă��邱�Ƃ��ۏ؂��ꂽ��̏������s�����Ƃ���݌v�B<BR>
     * �X�V�������������W��񂩂�A����ɔ��������̗l�X�ȃX�e�[�^�X���̍X�V�����������ōs������ړI�Ƃ���<BR>
     * �����p�� processSettlementBehavior() ���R�[���o�b�N����邽�߂̃t���O�̏����́A<BR>
     * behave()�Ɠ����������t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g�B<BR>
     * �܂� ( _is_active_in_the_tree_flg && !_was_paused_flg && _can_live_flg )�̏ꍇ�ł���B <BR>
     * settleBehavior()�́A���z�֐� processSettlementBehavior() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� settleBehavior() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�Ŗ{���\�b�h�𒼐ڌĂяo�����s��Ȃ����ƂƂ���B<BR>
     * ���ʃN���X�ł̓R�[������� processSettlementBehavior() ���I�[�o�[���C�h���ă��W�b�N���������邱�ƂƂ���B <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� settleBehavior() ���s��A���� judge() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void settleBehavior();

    /**
     * �m�[�h�̃t���[�����̔��菈��(���s�ΏہF���c���[�S��) .
     * ���̏����ł́A�m�[�h�Ԃ̗l�X�Ȕ��菈�����s�����Ƃ���݌v�B<BR>
     * �S�m�[�h���W�ړ������Ɣ��Ȃ��X�e�[�^�X�ނ̍X�V�����S�Ɋ������Ă��O��Ƃ��鏈�����s����B<BR>
     * �����p�� processJudgement() ���R�[���o�b�N����邽�߂̃t���O�̏����́Abehave()�Ɠ������A<BR>
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �܂� ( _is_active_in_the_tree_flg && !_was_paused_flg && _can_live_flg )�̏ꍇ <BR>
     * judge() �� ���z�֐� processJudgement() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� judge() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�Ŗ{���\�b�h�𒼐ڌĂяo�����s��Ȃ����ƂƂ���B<BR>
     * ���ʃN���X�ł̓R�[������� processJudgement() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� judge() ���s��A<BR>
     * �_(GgafGod)�͂��̌�A���t���[���܂ł̎c���Ԃɗ]�T������� preDraw() ������� doFinally() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void judge();

    /**
     * �m�[�h�̃t���[�����̕`�掖�O����(���s�ΏہF���c���[�S��)�i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����p�� processPreDraw() ���R�[���o�b�N���������́A�����t���O�A�����t���O���Z�b�g<BR>
     * (�܂� _is_active_flg && _can_live_flg)�̏ꍇ�ł���B <BR>
     * processPreDraw() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� preDraw() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * ���ʃN���X�ł̓R�[������� processPreDraw() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� preDraw() ���s��A���� draw() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void preDraw();

    /**
     * �m�[�h�̃t���[�����̕`��{����(���s�ΏہF���c���[�S��)�i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����p�� processDraw() ���R�[���o�b�N���������́A�����t���O�A�����t���O���Z�b�g<BR>
     * (�܂� _is_active_in_the_tree_flg && _can_live_flg)�̏ꍇ�ł���B <BR>
     * processDraw() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� draw() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * ���ʃN���X�ł̓R�[������� processDraw() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� draw() ���s��A���� afterDraw() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void draw();

    /**
     * �m�[�h�̃t���[�����̕`�掖�㏈��(���s�ΏہF���c���[�S��)�i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����p�� processAfterDraw() ���R�[���o�b�N���������́A�����t���O�A�����t���O���Z�b�g<BR>
     * (�܂� _is_active_in_the_tree_flg && _can_live_flg)�̏ꍇ�ł���B <BR>
     * processAfterDraw() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� afterDraw() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * ���ʃN���X�ł̓R�[������� processAfterDraw() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� afterDraw() ���s��A���� doFinally() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void afterDraw();

    /**
     * �m�[�h�̃t���[�����̍ŏI����(���s�ΏہF���c���[�S��) .
     * ���W�ړ������A���菈���A�`�揈�����I��������ɁA�Ō�ɍs����n���������s�����Ƃ���݌v�B<BR>
     * �����p�� processFinal() ���R�[���o�b�N���������́A
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �i_is_active_in_the_tree_flg && !_was_paused_flg && _can_live_flg�j�̏ꍇ�ł���B <BR>
     * processFinal() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� doFinally() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * ���ʃN���X�ł̓R�[������� processFinal() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� doFinally() ���s��A<BR>
     * ���t���[���܂ł̎c���Ԃɗ]�T������� clean() �����s����B<BR>
     * ���̌�� nextFrame() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void doFinally();

    /**
     * �񊈓����������ɐ؂�ւ�������̃R�[���o�b�N .
     * �񊈓���Ԃ��犈����Ԃɕω������Ƃ��ɁA behave() �����O�ɂP��R�[���o�b�N�����B<BR>
     * �K�v�ɉ����ăI�[�o�[���C�h����B<BR>
     * ���R�[�������^�C�~���O�ڍׁ�
     * �@�񊈓����������ɐ؂�ւ������
     * nextFrame() �������A�O�t���[���̏�ԃt���O�u�񊈓���ԁv�ŁA���t���[���̏�ԃt���O���u������ԁv�ƂȂ�ꍇ�A
     * nextFrame() ���ŁA���t���[���̏�ԃt���O���u������ԁv�ɂ��A�t���[�����Z������ �R�[���o�b�N
     * �A������A�P�t���[���ڂ̎�
     * ���ۂɂ͑��݂��Ȃ��O�t���[��(0�t���[����)�̏�ԃt���O���A������̏����l�Łu�񊈓���ԁv�Ƃ��Ă���ׁB
     * ������A���߂� nextFrame() ���������ꍇ�AnextFrame() ���ŃR�[���o�b�N����邱�ƂɂȂ�B
     */
    virtual void onActive() {
    }

    /**
     * �������񊈓����ɐ؂�ւ�������̃R�[���o�b�N .
     * ������Ԃ���񊈓���Ԃɕω������Ƃ��ɂP��R�[���o�b�N�����B<BR>
     * �Ăяo�����^�C�~���O�̓t���[�����Z����ł���B�ʏ� behave() �����O�Ɏ��s�����B<BR>
     * �K�v�ɉ����ăI�[�o�[���C�h����B<BR>
     */
    virtual void onInactive() {
    }

    /**
     * �t���[�����̌ʐU�镑�������������B(���[�U�[�����p) .
     * behave() ���̏����擪�ŃR�[���o�b�N�����B<BR>
     * ���̃����o�֐������ʃN���X�ŃI�[�o�[���C�h���āA�m�[�h�ʂ̐U�镑������������������B<BR>
     * �z�肵�Ă���U�镑�������Ƃ́A��ɍ��W�v�Z�ƈړ��������ł���B<BR>
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��āAnextFrame() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     */
    virtual void processBehavior() = 0;

    /**
     * �t���[�����̌ʐU�镑�����㏈���������B(�t���[�����[�N�����p) .
     */
    virtual void processSettlementBehavior() {}

    /**
     * �t���[�����̌ʔ��f�����������B(���[�U�[�����p) .
     * judge() ���̏����擪�ŃR�[���o�b�N�����B<BR>
     * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʔ��f�������L�q����B<BR>
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��ĂāAprocessBehavior() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     * �{�����o�֐��̑��݈Ӑ}�Ƃ��āAprocessBehavior() �ō��W�ړ��������S�Ċ���������A
     * �{�����o�֐��œ����蔻�菈������������Ƃ������g������z�肵�Ă���B<BR>
     */
    virtual void processJudgement() = 0;

    /**
     * �m�[�h�̃t���[�����̌ʕ`�掖�O�����������B(�{�t���[�����[�N�����p) .
     * preDraw() ���̏����擪�ŃR�[���o�b�N�����B �A���A�_(GgafGod)���`��X�L�b�v�����ꍇ�A�t���[�����ŌĂяo����܂���B<BR>
     * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʕ`�掖�O��������������B<BR>
     * �ʕ`�掖�O�����Ƃ́A��ɓ�����w�i�`��Ȃǂł���B<BR>
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��āAprocessJudgement() �����s�ς݂ł��邱�Ƃ��ۏ؂���B<BR>
     * ����ɁA�{�����o�֐����s��AprocessDraw()�AprocessAfterDraw() ���Ăяo����邱�Ƃ��ۏ؂����B
     */
    virtual void processPreDraw() {};

    /**
     * �m�[�h�̃t���[�����̌ʕ`��{�����������B(�{�t���[�����[�N�����p�^���[�U�[�����p) .
     * draw() ���̏����擪�ŃR�[���o�b�N�����B �A���ApreDraw() �Ɠ��l�ɐ_(GgafGod)���`��X�L�b�v���ꂽ�ꍇ�́A�t���[�����ŌĂяo����܂���B<BR>
     * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʕ`��{��������������B<BR>
     * �ʕ`��{�����Ƃ͎�ɃL�����N�^��A�w�i�̕`���z�肵�Ă���B
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��āAprocessPreDraw() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     */
    virtual void processDraw() = 0;

    /**
     * �m�[�h�̃t���[�����̌ʕ\�����㏈�����L�q�B(�{�t���[�����[�N�����p) .
     * afterDraw() ���̏����擪�ŃR�[���o�b�N�����B �A���ApreDraw() �Ɠ��l�ɐ_(GgafGod)���`��X�L�b�v���ꂽ�ꍇ�́A�t���[�����ŌĂяo����܂���B<BR>
     * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʕ\�����㏈������������B<BR>
     * �ʕ\�����㏈���Ƃ́A�őO�ʃ��C���[�Ŏ�������t�F�[�h�G�t�F�N�g��A��ɍőO�ʂɕ\���������\���Ȃǂł���B<BR>
     * �{�����o���R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��āAprocessDraw() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     */
    virtual void processAfterDraw() {};

    /**
     * �m�[�h�̃t���[�����̌ʏI�[�����������B(�{�t���[�����[�N�����p) .
     * doFinally() ���̏����擪�ŃR�[���o�b�N�����B<BR>
     * ���̃����o�֐������ʃN���X�ŃI�[�o�[���C�h���āA�m�[�h�ʂ̏I�[��������������B<BR>
     * �I�[�����Ƃ́A�t���O�Ǘ��̎��s�Ȃǂł���B<BR>
     * �z�肵�Ă���U�镑�������Ƃ́A��ɍ��W�v�Z�ƈړ������ł���B���̑��Ȃ�ł��ǂ��ł���B<BR>
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��āAprocessJudgement() �����s�ς݂� �`�揈���͏I�����Ă��邱�Ƃ�ۏ؂���B<BR>
     */
    virtual void processFinal() {};

    /**
     * ���m�[�h�Ǝ��m�[�h�����e�ɂ�����m�[�h�S�ĂɃC�x���g���b�Z�[�W��ʒm(�ʒm�ΏہF�c���[�S��) .
     * �C�x���g���󂯎�鑤�́AonCatchEvent(hashval, void) ���������K�v�ł��B<BR>
     * ���g�� onCatchEvent(hashval, void) �ɂ��ʒm�����̂Œ��ӂ��ĉ������B<BR>
     * @param prm_no �C�x���g���b�Z�[�W�ԍ�
     * @param prm_pSource  �C�x���g�p�ėp�|�C���^
     */
    virtual void throwEventUpperTree(hashval prm_no, void* prm_pSource);

    /**
     * ���m�[�h�Ǝ��m�[�h�����e�ɂ�����m�[�h�S�ĂɃC�x���g���b�Z�[�W��ʒm(�ʒm�ΏہF�c���[�S��) .
     * �C�x���g���󂯎�鑤�́AonCatchEvent(hashval, void) ���������K�v�ł��B<BR>
     * ���g�� onCatchEvent(hashval, void) �ɂ��ʒm�����̂Œ��ӂ��ĉ������B<BR>
     * �ėp���� void* �ɂ́Athis ���ݒ肳��܂��B<BR>
     * @param prm_no �C�x���g���b�Z�[�W�ԍ�
     */
    virtual void throwEventUpperTree(hashval prm_no) {
        throwEventUpperTree(prm_no, this);
    }


    /**
     * ���m�[�h�Ƃ��̔z���m�[�h�S�ĂɃC�x���g���b�Z�[�W��ʒm���܂�(�ʒm�ΏہF�����̐e�S��) .
     * �C�x���g���󂯎�鑤�́AonCatchEvent(hashval, void) ���������K�v�ł���B<BR>
     * ���g�� onCatchEvent(hashval, void) �ɂ��ʒm�����̂Œ��ӂ��ĉ������B<BR>
     * @param prm_no �C�x���g���b�Z�[�W�ԍ�
     * @param prm_pSource  �C�x���g�p�ėp�|�C���^
     */
    virtual void throwEventLowerTree(hashval prm_no, void* prm_pSource);

    /**
     * ���m�[�h�Ƃ��̔z���m�[�h�S�ĂɃC�x���g���b�Z�[�W��ʒm���܂�(�ʒm�ΏہF�����̐e�S��) .
     * �C�x���g���󂯎�鑤�́AonCatchEvent(hashval, void) ���������K�v�ł���B<BR>
     * ���g�� onCatchEvent(hashval, void) �ɂ��ʒm�����̂Œ��ӂ��ĉ������B<BR>
     * �ėp���� void* �ɂ́Athis ���ݒ肳��܂��B<BR>
     * @param prm_no �C�x���g���b�Z�[�W�ԍ�
     */
    virtual void throwEventLowerTree(hashval prm_no) {
        throwEventLowerTree(prm_no, this);
    }

    /**
     * �C�x���g�������̃R�[���o�b�N .
     * throwEventUpperTree() throwEventLowerTree() �Ŕ������ꍇ�R�[���o�b�N����܂��B<BR>
     * @param prm_no �C�x���g���b�Z�[�W�ԍ�
     * @param prm_pSource  �C�x���g�p�ėp�|�C���^
     */
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) = 0;


    virtual bool isDisappear();
    /**
     * �_�ɉy�� .
     * @return  �Ă΂�ďo�Ă����_
     */
    virtual GgafGod* askGod() = 0;

    //==================��ԑJ�ڃ��\�b�h�S==================>
    /**
     * ������Ԃɂ���(���s�ΏہFthis �̂�) .
     * ���m�ɂ́A���m�[�h�������t���[�����犈����Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪����(nextFrame())���ŁA�߂ł����������(_is_active_flg = true)�ɂȂ�B<BR>
     * ���O�̏�Ԃ��񊈓��������Ȃ�΁A�擪�������� onActive() �̃R�[���o�b�N���s����B<BR>
     * ���������āA�{���\�b�h�����s���Ă��w����t���[�����x�͊�����Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B<BR>
     * ���� inactivateDelay() ���s�ς݂̏ꍇ�́A���������activate()���L���ɂȂ�B<BR>
     * ���� activateDelay() ���s�ς݂̏ꍇ�́A����w��Z�t���[��1��(activate() = activateDelay(1))�㏑������B<BR>
     * <B>[�⑫]</B><BR>
     * �m�[�h��������̓f�t�H���g�Ŋ�����ԂƂȂ��Ă��邽�߁A�ŏ��� activate() �s�v�B<BR>
     * <B>�y���Ӂz</B><BR>
     * processBehavior() �� ���g�� activate() ���Ăяo���R�[�h�͒ʏ�Ӗ��������B<BR>
     * �^�X�N�V�X�e���̎d�g�ݏ� processBehavior() �͊�����Ԃɂ̂ݎ��s�����̂ŁA�i���Ɏ��s����Ȃ����ɂȂ�B<BR>
     */
    virtual void activate();

    /**
     * ������Ԃɂ���(���s�ΏہF���c���[�S��) .
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� activate() �����s�����B<BR>
     */
    virtual void activateTree();

    /**
     * �����x�����Ă��犈����Ԃɂ���(���s�ΏہFthis �̂�) .
     * �����̃t���[�����x������ activate() �����s�����B<BR>
     * activateDelay(1) �́Aactivate() �Ɠ����Ӗ��ɂȂ�B<BR>
     * @param prm_offset_frames �x���t���[����(1�`)
     */
    virtual void activateDelay(frame prm_offset_frames = 1);

    /**
     * �����x�����Ă��犈����Ԃɂ���(���s�ΏہF���c���[�S��) .
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� activateDelay(frame) �����s�����B<BR>
     * activateTreeDelay(1) �́AactivateTree() �Ɠ����Ӗ��ɂȂ�B<BR>
     * @param prm_offset_frames �x���t���[����(1�`)
     */
    virtual void activateTreeDelay(frame prm_offset_frames = 1);

    /**
     * ��莞�Ԃ���������Ԃɂ���(���s�ΏہFthis �̂�) .
     * ������Ԃɂ�����A�����̃t���[�����o�߂���ƁA�񊈓���ԂɂȂ�B
     * activateWhile(10); ��
     * activate(); inactivateDelay(10); �̎��s�Ɠ����̌��ʂł���B
     * @param prm_frames �����t���[��
     */
    virtual void activateWhile(frame prm_frames = 1);

    /**
     * �����Ɋ�����Ԃɂ���(���s�ΏہFthis �̂�) .
     * �����ɏ�ԃt���O���X�V(_is_active_flg = true)����B<BR>
     * onActive() �R�[���o�b�N�͎��s����Ȃ��B�������ȊO�Ŗ{���\�b�h�̎g�p�͔񐄏��B<BR>
     * �ȉ��̓_�𗯈ӂ��Ďg�p����ۂ͒��ӂ��K�v�ł���B<BR>
     * �w����t���[�����x�ł����Ă��A���ɏ������ꂽ�m�[�h�Ɩ������̃m�[�h�ŁA�قȂ��ԂɂȂ��Ă��܂��B<BR>
     * �����ŁA�u���̃m�[�h��������ԂȂ�΁E�E�E�v���A���̏�ԁi�t���O�j�ɂ�蕪�򂵂Ă����ꍇ�A<BR>
     * ����t���[�����̏������ʂ̐�����������鋰�ꂪ����B<BR>
     * ���m�[�h�̉e���A�c���[�\����ǂ��l���Ďg�p���邱�ƁB<BR>
     */
    virtual void activateImmed();

    /**
     * �����Ɋ�����Ԃɂ���(���s�ΏہF���c���[�S��) .
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� activateImmed() �����s�����B<BR>
     * activateImmed() �̐�����v�Q�ƁB<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    virtual void activateTreeImmed();
    //===================

    /**
     * �񊈓���Ԃɂ���(���s�ΏہFthis �̂�) .
     * ���m�ɂ́A���m�[�h�������t���[������񊈓���Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪����(nextFrame())���ŁA�{���̔񊈓����(_is_active_flg = false)�ɂȂ�B<BR>
     * ���O�̏�Ԃ�������Ԃ������Ȃ�΁A�擪�������� onInactive() �̃R�[���o�b�N���s����B<BR>
     * ���������āA�{���\�b�h�����s���Ă��w����t���[�����x�͊�����Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B<BR>
     */
    virtual void inactivate();

    /**
     * �񊈓���Ԃɂ���
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� inactivate() �����s�����B<BR>
     */
    virtual void inactivateTree();

    /**
     * �����x�����Ă���񊈓���Ԃɂ���(���s�ΏہFthis �̂�) .
     * �����̃t���[�����x������ inactivate() �����s�����B<BR>
     * inactivateDelay(1) �́Ainactivate() �Ɠ����Ӗ��ɂȂ�B<BR>
     * @param prm_offset_frames �x���t���[����(1�`)
     */
    virtual void inactivateDelay(frame prm_offset_frames = 1);


    /**
     * �����x�����Ă��犈����Ԃɂ���(���s�ΏہF���c���[�S��) .
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� inactivateDelay(frame) �����s�����B<BR>
     * inactivateDelay(1) �́AinactivateTree() �Ɠ����Ӗ��ɂȂ�B<BR>
     * @param prm_offset_frames �x���t���[����(1�`)
     */
    virtual void inactivateTreeDelay(frame prm_offset_frames = 1);

    /**
     * �����ɔ񊈓���Ԃɂ���(���s�ΏہFthis �̂�) .
     * �����ɏ�ԃt���O���X�V(_is_active_flg = false)����B<BR>
     * onInactive() �R�[���o�b�N�͎��s����Ȃ��B�������ȊO�Ŗ{���\�b�h�̎g�p�͔񐄏��B<BR>
     * �ȉ��̓_�𗯈ӂ��Ďg�p����ۂ͒��ӂ��K�v�ł���B<BR>
     * �w����t���[�����x�ł����Ă��A���ɏ������ꂽ�m�[�h�Ɩ������̃m�[�h�ŁA�قȂ��ԂɂȂ��Ă��܂��B<BR>
     * �����ŁA�u���̃m�[�h���񊈓���ԂȂ�΁E�E�E�v���A���̏�ԁi�t���O�j�ɂ�蕪�򂵂Ă����ꍇ�A<BR>
     * ����t���[�����̏������ʂ̐�����������鋰�ꂪ����B<BR>
     * ���m�[�h�̉e���A�c���[�\����ǂ��l���Ďg�p���邱�ƁB<BR>
     */
    virtual void inactivateImmed();

    /**
     * �����ɔ񊈓���Ԃɂ���(���s�ΏہF���c���[�S��) .
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� inactivateImmed() �����s�����B<BR>
     * inactivateImmed() �̐�����v�Q�ƁB<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    virtual void inactivateTreeImmed();

    //===================
    /**
     * �ꎞ��~��Ԃɂ���(���s�ΏہFthis �̂�) .
     * ���m�ɂ́A���m�[�h�������t���[������ꎞ��~�ɂ���\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪����(nextFrame())���ŁA�߂ł����ꎞ��~���(_was_paused_flg = true)�ɂȂ�B<BR>
     * ���������āA�{���\�b�h�����s���Ă��w����t���[�����x�͈ꎞ��~��Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B<BR>
     */
    virtual void pause();

    /**
     * �ꎞ��~��Ԃɂ���(���s�ΏہF���c���[�S��) .
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� pause() �����s�����B<BR>
     */
    virtual void pauseTree();

    /**
     * �����Ɉꎞ��~��Ԃɂ���(���s�ΏہFthis �̂�) .
     * �����Ɉꎞ��~��ԃt���O���X�V(_was_paused_flg = true)����B<BR>
     * �w����t���[�����x�ł����Ă��A���ɏ������ꂽ�m�[�h�Ɩ������̃m�[�h�ŁA�قȂ��ԂɂȂ��Ă��܂��B<BR>
     * ���m�[�h�̉e���A�c���[�\����ǂ��l���Ďg�p���邱�ƁB<BR>
     */
    virtual void pauseImmed();

    /**
     * �����Ɉꎞ��~��Ԃɂ���(���s�ΏہF���c���[�S��) .
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� pauseImmed() �����s�����B<BR>
     * pauseImmed() �̐�����v�Q�ƁB<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    virtual void pauseTreeImmed();

    //===================
    /**
     * �ꎞ��~��Ԃ���������(���s�ΏہFthis �̂�) .
     * ���m�ɂ́A���m�[�h�������t���[������ꎞ��~��Ԃ���������\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪����(nextFrame())���ŁA�߂ł����ꎞ��~��ԉ���(_was_paused_flg = false)�ɂȂ�B<BR>
     * ���������āA�{���\�b�h�����s���Ă��w����t���[�����x�͈ꎞ��~��Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B<BR>
     */
    virtual void unpause();

    /**
     * �ꎞ��~��Ԃ���������(���s�ΏہF���c���[�S��) .
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� unpause() �����s�����B<BR>
     */
    virtual void unpauseTree();

    /**
     * �����Ɉꎞ��~��Ԃ���������(���s�ΏہFthis �̂�) .
     * �����Ɉꎞ��~��ԃt���O���X�V(_was_paused_flg = false)����B<BR>
     * �w����t���[�����x�ł����Ă��A���ɏ������ꂽ�m�[�h�Ɩ������̃m�[�h�ŁA�قȂ��ԂɂȂ��Ă��܂��B<BR>
     * ���m�[�h�̉e���A�c���[�\����ǂ��l���Ďg�p���邱�ƁB<BR>
     */
    virtual void unpauseImmed();

    /**
     * �����Ɉꎞ��~��Ԃ���������(���s�ΏہF���c���[�S��) .
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� unpauseImmed() �����s�����B<BR>
     * unpauseImmed() �̐�����v�Q�ƁB<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    virtual void unpauseTreeImmed();


    //===================
    /**
     * ��Ԃ����Z�b�g���邽�߂̏����ł��� onReset() ���R�[���o�b�N����B(���s�ΏہFthis�̂�) .
     * ���̂悤�ȓ�����w�����x�ɍs���܂��B<BR>
     * ���t���[���̐擪����( nextFrame() )���ł͂���܂���B<BR>
     * ����t���[�����ŉ��x reset() ���Ăяo���Ă��A�P�t���[���� onReset() �͂P�񂵂��Ă΂�Ȃ�
     * �悤�ɂ��邽�߂̃��\�b�h�ł���B���̂悤�ɓ��삷��B<BR>
     * �@ ����t���[�����ŁA���߂Ă̌Ăяo���ł��邩�`�F�b�N<BR>
     *   �E���߂Ă̌Ăяo���ł���B  �� �A��<BR>
     *   �E�Q��ȏ�Ăяo����Ă���B�� �������Ȃ���return<BR>
     * �A ���ʎ��������� onReset() ���R�[���o�b�N����B<BR>
     * �⑫:������ initialize() �Ăяo������ɁA�P�񂾂� reset() �͎����I�ɌĂяo�����B<BR>
     */
    virtual void reset();
    // ������ initialize(), onReset(), onActive() �̎g�������ɂ��ā�
    // ��Ԃ����Z�b�g�����́A�ǂ��Ɏ�������ׂ����H
    // initialize() �E�E�E ������A�ŏ��̂P�񂾂����O�ɃR�[���o�b�N�����B�������������Ɏg�p���邱�Ƃ�z��B
    // onReset()    �E�E�E ������Ainitialize() �̌�A�P�񂾂��������ŃR�[�������B
    //                     ���̌�A�C�ӂ̃^�C�~���O�� reset() ���s�ŃR�[���o�b�N�����B
    // onActive()   �E�E�E ������Ainitialize() �̌�̊�����Ԏ� �P�t���[���ڂ� behave() ���O�ɃR�[�������B
    //                     ���̌� �񊈓���������ԂɂȂ������A�����I�ɃR�[���o�b�N�����B
    // �m�[�h(�A�N�^�[��V�[��)�̏����T�C�N���ɂ���Ďg��������B
    // �A�N�^�[������A���̃R���X�g���N�^�ŉ������Ȃ������ꍇ�A�ŏ��� nextFrame() ����
    // initialize() �� onReset() ��onActive() �̏��Ɏ��s����邱�ƂɂȂ�B
    //
    // �E�P�T�C�N���ȃm�[�h(�A�N�^�[��V�[��)�̏ꍇ
    // ������A���߂Ắu�I���v�Ƃ�����Ԃ��}�����ۂɁA���̂܂܉���ƂȂ�ꍇ�B�܂�A�C���X�^���X���g���܂킳�Ȃ��ꍇ�B
    // initialize(), onReset(), onActive() �͎��O�Ɋe�P����s�����̂ŁA�ǂ��ɏ�Ԃ����Z�b�g�������������Ă����ق͖����͂��B
    // �����̒ʏ�̃A�N�^�[��A�ꎞ�I�ȒZ���V�[���͂���ɊY������Ɨ\�z����B
    // �ǂ��Ɏ������Ă��ǂ����Ainitialize() �Ŏ����𓝈ꂵ���ق����A���̃I�u�W�F�N�g���瑀�삵�₷���B
    //
    // �EonActive() ���g�p���ׂ��ꍇ
    // �������ꂽ�m�[�h�ɁA�u�\���v�u��\���v�Ƃ�����Ԃ����݂��A�g���܂킷�ꍇ�B
    // �\��(����) �` ��\��(�񊈓�) ���A�m�[�h�̂P�T�C�N���̂ƈ�v����ꍇ�B
    // initialize() �E�E�E �����������A
    // onActive()   �E�E�E ��ԃ��Z�b�g����
    // �Ǝg�������ċL�q���B inacivate()�Aactive() �ŏ�ԃ��Z�b�g�s���B
    // �Ȃ� onReset() �ɏ�ԃ��Z�b�g�������L�q���Areset()�R�[���ł͂����Ȃ��̂��Ƃ����ƁA
    // �����̒��S�ł��� processBehavior() ���\�b�h�́A��\��(�񊈓�) �̓R�[������Ȃ����߁A
    // ���g�̃I�u�W�F�N�g�̏����� reset() ���L�q���Ă����s����邱�Ƃ������Ƃ������ԂɊׂ�B
    // �������A���̃I�u�W�F�N�g����A��\��(�񊈓�)���\��(����) ���`�F�b�N���Areset() �����s���Ă������
    // ���Ȃ����A�����Z�b�g�����̂��A������ǂ������Ȃ��ƕ�����Ȃ��悤�ɂȂ�Ƃ����f�����b�g������̂ł͂Ȃ����낤���B
    // onActive() ���R�[������Ă��AgetBehaveingFrame() �́u���Z�b�g����Ȃ��v���A
    // getActiveFrame()�́u���Z�b�g�v����鎖�ɒ��ӁB
    // ��ɓG�e�Ȃǔėp�I�ȃA�N�^�[�́A����ɊY������Ɨ\�z����B
    //
    // �EonReset() ���g�p���ׂ��ꍇ
    // �������ꂽ�m�[�h�ɁA�u�\���v�u��\���v�Ƃ����T�O�������i�����͕\�������ςȂ��j�ŁA
    // �Ȃ����A�����T�C�N���i���Z�b�g�j�̊T�O������m�[�h�ꍇ
    // initialize() �E�E�E �����������A
    // onReset()    �E�E�E ��ԃ��Z�b�g����
    // �Ǝg�������ċL�q���B reset() �ŏ�ԃ��Z�b�g���s���B
    // onReset() �R�[���o�b�N���́A�����t���[���J�E���^�́u���Z�b�g�����v���ɒ��ӁB
    // ��ɃV�[���ƁA�ꕔ�̃A�N�^�[�́A����ɊY������Ɨ\�z����B
    //
    // �EonActive() onReset() �������Ďg�p���ׂ��ꍇ�B
    // �\��(����) �` ��\��(�񊈓�) ���A�m�[�h�̂P�T�C�N���ƈ�v���Ȃ��ꍇ�A
    // initialize() �E�E�E �����������A
    // onActive()   �E�E�E ��ʕ`�掞����������
    // onReset()    �E�E�E ��ԃ��Z�b�g����
    // �Ǝg�������ċL�q���B inacivate()�Aactivate() �� reset() ���R�[�����B
    // reset() �ŏ�ԃ��Z�b�g���s���B
    // ���@�͂���ɊY������Ɨ\�z�B
    //
    // �Einitialize() onActive() onReset() �ǂ����ł��悢�ꍇ�B
    // �\��(����) �` ��\��(�񊈓�) ���A�m�[�h�̐����`����Ɉ�v����ꍇ�B
    // �܂胊�Z�b�g�Ƃ������g���񂷊T�O���Ȃ��I�u�W�F�N�g�́A�I�u�W�F�N�g�̏�������
    // initialize() onActive() onReset() �̉����ɋL�q���Ă��قڈӖ��͓����ł���B
    // ��������A�\��(����)�܂łɃ^�C�����O���݂�Ȃ�΁AonActive() onReset() �̂ǂ��炩��
    // �L�q���ׂ����B


    /**
     * ��Ԃ����Z�b�g����(���s�ΏہF���c���[�S��) .
     * ���c���[�S�ẴI�u�W�F�N�g�ɑ΂� reset() ���w�����x���s����B
     * reset() �̐����v�Q�ƁB
     */
    virtual void resetTree();

    /**
     * ���ۂ̏�Ԃ����Z�b�g���鏈��(���[�U�[�����p) .
     * reset() �����́AresetTree() �����s���邱�ƂŃR�[���o�b�N�����B
     * �ʂ̂̏�ԃ��Z�b�g�������A���ʃN���X�ŃI�[�o�[���C�h���Ă��������B
     */
    virtual void onReset() {}


    /**
     * �I���錾����B(���s�ΏہF���c���[�S��) .
     * ���m�[�h�������̃t���[����Ɂu�����I���v��Ԃɂ��邱�Ƃ�錾����B�i�I���\��t���O�𗧂Ă�j <BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� end(frame) �����s���ꐶ���I���錾���s����B<br>
     * �e�m�[�h���I������΁A�q�m�[�h���I��������𓾂Ȃ�����ł���B<BR>
     * �I���t���O�͈�x���Ă�ƌ��ɂ��ǂ��܂���B�ȍ~ end(frame) ���d�˂ČĂяo���Ă���������A<BR>
     * �����̗P�\�t���[���́A���̃t���[����ɐ����I���ƂȂ�x���t���[�����ł���B<BR>
     * �u�����I���v�Ƃ͋�̓I�ɂ́A�U�镑���t���O(_is_active_flg)�A�����t���O(_can_live_flg) ���A
     * �A���Z�b�g����\��t���O�𗧂Ă邱�Ǝ��ŁA�P�\�t���[����̐擪����( nextFrame() )�Ŏ��ۂɃt���O���X�V����
     * �{���̏I����ԂɂȂ�B<BR>
     * _can_live_flg ���A���Z�b�g����邱�Ƃɂ��A�����I�Ƀc���[����؂藣����S�~��(GgafGarbageBox) �z���ɁA
     * �������邱�ƂɂȂ�B���̌�A�_(GgafGod)���]�T�̂��鎞 (FPS�������Ƃ�) �����v�炢 clean() ���\�b�h�ɂ��A<BR>
     * GgafGarbageBox �ɏ�������z���m�[�h�� delete ���邵�A�������[�����������B<BR>
     * <b>�y���Ӂz</b><BR>
     * ���C�Â����Ǝv�����A�{���\�b�h�����s���Ĉ����̗P�\�t���[����ɂȂ��Ă��A
     * GgafGarbageBox �z���Ɉڂ邾���ŁA�����ɂ� delete�����Ƃ͌���Ȃ����߁A
     * �s���|�C���^�ɂ����ݓI�o�O���N�����B�אS�̒��ӂ��͂炨���`�i����A�������߂��j<BR>
     * @param prm_offset_frames �����I���P�\�t���[��(1�`)
     */
    virtual void end(frame prm_offset_frames = 1);

    /**
     * �S�~���ɕ��荞�܂�钼�O�ɌĂяo�����R�[���o�b�N .
     * end(frame) ���s��A�S�~��(GgafGarbageBox) �Ɏ�荞�܂�钼�O�ɌĂяo�����B<BR>
     * �ő��ŁAend(frame) �Ŏw�肵���t���[�� + GGAF_END_DELAY ��ɔ�������B<BR>
     * �������������ƁA����ȏ�̐�̃t���[���Ŕ�������B<BR>
     * ���O�ɏ������K�v�ȏꍇ�́A�I�[�o�[���C�h���Ď����\�B<BR>
     */
    virtual void onEnd() {
    }

    /**
     * ���m�[�h���ŏI�m�[�h�Ɉړ����� .
     * ���m�ɂ́A���t���[������ŏI�m�[�h�Ɉړ�����\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪����(nextFrame())���ŁA���m�[�h���ŏI�m�[�h�Ɉړ������鏈�����s����B<BR>
     * ���m�[�h�͐؂藣����āA���ׂ̃m�[�h�͐V���ɐڍ����A���݂̍ŏI�m�[�h�̎��̃m�[�h���ăC���T�[�g�����B<BR>
     * �{���\�b�h�����s���Ă��w����t���[�����x�́A�m�[�h�ړ��͖������߁A��ѐ��͕ۂ����B<BR>
     */
    virtual void moveLast() override {
        _will_mv_last_in_next_frame_flg = true;
    }

    /**
     * �����Ɏ��m�[�h���ŏI�m�[�h�Ɉړ����� .
     * �����Ɏ��m�[�h���ŏI�m�[�h�Ɉړ��i���[�e�[�V�����j�����邱�Ƃɂ��A
     * ����t���[�����ŁA�m�[�h�����̂Q�d���s�A�������s���Ȃ��m�[�h�����������鋰�ꂪ����B<BR>
     * ���m�[�h�̉e���A�c���[�\����ǂ��l���Ďg�p���邱�ƁB<BR>
     */
    virtual void moveLastImmed() {
        GgafNode<T>::moveLast();
    }

    /**
     * ���m�[�h��擪�m�[�h�Ɉړ����� .
     * ���m�ɂ́A���t���[������ŏI�m�[�h�Ɉړ�����\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪����(nextFrame())���ŁA���m�[�h��擪�m�[�h�Ɉړ������鏈�����s����B<BR>
     * ���m�[�h�͐؂藣����āA���ׂ̃m�[�h�͐V���ɐڍ����A���݂̐擪�m�[�h�̑O�̃m�[�h���ăC���T�[�g�����B<BR>
     * �{���\�b�h�����s���Ă��w����t���[�����x�́A�m�[�h�ړ��͖������߁A��ѐ��͕ۂ����B<BR>
     */
    virtual void moveFirst() override {
        _will_mv_first_in_next_frame_flg = true;
    }

    /**
     * �����Ɏ��m�[�h��擪�m�[�h�Ɉړ����� .
     * �����Ɏ��m�[�h��擪�m�[�h�Ɉړ��i���[�e�[�V�����j�����邱�Ƃɂ��A
     * ����t���[�����ŁA�m�[�h�����̂Q�d���s�A�������s���Ȃ��m�[�h�����������鋰�ꂪ����B<BR>
     * ���m�[�h�̉e���A�c���[�\����ǂ��l���Ďg�p���邱�ƁB<BR>
     */
    virtual void moveFirstImmed() {
        GgafNode<T>::moveFirst();
    }

    /**
     * ���m�[�h���񊈓����犈����Ԃɐ؂�ւ�������ǂ������ׂ� .
     * onActive() ���Ă΂ꂽ�t���[���̂� true �ɂȂ�B
     * onActive() �I�[�o�[���C�h�Ŏ������ꍇ�́A���̕�����������L�q�ł���͂��B<BR>
     * ���̃m�[�h�̏�ԕω���m�肽�����̂��߂ɁA�{���\�b�h���������܂����B<BR>
     * @return  bool true:�񊈓����犈����Ԑ؂�ւ�����^false:�؂�ւ���Ă��Ȃ�
     */
    inline bool onChangeToActive();

    /**
     * ���m�[�h��������Ԃ���񊈓��ɐ؂�ւ�������ǂ������ׂ� .
     * onInctive() ���Ă΂ꂽ�t���[���̂� true �ɂȂ�B
     * onInctive() �I�[�o�[���C�h�Ŏ������ꍇ�́A���̕�����������L�q�ł���͂��B<BR>
     * ���̃m�[�h�̏�ԕω���m�肽�����̂��߂ɁA�{���\�b�h���������܂����B<BR>
     * @return  bool true:������Ԃ���񊈓��ɐ؂�ւ�����^false:�؂�ւ���Ă��Ȃ�
     */
    inline bool onChangeToInactive();

    /**
     * �����\��Ԃ����ׂ�
     * @return  bool true:�����\��ԁ^false:�����s���
     */
    inline bool canLive() {
        return _can_live_flg;
    }

    /**
     * �����������ׂ� .
     * ���g�t���O�̏�ԂŊ��������ǂ������f
     * @return  bool true:�������^false:�񊈓���
     */
    inline bool isActive();

    /**
     * ���c���[�Ŋ��������ǂ������f <BR>
     * ���Ƃ��΁A���g�t���O�̏�ԂŊ������ł��A�e���������łȂ��ꍇ�A
     * ���g�͊����o���Ȃ��B������l��������ŁA�{���Ɋ��������ǂ���������s���B
     * @return true:���c���[�Ŋ������^false:���c���[�Ŕ񊈓���
     */
    inline bool isActiveInTheTree();

    /**
     * �ꎞ��~��Ԃ��ǂ������f
     * @return true:�ꎞ��~��ԁ^false:�ꎞ��~��Ԃł͖���
     */
    inline bool wasPaused();

    /**
     * �I���錾�������ǂ��� .
     * end(frame) �����s�ς݂��ǂ������ׂ܂��B
     * @return true:�I���錾�ς݁^false:�܂��I���錾����Ă��Ȃ�
     */
    inline bool wasDeclaredEnd();

    /**
     * �U�镑����Ԏ��ɉ��Z�����t���[�������擾���� .
     * �u�U�镑����ԁv�Ƃ́AcanBehave() �� true �̏����������̎����Ӗ�����B<BR>
     * 0 Frame��Ԃ͊�{���݂����A1 Frame �` ����̒l�ɂȂ�B�A����O�I��<BR>
     * �������R���X�g���N�^���A����сA�ŏ��� initialize() ���ł� 0 Frame ��Ԃ��B<BR>
     * ������s�� onActive()�AprocessBehavior()�AprocessJudgement() ���̒��� 1 �ɂȂ��Ă���B<BR>
     * �ȍ~�A�U�镑���Ԏ��Ƀt���[�����Z�����B<BR>
     * @return �U�镑���t���[�������v
     */
    inline frame getBehaveingFrame() {
        return _frame_of_behaving;
    }

    /**
     * ���߂� onActive() ����J�n�����U�镑����Ԃ͉��t���[���ڂ���Ԃ��B .
     * �ėp�I�u�W�F�N�g�ȂǁA��x�������Ďg���܂킷(delete���Ȃ�)�ꍇ�A<BR>
     * �������� inactivate() �A�o���� activate() ���J��Ԃ����Ƃ��z�肳���B<BR>
     * ���̂悤�ȏꍇ�ɁA���t���[���ڂ����擾����ۂɓs�����ǂ����\�b�h�B<BR>
     * onActive() �R�[���o�b�N�����������Ƀ��Z�b�g(0)�����B<BR>
     * getBehaveingFrame() �Ɠ����^�C�~���O�ŉ��Z�����BprocessBehavior()�ł́A1 �` ��Ԃ��B
     * @return onActive() ����̐U�镑���t���[����
     */
    inline frame getActiveFrame() {
        return _frame_of_behaving_since_onActive;
    }

    /**
     * ���g�Ɣz���S�ẴI�u�W�F�N�g�ɑ΂��Ďw��̊֐������s������ .
     * �z���I�u�W�F�N�g�i�A�N�^�[���V�[���j�̃|�C���^���A�����֐��|�C���^�� pFunc�̑�P�����ɓn���Ă���B<BR>
     * �����֐��|�C���^�� pFunc �̑�Q�����ɂ́AexecuteFuncLowerTree �Ăяo������ prm1(�����P)�̃|�C���^���n���Ă���B<BR>
     * �����֐��|�C���^�� pFunc �̑�R�����ɂ́AexecuteFuncLowerTree �Ăяo������ prm2(�����Q)�̃|�C���^���n���Ă���B<BR>
     * �z���̃I�u�W�F�N�g�����ł���̂������Ă����Ŏg�p���Ȃ��Ɗ댯�ł���B<BR>
     * ���ƁA�����_���ƃL���v�`���[���g�킹�Ă��������B<BR>
     *
     * ���g�p�၄<BR>
     * XXXXActor �z���̃I�u�W�F�N�g�S�ẴA�N�^�[(�A��GgafDxGeometricActor)�̃����o�ϐ� _x �ɁA
     * XXXXActor�����o�ϐ� _velo �̒l�����Z������B<BR>
     * XXXXActor �N���X�̎����T���v�����ȉ��ɋL��<BR>
     * <code><pre>
     *
     * class XXXXActor : public GgafDxGeometricActor {
     * public :
     *     int velo_;
     *
     *     static void addX(GgafObject* pThat, void* p1, void* p2) {
     *         if (pThat->instanceOf(Obj_GgafDxGeometricActor)) { //GgafDxGeometricActor�Ȃ��
     *             GgafDxGeometricActor* pActor = (GgafDxGeometricActor*)pThat;
     *             pActor->_x += (*((int*)p1));  //_x ���Z�Bp1 �ɂ� velo_ �ւ̃|�C���^���n���Ă���
     *         }
     *     }
     *
     *     void processBehavior() {
     *         //�z���A�N�^�[�S�Ă�addX���s
     *         velo_ = 1000;
     *         executeFuncLowerTree(XXXXActor::addX, &velo_, nullptr);
     *     }
     * }
     *
     * </pre></code>
     * @param pFunc �I�u�W�F�N�g�Ɏ��s���������֐��B�p�����[�^��(GgafObject*, void*, void*) �Œ�B
     * @param prm1 �n�������������̂P
     * @param prm2 �n�������������̂Q
     */
    virtual void executeFuncLowerTree(void (*pFunc)(GgafObject*, void*, void*), void* prm1, void* prm2);


    /**
     * �i���Ǘ��I�u�W�F�N�g(GgafProgress) ���Ǘ�����i���̏ꍇ����ݒ肷��B
     * �{���\�b�h���s��A_pProg �����o�[���g�p�\�ɂȂ�B
     * @param prm_num �i���̏ꍇ�̐�
     */
    virtual void useProgress(int prm_num = 10) {
        if (_pProg == nullptr) {
            _pProg = NEW GgafProgress(&_frame_of_behaving, prm_num);
        } else {
            _TRACE_("���x����useProgress() ["<<GgafNode<T>::getName()<<"] �͊��� useProgress ���Ă���B�ȑO�̐i���̏ꍇ�̐�="<<_pProg->_num_progress<<"�B������� prm_num="<<prm_num);
            if (_pProg->_num_progress != prm_num) {
                throwGgafCriticalException("useProgress() ["<<GgafNode<T>::getName()<<"] �͊��� useProgress ���Ă���B�_������Ȃ��̂��H�I�B\n�ȑO�̐i���̏ꍇ�̐�="<<_pProg->_num_progress<<"�B������� prm_num="<<prm_num);
            }
        }
    }

    virtual GgafProgress* createProgress(int prm_num = 10) {
        return NEW GgafProgress(&_frame_of_behaving, prm_num);
    }

    /**
     * �c���[�l������m�[�h�����t���O(��)
     */
    virtual void updateActiveInTheTree() = 0;

};

///////////////////////////////////////////////////////////////// ��������͎�����

template<class T>
GgafElement<T>::GgafElement(const char* prm_name) : GgafCore::GgafNode<T>(prm_name),
_pGod(nullptr),
_was_initialize_flg(false),
_frame_of_life(0),
_frame_of_behaving(0),
_frame_of_behaving_since_onActive(0),
_is_active_flg(true),
_is_active_in_the_tree_flg(false),
_was_paused_flg(false),
_can_live_flg(true),
_was_paused_flg_in_next_frame(false),
_will_end_after_flg(false),
_frame_of_life_when_end(MAX_FRAME),
_will_activate_after_flg(false),
_frame_of_life_when_activation(0),
_will_inactivate_after_flg(false),
_frame_of_life_when_inactivation(0),
_on_change_to_active_flg(false),
_on_change_to_inactive_flg(false),
_will_mv_first_in_next_frame_flg(false),
_will_mv_last_in_next_frame_flg(false),
_is_already_reset(false),
_pProg(nullptr)
{

}

template<class T>
void GgafElement<T>::nextFrame() {
    //moveLast�\��
    if (_will_mv_last_in_next_frame_flg) {
        _will_mv_last_in_next_frame_flg = false;
        moveLastImmed();
        return;
        //��return���鎖�͏d�v�BnextFrame() �����̂Q�d���s�������邽�߁B
        //���̃m�[�h�́A�����ɉ񂳂�Ă��邽�߁A�K��������x nextFrame() �̋@��K���B
    }
    _was_paused_flg = _was_paused_flg_in_next_frame;
    if (!_was_paused_flg) {
        _frame_of_life++;
        if (_will_end_after_flg && _frame_of_life_when_end == _frame_of_life) {
            _can_live_flg = false; //�I���̎���
        }
        _on_change_to_active_flg = false;
        _on_change_to_inactive_flg = false;
        if (_can_live_flg) {
            if (_is_active_flg) {  //����activate
                if (_frame_of_life == 1) { //����activate �� �P�t���[����
                    _on_change_to_active_flg = true;  //onActive�m��
                } else { //����activate �� �Q�t���[���ڈȍ~

                    if (_will_inactivate_after_flg) {  //����activate �ŁA�Q�t���[���ڈȍ~�ŁA
                                                       //����� inactivate�\��
                        if (_frame_of_life == _frame_of_life_when_inactivation) { //����activate �ŁA�Q�t���[���ڈȍ~�ŁA
                                                                                  //inactivate�\��ŁA��inactivate�ɂȂ鎞������
                            _is_active_flg = false; //�����t���OOFF
                            _on_change_to_inactive_flg = true; //onInactive�m��
                        } else { //����activate �ŁA�Q�t���[���ڈȍ~�ŁAinactivate�\�肾���A
                                 //����inactivate�ɂȂ鎞�ł͂Ȃ�����
                            //���ɉ����Ȃ�
                        }
                    } else { //����activate �ŁA�Q�t���[���ڈȍ~�ŁA
                             //����� inactivate������Ⴕ�܂���B
                        //���ɉ����Ȃ�
                    }
                }
            } else { //����inactivate
                if (_will_activate_after_flg) { //����inactivate �����Aactivate�\��B

                    if(_frame_of_life == _frame_of_life_when_activation) { //����inactivate �����Aactivate�\��
                                                                           //�����āAactivate�ɂȂ鎞������
                        _is_active_flg = true; //�����t���OON
                        _on_change_to_active_flg = true;  //onActive����
                    } else { //����inactivate �����Aactivate�\��
                             //�����āA�܂�activate�ɂȂ鎞�͗��Ȃ�
                        //���ɉ����Ȃ�
                    }
                } else {  //����inactivate �ŁAactivate�\��������E�E�E
                    //���ɉ����Ȃ�
                }
            }
            _is_already_reset = false;

            updateActiveInTheTree();     //_is_active_in_the_tree_flg ���X�V

            if (_is_active_in_the_tree_flg) {
                _frame_of_behaving++;
                // �i���𔽉f
                if (_pProg) {
                    _pProg->update();
                }
                _frame_of_behaving_since_onActive++;
            }
            //onActive����
            if (_on_change_to_active_flg) {
                if (!_was_initialize_flg) {
                    initialize();       //������
                    _was_initialize_flg = true;
                    reset(); //���Z�b�g
                }
                _frame_of_behaving_since_onActive = 1; //���Z�b�g
                onActive(); //�R�[���o�b�N
                _frame_of_life_when_activation = 0;
                _will_activate_after_flg = false;
            }
            //onInactive����
            if (_on_change_to_inactive_flg) {
                onInactive(); //�R�[���o�b�N
                _frame_of_life_when_inactivation = 0;
                _will_inactivate_after_flg = false;
            }
        }
    }

    //�z���̑S�m�[�h�ɍċA�I��nextFrame()���s
    T* pElement = GgafNode<T>::_pSubFirst; //��z���̐擪�m�[�h
    if (pElement) {
        while(!pElement->_is_last_flg) {
            //��z���̐擪�`���ԃm�[�h�� nextFrame()
            pElement->nextFrame();
            if (pElement->_can_live_flg) {
                pElement = pElement->_pNext;
            } else {
                pElement->onEnd();
                pElement = pElement->_pNext; //��i�܂��đޔ������Ă���
                GgafGarbageBox::_pGarbageBox->add(pElement->_pPrev); //��O���S�~����(�A�����؂��)
            }
        }
        //��z���̖����m�[�h�� nextFrame()
        pElement->nextFrame();
        if (pElement->_can_live_flg) {
            //OK�������Ȃ�
        } else {
            pElement->onEnd();
            GgafGarbageBox::_pGarbageBox->add(pElement); //�S�~����
        }
    }

    if (_will_mv_first_in_next_frame_flg) {
        _will_mv_first_in_next_frame_flg = false;
        moveFirstImmed();
        //moveFirst����ԍŌ�ɂ��邱�Ƃ͏d�v�B
        //����� nextFrame() �̂Q�d���s������邽�߁B
    }
}

template<class T>
void GgafElement<T>::behave() {
    if ( _is_active_flg && _is_active_in_the_tree_flg && _can_live_flg && !_was_paused_flg) {
        processBehavior();    //���[�U�[�����p
        callRecursive(&GgafElement<T>::behave); //�ċA
    }
}

template<class T>
void GgafElement<T>::settleBehavior() {
    if ( _is_active_flg && _is_active_in_the_tree_flg && _can_live_flg) { //_was_paused_flg �͖Y��Ă��܂���
        processSettlementBehavior(); //�t���[�����[�N�p
        callRecursive(&GgafElement<T>::settleBehavior); //�ċA
    }
}

template<class T>
void GgafElement<T>::judge() {
    if ( _is_active_flg && _is_active_in_the_tree_flg && _can_live_flg && !_was_paused_flg) {
        processJudgement();    //���[�U�[�����p
        callRecursive(&GgafElement<T>::judge); //�ċA
    }
}

template<class T>
void GgafElement<T>::preDraw() {
    if ( _is_active_flg && _is_active_in_the_tree_flg && _can_live_flg) {
        processPreDraw();
        callRecursive(&GgafElement<T>::preDraw); //�ċA
    }
}

template<class T>
void GgafElement<T>::draw() {
    if ( _is_active_flg && _is_active_in_the_tree_flg && _can_live_flg) {
        processDraw();
        callRecursive(&GgafElement<T>::draw); //�ċA
    }
}

template<class T>
void GgafElement<T>::afterDraw() {
    if ( _is_active_flg && _is_active_in_the_tree_flg && _can_live_flg) {
        processAfterDraw();
        callRecursive(&GgafElement<T>::afterDraw); //�ċA
    }
}

template<class T>
void GgafElement<T>::doFinally() {
    if ( _is_active_flg && _is_active_in_the_tree_flg && _can_live_flg && !_was_paused_flg) {
        processFinal();
        callRecursive(&GgafElement<T>::doFinally); //�ċA
    }
}

template<class T>
void GgafElement<T>::reset() {
    if (_can_live_flg) {
        if(_was_initialize_flg == false) {
            initialize();       //������
            _was_initialize_flg = true;
        }
        if (_is_already_reset == false) {
            onReset();
            _is_already_reset = true;
        }
    }
}

template<class T>
void GgafElement<T>::resetTree() {
    if (_can_live_flg) {
        if(_was_initialize_flg == false) {
            initialize();       //������
            _was_initialize_flg = true;
        }
        if (_is_already_reset == false) {
            onReset();
            _is_already_reset = true;
        }
        callRecursive(&GgafElement<T>::resetTree); //�ċA
    }
}

template<class T>
void GgafElement<T>::activate() {
    if (_can_live_flg) {
        activateDelay(1);
    }
}

template<class T>
void GgafElement<T>::activateTree() {
    if (_can_live_flg) {
        activateDelay(1);
        callRecursive(&GgafElement<T>::activateTree); //�ċA
    }
}

template<class T>
void GgafElement<T>::activateImmed() {
    if (_can_live_flg) {
        _is_active_flg = true;
    }
}

template<class T>
void GgafElement<T>::activateTreeImmed() {
    if (_can_live_flg) {
        activateImmed();
        callRecursive(&GgafElement<T>::activateTreeImmed); //�ċA
    }
}

template<class T>
void GgafElement<T>::activateDelay(frame prm_offset_frames) {
#ifdef MY_DEBUG
    if (prm_offset_frames == 0) {
        throwGgafCriticalException("activateDelay(0) �͖��Ӗ��ł���B���܂ł� activate() ����܂����I�I�I�B�Ӑ}���Ă܂����H name="<<GgafNode<T>::_name<<" this="<<this);
    }
    if (prm_offset_frames >= 60*60*60) { //�P���Ԍ�
        throwGgafCriticalException("activateDelay("<<prm_offset_frames<<") ���Ēx������񂿂Ⴄ��H�B���܂ł� activate() ����܂����I�I�I�B���̐��ɂȂ����̂Ƃ������H�B name="<<GgafNode<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {
#ifdef MY_DEBUG
        if (_is_active_flg) {
            _TRACE_("���x����activateDelay("<<prm_offset_frames<<") ���܂������ǁA���Ɋ�����Ԃł���B�Ӑ}���Ă܂����H name="<<GgafNode<T>::_name<<" this="<<this);
        }
#endif
        //����inactivateDelay()���s�ς݂̏ꍇ��
        //����inactivateDelay()�͖����������B
        _will_inactivate_after_flg = false;

        //����activateDelay()���s�ς݂̏ꍇ�́A����w��Z�t���[���ŏ㏑������i�㏟���j�B
        //(��inactivateDelay() �ƗD��̍l�����Ⴄ���ߒ���)
        _will_activate_after_flg = true;
        _frame_of_life_when_activation = _frame_of_life + prm_offset_frames;
    }
}

template<class T>
void GgafElement<T>::activateWhile(frame prm_frames) {
#ifdef MY_DEBUG
    if (prm_frames == 0) {
        throwGgafCriticalException("activateWhile(0) �͖��Ӗ��ł���B���܂ł� activate() ����܂����I�I�I�B�Ӑ}���Ă܂����H name="<<GgafNode<T>::_name<<" this="<<this);
    }
    if (prm_frames >= 60*60*60) { //�P���Ԍ�
        throwGgafCriticalException("activateWhile("<<prm_frames<<") ���Ēx������񂿂Ⴄ��H�B���܂ł� activate() ����܂����I���̐��ɂȂ����̂Ƃ������H�B name="<<GgafNode<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {
        _will_activate_after_flg = true;
        _frame_of_life_when_activation = _frame_of_life + 1;
        _will_inactivate_after_flg = true;
        _frame_of_life_when_inactivation = _frame_of_life + prm_frames;
    }
}

template<class T>
void GgafElement<T>::activateTreeDelay(frame prm_offset_frames) {
#ifdef MY_DEBUG
    if (prm_offset_frames == 0) {
        throwGgafCriticalException("activateTreeDelay(0) �͖��Ӗ��ł���B���܂ł� activate() ����܂����I�I�I�B�Ӑ}���Ă܂����H name="<<GgafNode<T>::_name<<" this="<<this);
    }
    if (prm_offset_frames >= 60*60*60) { //�P���Ԍ�
        throwGgafCriticalException("activateTreeDelay("<<prm_offset_frames<<") ���Ēx������񂿂Ⴄ��H�B���܂ł� activate() ����܂����I���̐��ɂȂ����̂Ƃ������H name="<<GgafNode<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {
        activateDelay(prm_offset_frames);
        callRecursive(&GgafElement<T>::activateTreeDelay, prm_offset_frames); //�ċA
    }
}

template<class T>
void GgafElement<T>::inactivate() {
    if (_can_live_flg) {
        inactivateDelay(1);
    }
}

template<class T>
void GgafElement<T>::inactivateTree() {
    if (_can_live_flg) {
        inactivateDelay(1);
        callRecursive(&GgafElement<T>::inactivateTree); //�ċA
    }
}

template<class T>
void GgafElement<T>::inactivateDelay(frame prm_offset_frames) {
#ifdef MY_DEBUG
    if (prm_offset_frames == 0) {
        throwGgafCriticalException("inactivateDelay(0) �͖��Ӗ��ł���B���܂ł� inactivate() ����܂����I�I�I�B�Ӑ}���Ă܂����H name="<<GgafNode<T>::_name<<" this="<<this);
    }
    if (prm_offset_frames >= 60*60*60) { //�P���Ԍ�
        throwGgafCriticalException("inactivateDelay("<<prm_offset_frames<<") ���Ēx������񂿂Ⴄ��H�B���܂ł� inactivate() ����܂����I���̐��ɂȂ����̂Ƃ������H name="<<GgafNode<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {
        if (_will_activate_after_flg) {
            //����activateDelay()���s�ς݂̏ꍇ
            if (_frame_of_life_when_activation >= _frame_of_life + prm_offset_frames) {
                //inactive �\�������� active �\��Ȃ�΁A(active�ɂ͂Ȃ�Ȃ�����)�����ɂ���B
                _will_activate_after_flg = false;
            }
        }
        if (_will_inactivate_after_flg) {
            //����inactivateDelay()���s�ς݂̏ꍇ�A��葁�� inactivate ����Ȃ�Ώ㏑������
            if (_frame_of_life_when_inactivation < _frame_of_life + prm_offset_frames) {
                //����w��Z�t���[���̕����x���ꍇ�͖��������B
                return;
            }
        }
        _will_inactivate_after_flg = true;
        _frame_of_life_when_inactivation = _frame_of_life + prm_offset_frames;
    }
}

template<class T>
void GgafElement<T>::inactivateTreeDelay(frame prm_offset_frames) {
#ifdef MY_DEBUG
    if (prm_offset_frames == 0) {
        throwGgafCriticalException("inactivateTreeDelay(0) �͖��Ӗ��ł���B���܂ł� inactivate() ����܂����I�I�I�B�Ӑ}���Ă܂����H name="<<GgafNode<T>::_name<<" this="<<this);
    }
    if (prm_offset_frames >= 60*60*60) { //�P���Ԍ�
        throwGgafCriticalException("inactivateTreeDelay("<<prm_offset_frames<<") ���Ēx������񂿂Ⴄ��H�B���܂ł� inactivate() ����܂����I���̐��ɂȂ����̂Ƃ������H name="<<GgafNode<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {
        inactivateDelay(prm_offset_frames);
        callRecursive(&GgafElement<T>::inactivateTreeDelay, prm_offset_frames); //�ċA
    }
}

template<class T>
void GgafElement<T>::inactivateImmed() {
    if (_can_live_flg) {
        _is_active_flg = false;
    }
}

template<class T>
void GgafElement<T>::inactivateTreeImmed() {
    if (_can_live_flg) {
        inactivateImmed();
        callRecursive(&GgafElement<T>::inactivateTreeImmed); //�ċA
    }
}

template<class T>
void GgafElement<T>::pauseTree() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = true;
        callRecursive(&GgafElement<T>::pauseTree); //�ċA
    }
}

template<class T>
void GgafElement<T>::pause() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = true;
    }
}

template<class T>
void GgafElement<T>::pauseTreeImmed() {
    if (_can_live_flg) {
        _was_paused_flg = true;
        _was_paused_flg_in_next_frame = true;
        callRecursive(&GgafElement<T>::pauseTreeImmed); //�ċA
    }
}

template<class T>
void GgafElement<T>::pauseImmed() {
    if (_can_live_flg) {
        _was_paused_flg = true;
        _was_paused_flg_in_next_frame = true;
    }
}

template<class T>
void GgafElement<T>::unpauseTree() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = false;
        callRecursive(&GgafElement<T>::unpauseTree); //�ċA
    }
}

template<class T>
void GgafElement<T>::unpause() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = false;
    }
}

template<class T>
void GgafElement<T>::unpauseTreeImmed() {
    if (_can_live_flg) {
        _was_paused_flg = false;
        _was_paused_flg_in_next_frame = false;
        callRecursive(&GgafElement<T>::unpauseTreeImmed); //�ċA
    }
}

template<class T>
void GgafElement<T>::unpauseImmed() {
    if (_can_live_flg) {
        _was_paused_flg = false;
        _was_paused_flg_in_next_frame = false;
    }
}

template<class T>
void GgafElement<T>::end(frame prm_offset_frames) {
    if (_will_end_after_flg) {
        //����end()���s�ς݂̏ꍇ�A��葁��end()����Ȃ�ΗL���Ƃ���
        if (_frame_of_life_when_end < _frame_of_life + prm_offset_frames + GGAF_END_DELAY) {
            //����w��̕����x���t���[���w��ł��邽�ߖ�������B
            return;
        }
    }
    _will_end_after_flg = true;
    _frame_of_life_when_end = _frame_of_life + prm_offset_frames + GGAF_END_DELAY;
    inactivateDelay(prm_offset_frames);
    //�w��t���[�����ɂ́A�܂�inactivate���s���A+GGAF_END_DELAY �t���[���� _can_live_flg = false�ɂȂ�B
    //onEnd()�� _can_live_flg = false ������
    if (GgafNode<T>::_pSubFirst) {
        T* pElementTemp = GgafNode<T>::_pSubFirst;
        while(true) {
            pElementTemp->end(prm_offset_frames);
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
bool GgafElement<T>::isActive() {
    return (_can_live_flg && _is_active_flg) ? true : false;
}
template<class T>
bool GgafElement<T>::isActiveInTheTree() {
    return ( _is_active_flg && _is_active_in_the_tree_flg && _can_live_flg) ? true : false;
}

template<class T>
bool GgafElement<T>::onChangeToActive() {
    return (_can_live_flg && _on_change_to_active_flg) ? true : false;
}

template<class T>
bool GgafElement<T>::onChangeToInactive() {
    return (_can_live_flg && _on_change_to_inactive_flg) ? true : false;
}

template<class T>
bool GgafElement<T>::wasPaused() {
    return _was_paused_flg;
}

template<class T>
bool GgafElement<T>::wasDeclaredEnd() {
    return (_will_end_after_flg || _can_live_flg == false) ? true : false;
}

//template<class T>
//T* GgafElement<T>::extract() {
//    if (_can_live_flg) {
//        return extract();
//    } else {
//        //_TRACE_("[GgafElement<"<<_class_name<<">::extract()] ���x���� "<<getName()<<"�́A����ł��܂��B");
//        return extract();
//    }
//}

template<class T>
void GgafElement<T>::clean(int prm_num_cleaning) {
    if (GgafNode<T>::_pSubFirst == nullptr) {
        return;
    }

    T* pElementTemp = GgafNode<T>::_pSubFirst->_pPrev;
    T* pWk;

    while(GgafGarbageBox::_cnt_cleaned < prm_num_cleaning) {
        if (pElementTemp->_pSubFirst) {
            //�q�̎q���܂��̂��Ă���ꍇ����ɂ�����
            pElementTemp->clean(prm_num_cleaning);
            if (GgafGarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                break;
            }
        }
        if (pElementTemp->_is_first_flg) { //�Ō�̈��
            if (pElementTemp->_pSubFirst) {
                //�q�̎q���܂��̂��Ă���ꍇ����ɂ�����
                pElementTemp->clean(prm_num_cleaning);
                if (GgafGarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            if (pElementTemp->_can_live_flg == false) {
                GGAF_DELETE(pElementTemp);
                GgafGarbageBox::_cnt_cleaned++;
                if (GgafGarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            break;
        } else {
            pWk = pElementTemp;
            if (pWk->_pSubFirst) {
                //�q�̎q���܂��̂��Ă���ꍇ����ɂ�����
                pWk->clean(prm_num_cleaning);
                if (GgafGarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            pElementTemp = pElementTemp->_pPrev;
            if (pWk->_can_live_flg == false) {
                GGAF_DELETE(pWk);
                GgafGarbageBox::_cnt_cleaned++;
                if (GgafGarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
        }
    }
}


template<class T>
void GgafElement<T>::executeFuncLowerTree(void (*pFunc)(GgafObject*, void*, void*), void* prm1, void* prm2) {
    if (_can_live_flg && _is_active_flg) {   //TODO:active�t���O���A����Ă��ǂ����ȁE�E�E
        if (_was_initialize_flg) {
            pFunc(this, prm1, prm2);
        } else {

        }
        if (GgafNode<T>::_pSubFirst) {
            T* pElementTemp = GgafNode<T>::_pSubFirst;
            while(true) {
                pElementTemp->executeFuncLowerTree(pFunc, prm1, prm2);
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::throwEventLowerTree(hashval prm_no, void* prm_pSource) {
    if (_can_live_flg) {
        onCatchEvent(prm_no, prm_pSource);
        if (GgafNode<T>::_pSubFirst) {
            T* pElementTemp = GgafNode<T>::_pSubFirst;
            while(true) {
                pElementTemp->throwEventLowerTree(prm_no, prm_pSource);
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::throwEventUpperTree(hashval prm_no, void* prm_pSource) {
    if (_can_live_flg) {
        if (_was_initialize_flg) {
            onCatchEvent(prm_no, prm_pSource);
        }
        if (GgafNode<T>::_pParent) {
            T* pElementTemp = GgafNode<T>::_pParent;
            pElementTemp->throwEventUpperTree(prm_no, prm_pSource);
        } else {
            //�Ă��؂�
        }
    }
}

template<class T>
bool GgafElement<T>::isDisappear() {
    if (_is_active_in_the_tree_flg == false) {
        return true;
    } else {
        return false;
    }
}

template<class T>
GgafElement<T>::~GgafElement() {
    GGAF_DELETE_NULLABLE(_pProg);
}

}
#endif /*GGAFCORE_GGAFELEMENT_H_*/
