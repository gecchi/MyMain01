#ifndef GGAFELEMENT_H_
#define GGAFELEMENT_H_
namespace GgafCore {

#define SUPER GgafCore::GgafNode<T>

/**
 * GgafNode�ɁA�^�X�N�V�X�e���y�їl�X�ȏ�ԊǗ��i�t���O�Ǘ��j��ǉ��B .
 * ���t���[���A��_(GgafGod)�͂��̐�(GgafUniverse)�ɁA���̃��\�b�h���ŌĂяo���d�g�݂ɂȂ��Ă���B���̐�(GgafUniverse)���{template���������Ă���B<BR>
 * nextFrame() > behave() > judge() > [preDraw() > draw() > afterDraw()] > finally() <BR>
 * ��L�̓��AnextFrame() finally() �͖��t���[�����s�����B<BR>
 * behave() judge() �͊�����ԃt���O(_is_active_flg)�� true�A���A�ꎞ��~�t���O(_was_paused_flg)�� false �̏ꍇ���s�����B<BR>
 * preDraw() draw() afterDraw() �́A���t���[���܂ł̎c���Ԃɗ]�T������ꍇ<BR>
 * ���s�����B���t���[���܂ł̎c���Ԃɗ]�T�������ꍇ�A�_�͂��̂R���\�b�h���X�L�b�v���邪�AMAX_SKIP_FRAME �t���[���ɂP��͎��s����B<BR>
 * ��L�� nextFrame() �` finally() �̃I�[�o�[���C�h�͔񐄏��B�I�[�o�[���C�h�p�ɏ������z(processXxxxxx()) ��p�ӂ��Ă���B<BR>
 * initialize() �́A��L�� nextFrame() �` finally() �����ꂩ���Ăяo���O�ɃC���X�^���X���ƂɂP�񂾂��Ă΂��d�g�݂ɂȂ��Ă���B<BR>
 * �A���A�����t���O(_can_live_flg)��false�̏ꍇ�idelete�����j�́AnextFrame() �` finally() �͑S�Ď��s����Ȃ��B<BR>
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafElement : public GgafNode<T> {

private:

protected:

public:
    /** �_�ւ̋ߓ� */
    GgafGod* _pGod;
    /** initialize���s��ꂽ�ǂ����̃t���O(true=�s��ꂽ) */
    bool _was_initialize_flg;

    /** �]�� */
    DWORD _dwGodFrame_when_goodbye;
    /** ���΃t���[���v�Z�p */
    DWORD _frame_relative;
    /** �m�[�h�����t���O */
    bool _is_active_flg;
    /** �ꎞ��~�t���O */
    bool _was_paused_flg;
    /** �m�[�h�����t���O */
    bool _can_live_flg;

    /** ���t���[���̃m�[�h�����t���O�A���t���[���̃t���[�����Z�� _is_active_flg �ɔ��f����� */
    bool _is_active_flg_in_next_frame;
    /** ���t���[���̈ꎞ��~�t���O�A���t���[���̃t���[�����Z�� _was_paused_flg �ɔ��f����� */
    bool _was_paused_flg_in_next_frame;
    /** ���t���[���̈ꎞ��\���t���O�A���t���[���̃t���[�����Z�� _can_live_flg �ɔ��f�����  */
    bool _can_live_flg_in_next_frame;

    /** �擪�m�[�h�Ɉړ��\��t���O�A���t���[���̃t���[�����Z���ɁA���m�[�h���擪�m�[�h�Ɉړ����� */
    bool _will_move_first_in_next_frame_flg;
    /** �����m�[�h�Ɉړ��\��t���O�A���t���[���̃t���[�����Z���ɁA���m�[�h�������m�[�h�Ɉړ����� */
    bool _will_move_last_in_next_frame_flg;

    /** ���ƂŊ����\��t���O */
    bool _will_activate_after_a_few_frames_flg;
    /** ���ƂŊ����܂ł̎c�t���[�����i�_�t���[���ƈ�v�����犈���j */
    DWORD _frame_of_activation;

    /** ���ƂŔ񊈓��\��t���O */
    bool _will_inactivate_after_a_few_frames_flg;
    /** ���ƂŒ�~�̎c�t���[�����i�_�t���[���ƈ�v�������~�j */
    DWORD _frame_of_inactivation;

