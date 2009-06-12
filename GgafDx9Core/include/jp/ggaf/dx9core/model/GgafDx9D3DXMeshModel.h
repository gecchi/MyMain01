#ifndef GGAFDX9D3DXMESHMODEL_H_
#define GGAFDX9D3DXMESHMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9D3DXActor�p���f���N���X.(���ݖ��g�p�H)
 * GgafDx9D3DXMeshModel �� D3DXLoadMeshFromX ���g�p���āAX�t�@�C�����烂�f���f�[�^��ǂݍ��ݐݒ肷��B<BR>
 */
class GgafDx9D3DXMeshModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

public:
    /** ���b�V��(�C���X�^���X�̓��f�����j */
    LPD3DXMESH _pID3DXMesh;
    /** �e�N�X�`���z��(�C���X�^���X�̓e�N�X�`�����A���f���Ƃ͕ʊǗ��j */
    GgafDx9TextureConnection** _papTextureCon;
    /** D3DXLoadMeshFromX�̃I�v�V���� */
    DWORD _dwOptions;

    /** ���b�V���Ɋ܂܂��e�ʂ̗אږʂ��i�[����|�C���^ */
    //	LPD3DXBUFFER	_pAdjacency;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model ���f���̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     * @param prm_dwOptions D3DXLoadMeshFromX�̃I�v�V����
     * @return
     */
    GgafDx9D3DXMeshModel(char* prm_model, DWORD prm_dwOptions);

    /**
     * GgafDx9D3DXMeshModel�I�u�W�F�N�g�̕`��<BR>
     * @param	prm_pActor_Target �`�悷��GgafDx9D3DXMeshActor
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target);

    virtual void restore();

    virtual void onDeviceLost();

    virtual void release();

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9D3DXMeshModelManager�ł���<BR>
     */
    virtual ~GgafDx9D3DXMeshModel(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9D3DXMESHMODEL_H_*/
