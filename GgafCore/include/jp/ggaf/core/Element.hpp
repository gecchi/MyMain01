#ifndef GGAF_CORE_ELEMENT_H_
#define GGAF_CORE_ELEMENT_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Node.hpp"

#include "jp/ggaf/core/Progress.h"
#include "jp/ggaf/core/GarbageBox.h"
#include "jp/ggaf/core/exception/CriticalException.h"

namespace GgafCore {

/**
 * �m�[�h(Node<T>)�ɁA�l�X�ȏ�ԊǗ��@�\��ǉ������N���X .
 * �����^�X�N�V�X�e���ɕK�v�ȏ�ԑJ�ڋ@�\����������Ă���B<BR>
 * ���t���[���A�_(God)�́A���̐�(Spacetime)�ɁA���̃��\�b�h�����ɌĂяo���d�g�݂ɂȂ��Ă���B<BR>
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
 * (�����N���X����Factor)
 * @tparam T �Ǘ�����v�f�̌^�i���̌^�̃|�C���^�^�������ŊǗ������B�j
 * @version 1.00
 * @since 2008/08/21
 * @author Masatoshi Tsuge
 */
template<class T>
class Element : public Node<T> {

private:
    /**
     * ���c���[�̔z���m�[�h�S�ĂɁA�ċA�Ăяo�����s���B
     * @param pFunc �ċA�Ăяo�����郁�\�b�h
     */
    inline void callRecursive(void (Element<T>::*pFunc)()) const {
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            (pElementTemp->*pFunc)(); //���s
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }

