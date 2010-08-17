#ifndef GGAFELEMENT_H_
#define GGAFELEMENT_H_
namespace GgafCore {

#define GGAF_NODE GgafCore::GgafNode<T>
#define GGAF_SAYONARA_DELAY 120
/**
 * GgafNode�ɁA�l�X�ȏ�ԑJ�ڊǗ��i�^�X�N�V�X�e���j��ǉ��B .
 * ���t���[���A�_(GgafGod)�͂��̐�(GgafUniverse)�ɁA���̃��\�b�h���ŌĂяo���d�g�݂ɂȂ��Ă���B���̐�(GgafUniverse)���{template���������Ă���B<BR>
 * nextFrame() > behave() > settleBehavior() > judge() > [preDraw() > draw() > afterDraw()] > finally() <BR>
 * ��L�̓��AnextFrame() finally() �͖��t���[�����s�����B<BR>
 * behave() settleBehavior() judge() �͊�����ԃt���O(_is_active_flg)�� true�A���A�ꎞ��~�t���O(_was_paused_flg)�� false �̏ꍇ���s�����B<BR>
 * preDraw() draw() afterDraw() �́A���t���[���܂ł̎c���Ԃɗ]�T������ꍇ���s�����B<BR>
 * ���t���[���܂ł̎c���Ԃɗ]�T�������ꍇ�A�_�͂��̂R���\�b�h���X�L�b�v���邪�AMAX_SKIP_FRAME �t���[���ɂP��͎��s����B<BR>
 * ��L�� nextFrame() �` finally() �̒��ڃI�[�o�[���C�h�͔񐄏��B�I�[�o�[���C�h�p�Ɋe���\�b�h�ŃR�[���o�b�N����鏃�����z�֐�(processXxxxxx()) ��p�ӂ��Ă���B<BR>
 * initialize() �́A��L�� nextFrame() �` finally() �����ꂩ���Ăяo���O�ɃC���X�^���X���ƂɂP�񂾂��Ă΂��d�g�݂ɂȂ��Ă���B<BR>
 * �A���A�����t���O(_can_live_flg)��false�̏ꍇ�idelete�����j�́AnextFrame() �` finally() �͑S�Ď��s����Ȃ��B<BR>
 * (�����N���X����GgafFactor)
 * @version 1.00
 * @since 2008/08/21
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafElement : public GgafNode<T> {

private:

protected:

public:
    /** [r]�_�ւ̋ߓ� */
    GgafGod* _pGod;
    /** [r]initialize���s��ꂽ�ǂ����̃t���O(true=�s��ꂽ) */
    bool _was_initialize_flg;

    /** [r]�m�[�h���a��(addSub���ꂽ�j������̃t���[�������v(�A���A_was_paused_flg==true ���͉��Z���ꖳ��) */
    frame _frame_of_life;
    /** [r]�m�[�h���a��(addSub���ꂽ�j������A�U�������t���[�������v */
    frame _frame_of_behaving;
    /** [r]�m�[�h�������J�n(onActive())������̐U�������t���[�������v */
    frame _frame_of_behaving_since_onActive;
    /** [r]���΃t���[���v�Z�p */
    frame _frameEnd;
    /** [r]�m�[�h�����t���O */
    bool _is_active_flg;
    /** [r]�ꎞ��~�t���O */
    bool _was_paused_flg;
    /** [r]�m�[�h�����t���O */
    bool _can_live_flg;

