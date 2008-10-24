#ifndef GGAFDX9PLATEMODEL_H_
#define GGAFDX9PLATEMODEL_H_

class GgafDx9PlateModel : public GgafDx9Model {
    friend class GgafDx9PlateModelManager;
    friend class GgafDx9PlateActor;

public:

	/** VERTEX��FVF */
	static DWORD FVF;
	// /** �}�e���A�� */
	// D3DMATERIAL9* 		_pD3DMaterial9;
	//
	/** �e�N�X�`��(�A�j���[�V�����p�^�[���j */
	LPDIRECT3DTEXTURE9 _pID3DTexture9;

	/** �A�j���[�V���[���̂��߂̃e�N�X�`���̍��W�̔z��i�v�f���̓A�j���[�V�������j */
	GgafDx9RectUV*  _paRectUV;


	/** �O��\����UV */
	GgafDx9RectUV*  _pRectUV_drawlast;


	/** �S�A�j���p�^�[���� */
	int _iPatternNo_Max;
	float  _fSize_PlateModelWidth;
	float  _fSize_PlateModelHeight;
	int    _iRowNum_TextureSplit;
	int    _iColNum_TextureSplit;

	/**
	 * �R���X�g���N�^<BR>
	 * @param	�X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
	 */
	GgafDx9PlateModel(string prm_platemodel_name);

	/**
	 * GgafDx9PlateModel�I�u�W�F�N�g�̕`��<BR>
	 * @param	prm_pActor_Target �`�悷��GgafDx9PlateActor
	 * @return	HRESULT
	 */
	virtual HRESULT draw(GgafDx9MainActor* prm_pActor_Target);

	virtual void restore();

	virtual void onDeviceLost();

	/**
	 * �f�X�g���N�^<BR>
	 * delete����̂�GgafDx9PlateModelManager�ł���<BR>
	 */
	virtual ~GgafDx9PlateModel();		//�f�X�g���N�^

};

#endif /*GGAFDX9PLATEMODEL_H_*/
