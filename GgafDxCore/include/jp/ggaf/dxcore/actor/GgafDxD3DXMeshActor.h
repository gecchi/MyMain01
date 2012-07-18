#ifndef GGAFDXD3DXMESHACTOR_H_
#define GGAFDXD3DXMESHACTOR_H_
namespace GgafDxCore {

/**
 * DirectX���b�V���A�N�^�[.
 * GgafDxDrawableActor ���p�����AX�t�@�C����`�̃��b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł�<BR>
 * @version 1.00
 * @since 2008/01/28
 * @author Masatoshi Tsuge
 */
class GgafDxD3DXMeshActor : public GgafDxDrawableActor {
private:

public:
    static DWORD FVF;
    /** [r]���f�� */
    GgafDxD3DXMeshModel* _pD3DXMeshModel;
    /** [r]�G�t�F�N�g���� */
    GgafDxMeshEffect* _pMeshEffect;

    GgafDxD3DXMeshActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique,
                         GgafCore::GgafStatus* prm_pStat,
                         GgafDxChecker* prm_pChecker);

    /**
     * GgafDxD3DXMeshActor��`�� .
     */
    virtual void processDraw() override;

    /**
     * ���ݒ�.
     * @param prm_alpha
     */
    virtual void setAlpha(float prm_alpha) override;

    /**
     * �����Z .
     * @param prm_alpha
     */
    virtual void addAlpha(float prm_alpha) override;

    virtual ~GgafDxD3DXMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDXD3DXMESHACTOR_H_*/