    /** �m�[�h�������ɐ؂�ւ����(_is_active_flg �� false �� true)�u�ԂɂP�t���[�������Z�b�g�����t���O */
    bool _on_change_to_active_flg;
    /** �m�[�h����~�ɐ؂�ւ����(_is_active_flg �� true �� false)�u�ԂɂP�t���[�������Z�b�g�����t���O */
    bool _on_change_to_inactive_flg;



    /** �m�[�h���a��(addSub���ꂽ�j������̃t���[�� */
    DWORD _lifeframe;

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
    virtual void cleane(int prm_num_cleaning);

    /**
     * �m�[�h��������(�P��) .
     * �C���X�^���X������A
     * ���ꂩ���Ăяo�����O�ɁA�ŏ��ɕK���P�񂾂��Ăяo�����B<BR>
     */
    virtual void initialize() = 0;

    /**
     * �m�[�h�̃t���[�������Z�ƁA�t���[���J�n�ɂ������Ă̂��낢��ȏ�������(���c���[) .
     * _is_active_flg_in_next_frame _was_paused_flg_in_next_frame _can_live_flg_in_next_frame ��<BR>
     * _is_active_flg _was_paused_flg _can_live_flg �ɔ��f�i�R�s�[�j����B<BR>
     * �܂��A_will_move_first_in_next_frame_flg, _will_move_last_in_next_frame_flg �� true �̏ꍇ�́A<BR>
     * ���ꂼ��A���m�[�h�̐擪�m�[�h�ւ̈ړ��A�����m�[�h�ւ̈ړ����������s�����B<BR>
     * ���̌�A�z���m�[�h�S�Ă� nextFrame() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��Ė{�����o�֐����s��Abehave()�����s����B<BR>
     */
    virtual void nextFrame();

    /**
     * �m�[�h�̃t���[�����̐U�镑������(���c���[) .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �i _is_active_flg && !_was_paused_flg && _can_live_flg �j�̏ꍇ <BR>
     * processBehavior() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� behave() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��Ė{�����o�֐����s��Ajudge()�����s����B<BR>
     */
    virtual void behave();

    /**
     * �񊈓����������ɐ؂�ւ�������̏���(�P��) .
     * �񊈓���Ԃ��犈����Ԃɕω������Ƃ��ɂP��R�[���o�b�N�����B<BR>
     * �Ăяo�����^�C�~���O�̓t���[�����Z����ł���B
     * �K�v�ɉ����ăI�[�o�[���C�h����B<BR>
     */
    virtual void onActive() {
    }

    /**
     * �������񊈓����ɐ؂�ւ�������̏���(�P��) .
     * ������Ԃ���񊈓���Ԃɕω������Ƃ��ɂP��R�[���o�b�N�����B<BR>
     * �Ăяo�����^�C�~���O�̓t���[�����Z����ł���B
     * �K�v�ɉ����ăI�[�o�[���C�h����B<BR>
     */
    virtual void onInactive() {
    }

    /**
     * �m�[�h�̃t���[�����̔��菈��(���c���[) .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �܂� ( _is_active_flg && !_was_paused_flg && _can_live_flg )�̏ꍇ <BR>
     * processJudgement() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� judge() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��Ė{�����o�֐����s��A���t���[���܂ł̎c���Ԃɗ]�T������� preDraw()
     * ������� finally() �����s����B<BR>
     */
    virtual void judge();

    /**
     * �m�[�h�̃t���[�����̕`�掖�O����(���c���[)�i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����t���O�A�����t���O���Z�b�g�A<BR>
     * (�܂� _is_active_flg && _can_live_flg)�̏ꍇ <BR>
     * processPreDraw() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� preDraw() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��Ė{�����o�֐����s��Adraw() �����s����B<BR>
     */
    virtual void preDraw();

    /**
     * �m�[�h�̃t���[�����̕`��{����(���c���[)�i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����t���O�A�����t���O���Z�b�g�A<BR>
     * (�܂� _is_active_flg && _can_live_flg)�̏ꍇ <BR>
     * processDraw() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� draw() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��Ė{�����o�֐����s��AafterDraw() �����s����B<BR>
     */
    virtual void draw();

