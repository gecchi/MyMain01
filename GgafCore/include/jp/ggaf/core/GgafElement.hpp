#ifndef GGAFELEMENT_H_
#define GGAFELEMENT_H_


#define SUPER GgafNode<T>

/**
 * GgafNode�ɁA�l�X�ȏ�ԊǗ��i�t���O�Ǘ��j��ǉ�����N���X�B
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */
template<class T>
class GgafElement : public SUPER {

protected:

	/** �_�l�ւ̋ߓ� */
	GgafGod* _pGod;

	/** initialize���s��ꂽ�ǂ����̃t���O(true=�s��ꂽ) */
	bool _wasInitialized;

	/** ���[�v�p */
	T* _pElementTemp;

public:
	/** �m�[�h���a��(addSub���ꂽ�j������̃t���[�� */
	DWORD _dwFrame;
    /** ���΃t���[���v�Z�p */
    DWORD _dwFrame_relative;
	/** �m�[�h�����t���O */
	bool _isPlaying;
	/** �ꎞ��~�t���O */
	bool _wasPaused;
	/** �ꎞ��\���t���O */
	bool _wasBlinded;
	/** �m�[�h�����t���O */
	bool _isAlive;

	/** ���t���[���̃t���[�����Z���ɐݒ肳���m�[�h�����t���O */
	bool _willPlayNextFrame;
	/** ���t���[���̃t���[�����Z���ɐݒ肳���ꎞ��~�t���O */
	bool _willPauseNextFrame;
	/** ���t���[���̃t���[�����Z���ɐݒ肳���\���t���O  */
	bool _willBlindNextFrame;
	/** ���t���[���̃t���[�����Z���ɐݒ肳���ꎞ��\���t���O */
	bool _willBeAliveNextFrame;

	/** ���t���[���̃t���[�����Z���ɁA���m�[�h���擪�m�[�h�Ɉړ����邱�Ƃ��������t���O */
	bool _willMoveFirstNextFrame;
	/** ���t���[���̃t���[�����Z���ɁA���m�[�h�������m�[�h�Ɉړ����邱�Ƃ��������t���O */
	bool _willMoveLastNextFrame;

	/** ���ƂŊ����t���O */
	bool _willPlayAfterFrame;
	/** ���ƂŊ����c�t���[�� */
	DWORD _dwGodFremeWhenPlay;

	/** ���ƂŒ�~�t���O */
	bool _willStopAfterFrame;
	/** ���ƂŒ�~�c�t���[�� */
	DWORD _dwGodFremeWhenStop;

	/** �m�[�h�������ɐ؂�ւ����(stop��play)�u�ԂɂP�t���[�������Z�b�g�����t���O */
	bool _switchedToPlay;
	/** �m�[�h����~�ɐ؂�ւ����(play��stop)�u�ԂɂP�t���[�������Z�b�g�����t���O */
	bool _switchedToStop;

	/** �`�悳��܂����t���O */
	bool _wasExecuted_processDrawMain;


	/**
	 * �R���X�g���N�^
	 * @param prm_name �m�[�h���́i���j�[�N�ɂ��ĉ������j
	 */
	GgafElement(string prm_name);

	/**
	 * �f�X�g���N�^�B���c���[�m�[�h��������܂��B .
	 */
	virtual ~GgafElement();

	/**
	 * �|�� .
	 * �_���������Ԃɗ]�T���ł��Ƃ��ɌĂ΂�܂��B<BR>
	 * �z���m�[�h�̒��Ƀm�[�h�����t���O(_isAlive)�� false �ɂȂ��Ă���m�[�h������΂P����������܂��B<BR>
	 */
	virtual void cleane();

	/**
	 * �m�[�h�������� .
	 * �C���X�^���X������AnextFrame(),behave(),judge(),drawPrior(),drawMain(),drawTerminate(),happen(int),finally() ��
	 * ���ꂩ���Ăяo���ꂽ���A�ŏ��ɕK���P�񂾂��Ăяo����܂��B<BR>
	 */
	virtual void initialize() {};

	/**
	 * �m�[�h�̃t���[�������Z�ƁA�t���[���J�n�ɂ������Ă̂��낢��ȏ������� .
	 * �����t���O�A�����t���O���Z�b�g����Ă���ꍇ�m�[�h�̃t���[�������Z���܂��B���̒����<BR>
	 * _willPlayNextFrame, _willPauseNextFrame, _willBlindNextFrame, _willBeAliveNextFrame ��<BR>
	 * _isPlaying, _wasPaused, _wasBlinded, _isAlive �ɔ��f�i�R�s�[�j���܂��B<BR>
	 * �܂��A_willMoveFirstNextFrame, _willMoveLastNextFrame �� true �̏ꍇ�́A<BR>
	 * ���ꂼ��A���m�[�h�̐擪�m�[�h�ւ̈ړ��A�����m�[�h�ւ̈ړ������s����܂��B<BR>
	 * ���̌�A�z���m�[�h�S�Ă� nextFrame() �����s���܂��B<BR>
	 * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��Abehave()�����s���܂��B<BR>
	 */
	virtual void nextFrame();

