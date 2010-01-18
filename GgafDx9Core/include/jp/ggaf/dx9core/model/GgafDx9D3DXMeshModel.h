#ifndef GGAFDX9D3DXMESHMODEL_H_
#define GGAFDX9D3DXMESHMODEL_H_
namespace GgafDx9Core {

/**
 * ���b�V�����f���N���X(GgafDx9D3DXActor�p).
 * GgafDx9D3DXMeshModel �� D3DXLoadMeshFromX ���g�p���āAX�t�@�C�����烂�f���f�[�^��ǂݍ��݁A<BR>
 * �`�悷��@�\���������ÓI���f���p�̃N���X�ł��B
 * ��������
 * �ED3DXLoadMeshFromX ���g�p���ēǂݍ��ނ��߁A���G��X�t�@�C���ł����Ȃ��ǂ݂��ݕ`��ł���B
 * ���Z����
 * �E���̃��f���N���X�S�ɔ�ׂāA�`��̍œK���Ƃ����ʂł͗��B�ǂݍ���� DrawSubset() ���邾���B
 * @version 1.00
 * @since 2008/02/22
 * @author Masatoshi Tsuge
 */
class GgafDx9D3DXMeshModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

public:
    /** ���b�V��(�C���X�^���X�̓��f�����j */
    LPD3DXMESH _pID3DXMesh;
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
    virtual HRESULT draw(GgafDx9DrawableActor* prm_pActor_Target) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    virtual void release() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9D3DXMeshModelManager�ł���<BR>
     */
    virtual ~GgafDx9D3DXMeshModel(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9D3DXMESHMODEL_H_*/
