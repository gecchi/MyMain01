#ifndef GGAFDX9PLATEACTORD_H_
#define GGAFDX9PLATEACTORD_H_
namespace GgafDx9Core {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[.
 * GgafDx9TransformedActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ������A�N�^�[�ł�<BR>
 */
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
	/** ���f���I�u�W�F�N�g�ւ̃|�C���^ */
	GgafDx9ModelLead* _pModelLead;
	GgafDx9PlateModel* _pPlateModel;
	/** �L�����S�̂̃� */
	float _fAlpha;

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


	GgafDx9PlateActor(char* prm_name, char* prm_spritemodel_name);

 	/**
	 * ��OverRide �ł���<BR>
	 */
	virtual void processDrawMain();

	virtual void setPatternNo(int prm_iPlateNo);

	void setAlpha(float prm_fAlpha) {
		_fAlpha = prm_fAlpha;
	}

	float getAlpha() {
		return _fAlpha;
	}

	virtual ~GgafDx9PlateActor();		//�f�X�g���N�^

	//virtual void setCoordinates(float prm_x, float prm_y, float prm_z);


};


}
#endif /*GGAFDX9PLATEACTORD_H_*/