	/**
	 * �m�[�h�̃t���[�����̐U�镑������ .
	 * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
	 * �i_isPlaying && !_wasPaused && _isAlive�j�̏ꍇ <BR>
	 * processBehavior() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� behave() �����s���܂��B<BR>
	 * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��Ajudge()�����s���܂��B<BR>
	 */
	virtual void behave();

	/**
	 * �Đ������� .
	 * ��~��Ԃ���Đ���Ԃɕω������Ƃ��ɂP�x�����Ă΂��B
	 * �K�v�ɉ����ăI�[�o�[���C�h���܂��B
	 */
	virtual void onPlay() {};

	/**
	 * ��~������ .
	 * �Đ���Ԃ����~��Ԃɕω������Ƃ��ɂP�x�����Ă΂��B
	 * �K�v�ɉ����ăI�[�o�[���C�h���܂��B
	 */
	virtual void onStop() {};

	/**
	 * �m�[�h�̃t���[�����̔��菈�� .
	 * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
	 * (�܂� _isPlaying && !_wasPaused && _isAlive)�̏ꍇ <BR>
	 * processJudgement() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� judge() �����s���܂��B<BR>
	 * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��A�t���[�����Ԃɗ]�T������� drawPrior()�A������� finally()�����s���܂��B<BR>
	 */
	virtual void judge();

	/**
	 * �m�[�h�̃t���[�����̕`�掖�O�����i�A�������׎��́A�_�̔��f�Ńt���[���X�L�b�v����ČĂяo����Ȃ����ꍇ������܂��B�j .
	 * �����t���O�A�����t���O���Z�b�g�A���ꎞ��\���t���O���A���Z�b�g<BR>
	 * (�܂� _isPlaying && !_wasBlinded && _isAlive)�̏ꍇ <BR>
	 * processDrawPrior() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� drawPrior() �����s���܂��B<BR>
	 * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��AdrawMain() �����s���܂��B<BR>
	 */
	virtual void drawPrior();

	/**
	 * �m�[�h�̃t���[�����̕`��{�����i�A�������׎��́A�_�̔��f�Ńt���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������܂��B�j .
	 * �����t���O�A�����t���O���Z�b�g�A���ꎞ��\���t���O���A���Z�b�g<BR>
	 * (�܂� _isPlaying && !_wasBlinded && _isAlive)�̏ꍇ <BR>
	 * processDrawMain() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� drawMain() �����s���܂��B<BR>
	 * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��AdrawTerminate() �����s���܂��B<BR>
	 */
	virtual void drawMain();

	/**
	 * �m�[�h�̃t���[�����̕`�掖�㏈���i�A�������׎��́A�_�̔��f�Ńt���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������܂��B�j .
	 * �����t���O�A�����t���O���Z�b�g�A���ꎞ��\���t���O���A���Z�b�g<BR>
	 * (�܂� _isPlaying && !_wasBlinded && _isAlive)�̏ꍇ <BR>
	 * processTerminate() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� drawTerminate() �����s���܂��B<BR>
	 * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��Afinally() �����s���܂��B<BR>
	 */
	virtual void drawTerminate();

	/**
	 * �m�[�h�̃t���[�����̍ŏI���� .
	 * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
	 * �i_isPlaying && !_wasPaused && _isAlive�j�̏ꍇ <BR>
	 * processFinally() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� finally() �����s���܂��B<BR>
	 * �_(GgafGod)�́A���E(GgafWorld)�ɑ΂��Ė{�����o�֐����s��A�t���[�����Ԃɗ]�T������� cleane() �����s���܂��B<BR>
	 */
	virtual void finally();

	/**
	 * �m�[�h�̉����̏���(�t���[�����ł͂Ȃ�) .
	 * �����t���O���Z�b�g�A(�܂� _isPlaying)�̏ꍇ <BR>
	 * processHappen(int) ���R�[��������A�z���̃m�[�h�S�Ăɂ��� happen() �����s���܂��B<BR>
	 * @param	prm_no �����̔ԍ�
	 */
	virtual void happen(int prm_no);