    /**
     * �m�[�h�̃t���[�����̕`�掖�㏈��(���c���[)�i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����t���O�A�����t���O���Z�b�g<BR>
     * (�܂� _is_active_flg && _can_live_flg)�̏ꍇ <BR>
     * processTerminate() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� afterDraw() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��Ė{�����o�֐����s��Afinally() �����s����B<BR>
     */
    virtual void afterDraw();

    /**
     * �m�[�h�̃t���[�����̍ŏI����(���c���[) .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �i_is_active_flg && !_was_paused_flg && _can_live_flg�j�̏ꍇ <BR>
     * processFinally() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� finally() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��Ė{�����o�֐����s��A���t���[���܂ł̎c���Ԃɗ]�T������� cleane() �����s����B<BR>
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
     * �t���[�����̌ʐU�镑�������������B(�t���[�����[�N�����p�A�P��) .
     */
    virtual void processPreBehavior() {}

    /**
     * �t���[�����̌ʐU�镑�������������B(���[�U�[�����p�A�P��) .
     * behave() ���̏����擪�ŃR�[���o�b�N�����B<BR>
     * ���̃����o�֐������ʃN���X�ŃI�[�o�[���C�h���āA�m�[�h�ʂ̐U�镑������������������B<BR>
     * �z�肵�Ă���U�镑�������Ƃ́A��ɍ��W�v�Z�ƈړ��������ł���B<BR>
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��āAnextFrame() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     */
    virtual void processBehavior() = 0;

    /**
     * �t���[�����̌ʔ��f�����������B(�t���[�����[�N�����p�A�P��) .
     */
    virtual void processPreJudgement() {}

    /**
     * �t���[�����̌ʔ��f�����������B(���[�U�[�����p�A�P��) .
     * judge() ���̏����擪�ŃR�[���o�b�N�����B<BR>
     * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʔ��f�������L�q����B<BR>
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��ĂāAprocessBehavior() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     * �{�����o�֐��̑��݈Ӑ}�Ƃ��āAprocessBehavior() �ō��W�ړ��������S�Ċ���������
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
     * �m�[�h�̃t���[�����̌ʕ`��{�����������B(�P��) .
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
     * �m�[�h�̃t���[�����̌ʏI�[�����������B(�P��) .
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
     * @param   int prm_no �����̔ԍ�
     */
    virtual void processHappen(int prm_no) = 0;

    /**
     * �_�ɉy�� .
     * @return  �Ă΂�ďo�Ă����_
     */
    virtual GgafGod* askGod() = 0;

    //==================��ԕψڃ��\�b�h�S==================>
    /**
     * ������Ԃɂ���(���c���[) .
     * ���m�ɂ́A���t���[�����犈����Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����Ŋ�����ԂɂȂ鎖�ɂȂ�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� activateTree() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͊�����Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * ���m�[�h�� processBehavior() �Ŗ{���\�b�h���Ăяo���R�[�h�������Ă��A�^�X�N�V�X�e���̎d�g�ݏ�A<BR>
     * ���s����邱�Ƃ͖����̂ŁA���m�[�h������s������AprocessFinal() �Ȃǂł̎g�p��z��B<BR>
     * <B>[�⑫]</B>�m�[�h��������́A������ԂƂȂ��Ă���B<BR>
     */
    void activateTree();

    /**
     * ������Ԃɂ���(�P��) .
     * N�t���[����� activate() �����s����邱�Ƃ�\�񂷂�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� activateAfter(DWORD) �����s�����B<BR>
     * activateAfter(1) �́Aactivate() �Ɠ����Ӗ��ɂȂ�܂��B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͊�����Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * @param prm_frame_offset �x���t���[����(1�`)
     */
    void activateAfter(DWORD prm_frame_offset);

    /**
     * ������Ԃɂ���(�P��) .
     * ���m�[�h�������t���[�����犈����Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͊�����Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     */
    void activate();

