#ifndef GGAFELEMENT_H_
#define GGAFELEMENT_H_
namespace GgafCore {

#define SUPER GgafCore::GgafNode<T>

/**
 * GgafNode�ɁA�^�X�N�V�X�e���y�їl�X�ȏ�ԊǗ��i�t���O�Ǘ��j��ǉ��B .
 * ���t���[���A��_(GgafGod)�͐��E(GgafWorld)�ɁA���̃��\�b�h���ŌĂяo���d�g�݂ɂȂ��Ă���B���E(GgafWorld)���{template���������Ă���B<BR>
 * nextFrame() > behave() > judge() > [drawPrior() > drawMain() > drawTerminate()] > finally() <BR>
 * ��L�̓��AnextFrame()�Afinally() �͖��t���[�����s�����B<BR>
 * behave()�Ajudge() �͊�����ԃt���O(_isActiveFlg)�� true�A���A�ꎞ��~�t���O(_wasPausedFlg)�� false �̏ꍇ���s�����B<BR>
 * drawPrior()�AdrawMain()�AdrawTerminate() �́A���t���[���܂ł̎c���Ԃɗ]�T������A���ꎞ��\���t���O(_wasHiddenFlg) �� false �̏ꍇ<BR>
 * ���s�����B���t���[���܂ł̎c���Ԃɗ]�T�������ꍇ�A�_�͂��̂R���\�b�h���X�L�b�v���邪�AMAX_SKIP_FRAME �t���[���ɂP��͎��s����B<BR>
 * ��L�� nextFrame() �` finally() �̃I�[�o�[���C�h�͔񐄏��B�I�[�o�[���C�h�p�ɏ������z(processXxxxxx()) ��p�ӂ��Ă���B<BR>
 * initialize() �́A��L�� nextFrame() �` finally() �����ꂩ���Ăяo���O�ɃC���X�^���X���ƂɂP�񂾂��Ă΂��d�g�݂ɂȂ��Ă���B<BR>
 * �A���A�����t���O(_canLiveFlg)��false�̏ꍇ�idelete�����j�́AnextFrame() �` finally() �͑S�Ď��s����Ȃ��B<BR>
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
    bool _wasInitializedFlg;

    /** �]�� */
    DWORD _dwGodFrame_when_goodbye;
    /** �m�[�h���a��(addSub���ꂽ�j������̃t���[�� */
    DWORD _lifeframe;
    /** ���΃t���[���v�Z�p */
    DWORD _dwFrame_relative;
    /** �m�[�h�����t���O */
    bool _isActiveFlg;
    /** �ꎞ��~�t���O */
    bool _wasPausedFlg;
    /** �ꎞ��\���t���O */
    bool _wasHiddenFlg;
    /** �m�[�h�����t���O */
    bool _canLiveFlg;

    /** ���t���[���m�[�h�����\��t���O�A���t���[���̃t���[�����Z�� _isActiveFlg �ɔ��f����� */
    bool _willActivateAtNextFrameFlg;
    /** ���t���[���ꎞ��~�\��t���O�A���t���[���̃t���[�����Z�� _wasPausedFlg �ɔ��f����� */
    bool _willPauseAtNextFrameFlg;
    /** ���t���[���ꎞ��\���\��t���O�A���t���[���̃t���[�����Z�� _wasHiddenFlg �ɔ��f�����  */
    bool _willBlindAtNextFrameFlg;
    /** ���t���[�������\��t���O�A���t���[���̃t���[�����Z�� _canLiveFlg �ɐݒ肳��� */
    bool _willBeAliveAtNextFrameFlg;

    /** �擪�m�[�h�Ɉړ��\��t���O�A���t���[���̃t���[�����Z���ɁA���m�[�h���擪�m�[�h�Ɉړ����� */
    bool _willMoveFirstAtNextFrameFlg;
    /** �����m�[�h�Ɉړ��\��t���O�A���t���[���̃t���[�����Z���ɁA���m�[�h�������m�[�h�Ɉړ����� */
    bool _willMoveLastAtNextFrameFlg;

    /** ���ƂŊ����\��t���O */
    bool _willActivateAfterFrameFlg;
    /** ���ƂŊ����܂ł̎c�t���[�����i�_�t���[���ƈ�v�����犈���j */
    DWORD _dwGodFremeWhenActive;

    /** ���ƂŔ񊈓��\��t���O */
    bool _willInactivateAfterFrameFlg;
    /** ���ƂŒ�~�̎c�t���[�����i�_�t���[���ƈ�v�������~�j */
    DWORD _dwGodFremeWhenInactivate;

