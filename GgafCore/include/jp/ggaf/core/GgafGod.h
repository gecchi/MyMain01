#ifndef GGAFGOD_H_
#define GGAFGOD_H_



class GgafGod : public GgafObject {

public:
	static int _s_iNumClean_Node;

	static DWORD _dwNextTimeOffset[];
	/** GgafSubcontractor::work �X���b�h�n���h��  */
	HANDLE _handleFactory01;
	/** GgafSubcontractor::work �X���b�hID  */
	unsigned int _thID01;
	/** �N���e�B�J���Z�N�V�����i�Z�}�t�H�j */
	static CRITICAL_SECTION CS1;
	static CRITICAL_SECTION CS2;
	/** �t���[���J�n�V�X�e������ */
	DWORD _dwTime_FrameBegin;
	/** ����GgafWorld�����������鎞�� */
	DWORD _dwTime_ScheduledNextFrame;
	/** �_�a������̃t���[���� */
	DWORD _dwFrame_God;
	/** �X�L�b�v�t���[���J�E���^ */
	DWORD _dwFrame_SkipCount;

	/** fps�l�i��1000ms���Ɍv�Z�����j */
	float _fFps;
	/** �O��fps�v�Z���̃V�X�e������ */
	DWORD _dwTime_Prev;
	/** �`��t���[���J�E���^ */
	DWORD _dwFrame_Visualize;
	/** �O��fps�v�Z���̕`��t���[���J�E���g�l */
	DWORD _dwFrame_PrevVisualize;

	/** �����̃��[���h�V�[�� */
	GgafWorld* _pWorld;

	GgafGod();

	/**
	 * ���݂���<BR>
	 */
	void be();

//	/**
//	 * �t���[����i�߂�<BR>
//	 */
//	virtual void nextFrame();

	/**
	 * ���E�𑶍݂�����<BR>
	 */
	virtual void makeWorldBe();

	/**
	 * ���E��R������<BR>
	 */
	virtual void makeWorldJudge();

	/**
	 * �������<BR>
	 */
	virtual void makeWorldMaterialize();

	/**
	 * ���o������<BR>
	 */
	virtual void makeWorldVisualize();

	/**
	 * �ŏI<BR>
	 */
	virtual void makeWorldFinalize();


	virtual GgafWorld* getWorld();

    /**
     * World�V�[�����쐬�B
	 */
	virtual GgafWorld* createWorld() = 0;


	virtual ~GgafGod();
};



#endif /*GGAFGOD_H_*/
