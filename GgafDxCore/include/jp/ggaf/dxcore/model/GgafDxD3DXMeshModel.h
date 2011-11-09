#ifndef GGAFDXD3DXMESHMODEL_H_
#define GGAFDXD3DXMESHMODEL_H_
namespace GgafDxCore {

/**
 * ���b�V�����f���N���X(GgafDxD3DXActor�p).
 * GgafDxD3DXMeshModel �� D3DXLoadMeshFromX ���g�p���āAX�t�@�C�����烂�f���f�[�^��ǂݍ��݁A<BR>
 * �`�悷��@�\���������ÓI���f���p�̃N���X�ł��B
 * ��������
 * �ED3DXLoadMeshFromX ���g�p���ēǂݍ��ނ��߁A���G��X�t�@�C���ł����Ȃ��ǂ݂��ݕ`��ł���B
 * �E�@���D��B���f�����O�c�[���ō�����Ƃ���̌����ڂɂȂ�B
 * ���Z����
 * �E���̃��f���N���X�S�ɔ�ׂāA���x�ʂŗ��B�ǂݍ���� DrawSubset() ���邾���B
 * @version 1.00
 * @since 2008/02/22
 * @author Masatoshi Tsuge
 */
class GgafDxD3DXMeshModel : public GgafDxModel {
    friend class GgafDxModelManager;

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
    GgafDxD3DXMeshModel(char* prm_model, DWORD prm_dwOptions);

    /**
     * GgafDxD3DXMeshModel�I�u�W�F�N�g�̕`��<BR>
     * @param	prm_pActor_Target �`�悷��GgafDxD3DXMeshActor
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxD3DXMeshModelManager�ł���<BR>
     */
    virtual ~GgafDxD3DXMeshModel(); //�f�X�g���N�^

};

}
#endif /*GGAFDXD3DXMESHMODEL_H_*/