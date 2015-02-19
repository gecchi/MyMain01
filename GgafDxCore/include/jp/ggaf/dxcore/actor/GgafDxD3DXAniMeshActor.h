#ifndef GGAFDXCORE_GGAFDXD3DXANIMESHACTOR_H_
#define GGAFDXCORE_GGAFDXD3DXANIMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"

namespace GgafDxCore {

/**
 * �t���[���A�j���[�V�����t�����b�V���A�N�^�[.
 * GgafDxFigureActor ���p�����AX�t�@�C����`��
 * �t���[���A�j���[�V�������b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł�<BR>
 * �A�j���[�V�����̓p�y�b�^�[(GgafDxPuppeteer)�ɂ��肢���܂��B<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class GgafDxD3DXAniMeshActor : public GgafDxFigureActor {

public:
    static DWORD FVF;
    /** ���f�� */
    GgafDxD3DXAniMeshModel* _pD3DXAniMeshModel;
    /** �G�t�F�N�g���� */
    GgafDxD3DXAniMeshEffect* _pD3DXAniMeshEffect;
    /** �p�y�b�^�[�i�A�j���[�V��������I�u�W�F�N�g) */
    GgafDxPuppeteer* _pPuppeteer;

    LPD3DXANIMATIONSET* _papAnimationSet;

public:
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
    virtual void setAlpha(float prm_alpha) override;

    /**
     * �����Z .
     * @param prm_alpha
     */
    virtual void addAlpha(float prm_alpha) override;

    virtual ~GgafDxD3DXAniMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXD3DXANIMESHACTOR_H_*/