	/**
	 * �t���[�����̌ʐU�镑�������������B .
	 * behave() ���̏����擪�ŃR�[���o�b�N����܂��B<BR>
	 * ���̃����o�֐������ʃN���X�ŃI�[�o�[���C�h���āA�m�[�h�ʂ̐U�镑�����������������܂��B<BR>
	 * �z�肵�Ă���U�镑�������Ƃ́A��ɍ��W�v�Z�ƈړ��������ł��B<BR>
	 * �{�����o�֐����R�[���o�b�N�����ƌ������́A���c���[�m�[�h�S�Ăɑ΂��āAnextFrame() �����s�ς݂ł��邱�Ƃ�ۏ؂��܂�<BR>
	 */
	virtual void processBehavior() = 0;

	/**
	 * �t���[�����̌ʔ��f�����������B .
	 * judge() ���̏����擪�ŃR�[���o�b�N����܂��B<BR>
	 * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʔ��f�������L�q���܂��B<BR>
	 * �{�����o�֐����R�[���o�b�N�����ƌ������́A���c���[�m�[�h�S�Ăɑ΂��āAbehave() �����s�ς݂ł��邱�Ƃ�ۏ؂��܂��B<BR>
	 * �{�����o�֐��̑��݈Ӑ}�Ƃ��āAprocessBehavior() �ō��W�ړ��������S�Ċ��������㤖{�����o�֐��œ����蔻�菈������������Ƃ������g������z�肵�Ă��܂��B<BR>
	 */
	virtual void processJudgement() = 0;

	/**
	 * �m�[�h�̃t���[�����̌ʕ`�掖�O�����������B .
	 * drawPrior() ���̏����擪�ŃR�[���o�b�N����܂��B �A���A�_(GgafGod)���`��X�L�b�v�����ꍇ�A�t���[�����ŌĂяo����܂���B<BR>
	 * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʕ`�掖�O�������������܂��B<BR>
	 * �ʕ`�掖�O�����Ƃ́A��ɓ�����w�i�`��Ȃǂł��B<BR>
	 * �{�����o�֐����R�[���o�b�N�����ƌ������́A���c���[�m�[�h�S�Ăɑ΂��āAjudge() �����s�ς݂ł��邱�Ƃ��ۏ؂��܂�<BR>
	 * ����ɁA�{�����o�֐����s��AprocessDrawMain()�AprocessDrawTerminate() ���Ăяo����邱�Ƃ��ۏ؂���܂��B
	 */
	virtual void processDrawPrior() = 0;

	/**
	 * �m�[�h�̃t���[�����̌ʕ`��{�����������B .
	 * drawMain() ���̏����擪�ŃR�[���o�b�N����܂��B �A���AdrawPrior() �Ɠ��l�ɐ_(GgafGod)���`��X�L�b�v���ꂽ�ꍇ�́A�t���[�����ŌĂяo����܂���B<BR>
	 * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʕ`��{�������������܂��B<BR>
	 * �ʕ`��{�����Ƃ͎�ɃL�����N�^��A�w�i�̕`���z�肵�Ă��܂��B
	 * �{�����o�֐����R�[���o�b�N�����ƌ������́A���c���[�m�[�h�S�Ăɑ΂��āAdrawPrior() �����s�ς݂ł��邱�Ƃ�ۏ؂��܂�<BR>
	 */
	virtual void processDrawMain() = 0;

	/**
	 * �m�[�h�̃t���[�����̌ʕ\�����㏈�����L�q
	 * drawTerminate() ���̏����擪�ŃR�[���o�b�N����܂��B �A���AdrawPrior() �Ɠ��l�ɐ_(GgafGod)���`��X�L�b�v���ꂽ�ꍇ�́A�t���[�����ŌĂяo����܂���B<BR>
	 * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʕ\�����㏈�����������܂��B<BR>
	 * �ʕ\�����㏈���Ƃ́A�őO�ʃ��C���[�Ŏ�������t�F�[�h�G�t�F�N�g��A��ɍőO�ʂɕ\���������\���Ȃǂł��B<BR>
	 * �{�����o���R�[���o�b�N�����ƌ������́A���c���[�m�[�h�S�Ăɑ΂��āAdrawMain() �����s�ς݂ł��邱�Ƃ�ۏ؂��܂�<BR>
	 */
	virtual void processDrawTerminate() = 0;


	/**
	 * �m�[�h�̃t���[�����̌ʏI�[�����������B .
	 * finally() ���̏����擪�ŃR�[���o�b�N����܂��B<BR>
	 * ���̃����o�֐������ʃN���X�ŃI�[�o�[���C�h���āA�m�[�h�ʂ̏I�[�������������܂��B<BR>
	 * �I�[�����Ƃ́A�t���O�Ǘ��̎��s�Ȃǂł��B<BR>
	 * �z�肵�Ă���U�镑�������Ƃ́A��ɍ��W�v�Z�ƈړ������ł��B���̑��Ȃ�ł��ǂ��ł��B<BR>
	 * �{�����o�֐����R�[���o�b�N�����ƌ������́A���c���[�m�[�h�S�Ăɑ΂��āAjudge() �����s�ς݂ł��邱�Ƃ�ۏ؂��܂�<BR>
	 */
	virtual void processFinal() = 0;

