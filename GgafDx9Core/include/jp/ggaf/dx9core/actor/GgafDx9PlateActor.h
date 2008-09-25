#ifndef GGAFDX9PLATEACTORD_H_
#define GGAFDX9PLATEACTORD_H_


class GgafDx9PlateActor : public GgafDx9TransformedActor {
private:

	struct VERTEX{
		float x, y, z;    // ���_���W
		float rhw;
		D3DCOLOR color;
		float tu, tv;     // �e�N�X�`�����W
	};

	/** �����A�j���p�^�[���p�J�E���^�[ */
	int _iCounter_PatternNo;
	/** �����A�j���t���[���p�J�E���^ */
	int _iCounter_AnimationFrame;

public:
	GgafDx9PlateModel* _pPlateModel;


	/** ��`�̒��_��� */
	VERTEX* _paVertex;
	/** ��`�̒��_���v�̃T�C�Y */
	UINT _iSize_Vertecs;
	/** 1���_�̃T�C�Y */
	UINT _iSize_Vertec_unit;

	/** �A�j���p�^�[���ԍ��̏���ԍ� */
	int _iPatternNo_Top;
	/** ���ݕ\�����̃A�j���p�^�[���ԍ� */
	int _iPatternNo_Bottom;
	/** ���ݕ\�����̃A�j���p�^�[���ԍ� */
	int _iPatternNo_Active;


	GgafDx9PlateActor(string prm_name, string prm_spritemodel_name);

 	/**
	 * ��OverRide �ł���<BR>
	 */
	virtual void processDrawMain();

	virtual void setPatternNo(int prm_iPlateNo);

	virtual ~GgafDx9PlateActor();		//�f�X�g���N�^

	//virtual void setCoordinates(float prm_x, float prm_y, float prm_z);


};

#endif /*GGAFDX9PLATEACTORD_H_*/
