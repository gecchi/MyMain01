#ifndef GGAFDX9XMESHMODEL_H_
#define GGAFDX9XMESHMODEL_H_

class GgafDx9MeshModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

public:
	/** ���b�V��(ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�j */
	LPD3DXMESH			_pID3DXMesh;
	/** �}�e���A��(D3DMATERIAL9�\���̂�v�f�Ƃ���z��̐擪�A�h���X���w���|�C���^�j */
	D3DMATERIAL9* 		_paD3DMaterial9;
	/** �e�N�X�`��(IDirect3DTexture9�C���^�[�t�F�C�X�ւ̃|�C���^��v�f�Ƃ���z��̐擪�A�h���X���w���|�C���^�j */
	LPDIRECT3DTEXTURE9* _papID3DTexture9;
	/** ���b�V���Ɋ܂܂��e�ʂ̗אږʂ��i�[����|�C���^ */
//	LPD3DXBUFFER	_pAdjacency;
	/** �}�e���A����(=���b�V����) */
	DWORD               _dwNumMaterials;

public:
	/**
	 * �R���X�g���N�^<BR>
	 * @param	���f���̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
	 */
	GgafDx9MeshModel(string prm_meshmodel_name);

	/**
	 * GgafDx9MeshModel�I�u�W�F�N�g�̕`��<BR>
	 * @param	prm_pActor_Target �`�悷��GgafDx9MeshActor
	 * @return	HRESULT
	 */
	virtual HRESULT draw(GgafDx9MainActor* prm_pActor_Target);

	virtual void restore();

	virtual void onDeviceLost();

	/**
	 * �f�X�g���N�^<BR>
	 * delete����̂�GgafDx9MeshModelManager�ł���<BR>
	 */
	virtual ~GgafDx9MeshModel();		//�f�X�g���N�^

};

#endif /*GGAFDX9XMESHMODEL_H_*/