	/**
	 * �m�[�h�̌ʉ����̏������L�q
	 * happen() ���̏����擪�ŃR�[���o�b�N����܂��B
	 * ���p�ړI�s��̔ėp�C�x���g�p���\�b�h
	 * @param	int prm_no �����̔ԍ�
	 */
	virtual void processHappen(int prm_no) = 0;

    /**
	 * �_�l�ɐڌ� .
	 * @return	�Ă΂�ďo�Ă����_�l
	 */
	virtual GgafGod* askGod() = 0;

	/**
	 * ���c���[�m�[�h�����t���[������Đ���Ԃɂ��� .
	 * ���g�Ǝ�����艺�ʂ̃m�[�h�S�ĂɍĐ�(declarePlay())�����s�����B<BR>
	 * <B>[�⑫]</B>�m�[�h��������́A�Đ���ԂƂȂ��Ă���B<BR>
	 */
	void declarePlay();

	/**
	 * ���c���[�m�[�h�𑦍��ɍĐ���Ԃɂ��� .
	 * ���g�Ǝ�����艺�ʂ̃m�[�h�S�ĂɍĐ�(playImmediately())�����s�����B<BR>
	 * <B>[�⑫]</B><BR>
	 * processFinal()�ȊO�Ɏ�����Athis �ȊO�Ɏ��s����ꍇ�A���̃m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
	 */
	void playImmediately();

	/**
	 * ���c���[�m�[�h��N�t���[����ɍĐ���Ԃɂ��� .
	 * @param prm_dwFrameOffset �x���t���[����
	 */
	void playAfter(DWORD prm_dwFrameOffset);

	/**
	 * ���c���[�m�[�h�����t���[�������~��Ԃɂ��� .
	 * ���g�Ǝ�����艺�ʂ̃m�[�h�S�Ăɒ�~(declarePlay())�����s�����B<BR>
	 */
	void declareStop();

	/**
	 * ���c���[�m�[�h�𑦍��ɒ�~��Ԃɂ��� .
	 * ���g�Ǝ�����艺�ʂ̃m�[�h�S�Ăɒ�~(playImmediately())�����s�����B<BR>
	 * <B>[�⑫]</B><BR>
	 * processFinal()�ȊO�Ɏ�����Athis �ȊO�Ŏ��s����ꍇ�A���̃m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
	 */
	void stopImmediately();

	/**
	 * ���c���[�m�[�h��N�t���[����ɒ�~��Ԃɂ��� .
	 * @param prm_dwFrameOffset �x���t���[����
	 */
	void stopAfter(DWORD prm_dwFrameOffset);

	/**
	 * ���c���[�m�[�h�����t���[������ꎞ��~��Ԃɂ��� .
	 * ���g�Ǝ�����艺�ʂ̃m�[�h�S�ĂɈꎞ��~(declarePause())�����s�����B<BR>
	 * <B>[�⑫]</B>�Đ����ɖ{�֐������s����ƐÎ~�摜�\����ԂƂȂ�B<BR>
	 */
	void declarePause();

	/**
	 * ���c���[�m�[�h�𑦍��Ɉꎞ��~��Ԃɂ��� .
	 * ���g�Ǝ�����艺�ʂ̃m�[�h�S�ĂɈꎞ��~���(pauseImmediately())�����s�����B<BR>
	 * <B>[�⑫]</B><BR>
	 * processFinal()�ȊO�Ɏ�����Athis �ȊO�Ŏ��s����ꍇ�A���̃m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
	 */
	void pauseImmediately();

	/**
	 * ���c���[�m�[�h�����t���[������ꎞ��~�����ɂ��� .
	 * ���g�Ǝ�����艺�ʂ̃m�[�h�S�ĂɈꎞ��~����(declareUnpause())�����s�����B<BR>
	 * <B>[�⑫]</B>declarePause()���s�Ȃ킸�ɖ{���\�b�h���Ăяo���Ă������s���܂���B<BR>
	 */
	void declareUnpause();

	/**
	 * ���c���[�m�[�h�𑦍��Ɉꎞ��~�����ɂ��� .
	 * ���g�Ǝ�����艺�ʂ̃m�[�h�S�ĂɈꎞ��~���(unpauseImmediately())�����s�����B<BR>
	 * <B>[�⑫]</B><BR>
	 * processFinal()�ȊO�Ɏ�����Athis �ȊO�Ŏ��s����ꍇ�A���̃m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
	 */
	void unpauseImmediately();