    /**
     * ������Ԃɂ���(�P�́E����) .
     * ���m�[�h�ɂ��āA�����Ɋ�����Ԃɂ���B�ʏ�A�{���\�b�h�̎g�p�͔񐄏��B<BR>
     * �����ɏ�Ԃ��ω����邽�߁A�ȉ��̓_�𗯈ӂ��āA�g�p����ۂ͒��ӂ��K�v�ł���B<BR>
     * ���s�O�̎��m�[�h��Ԃ� �񊈓���� ( _is_active_flg == false ) �̏ꍇ�A�񊈓��������ɕω������Ƃ��āA<BR>
     * ������ onActive() �R�[���o�b�N���Ăяo���A�܂� _on_change_to_active_flg = true �Ƃ���B<BR>
     * onActive() �R�[���o�b�N�́A���t���[�����Z���͌Ăяo����Ȃ��B �i�Q�d�ɌĂ΂�鎖�͖����悤�ɂ��Ă���j<BR>
     * ����� onActive() �͉��z�֐��ł��邽�߁A�����{�N���X���p���������ʂɃN���X�̃R���X�g���N�^���� activateImmediately() <BR>
     * ���Ăяo�����ꍇ�A�p���N���X�̎����� onActive() �͎��s���ꂸ�A������̖{�N���X�� onInctive() ���Ăяo�����B<BR>
     * �܂��A _on_change_to_active_flg ���͂��߁A���̑��{���\�b�h�ɂ���ĕω������V���ȃt���O��Ԃ́A<BR>
     * �w����t���[�����x�̎c��̖������̃m�[�h�ɑ΂��Ă̂ݗL���ƂȂ�B�܂�A<BR>
     * �w����t���[�����x�ł����Ă��A���ɏ������ꂽ�m�[�h�Ƃ͈قȂ��ԂɂȂ�\�����傫���A<BR>
     * ���m�[�h�̃��W�b�N���A�u���̃m�[�h��������ԂȂ�΁E�E�E�v���A���̏�ԁi�t���O�j�ɂ�菈�����򂵂Ă����ꍇ�A<BR>
     * ����t���[�����̏������ʂ̐�����������鋰�ꂪ����B<BR>
     * ���m�[�h�̉e���A�c���[�\����ǂ��l���Ďg�p���邱�ƁB<BR>
     */
    void activateImmediately();

    /**
     * ������Ԃɂ���(���c���[�E����) .
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� activateImmediately() �����s�����B<BR>
     * activateImmediately() �̐�����v�Q�ƁB<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void activateTreeImmediately();
    //===================
    /**
     * �񊈓���Ԃɂ���(���c���[) .
     * ���m�ɂ́A���t���[������񊈓���Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����Ŕ񊈓���ԂɂȂ鎖�ɂȂ�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� inactivate() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͔񊈓���Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     */
    void inactivateTree();

    /**
     * �񊈓��\�񂷂�(���c���[) .
     * N�t���[����� inactivateTree() �����s����邱�Ƃ�\�񂷂�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� inactivateAfter(DWORD) �����s�����B<BR>
     * inactivateAfter(1) �́AinactivateTree() �Ɠ����Ӗ��ɂȂ�܂��B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͔񊈓���Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * @param prm_frame_offset �x���t���[����(1�`)
     */
    void inactivateAfter(DWORD prm_frame_offset);

    /**
     * �񊈓���Ԃɂ���(�P��) .
     * ���m�[�h�������t���[������񊈓���Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͔񊈓���Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     */
    void inactivate();

