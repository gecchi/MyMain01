#ifndef GGAFDX9D3DXANIMESHACTOR_H_
#define GGAFDX9D3DXANIMESHACTOR_H_
namespace GgafDx9Core {

/**
 * �t���[���A�j���[�V�����t�����b�V���A�N�^�[.
 * GgafDx9DrawableActor ���p�����AX�t�@�C����`��
 * �t���[���A�j���[�V�������b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł�<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class GgafDx9D3DXAniMeshActor : public GgafDx9DrawableActor {
private:

public:
    static DWORD FVF;
    /** ���f�� */
    GgafDx9D3DXAniMeshModel* _pD3DXAniMeshModel;
    /** �G�t�F�N�g���� */
    GgafDx9D3DXAniMeshEffect* _pD3DXAniMeshEffect;

    GgafDx9Puppeteer* _pPuppeteer;

    LPD3DXANIMATIONSET* _papAnimationSet;

    GgafDx9D3DXAniMeshActor(const char* prm_name,
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
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha) override;

    /**
     * �����Z .
     * @param prm_fAlpha
     */
    void addAlpha(float prm_fAlpha) override;

    virtual ~GgafDx9D3DXAniMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9D3DXANIMESHACTOR_H_*/