	/**
	 * ���c���[�m�[�h�����t���[�������\����Ԃɂ��� .
	 * ���g�Ǝ�����艺�ʂ̃m�[�h�S�Ăɔ�\�����(declareBlind())�����s�����B<BR>
	 * <B>[�⑫]</B>�Đ����ɖ{�֐������s����ƁA�I�u�W�F�N�g�͕\������Ȃ����̂́A�����I�ɍ��W�ړ��A�����蔻��Ȃǂ̊����͌p�������B<BR>
	 */
	void declareBlind();

	/**
	 * ���c���[�m�[�h�𑦍��ɔ�\����Ԃɂ��� .
	 * ���g�Ǝ�����艺�ʂ̃m�[�h�S�Ăɔ�\�����(blindImmediately())�����s�����B<BR>
	 * <B>[�⑫]</B><BR>
	 * processFinal()�ȊO�Ɏ�����Athis �ȊO�Ŏ��s����ꍇ�A���̃m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
	 */
	void blindImmediately();

	/**
	 * ���c���[�m�[�h�����t���[�������\�������ɂ��� .
	 * ���g�Ǝ�����艺�ʂ̃m�[�h�S�Ăɔ�\������(��\��())�����s�����B<BR>
	 * <B>[�⑫]</B>declareBlind()���s�Ȃ킸�ɖ{���\�b�h���Ăяo���Ă������s���܂���B<BR>
	 */
	void declareUnblind();

	/**
	 * ���c���[�m�[�h�𑦍��ɔ�\�������ɂ��� .
	 * ���g�Ǝ�����艺�ʂ̃m�[�h�S�Ăɔ�\�����(unblindImmediately())�����s�����B<BR>
	 * <B>[�⑫]</B><BR>
	 * processFinal()�ȊO�Ɏ�����Athis �ȊO�Ŏ��s����ꍇ�A���̃m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
	 */
	void unblindImmediately();

	/**
	 * ���m�[�h�����t���[������▽�����邱�Ƃ�錾���܂� .
	 * ���g�Ǝ�����艺�ʂ̃m�[�h�S�Ăɐl���I��(declareFinishLife())�����m�点���͂��B<BR>
	 * �▽������Ƃ͋�̓I�ɂ́A�\���t���O(_wasBlinded)�A�U�镑���t���O(_isPlaying)�A�����t���O(_isAlive) �� <BR>
	 * ���t���[������A���Z�b�g���鎖�ł���B<BR>
	 * ����ɂ��A�_(GgafGod)���������Ԃ̗]�T�̂���t���[���Ɏ��s���� cleane()���� delete �̑ΏۂƂȂ�B<BR>
	 * ���������āA�{�����o�֐������s���Ă��A�t���O�̓A���Z�b�g����邽�ߕ\�ʂɂ͂ł܂��񂪁A�C���X�^���X�������ɉ�������Ƃ͌���܂���B<BR>
	 */
	void declareFinishLife();

	/**
	 * ���c���[�m�[�h���ŏI�m�[�h�ɏ��J�肷�� .
	 * ���t���[���̐擪����(nextFrame())�Ŏ��c���[�m�[�h���Z��m�[�h�O���[�v�̍ŏI�ɃV�t�g���܂��B<BR>
	 * <B>[����]</B>�����ɏ��J�菈�������s�����킯�ł͂���܂���B<BR>
	 */
	void declareMoveLast();

	/**
	 * ���c���[�m�[�h��擪�m�[�h�ɏ��J�肷�� .
	 * ���t���[���̐擪����(nextFrame())�Ŏ��c���[�m�[�h���Z��m�[�h�O���[�v�̐擪�ɃV�t�g���܂��B<BR>
	 * <B>[����]</B>�����ɏ��J�菈�������s�����킯�ł͂���܂���B<BR>
	 */
	void declareMoveFirst();

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
	 * �Đ�����
	 * @return	bool true:�Đ����^false:��~��
	 */
	bool isPlaying();


	/**
	 * ��~����Đ��ɐ؂�ւ�������ǂ��� .
	 * �������AonPlay() �ő�p�ł���ꍇ�́A��������I�[�o�[���C�h�����ق�����������L�q�ł���͂��B
	 * @return	bool true:�؂�ւ�����^false:�؂�ւ���Ă��Ȃ�
	 */
	bool switchedToPlay();

	/**
	 * �Đ������~�ɐ؂�ւ�������ǂ��� .
	 * ���̃��\�b�h�͍��̂Ƃ���g���ǂ���͖�����������܂���B
	 * @return	bool true:�؂�ւ�����^false:�؂�ւ���Ă��Ȃ�
	 */
	bool switchedToStop();


	/**
	 * �������Ă��邩
	 * @return	bool true:�����\�^false:�����s��
	 */
	bool isBehaving();