    /**
     * �񊈓���Ԃɂ���(�P�́E����) .
     * ���m�[�h�ɂ��āA�����ɔ񊈓���Ԃɂ���B�ʏ�A�{���\�b�h�̎g�p�͔񐄏��B<BR>
     * �����ɏ�Ԃ��ω����邽�߁A�ȉ��̓_�𗯈ӂ��āA�g�p����ۂ͒��ӂ��K�v�ł���B<BR>
     * ���s�O�̎��m�[�h��Ԃ� ������� ( _is_active_flg == true ) �̏ꍇ�A�������񊈓��ɕω������Ƃ��āA<BR>
     * ������ onInctive() �R�[���o�b�N���Ăяo���A�܂� _on_change_to_inactive_flg = true �Ƃ���B<BR>
     * onInctive() �R�[���o�b�N�́A���t���[�����Z���͌Ăяo����Ȃ��B�i�Q�d�ɌĂ΂�鎖�͖����悤�ɂ��Ă���j <BR>
     * ����� onInctive() �͉��z�֐��ł��邽�߁A�����{�N���X���p���������ʂɃN���X�̃R���X�g���N�^���� inactivateImmediately() <BR>
     * ���Ăяo�����ꍇ�A�p���N���X�̎����� onInctive() �͎��s���ꂸ�A������̖{�N���X�� onInctive() ���Ăяo�����B<BR>
     * �܂��A _on_change_to_inactive_flg ���͂��߁A���̑��{���\�b�h�ɂ���ĕω������V���ȃt���O��Ԃ́A<BR>
     * �w����t���[�����x�̎c��̖������̃m�[�h�ɑ΂��Ă̂ݗL���ƂȂ�B�܂�A<BR>
     * �w����t���[�����x�ł����Ă��A���ɏ������ꂽ�m�[�h�Ƃ͈قȂ��ԂɂȂ�\�����傫���A<BR>
     * ���m�[�h�̃��W�b�N���A�u���̃m�[�h���񊈓���ԂȂ�΁E�E�E�v���A���̏�ԁi�t���O�j�ɂ�菈�����򂵂Ă����ꍇ�A<BR>
     * ����t���[�����̏������ʂ̐�����������鋰�ꂪ����B<BR>
     * ���m�[�h�̉e���A�c���[�\����ǂ��l���Ďg�p���邱�ƁB<BR>
     */
    void inactivateImmediately();

    /**
     * �񊈓���Ԃɂ���(���c���[�E����) .
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� inactivateImmediately() �����s�����B<BR>
     * inactivateImmediately() �̐�����v�Q�ƁB<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void inactivateTreeImmediately();

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
     * ����Ȃ炵�܂��B(���c���[) .
     * ���m�[�h�����t���[������u�����I���v��Ԃɂ��邱�Ƃ�錾����B <BR>
     * ���c���[�m�[�h�S�Ăɐ����I��(adios())�����m�点���͂��B<BR>
     * �����I���Ƃ͋�̓I�ɂ́A�U�镑���t���O(_is_active_flg)�A�����t���O(_can_live_flg) ���A
     * ���t���[������A���Z�b�g���鎖�ł���B<BR>
     * _can_live_flg ���A���Z�b�g����邱�Ƃɂ��A�_(GgafGod)���������Ԃ̗]�T�̂��鎞�� cleane() ���\�b�h�ɂ��
     * delete �̑ΏۂƂȂ�B<BR>
     * ���������āA�{�����o�֐������s���Ă��A�w����t���[�����x�ł́A�܂�delete�͍s�Ȃ��Ȃ��B
     * �C���X�^���X�������ɉ������Ȃ����Ƃɒ��ӁB���͂���Ȃ炷�邾���B<BR>
     * ���ӁF����Ȃ炵����w����t���[�����x�ɁA _can_live_flg ���Z�b�g�������Ă��ʖڂł��B<BR>
     * ����͖{���\�b�h�ŁAGgafGarbageRootActor�ɏ������邽�߂ł��B<BR>
     */
    void adios(DWORD prm_frame_offset = 0);

    /**
     * ���c���[�m�[�h���ŏI�m�[�h�Ɉړ�����(�P��) .
     * ���t���[���̐擪����(nextFrame())�Ŏ��c���[�m�[�h���Z��m�[�h�O���[�v�̍ŏI�ɃV�t�g����B<BR>
     * <B>[����]</B>�����ɏ��J�菈�������s�����킯�ł͂Ȃ��B<BR>
     */
    void moveLast() {
        _will_move_last_in_next_frame_flg = true;
    }

    /**
     * ���c���[�m�[�h��擪�m�[�h�Ɉړ�����(�P��) .
     * ���t���[���̐擪����(nextFrame())�Ŏ��c���[�m�[�h���Z��m�[�h�O���[�v�̐擪�ɃV�t�g����B<BR>
     * <B>[����]</B>�����ɏ��J�菈�������s�����킯�ł͂Ȃ��B<BR>
     */
    void moveFirst() {
        _will_move_first_in_next_frame_flg = true;
    }

