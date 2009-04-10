#ifndef GGAFELEMENT_H_
#define GGAFELEMENT_H_
namespace GgafCore {

#define SUPER GgafCore::GgafNode<T>

/**
 * GgafNode�ɁA�^�X�N�V�X�e���y�їl�X�ȏ�ԊǗ��i�t���O�Ǘ��j��ǉ��B .
 * ���t���[���A��_(GgafGod)�͐��E(GgafWorld)�ɁA���̃��\�b�h���ŌĂяo���d�g�݂ɂȂ��Ă���B���E(GgafWorld)���{template���������Ă���B<BR>
 * nextFrame() > behave() > judge() > [drawPrior() > drawMain() > drawTerminate()] > finally() <BR>
 * ��L�̓��AnextFrame()�Afinally() �͖��t���[�����s�����B<BR>
 * behave()�Ajudge() �͊�����ԃt���O(_is_active_flg)�� true�A���A�ꎞ��~�t���O(_was_paused_flg)�� false �̏ꍇ���s�����B<BR>
 * drawPrior()�AdrawMain()�AdrawTerminate() �́A���t���[���܂ł̎c���Ԃɗ]�T������A���ꎞ��\���t���O(_was_hidden_flg) �� false �̏ꍇ<BR>
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
    /** �_�ւ̋ߓ� */
    GgafGod* _pGod;
    /** initialize���s��ꂽ�ǂ����̃t���O(true=�s��ꂽ) */
    bool _was_initialize_flg;

    /** �]�� */
    DWORD _dwGodFrame_when_goodbye;
    /** �m�[�h���a��(addSub���ꂽ�j������̃t���[�� */
    DWORD _lifeframe;
    /** ���΃t���[���v�Z�p */
    DWORD _frame_relative;
    /** �m�[�h�����t���O */
    bool _is_active_flg;
    /** �ꎞ��~�t���O */
    bool _was_paused_flg;
    /** �ꎞ��\���t���O */
    bool _was_hidden_flg;
    /** �m�[�h�����t���O */
    bool _can_live_flg;

    /** ���t���[���m�[�h�����\��t���O�A���t���[���̃t���[�����Z�� _is_active_flg �ɔ��f����� */
    bool _will_activate_at_next_frame_flg;
    /** ���t���[���ꎞ��~�\��t���O�A���t���[���̃t���[�����Z�� _was_paused_flg �ɔ��f����� */
    bool _wil_pause_at_next_frame_flg;
    /** ���t���[���ꎞ��\���\��t���O�A���t���[���̃t���[�����Z�� _was_hidden_flg �ɔ��f�����  */
    bool _will_hidden_at_next_frame_flg;
    /** ���t���[�������\��t���O�A���t���[���̃t���[�����Z�� _can_live_flg �ɐݒ肳��� */
    bool _will_be_alive_at_next_frame_flg;