	/**
	 * �`��ł��邩�i��\���łȂ����ǂ����j
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
	 * ���ӁF����q���������ɂ��ArelativeFrame(int) ���Ăяo�����񐔂��ω�����ꍇ�A���Όo�߃t���[�����ω����܂��B
	 * @param	prm_dwFrame_relative	�o�߃t���[����
	 * @return	bool	true:�o�߃t���[�����ɒB����/false:�B���Ă��Ȃ�
	 */
	bool relativeFrame(DWORD prm_dwFrame_relative);

};



//////////////////////////////////////////////////////////////////

/**
 * ��������͎�����
 */


template<class T>
GgafElement<T>::GgafElement(string prm_name) : SUPER (prm_name),
_pGod(NULL),
_wasInitialized(false),
_pElementTemp(NULL),
_dwFrame(0),
_dwFrame_relative(0),
_isPlaying(true),
_wasPaused(false),
_wasBlinded(false),
_isAlive(true),
_willPlayNextFrame(true),
_willPauseNextFrame(false),
_willBlindNextFrame(false),
_willBeAliveNextFrame(true),
_willMoveFirstNextFrame(false),
_willMoveLastNextFrame(false),
_willPlayAfterFrame(false),
_dwGodFremeWhenPlay(0),
_willStopAfterFrame(false),
_dwGodFremeWhenStop(0),
_switchedToPlay(false),
_switchedToStop(false),
_wasExecuted_processDrawMain(false)
{
}


template<class T>
void GgafElement<T>::nextFrame() {
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
			if (_willPlayAfterFrame) {
				//�x��play����
				if (askGod()->_dwFrame_God == _dwGodFremeWhenPlay) {
					playImmediately();
					_willPlayAfterFrame = false;
				}
			} else if (_willStopAfterFrame) {
				//�x��stop����
				if (askGod()->_dwFrame_God == _dwGodFremeWhenPlay) {
					stopImmediately();
					_willStopAfterFrame = false;
				}
			}
			if (_isPlaying) {
				_dwFrame++;
			}
		}

		//�t���O�����𔽉f
		if (_isPlaying == false && _willPlayNextFrame) {
			// not Play �� Play ��Ԃ̏ꍇ
			_switchedToPlay = true;
		} else if (_isPlaying && _willPlayNextFrame == false) {
			// Play �� not Play ��Ԃ̏ꍇ
			_switchedToStop = true;
		} else {
			_switchedToPlay = false;
			_switchedToStop = false;
		}
		_isPlaying = _willPlayNextFrame;
		_wasPaused = _willPauseNextFrame;
		_wasBlinded = _willBlindNextFrame;
		_isAlive = _willBeAliveNextFrame;

		if (SUPER::_pSubFirst != NULL) {
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				if (_pElementTemp -> _isLast) {
					_pElementTemp -> nextFrame();
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
					_pElementTemp -> SUPER::_pPrev-> nextFrame();
				}
			}
		}

		if (_willMoveFirstNextFrame) {
			_willMoveFirstNextFrame = false;
			SUPER::moveFirst();
		}

	}
}

