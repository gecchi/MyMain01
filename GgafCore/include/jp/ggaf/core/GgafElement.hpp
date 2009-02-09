#ifndef GGAFELEMENT_H_
#define GGAFELEMENT_H_
namespace GgafCore {

#define SUPER GgafCore::GgafNode<T>

/**
 * GgafNode�ɁA�^�X�N�V�X�e���y�їl�X�ȏ�ԊǗ��i�t���O�Ǘ��j��ǉ��B .
 * ���t���[���A��_(GgafGod)�͐��E(GgafWorld)�ɁA���̃��\�b�h���ŌĂяo���d�g�݂ɂȂ��Ă���B���E(GgafWorld)���{template���������Ă���B<BR>
 * nextFrame() > behave() > judge() > [drawPrior() > drawMain() > drawTerminate()] > finally() <BR>
 * ��L�̓��AnextFrame()�Afinally() �͖��t���[�����s�����B<BR>
 * behave()�Ajudge() �͊�����ԃt���O(_isActive)�� true�A���A�ꎞ��~�t���O(_wasPaused)�� false �̏ꍇ���s�����B<BR>
 * drawPrior()�AdrawMain()�AdrawTerminate() �́A���t���[���܂ł̎c���Ԃɗ]�T������A���ꎞ��\���t���O(_wasBlinded) �� false �̏ꍇ<BR>
 * ���s�����B���t���[���܂ł̎c���Ԃɗ]�T�������ꍇ�A�_�͂��̂R���\�b�h���X�L�b�v���邪�AMAX_SKIP_FRAME �t���[���ɂP��͎��s����B<BR>
 * ��L�� nextFrame() �` finally() �̃I�[�o�[���C�h�͔񐄏��B�I�[�o�[���C�h�p�ɏ������z(processXxxxxx()) ��p�ӂ��Ă���B<BR>
 * initialize() �́A��L�� nextFrame() �` finally() �����ꂩ���Ăяo���O�ɃC���X�^���X���ƂɂP�񂾂��Ă΂��d�g�݂ɂȂ��Ă���B<BR>
 * �A���A�����t���O(_isAlive)��false�̏ꍇ�idelete�����j�́AnextFrame() �` finally() �͑S�Ď��s����Ȃ��B<BR>
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafElement : public GgafNode<T> {

protected:

    /** �_�ւ̋ߓ� */
    GgafGod* _pGod;
    /** initialize���s��ꂽ�ǂ����̃t���O(true=�s��ꂽ) */
    bool _wasInitialized;

public:
    /** �]�� */
    DWORD _dwGodFrame_ofDeath;
    /** �m�[�h���a��(addSub���ꂽ�j������̃t���[�� */
    DWORD _dwFrame;
    /** ���΃t���[���v�Z�p */
    DWORD _dwFrame_relative;
    /** �m�[�h�����t���O */
    bool _isActive;
    /** �ꎞ��~�t���O */
    bool _wasPaused;
    /** �ꎞ��\���t���O */
    bool _wasBlinded;
    /** �m�[�h�����t���O */
    bool _isAlive;

    /** ���t���[���m�[�h�����\��t���O�A���t���[���̃t���[�����Z�� _isActive �ɔ��f����� */
    bool _willActNextFrame;
    /** ���t���[���ꎞ��~�\��t���O�A���t���[���̃t���[�����Z�� _wasPaused �ɔ��f����� */
    bool _willPauseNextFrame;
    /** ���t���[���ꎞ��\���\��t���O�A���t���[���̃t���[�����Z�� _wasBlinded �ɔ��f�����  */
    bool _willBlindNextFrame;
    /** ���t���[�������\��t���O�A���t���[���̃t���[�����Z�� _isAlive �ɐݒ肳��� */
    bool _willBeAliveNextFrame;

    /** �擪�m�[�h�Ɉړ��\��t���O�A���t���[���̃t���[�����Z���ɁA���m�[�h���擪�m�[�h�Ɉړ����� */
    bool _willMoveFirstNextFrame;
    /** �����m�[�h�Ɉړ��\��t���O�A���t���[���̃t���[�����Z���ɁA���m�[�h�������m�[�h�Ɉړ����� */
    bool _willMoveLastNextFrame;

    /** ���ƂŊ����\��t���O */
    bool _willActAfterFrame;
    /** ���ƂŊ����܂ł̎c�t���[�����i�_�t���[���ƈ�v�����犈���j */
    DWORD _dwGodFremeWhenAct;

    /** ���ƂŔ񊈓��\��t���O */
    bool _willRefrainAfterFrame;
    /** ���ƂŒ�~�̎c�t���[�����i�_�t���[���ƈ�v�������~�j */
    DWORD _dwGodFremeWhenRefrain;

    /** �m�[�h�������ɐ؂�ւ����(_isActive �� false �� true)�u�ԂɂP�t���[�������Z�b�g�����t���O */
    bool _switchedToAct;
    /** �m�[�h����~�ɐ؂�ւ����(_isActive �� true �� false)�u�ԂɂP�t���[�������Z�b�g�����t���O */
    bool _switchedToRefrain;