    /** �擪�m�[�h�Ɉړ��\��t���O�A���t���[���̃t���[�����Z���ɁA���m�[�h���擪�m�[�h�Ɉړ����� */
    bool _will_move_first_at_next_frame_flg;
    /** �����m�[�h�Ɉړ��\��t���O�A���t���[���̃t���[�����Z���ɁA���m�[�h�������m�[�h�Ɉړ����� */
    bool _will_move_last_at_next_frame_flg;

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
     * �|�� .
     * �_���������Ԃɗ]�T���ł��Ƃ����ɁA�_���Ăт����B<BR>
     * �z���m�[�h�̒��Ƀm�[�h�����t���O(_can_live_flg)�� false �ɂȂ��Ă���m�[�h������� prm_num_cleaning ���� delete ����B<BR>
     * @param prm_num_cleaning �������I�u�W�F�N�g��
     */
    virtual void cleane(int prm_num_cleaning);

    /**
     * �m�[�h�������� .
     * �C���X�^���X������AnextFrame(),behave(),judge(),drawPrior(),drawMain(),drawTerminate(),happen(int),finally() ��
     * ���ꂩ���Ăяo���ꂽ���A�ŏ��ɕK���P�񂾂��Ăяo�����B<BR>
     */
    virtual void initialize() = 0;

    /**
     * �m�[�h�̃t���[�������Z�ƁA�t���[���J�n�ɂ������Ă̂��낢��ȏ������� .
     * _will_activate_at_next_frame_flg, _wil_pause_at_next_frame_flg, _will_hidden_at_next_frame_flg, _will_be_alive_at_next_frame_flg ��<BR>
     * _is_active_flg, _was_paused_flg, _was_hidden_flg, _can_live_flg �ɔ��f�i�R�s�[�j����B<BR>
     * �܂��A_will_move_first_at_next_frame_flg, _will_move_last_at_next_frame_flg �� true �̏ꍇ�́A<BR>
     * ���ꂼ��A���m�[�h�̐擪�m�[�h�ւ̈ړ��A�����m�[�h�ւ̈ړ����������s�����B<BR>
     * ���̌�A�z���m�[�h�S�Ă� nextFrame() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��Abehave()�����s����B<BR>
     */
    virtual void nextFrame();

    /**
     * �m�[�h�̃t���[�����̐U�镑������ .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �i_is_active_flg && !_was_paused_flg && _can_live_flg�j�̏ꍇ <BR>
     * processBehavior() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� behave() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��Ajudge()�����s����B<BR>
     */
    virtual void behave();

    /**
     * �񊈓����������ɐ؂�ւ�������̏��� .
     * �񊈓���Ԃ��犈����Ԃɕω������Ƃ��ɂP��R�[���o�b�N�����B<BR>
     * �K�v�ɉ����ăI�[�o�[���C�h����B<BR>
     */
    virtual void onActive() {
    }

    /**
     * �������񊈓����ɐ؂�ւ�������̏��� .
     * ������Ԃ���񊈓���Ԃɕω������Ƃ��ɂP��R�[���o�b�N�����B<BR>
     * �K�v�ɉ����ăI�[�o�[���C�h����B<BR>
     */
    virtual void onInactive() {
    }

    /**
     * �m�[�h�̃t���[�����̔��菈�� .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * (�܂� _is_active_flg && !_was_paused_flg && _can_live_flg)�̏ꍇ <BR>
     * processJudgement() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� judge() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��A���t���[���܂ł̎c���Ԃɗ]�T������� drawPrior()�A
     * ������� finally()�����s����B<BR>
     */
    virtual void judge();

    /**
     * �m�[�h�̃t���[�����̕`�掖�O�����i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��\���t���O���A���Z�b�g<BR>
     * (�܂� _is_active_flg && !_was_hidden_flg && _can_live_flg)�̏ꍇ <BR>
     * processDrawPrior() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� drawPrior() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��AdrawMain() �����s����B<BR>
     */
    virtual void drawPrior();

    /**
     * �m�[�h�̃t���[�����̕`��{�����i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��\���t���O���A���Z�b�g<BR>
     * (�܂� _is_active_flg && !_was_hidden_flg && _can_live_flg)�̏ꍇ <BR>
     * processDrawMain() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� drawMain() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��AdrawTerminate() �����s����B<BR>
     */
    virtual void drawMain();

    /**
     * �m�[�h�̃t���[�����̕`�掖�㏈���i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��\���t���O���A���Z�b�g<BR>
     * (�܂� _is_active_flg && !_was_hidden_flg && _can_live_flg)�̏ꍇ <BR>
     * processTerminate() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� drawTerminate() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��Afinally() �����s����B<BR>
     */
    virtual void drawTerminate();

    /**
     * �m�[�h�̃t���[�����̍ŏI���� .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �i_is_active_flg && !_was_paused_flg && _can_live_flg�j�̏ꍇ <BR>
     * processFinally() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� finally() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��A���t���[���܂ł̎c���Ԃɗ]�T������� cleane() �����s����B<BR>
     */
    virtual void finally();

    /**
     * �m�[�h�̉����̏���(�t���[�����ł͂Ȃ�) .
     * �����t���O���Z�b�g�A(�܂� _is_active_flg)�̏ꍇ <BR>
     * processHappen(int) ���R�[��������A�z���̃m�[�h�S�Ăɂ��� happen() ���ċA�I�Ɏ��s����B<BR>
     * @param   prm_no �����̔ԍ�
     */
    virtual void happen(int prm_no);

    /**
     * �t���[�����̌ʐU�镑�������������B .
     * behave() ���̏����擪�ŃR�[���o�b�N�����B<BR>
     * ���̃����o�֐������ʃN���X�ŃI�[�o�[���C�h���āA�m�[�h�ʂ̐U�镑������������������B<BR>
     * �z�肵�Ă���U�镑�������Ƃ́A��ɍ��W�v�Z�ƈړ��������ł���B<BR>
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A���c���[�m�[�h�S�Ăɑ΂��āAnextFrame() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     */
    virtual void processBehavior() = 0;

    /**
     * �t���[�����̌ʔ��f�����������B .
     * judge() ���̏����擪�ŃR�[���o�b�N�����B<BR>
     * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʔ��f�������L�q����B<BR>
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A���c���[�m�[�h�S�Ăɑ΂��āAbehave() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     * �{�����o�֐��̑��݈Ӑ}�Ƃ��āAprocessBehavior() �ō��W�ړ��������S�Ċ���������
     * �{�����o�֐��œ����蔻�菈������������Ƃ������g������z�肵�Ă���B<BR>
     */
    virtual void processJudgement() = 0;

    /**
     * �m�[�h�̃t���[�����̌ʕ`�掖�O�����������B .
     * drawPrior() ���̏����擪�ŃR�[���o�b�N�����B �A���A�_(GgafGod)���`��X�L�b�v�����ꍇ�A�t���[�����ŌĂяo����܂���B<BR>
     * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʕ`�掖�O��������������B<BR>
     * �ʕ`�掖�O�����Ƃ́A��ɓ�����w�i�`��Ȃǂł���B<BR>
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A���c���[�m�[�h�S�Ăɑ΂��āAjudge() �����s�ς݂ł��邱�Ƃ��ۏ؂���B<BR>
     * ����ɁA�{�����o�֐����s��AprocessDrawMain()�AprocessDrawTerminate() ���Ăяo����邱�Ƃ��ۏ؂����B
     */
    virtual void processDrawPrior() = 0;

    /**
     * �m�[�h�̃t���[�����̌ʕ`��{�����������B .
     * drawMain() ���̏����擪�ŃR�[���o�b�N�����B �A���AdrawPrior() �Ɠ��l�ɐ_(GgafGod)���`��X�L�b�v���ꂽ�ꍇ�́A�t���[�����ŌĂяo����܂���B<BR>
     * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʕ`��{��������������B<BR>
     * �ʕ`��{�����Ƃ͎�ɃL�����N�^��A�w�i�̕`���z�肵�Ă���B
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A���c���[�m�[�h�S�Ăɑ΂��āAdrawPrior() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     */
    virtual void processDrawMain() = 0;

    /**
     * �m�[�h�̃t���[�����̌ʕ\�����㏈�����L�q
     * drawTerminate() ���̏����擪�ŃR�[���o�b�N�����B �A���AdrawPrior() �Ɠ��l�ɐ_(GgafGod)���`��X�L�b�v���ꂽ�ꍇ�́A�t���[�����ŌĂяo����܂���B<BR>
     * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʕ\�����㏈������������B<BR>
     * �ʕ\�����㏈���Ƃ́A�őO�ʃ��C���[�Ŏ�������t�F�[�h�G�t�F�N�g��A��ɍőO�ʂɕ\���������\���Ȃǂł���B<BR>
     * �{�����o���R�[���o�b�N�����ƌ������́A���c���[�m�[�h�S�Ăɑ΂��āAdrawMain() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     */
    virtual void processDrawTerminate() = 0;

    /**
     * �m�[�h�̃t���[�����̌ʏI�[�����������B .
     * finally() ���̏����擪�ŃR�[���o�b�N�����B<BR>
     * ���̃����o�֐������ʃN���X�ŃI�[�o�[���C�h���āA�m�[�h�ʂ̏I�[��������������B<BR>
     * �I�[�����Ƃ́A�t���O�Ǘ��̎��s�Ȃǂł���B<BR>
     * �z�肵�Ă���U�镑�������Ƃ́A��ɍ��W�v�Z�ƈړ������ł���B���̑��Ȃ�ł��ǂ��ł���B<BR>
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A���c���[�m�[�h�S�Ăɑ΂��āAjudge() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     */
    virtual void processFinal() = 0;

    /**
     * �m�[�h�̌ʉ����̏������L�q
     * happen() ���̏����擪�ŃR�[���o�b�N�����B
     * ���p�ړI�s��̔ėp�C�x���g�p���\�b�h
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
     * �����āA���t���[���擪�����Ŋ�����ԂɂȂ鎖�ɂȂ�܂��B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� activateTree() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͊�����Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * ���m�[�h�� processBehavior() �Ŗ{���\�b�h���Ăяo���R�[�h�������Ă��A�^�X�N�V�X�e���̎d�g�ݏ�A<BR>
     * ���s����邱�Ƃ͖����̂ŁA���m�[�h������s������AprocessFinal() �Ȃǂł̎g�p��z��B<BR>
     * <B>[�⑫]</B>�m�[�h��������́A������ԂƂȂ��Ă���B<BR>
     */
    void activateTree();
    /**
     * �����\�񂷂�(���c���[) .
     * N�t���[����� activateTree() �����s����邱�Ƃ�\�񂷂�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� activateTreeAfter(DWORD) �����s�����B<BR>
     * activateTreeAfter(1) �́AactivateTree() �Ɠ����Ӗ��ɂȂ�܂��B<BR>
     * @param prm_frame_offset �x���t���[����(1�`)
     */
    void activateTreeAfter(DWORD prm_frame_offset);
    /**
     * ������Ԃɂ���(�P��) .
     * ���m�[�h�������t���[�����犈����Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     */
    void activateAlone();
    /**
     * ������Ԃɂ���(���c���[�E����) .
     * ���m�ɂ́A�����t���O�𑦍��ɗ��Ă�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� activateTreeNow() �����s�����B<BR>
     * ���̃m�[�h����́A�u������ԂȂ�΁E�E�E�����v�Ƃ���������s�Ȃ��Ă���ꍇ�A<BR>
     * �g�p�ɂ͒��ӂ��K�v�B�Ȃ��Ȃ�΁AactivateTreeNow() �����s����O�Ǝ��s�������<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B���̃m�[�h����̎Q�Ƃ���^�C�~���O�ɂ���Ă�<BR>
     * ����t���[���ł���ɂ�������炸�A�قȂ�����Ԕ���ɂȂ邩������Ȃ��B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void activateTreeNow();
    /**
     * ������Ԃɂ���(�P�́E����) .
     * ���m�[�h�݂̂ɂ��āA�����t���O�𑦍��ɗ��Ă�B<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void activateAloneNow();
    //===================
    /**
     * �񊈓���Ԃɂ���(���c���[) .
     * ���m�ɂ́A���t���[������񊈓���Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����Ŕ񊈓���ԂɂȂ鎖�ɂȂ�܂��B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� inactivateTree() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͔񊈓���Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * ���m�[�h�ɑ΂��Ďg�p������AprocessFinal() �Ȃǂł̎g�p��z��B<BR>
     */
    void inactivateTree();
    /**
     * �񊈓��\�񂷂�(���c���[) .
     * N�t���[����� inactivateTree() �����s����邱�Ƃ�\�񂷂�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� inactivateTreeAfter(DWORD) �����s�����B<BR>
     * inactivateTreeAfter(1) �́AinactivateTree() �Ɠ����Ӗ��ɂȂ�܂��B<BR>
     * @param prm_frame_offset �x���t���[����(1�`)
     */
    void inactivateTreeAfter(DWORD prm_frame_offset);
    /**
     * �񊈓���Ԃɂ���(�P��) .
     * ���m�[�h�������t���[������񊈓���Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     */
    void inactivateAlone();
    /**
     * �񊈓���Ԃɂ���(���c���[�E����) .
     * ���m�ɂ́A�����t���O�𑦍��ɉ�����B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� inactivateTreeNow() �����s�����B<BR>
     * ���̃m�[�h����́A�u�񊈓���ԂȂ�΁E�E�E�����v�Ƃ���������s�Ȃ��Ă���ꍇ�A<BR>
     * �g�p�ɂ͒��ӂ��K�v�B�Ȃ��Ȃ�΁AinactivateTreeNow() �����s����O�Ǝ��s�������<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B���̃m�[�h����̎Q�Ƃ���^�C�~���O�ɂ���Ă�<BR>
     * ����t���[���ł���ɂ�������炸�A�قȂ�����Ԕ���ɂȂ邩������Ȃ��B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void inactivateTreeNow();
    /**
     * �񊈓���Ԃɂ���(�P�́E����) .
     * ���m�[�h�݂̂ɂ��āA�񊈓��t���O�𑦍��ɗ��Ă�B<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void inactivateAloneNow();
    //===================
    /**
     * �ꎞ��~�ɂ���(���c���[) .
     * ���m�ɂ́A���t���[������ꎞ��~�ɂ���\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����ňꎞ��~�ɂȂ鎖�ɂȂ�܂��B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� pauseTree() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͈ꎞ��~�̕ω��͖�����ѐ��͕ۂ����B<BR>
     * ���m�[�h�ɑ΂��Ďg�p������AprocessFinal() �Ȃǂł̎g�p��z��B<BR>
     */
    void pauseTree();
    /**
     * �ꎞ��~�ɂ���(�P��) .
     * ���m�[�h�������t���[������ꎞ��~�ɂ���\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     */
    void pauseAlone();
    /**
     * �ꎞ��~�ɂ���(���c���[�E����) .
     * ���m�ɂ́A�ꎞ��~�t���O�𑦍��ɗ��Ă�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� pauseTreeNow() �����s�����B<BR>
     * ���̃m�[�h����́A�u�ꎞ��~�Ȃ�΁E�E�E�����v�Ƃ���������s�Ȃ��Ă���ꍇ�A<BR>
     * �g�p�ɂ͒��ӂ��K�v�B�Ȃ��Ȃ�΁ApauseTreeNow() �����s����O�Ǝ��s�������<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B���̃m�[�h����̎Q�Ƃ���^�C�~���O�ɂ���Ă�<BR>
     * ����t���[���ł���ɂ�������炸�A�قȂ�����Ԕ���ɂȂ邩������Ȃ��B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void pauseTreeNow();
    /**
     * �ꎞ��~�ɂ���(�P�́E����) .
     * ���m�[�h�݂̂ɂ��āA�ꎞ��~�t���O�𑦍��ɗ��Ă�B<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void pauseAloneNow();
    //===================
    /**
     * �ꎞ��~��Ԃ������ɂ���(���c���[) .
     * ���m�ɂ́A���t���[������ꎞ��~��Ԃ���������\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����ňꎞ��~��Ԃ���������鎖�ɂȂ�܂��B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� unpauseTree() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͈ꎞ��~��Ԃ������̕ω��͖�����ѐ��͕ۂ����B<BR>
     * ���m�[�h�ɑ΂��Ďg�p������AprocessFinal() �Ȃǂł̎g�p��z��B<BR>
     */
    void unpauseTree();
    /**
     * �ꎞ��~��Ԃ������ɂ���(�P��) .
     * ���m�[�h�������t���[������ꎞ��~��Ԃ������ɂ���\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     */
    void unpauseAlone();
    /**
     * �ꎞ��~��Ԃ���������(���c���[�E����) .
     * ���m�ɂ́A�ꎞ��~��ԃt���O�𑦍��ɉ�����B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� unpauseTreeNow() �����s�����B<BR>
     * ���̃m�[�h����́A�u�ꎞ��~��ԂȂ�΁E�E�E�����v�Ƃ���������s�Ȃ��Ă���ꍇ�A<BR>
     * �g�p�ɂ͒��ӂ��K�v�B�Ȃ��Ȃ�΁AunpauseTreeNow() �����s����O�Ǝ��s�������<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B���̃m�[�h����̎Q�Ƃ���^�C�~���O�ɂ���Ă�<BR>
     * ����t���[���ł���ɂ�������炸�A�قȂ�����Ԕ���ɂȂ邩������Ȃ��B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void unpauseTreeNow();
    /**
     * �ꎞ��~��Ԃ������ɂ���(�P�́E����) .
     * ���m�[�h�݂̂ɂ��āA�񊈓��t���O�𑦍��ɗ��Ă�B<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void unpauseAloneNow();
    //===================
    /**
     * ��\����Ԃɂ���(���c���[) .
     * ���m�ɂ́A���t���[�������\����Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����Ŕ�\����ԂɂȂ鎖�ɂȂ�܂��B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� hideTree() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͔�\����Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * ���m�[�h�ɑ΂��Ďg�p������AprocessFinal() �Ȃǂł̎g�p��z��B<BR>
     * <B>[�⑫]</B>�m�[�h��������́A��\����ԂƂȂ��Ă���B<BR>
     */
    void hideTree();
    /**
     * ��\����Ԃɂ���(�P��) .
     * ���m�[�h�������t���[�������\����Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     */
    void hideAlone();
    /**
     * ��\����Ԃɂ���(���c���[�E����) .
     * ���m�ɂ́A�񊈓��t���O�𑦍��ɗ��Ă�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� hideTreeNow() �����s�����B<BR>
     * ���̃m�[�h����́A�u��\����ԂȂ�΁E�E�E�����v�Ƃ���������s�Ȃ��Ă���ꍇ�A<BR>
     * �g�p�ɂ͒��ӂ��K�v�B�Ȃ��Ȃ�΁AhideTreeNow() �����s����O�Ǝ��s�������<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B���̃m�[�h����̎Q�Ƃ���^�C�~���O�ɂ���Ă�<BR>
     * ����t���[���ł���ɂ�������炸�A�قȂ�����Ԕ���ɂȂ邩������Ȃ��B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void hideTreeNow();
    /**
     * ��\����Ԃɂ���(�P�́E����) .
     * ���m�[�h�݂̂ɂ��āA�񊈓��t���O�𑦍��ɗ��Ă�B<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void hideAloneNow();
    //===================
    /**
     * ��\����Ԃ������ɂ���(���c���[) .
     * ���m�ɂ́A���t���[�������\����Ԃ���������\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����Ŕ�\����Ԃ���������鎖�ɂȂ�܂��B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� showTree() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͔�\����Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * ���m�[�h�ɑ΂��Ďg�p������AprocessFinal() �Ȃǂł̎g�p��z��B<BR>
     */
    void showTree();
    /**
     * ��\����Ԃ������ɂ���(�P��) .
     * ���m�[�h�������t���[�������\����Ԃ���������\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     */
    void showAlone();
    /**
     * ��\����Ԃ���������(���c���[�E����) .
     * ���m�ɂ́A��\���t���O�𑦍��ɉ�����B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� showTreeNow() �����s�����B<BR>
     * ���̃m�[�h����́A�u��\����ԂȂ�΁E�E�E�����v�Ƃ���������s�Ȃ��Ă���ꍇ�A<BR>
     * �g�p�ɂ͒��ӂ��K�v�B�Ȃ��Ȃ�΁AshowTreeNow() �����s����O�Ǝ��s�������<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B���̃m�[�h����̎Q�Ƃ���^�C�~���O�ɂ���Ă�<BR>
     * ����t���[���ł���ɂ�������炸�A�قȂ�����Ԕ���ɂȂ邩������Ȃ��B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void showTreeNow();
    /**
     * ��\����Ԃ���������(�P�́E����) .
     * ���m�[�h�݂̂ɂ��āA��\����t���O�𑦍��ɉ�����B<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void showAloneNow();
    //===================
    /**
     * ����Ȃ炵�܂��B .
     * ���m�[�h�����t���[������u�����I���v��Ԃɂ��邱�Ƃ�錾����B <BR>
     * ���c���[�m�[�h�S�Ăɐ����I��(arigatou_sayounara())�����m�点���͂��B<BR>
     * �����I���Ƃ͋�̓I�ɂ́A�\���t���O(_was_hidden_flg)�A�U�镑���t���O(_is_active_flg)�A�����t���O(_can_live_flg) ���A
     * ���t���[������A���Z�b�g���鎖�ł���B<BR>
     * _can_live_flg ���A���Z�b�g����邱�Ƃɂ��A�_(GgafGod)���������Ԃ̗]�T�̂��鎞�� cleane() ���\�b�h�ɂ��
     * delete �̑ΏۂƂȂ�B<BR>
     * ���������āA�{�����o�֐������s���Ă��A�w����t���[�����x�ł́A�܂�delete�͍s�Ȃ��Ȃ��B
     * �C���X�^���X�������ɉ������Ȃ����Ƃɒ��ӁB���͂���Ȃ炷�邾���B<BR>
     * ���ӁF����Ȃ炵����w����t���[�����x�ɁA _can_live_flg ���Z�b�g�������Ă��ʖڂł��B<BR>
     * ����͖{���\�b�h�ŁAGgafGarbageRootActor�ɏ������邽�߂ł��B<BR>
     */
    void arigatou_sayounara(DWORD prm_frame_offset = 0);

    /**
     * ���c���[�m�[�h���ŏI�m�[�h�Ɉړ����� .
     * ���t���[���̐擪����(nextFrame())�Ŏ��c���[�m�[�h���Z��m�[�h�O���[�v�̍ŏI�ɃV�t�g����B<BR>
     * <B>[����]</B>�����ɏ��J�菈�������s�����킯�ł͂���܂���B<BR>
     */
    void moveLast() {
        _will_move_last_at_next_frame_flg = true;
    }

    /**
     * ���c���[�m�[�h��擪�m�[�h�Ɉړ����� .
     * ���t���[���̐擪����(nextFrame())�Ŏ��c���[�m�[�h���Z��m�[�h�O���[�v�̐擪�ɃV�t�g����B<BR>
     * <B>[����]</B>�����ɏ��J�菈�������s�����킯�ł͂���܂���B<BR>
     */
    void moveFirst() {
        _will_move_first_at_next_frame_flg = true;
    }

    /**
     * �����c���[����Ɨ�����
     * @return  T* �E�ނ��Ɨ��������m�[�h�̃|�C���^
     *
     */
    T* becomeIndependent();


    /**
     * �񊈓����犈���ɐ؂�ւ�������ǂ��� .
     * �������AonActive() �ő�p�ł���ꍇ�́A��������I�[�o�[���C�h�����ق�����������L�q�ł���͂��B
     * @return  bool true:�؂�ւ�����^false:�؂�ւ���Ă��Ȃ�
     */
    bool onChangeToActive();

    /**
     * ���������~�ɐ؂�ւ�������ǂ��� .
     * ���̃��\�b�h�͍��̂Ƃ���g���ǂ���͖�����������܂���B
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
     * �`�悷�邩�ǂ������ׂ�i��\���łȂ����ǂ����j
     * @return  bool true:�`��ł���(�\���Ώ�)�^false:�`��͂��Ȃ�(��\���Ώ�)
     */
    bool isVisible();

    /**
     * �m�[�h�̌��݂̌o�߃t���[�����擾����
     */
    DWORD getSurvivalFrame() {
        return _lifeframe;
    }

    bool willActivateAtNextFrame() {
        return _will_activate_at_next_frame_flg;
    }

    bool willPauseAtNextFrame() {
        return _wil_pause_at_next_frame_flg;
    }

    bool willHiddenAtNextFrame() {
        return _will_hidden_at_next_frame_flg;
    }

    bool willBeAliveAtNextFrame() {
        return _will_be_alive_at_next_frame_flg;
    }

    bool willMoveFirstAtNextFrame() {
        return _will_move_first_at_next_frame_flg;
    }

    bool willMoveLastAtNextFrame() {
        return _will_move_last_at_next_frame_flg;
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
            _frame_relative(0), _is_active_flg(true), _was_paused_flg(false), _was_hidden_flg(false), _can_live_flg(true),
            _will_activate_at_next_frame_flg(true), _wil_pause_at_next_frame_flg(false), _will_hidden_at_next_frame_flg(false),
            _will_be_alive_at_next_frame_flg(true), _will_move_first_at_next_frame_flg(false), _will_move_last_at_next_frame_flg(false),
            _will_activate_after_a_few_frames_flg(false), _frame_of_activation(0), _will_inactivate_after_a_few_frames_flg(false), _frame_of_inactivation(0),
            _on_change_to_active_flg(false), _on_change_to_inactive_flg(false) {
}

template<class T>
void GgafElement<T>::nextFrame() {
    TRACE("GgafElement::nextFrame BEGIN _lifeframe=" << _lifeframe << " name=" << GgafNode<T>::_name << " class="
            << GgafNode<T>::_class_name);

    //���̎���
    if (_dwGodFrame_when_goodbye == (askGod()->_godframe)) {
        _will_activate_at_next_frame_flg = false;
        _will_be_alive_at_next_frame_flg = false;
    }


    if (_will_move_last_at_next_frame_flg) {
        _will_move_last_at_next_frame_flg = false;
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
                    activateTreeNow();
                    _frame_of_activation = 0;
                    _will_activate_after_a_few_frames_flg = false;
                }
            } else if (_will_inactivate_after_a_few_frames_flg) {
                //�x��stop����
                if (_lifeframe == _frame_of_inactivation) {
                    inactivateTreeNow();
                    _frame_of_inactivation = 0;
                    _will_inactivate_after_a_few_frames_flg = false;
                }
            }
            if (_is_active_flg) {
                _lifeframe++;
            }
        }

        //�����A�񊈓��̏�ԕω���
        if (_is_active_flg == false && _will_activate_at_next_frame_flg) {
            _on_change_to_active_flg = true;
        } else if (_is_active_flg && _will_activate_at_next_frame_flg == false) {
            _on_change_to_inactive_flg = true;
        } else {
            _on_change_to_active_flg = false;
            _on_change_to_inactive_flg = false;
        }
        //�t���O�����𔽉f
        _is_active_flg   = _will_activate_at_next_frame_flg;
        _was_paused_flg  = _wil_pause_at_next_frame_flg;
        _was_hidden_flg = _will_hidden_at_next_frame_flg;
        _can_live_flg    = _will_be_alive_at_next_frame_flg;

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

        if (_will_move_first_at_next_frame_flg) {
            _will_move_first_at_next_frame_flg = false;
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

    //�����A�񊈓��̏�ԕω����R�[���o�b�N
    if (_on_change_to_active_flg) {
        onActive();
    } else if (_on_change_to_inactive_flg) {
        onInactive();
    }

    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        _frame_relative = 0;
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
void GgafElement<T>::drawPrior() {
    if(_was_initialize_flg == false) {
        initialize();
        _was_initialize_flg = true;
    }

    if (_is_active_flg && !_was_hidden_flg && _can_live_flg) {
        _frame_relative = 0;
        processDrawPrior();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->drawPrior();
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
void GgafElement<T>::drawMain() {
    if(_was_initialize_flg == false) {
        initialize();
        _was_initialize_flg = true;
    }

    if (_is_active_flg && !_was_hidden_flg && _can_live_flg) {
        _frame_relative = 0;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->drawMain();
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
void GgafElement<T>::drawTerminate() {
    if(_was_initialize_flg == false) {
        initialize();
        _was_initialize_flg = true;
    }

    if (_is_active_flg && !_was_hidden_flg && _can_live_flg) {
        _frame_relative = 0;
        processDrawTerminate();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->drawTerminate();
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
void GgafElement<T>::activateAlone() {
    if (_can_live_flg) {
        _will_activate_at_next_frame_flg = true;
        _wil_pause_at_next_frame_flg = false;
        _will_hidden_at_next_frame_flg = false;
    }
}

template<class T>
void GgafElement<T>::activateTree() {
    if (_can_live_flg) {
        _will_activate_at_next_frame_flg = true;
        _wil_pause_at_next_frame_flg = false;
        _will_hidden_at_next_frame_flg = false;
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
void GgafElement<T>::activateAloneNow() {
    if (_can_live_flg) {
        if (_is_active_flg == false) {
            _on_change_to_active_flg = true;
        } else {
            _on_change_to_active_flg = false;
        }
        _is_active_flg = true;
        _was_paused_flg = false;
        _was_hidden_flg = false;
        _will_activate_at_next_frame_flg = true;
        _wil_pause_at_next_frame_flg = false;
        _will_hidden_at_next_frame_flg = false;
    }
}

template<class T>
void GgafElement<T>::activateTreeNow() {
    if (_can_live_flg) {
        if (_is_active_flg == false) {
            _on_change_to_active_flg = true;
        } else {
            _on_change_to_active_flg = false;
        }
        _is_active_flg = true;
        _was_paused_flg = false;
        _was_hidden_flg = false;
        _will_activate_at_next_frame_flg = true;
        _wil_pause_at_next_frame_flg = false;
        _will_hidden_at_next_frame_flg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->activateTreeNow();
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
void GgafElement<T>::activateTreeAfter(DWORD prm_frame_offset) {
    _will_activate_after_a_few_frames_flg = true;
    _frame_of_activation = _lifeframe + prm_frame_offset;
}

template<class T>
void GgafElement<T>::inactivateAlone() {
    if (_can_live_flg) {
        _will_activate_at_next_frame_flg = false;
    }
}

template<class T>
void GgafElement<T>::inactivateTree() {
    if (_can_live_flg) {
        _will_activate_at_next_frame_flg = false;
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
void GgafElement<T>::inactivateTreeAfter(DWORD prm_frame_offset) {
    _will_inactivate_after_a_few_frames_flg = true;
    _frame_of_inactivation = _lifeframe + prm_frame_offset;
}

template<class T>
void GgafElement<T>::inactivateAloneNow() {
    if (_can_live_flg) {
        if (_is_active_flg) {
            _on_change_to_inactive_flg = true;
        } else {
            _on_change_to_inactive_flg = false;
        }
        _is_active_flg = false;
        _will_activate_at_next_frame_flg = false;
    }
}

template<class T>
void GgafElement<T>::inactivateTreeNow() {
    if (_can_live_flg) {
        if (_is_active_flg) {
            _on_change_to_inactive_flg = true;
        } else {
            _on_change_to_inactive_flg = false;
        }
        _is_active_flg = false;
        _will_activate_at_next_frame_flg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->inactivateTreeNow();
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
        _wil_pause_at_next_frame_flg = true;
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
void GgafElement<T>::pauseAlone() {
    if (_can_live_flg) {
        _wil_pause_at_next_frame_flg = true;
    }
}

template<class T>
void GgafElement<T>::pauseTreeNow() {
    if (_can_live_flg) {
        _was_paused_flg = true;
        _wil_pause_at_next_frame_flg = true;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->pauseTreeNow();
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
void GgafElement<T>::pauseAloneNow() {
    if (_can_live_flg) {
        _was_paused_flg = true;
        _wil_pause_at_next_frame_flg = true;
    }
}

template<class T>
void GgafElement<T>::unpauseTree() {
    if (_can_live_flg) {
        _wil_pause_at_next_frame_flg = false;
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
void GgafElement<T>::unpauseAlone() {
    if (_can_live_flg) {
        _wil_pause_at_next_frame_flg = false;
    }
}

template<class T>
void GgafElement<T>::unpauseTreeNow() {
    if (_can_live_flg) {
        _was_paused_flg = false;
        _wil_pause_at_next_frame_flg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->unpauseTreeNow();
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
void GgafElement<T>::unpauseAloneNow() {
    if (_can_live_flg) {
        _was_paused_flg = false;
        _wil_pause_at_next_frame_flg = false;
    }
}

template<class T>
void GgafElement<T>::hideTree() {
    if (_can_live_flg) {
        _will_hidden_at_next_frame_flg = true;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->hideTree();
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
void GgafElement<T>::hideAlone() {
    if (_can_live_flg) {
        _will_hidden_at_next_frame_flg = true;
    }
}

template<class T>
void GgafElement<T>::hideTreeNow() {
    if (_can_live_flg) {
        _was_hidden_flg = true;
        _will_hidden_at_next_frame_flg = true;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->hideTreeNow();
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
void GgafElement<T>::hideAloneNow() {
    if (_can_live_flg) {
        _was_hidden_flg = true;
        _will_hidden_at_next_frame_flg = true;
    }
}

template<class T>
void GgafElement<T>::showTree() {
    if (_can_live_flg) {
        _will_hidden_at_next_frame_flg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->showTree();
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
void GgafElement<T>::showAlone() {
    if (_can_live_flg) {
        _will_hidden_at_next_frame_flg = false;
    }
}

template<class T>
void GgafElement<T>::showTreeNow() {
    if (_can_live_flg) {
        _was_hidden_flg = false;
        _will_hidden_at_next_frame_flg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->showTreeNow();
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
void GgafElement<T>::showAloneNow() {
    if (_can_live_flg) {
        _was_hidden_flg = false;
        _will_hidden_at_next_frame_flg = false;
    }
}
template<class T>
void GgafElement<T>::arigatou_sayounara(DWORD prm_frame_offset) {

    _dwGodFrame_when_goodbye = (askGod()->_godframe) + prm_frame_offset + 1;
    if (SUPER::_pSubFirst != NULL) {
        T* pElementTemp = SUPER::_pSubFirst;
        while(true) {
            pElementTemp->arigatou_sayounara(prm_frame_offset);
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
    if (_can_live_flg && _is_active_flg && !_was_hidden_flg) {
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
        return SUPER::breakAwayFromTree();
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