    /**
     * �����c���[����Ɨ�����(�P��)
     * @return  T* �E�ނ��Ɨ��������m�[�h�̃|�C���^
     *
     */
    T* becomeIndependent();


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
     * �U�镑���͍s�Ȃ��Ă��邩�i���ꎞ��~����Ă��Ȃ����j
     * @return  bool true:�U�镑���\�i�ꎞ��~�ł͖����j�^false:�U�镑���s�i�ꎞ��~���j
     */
    bool isBehaving();

    /**
     * �`�撆���ǂ������ׂ�i��\���łȂ����ǂ����j
     * @return  bool true:�`��ł���(�\���Ώ�)�^false:�`��͂��Ȃ�(��\���Ώ�)
     */
    bool isVisible();

    /**
     * �m�[�h�̌��݂̌o�߃t���[�����擾����
     */
    DWORD getSurvivalFrame() {
        return _lifeframe;
    }

    /**
     * ���Όo�߃t���[���̔���B
     * ���O�� relativeFrame(int) ���s���i���ʂ�true/false�Ɋւ�炸�j�̃t���[��������̌o�߃t���[�����ɒB���������肷��B
     * ���ӁF����q���������ɂ��ArelativeFrame(int) ���Ăяo�����񐔂��ω�����ꍇ�A���Όo�߃t���[�����ω�����B
     * @param   prm_frame_relative    �o�߃t���[����
     * @return  bool    true:�o�߃t���[�����ɒB����/false:�B���Ă��Ȃ�
     */
    bool relativeFrame(DWORD prm_frame_relative);

};

///////////////////////////////////////////////////////////////// ��������͎�����

template<class T>
GgafElement<T>::GgafElement(const char* prm_name) : SUPER(prm_name),
            _pGod(NULL), _was_initialize_flg(false), _dwGodFrame_when_goodbye(MAXDWORD), _lifeframe(0),
            _frame_relative(0), _is_active_flg(true), _was_paused_flg(false), _can_live_flg(true),
            _is_active_flg_in_next_frame(true), _was_paused_flg_in_next_frame(false),
            _can_live_flg_in_next_frame(true), _will_move_first_in_next_frame_flg(false), _will_move_last_in_next_frame_flg(false),
            _will_activate_after_a_few_frames_flg(false), _frame_of_activation(0), _will_inactivate_after_a_few_frames_flg(false), _frame_of_inactivation(0),
            _on_change_to_active_flg(false), _on_change_to_inactive_flg(false) {
}

template<class T>
void GgafElement<T>::nextFrame() {
    TRACE("GgafElement::nextFrame BEGIN _lifeframe=" << _lifeframe << " name=" << GgafNode<T>::_name << " class="
            << GgafNode<T>::_class_name);
    _was_paused_flg  = _was_paused_flg_in_next_frame;
    if (_was_paused_flg) {
        return;
    }

    //���̎���
    if (_dwGodFrame_when_goodbye == (askGod()->_godframe)) {
        _is_active_flg_in_next_frame = false;
        _can_live_flg_in_next_frame = false;
    }


    if (_will_move_last_in_next_frame_flg) {
        _will_move_last_in_next_frame_flg = false;
        SUPER::moveLast();
    } else {

        if(_was_initialize_flg == false) {
            initialize();
            _was_initialize_flg = true;
        }

        if (_can_live_flg) {
            if (_will_activate_after_a_few_frames_flg) {
                //�x��play����
                if (_lifeframe >= _frame_of_activation) {
                    activate();
                    _frame_of_activation = 0;
                    _will_activate_after_a_few_frames_flg = false;
                }
            }

            if (_will_inactivate_after_a_few_frames_flg) {
                //�x��stop����
                if (_lifeframe == _frame_of_inactivation) {
                    inactivate();
                    _frame_of_inactivation = 0;
                    _will_inactivate_after_a_few_frames_flg = false;
                }
            }
            if (_is_active_flg) {
                _lifeframe++;
            }
        }

        //�����A�񊈓��̏�ԕω���
        if (_is_active_flg == false && _is_active_flg_in_next_frame) {
            _on_change_to_active_flg = true;
            onActive(); //�R�[���o�b�N
        } else if (_is_active_flg && _is_active_flg_in_next_frame == false) {
            _on_change_to_inactive_flg = true;
            onInactive(); //�R�[���o�b�N
        } else {
            _on_change_to_active_flg = false;
            _on_change_to_inactive_flg = false;
        }

        //�t���O�����𔽉f
        _is_active_flg   = _is_active_flg_in_next_frame;
        _can_live_flg    = _can_live_flg_in_next_frame;

        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                if (pElementTemp->_is_last_flg) {
                    pElementTemp->nextFrame();
                    if (pElementTemp->_can_live_flg == false) {
                        GgafFactory::_pGarbageBox->add(pElementTemp);
                    }
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                    pElementTemp->SUPER::_pPrev->nextFrame();
                    if (pElementTemp->SUPER::_pPrev->_can_live_flg == false) {
                        GgafFactory::_pGarbageBox->add(pElementTemp->SUPER::_pPrev);
                    }
                }
            }
        }

        if (_will_move_first_in_next_frame_flg) {
            _will_move_first_in_next_frame_flg = false;
            SUPER::moveFirst();
        }

    }
    TRACE("GgafElement::nextFrame END _lifeframe="<<_lifeframe<<" name="<<GgafNode<T>::_name<<" class="<<GgafNode<T>::_class_name);
}