template<class T>
void GgafElement<T>::behave() {
	if(_wasInitialized == false) {
		initialize();
		_wasInitialized = true;
	}

	if (_switchedToPlay) {
		onPlay();
	} else if (_switchedToStop) {
		onStop();
	}

	if (_isPlaying && !_wasPaused && _isAlive) {
		_dwFrame_relative = 0;
		processBehavior();
		if (SUPER::_pSubFirst != NULL) {
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				_pElementTemp -> behave();
				if (_pElementTemp -> _isLast) {
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
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

	if (_isPlaying && !_wasPaused && _isAlive) {
		_dwFrame_relative = 0;
		processJudgement();
		if (SUPER::_pSubFirst != NULL) {
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				_pElementTemp -> judge();
				if (_pElementTemp -> _isLast) {
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
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

	if (_isPlaying && !_wasBlinded && _isAlive) {
		_dwFrame_relative = 0;
		processDrawPrior();
		if (SUPER::_pSubFirst != NULL) {
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				_pElementTemp -> drawPrior();
				if (_pElementTemp -> _isLast) {
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
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

	if (_isPlaying && !_wasBlinded && _isAlive) {
		_dwFrame_relative = 0;
		if (!_wasExecuted_processDrawMain) {
			processDrawMain();
			_wasExecuted_processDrawMain = true;
		}
		if (SUPER::_pSubFirst != NULL) {
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				_pElementTemp -> drawMain();
				if (_pElementTemp -> _isLast) {
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
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

	if (_isPlaying && !_wasBlinded && _isAlive) {
		_dwFrame_relative = 0;
		processDrawTerminate();
		if (SUPER::_pSubFirst != NULL) {
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				_pElementTemp -> drawTerminate();
				if (_pElementTemp -> _isLast) {
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
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
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				_pElementTemp -> happen(prm_no);
				if (_pElementTemp -> _isLast) {
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
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

	if (_isPlaying && !_wasPaused && _isAlive) {
		_dwFrame_relative = 0;
		processFinal();
		if (SUPER::_pSubFirst != NULL) {
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				_pElementTemp -> finally();
				if (_pElementTemp -> _isLast) {
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
				}
			}
		}
	}
}


template<class T>
void GgafElement<T>::declarePlay() {
	if (_isAlive) {
		_willPlayNextFrame = true;
		_willPauseNextFrame = false;
		_willBlindNextFrame = false;
		if (SUPER::_pSubFirst != NULL) {
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				_pElementTemp -> declarePlay();
				if (_pElementTemp -> _isLast) {
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
				}
			}
		}
	}
}

template<class T>
void GgafElement<T>::playImmediately() {
	if (_isAlive) {
		if (_isPlaying == false) {
			_switchedToPlay = true;
		} else {
			_switchedToPlay = false;
		}
		_isPlaying = true;
		_wasPaused = false;
		_wasBlinded = false;
		_willPlayNextFrame = true;
		_willPauseNextFrame = false;
		_willBlindNextFrame = false;
		if (SUPER::_pSubFirst != NULL) {
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				_pElementTemp -> playImmediately();
				if (_pElementTemp -> _isLast) {
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
				}
			}
		}
	}
}

template<class T>
void GgafElement<T>::playAfter(DWORD prm_dwFrameOffset) {
	_willPlayAfterFrame = true;
	_dwGodFremeWhenPlay = askGod()->_dwFrame_God + prm_dwFrameOffset;
}


template<class T>
void GgafElement<T>::declareStop() {
	if (_isAlive) {
		_willPlayNextFrame = false;
		if (SUPER::_pSubFirst != NULL) {
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				_pElementTemp -> declareStop();
				if (_pElementTemp -> _isLast) {
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
				}
			}
		}
	}
}

template<class T>
void GgafElement<T>::stopAfter(DWORD prm_dwFrameOffset) {
	_willStopAfterFrame = true;
	_dwGodFremeWhenStop = askGod()->_dwFrame_God + prm_dwFrameOffset;
}

template<class T>
void GgafElement<T>::stopImmediately() {
	if (_isAlive) {
		if (_isPlaying) {
			_switchedToStop = true;
		} else {
			_switchedToStop = false;
		}
		_isPlaying = false;
		_willPlayNextFrame = false;
		if (SUPER::_pSubFirst != NULL) {
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				_pElementTemp -> stopImmediately();
				if (_pElementTemp -> _isLast) {
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
				}
			}
		}
	}
}


template<class T>
void GgafElement<T>::declarePause() {
	if (_isAlive) {
		_willPauseNextFrame = true;
		_isPlaying = false;
		if (SUPER::_pSubFirst != NULL) {
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				_pElementTemp -> declarePause();
				if (_pElementTemp -> _isLast) {
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
				}
			 }
		}
	}
}

template<class T>
void GgafElement<T>::pauseImmediately() {
	if (_isAlive) {
		_wasPaused = true;
		_willPauseNextFrame = true;
		_isPlaying = false;
		if (SUPER::_pSubFirst != NULL) {
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				_pElementTemp -> pauseImmediately();
				if (_pElementTemp -> _isLast) {
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
				}
			 }
		}
	}
}

template<class T>
void GgafElement<T>::declareUnpause() {
	if (_isAlive) {
		_willPauseNextFrame = false;
		if (SUPER::_pSubFirst != NULL) {
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				_pElementTemp -> declareUnpause();
				if (_pElementTemp -> _isLast) {
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
				}
			}
		}
	}
}

template<class T>
void GgafElement<T>::unpauseImmediately() {
	if (_isAlive) {
		_wasPaused = false;
		_willPauseNextFrame = false;
		if (SUPER::_pSubFirst != NULL) {
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				_pElementTemp -> unpauseImmediately();
				if (_pElementTemp -> _isLast) {
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
				}
			}
		}
	}
}

template<class T>
void GgafElement<T>::declareBlind() {
	if (_isAlive) {
		_willBlindNextFrame = true;
		if (SUPER::_pSubFirst != NULL) {
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				_pElementTemp -> declareBlind();
				if (_pElementTemp -> _isLast) {
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
				}
			}
		}
	}
}

template<class T>
void GgafElement<T>::blindImmediately() {
	if (_isAlive) {
		_wasBlinded = true;
		_willBlindNextFrame = true;
		if (SUPER::_pSubFirst != NULL) {
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				_pElementTemp -> blindImmediately();
				if (_pElementTemp -> _isLast) {
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
				}
			}
		}
	}
}

template<class T>
void GgafElement<T>::declareUnblind() {
	if (_isAlive) {
		_willBlindNextFrame = false;
		if (SUPER::_pSubFirst != NULL) {
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				_pElementTemp -> declareUnblind();
				if (_pElementTemp -> _isLast) {
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
				}
			}
		}
	}
}

template<class T>
void GgafElement<T>::unblindImmediately() {
	if (_isAlive) {
		_wasBlinded = false;
		_willBlindNextFrame = false;
		if (SUPER::_pSubFirst != NULL) {
			_pElementTemp = SUPER::_pSubFirst;
			while(true) {
				_pElementTemp -> unblindImmediately();
				if (_pElementTemp -> _isLast) {
					break;
				} else {
					_pElementTemp = _pElementTemp -> SUPER::_pNext;
				}
			}
		}
	}
}

template<class T>
void GgafElement<T>::declareFinishLife() {
	_TRACE_("GgafElement<"<<SUPER::_class_name << ">::declareFinishLife() :"<< SUPER::getName());
	_willPlayNextFrame = false;
	_willBeAliveNextFrame = false;
	SUPER::_name = "_x_"+SUPER::_name;
	if (SUPER::_pSubFirst != NULL) {
		_pElementTemp = SUPER::_pSubFirst;
		while(true) {
			_pElementTemp -> declareFinishLife();
			if (_pElementTemp -> _isLast) {
				break;
			} else {
				_pElementTemp = _pElementTemp -> SUPER::_pNext;
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
	if (_isAlive && _isPlaying) {
		return true;
	} else {
		return false;
	}
}

template<class T>
bool GgafElement<T>::switchedToPlay() {
	if (_isAlive && _switchedToPlay) {
		return true;
	} else {
		return false;
	}
}

template<class T>
bool GgafElement<T>::switchedToStop() {
	if (_isAlive && _switchedToStop) {
		return true;
	} else {
		return false;
	}
}

template<class T>
bool GgafElement<T>::canDraw() {
	if (_isAlive && _isPlaying && !_wasBlinded) {
		return true;
	} else {
		return false;
	}
}

template<class T>
bool GgafElement<T>::isBehaving() {
	if (_isAlive && _isPlaying && !_wasPaused) {
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
void GgafElement<T>::declareMoveLast() {
	_willMoveLastNextFrame = true;
}

template<class T>
void GgafElement<T>::declareMoveFirst() {
	_willMoveFirstNextFrame = true;
}

template<class T>
T* GgafElement<T>::becomeIndependent() {
	if (_isAlive) {
		return SUPER::tear();
	} else {
		throw_GgafCriticalException("[GgafTreeNode<"<<SUPER::_class_name<<">::becomeIndependent()] ���x���� "<<SUPER::getName()<<"�́A�����ꎀ�ɍs���^���ł��B");
	}
}



template<class T>
void GgafElement<T>::cleane() {
	if (SUPER::_pSubFirst == NULL || GgafGod::_s_iNumClean_Node != 0) {
		return;
	}

	if (_isAlive == false) {
		throw_GgafCriticalException("[GgafElement<"<<SUPER::_class_name<<">::cleane()] Error! ���E���Ȃ���΂����܂���B���̑O�ɐe��clean�����͂��ł��B���������ł��B(name="<<SUPER::getName()+")");
	}

	//�q�𒲂ׂ�delete����
	_pElementTemp = SUPER::_pSubFirst -> SUPER::_pPrev;
	while(GgafGod::_s_iNumClean_Node == 0) {
		if (_pElementTemp->_isFirst) { //�������猩�čs���Ō�̈��

			if (_pElementTemp->_isAlive == false) {
				delete (_pElementTemp);
				GgafGod::_s_iNumClean_Node++;
			}
			break;
		} else { //�������珇�Ɍ��Ă���
			_pElementTemp = _pElementTemp -> SUPER::_pPrev;
			if (_pElementTemp->SUPER::_pNext->_isAlive == false) {
				delete (_pElementTemp->SUPER::_pNext);
				GgafGod::_s_iNumClean_Node++;
			}
		}
	}

	//�q���܂��̂��Ă���ꍇ����ɂ�����
	if (SUPER::_pSubFirst != NULL) {
		_pElementTemp = SUPER::_pSubFirst;
		while(true) {
			_pElementTemp -> cleane();
			if (_pElementTemp -> _isLast) {
				break;
			} else {
				_pElementTemp = _pElementTemp -> SUPER::_pNext;

			}
		}
	}
}



template<class T>
GgafElement<T>::~GgafElement() {
}

#endif /*GGAFELEMENT_H_*/