    /** �`�悳��܂����t���O */
    bool _wasExecuted_processDrawMain;

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
     * �_���������Ԃɗ]�T���ł��Ƃ����ɌĂ΂��B<BR>
     * �z���m�[�h�̒��Ƀm�[�h�����t���O(_isAlive)�� false �ɂȂ��Ă���m�[�h������� prm_iNumCleanNode ���� delete ����B<BR>
     * @param prm_iNumCleanNode �������I�u�W�F�N�g��
     */
    virtual void cleane(int prm_iNumCleanNode);

    /**
     * �m�[�h�������� .
     * �C���X�^���X������AnextFrame(),behave(),judge(),drawPrior(),drawMain(),drawTerminate(),happen(int),finally() ��
     * ���ꂩ���Ăяo���ꂽ���A�ŏ��ɕK���P�񂾂��Ăяo�����B<BR>
     */
    virtual void initialize() = 0;

    /**
     * �m�[�h�̃t���[�������Z�ƁA�t���[���J�n�ɂ������Ă̂��낢��ȏ������� .
     * _willActNextFrame, _willPauseNextFrame, _willBlindNextFrame, _willBeAliveNextFrame ��<BR>
     * _isActive, _wasPaused, _wasBlinded, _isAlive �ɔ��f�i�R�s�[�j����B<BR>
     * �܂��A_willMoveFirstNextFrame, _willMoveLastNextFrame �� true �̏ꍇ�́A<BR>
     * ���ꂼ��A���m�[�h�̐擪�m�[�h�ւ̈ړ��A�����m�[�h�ւ̈ړ����������s�����B<BR>
     * ���̌�A�z���m�[�h�S�Ă� nextFrame() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��Abehave()�����s����B<BR>
     */
    virtual void nextFrame();

    /**
     * �m�[�h�̃t���[�����̐U�镑������ .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �i_isActive && !_wasPaused && _isAlive�j�̏ꍇ <BR>
     * processBehavior() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� behave() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��Ajudge()�����s����B<BR>
     */
    virtual void behave();

    /**
     * �񊈓����������ɐ؂�ւ�������̏��� .
     * �񊈓���Ԃ��犈����Ԃɕω������Ƃ��ɂP��R�[���o�b�N�����B<BR>
     * �K�v�ɉ����ăI�[�o�[���C�h����B<BR>
     */
    virtual void onAct() {
    }

    /**
     * �������񊈓����ɐ؂�ւ�������̏��� .������ .
     * ������Ԃ���񊈓���Ԃɕω������Ƃ��ɂP��R�[���o�b�N�����B<BR>
     * �K�v�ɉ����ăI�[�o�[���C�h����B<BR>
     */
    virtual void onRefrain() {
    }

    /**
     * �m�[�h�̃t���[�����̔��菈�� .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * (�܂� _isActive && !_wasPaused && _isAlive)�̏ꍇ <BR>
     * processJudgement() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� judge() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��A���t���[���܂ł̎c���Ԃɗ]�T������� drawPrior()�A
     * ������� finally()�����s����B<BR>
     */
    virtual void judge();

    /**
     * �m�[�h�̃t���[�����̕`�掖�O�����i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��\���t���O���A���Z�b�g<BR>
     * (�܂� _isActive && !_wasBlinded && _isAlive)�̏ꍇ <BR>
     * processDrawPrior() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� drawPrior() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��AdrawMain() �����s����B<BR>
     */
    virtual void drawPrior();

    /**
     * �m�[�h�̃t���[�����̕`��{�����i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��\���t���O���A���Z�b�g<BR>
     * (�܂� _isActive && !_wasBlinded && _isAlive)�̏ꍇ <BR>
     * processDrawMain() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� drawMain() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��AdrawTerminate() �����s����B<BR>
     */
    virtual void drawMain();

    /**
     * �m�[�h�̃t���[�����̕`�掖�㏈���i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��\���t���O���A���Z�b�g<BR>
     * (�܂� _isActive && !_wasBlinded && _isAlive)�̏ꍇ <BR>
     * processTerminate() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� drawTerminate() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��Afinally() �����s����B<BR>
     */
    virtual void drawTerminate();

    /**
     * �m�[�h�̃t���[�����̍ŏI���� .
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �i_isActive && !_wasPaused && _isAlive�j�̏ꍇ <BR>
     * processFinally() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� finally() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��A���t���[���܂ł̎c���Ԃɗ]�T������� cleane() �����s����B<BR>
     */
    virtual void finally();

    /**
     * �m�[�h�̉����̏���(�t���[�����ł͂Ȃ�) .
     * �����t���O���Z�b�g�A(�܂� _isActive)�̏ꍇ <BR>
     * processHappen(int) ���R�[��������A�z���̃m�[�h�S�Ăɂ��� happen() ���ċA�I�Ɏ��s����B<BR>
     * @param	prm_no �����̔ԍ�
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
     * @param	int prm_no �����̔ԍ�
     */
    virtual void processHappen(int prm_no) = 0;

    /**
     * �_�ɉy�� .
     * @return	�Ă΂�ďo�Ă����_
     */
    virtual GgafGod* askGod() = 0;

    //==================��ԕψڃ��\�b�h�S==================>
    /**
     * ������Ԃɂ���(���c���[) .
     * ���m�ɂ́A���t���[�����犈����Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����Ŋ�����ԂɂȂ鎖�ɂȂ�܂��B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� act() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͊�����Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * ���m�[�h�� processBehavior() �Ŗ{���\�b�h���Ăяo���R�[�h�������Ă��A�^�X�N�V�X�e���̎d�g�ݏ�A<BR>
     * ���s����邱�Ƃ͖����̂ŁA���m�[�h������s������AprocessFinal() �Ȃǂł̎g�p��z��B<BR>
     * <B>[�⑫]</B>�m�[�h��������́A������ԂƂȂ��Ă���B<BR>
     */
    void act();
    /**
     * �����\�񂷂�(���c���[) .
     * N�t���[����� act() �����s����邱�Ƃ�\�񂷂�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� actAfter(DWORD) �����s�����B<BR>
     * actAfter(1) �́Aact() �Ɠ����Ӗ��ɂȂ�܂��B<BR>
     * @param prm_dwFrameOffset �x���t���[����(1�`)
     */
    void actAfter(DWORD prm_dwFrameOffset);
    /**
     * ������Ԃɂ���(�P��) .
     * ���m�[�h�������t���[�����犈����Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     */
    void actAlone();
    /**
     * ������Ԃɂ���(���c���[�E����) .
     * ���m�ɂ́A�����t���O�𑦍��ɗ��Ă�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� actImmediately() �����s�����B<BR>
     * ���̃m�[�h����́A�u������ԂȂ�΁E�E�E�����v�Ƃ���������s�Ȃ��Ă���ꍇ�A<BR>
     * �g�p�ɂ͒��ӂ��K�v�B�Ȃ��Ȃ�΁AactImmediately() �����s����O�Ǝ��s�������<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B���̃m�[�h����̎Q�Ƃ���^�C�~���O�ɂ���Ă�<BR>
     * ����t���[���ł���ɂ�������炸�A�قȂ�����Ԕ���ɂȂ邩������Ȃ��B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void actImmediately();
    /**
     * ������Ԃɂ���(�P�́E����) .
     * ���m�[�h�݂̂ɂ��āA�����t���O�𑦍��ɗ��Ă�B<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void actImmediatelyAlone();
    //===================
    /**
     * �񊈓���Ԃɂ���(���c���[) .
     * ���m�ɂ́A���t���[������񊈓���Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����Ŕ񊈓���ԂɂȂ鎖�ɂȂ�܂��B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� refrain() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͔񊈓���Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * ���m�[�h�ɑ΂��Ďg�p������AprocessFinal() �Ȃǂł̎g�p��z��B<BR>
     */
    void refrain();
    /**
     * �񊈓��\�񂷂�(���c���[) .
     * N�t���[����� refrain() �����s����邱�Ƃ�\�񂷂�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� refrainAfter(DWORD) �����s�����B<BR>
     * refrainAfter(1) �́Arefrain() �Ɠ����Ӗ��ɂȂ�܂��B<BR>
     * @param prm_dwFrameOffset �x���t���[����(1�`)
     */
    void refrainAfter(DWORD prm_dwFrameOffset);
    /**
     * �񊈓���Ԃɂ���(�P��) .
     * ���m�[�h�������t���[������񊈓���Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     */
    void refrainAlone();
    /**
     * �񊈓���Ԃɂ���(���c���[�E����) .
     * ���m�ɂ́A�����t���O�𑦍��ɉ�����B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� refrainImmediately() �����s�����B<BR>
     * ���̃m�[�h����́A�u�񊈓���ԂȂ�΁E�E�E�����v�Ƃ���������s�Ȃ��Ă���ꍇ�A<BR>
     * �g�p�ɂ͒��ӂ��K�v�B�Ȃ��Ȃ�΁ArefrainImmediately() �����s����O�Ǝ��s�������<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B���̃m�[�h����̎Q�Ƃ���^�C�~���O�ɂ���Ă�<BR>
     * ����t���[���ł���ɂ�������炸�A�قȂ�����Ԕ���ɂȂ邩������Ȃ��B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void refrainImmediately();
    /**
     * �񊈓���Ԃɂ���(�P�́E����) .
     * ���m�[�h�݂̂ɂ��āA�񊈓��t���O�𑦍��ɗ��Ă�B<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void refrainImmediatelyAlone();
    //===================
    /**
     * �ꎞ��~�ɂ���(���c���[) .
     * ���m�ɂ́A���t���[������ꎞ��~�ɂ���\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����ňꎞ��~�ɂȂ鎖�ɂȂ�܂��B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� pause() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͈ꎞ��~�̕ω��͖�����ѐ��͕ۂ����B<BR>
     * ���m�[�h�ɑ΂��Ďg�p������AprocessFinal() �Ȃǂł̎g�p��z��B<BR>
     */
    void pause();
    /**
     * �ꎞ��~�ɂ���(�P��) .
     * ���m�[�h�������t���[������ꎞ��~�ɂ���\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     */
    void pauseAlone();
    /**
     * �ꎞ��~�ɂ���(���c���[�E����) .
     * ���m�ɂ́A�ꎞ��~�t���O�𑦍��ɗ��Ă�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� pauseImmediately() �����s�����B<BR>
     * ���̃m�[�h����́A�u�ꎞ��~�Ȃ�΁E�E�E�����v�Ƃ���������s�Ȃ��Ă���ꍇ�A<BR>
     * �g�p�ɂ͒��ӂ��K�v�B�Ȃ��Ȃ�΁ApauseImmediately() �����s����O�Ǝ��s�������<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B���̃m�[�h����̎Q�Ƃ���^�C�~���O�ɂ���Ă�<BR>
     * ����t���[���ł���ɂ�������炸�A�قȂ�����Ԕ���ɂȂ邩������Ȃ��B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void pauseImmediately();
    /**
     * �ꎞ��~�ɂ���(�P�́E����) .
     * ���m�[�h�݂̂ɂ��āA�ꎞ��~�t���O�𑦍��ɗ��Ă�B<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void pauseImmediatelyAlone();
    //===================
    /**
     * �ꎞ��~��Ԃ������ɂ���(���c���[) .
     * ���m�ɂ́A���t���[������ꎞ��~��Ԃ���������\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����ňꎞ��~��Ԃ���������鎖�ɂȂ�܂��B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� unpause() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͈ꎞ��~��Ԃ������̕ω��͖�����ѐ��͕ۂ����B<BR>
     * ���m�[�h�ɑ΂��Ďg�p������AprocessFinal() �Ȃǂł̎g�p��z��B<BR>
     */
    void unpause();
    /**
     * �ꎞ��~��Ԃ������ɂ���(�P��) .
     * ���m�[�h�������t���[������ꎞ��~��Ԃ������ɂ���\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     */
    void unpauseAlone();
    /**
     * �ꎞ��~��Ԃ���������(���c���[�E����) .
     * ���m�ɂ́A�ꎞ��~��ԃt���O�𑦍��ɉ�����B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� unpauseImmediately() �����s�����B<BR>
     * ���̃m�[�h����́A�u�ꎞ��~��ԂȂ�΁E�E�E�����v�Ƃ���������s�Ȃ��Ă���ꍇ�A<BR>
     * �g�p�ɂ͒��ӂ��K�v�B�Ȃ��Ȃ�΁AunpauseImmediately() �����s����O�Ǝ��s�������<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B���̃m�[�h����̎Q�Ƃ���^�C�~���O�ɂ���Ă�<BR>
     * ����t���[���ł���ɂ�������炸�A�قȂ�����Ԕ���ɂȂ邩������Ȃ��B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void unpauseImmediately();
    /**
     * �ꎞ��~��Ԃ������ɂ���(�P�́E����) .
     * ���m�[�h�݂̂ɂ��āA�񊈓��t���O�𑦍��ɗ��Ă�B<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void unpauseImmediatelyAlone();
    //===================
    /**
     * ��\����Ԃɂ���(���c���[) .
     * ���m�ɂ́A���t���[�������\����Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����Ŕ�\����ԂɂȂ鎖�ɂȂ�܂��B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� blind() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͔�\����Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * ���m�[�h�ɑ΂��Ďg�p������AprocessFinal() �Ȃǂł̎g�p��z��B<BR>
     * <B>[�⑫]</B>�m�[�h��������́A��\����ԂƂȂ��Ă���B<BR>
     */
    void blind();
    /**
     * ��\����Ԃɂ���(�P��) .
     * ���m�[�h�������t���[�������\����Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     */
    void blindAlone();
    /**
     * ��\����Ԃɂ���(���c���[�E����) .
     * ���m�ɂ́A�񊈓��t���O�𑦍��ɗ��Ă�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� blindImmediately() �����s�����B<BR>
     * ���̃m�[�h����́A�u��\����ԂȂ�΁E�E�E�����v�Ƃ���������s�Ȃ��Ă���ꍇ�A<BR>
     * �g�p�ɂ͒��ӂ��K�v�B�Ȃ��Ȃ�΁AblindImmediately() �����s����O�Ǝ��s�������<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B���̃m�[�h����̎Q�Ƃ���^�C�~���O�ɂ���Ă�<BR>
     * ����t���[���ł���ɂ�������炸�A�قȂ�����Ԕ���ɂȂ邩������Ȃ��B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void blindImmediately();
    /**
     * ��\����Ԃɂ���(�P�́E����) .
     * ���m�[�h�݂̂ɂ��āA�񊈓��t���O�𑦍��ɗ��Ă�B<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void blindImmediatelyAlone();
    //===================
    /**
     * ��\����Ԃ������ɂ���(���c���[) .
     * ���m�ɂ́A���t���[�������\����Ԃ���������\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����Ŕ�\����Ԃ���������鎖�ɂȂ�܂��B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� unblind() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͔�\����Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * ���m�[�h�ɑ΂��Ďg�p������AprocessFinal() �Ȃǂł̎g�p��z��B<BR>
     */
    void unblind();
    /**
     * ��\����Ԃ������ɂ���(�P��) .
     * ���m�[�h�������t���[�������\����Ԃ���������\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     */
    void unblindAlone();
    /**
     * ��\����Ԃ���������(���c���[�E����) .
     * ���m�ɂ́A��\���t���O�𑦍��ɉ�����B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� unblindImmediately() �����s�����B<BR>
     * ���̃m�[�h����́A�u��\����ԂȂ�΁E�E�E�����v�Ƃ���������s�Ȃ��Ă���ꍇ�A<BR>
     * �g�p�ɂ͒��ӂ��K�v�B�Ȃ��Ȃ�΁AunblindImmediately() �����s����O�Ǝ��s�������<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B���̃m�[�h����̎Q�Ƃ���^�C�~���O�ɂ���Ă�<BR>
     * ����t���[���ł���ɂ�������炸�A�قȂ�����Ԕ���ɂȂ邩������Ȃ��B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void unblindImmediately();
    /**
     * ��\����Ԃ���������(�P�́E����) .
     * ���m�[�h�݂̂ɂ��āA��\����t���O�𑦍��ɉ�����B<BR>
     * �w����t���[�����x�ŁA��Ԃ��ω����邽�߂ł���B<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    void unblindImmediatelyAlone();
    //===================
    /**
     * ���m�[�h�����t���[������▽�����邱�Ƃ�錾���� .
     * �z���m�[�h�S�Ăɐ����I��(farewell())�����m�点���͂��B<BR>
     * �▽������Ƃ͋�̓I�ɂ́A�\���t���O(_wasBlinded)�A�U�镑���t���O(_isActive)�A�����t���O(_isAlive) �� <BR>
     * ���t���[������A���Z�b�g���鎖�ł���B<BR>
     * ����ɂ��A�_(GgafGod)���������Ԃ̗]�T�̂��鎞�Ɏ��s����� cleane() ���\�b�h�ɂ�� delete �̑ΏۂƂȂ�B<BR>
     * ���������āA�{�����o�֐������s���Ă��A�w����t���[�����x�ł̓C���X�^���X�������ɉ������܂���B<BR>
     */
    void farewell(DWORD prm_dwFrameOffset = 0);

    /**
     * ���c���[�m�[�h���ŏI�m�[�h�Ɉړ����� .
     * ���t���[���̐擪����(nextFrame())�Ŏ��c���[�m�[�h���Z��m�[�h�O���[�v�̍ŏI�ɃV�t�g����B<BR>
     * <B>[����]</B>�����ɏ��J�菈�������s�����킯�ł͂���܂���B<BR>
     */
    void moveLast();

    /**
     * ���c���[�m�[�h��擪�m�[�h�Ɉړ����� .
     * ���t���[���̐擪����(nextFrame())�Ŏ��c���[�m�[�h���Z��m�[�h�O���[�v�̐擪�ɃV�t�g����B<BR>
     * <B>[����]</B>�����ɏ��J�菈�������s�����킯�ł͂���܂���B<BR>
     */
    void moveFirst();

    /**
     * �����c���[����Ɨ�����
     * @return	T* �E�ނ��Ɨ��������m�[�h�̃|�C���^
     *
     */
    T* becomeIndependent();

    /**
     * �����\�����ׂ�
     * @return	bool true:�����\�^false:�����s��
     */
    bool isAlive();

    /**
     * �����������ׂ�
     * @return	bool true:�������^false:�񊈓���
     */
    bool isPlaying();

    /**
     * �񊈓����犈���ɐ؂�ւ�������ǂ��� .
     * �������AonAct() �ő�p�ł���ꍇ�́A��������I�[�o�[���C�h�����ق�����������L�q�ł���͂��B
     * @return	bool true:�؂�ւ�����^false:�؂�ւ���Ă��Ȃ�
     */
    bool switchedToAct();

    /**
     * ���������~�ɐ؂�ւ�������ǂ��� .
     * ���̃��\�b�h�͍��̂Ƃ���g���ǂ���͖�����������܂���B
     * @return	bool true:�؂�ւ�����^false:�؂�ւ���Ă��Ȃ�
     */
    bool switchedToRefrain();

    /**
     * �������Ă��邩
     * @return	bool true:�����\�^false:�����s��
     */
    bool isBehaving();

    /**
     * �`�悷�邩�ǂ������ׂ�i��\���łȂ����ǂ����j
     * @return	bool true:�`��ł���^false:�`��͂��Ȃ�
     */
    bool canDraw();

    /**
     * �m�[�h�̌��݂̌o�߃t���[�����擾����
     */
    DWORD getFrame();

    /**
     * ���Όo�߃t���[���̔���B
     * ���O�� relativeFrame(int) ���s���i���ʂ�true/false�Ɋւ�炸�j�̃t���[��������̌o�߃t���[�����ɒB���������肷��B
     * ���ӁF����q���������ɂ��ArelativeFrame(int) ���Ăяo�����񐔂��ω�����ꍇ�A���Όo�߃t���[�����ω�����B
     * @param	prm_dwFrame_relative	�o�߃t���[����
     * @return	bool	true:�o�߃t���[�����ɒB����/false:�B���Ă��Ȃ�
     */
    bool relativeFrame(DWORD prm_dwFrame_relative);

};

///////////////////////////////////////////////////////////////// ��������͎�����

template<class T>
GgafElement<T>::GgafElement(const char* prm_name) : SUPER(prm_name),
            _pGod(NULL), _wasInitialized(false), _dwGodFrame_ofDeath(MAXDWORD), _dwFrame(0),
            _dwFrame_relative(0), _isActive(true), _wasPaused(false), _wasBlinded(false), _isAlive(true),
            _willActNextFrame(true), _willPauseNextFrame(false), _willBlindNextFrame(false),
            _willBeAliveNextFrame(true), _willMoveFirstNextFrame(false), _willMoveLastNextFrame(false),
            _willActAfterFrame(false), _dwGodFremeWhenAct(0), _willRefrainAfterFrame(false), _dwGodFremeWhenRefrain(0),
            _switchedToAct(false), _switchedToRefrain(false), _wasExecuted_processDrawMain(false) {
}

template<class T>
void GgafElement<T>::nextFrame() {
    TRACE("GgafElement::nextFrame BEGIN _dwFrame=" << _dwFrame << " name=" << GgafNode<T>::_name << " class="
            << GgafNode<T>::_class_name);

    //���̎���
    if (_dwGodFrame_ofDeath == (askGod()->_dwFrame_God)) {
        _willActNextFrame = false;
        _willBeAliveNextFrame = false;
    }


    if (_willMoveLastNextFrame) {
        _willMoveLastNextFrame = false;
        SUPER::moveLast();
    } else {

        if(_wasInitialized == false) {
            initialize();
            _wasInitialized = true;
        }

        _wasExecuted_processDrawMain = false; //���`���

        if (_isAlive) {
            if (_willActAfterFrame) {
                //�x��play����
                if (askGod()->_dwFrame_God >= _dwGodFremeWhenAct) {
                    actImmediately();
                    _dwGodFremeWhenAct = 0;
                    _willActAfterFrame = false;
                }
            } else if (_willRefrainAfterFrame) {
                //�x��stop����
                if (askGod()->_dwFrame_God == _dwGodFremeWhenRefrain) {
                    refrainImmediately();
                    _dwGodFremeWhenRefrain = 0;
                    _willRefrainAfterFrame = false;
                }
            }
            if (_isActive) {
                _dwFrame++;
            }
        }

        //�����A�񊈓��̏�ԕω���
        if (_isActive == false && _willActNextFrame) {
            _switchedToAct = true;
        } else if (_isActive && _willActNextFrame == false) {
            _switchedToRefrain = true;
        } else {
            _switchedToAct = false;
            _switchedToRefrain = false;
        }
        //�t���O�����𔽉f
        _isActive = _willActNextFrame;
        _wasPaused = _willPauseNextFrame;
        _wasBlinded = _willBlindNextFrame;
        _isAlive = _willBeAliveNextFrame;

        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                if (pElementTemp->_isLast) {
                    pElementTemp->nextFrame();
                    if (pElementTemp->_isAlive == false) {
                        GgafFactory::_pGarbageBox->add(pElementTemp);
                    }
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                    pElementTemp->SUPER::_pPrev->nextFrame();
                    if (pElementTemp->SUPER::_pPrev->_isAlive == false) {
                        GgafFactory::_pGarbageBox->add(pElementTemp->SUPER::_pPrev);
                    }
                }
            }
        }

        if (_willMoveFirstNextFrame) {
            _willMoveFirstNextFrame = false;
            SUPER::moveFirst();
        }

    }
    TRACE("GgafElement::nextFrame END _dwFrame="<<_dwFrame<<" name="<<GgafNode<T>::_name<<" class="<<GgafNode<T>::_class_name);
}