    /**
     * ���c���[�̔z���m�[�h�S�ĂɁA�ċA�Ăяo�����s���B
     * @param pFunc �ċA�Ăяo�����郁�\�b�h(frame �����L��)
     * @param prm_frame pFunc�̈����ł���frame
     */
    inline void callRecursive(void (Element<T>::*pFunc)(frame), frame prm_frame) const {
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            (pElementTemp->*pFunc)(prm_frame); //���s
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }


public:
    /** [r]�_�ւ̋ߓ� */
    God* _pGod;
    /** [r]initialize���s��ꂽ�ǂ����̃t���O(true=�s��ꂽ) */
    bool _was_initialize_flg;
    /** [r]�m�[�h���a��(appendChild���ꂽ�j������̃t���[�������v(�A���A_was_paused_flg = true ���͉��Z���ꖳ��) */
    frame _frame_of_life;
    /** [r]�m�[�h���a��(appendChild���ꂽ�j������A�U�������t���[�������v(�A���A_was_paused_flg = true ���� _is_active_flg = false ���͉��Z���ꖳ��) */
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
    /** [r]�I������\��� _frame_of_life */
    frame _frame_of_life_when_end;
    /** [r]�����J�n����\��� _frame_of_life */
    frame _frame_of_life_when_activation;
    /** [r]�����I������\��� _frame_of_life */
    frame _frame_of_life_when_inactivation;
    /** [r]������ԕύX���̃t���O�B0:�R�[���o�b�N�Ȃ� / 1:onInactive()������ / 2:onActive()������ */
    int _on_change_to;
    /** [r]�J�����g�t���[�����ň�x�ł����Z�b�g�����s������true�B���t���[�� false �ɍX�V����� */
    bool _is_already_reset;
    /** [r]��Ԑi���Ǘ��I�u�W�F�N�g */
    Progress* _pProg;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name �m�[�h���́i���j�[�N�ɂ��ĉ������j
     */
    explicit Element(const char* prm_name);

    /**
     * �f�X�g���N�^�B���c���[�m�[�h���������B .
     */
    virtual ~Element();

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
     * ���R���X�g���N�^��initialize()�̎g�������ɂ��ā�<BR>
     * �E�R���X�g���N�^�͈��Ő������ɌĂяo����邪�Ainitialize() �̓c���[�ɑ����A�����J�n���钼�O�ɌĂ΂��B
     * �Einitialize() �� �R���X�g���N�^�ł͕s�ȁA���z�֐����Ăׂ�Ƃ��������b�g������B<BR>
     * �Einitialize() �́A�P�Ȃ�֐��Ȃ̂ŁA�C�ӂ̉ӏ��Ŗ����I�ɉ��x�ł��Ăяo�����Ƃ��\�B<BR>
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
     * �_(God)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * �_(God)�́A���̐�(Spacetime)�ɑ΂��� nextFrame() ���s��A���� behave() �����s���邱�ƂɂȂ�B<BR>
     * ���̂悤�ȍ\���̏ꍇ�A���s���͇@�`�L�̏����ƂȂ�B������ pre-order ���B<BR>
     * �m�[�h�ԂŎQ�Ɗ֌W������ꍇ�́A���ӂ��K�v�B<BR>
     * <pre>
     * (�o)�̇@�o��(�o)
     *         ��
     * (�d)�̇A�`�̇E�a�̇J�b�̇K�c�̇L�d��(�`)
     *         ��    ����������������������������
     *         ��                              ��
     * (�g)�̇B�e�̇C�f�̇D�g��(�e)    (�k)�̇F�h�̇G�i�̇H�j�̇I�k��(�h)
     *
     * ����{�͐擪�������̏��A�A���q�����݂���ΐ�Ɏ��s�A���݂��Ȃ���Ύ�(��)�����s�B
     * </pre>
     * ���\�b�h�����Ɂw(���s�ΏہF���c���[�S��)�x�ƋL�q����Ă���ꍇ�́A�S�ď�L�̏����Ŏ��s�����B
     */
    virtual void nextFrame();

    /**
     * �m�[�h�̃t���[�����̐U�镑������(���s�ΏہF���c���[�S��) .
     * ���̏����ł́A�S�m�[�h���W�ړ��������s�����ƂƂ���B<BR>
     * �����p�� processBehavior() ���R�[���o�b�N����邽�߂̃t���O�̏����́A<BR>
     * �����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �i _is_active_in_the_tree_flg && !_was_paused_flg �j�̏ꍇ�ł���B <BR>
     * behave() �� ���z�֐� processBehavior() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� behave() ���ċA�I�Ɏ��s����B<BR>
     * �_(God)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�Ŗ{���\�b�h�𒼐ڌĂяo�����s��Ȃ����ƂƂ���B<BR>
     * ���ʃN���X�ł̓R�[������� processBehavior() ���I�[�o�[���C�h���ċ�̓I�ȍ��W�ړ����W�b�N����������B <BR>
     * �_(God)�́A���̐�(Spacetime)�ɑ΂��� behave() ���s��A���� settleBehavior() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void behave();

    /**
     * �m�[�h�̃t���[�����̐U�镑�����㏈��(���s�ΏہF���c���[�S��) .
     * ���̏����ł́A�S�m�[�h���W�ړ����������Ă��邱�Ƃ��ۏ؂��ꂽ��̏������s�����Ƃ���݌v�B<BR>
     * �X�V�������������W��񂩂�A����ɔ��������̗l�X�ȃX�e�[�^�X���̍X�V�����������ōs������ړI�Ƃ���<BR>
     * �����p�� processSettlementBehavior() ���R�[���o�b�N����邽�߂̃t���O�̏����́A<BR>
     * �ꎞ��~�t���O�̏�ԂƖ��֌W�Ɏ��s�����_�� behave() �ƈقȂ�B<BR>
     * settleBehavior()�́A���z�֐� processSettlementBehavior() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� settleBehavior() ���ċA�I�Ɏ��s����B<BR>
     * �_(God)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�Ŗ{���\�b�h�𒼐ڌĂяo�����s��Ȃ����ƂƂ���B<BR>
     * ���ʃN���X�ł̓R�[������� processSettlementBehavior() ���I�[�o�[���C�h���ă��W�b�N���������邱�ƂƂ���B <BR>
     * �_(God)�́A���̐�(Spacetime)�ɑ΂��� settleBehavior() ���s��A���� judge() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void settleBehavior();


    virtual void preJudge();
    /**
     * �m�[�h�̃t���[�����̔��菈��(���s�ΏہF���c���[�S��) .
     * ���̏����ł́A�m�[�h�Ԃ̗l�X�Ȕ��菈�����s�����Ƃ���݌v�B<BR>
     * �S�m�[�h���W�ړ������Ɣ��Ȃ��X�e�[�^�X�ނ̍X�V�����S�Ɋ������Ă��O��Ƃ��鏈�����s����B<BR>
     * �����p�� processJudgement() ���R�[���o�b�N����邽�߂̃t���O�̏����́Abehave()�Ɠ������A<BR>
     * �����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �܂� ( _is_active_in_the_tree_flg && !_was_paused_flg )�̏ꍇ <BR>
     * judge() �� ���z�֐� processJudgement() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� judge() ���ċA�I�Ɏ��s����B<BR>
     * �_(God)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�Ŗ{���\�b�h�𒼐ڌĂяo�����s��Ȃ����ƂƂ���B<BR>
     * ���ʃN���X�ł̓R�[������� processJudgement() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(God)�́A���̐�(Spacetime)�ɑ΂��� judge() ���s��A<BR>
     * �_(God)�͂��̌�A���t���[���܂ł̎c���Ԃɗ]�T������� preDraw() ������� doFinally() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void judge();

    /**
     * �m�[�h�̃t���[�����̕`�掖�O����(���s�ΏہF���c���[�S��)�i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����p�� processPreDraw() ���R�[���o�b�N���������́A�����t���O���Z�b�g<BR>
     * ( _is_active_in_the_tree_flg )�̏ꍇ�ł���B <BR>
     * processPreDraw() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� preDraw() ���ċA�I�Ɏ��s����B<BR>
     * �_(God)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * ���ʃN���X�ł̓R�[������� processPreDraw() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(God)�́A���̐�(Spacetime)�ɑ΂��� preDraw() ���s��A���� draw() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void preDraw();

    /**
     * �m�[�h�̃t���[�����̕`��{����(���s�ΏہF���c���[�S��)�i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����p�� processDraw() ���R�[���o�b�N���������́A�����t���O���Z�b�g<BR>
     * (_is_active_in_the_tree_flg)�̏ꍇ�ł���B <BR>
     * processDraw() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� draw() ���ċA�I�Ɏ��s����B<BR>
     * �_(God)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * ���ʃN���X�ł̓R�[������� processDraw() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(God)�́A���̐�(Spacetime)�ɑ΂��� draw() ���s��A���� afterDraw() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void draw();

    /**
     * �m�[�h�̃t���[�����̕`�掖�㏈��(���s�ΏہF���c���[�S��)�i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����p�� processAfterDraw() ���R�[���o�b�N���������́A�����t���O���Z�b�g<BR>
     * (_is_active_in_the_tree_flg)�̏ꍇ�ł���B <BR>
     * processAfterDraw() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� afterDraw() ���ċA�I�Ɏ��s����B<BR>
     * �_(God)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * ���ʃN���X�ł̓R�[������� processAfterDraw() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(God)�́A���̐�(Spacetime)�ɑ΂��� afterDraw() ���s��A���� doFinally() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void afterDraw();

    /**
     * �m�[�h�̃t���[�����̍ŏI����(���s�ΏہF���c���[�S��) .
     * ���W�ړ������A���菈���A�`�揈�����I��������ɁA�Ō�ɍs����n���������s�����Ƃ���݌v�B<BR>
     * �����p�� processFinal() ���R�[���o�b�N���������́A
     * �����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �i_is_active_in_the_tree_flg && !_was_paused_flg�j�̏ꍇ�ł���B <BR>
     * processFinal() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� doFinally() ���ċA�I�Ɏ��s����B<BR>
     * �_(God)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * ���ʃN���X�ł̓R�[������� processFinal() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(God)�́A���̐�(Spacetime)�ɑ΂��� doFinally() ���s��A<BR>
     * ���t���[���܂ł̎c���Ԃɗ]�T������� clean() �����s����B<BR>
     * ���̌�� nextFrame() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void doFinally();

    /**
     * �񊈓����������ɐ؂�ւ�������̃R�[���o�b�N(���[�U�[�����p) .
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
     * �������񊈓����ɐ؂�ւ�������̃R�[���o�b�N(���[�U�[�����p) .
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


    virtual void processPreJudgement() {}
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
     * preDraw() ���̏����擪�ŃR�[���o�b�N�����B �A���A�_(God)���`��X�L�b�v�����ꍇ�A�t���[�����ŌĂяo����܂���B<BR>
     * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʕ`�掖�O��������������B<BR>
     * �ʕ`�掖�O�����Ƃ́A��ɓ�����w�i�`��Ȃǂł���B<BR>
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��āAprocessJudgement() �����s�ς݂ł��邱�Ƃ��ۏ؂���B<BR>
     * ����ɁA�{�����o�֐����s��AprocessDraw()�AprocessAfterDraw() ���Ăяo����邱�Ƃ��ۏ؂����B
     */
    virtual void processPreDraw() {};

    /**
     * �m�[�h�̃t���[�����̌ʕ`��{�����������B(�{�t���[�����[�N�����p�^���[�U�[�����p) .
     * draw() ���̏����擪�ŃR�[���o�b�N�����B �A���ApreDraw() �Ɠ��l�ɐ_(God)���`��X�L�b�v���ꂽ�ꍇ�́A�t���[�����ŌĂяo����܂���B<BR>
     * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʕ`��{��������������B<BR>
     * �ʕ`��{�����Ƃ͎�ɃL�����N�^��A�w�i�̕`���z�肵�Ă���B
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��āAprocessPreDraw() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     */
    virtual void processDraw() = 0;

    /**
     * �m�[�h�̃t���[�����̌ʕ\�����㏈�����L�q�B(�{�t���[�����[�N�����p) .
     * afterDraw() ���̏����擪�ŃR�[���o�b�N�����B �A���ApreDraw() �Ɠ��l�ɐ_(God)���`��X�L�b�v���ꂽ�ꍇ�́A�t���[�����ŌĂяo����܂���B<BR>
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
     * �A���A�m�[�h�͐������c���[�̈���łȂ���Βʒm����܂���B<BR>
     * �������c���[�̈���Ƃ́A_can_live_flg �� _was_initialize_flg �� true �ł��鎖�ł��B<BR>
     * �C�x���g���󂯎�鑤�́AonCatchEvent(hashval, void) ���������K�v�ł��B<BR>
     * ���g�� onCatchEvent(hashval, void) �ɂ��ʒm�����̂Œ��ӂ��ĉ������B<BR>
     * @param prm_no �C�x���g���b�Z�[�W�ԍ�
     * @param prm_pSource  �C�x���g�p�ėp�|�C���^
     */
    virtual void throwEventUpperTree(hashval prm_no, void* prm_pSource);

    /**
     * ���m�[�h�Ǝ��m�[�h�����e�ɂ�����m�[�h�S�ĂɃC�x���g���b�Z�[�W��ʒm(�ʒm�ΏہF�c���[�S��) .
     * �A���A�m�[�h�͐������c���[�̈���łȂ���Βʒm����܂���B<BR>
     * �������c���[�̈���Ƃ́A_can_live_flg �� _was_initialize_flg �� true �ł��鎖�ł��B<BR>
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
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) {}


    virtual bool isDisappear();
    /**
     * �_�ɉy�� .
     * @return  �Ă΂�ďo�Ă����_
     */
    virtual God* askGod() = 0;

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
    // �������ꂽ�m�[�h�ɁA�u�\��(����)�v�u��\��(�񊈓�)�v�Ƃ�����Ԃ����݂��A���x���g���܂킷�ꍇ�B
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
    // �������ꂽ�m�[�h�ɁA�u�\��(����)�v�u��\��(�񊈓�)�v�Ƃ����T�O�������B�\��(����)�����ςȂ��B
    // �����������A�����T�C�N���i���Z�b�g�j�̊T�O������m�[�h�ꍇ
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
     * _can_live_flg ���A���Z�b�g����邱�Ƃɂ��A�����I�Ƀc���[����؂藣����S�~��(GarbageBox) �z���ɁA
     * �������邱�ƂɂȂ�B���̌�A�_(God)���]�T�̂��鎞 (FPS�������Ƃ�) �����v�炢 clean() ���\�b�h�ɂ��A<BR>
     * GarbageBox �ɏ�������z���m�[�h�� delete ���邵�A�������[�����������B<BR>
     * <b>�y���Ӂz</b><BR>
     * �{���\�b�h�����s���Ĉ����̗P�\�t���[����ɂȂ��Ă��A
     * GarbageBox �z���Ɉڂ邾���ŁA�����ɂ� delete�����Ƃ͌���Ȃ����߁A
     * �s���|�C���^�ɂ����ݓI�o�O���N�����B�אS�̒��ӂ��͂炨���`�i����A�������߂��j<BR>
     * @param prm_offset_frames �����I���P�\�t���[��(1�`)
     */
    virtual void end(frame prm_offset_frames = 1);

    /**
     * �S�~���ɕ��荞�܂�钼�O�ɌĂяo�����R�[���o�b�N(�t���[�����[�N�����p) .
     * end(frame) ���s��A�S�~��(GarbageBox) �Ɏ�荞�܂�钼�O�ɌĂяo�����B<BR>
     * �܂�A_can_live_flg �� false ���� true �ɂȂ������ɌĂяo�����B<BR>
     * �ł����A�܂��c���[�ɏ������Ă�����A���g�̃m�[�h�̍��͂܂��؂�Ă��Ȃ���Ԃł��B<BR>
     * �ő��ŁAend(frame) �Ŏw�肵���t���[�� + GGAF_END_DELAY ��ɔ�������B<BR>
     * �������������ƁA����ȏ�̐�̃t���[���Ŕ�������B<BR>
     * ���O�ɏ������K�v�ȏꍇ�́A�I�[�o�[���C�h���Ď����\�B<BR>
     */
    virtual void onEnd() {
    }

    /**
     * ���m�[�h���񊈓����犈����Ԃɐ؂�ւ�������ǂ������ׂ� .
     * onActive() ���Ă΂ꂽ�t���[���̂� true �ɂȂ�B
     * onActive() �I�[�o�[���C�h�Ŏ������ꍇ�́A���̕�����������L�q�ł���͂��B<BR>
     * ���̃m�[�h�̏�ԕω���m�肽�����̂��߂ɁA�{���\�b�h���������܂����B<BR>
     * @return  bool true:�񊈓����犈����Ԑ؂�ւ�����^false:�؂�ւ���Ă��Ȃ�
     */
    inline bool hasJustChangedToActive() const {
        return _on_change_to == 2 ? true : false;
    }

    /**
     * ���m�[�h��������Ԃ���񊈓��ɐ؂�ւ�������ǂ������ׂ� .
     * onInctive() ���Ă΂ꂽ�t���[���̂� true �ɂȂ�B
     * onInctive() �I�[�o�[���C�h�Ŏ������ꍇ�́A���̕�����������L�q�ł���͂��B<BR>
     * ���̃m�[�h�̏�ԕω���m�肽�����̂��߂ɁA�{���\�b�h���������܂����B<BR>
     * @return  bool true:������Ԃ���񊈓��ɐ؂�ւ�����^false:�؂�ւ���Ă��Ȃ�
     */
    inline bool hasJustChangedToInactive() const {
        return _on_change_to == 1 ? true : false;
    }

    /**
     * �����\��Ԃ����ׂ�
     * @return  bool true:�����\��ԁ^false:�����s���
     */
    inline bool canLive() const {
        return _can_live_flg;
    }

    /**
     * �����������ׂ� .
     * ���g�t���O�̏�ԂŊ��������ǂ������f
     * @return  bool true:�������^false:�񊈓���
     */
    inline bool isActive() const {
        return (_can_live_flg && _is_active_flg) ? true : false;
    }

    /**
     * ���c���[�Ŋ��������ǂ������f <BR>
     * ���Ƃ��΁A���g�t���O�̏�ԂŊ������ł��A�e���������łȂ��ꍇ�A
     * ���g�͊����o���Ȃ��B������l��������ŁA�{���Ɋ��������ǂ���������s���B
     * @return true:���c���[�Ŋ������^false:���c���[�Ŕ񊈓���
     */
    inline bool isActiveInTheTree() const {
        return (_is_active_in_the_tree_flg && _can_live_flg) ? true : false;
    }

    /**
     * �ꎞ��~��Ԃ��ǂ������f
     * @return true:�ꎞ��~��ԁ^false:�ꎞ��~��Ԃł͖���
     */
    inline bool wasPaused() const {
        return _was_paused_flg;
    }

    /**
     * �I���錾�������ǂ��� .
     * end(frame) �����s�ς݂��ǂ������ׂ܂��B
     * @return true:�I���錾�ς݁^false:�܂��I���錾����Ă��Ȃ�
     */
    inline bool wasDeclaredEnd() const {
        return (_frame_of_life_when_end > _frame_of_life || _can_live_flg == false) ? true : false;
    }

    /**
     * �U�镑����Ԏ��ɉ��Z�����t���[�������擾���� .
     * �u�U�镑����ԁv�Ƃ́AcanBehave() �� true �̏����������̎����Ӗ�����B<BR>
     * 0 Frame��Ԃ͊�{���݂����A1 Frame �` ����̒l�ɂȂ�B�A����O�I��<BR>
     * �������R���X�g���N�^���A����сA�ŏ��� initialize() ���ł� 0 Frame ��Ԃ��B<BR>
     * ������s�� onActive()�AprocessBehavior()�AprocessJudgement() ���̒��� 1 �ɂȂ��Ă���B<BR>
     * �ȍ~�A�U�镑���Ԏ��Ƀt���[�����Z�����B<BR>
     * @return �U�镑���t���[�������v
     */
    inline frame getBehaveingFrame() const {
        return _frame_of_behaving;
    }

    /**
     * ���߂� onActive() ����J�n�����U�镑����Ԃ͉��t���[���ڂ���Ԃ��B .
     * �ėp�I�u�W�F�N�g�ȂǁA��x�������Ďg���܂킷(delete���Ȃ�)�ꍇ�A<BR>
     * �������� inactivate() �A�o���� activate() ���J��Ԃ����Ƃ��z�肳���B<BR>
     * ���̂悤�ȏꍇ�ɁA���t���[���ڂ����擾����ۂɓs�����ǂ����\�b�h�B<BR>
     * onActive() �R�[���o�b�N�����������Ƀ��Z�b�g(0)����AonActive() ���ł́A��� 0 ��Ԃ��B<BR>
     * getBehaveingFrame() �Ɠ����^�C�~���O�ŉ��Z�����BprocessBehavior()�ł́A1 �` ��Ԃ��B<BR>
     * @return onActive() ����̐U�镑���t���[����
     */
    inline frame getActiveFrame() const {
        return _frame_of_behaving_since_onActive;
    }

    /**
     * ���g�Ɣz���S�ẴI�u�W�F�N�g�ɑ΂��Ďw��̊֐������s������ .
     * �z���I�u�W�F�N�g�i�A�N�^�[���V�[���j�̃|�C���^���A�����֐��|�C���^�� pFunc�̑�P�����ɓn���Ă���B<BR>
     * �����֐��|�C���^�� pFunc �̑�Q�����ɂ́AexecuteFuncLowerTree �Ăяo������ prm1(�����P)�̃|�C���^���n���Ă���B<BR>
     * �����֐��|�C���^�� pFunc �̑�R�����ɂ́AexecuteFuncLowerTree �Ăяo������ prm2(�����Q)�̃|�C���^���n���Ă���B<BR>
     * �����֐��|�C���^�� pFunc �̑�S�����ɂ́AexecuteFuncLowerTree �Ăяo������ prm3(�����R)�̃|�C���^���n���Ă���B<BR>
     * �z���̃I�u�W�F�N�g�����ł���̂������Ă����Ŏg�p���Ȃ��Ɗ댯�ł���B<BR>
     *
     * ���g�p�၄<BR>
     * XXXXActor �z���̃I�u�W�F�N�g�S�ẴA�N�^�[(�A��GgafDx::GeometricActor)�̃����o�ϐ� _x �ɁA
     * XXXXActor�����o�ϐ� _velo �̒l�����Z������B<BR>
     * XXXXActor �N���X�̎����T���v�����ȉ��ɋL��<BR>
     * <code><pre>
     *
     * class XXXXActor : public GgafDx::GeometricActor {
     * public :
     *     int velo_;
     *
     *     static void addX(Object* pThat, void* p1, void* p2, void* p3) {
     *         if (pThat->instanceOf(Obj_GgafDx_GeometricActor)) { //GeometricActor�Ȃ��
     *             GgafDx::GeometricActor* pActor = (GgafDx::GeometricActor*)pThat;
     *             pActor->_x += (*((int*)p1));  //_x ���Z�Bp1 �ɂ� velo_ �ւ̃|�C���^���n���Ă���
     *         }
     *     }
     *
     *     void processBehavior() {
     *         //�z���A�N�^�[�S�Ă�addX���s
     *         velo_ = 1000;
     *         executeFuncLowerTree(XXXXActor::addX, &velo_, nullptr, nullptr);
     *     }
     * }
     *
     * </pre></code>
     * @param pFunc �I�u�W�F�N�g�Ɏ��s���������֐��B�p�����[�^��(Object*, void*, void*, void*) �Œ�B
     * @param prm1 �n�������������̂P
     * @param prm2 �n�������������̂Q
     * @param prm3 �n�������������̂R
     */
    virtual void executeFuncLowerTree(void (*pFunc)(Object*, void*, void*, void*), void* prm1, void* prm2, void* prm3);

    /**
     * �i���Ǘ��I�u�W�F�N�g(Progress) ���擾����B
     * @return �i���Ǘ��I�u�W�F�N�g
     */
    inline virtual Progress* getProgress() const {
        return _pProg;
    }

    /**
     * �{�I�u�W�F�N�g�� _frame_of_behaving �Ɋ֘A�����������A�i���Ǘ��I�u�W�F�N�g(Progress) �𐶐����擾 .
     * �����Ői���̍X�V�͍s���Ȃ��̂ŁA�Ăяo������ update���s���Ă��������B
     * @param prm_num �i���̏ꍇ�̐�
     * @return �V�����i���Ǘ��I�u�W�F�N�g
     */
    virtual Progress* createProgress() {
        return NEW Progress(&_frame_of_behaving);
    }

    /**
     * �c���[�l������m�[�h�����t���O(��)
     */
    virtual void updateActiveInTheTree() = 0;

    /**
     * �����\�肩�ۂ���Ԃ� .
     * @return
     */
    inline bool willActivateAfter() {
        if (_frame_of_life_when_activation > _frame_of_life) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * �񊈓��\�肩�ۂ���Ԃ� .
     * @return
     */
    inline bool willInactivateAfter() {
        if (0 < _frame_of_life_when_inactivation &&
                _frame_of_life_when_inactivation > _frame_of_life) {
            return true;
        } else {
            return false;
        }
    }
};

///////////////////////////////////////////////////////////////// ��������͎�����

template<class T>
Element<T>::Element(const char* prm_name) :
    Node<T>(prm_name),
    _pGod(nullptr),
    _was_initialize_flg(false),
    _frame_of_life(0),
    _frame_of_behaving(0),
    _frame_of_behaving_since_onActive(0),
    _is_active_flg(false),             //���������false�ł��邪�A�������Ȃ��Ə���nextFrame()�ŃA�N�e�B�u�ɂȂ�\��
    _is_active_in_the_tree_flg(false),
    _was_paused_flg(false),
    _can_live_flg(true),
    _was_paused_flg_in_next_frame(false),
    _frame_of_life_when_end(0),
    _frame_of_life_when_activation(1), //����t���[���ɃA�N�e�B�u�ɂȂ邽�߂�1
    _frame_of_life_when_inactivation(0),
    _on_change_to(0),
    _is_already_reset(false),
    _pProg(nullptr)
{
}

template<class T>
void Element<T>::nextFrame() {
    _was_paused_flg = _was_paused_flg_in_next_frame;
    if (!_was_paused_flg) {
        const frame frame_of_life = (++_frame_of_life);
        _is_already_reset = false;
        if (frame_of_life == _frame_of_life_when_end) {
            _can_live_flg = false; //�I���̎���
        } else {
            if (_is_active_flg) {  //����activate
                if (frame_of_life == _frame_of_life_when_inactivation) { //���� activate �����A��inactivate�ɂȂ鎞������
                    _on_change_to = 1;
                    _is_active_flg = false; //�����t���OOFF
                    _is_active_in_the_tree_flg = false;
                    onInactive(); //�R�[���o�b�N
                } else {
                    _on_change_to = 0;
                    updateActiveInTheTree();     //_is_active_in_the_tree_flg ���X�V
                    if (_is_active_in_the_tree_flg) {
                        _frame_of_behaving++;
                        if (_pProg) {  _pProg->update();  } // �i���𔽉f
                        _frame_of_behaving_since_onActive++;
                    }
                }

            } else { //����inactivate
                if(frame_of_life == _frame_of_life_when_activation) { //����inactivate �����A��activate�ɂȂ鎞������
                    _on_change_to = 2;      //onActive����
                    _is_active_flg = true;  //�����t���OON
                    updateActiveInTheTree();     //_is_active_in_the_tree_flg ���X�V
                    if (_is_active_in_the_tree_flg) {
                        _frame_of_behaving++;
                        if (_pProg) {  _pProg->update();  } // �i���𔽉f
                        _frame_of_behaving_since_onActive++;
                    }
                    if (!_was_initialize_flg) {
                        initialize();       //������
                        _was_initialize_flg = true;
                        reset(); //���Z�b�g
                    }
                    _frame_of_behaving_since_onActive = 0; //���Z�b�g
                    onActive();   //�R�[���o�b�N
                    _frame_of_behaving_since_onActive = 1;
                } else {
                    _on_change_to = 0;
                    _is_active_in_the_tree_flg = false;
                }
            }
        }
    }
    //�ċA
    //�z���̑S�m�[�h�ɍċA�I��nextFrame()���s
    T* p = Node<T>::_pChildFirst; //��z���̐擪�m�[�h�B�����ꍇ�͐�ɐ���B
    if (p) {
        while (!p->_is_last_flg) {
            //�z���̐擪 �` ����-1 �m�[�h�� nextFrame()
            p->nextFrame();  //�ċA
            if (p->_can_live_flg) {
                p = p->_pNext;
            } else {
                p->onEnd();
                p = p->_pNext; //��Ɉ�i�܂��đޔ������Ă���
                GarbageBox::_pGarbageBox->add(p->_pPrev); //��O���S�~����(�A�����؂��)
            }
        }
        //�z���̍Ō�̖����m�[�h�� nextFrame()
        p->nextFrame(); //�ċA
        if (p->_can_live_flg) {
            //OK ���͖������e�m�[�h�̏�����
        } else {
            p->onEnd();
            GarbageBox::_pGarbageBox->add(p); //�S�~����
        }
    }
}

template<class T>
void Element<T>::behave() {
    if (_is_active_in_the_tree_flg && !_was_paused_flg) {
        processBehavior();    //���[�U�[�����p
        callRecursive(&Element<T>::behave); //�ċA
    }
}

template<class T>
void Element<T>::settleBehavior() {
    if (_is_active_in_the_tree_flg) { //_was_paused_flg �͖Y��Ă��܂���
        processSettlementBehavior(); //�t���[�����[�N�p
        callRecursive(&Element<T>::settleBehavior); //�ċA
    }
}

template<class T>
void Element<T>::preJudge() {
    if (_is_active_in_the_tree_flg) { //_was_paused_flg �͖Y��Ă��܂���
        processPreJudgement();    //�t���[�����[�N�p
        callRecursive(&Element<T>::preJudge); //�ċA
    }
}

template<class T>
void Element<T>::judge() {
    if (_is_active_in_the_tree_flg && !_was_paused_flg) {
        processJudgement();    //���[�U�[�����p
        callRecursive(&Element<T>::judge); //�ċA
    }
}

template<class T>
void Element<T>::preDraw() {
    if (_is_active_in_the_tree_flg) {
        processPreDraw();
        callRecursive(&Element<T>::preDraw); //�ċA
    }
}

template<class T>
void Element<T>::draw() {
    if (_is_active_in_the_tree_flg) {
        processDraw();
        callRecursive(&Element<T>::draw); //�ċA
    }
}

template<class T>
void Element<T>::afterDraw() {
    if (_is_active_in_the_tree_flg) {
        processAfterDraw();
        callRecursive(&Element<T>::afterDraw); //�ċA
    }
}

template<class T>
void Element<T>::doFinally() {
    if (_is_active_in_the_tree_flg && !_was_paused_flg) {
        processFinal();
        callRecursive(&Element<T>::doFinally); //�ċA
    }
}

template<class T>
void Element<T>::reset() {
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
void Element<T>::resetTree() {
    if (_can_live_flg) {
        if(_was_initialize_flg == false) {
            initialize();       //������
            _was_initialize_flg = true;
        }
        if (_is_already_reset == false) {
            onReset();
            _is_already_reset = true;
        }
        callRecursive(&Element<T>::resetTree); //�ċA
    }
}

template<class T>
void Element<T>::activate() {
    if (_can_live_flg) {
        activateDelay(1);
    }
}

template<class T>
void Element<T>::activateTree() {
    if (_can_live_flg) {
        activateDelay(1);
        callRecursive(&Element<T>::activateTree); //�ċA
    }
}

template<class T>
void Element<T>::activateImmed() {
    if (_can_live_flg) {
        if (!_was_initialize_flg) {
            initialize();       //������
            _was_initialize_flg = true;
            reset(); //���Z�b�g
        }
        _is_active_flg = true;
        _frame_of_life_when_activation = _frame_of_life;
        updateActiveInTheTree();
    }
}

template<class T>
void Element<T>::activateTreeImmed() {
    if (_can_live_flg) {
        activateImmed();
        callRecursive(&Element<T>::activateTreeImmed); //�ċA
    }
}

template<class T>
void Element<T>::activateDelay(frame prm_offset_frames) {
#ifdef MY_DEBUG
    if (prm_offset_frames == 0) {
        throwCriticalException("activateDelay(0) �͖��Ӗ��ł���B���܂ł� activate() ����܂����I�I�I�B�Ӑ}���Ă܂����H name="<<Node<T>::_name<<" this="<<this);
    }
    if (prm_offset_frames >= 60*60*60) { //�P���Ԍ�
        throwCriticalException("activateDelay("<<prm_offset_frames<<") ���Ēx������񂿂Ⴄ��H�B���܂ł� activate() ����܂����I�I�I�B���̐��ɂȂ����̂Ƃ������H�B name="<<Node<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {
#ifdef MY_DEBUG
        if (_is_active_flg) {
            _TRACE_("���x����activateDelay("<<prm_offset_frames<<") ���܂������ǁA���Ɋ�����Ԃł���B�Ӑ}���Ă܂����H name="<<Node<T>::_name<<" this="<<this);
        }
#endif
        //����inactivateDelay()���s�ς݂̏ꍇ��
        //����inactivateDelay()�͖����������B
        //
        //inactivate();
        //activate();
        //�̏��Ɏ��s����ƁAactivate() ���������ŏ���
        //activate();
        //inactivate();
        //�̏��Ɏ��s����ƁAinactivate() ������
        //����activateDelay()���s�ς݂̏ꍇ�́A����w��Z�t���[���ŏ㏑������i�㏟���j�B
        //(��inactivateDelay() �ƗD��̍l�����Ⴄ���ߒ���)
        _frame_of_life_when_inactivation = 0;
        _frame_of_life_when_activation = _frame_of_life + prm_offset_frames;
    }
}

template<class T>
void Element<T>::activateWhile(frame prm_frames) {
#ifdef MY_DEBUG
    if (prm_frames == 0) {
        throwCriticalException("activateWhile(0) �͖��Ӗ��ł���B���܂ł� activate() ����܂����I�I�I�B�Ӑ}���Ă܂����H name="<<Node<T>::_name<<" this="<<this);
    }
    if (prm_frames >= 60*60*60) { //�P���Ԍ�
        throwCriticalException("activateWhile("<<prm_frames<<") ���Ēx������񂿂Ⴄ��H�B���܂ł� activate() ����܂����I���̐��ɂȂ����̂Ƃ������H�B name="<<Node<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {
        _frame_of_life_when_activation = _frame_of_life + 1;
        _frame_of_life_when_inactivation = _frame_of_life + prm_frames;
    }
}

template<class T>
void Element<T>::activateTreeDelay(frame prm_offset_frames) {
#ifdef MY_DEBUG
    if (prm_offset_frames == 0) {
        throwCriticalException("activateTreeDelay(0) �͖��Ӗ��ł���B���܂ł� activate() ����܂����I�I�I�B�Ӑ}���Ă܂����H name="<<Node<T>::_name<<" this="<<this);
    }
    if (prm_offset_frames >= 60*60*60) { //�P���Ԍ�
        throwCriticalException("activateTreeDelay("<<prm_offset_frames<<") ���Ēx������񂿂Ⴄ��H�B���܂ł� activate() ����܂����I���̐��ɂȂ����̂Ƃ������H name="<<Node<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {
        activateDelay(prm_offset_frames);
        callRecursive(&Element<T>::activateTreeDelay, prm_offset_frames); //�ċA
    }
}

template<class T>
void Element<T>::inactivate() {
    if (_can_live_flg) {
        inactivateDelay(1);
    }
}

template<class T>
void Element<T>::inactivateTree() {
    if (_can_live_flg) {
        inactivateDelay(1);
        callRecursive(&Element<T>::inactivateTree); //�ċA
    }
}

template<class T>
void Element<T>::inactivateDelay(frame prm_offset_frames) {
#ifdef MY_DEBUG
    if (prm_offset_frames == 0) {
        throwCriticalException("inactivateDelay(0) �͖��Ӗ��ł���B���܂ł� inactivate() ����܂����I�I�I�B�Ӑ}���Ă܂����H name="<<Node<T>::_name<<" this="<<this);
    }
    if (prm_offset_frames >= 60*60*60) { //�P���Ԍ�
        throwCriticalException("inactivateDelay("<<prm_offset_frames<<") ���Ēx������񂿂Ⴄ��H�B���܂ł� inactivate() ����܂����I���̐��ɂȂ����̂Ƃ������H name="<<Node<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {


        if (_frame_of_life_when_activation >= _frame_of_life + prm_offset_frames) {
            //inactive �Ɠ��t���[���A�܂��� inactive �\�������� active �\��Ȃ�΁A
            //(active�ɂ͂Ȃ�Ȃ��悤�ɂ��邽��)�����ɂ���B
            //activate();
            //inactivate();
            //�̏��Ɏ��s����ƁAinactivate() ������
            _frame_of_life_when_activation = 0;
        }

        //����inactivateDelay()���s�ς݂̏ꍇ�A����̎w�肪�A
        //��葁�� inactivate ����w��Ȃ�Ώ㏑�����邪�A
        //���x�� inactivate ����w��Ȃ�΁A�ߋ���inactivate �������D��
        if (0 < _frame_of_life_when_inactivation &&
                _frame_of_life_when_inactivation < _frame_of_life + prm_offset_frames) {
            //����w��Z�t���[���̕����x���ꍇ�͖��������B
            return;
        } else {
            //inactivate��\��
            _frame_of_life_when_inactivation = _frame_of_life + prm_offset_frames;
        }
    }
}

template<class T>
void Element<T>::inactivateTreeDelay(frame prm_offset_frames) {
#ifdef MY_DEBUG
    if (prm_offset_frames == 0) {
        throwCriticalException("inactivateTreeDelay(0) �͖��Ӗ��ł���B���܂ł� inactivate() ����܂����I�I�I�B�Ӑ}���Ă܂����H name="<<Node<T>::_name<<" this="<<this);
    }
    if (prm_offset_frames >= 60*60*60) { //�P���Ԍ�
        throwCriticalException("inactivateTreeDelay("<<prm_offset_frames<<") ���Ēx������񂿂Ⴄ��H�B���܂ł� inactivate() ����܂����I���̐��ɂȂ����̂Ƃ������H name="<<Node<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {
        inactivateDelay(prm_offset_frames);
        callRecursive(&Element<T>::inactivateTreeDelay, prm_offset_frames); //�ċA
    }
}

template<class T>
void Element<T>::inactivateImmed() {
#ifdef MY_DEBUG
    if (_frame_of_life == 0) {
        throwCriticalException("inactivateImmed() �A�N�^�[�����シ����inactivateImmed()���邱�Ƃ͖��Ӗ��ł��������Binactivate()�ŗǂ��Ȃ��ł����H name="<<Node<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {
        _is_active_flg = false;
        _frame_of_life_when_inactivation = _frame_of_life;
        updateActiveInTheTree();
    }
}

template<class T>
void Element<T>::inactivateTreeImmed() {
    if (_can_live_flg) {
        inactivateImmed();
        callRecursive(&Element<T>::inactivateTreeImmed); //�ċA
    }
}

template<class T>
void Element<T>::pauseTree() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = true;
        callRecursive(&Element<T>::pauseTree); //�ċA
    }
}

template<class T>
void Element<T>::pause() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = true;
    }
}

template<class T>
void Element<T>::unpauseTree() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = false;
        callRecursive(&Element<T>::unpauseTree); //�ċA
    }
}

template<class T>
void Element<T>::unpause() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = false;
    }
}

template<class T>
void Element<T>::end(frame prm_offset_frames) {
    if (_frame_of_life < _frame_of_life_when_end &&
                         _frame_of_life_when_end < _frame_of_life + prm_offset_frames + GGAF_END_DELAY) {
        //����end()���s�ς݂ł���A����ɍ���w��̂������� _frame_of_life_when_end �ɓ��B���邽�ߖ�������B
        return;
    }
    _frame_of_life_when_end = _frame_of_life + prm_offset_frames + GGAF_END_DELAY;
    inactivateDelay(prm_offset_frames);
    //�w��t���[�����ɂ́A�܂�inactivate���s���A+GGAF_END_DELAY �t���[���� _can_live_flg = false�ɂȂ�B
    //onEnd()�� _can_live_flg = false ������
    T* pElementTemp = Node<T>::_pChildFirst;
    while (pElementTemp) {
        pElementTemp->end(prm_offset_frames);
        if (pElementTemp->_is_last_flg) {
            break;
        } else {
            pElementTemp = pElementTemp->_pNext;
        }
    }
}

//template<class T>
//T* Element<T>::extract() {
//    if (_can_live_flg) {
//        return extract();
//    } else {
//        //_TRACE_("[Element<"<<_class_name<<">::extract()] ���x���� "<<getName()<<"�́A����ł��܂��B");
//        return extract();
//    }
//}

template<class T>
void Element<T>::clean(int prm_num_cleaning) {
    if (Node<T>::_pChildFirst == nullptr) {
        return;
    }

    T* pElementTemp = Node<T>::_pChildFirst->_pPrev;
    T* pWk;

    while (GarbageBox::_cnt_cleaned < prm_num_cleaning) {
        if (pElementTemp->_pChildFirst) {
            //�q�̎q���܂��̂��Ă���ꍇ����ɂ�����
            pElementTemp->clean(prm_num_cleaning);
            if (GarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                break;
            }
        }
        if (pElementTemp->_is_first_flg) { //�Ō�̈��
            if (pElementTemp->_pChildFirst) {
                //�q�̎q���܂��̂��Ă���ꍇ����ɂ�����
                pElementTemp->clean(prm_num_cleaning);
                if (GarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            GGAF_DELETE(pElementTemp);
            GarbageBox::_cnt_cleaned++;
            if (GarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                break;
            }
            break;
        } else {
            pWk = pElementTemp;
            if (pWk->_pChildFirst) {
                //�q�̎q���܂��̂��Ă���ꍇ����ɂ�����
                pWk->clean(prm_num_cleaning);
                if (GarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            pElementTemp = pElementTemp->_pPrev;
            GGAF_DELETE(pWk);
            GarbageBox::_cnt_cleaned++;
            if (GarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                break;
            }
        }
    }
}

template<class T>
void Element<T>::executeFuncLowerTree(void (*pFunc)(Object*, void*, void*, void*), void* prm1, void* prm2, void* prm3) {
    if (_can_live_flg && _is_active_flg) {
        pFunc(this, prm1, prm2, prm3);
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            pElementTemp->executeFuncLowerTree(pFunc, prm1, prm2, prm3);
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
void Element<T>::throwEventLowerTree(hashval prm_no, void* prm_pSource) {
    if (_can_live_flg) {
        onCatchEvent(prm_no, prm_pSource);
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            pElementTemp->throwEventLowerTree(prm_no, prm_pSource);
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
void Element<T>::throwEventUpperTree(hashval prm_no, void* prm_pSource) {
    if (_can_live_flg) {
        onCatchEvent(prm_no, prm_pSource);
        if (Node<T>::_pParent) {
            T* pElementTemp = Node<T>::_pParent;
            pElementTemp->throwEventUpperTree(prm_no, prm_pSource);
        } else {
            //�c���[�̒��_�Ȃ̂ŁA�ċA�I��
        }
    }
}

template<class T>
bool Element<T>::isDisappear() {
    if (_is_active_in_the_tree_flg == false) {
        return true;
    } else {
        return false;
    }
}

template<class T>
Element<T>::~Element() {
    GGAF_DELETE_NULLABLE(_pProg);
}

}
#endif /*GGAF_CORE_ELEMENT_H_*/