template<class T>
void GgafElement<T>::behave() {
    if(_was_initialize_flg == false) {
        initialize();
        _was_initialize_flg = true;
    }

    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        _frame_relative = 0;
        processPreBehavior();
        processBehavior();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->behave();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::judge() {
    if(_was_initialize_flg == false) {
        initialize();
        _was_initialize_flg = true;
    }

    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        _frame_relative = 0;
        processPreJudgement();
        processJudgement();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->judge();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::preDraw() {
    if(_was_initialize_flg == false) {
        initialize();
        _was_initialize_flg = true;
    }

    if (_is_active_flg && _can_live_flg) {
        _frame_relative = 0;
        processPreDraw();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->preDraw();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::draw() {
    if (_is_active_flg && _can_live_flg) {
        _frame_relative = 0;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->draw();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::afterDraw() {
    if (_is_active_flg && _can_live_flg) {
        _frame_relative = 0;
        processAfterDraw();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->afterDraw();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::happen(int prm_no) {
    if(_was_initialize_flg == false) {
        initialize();
        _was_initialize_flg = true;
    }

    if (_can_live_flg) {
        _frame_relative = 0;
        processHappen(prm_no);
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->happen(prm_no);
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::finally() {
    if(_was_initialize_flg == false) {
        initialize();
        _was_initialize_flg = true;
    }

    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        _frame_relative = 0;
        processFinal();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->finally();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::activate() {
    if (_can_live_flg) {
        _is_active_flg_in_next_frame = true;
        _was_paused_flg_in_next_frame = false;
    }
}

template<class T>
void GgafElement<T>::activateTree() {
    if (_can_live_flg) {
        _is_active_flg_in_next_frame = true;
        _was_paused_flg_in_next_frame = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->activateTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::activateImmediately() {
    if (_can_live_flg) {
        if (_is_active_flg == false) {
            _on_change_to_active_flg = true;
            onActive(); //�R�[���o�b�N
        } else {
            _on_change_to_active_flg = false;
        }
        _is_active_flg = true;
        _was_paused_flg = false;
        _is_active_flg_in_next_frame = true;
        _was_paused_flg_in_next_frame = false;
    }
}

template<class T>
void GgafElement<T>::activateTreeImmediately() {
    if (_can_live_flg) {
        if (_is_active_flg == false) {
            _on_change_to_active_flg = true;
            onInactive(); //�R�[���o�b�N
        } else {
            _on_change_to_active_flg = false;
        }
        _is_active_flg = true;
        _was_paused_flg = false;
        _is_active_flg_in_next_frame = true;
        _was_paused_flg_in_next_frame = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->activateTreeImmediately();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::activateAfter(DWORD prm_frame_offset) {
    _will_activate_after_a_few_frames_flg = true;
    _frame_of_activation = _lifeframe + prm_frame_offset;
}

template<class T>
void GgafElement<T>::inactivate() {
    if (_can_live_flg) {
        _is_active_flg_in_next_frame = false;
    }
}

template<class T>
void GgafElement<T>::inactivateTree() {
    if (_can_live_flg) {
        _is_active_flg_in_next_frame = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->inactivateTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::inactivateAfter(DWORD prm_frame_offset) {
    _will_inactivate_after_a_few_frames_flg = true;
    _frame_of_inactivation = _lifeframe + prm_frame_offset;
}

template<class T>
void GgafElement<T>::inactivateImmediately() {
    if (_can_live_flg) {
        if (_is_active_flg) {
            _on_change_to_inactive_flg = true;
        } else {
            _on_change_to_inactive_flg = false;
        }
        _is_active_flg = false;
        _is_active_flg_in_next_frame = false;
    }
}

template<class T>
void GgafElement<T>::inactivateTreeImmediately() {
    if (_can_live_flg) {
        if (_is_active_flg) {
            _on_change_to_inactive_flg = true;
        } else {
            _on_change_to_inactive_flg = false;
        }
        _is_active_flg = false;
        _is_active_flg_in_next_frame = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->inactivateTreeImmediately();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
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
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->pauseTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
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
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->pauseTreeImmediately();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
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
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->unpauseTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
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
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->unpauseTreeImmediately();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
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
void GgafElement<T>::adios(DWORD prm_frame_offset) {

    _dwGodFrame_when_goodbye = (askGod()->_godframe) + prm_frame_offset + 1;
    if (SUPER::_pSubFirst != NULL) {
        T* pElementTemp = SUPER::_pSubFirst;
        while(true) {
            pElementTemp->adios(prm_frame_offset);
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->SUPER::_pNext;
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
bool GgafElement<T>::isVisible() {
    if (_can_live_flg && _is_active_flg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::isBehaving() {
    if (_can_live_flg && _is_active_flg && !_was_paused_flg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::relativeFrame(DWORD prm_frame_relative) {
    _frame_relative += prm_frame_relative;
    if (_lifeframe == _frame_relative) {
        return true;
    } else {
        return false;
    }
}


template<class T>
T* GgafElement<T>::becomeIndependent() {
    if (_can_live_flg) {
        return SUPER::extract();
    } else {
        throwGgafCriticalException("[GgafTreeNode<"<<SUPER::_class_name<<">::becomeIndependent()] ���x���� "<<SUPER::getName()<<"�́A�����ꎀ�ɍs���^���ł���B");
    }
}

template<class T>
void GgafElement<T>::cleane(int prm_num_cleaning) {
    if (SUPER::_pSubFirst == NULL) {
        return;
    }

    T* pElementTemp = SUPER::_pSubFirst->_pPrev;
    T* pWk;

    while(GgafFactory::_cnt_cleaned < prm_num_cleaning) {

        if (pElementTemp->_pSubFirst) {
            //�q�̎q���܂��̂��Ă���ꍇ����ɂ�����
            pElementTemp->cleane(prm_num_cleaning);
            if (GgafFactory::_cnt_cleaned >= prm_num_cleaning) {
                break;
            }
        }

        if (pElementTemp->_is_first_flg) { //�Ō�̈��
            if (pElementTemp->_pSubFirst) {
                //�q�̎q���܂��̂��Ă���ꍇ����ɂ�����
                pElementTemp->cleane(prm_num_cleaning);
                if (GgafFactory::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            if (pElementTemp->_can_live_flg == false) {
                DELETE_IMPOSSIBLE_NULL(pElementTemp);
                GgafFactory::_cnt_cleaned++;
                Sleep(1);
            }
            break;
        } else {
            pWk = pElementTemp;
            if (pWk->_pSubFirst) {
                //�q�̎q���܂��̂��Ă���ꍇ����ɂ�����
                pWk->cleane(prm_num_cleaning);
                if (GgafFactory::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            pElementTemp = pElementTemp->_pPrev;
            if (pWk->_can_live_flg == false) {
                DELETE_IMPOSSIBLE_NULL(pWk);
                GgafFactory::_cnt_cleaned++;
                Sleep(1);
            }
        }
    }
}

template<class T>
GgafElement<T>::~GgafElement() {
}

}
#endif /*GGAFELEMENT_H_*/