template<class T>
void GgafElement<T>::behave() {
    if(_wasInitialized == false) {
        initialize();
        _wasInitialized = true;
    }

    //�����A�񊈓��̏�ԕω����R�[���o�b�N
    if (_switchedToAct) {
        onAct();
    } else if (_switchedToRefrain) {
        onRefrain();
    }

    if (_isActive && !_wasPaused && _isAlive) {
        _dwFrame_relative = 0;
        processBehavior();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->behave();
                if (pElementTemp->_isLast) {
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
    if(_wasInitialized == false) {
        initialize();
        _wasInitialized = true;
    }

    if (_isActive && !_wasPaused && _isAlive) {
        _dwFrame_relative = 0;
        processJudgement();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->judge();
                if (pElementTemp->_isLast) {
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
    if(_wasInitialized == false) {
        initialize();
        _wasInitialized = true;
    }

    if (_isActive && !_wasBlinded && _isAlive) {
        _dwFrame_relative = 0;
        processDrawPrior();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->drawPrior();
                if (pElementTemp->_isLast) {
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
    if(_wasInitialized == false) {
        initialize();
        _wasInitialized = true;
    }

    if (_isActive && !_wasBlinded && _isAlive) {
        _dwFrame_relative = 0;
        if (!_wasExecuted_processDrawMain) {
            processDrawMain();
            _wasExecuted_processDrawMain = true;
        }
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->drawMain();
                if (pElementTemp->_isLast) {
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
    if(_wasInitialized == false) {
        initialize();
        _wasInitialized = true;
    }

    if (_isActive && !_wasBlinded && _isAlive) {
        _dwFrame_relative = 0;
        processDrawTerminate();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->drawTerminate();
                if (pElementTemp->_isLast) {
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
    if(_wasInitialized == false) {
        initialize();
        _wasInitialized = true;
    }

    if (_isAlive) {
        _dwFrame_relative = 0;
        processHappen(prm_no);
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->happen(prm_no);
                if (pElementTemp->_isLast) {
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
    if(_wasInitialized == false) {
        initialize();
        _wasInitialized = true;
    }

    if (_isActive && !_wasPaused && _isAlive) {
        _dwFrame_relative = 0;
        processFinal();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->finally();
                if (pElementTemp->_isLast) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::actAlone() {
    if (_isAlive) {
        _willActNextFrame = true;
        _willPauseNextFrame = false;
        _willBlindNextFrame = false;
    }
}

template<class T>
void GgafElement<T>::act() {
    if (_isAlive) {
        _willActNextFrame = true;
        _willPauseNextFrame = false;
        _willBlindNextFrame = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->act();
                if (pElementTemp->_isLast) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::actImmediatelyAlone() {
    if (_isAlive) {
        if (_isActive == false) {
            _switchedToAct = true;
        } else {
            _switchedToAct = false;
        }
        _isActive = true;
        _wasPaused = false;
        _wasBlinded = false;
        _willActNextFrame = true;
        _willPauseNextFrame = false;
        _willBlindNextFrame = false;
    }
}

template<class T>
void GgafElement<T>::actImmediately() {
    if (_isAlive) {
        if (_isActive == false) {
            _switchedToAct = true;
        } else {
            _switchedToAct = false;
        }
        _isActive = true;
        _wasPaused = false;
        _wasBlinded = false;
        _willActNextFrame = true;
        _willPauseNextFrame = false;
        _willBlindNextFrame = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->actImmediately();
                if (pElementTemp->_isLast) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::actAfter(DWORD prm_dwFrameOffset) {
    _willActAfterFrame = true;
    _dwGodFremeWhenAct = askGod()->_dwFrame_God + prm_dwFrameOffset;
}

template<class T>
void GgafElement<T>::refrainAlone() {
    if (_isAlive) {
        _willActNextFrame = false;
    }
}

template<class T>
void GgafElement<T>::refrain() {
    if (_isAlive) {
        _willActNextFrame = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->refrain();
                if (pElementTemp->_isLast) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::refrainAfter(DWORD prm_dwFrameOffset) {
    _willRefrainAfterFrame = true;
    _dwGodFremeWhenRefrain = askGod()->_dwFrame_God + prm_dwFrameOffset;
}

template<class T>
void GgafElement<T>::refrainImmediatelyAlone() {
    if (_isAlive) {
        if (_isActive) {
            _switchedToRefrain = true;
        } else {
            _switchedToRefrain = false;
        }
        _isActive = false;
        _willActNextFrame = false;
    }
}

template<class T>
void GgafElement<T>::refrainImmediately() {
    if (_isAlive) {
        if (_isActive) {
            _switchedToRefrain = true;
        } else {
            _switchedToRefrain = false;
        }
        _isActive = false;
        _willActNextFrame = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->refrainImmediately();
                if (pElementTemp->_isLast) {
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
    if (_isAlive) {
        _willPauseNextFrame = true;
        //_isActive = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->pause();
                if (pElementTemp->_isLast) {
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
    if (_isAlive) {
        _willPauseNextFrame = true;
    }
}

template<class T>
void GgafElement<T>::pauseImmediately() {
    if (_isAlive) {
        _wasPaused = true;
        _willPauseNextFrame = true;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->pauseImmediately();
                if (pElementTemp->_isLast) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::pauseImmediatelyAlone() {
    if (_isAlive) {
        _wasPaused = true;
        _willPauseNextFrame = true;
    }
}

template<class T>
void GgafElement<T>::unpause() {
    if (_isAlive) {
        _willPauseNextFrame = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->unpause();
                if (pElementTemp->_isLast) {
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
    if (_isAlive) {
        _willPauseNextFrame = false;
    }
}

template<class T>
void GgafElement<T>::unpauseImmediately() {
    if (_isAlive) {
        _wasPaused = false;
        _willPauseNextFrame = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->unpauseImmediately();
                if (pElementTemp->_isLast) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::unpauseImmediatelyAlone() {
    if (_isAlive) {
        _wasPaused = false;
        _willPauseNextFrame = false;
    }
}

template<class T>
void GgafElement<T>::blind() {
    if (_isAlive) {
        _willBlindNextFrame = true;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->blind();
                if (pElementTemp->_isLast) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::blindAlone() {
    if (_isAlive) {
        _willBlindNextFrame = true;
    }
}

template<class T>
void GgafElement<T>::blindImmediately() {
    if (_isAlive) {
        _wasBlinded = true;
        _willBlindNextFrame = true;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->blindImmediately();
                if (pElementTemp->_isLast) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::blindImmediatelyAlone() {
    if (_isAlive) {
        _wasBlinded = true;
        _willBlindNextFrame = true;
    }
}

template<class T>
void GgafElement<T>::unblind() {
    if (_isAlive) {
        _willBlindNextFrame = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->unblind();
                if (pElementTemp->_isLast) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::unblindAlone() {
    if (_isAlive) {
        _willBlindNextFrame = false;
    }
}

template<class T>
void GgafElement<T>::unblindImmediately() {
    if (_isAlive) {
        _wasBlinded = false;
        _willBlindNextFrame = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->unblindImmediately();
                if (pElementTemp->_isLast) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::unblindImmediatelyAlone() {
    if (_isAlive) {
        _wasBlinded = false;
        _willBlindNextFrame = false;
    }
}
template<class T>
void GgafElement<T>::farewell(DWORD prm_dwFrameOffset) {

    _dwGodFrame_ofDeath = (askGod()->_dwFrame_God) + prm_dwFrameOffset + 1;
    if (SUPER::_pSubFirst != NULL) {
        T* pElementTemp = SUPER::_pSubFirst;
        while(true) {
            pElementTemp->farewell(prm_dwFrameOffset);
            if (pElementTemp->_isLast) {
                break;
            } else {
                pElementTemp = pElementTemp->SUPER::_pNext;
            }
        }
    }
}

template<class T>
DWORD GgafElement<T>::getFrame() {
    return _dwFrame;
}

template<class T>
bool GgafElement<T>::isAlive() {
    return _isAlive;
}

template<class T>
bool GgafElement<T>::isPlaying() {
    if (_isAlive && _isActive) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::switchedToAct() {
    if (_isAlive && _switchedToAct) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::switchedToRefrain() {
    if (_isAlive && _switchedToRefrain) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::canDraw() {
    if (_isAlive && _isActive && !_wasBlinded) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::isBehaving() {
    if (_isAlive && _isActive && !_wasPaused) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::relativeFrame(DWORD prm_dwFrame_relative) {
    _dwFrame_relative += prm_dwFrame_relative;
    if (_dwFrame == _dwFrame_relative) {
        return true;
    } else {
        return false;
    }
}

template<class T>
void GgafElement<T>::moveLast() {
    _willMoveLastNextFrame = true;
}

template<class T>
void GgafElement<T>::moveFirst() {
    _willMoveFirstNextFrame = true;
}

template<class T>
T* GgafElement<T>::becomeIndependent() {
    if (_isAlive) {
        return SUPER::tear();
    } else {
        throwGgafCriticalException("[GgafTreeNode<"<<SUPER::_class_name<<">::becomeIndependent()] ���x���� "<<SUPER::getName()<<"�́A�����ꎀ�ɍs���^���ł���B");
    }
}

template<class T>
void GgafElement<T>::cleane(int prm_iNumCleanNode) {
    if (SUPER::_pSubFirst == NULL) {
        return;
    }

    T* pElementTemp = SUPER::_pSubFirst->_pPrev;
    T* pWk;

    while(GgafFactory::_s_iCountCleanedNode < prm_iNumCleanNode) {

        if (pElementTemp->_pSubFirst) {
            //�q�̎q���܂��̂��Ă���ꍇ����ɂ�����
            pElementTemp->cleane(prm_iNumCleanNode);
            if (GgafFactory::_s_iCountCleanedNode >= prm_iNumCleanNode) {
                break;
            }
        }

        if (pElementTemp->_isFirst) { //�Ō�̈��
            if (pElementTemp->_pSubFirst) {
                //�q�̎q���܂��̂��Ă���ꍇ����ɂ�����
                pElementTemp->cleane(prm_iNumCleanNode);
                if (GgafFactory::_s_iCountCleanedNode >= prm_iNumCleanNode) {
                    break;
                }
            }
            if (pElementTemp->_isAlive == false) {
                DELETE_IMPOSSIBLE_NULL(pElementTemp);
                GgafFactory::_s_iCountCleanedNode++;
                Sleep(1);
            }
            break;
        } else {
            pWk = pElementTemp;
            if (pWk->_pSubFirst) {
                //�q�̎q���܂��̂��Ă���ꍇ����ɂ�����
                pWk->cleane(prm_iNumCleanNode);
                if (GgafFactory::_s_iCountCleanedNode >= prm_iNumCleanNode) {
                    break;
                }
            }
            pElementTemp = pElementTemp->_pPrev;
            if (pWk->_isAlive == false) {
                DELETE_IMPOSSIBLE_NULL(pWk);
                GgafFactory::_s_iCountCleanedNode++;
                Sleep(1);
            }
        }
    }
}

template<class T>
GgafElement<T>::~GgafElement() {
    //_TRACE_("~GgafElement() <"<<SUPER::_class_name << ">::farewell() :"<< SUPER::getName() <<"_dwGodFrame_ofDeath="<<_dwGodFrame_ofDeath<<"/_dwFrame="<<_dwFrame);
}

}
#endif /*GGAFELEMENT_H_*/