    /** �m�[�h�������ɐ؂�ւ����(_isActiveFlg �� false �� true)�u�ԂɂP�t���[�������Z�b�g�����t���O */
    bool _switchedToActiveFlg;
    /** �m�[�h����~�ɐ؂�ւ����(_isActiveFlg �� true �� false)�u�ԂɂP�t���[�������Z�b�g�����t���O */
    bool _switchedToInactiveFlg;

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
     * �z���m�[�h�̒��Ƀm�[�h�����t���O(_canLiveFlg)�� false �ɂȂ��Ă���m�[�h������� prm_num_cleaning ���� delete ����B<BR>
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
     * _willActivateAtNextFrameFlg, _willPauseAtNextFrameFlg, _willBlindAtNextFrameFlg, _willBeAliveAtNextFrameFlg ��<BR>
     * _isActiveFlg, _wasPausedFlg, _wasHiddenFlg, _canLiveFlg �ɔ��f�i�R�s�[�j����B<BR>
     * �܂��A_willMoveFirstAtNextFrameFlg, _willMoveLastAtNextFrameFlg �� true �̏ꍇ�́A<BR>
     * ���ꂼ��A���m�[�h�̐擪�m�[�h�ւ̈ړ��A�����m�[�h�ւ̈ړ����������s�����B<BR>
     * ���̌�A�z���m�[�h�S�Ă� nextFrame() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��Abehave()�����s����B<BR>
     */
    virtual void nextFrame();

    /**
     * �m�[�h�̃t���[�����̐U�镑������ .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �i_isActiveFlg && !_wasPausedFlg && _canLiveFlg�j�̏ꍇ <BR>
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
     * (�܂� _isActiveFlg && !_wasPausedFlg && _canLiveFlg)�̏ꍇ <BR>
     * processJudgement() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� judge() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��A���t���[���܂ł̎c���Ԃɗ]�T������� drawPrior()�A
     * ������� finally()�����s����B<BR>
     */
    virtual void judge();

    /**
     * �m�[�h�̃t���[�����̕`�掖�O�����i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��\���t���O���A���Z�b�g<BR>
     * (�܂� _isActiveFlg && !_wasHiddenFlg && _canLiveFlg)�̏ꍇ <BR>
     * processDrawPrior() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� drawPrior() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��AdrawMain() �����s����B<BR>
     */
    virtual void drawPrior();

    /**
     * �m�[�h�̃t���[�����̕`��{�����i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��\���t���O���A���Z�b�g<BR>
     * (�܂� _isActiveFlg && !_wasHiddenFlg && _canLiveFlg)�̏ꍇ <BR>
     * processDrawMain() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� drawMain() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��AdrawTerminate() �����s����B<BR>
     */
    virtual void drawMain();

    /**
     * �m�[�h�̃t���[�����̕`�掖�㏈���i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��\���t���O���A���Z�b�g<BR>
     * (�܂� _isActiveFlg && !_wasHiddenFlg && _canLiveFlg)�̏ꍇ <BR>
     * processTerminate() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� drawTerminate() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��Afinally() �����s����B<BR>
     */
    virtual void drawTerminate();

    /**
     * �m�[�h�̃t���[�����̍ŏI���� .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �i_isActiveFlg && !_wasPausedFlg && _canLiveFlg�j�̏ꍇ <BR>
     * processFinally() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� finally() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��A���t���[���܂ł̎c���Ԃɗ]�T������� cleane() �����s����B<BR>
     */
    virtual void finally();

    /**
     * �m�[�h�̉����̏���(�t���[�����ł͂Ȃ�) .
     * �����t���O���Z�b�g�A(�܂� _isActiveFlg)�̏ꍇ <BR>
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
     * @param prm_dwFrameOffset �x���t���[����(1�`)
     */
    void activateTreeAfter(DWORD prm_dwFrameOffset);
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
     * @param prm_dwFrameOffset �x���t���[����(1�`)
     */
    void inactivateTreeAfter(DWORD prm_dwFrameOffset);
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
     * �����I���Ƃ͋�̓I�ɂ́A�\���t���O(_wasHiddenFlg)�A�U�镑���t���O(_isActiveFlg)�A�����t���O(_canLiveFlg) ���A
     * ���t���[������A���Z�b�g���鎖�ł���B<BR>
     * _canLiveFlg ���A���Z�b�g����邱�Ƃɂ��A�_(GgafGod)���������Ԃ̗]�T�̂��鎞�� cleane() ���\�b�h�ɂ��
     * delete �̑ΏۂƂȂ�B<BR>
     * ���������āA�{�����o�֐������s���Ă��A�w����t���[�����x�ł́A�܂�delete�͍s�Ȃ��Ȃ��B
     * �C���X�^���X�������ɉ������Ȃ����Ƃɒ��ӁB���͂���Ȃ炷�邾���B<BR>
     * ���ӁF����Ȃ炵����w����t���[�����x�ɁA _canLiveFlg ���Z�b�g�������Ă��ʖڂł��B<BR>
     * ����͖{���\�b�h�ŁAGgafGarbageRootActor�ɏ������邽�߂ł��B<BR>
     */
    void arigatou_sayounara(DWORD prm_dwFrameOffset = 0);

    /**
     * ���c���[�m�[�h���ŏI�m�[�h�Ɉړ����� .
     * ���t���[���̐擪����(nextFrame())�Ŏ��c���[�m�[�h���Z��m�[�h�O���[�v�̍ŏI�ɃV�t�g����B<BR>
     * <B>[����]</B>�����ɏ��J�菈�������s�����킯�ł͂���܂���B<BR>
     */
    void moveLast() {
        _willMoveLastAtNextFrameFlg = true;
    }

    /**
     * ���c���[�m�[�h��擪�m�[�h�Ɉړ����� .
     * ���t���[���̐擪����(nextFrame())�Ŏ��c���[�m�[�h���Z��m�[�h�O���[�v�̐擪�ɃV�t�g����B<BR>
     * <B>[����]</B>�����ɏ��J�菈�������s�����킯�ł͂���܂���B<BR>
     */
    void moveFirst() {
        _willMoveFirstAtNextFrameFlg = true;
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
    bool switchedToActive();

    /**
     * ���������~�ɐ؂�ւ�������ǂ��� .
     * ���̃��\�b�h�͍��̂Ƃ���g���ǂ���͖�����������܂���B
     * @return  bool true:�؂�ւ�����^false:�؂�ւ���Ă��Ȃ�
     */
    bool switchedToInactive();

    /**
     * �����\�����ׂ�
     * @return  bool true:�����\�^false:�����s��
     */
    bool canLive() {
        return _canLiveFlg;
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
    DWORD getFrame() {
        return _lifeframe;
    }

    bool willActivateNextFrame() {
        return _willActivateAtNextFrameFlg;
    }

    bool willPauseNextFrame() {
        return _willPauseAtNextFrameFlg;
    }

    bool willBlindNextFrame() {
        return _willBlindAtNextFrameFlg;
    }

    bool willBeAliveNextFrame() {
        return _willBeAliveAtNextFrameFlg;
    }

    bool willMoveFirstNextFrame() {
        return _willMoveFirstAtNextFrameFlg;
    }

    bool willMoveLastNextFrame() {
        return _willMoveLastAtNextFrameFlg;
    }

    /**
     * ���Όo�߃t���[���̔���B
     * ���O�� relativeFrame(int) ���s���i���ʂ�true/false�Ɋւ�炸�j�̃t���[��������̌o�߃t���[�����ɒB���������肷��B
     * ���ӁF����q���������ɂ��ArelativeFrame(int) ���Ăяo�����񐔂��ω�����ꍇ�A���Όo�߃t���[�����ω�����B
     * @param   prm_dwFrame_relative    �o�߃t���[����
     * @return  bool    true:�o�߃t���[�����ɒB����/false:�B���Ă��Ȃ�
     */
    bool relativeFrame(DWORD prm_dwFrame_relative);

};

///////////////////////////////////////////////////////////////// ��������͎�����

template<class T>
GgafElement<T>::GgafElement(const char* prm_name) : SUPER(prm_name),
            _pGod(NULL), _wasInitializedFlg(false), _dwGodFrame_when_goodbye(MAXDWORD), _lifeframe(0),
            _dwFrame_relative(0), _isActiveFlg(true), _wasPausedFlg(false), _wasHiddenFlg(false), _canLiveFlg(true),
            _willActivateAtNextFrameFlg(true), _willPauseAtNextFrameFlg(false), _willBlindAtNextFrameFlg(false),
            _willBeAliveAtNextFrameFlg(true), _willMoveFirstAtNextFrameFlg(false), _willMoveLastAtNextFrameFlg(false),
            _willActivateAfterFrameFlg(false), _dwGodFremeWhenActive(0), _willInactivateAfterFrameFlg(false), _dwGodFremeWhenInactivate(0),
            _switchedToActiveFlg(false), _switchedToInactiveFlg(false) {
}

template<class T>
void GgafElement<T>::nextFrame() {
    TRACE("GgafElement::nextFrame BEGIN _lifeframe=" << _lifeframe << " name=" << GgafNode<T>::_name << " class="
            << GgafNode<T>::_class_name);

    //���̎���
    if (_dwGodFrame_when_goodbye == (askGod()->_dwFrame_God)) {
        _willActivateAtNextFrameFlg = false;
        _willBeAliveAtNextFrameFlg = false;
    }


    if (_willMoveLastAtNextFrameFlg) {
        _willMoveLastAtNextFrameFlg = false;
        SUPER::moveLast();
    } else {

        if(_wasInitializedFlg == false) {
            initialize();
            _wasInitializedFlg = true;
        }

        if (_canLiveFlg) {
            if (_willActivateAfterFrameFlg) {
                //�x��play����
                if (askGod()->_dwFrame_God >= _dwGodFremeWhenActive) {
                    activateTreeNow();
                    _dwGodFremeWhenActive = 0;
                    _willActivateAfterFrameFlg = false;
                }
            } else if (_willInactivateAfterFrameFlg) {
                //�x��stop����
                if (askGod()->_dwFrame_God == _dwGodFremeWhenInactivate) {
                    inactivateTreeNow();
                    _dwGodFremeWhenInactivate = 0;
                    _willInactivateAfterFrameFlg = false;
                }
            }
            if (_isActiveFlg) {
                _lifeframe++;
            }
        }

        //�����A�񊈓��̏�ԕω���
        if (_isActiveFlg == false && _willActivateAtNextFrameFlg) {
            _switchedToActiveFlg = true;
        } else if (_isActiveFlg && _willActivateAtNextFrameFlg == false) {
            _switchedToInactiveFlg = true;
        } else {
            _switchedToActiveFlg = false;
            _switchedToInactiveFlg = false;
        }
        //�t���O�����𔽉f
        _isActiveFlg   = _willActivateAtNextFrameFlg;
        _wasPausedFlg  = _willPauseAtNextFrameFlg;
        _wasHiddenFlg = _willBlindAtNextFrameFlg;
        _canLiveFlg    = _willBeAliveAtNextFrameFlg;

        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                if (pElementTemp->_isLastFlg) {
                    pElementTemp->nextFrame();
                    if (pElementTemp->_canLiveFlg == false) {
                        GgafFactory::_pGarbageBox->add(pElementTemp);
                    }
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                    pElementTemp->SUPER::_pPrev->nextFrame();
                    if (pElementTemp->SUPER::_pPrev->_canLiveFlg == false) {
                        GgafFactory::_pGarbageBox->add(pElementTemp->SUPER::_pPrev);
                    }
                }
            }
        }

        if (_willMoveFirstAtNextFrameFlg) {
            _willMoveFirstAtNextFrameFlg = false;
            SUPER::moveFirst();
        }

    }
    TRACE("GgafElement::nextFrame END _lifeframe="<<_lifeframe<<" name="<<GgafNode<T>::_name<<" class="<<GgafNode<T>::_class_name);
}

template<class T>
void GgafElement<T>::behave() {
    if(_wasInitializedFlg == false) {
        initialize();
        _wasInitializedFlg = true;
    }

    //�����A�񊈓��̏�ԕω����R�[���o�b�N
    if (_switchedToActiveFlg) {
        onActive();
    } else if (_switchedToInactiveFlg) {
        onInactive();
    }

    if (_isActiveFlg && !_wasPausedFlg && _canLiveFlg) {
        _dwFrame_relative = 0;
        processBehavior();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->behave();
                if (pElementTemp->_isLastFlg) {
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
    if(_wasInitializedFlg == false) {
        initialize();
        _wasInitializedFlg = true;
    }

    if (_isActiveFlg && !_wasPausedFlg && _canLiveFlg) {
        _dwFrame_relative = 0;
        processJudgement();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->judge();
                if (pElementTemp->_isLastFlg) {
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
    if(_wasInitializedFlg == false) {
        initialize();
        _wasInitializedFlg = true;
    }

    if (_isActiveFlg && !_wasHiddenFlg && _canLiveFlg) {
        _dwFrame_relative = 0;
        processDrawPrior();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->drawPrior();
                if (pElementTemp->_isLastFlg) {
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
    if(_wasInitializedFlg == false) {
        initialize();
        _wasInitializedFlg = true;
    }

    if (_isActiveFlg && !_wasHiddenFlg && _canLiveFlg) {
        _dwFrame_relative = 0;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->drawMain();
                if (pElementTemp->_isLastFlg) {
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
    if(_wasInitializedFlg == false) {
        initialize();
        _wasInitializedFlg = true;
    }

    if (_isActiveFlg && !_wasHiddenFlg && _canLiveFlg) {
        _dwFrame_relative = 0;
        processDrawTerminate();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->drawTerminate();
                if (pElementTemp->_isLastFlg) {
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
    if(_wasInitializedFlg == false) {
        initialize();
        _wasInitializedFlg = true;
    }

    if (_canLiveFlg) {
        _dwFrame_relative = 0;
        processHappen(prm_no);
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->happen(prm_no);
                if (pElementTemp->_isLastFlg) {
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
    if(_wasInitializedFlg == false) {
        initialize();
        _wasInitializedFlg = true;
    }

    if (_isActiveFlg && !_wasPausedFlg && _canLiveFlg) {
        _dwFrame_relative = 0;
        processFinal();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->finally();
                if (pElementTemp->_isLastFlg) {
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
    if (_canLiveFlg) {
        _willActivateAtNextFrameFlg = true;
        _willPauseAtNextFrameFlg = false;
        _willBlindAtNextFrameFlg = false;
    }
}

template<class T>
void GgafElement<T>::activateTree() {
    if (_canLiveFlg) {
        _willActivateAtNextFrameFlg = true;
        _willPauseAtNextFrameFlg = false;
        _willBlindAtNextFrameFlg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->activateTree();
                if (pElementTemp->_isLastFlg) {
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
    if (_canLiveFlg) {
        if (_isActiveFlg == false) {
            _switchedToActiveFlg = true;
        } else {
            _switchedToActiveFlg = false;
        }
        _isActiveFlg = true;
        _wasPausedFlg = false;
        _wasHiddenFlg = false;
        _willActivateAtNextFrameFlg = true;
        _willPauseAtNextFrameFlg = false;
        _willBlindAtNextFrameFlg = false;
    }
}

template<class T>
void GgafElement<T>::activateTreeNow() {
    if (_canLiveFlg) {
        if (_isActiveFlg == false) {
            _switchedToActiveFlg = true;
        } else {
            _switchedToActiveFlg = false;
        }
        _isActiveFlg = true;
        _wasPausedFlg = false;
        _wasHiddenFlg = false;
        _willActivateAtNextFrameFlg = true;
        _willPauseAtNextFrameFlg = false;
        _willBlindAtNextFrameFlg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->activateTreeNow();
                if (pElementTemp->_isLastFlg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::activateTreeAfter(DWORD prm_dwFrameOffset) {
    _willActivateAfterFrameFlg = true;
    _dwGodFremeWhenActive = askGod()->_dwFrame_God + prm_dwFrameOffset;
}

template<class T>
void GgafElement<T>::inactivateAlone() {
    if (_canLiveFlg) {
        _willActivateAtNextFrameFlg = false;
    }
}

template<class T>
void GgafElement<T>::inactivateTree() {
    if (_canLiveFlg) {
        _willActivateAtNextFrameFlg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->inactivateTree();
                if (pElementTemp->_isLastFlg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::inactivateTreeAfter(DWORD prm_dwFrameOffset) {
    _willInactivateAfterFrameFlg = true;
    _dwGodFremeWhenInactivate = askGod()->_dwFrame_God + prm_dwFrameOffset;
}

template<class T>
void GgafElement<T>::inactivateAloneNow() {
    if (_canLiveFlg) {
        if (_isActiveFlg) {
            _switchedToInactiveFlg = true;
        } else {
            _switchedToInactiveFlg = false;
        }
        _isActiveFlg = false;
        _willActivateAtNextFrameFlg = false;
    }
}

template<class T>
void GgafElement<T>::inactivateTreeNow() {
    if (_canLiveFlg) {
        if (_isActiveFlg) {
            _switchedToInactiveFlg = true;
        } else {
            _switchedToInactiveFlg = false;
        }
        _isActiveFlg = false;
        _willActivateAtNextFrameFlg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->inactivateTreeNow();
                if (pElementTemp->_isLastFlg) {
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
    if (_canLiveFlg) {
        _willPauseAtNextFrameFlg = true;
        //_isActiveFlg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->pauseTree();
                if (pElementTemp->_isLastFlg) {
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
    if (_canLiveFlg) {
        _willPauseAtNextFrameFlg = true;
    }
}

template<class T>
void GgafElement<T>::pauseTreeNow() {
    if (_canLiveFlg) {
        _wasPausedFlg = true;
        _willPauseAtNextFrameFlg = true;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->pauseTreeNow();
                if (pElementTemp->_isLastFlg) {
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
    if (_canLiveFlg) {
        _wasPausedFlg = true;
        _willPauseAtNextFrameFlg = true;
    }
}

template<class T>
void GgafElement<T>::unpauseTree() {
    if (_canLiveFlg) {
        _willPauseAtNextFrameFlg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->unpauseTree();
                if (pElementTemp->_isLastFlg) {
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
    if (_canLiveFlg) {
        _willPauseAtNextFrameFlg = false;
    }
}

template<class T>
void GgafElement<T>::unpauseTreeNow() {
    if (_canLiveFlg) {
        _wasPausedFlg = false;
        _willPauseAtNextFrameFlg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->unpauseTreeNow();
                if (pElementTemp->_isLastFlg) {
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
    if (_canLiveFlg) {
        _wasPausedFlg = false;
        _willPauseAtNextFrameFlg = false;
    }
}

template<class T>
void GgafElement<T>::hideTree() {
    if (_canLiveFlg) {
        _willBlindAtNextFrameFlg = true;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->hideTree();
                if (pElementTemp->_isLastFlg) {
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
    if (_canLiveFlg) {
        _willBlindAtNextFrameFlg = true;
    }
}

template<class T>
void GgafElement<T>::hideTreeNow() {
    if (_canLiveFlg) {
        _wasHiddenFlg = true;
        _willBlindAtNextFrameFlg = true;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->hideTreeNow();
                if (pElementTemp->_isLastFlg) {
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
    if (_canLiveFlg) {
        _wasHiddenFlg = true;
        _willBlindAtNextFrameFlg = true;
    }
}

template<class T>
void GgafElement<T>::showTree() {
    if (_canLiveFlg) {
        _willBlindAtNextFrameFlg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->showTree();
                if (pElementTemp->_isLastFlg) {
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
    if (_canLiveFlg) {
        _willBlindAtNextFrameFlg = false;
    }
}

template<class T>
void GgafElement<T>::showTreeNow() {
    if (_canLiveFlg) {
        _wasHiddenFlg = false;
        _willBlindAtNextFrameFlg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->showTreeNow();
                if (pElementTemp->_isLastFlg) {
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
    if (_canLiveFlg) {
        _wasHiddenFlg = false;
        _willBlindAtNextFrameFlg = false;
    }
}
template<class T>
void GgafElement<T>::arigatou_sayounara(DWORD prm_dwFrameOffset) {

    _dwGodFrame_when_goodbye = (askGod()->_dwFrame_God) + prm_dwFrameOffset + 1;
    if (SUPER::_pSubFirst != NULL) {
        T* pElementTemp = SUPER::_pSubFirst;
        while(true) {
            pElementTemp->arigatou_sayounara(prm_dwFrameOffset);
            if (pElementTemp->_isLastFlg) {
                break;
            } else {
                pElementTemp = pElementTemp->SUPER::_pNext;
            }
        }
    }
}


template<class T>
bool GgafElement<T>::isActive() {
    if (_canLiveFlg && _isActiveFlg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::switchedToActive() {
    if (_canLiveFlg && _switchedToActiveFlg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::switchedToInactive() {
    if (_canLiveFlg && _switchedToInactiveFlg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::isVisible() {
    if (_canLiveFlg && _isActiveFlg && !_wasHiddenFlg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::isBehaving() {
    if (_canLiveFlg && _isActiveFlg && !_wasPausedFlg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::relativeFrame(DWORD prm_dwFrame_relative) {
    _dwFrame_relative += prm_dwFrame_relative;
    if (_lifeframe == _dwFrame_relative) {
        return true;
    } else {
        return false;
    }
}


template<class T>
T* GgafElement<T>::becomeIndependent() {
    if (_canLiveFlg) {
        return SUPER::tear();
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

        if (pElementTemp->_isFirstFlg) { //�Ō�̈��
            if (pElementTemp->_pSubFirst) {
                //�q�̎q���܂��̂��Ă���ꍇ����ɂ�����
                pElementTemp->cleane(prm_num_cleaning);
                if (GgafFactory::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            if (pElementTemp->_canLiveFlg == false) {
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
            if (pWk->_canLiveFlg == false) {
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
