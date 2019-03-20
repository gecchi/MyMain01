#ifndef GGAF_DX_D3DXANIMESHACTOR_H_
#define GGAF_DX_D3DXANIMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * �t���[���A�j���[�V�����t�����b�V���A�N�^�[.
 * FigureActor ���p�����AX�t�@�C����`��
 * �t���[���A�j���[�V�������b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł�<BR>
 * �A�j���[�V�����̓p�y�b�^�[(Puppeteer)�ɂ��肢���܂��B<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class D3DXAniMeshActor : public FigureActor {

public:
    static DWORD FVF;
    /** ���f�� */
    D3DXAniMeshModel* _pD3DXAniMeshModel;
    /** �G�t�F�N�g���� */
    D3DXAniMeshEffect* _pD3DXAniMeshEffect;
    /** �p�y�b�^�[�i�A�j���[�V��������I�u�W�F�N�g) */
    Puppeteer* _pPuppeteer;

    LPD3DXANIMATIONSET* _papAnimationSet;

public:
    D3DXAniMeshActor(const char* prm_name,
                     const char* prm_model_id,
                     const char* prm_effect_id,
                     const char* prm_technique,
                     Checker* prm_pChecker);

    virtual void processDraw() override;

    virtual ~D3DXAniMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_D3DXANIMESHACTOR_H_*/