    /** [r]���t���[���̃m�[�h�����t���O�A���t���[���̃t���[�����Z�� _is_active_flg �ɔ��f����� */
    bool _is_active_flg_in_next_frame;
    /** [r]���t���[���̈ꎞ��~�t���O�A���t���[���̃t���[�����Z�� _was_paused_flg �ɔ��f����� */
    bool _was_paused_flg_in_next_frame;
    /** [r]���t���[���̈ꎞ��\���t���O�A���t���[���̃t���[�����Z�� _can_live_flg �ɔ��f�����  */
    bool _can_live_flg_in_next_frame;

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
     * �|��(���c���[) .
     * �_���������Ԃɗ]�T���ł��Ƃ����ɁA�_���Ăт����B<BR>
     * �z���m�[�h�̒��Ƀm�[�h�����t���O(_can_live_flg)�� false �ɂȂ��Ă���m�[�h������� prm_num_cleaning ���� delete ����B<BR>
     * @param prm_num_cleaning �������I�u�W�F�N�g��
     */
    virtual void clean(int prm_num_cleaning);

    /**
     * �m�[�h��������(�P��) .
     * �C���X�^���X������A
     * ���ꂩ���Ăяo�����O�ɁA�ŏ��ɕK���P�񂾂��Ăяo�����B<BR>
     */
    virtual void initialize() = 0;

    /**
     * �m�[�h�̃t���[�������Z�ƁA�t���[���J�n�ɂ������Ă̂��낢��ȏ�������(���c���[) .
     * �t���O�֘A�̍X�V����ɍs�� <BR>
     * _is_active_flg_in_next_frame _was_paused_flg_in_next_frame _can_live_flg_in_next_frame ��<BR>
     * _is_active_flg _was_paused_flg _can_live_flg �ɔ��f�i�R�s�[�j����B<BR>
     * �܂��A_will_mv_first_in_next_frame_flg, _will_mv_last_in_next_frame_flg �� true �̏ꍇ�́A<BR>
     * ���ꂼ��A���m�[�h�̐擪�m�[�h�ւ̈ړ��A�����m�[�h�ւ̈ړ����������s�����B<BR>
     * ���̌�A�z���m�[�h�S�Ă� nextFrame() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� nextFrame() ���s��A���� behave() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void nextFrame();

    /**
     * �m�[�h�̃t���[�����̐U�镑������(���c���[) .
     * ���̏����ł́A�S�m�[�h���W�ړ��������s�����ƂƂ���B<BR>
     * ���s����邽�߂̃t���O�̏����́A<BR>
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �i _is_active_flg && !_was_paused_flg && _can_live_flg �j�̏ꍇ <BR>
     * behave() �� ���z�֐� processBehavior() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� behave() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�Ŗ{���\�b�h�𒼐ڌĂяo�����s��Ȃ����ƂƂ���B<BR>
     * ���ʃN���X�ł̓R�[������� processBehavior() ���I�[�o�[���C�h���ċ�̓I�ȍ��W�ړ����W�b�N����������B <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� behave() ���s��A���� settleBehavior() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void behave();

    /**
     * �񊈓����������ɐ؂�ւ�������̏���(�P��) .
     * �񊈓���Ԃ��犈����Ԃɕω������Ƃ��ɂP��R�[���o�b�N�����B<BR>
     * �Ăяo�����^�C�~���O�̓t���[�����Z����ł���B�ʏ� behave() �����O�Ɏ��s�����B<BR>
     * �K�v�ɉ����ăI�[�o�[���C�h����B<BR>
     */
    virtual void onActive() {
    }

    /**
     * �������񊈓����ɐ؂�ւ�������̏���(�P��) .
     * ������Ԃ���񊈓���Ԃɕω������Ƃ��ɂP��R�[���o�b�N�����B<BR>
     * �Ăяo�����^�C�~���O�̓t���[�����Z����ł���B�ʏ� behave() �����O�Ɏ��s�����B<BR>
     * �K�v�ɉ����ăI�[�o�[���C�h����B<BR>
     */
    virtual void onInactive() {
    }

    /**
     * �m�[�h�̃t���[�����̐U�镑�����㏈��(���c���[) .
     * ���̏����ł́A�S�m�[�h���W�ړ����������Ă��邱�Ƃ��ۏ؂��ꂽ��̏������s�����Ƃ���݌v�B<BR>
     * �X�V�������������W��񂩂�A����ɔ��������̗l�X�ȃX�e�[�^�X���̍X�V�����������ōs������ړI�Ƃ���<BR>
     * ���s����邽�߂̃t���O�̏����́Abehave()�Ɠ������A�����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g�B<BR>
     * �܂� ( _is_active_flg && !_was_paused_flg && _can_live_flg )�̏ꍇ�ł���B <BR>
     * settleBehavior()�́A���z�֐� processSettlementBehavior() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� settleBehavior() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�Ŗ{���\�b�h�𒼐ڌĂяo�����s��Ȃ����ƂƂ���B<BR>
     * ���ʃN���X�ł̓R�[������� processSettlementBehavior() ���I�[�o�[���C�h���ă��W�b�N���������邱�ƂƂ���B <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� settleBehavior() ���s��A���� judge() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void settleBehavior();


    /**
     * �m�[�h�̃t���[�����̔��菈��(���c���[) .
     * ���̏����ł́A�m�[�h�Ԃ̗l�X�Ȕ��菈�����s�����Ƃ���݌v�B<BR>
     * �S�m�[�h���W�ړ������Ɣ��Ȃ��X�e�[�^�X�ނ̍X�V�����S�Ɋ������Ă��O��Ƃ��鏈�����s����B<BR>
     * ���s����邽�߂̃t���O�̏����́Abehave()�Ɠ������A<BR>
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �܂� ( _is_active_flg && !_was_paused_flg && _can_live_flg )�̏ꍇ <BR>
     * judge() �� ���z�֐� processJudgement() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� judge() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�Ŗ{���\�b�h�𒼐ڌĂяo�����s��Ȃ����ƂƂ���B<BR>
     * ���ʃN���X�ł̓R�[������� processJudgement() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� judge() ���s��A<BR>
     * �_(GgafGod)�͂��̌�A���t���[���܂ł̎c���Ԃɗ]�T������� preDraw() ������� finally() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void judge();

    /**
     * �m�[�h�̃t���[�����̕`�掖�O����(���c���[)�i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����t���O�A�����t���O���Z�b�g�A<BR>
     * (�܂� _is_active_flg && _can_live_flg)�̏ꍇ <BR>
     * processPreDraw() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� preDraw() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * ���ʃN���X�ł̓R�[������� processPreDraw() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� preDraw() ���s��A���� draw() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void preDraw();

    /**
     * �m�[�h�̃t���[�����̕`��{����(���c���[)�i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����t���O�A�����t���O���Z�b�g�A<BR>
     * (�܂� _is_active_flg && _can_live_flg)�̏ꍇ <BR>
     * processDraw() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� draw() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * ���ʃN���X�ł̓R�[������� processDraw() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� draw() ���s��A���� afterDraw() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void draw();

    /**
     * �m�[�h�̃t���[�����̕`�掖�㏈��(���c���[)�i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����t���O�A�����t���O���Z�b�g<BR>
     * (�܂� _is_active_flg && _can_live_flg)�̏ꍇ <BR>
     * processAfterDraw() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� afterDraw() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * ���ʃN���X�ł̓R�[������� processAfterDraw() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� afterDraw() ���s��A���� finally() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void afterDraw();

    /**
     * �m�[�h�̃t���[�����̍ŏI����(���c���[) .
     * ���W�ړ������A���菈���A�`�揈�����I��������ɁA�Ō�ɍs����n���������s�����Ƃ���݌v�B<BR>
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �i_is_active_flg && !_was_paused_flg && _can_live_flg�j�̏ꍇ <BR>
     * processFinally() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� finally() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * ���ʃN���X�ł̓R�[������� processFinally() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� finally() ���s��A<BR>
     * ���t���[���܂ł̎c���Ԃɗ]�T������� clean() �����s����B<BR>
     * ���̌�� nextFrame() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void finally();

    /**
     * �m�[�h�̉����̏���(���c���[)(�t���[�����ł͂Ȃ�) .
     * �����t���O���Z�b�g�A( _is_active_flg = true )�̏ꍇ <BR>
     * ������ processHappen(int) ���R�[��������A�z���̃m�[�h�S�Ăɂ��� happen() ���ċA�I�Ɏ��s����B<BR>
     * @param   prm_no �����̔ԍ�
     */
    virtual void happen(int prm_no);

    /**
     * �t���[�����̌ʐU�镑�������������B(���[�U�[�����p�A�P��) .
     * behave() ���̏����擪�ŃR�[���o�b�N�����B<BR>
     * ���̃����o�֐������ʃN���X�ŃI�[�o�[���C�h���āA�m�[�h�ʂ̐U�镑������������������B<BR>
     * �z�肵�Ă���U�镑�������Ƃ́A��ɍ��W�v�Z�ƈړ��������ł���B<BR>
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��āAnextFrame() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     */
    virtual void processBehavior() = 0;

    /**
     * �t���[�����̌ʐU�镑�����㏈���������B(�t���[�����[�N�����p�A�P��) .
     */
    virtual void processSettlementBehavior() {}

    /**
     * �t���[�����̌ʔ��f�����������B(���[�U�[�����p�A�P��) .
     * judge() ���̏����擪�ŃR�[���o�b�N�����B<BR>
     * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʔ��f�������L�q����B<BR>
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��ĂāAprocessBehavior() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     * �{�����o�֐��̑��݈Ӑ}�Ƃ��āAprocessBehavior() �ō��W�ړ��������S�Ċ���������A
     * �{�����o�֐��œ����蔻�菈������������Ƃ������g������z�肵�Ă���B<BR>
     */
    virtual void processJudgement() = 0;

    /**
     * �m�[�h�̃t���[�����̌ʕ`�掖�O�����������B(�t���[�����[�N�����p�A�P��) .
     * preDraw() ���̏����擪�ŃR�[���o�b�N�����B �A���A�_(GgafGod)���`��X�L�b�v�����ꍇ�A�t���[�����ŌĂяo����܂���B<BR>
     * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʕ`�掖�O��������������B<BR>
     * �ʕ`�掖�O�����Ƃ́A��ɓ�����w�i�`��Ȃǂł���B<BR>
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��āAprocessJudgement() �����s�ς݂ł��邱�Ƃ��ۏ؂���B<BR>
     * ����ɁA�{�����o�֐����s��AprocessDraw()�AprocessAfterDraw() ���Ăяo����邱�Ƃ��ۏ؂����B
     */
    virtual void processPreDraw() {};

    /**
     * �m�[�h�̃t���[�����̌ʕ`��{�����������B(�t���[�����[�N�����p�^���[�U�[�����p�A�P��) .
     * draw() ���̏����擪�ŃR�[���o�b�N�����B �A���ApreDraw() �Ɠ��l�ɐ_(GgafGod)���`��X�L�b�v���ꂽ�ꍇ�́A�t���[�����ŌĂяo����܂���B<BR>
     * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʕ`��{��������������B<BR>
     * �ʕ`��{�����Ƃ͎�ɃL�����N�^��A�w�i�̕`���z�肵�Ă���B
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��āAprocessPreDraw() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     */
    virtual void processDraw() = 0;

    /**
     * �m�[�h�̃t���[�����̌ʕ\�����㏈�����L�q�B(�t���[�����[�N�����p�A�P��) .
     * afterDraw() ���̏����擪�ŃR�[���o�b�N�����B �A���ApreDraw() �Ɠ��l�ɐ_(GgafGod)���`��X�L�b�v���ꂽ�ꍇ�́A�t���[�����ŌĂяo����܂���B<BR>
     * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʕ\�����㏈������������B<BR>
     * �ʕ\�����㏈���Ƃ́A�őO�ʃ��C���[�Ŏ�������t�F�[�h�G�t�F�N�g��A��ɍőO�ʂɕ\���������\���Ȃǂł���B<BR>
     * �{�����o���R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��āAprocessDraw() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     */
    virtual void processAfterDraw() {};

    /**
     * �m�[�h�̃t���[�����̌ʏI�[�����������B(���[�U�[�����p�A�P��) .
     * finally() ���̏����擪�ŃR�[���o�b�N�����B<BR>
     * ���̃����o�֐������ʃN���X�ŃI�[�o�[���C�h���āA�m�[�h�ʂ̏I�[��������������B<BR>
     * �I�[�����Ƃ́A�t���O�Ǘ��̎��s�Ȃǂł���B<BR>
     * �z�肵�Ă���U�镑�������Ƃ́A��ɍ��W�v�Z�ƈړ������ł���B���̑��Ȃ�ł��ǂ��ł���B<BR>
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��āAprocessJudgement() �����s�ς݂� �`�揈���͏I�����Ă��邱�Ƃ�ۏ؂���B<BR>
     */
    virtual void processFinal() = 0;

    /**
     * �m�[�h�̌ʉ����̏������L�q�B(�P��)
     * happen() ���̏����擪�ŃR�[���o�b�N�����B
     * ���p�ړI�s��̔ėp�C�x���g�p�R�[���o�b�N
     * @param prm_no �����̔ԍ�
     */
    virtual void processHappen(int prm_no) = 0;

    /**
     * �_�ɉy�� .
     * @return  �Ă΂�ďo�Ă����_
     */
    virtual GgafGod* askGod() = 0;

    //==================��ԑJ�ڃ��\�b�h�S==================>
    /**
     * ������Ԃɂ���(���c���[�E�R�[���o�b�N�L��) .
     * ���m�ɂ́A���t���[�����犈����Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����Ŋ�����ԂɂȂ鎖�ɂȂ�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� activateTree() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͊�����Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * ���m�[�h�� processBehavior() �� ���g�� activateTree() ���Ăяo���R�[�h�������Ă��A�^�X�N�V�X�e���̎d�g�ݏ�A<BR>
     * processBehavior()�͊�����Ԃɂ̂ݎ��s�����̂ŁA���s����邱�Ƃ������Ӗ��������B<BR>
     * ���m�[�h�֎��s������AprocessFinal() �Ȃǂł̎g�p��z��B<BR>
     * <B>[�⑫]</B>�m�[�h��������́A������ԂƂȂ��Ă���B<BR>
     */
    virtual void activateTree();

    /**
     * ������Ԃɂ���(�P�́E�R�[���o�b�N�L��) .
     * ���m�[�h�������t���[�����犈����Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͊�����Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     */
    virtual void activate();

    /**
     * ������Ԃɂ���(�P�́E�R�[���o�b�N�L��).
     * N�t���[����� activate() �����s����邱�Ƃ�\�񂷂�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� activateAfter(UINT32) �����s�����B<BR>
     * activateAfter(1) �́Aactivate() �Ɠ����Ӗ��ɂȂ�܂��B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͊�����Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * @param prm_frame_offset �x���t���[����(1�`)
     */
    virtual void activateAfter(frame prm_frame_offset);


    virtual void activateTreeAfter(frame prm_frame_offset);


    /**
     * ������Ԃɂ���(�P�́E�����E�R�[���o�b�N����) .
     * ���m�[�h�ɂ��āA�����Ɋ�����Ԃɂ���B�ʏ�A�������ȊO�Ŗ{���\�b�h�̎g�p�͔񐄏��B<BR>
     * onActive() �R�[���o�b�N�͎��s����Ȃ��B<BR>
     * �����ɏ�Ԃ��ω����邽�߁A�ȉ��̓_�𗯈ӂ��āA�g�p����ۂ͒��ӂ��K�v�ł���B<BR>
     * �w����t���[�����x�̎c��̖������̃m�[�h�ɑ΂��ėL���ɂȂ��Ă��܂��B�܂�A<BR>
     * �w����t���[�����x�ł����Ă��A���ɏ������ꂽ�m�[�h�Ƃ͈قȂ��ԂɂȂ�\�����傫���A<BR>
     * ���m�[�h�̃��W�b�N���A�u���̃m�[�h��������ԂȂ�΁E�E�E�v���A���̏�ԁi�t���O�j�ɂ�菈�����򂵂Ă����ꍇ�A<BR>
     * ����t���[�����̏������ʂ̐�����������鋰�ꂪ����B<BR>
     * ���m�[�h�̉e���A�c���[�\����ǂ��l���Ďg�p���邱�ƁB<BR>
     */
    virtual void activateImmediately();

    /**
     * ������Ԃɂ���(���c���[�E�����E�R�[���o�b�N����)
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� activateImmediately() �����s�����B<BR>
     * activateImmediately() �̐�����v�Q�ƁB<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    virtual void activateTreeImmediately();
    //===================
    /**
     * �񊈓���Ԃɂ���(���c���[�E�R�[���o�b�N�L��) .
     * ���m�ɂ́A���t���[������񊈓���Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����Ŕ񊈓���ԂɂȂ鎖�ɂȂ�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� inactivate() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͔񊈓���Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     */
    virtual void inactivateTree();

    /**
     * �񊈓���Ԃɂ���(�P�́E�R�[���o�b�N�L��) .
     * ���m�[�h�������t���[������񊈓���Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͔񊈓���Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     */
    virtual void inactivate();

    /**
     * �񊈓��\�񂷂�(���c���[�E�R�[���o�b�N�L��) .
     * N�t���[����� inactivateTree() �����s����邱�Ƃ�\�񂷂�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� inactivateAfter(UINT32) �����s�����B<BR>
     * inactivateAfter(1) �́AinactivateTree() �Ɠ����Ӗ��ɂȂ�܂��B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͔񊈓���Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * @param prm_frame_offset �x���t���[����(1�`)
     */
    virtual void inactivateAfter(frame prm_frame_offset);



    virtual void inactivateTreeAfter(frame prm_frame_offset);

    /**
     * �񊈓���Ԃɂ���(�P�́E�����E�R�[���o�b�N����)  .
     * ���m�[�h�ɂ��āA�����ɔ񊈓���Ԃɂ���B�ʏ�A�{���\�b�h�̎g�p�͔񐄏��B<BR>
     * onInactive() �R�[���o�b�N�͎��s����Ȃ��B<BR>
     * �����ɏ�Ԃ��ω����邽�߁A�ȉ��̓_�𗯈ӂ��āA�g�p����ۂ͒��ӂ��K�v�ł���B<BR>
     * �w����t���[�����x�̎c��̖������̃m�[�h�ɑ΂��Ă̂ݗL���ƂȂ�B�܂�A<BR>
     * �w����t���[�����x�ł����Ă��A���ɏ������ꂽ�m�[�h�Ƃ͈قȂ��ԂɂȂ�\�����傫���A<BR>
     * ���m�[�h�̃��W�b�N���A�u���̃m�[�h���񊈓���ԂȂ�΁E�E�E�v���A���̏�ԁi�t���O�j�ɂ�菈�����򂵂Ă����ꍇ�A<BR>
     * ����t���[�����̏������ʂ̐�����������鋰�ꂪ����B<BR>
     * ���m�[�h�̉e���A�c���[�\����ǂ��l���Ďg�p���邱�ƁB<BR>
     */
    virtual void inactivateImmediately();

    /**
     * �񊈓���Ԃɂ���(���c���[�E�����E�R�[���o�b�N����)  .
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� inactivateImmediately() �����s�����B<BR>
     * inactivateImmediately() �̐�����v�Q�ƁB<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    virtual void inactivateTreeImmediately();

    //===================
    /**
     * �ꎞ��~�ɂ���(���c���[) .
     * ���m�ɂ́A���t���[������ꎞ��~�ɂ���\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����ňꎞ��~�ɂȂ鎖�ɂȂ�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� pause() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͈ꎞ��~�̕ω��͖�����ѐ��͕ۂ����B<BR>
     */
    void pauseTree();

    /**
     * �ꎞ��~�ɂ���(�P��) .
     * ���m�[�h�������t���[������ꎞ��~�ɂ���\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͈ꎞ��~�̕ω��͖�����ѐ��͕ۂ����B<BR>
     */
    void pause();

    /**
     * �ꎞ��~��Ԃɂ���(�P�́E����) .
     * ���m�[�h�ɂ��āA�����Ɉꎞ��~��ԁi _was_paused_flg = true �j�ɂ���B�ʏ�A�{���\�b�h�̎g�p�͔񐄏��B<BR>
     * �����ɏ�Ԃ��ω����邽�߁A�ȉ��̓_�𗯈ӂ��Ďg�p����ۂ͒��ӂ��K�v�ł���B<BR>
     * �ω������V���ȃt���O��Ԃ́A�w����t���[�����x�̎c��̖������̃m�[�h�ɑ΂��Ă̂ݗL���ƂȂ�B�܂�A<BR>
     * �w����t���[�����x�ł����Ă��A���ɏ������ꂽ�m�[�h�Ƃ͈قȂ��ԂɂȂ�\��������A<BR>
     * ���m�[�h�̃��W�b�N���A�u���̃m�[�h���ꎞ��~��ԂȂ�΁E�E�E�v���A���̏�ԁi�t���O�j�ɂ�菈�����򂵂Ă����ꍇ�A<BR>
     * ����t���[�����̏������ʂ̐�����������鋰�ꂪ����B<BR>
     * ���m�[�h�̉e���A�c���[�\����ǂ��l���Ďg�p���邱�ƁB<BR>
     */
    void pauseImmediately();

    /**
     * �ꎞ��~��Ԃɂ���(���c���[�E����) .
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� pauseImmediately() �����s�����B<BR>
     * pauseImmediately() �̐�����v�Q�ƁB<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void pauseTreeImmediately();

    //===================
    /**
     * �ꎞ��~��Ԃ���������(���c���[) .
     * ���m�ɂ́A���t���[������ꎞ��~��Ԃ���������\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����ňꎞ��~��Ԃ���������鎖�ɂȂ�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� unpause() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͈ꎞ��~��Ԃ������̕ω��͖�����ѐ��͕ۂ����B<BR>
     */
    void unpauseTree();
    /**
     * �ꎞ��~��Ԃ���������(�P��) .
     * ���m�[�h�������t���[������ꎞ��~��Ԃ������ɂ���\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͈ꎞ��~��Ԃ������̕ω��͖�����ѐ��͕ۂ����B<BR>
     */
    void unpause();

    /**
     * �ꎞ��~��Ԃ���������(���c���[�E����) .
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� unpauseImmediately() �����s�����B<BR>
     * unpauseImmediately() �̐�����v�Q�ƁB<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void unpauseTreeImmediately();

    /**
     * �ꎞ��~��Ԃ���������(�P�́E����) .
     * ���m�[�h�ɂ��āA�����Ɉꎞ��~���Ă��Ȃ���ԁi _was_paused_flg = false �j�ɂ���B�ʏ�A�{���\�b�h�̎g�p�͔񐄏��B<BR>
     * �����ɏ�Ԃ��ω����邽�߁A�ȉ��̓_�𗯈ӂ��Ďg�p����ۂ͒��ӂ��K�v�ł���B<BR>
     * �ω������V���ȃt���O��Ԃ́A�w����t���[�����x�̎c��̖������̃m�[�h�ɑ΂��Ă̂ݗL���ƂȂ�B�܂�A<BR>
     * �w����t���[�����x�ł����Ă��A���ɏ������ꂽ�m�[�h�Ƃ͈قȂ��ԂɂȂ�\��������A<BR>
     * ���m�[�h�̃��W�b�N���A�u���̃m�[�h���ꎞ��~��ԂȂ�΁E�E�E�v���A���̏�ԁi�t���O�j�ɂ�菈�����򂵂Ă����ꍇ�A<BR>
     * ����t���[�����̏������ʂ̐�����������鋰�ꂪ����B<BR>
     * ���m�[�h�̉e���A�c���[�\����ǂ��l���Ďg�p���邱�ƁB<BR>
     */
    void unpauseImmediately();
    //===================

    /**
     * �I�����܂��B(���c���[) .
     * ���m�[�h�������̃t���[����Ɂu�����I���v��Ԃɂ��邱�Ƃ�錾����B�i�I���t���O�𗧂Ă�j <BR>
     * ���c���[�m�[�h�S�ē��A��ŁA�I��(end())�����m�点���͂��B<br>
     * �e�m�[�h���I������΁A�q�m�[�h���I��������𓾂Ȃ�����ł���B<BR>
     * �I���t���O�͈�x���Ă�ƌ��ɂ��ǂ��܂���B�ȍ~ end() ���d�˂ČĂяo���Ă��������܂��B<BR>
     * �����̗P�\�t���[����ɐ����I���Ƃ���B<BR>
     * �u�����I���v�Ƃ͋�̓I�ɂ́A�U�镑���t���O(_is_active_flg)�A�����t���O(_can_live_flg) ���A
     * ���t���[������A���Z�b�g����\��t���O�𗧂Ă邱�Ǝ��ł���B<BR>
     * _can_live_flg ���A���Z�b�g����邱�Ƃɂ��A�S�~��(GgafGarbageBox) �ɏ������邱�ƂɂȂ�B<BR>
     * �����Đ_(GgafGod)�����ɗ]�T�̂��鎞�����v�炢 clean() ���\�b�h�ɂ��A<BR>
     * GgafDisusedActor �z���m�[�h�� delete ���邱�ƂƂȂ�B<BR>
     * ���������āA�{�����o�֐������s���Ĉ����̗P�\�t���[����ɂȂ��Ă��A�܂�delete�͍s�Ȃ�ꂸ�A<BR>
     * GgafDisusedActor �z���Ɉڂ邾���B�i�^�X�N����͏��O����Ă���j�B<BR>
     * ���t���[���ȍ~�ł������ɂ� delete �����Ƃ͌���Ȃ��B<BR>
     * �C���X�^���X�������ɉ������Ȃ����Ƃɒ��ӂ���I�i�����I�ȃo�O�𐶂݂₷���j�B<BR>
     * @param prm_frame_offset �����I���P�\�t���[��(1�`)
     */
    void end(frame prm_frame_offset = 1);

    /**
     * ���c���[�m�[�h���ŏI�m�[�h�Ɉړ�����(�P��) .
     * ���t���[���̐擪����(nextFrame())�Ŏ��c���[�m�[�h���Z��m�[�h�O���[�v�̍ŏI�ɃV�t�g����B<BR>
     * <B>[����]</B>�����ɏ��J�菈�������s�����킯�ł͂Ȃ��B<BR>
     */
    void moveLast() {
        _will_mv_last_in_next_frame_flg = true;
    }

    /**
     * ���c���[�m�[�h��擪�m�[�h�Ɉړ�����(�P��) .
     * ���t���[���̐擪����(nextFrame())�Ŏ��c���[�m�[�h���Z��m�[�h�O���[�v�̐擪�ɃV�t�g����B<BR>
     * <B>[����]</B>�����ɏ��J�菈�������s�����킯�ł͂Ȃ��B<BR>
     */
    void moveFirst() {
        _will_mv_first_in_next_frame_flg = true;
    }

    /**
     * �����c���[����Ɨ�����(�P��)
     * extract() �̃��b�p�[�ŁA�����m�F�̃`�F�b�N�t���B�ʏ�͂�������g�p����B
     * @return  T* �E�ނ��Ɨ��������m�[�h�̃|�C���^
     */
    virtual T* extract() override;


    /**
     * �񊈓����犈���ɐ؂�ւ�������ǂ��� .
     * �������AonActive() �I�[�o�[���C�h�Ŏ������ꍇ�́A���̕�����������L�q�ł���͂��B<BR>
     * ���̃m�[�h�̏�ԕω���m�肽�����̂��߂ɁA�{���\�b�h�����������B<BR>
     * @return  bool true:�؂�ւ�����^false:�؂�ւ���Ă��Ȃ�
     */
    bool onChangeToActive();

    /**
     * ���������~�ɐ؂�ւ�������ǂ��� .
     * �������AonInactive() �I�[�o�[���C�h�Ŏ������ꍇ�́A���̕�����������L�q�ł���͂��B<BR>
     * ���̃m�[�h�̏�ԕω���m�肽�����̂��߂ɁA�{���\�b�h�����������B<BR>
     * @return  bool true:�؂�ւ�����^false:�؂�ւ���Ă��Ȃ�
     */
    bool onChangeToInactive();

    /**
     * �����\�����ׂ�
     * @return  bool true:�����\�^false:�����s��
     */
    bool canLive() {
        return _can_live_flg;
    }

    /**
     * �����������ׂ�
     * @return  bool true:�������^false:�񊈓���
     */
    bool isActive();

    /**
     * �U�镑���\�����ׂ�i���ꎞ��~����Ă��Ȃ����j
     * @return  bool true:�U�镑���\�i�������ňꎞ��~�ł͖����j�^false:�U�镑���s��
     */
    bool canBehave();

    /**
     */
    bool wasPause();

    /**
     * �I���錾�������ǂ���
     * @return
     */
    bool wasDeclaredEnd();

    /**
     * �U�镑����Ԃɉ��Z�����t���[�������擾���� .
     * �����Z�b�g���Ȃ��ꍇ�A���̂悤�Ȓl��Ԃ��B<BR>
     * 1 Frame �` ����̒l�ɂȂ�B0 Frame��Ԃ͊�{���݂��Ȃ��B�A����O�I��<BR>
     * �������R���X�g���N�^���A����сA�ŏ��� initialize() ���ł� 0 Frame ��Ԃ��B<BR>
     * ������s�� onActive()�AprocessBehavior()�AprocessJudgement() ���̒��� 1 �ɂȂ��Ă���B<BR>
     * �ȍ~�A�U�镑���Ԏ��Ƀt���[�����Z�����B<BR>
     * �u�U�镑����ԁv�Ƃ́AcanBehave() == true �̏����������̎����Ӗ�����B<BR>
     * @return �U�镑���t���[�������v
     */
    UINT32 getBehaveingFrame();

    /**
     * onActive()����̐U�镑����Ԃɉ��Z�����t���[�������擾���� .
     * �ėp�I�u�W�F�N�g�ȂǁA��x�������Ďg���܂킷(delete���Ȃ�)�ꍇ�A<BR>
     * �������� inactivate() �A �o���� activate() ���J��Ԃ����Ƃ�z��B<BR>
     * getBehaveingFrame() �Ɠ����^�C�~���O�ŉ��Z����邪�AonActive()�Ń��Z�b�g�����B<BR>
     * @return onActive()����̐U�镑���t���[����
     */
    UINT32 getActivePartFrame();


    /**
     * ���Όo�ߐU�镑���t���[���̔���B
     * ���O�� relativeFrame(int) ���s���i���ʂ�true/false�Ɋւ�炸�j�̃t���[��������̌o�߃t���[�����ɒB���������肷��B
     * ����Ăяo���́AgetBehaveingFrame() == �O����̑��΃t���[�����ƂȂ邽�߁A�P�x�͋�Ăяo�����s���i�Ȃ�Ƃ��������j���ɂȂ邩������Ȃ��B
     * ���ӁF����q���������ɂ��ArelativeFrame(int) ���Ăяo�����񐔂��ω�����ꍇ�A���Όo�߃t���[�����ω�����B
     * @param   prm_frameEnd    ���ΐU�镑���t���[����
     * @return  bool    true:�o�߃t���[�����ɒB����/false:�B���Ă��Ȃ�
     */
    bool relativeFrame(frame prm_frameEnd);

};

///////////////////////////////////////////////////////////////// ��������͎�����

template<class T>
GgafElement<T>::GgafElement(const char* prm_name) : GgafCore::GgafNode<T>(prm_name),
_pGod(NULL),
_was_initialize_flg(false),
_frame_of_life(0),
_frame_of_behaving(0),
_frame_of_behaving_since_onActive(0),
_frameEnd(0),
_is_active_flg(true),
_was_paused_flg(false),
_can_live_flg(true),
_is_active_flg_in_next_frame(true),
_was_paused_flg_in_next_frame(false),
_can_live_flg_in_next_frame(true),
_will_end_after_flg(false),
_frame_of_life_when_end(MAXDWORD),
_will_activate_after_flg(false),
_frame_of_life_when_activation(0),
_will_inactivate_after_flg(false),
_frame_of_life_when_inactivation(0),
_on_change_to_active_flg(false),
_on_change_to_inactive_flg(false),
_will_mv_first_in_next_frame_flg(false),
_will_mv_last_in_next_frame_flg(false)
{
}

template<class T>
void GgafElement<T>::nextFrame() {
    TRACE("GgafElement::nextFrame BEGIN _frame_of_behaving=" << _frame_of_behaving << " name=" << GgafNode<T>::_name << " class="
            << GgafNode<T>::_class_name);
    _was_paused_flg  = _was_paused_flg_in_next_frame;
    if (_was_paused_flg) {
        return;
    }

    //�I���̎���
    if (_will_end_after_flg && _frame_of_life_when_end == _frame_of_life+1) {
        _is_active_flg_in_next_frame = false;
        _can_live_flg_in_next_frame = false;
    }

    //moveLast�\��
    if (_will_mv_last_in_next_frame_flg) {
        _will_mv_last_in_next_frame_flg = false;
        GGAF_NODE::moveLast();
        return;
        //��return���鎖�͏d�v�B
        //moveLast�𑦎��ɍs���A_frame_of_life�����Z���Ȃ��B
        //����� _frame_of_life���Z���moveLast���Ă��܂��ƁA2�t���[�������ɂȂ��Ă��܂����߁B
        //nextFrame() �ȍ~���̃m�[�h�́A�����ɉ񂳂�Ă��邽�߁A
        //���t���[����behave() �` finnary()�͂����ƂP����s�����B
    }


    if(_was_initialize_flg == false) {
        initialize();
        _was_initialize_flg = true;
    }

    _frame_of_life++;
    if (_can_live_flg) {
        if (_will_activate_after_flg) {
            //�x��activate����
            if (_frame_of_life >= _frame_of_life_when_activation) {
                activate();
                _frame_of_life_when_activation = 0;
                _will_activate_after_flg = false;
            }
        }

        if (_will_inactivate_after_flg) {
            //�x��inactivate����
            if (_frame_of_life == _frame_of_life_when_inactivation) {
                inactivate();
                _frame_of_life_when_inactivation = 0;
                _will_inactivate_after_flg = false;
            }
        }
        if (_is_active_flg) {
            _frame_of_behaving++;
            _frame_of_behaving_since_onActive++;
        }
    }

    _on_change_to_active_flg = false;
    _on_change_to_inactive_flg = false;
    if (_is_active_flg && _is_active_flg_in_next_frame == false) {
        _on_change_to_inactive_flg = true;
        onInactive(); //�R�[���o�b�N
    }
    //�����A�񊈓��̏�ԕω���
    if (_is_active_flg == false && _is_active_flg_in_next_frame) {
        _on_change_to_active_flg = true;
        _frame_of_behaving_since_onActive = 0;
        onActive(); //�R�[���o�b�N
    } else if (_is_active_flg && _frame_of_life == 1) {
        //���܂�Ă��̂܂܂Ȃ�΁A�����Ȃ��񂾂�onActive()�B
        _on_change_to_active_flg = true;
        _frame_of_behaving_since_onActive = 0;
        onActive(); //�R�[���o�b�N
    }

    //�t���O�����𔽉f
    _is_active_flg   = _is_active_flg_in_next_frame;
    _can_live_flg    = _can_live_flg_in_next_frame;

    if (GGAF_NODE::_pSubFirst != NULL) {
        T* pElementTemp = GGAF_NODE::_pSubFirst;
        while(true) {
            if (pElementTemp->_is_last_flg) {
                pElementTemp->nextFrame();
                if (pElementTemp->_can_live_flg == false) {
                    GgafFactory::_pGarbageBox->add(pElementTemp); //�S�~����
                }
                break;
            } else {
                pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                pElementTemp->GGAF_NODE::_pPrev->nextFrame();
                if (pElementTemp->GGAF_NODE::_pPrev->_can_live_flg == false) {
                    GgafFactory::_pGarbageBox->add(pElementTemp->GGAF_NODE::_pPrev); //�S�~����
                }
            }
        }
    }

    if (_will_mv_first_in_next_frame_flg) {
        _will_mv_first_in_next_frame_flg = false;
        GGAF_NODE::moveFirst();
        //moveFirst����ԍŌ�ɂ��邱�Ƃ͏d�v�B
        //����� �c���[�̑S�m�[�h��nextFrame()���s����ۂɁA2����s������邽�߁B
    }

    TRACE("GgafElement::nextFrame END _frame_of_behaving="<<_frame_of_behaving<<" name="<<GgafNode<T>::_name<<" class="<<GgafNode<T>::_class_name);
}

template<class T>
void GgafElement<T>::behave() {
//    if(_was_initialize_flg == false) {
//        initialize();
//        _was_initialize_flg = true;
//    }

    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processBehavior();    //���[�U�[�����p
        }
        if (GGAF_NODE::_pSubFirst != NULL) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->behave();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::settleBehavior() {
//    if(_was_initialize_flg == false) {
//        initialize();
//        _was_initialize_flg = true;
//    }

    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processSettlementBehavior(); //�t���[�����[�N�p
        }
        if (GGAF_NODE::_pSubFirst != NULL) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->settleBehavior();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}


template<class T>
void GgafElement<T>::judge() {
//    if(_was_initialize_flg == false) {
//        initialize();
//        _was_initialize_flg = true;
//    }

    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processJudgement();    //���[�U�[�����p
        }
        if (GGAF_NODE::_pSubFirst != NULL) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->judge();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::preDraw() {
//    if(_was_initialize_flg == false) {
//        initialize();
//        _was_initialize_flg = true;
//    }

    if (_is_active_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processPreDraw();
        }
        if (GGAF_NODE::_pSubFirst != NULL) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->preDraw();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::draw() {
    if (_is_active_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processDraw();
        }
        if (GGAF_NODE::_pSubFirst != NULL) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->draw();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::afterDraw() {
    if (_is_active_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processAfterDraw();
        }
        if (GGAF_NODE::_pSubFirst != NULL) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->afterDraw();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::happen(int prm_no) {
//    if(_was_initialize_flg == false) {
//        initialize();
//        _was_initialize_flg = true;
//    }

    if (_can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processHappen(prm_no);
        }
        if (GGAF_NODE::_pSubFirst != NULL) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->happen(prm_no);
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::finally() {
//    if(_was_initialize_flg == false) {
//        initialize();
//        _was_initialize_flg = true;
//    }

    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processFinal();
        }
        if (GGAF_NODE::_pSubFirst != NULL) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->finally();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::activate() {
    if (_can_live_flg) {
        _is_active_flg_in_next_frame = true;
    }
}

template<class T>
void GgafElement<T>::activateTree() {
    if (_can_live_flg) {
        _is_active_flg_in_next_frame = true;
        if (GGAF_NODE::_pSubFirst != NULL) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->activateTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::activateImmediately() {
    if (_can_live_flg) {
        _is_active_flg = true;
        _is_active_flg_in_next_frame = true;
    }
}

template<class T>
void GgafElement<T>::activateTreeImmediately() {
    if (_can_live_flg) {
        _is_active_flg = true;
        _is_active_flg_in_next_frame = true;
        if (GGAF_NODE::_pSubFirst != NULL) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->activateTreeImmediately();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::activateAfter(frame prm_frame_offset) {
    if (_can_live_flg) {
        _will_activate_after_flg = true;
        _frame_of_life_when_activation = _frame_of_life + prm_frame_offset;
    }
}

template<class T>
void GgafElement<T>::activateTreeAfter(frame prm_frame_offset) {
    if (_can_live_flg) {
        _will_activate_after_flg = true;
        _frame_of_life_when_activation = _frame_of_life + prm_frame_offset;
        if (GGAF_NODE::_pSubFirst != NULL) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->activateTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::inactivate() {
    if (_can_live_flg) {
        if (_is_active_flg) {
            _is_active_flg_in_next_frame = false;
        }
    }
}

template<class T>
void GgafElement<T>::inactivateTree() {
    if (_can_live_flg) {
        if (_is_active_flg) {
            _is_active_flg_in_next_frame = false;
        }
        if (GGAF_NODE::_pSubFirst != NULL) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->inactivateTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::inactivateAfter(frame prm_frame_offset) {
    if (_can_live_flg) {
        if (_is_active_flg) {
            _will_inactivate_after_flg = true;
            _frame_of_life_when_inactivation = _frame_of_life + prm_frame_offset;
        }
    }
}

template<class T>
void GgafElement<T>::inactivateTreeAfter(frame prm_frame_offset) {
    if (_can_live_flg) {
        if (_is_active_flg) {
            _will_inactivate_after_flg = true;
            _frame_of_life_when_inactivation = _frame_of_life + prm_frame_offset;
        }
        if (GGAF_NODE::_pSubFirst != NULL) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->inactivateTreeAfter(prm_frame_offset);
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::inactivateImmediately() {
    if (_can_live_flg) {
        if (_is_active_flg) {
            _is_active_flg = false;
            _is_active_flg_in_next_frame = false;
        }
    }
}

template<class T>
void GgafElement<T>::inactivateTreeImmediately() {
    if (_can_live_flg) {
        if (_is_active_flg) {
            _is_active_flg = false;
            _is_active_flg_in_next_frame = false;
        }
        if (GGAF_NODE::_pSubFirst != NULL) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->inactivateTreeImmediately();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::pauseTree() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = true;
        //_is_active_flg = false;
        if (GGAF_NODE::_pSubFirst != NULL) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->pauseTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::pause() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = true;
    }
}

template<class T>
void GgafElement<T>::pauseTreeImmediately() {
    if (_can_live_flg) {
        _was_paused_flg = true;
        _was_paused_flg_in_next_frame = true;
        if (GGAF_NODE::_pSubFirst != NULL) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->pauseTreeImmediately();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::pauseImmediately() {
    if (_can_live_flg) {
        _was_paused_flg = true;
        _was_paused_flg_in_next_frame = true;
    }
}

template<class T>
void GgafElement<T>::unpauseTree() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = false;
        if (GGAF_NODE::_pSubFirst != NULL) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->unpauseTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::unpause() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = false;
    }
}

template<class T>
void GgafElement<T>::unpauseTreeImmediately() {
    if (_can_live_flg) {
        _was_paused_flg = false;
        _was_paused_flg_in_next_frame = false;
        if (GGAF_NODE::_pSubFirst != NULL) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->unpauseTreeImmediately();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::unpauseImmediately() {
    if (_can_live_flg) {
        _was_paused_flg = false;
        _was_paused_flg_in_next_frame = false;
    }
}
template<class T>
void GgafElement<T>::end(frame prm_frame_offset) {
    if (_will_end_after_flg == false) { //��x�I��������Q�x�Ǝ������܂���B
        _will_end_after_flg = true;
        inactivateAfter(prm_frame_offset);
        _frame_of_life_when_end = _frame_of_life + prm_frame_offset + GGAF_SAYONARA_DELAY;
        if (GGAF_NODE::_pSubFirst != NULL) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->end(prm_frame_offset);
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}


template<class T>
bool GgafElement<T>::isActive() {
    if (_can_live_flg && _is_active_flg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::onChangeToActive() {
    if (_can_live_flg && _on_change_to_active_flg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::onChangeToInactive() {
    if (_can_live_flg && _on_change_to_inactive_flg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::canBehave() {
    if (_can_live_flg && _is_active_flg && !_was_paused_flg) {
        return true;
    } else {
        return false;
    }
}


template<class T>
bool GgafElement<T>::wasPause() {
    if (_was_paused_flg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::wasDeclaredEnd() {
    if (_will_end_after_flg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::relativeFrame(frame prm_frameEnd) {
    _frameEnd += prm_frameEnd;
    if (_frame_of_behaving == _frameEnd) {
        return true;
    } else {
        return false;
    }
}


template<class T>
T* GgafElement<T>::extract() {
    if (_can_live_flg) {
        return GGAF_NODE::extract();
    } else {
        //_TRACE_("[GgafElement<"<<GGAF_NODE::_class_name<<">::extract()] ���x���� "<<GGAF_NODE::getName()<<"�́A����ł��܂��B");
        return GGAF_NODE::extract();
    }
}

template<class T>
void GgafElement<T>::clean(int prm_num_cleaning) {
    if (GGAF_NODE::_pSubFirst == NULL) {
        return;
    }

    T* pElementTemp = GGAF_NODE::_pSubFirst->_pPrev;
    T* pWk;

    while(GgafFactory::_cnt_cleaned < prm_num_cleaning) {

        if (pElementTemp->_pSubFirst) {
            //�q�̎q���܂��̂��Ă���ꍇ����ɂ�����
            pElementTemp->clean(prm_num_cleaning);
            if (GgafFactory::_cnt_cleaned >= prm_num_cleaning) {
                break;
            }
        }

        if (pElementTemp->_is_first_flg) { //�Ō�̈��
            if (pElementTemp->_pSubFirst) {
                //�q�̎q���܂��̂��Ă���ꍇ����ɂ�����
                pElementTemp->clean(prm_num_cleaning);
                if (GgafFactory::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            if (pElementTemp->_can_live_flg == false) {
                DELETE_IMPOSSIBLE_NULL(pElementTemp);
                GgafFactory::_cnt_cleaned++;
            }
            break;
        } else {
            pWk = pElementTemp;
            if (pWk->_pSubFirst) {
                //�q�̎q���܂��̂��Ă���ꍇ����ɂ�����
                pWk->clean(prm_num_cleaning);
                if (GgafFactory::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            pElementTemp = pElementTemp->_pPrev;
            if (pWk->_can_live_flg == false) {
                DELETE_IMPOSSIBLE_NULL(pWk);
                GgafFactory::_cnt_cleaned++;
            }
        }
    }
}


template<class T>
UINT32 GgafElement<T>::getBehaveingFrame() {
   return _frame_of_behaving;
}

template<class T>
UINT32 GgafElement<T>::getActivePartFrame() {
   return _frame_of_behaving_since_onActive;
}

template<class T>
GgafElement<T>::~GgafElement() {
}

}
#endif /*GGAFELEMENT_H_*/
