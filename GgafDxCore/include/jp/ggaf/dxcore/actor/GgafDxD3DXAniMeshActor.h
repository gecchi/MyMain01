#ifndef GGAFDXD3DXANIMESHACTOR_H_
#define GGAFDXD3DXANIMESHACTOR_H_
namespace GgafDxCore {

/**
 * �t���[���A�j���[�V�����t�����b�V���A�N�^�[.
 * GgafDxDrawableActor ���p�����AX�t�@�C����`��
 * �t���[���A�j���[�V�������b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł�<BR>
 * �A�j���[�V�����̓p�y�b�^�[(GgafDxPuppeteer)�ɂ��肢���܂��B<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class GgafDxD3DXAniMeshActor : public GgafDxDrawableActor {
private:

public:
    static DWORD FVF;
    /** ���f�� */
    GgafDxD3DXAniMeshModel* _pD3DXAniMeshModel;
    /** �G�t�F�N�g���� */
    GgafDxD3DXAniMeshEffect* _pD3DXAniMeshEffect;
    /** �p�y�b�^�[�i�A�j���[�V��������I�u�W�F�N�g) */
    GgafDxPuppeteer* _pPuppeteer;

    LPD3DXANIMATIONSET* _papAnimationSet;

    GgafDxD3DXAniMeshActor(const char* prm_name,
                             const char* prm_model_id,
                             const char* prm_effect_id,
                             const char* prm_technique,
                             GgafCore::GgafStatus* prm_pStat,
                             GgafDxChecker* prm_pChecker);

    virtual void processDraw() override;

    /**
     * ���ݒ�.
     * @param prm_alpha
     */
    void setAlpha(float prm_alpha) override;

    /**
     * �����Z .
     * @param prm_alpha
     */
    void addAlpha(float prm_alpha) override;

    virtual ~GgafDxD3DXAniMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDXD3DXANIMESHACTOR_H_*/
