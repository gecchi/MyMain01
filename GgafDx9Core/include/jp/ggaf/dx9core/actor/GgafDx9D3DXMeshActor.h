#ifndef GGAFDX9D3DXMESHACTOR_H_
#define GGAFDX9D3DXMESHACTOR_H_
namespace GgafDx9Core {

/**
 * DirectX���b�V���A�N�^�[.
 * GgafDx9DrawableActor ���p�����AX�t�@�C����`�̃��b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł�<BR>
 * @version 1.00
 * @since 2008/01/28
 * @author Masatoshi Tsuge
 */
class GgafDx9D3DXMeshActor : public GgafDx9DrawableActor {
private:

public:
    static DWORD FVF;
    /** ���f�� */
    GgafDx9D3DXMeshModel* _pD3DXMeshModel;
    /** �G�t�F�N�g���� */
    GgafDx9MeshEffect* _pMeshEffect;

    GgafDx9D3DXMeshActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique,
                         GgafDx9Checker* prm_pChecker);

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processDraw() override;

    /**
     * ���ݒ�.
     * ���I�[�o�[���C�g��
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha) override;

    virtual ~GgafDx9D3DXMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9D3DXMESHACTOR_H_*/
