#ifndef GGAFDX9UNTRANSFORMEDACTOR_H_
#define GGAFDX9UNTRANSFORMEDACTOR_H_

class GgafDx9UntransformedActor : public GgafDx9MainActor {

private:


public:

	/** ���[���hX���W */
	int _X;
	/** ���[���hY���W */
	int _Y;
	/** ���[���hZ���W */
	int _Z;
//	/** �t���[�������[���hX���W�̑��� */
//	int _incX;
//	/** �t���[�������[���hY���W�̑��� */
//	int _incY;
//	/** �t���[�������[���hZ���W�̑��� */
//	int _incZ;

	/** ���[���hX����]�p */
	int _RX;
	/** ���[���hY����]�p */
	int _RY;
	/** ���[���hZ����]�p */
	int _RZ;
//	/** �t���[�������[���hX����]�p�̑��� */
//	int _incRX;
//	/** �t���[�������[���hY����]�p�̑��� */
//	int _incRY;
//	/** �t���[�������[���hZ����]�p�̑��� */
//	int _incRZ;

	/** ���[���hX�������{�� */
	int _SX;
	/** ���[���hY�������{�� */
	int _SY;
	/** ���[���hZ�������{�� */
	int _SZ;

	//�⑫
	//�y_X, _Y, _Z �̒P�ʂɂ��āz
	//�@�̂蓾��l�� DirectX9�̃��[���h���W(float)*1000 �̒l�ł���B
	//�@�`��̒��O�� 1000 �ŏ��Z���ꕽ�s�ړ��̃��[���h�ϊ��Ɏg�p�����B
	//�@�Ȃ�ł��Ƃ����Ɛ����ō��W�v�Z���ď����ł��������������߁B
	//�y_RX, _RY, _RZ �̒P�ʂɂ��āz
	//�@�Ǝ��P�ʂ́u�A���O���l�v���̂�B�u�A���O���l�v�Ƃ� 0~360000 �̒l�ŁA1000�{�̐��x�̊p�x�l�ł���B
	//�@�~���p�Ɠ�����3���̕�����0�Ƃ��A�����v���ɃA���O���l�͑�������̂Ƃ���B���p�̒l��90000�A������180000�ł���B
	//�y_SX, _SY, _SZ �̒P�ʂɂ��āz
	//�@�`��̒��O�� 1000 �ŏ��Z����A�X�P�[���̃��[���h�ϊ��Ɏg�p�����B
	//�@1000���P�{�̃X�P�[���Ӗ�����B


	GgafDx9GeometryMover* _pGeoMover;

	GgafDx9GeometryChecker* _pGeoChecker;


	const int _X_OffScreenLeft;
	const int _X_OffScreenRight;
	const int _Y_OffScreenTop;
	const int _Y_OffScreenBottom;


	/**
	 * �R���X�g���N�^<BR>
	 * @param	prm_name ���ʖ�
	 */
	GgafDx9UntransformedActor(string prm_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

	virtual GgafDx9UntransformedActor* getPrev() {
		return (GgafDx9UntransformedActor*)GgafActor::getPrev();
	}

	virtual GgafDx9UntransformedActor* getNext() {
		return (GgafDx9UntransformedActor*)GgafActor::getNext();
	}

	virtual bool processBumpChkLogic(GgafActor* prm_pActor_Opponent);

	virtual bool isOffScreen() { return false; }

	virtual void setGeometry(int X, int Y, int Z) {
		_X = X;
		_Y = Y;
		_Z = Z;
	}

	/**
	 * _Z�̒l�ɂ��A��܂��Ƀ����_�����O������ݒ肷��B
	 * �C�ӂ̗D�揇�ʂŃ����_�����O�������ꍇ�́A���̃��\�b�h���I�[�o�[���C�h��
	 * GgafWorld::_apActorDrawDepthLevel_first[n] �̍D���� n �� addSubLast(this) ���s���ĉ������B
	 * �A�� 0 �� n �� MAX_DRAW_DEPTH_LEVEL
	 */
	virtual void processDrawPrior();

	virtual ~GgafDx9UntransformedActor();		//�f�X�g���N�^


};


#endif /*GGAFDX9UNTRANSFORMEDACTOR_H_*/
