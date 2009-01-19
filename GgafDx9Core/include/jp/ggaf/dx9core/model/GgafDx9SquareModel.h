#ifndef GGAFDX9SQUAREMODEL_H_
#define GGAFDX9SQUAREMODEL_H_
namespace GgafDx9Core {


class GgafDx9SquareModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

protected:
	struct VERTEX{
		float x, y, z;    // ���_���W
		float nx, ny, nz; // �@��
		DWORD color;      // ���_�̐F
//		float tu, tv;     // �e�N�X�`�����W
	};
	/** VERTEX��FVF */
	static DWORD FVF;
	/** �}�e���A�� */
	D3DMATERIAL9* 		_pD3DMaterial9;
//	/** �e�N�X�`��(�A�j���[�V�����p�^�[���j */
//	LPDIRECT3DTEXTURE9 _pID3DTexture9;
	/** ��`�̒��_���v�̃T�C�Y */
	UINT _iSize_Vertecs;
	/** 1���_�̃T�C�Y */
	UINT _iSize_Vertec_unit;
//	/** �A�j���[�V���[���̂��߂̃e�N�X�`���̍��W�̔z��i�v�f���̓A�j���[�V�������j */
//	GgafDx9RectUV*  _paRectUV;


	/** ���_�o�b�t�@�ւ̃|�C���^ */
	LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;


public:
	/** �S�A�j���p�^�[���� */
//	int _iAnimationPatternNo_Max;
//	float  _fSize_SquareModelWidth;
//	float  _fSize_SquareModelHeight;
//	int    _iRowNum_TextureSplit;
//	int    _iColNum_TextureSplit;

	/**
	 * �R���X�g���N�^<BR>
	 * @param prm_squaremodel_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
	 */
	GgafDx9SquareModel(string prm_squaremodel_name);

	/**
	 * GgafDx9SquareModel�I�u�W�F�N�g�̕`��<BR>
	 * @param	prm_pActor_Target �`�悷��GgafDx9SquareActor
	 * @return	HRESULT
	 */
	virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target);

	virtual void restore();

	virtual void onDeviceLost();
	/**
	 * �f�X�g���N�^<BR>
	 * delete����̂�GgafDx9SquareModelManager�ł���<BR>
	 */
	virtual ~GgafDx9SquareModel();		//�f�X�g���N�^

};


}
#endif /*GGAFDX9SQUAREMODEL_H_*/
