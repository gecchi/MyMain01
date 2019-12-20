#ifndef GGAF_DX_SKINANIMESHACTOR_H_
#define GGAF_DX_SKINANIMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

#include "jp/ggaf/dx/util/SkinAniMeshWorldMatStack.h"

namespace GgafDx {

/**
 * �X�L���A�j���[�V�����t�����b�V���A�N�^�[.
 * FigureActor ���p�����AX�t�@�C����`��
 * �t���[���A�j���[�V�������b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł�<BR>
 * �A�j���[�V�����̓p�y�b�^�[(Puppeteer)�ɂ��肢���܂��B<BR>
 * @version 1.00
 * @since 2019/12/20
 * @author Masatoshi Tsuge
 */
class SkinAniMeshActor : public FigureActor {

public:
    static DWORD FVF;
    /** ���f�� */
    SkinAniMeshModel* _pSkinAniMeshModel;
    /** �G�t�F�N�g���� */
    SkinAniMeshEffect* _pSkinAniMeshEffect;
    /** �p�y�b�^�[�i�A�j���[�V��������I�u�W�F�N�g) */
    Puppeteer* _pPuppeteer;

    SkinAniMeshWorldMatStack _stackWorldMat;

    LPD3DXANIMATIONSET* _papAnimationSet;

public:
    SkinAniMeshActor(const char* prm_name,
                 const char* prm_model_id,
                 const char* prm_effect_id,
                 const char* prm_technique,
                 Checker* prm_pChecker);

    virtual void processDraw() override;

    virtual Puppeteer* getPuppeteer() {
        return _pPuppeteer;
    }

    virtual ~SkinAniMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_SKINANIMESHACTOR_H_*/
