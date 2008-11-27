#ifndef GGAFGOD_H_
#define GGAFGOD_H_



class GgafGod : public GgafObject {

public:

	/** �|���I�u�W�F�N�g�� */
	static int _s_iNumCleanNodePerFrame;
	/** �����H��(�ʃX���b�h)�̃G���[��ԁBNULL������ғ����^not NULL���ُ픭�� */
	static GgafCriticalException* _pException_Factory;
	/** ���ɐ��E�����������鎞�Ԃ̃I�t�Z�b�g */
	static DWORD _aDwTime_OffsetOfNextFrame[];

	/** GgafFactory::work �X���b�h�n���h��  */
	HANDLE _handleFactory01;
	/** GgafFactory::work �X���b�hID  */
	unsigned int _thID01;
	/** �N���e�B�J���Z�N�V�����i�Z�}�t�H�j */
	static CRITICAL_SECTION CS1;
	static CRITICAL_SECTION CS2;

	/** �_�̃t���[���J�n�V�X�e������ */
	DWORD _dwTime_FrameBegin;
	/** ���ɐ��E������������V�X�e������ */
	DWORD _dwTime_ScheduledNextFrame;
	/** �_�a������̃t���[���� */
	DWORD _dwFrame_God;
	/** ���E�����o���ł��Ȃ������i�X�L�b�v�����j�� */
	DWORD _dwFrame_SkipCount;
	/** ���E */
	GgafWorld* _pWorld;


	/** fps�l�i��1000ms���Ɍv�Z�����j */
	float _fFps;
	/** �O��fps�v�Z���̃V�X�e������ */
	DWORD _dwTime_Prev;
	/** �`��t���[���J�E���^ */
	DWORD _dwFrame_Visualize;
	/** �O��fps�v�Z���̕`��t���[���J�E���g�l */
	DWORD _dwFrame_PrevVisualize;



	bool _isBehaved;
	GgafGod();

	/**
	 * �_�̑���<BR>
	 */
	void be();

	/**
	 * ���E�𑶍݂�����<BR>
	 */
	virtual void makeWorldBe() {
		_pWorld -> nextFrame();
		_pWorld -> behave();
	};

	/**
	 * ���E��R������<BR>
	 */
	virtual void makeWorldJudge() {
		_pWorld -> judge();
	};

	/**
	 * ���E���������<BR>
	 */
	virtual void void makeWorldMaterialize() {
		_pWorld -> drawPrior();
		_pWorld -> drawMain();
		_pWorld -> drawTerminate();
	};

	/**
	 * ���E�����o������<BR>
	 */
	virtual void makeWorldVisualize() {
		_pWorld -> dump();
	};

	/**
	 * ���E�̌�n��<BR>
	 */
	virtual void makeWorldFinalize() {
		_pWorld -> finally();
		//_pWorld -> cleane();//���񂾂̂𖕏�
	};

	/**
	 * ���E���擾<BR>
	 * @return ���E
	 */
	virtual GgafWorld* getWorld(){
		return _pWorld;
	}

	/**
	 * ���E��n��<BR>
	 * @return ���E
	 */
	virtual GgafWorld* createWorld() = 0;


	virtual ~GgafGod();
};



#endif /*GGAFGOD_H_*/
