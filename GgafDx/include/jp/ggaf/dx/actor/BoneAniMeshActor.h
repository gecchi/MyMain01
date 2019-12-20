#ifndef GGAF_DX_BONEANIMESHACTOR_H_
#define GGAF_DX_BONEANIMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

#include "jp/ggaf/dx/util/BoneAniMeshWorldMatStack.h"

namespace GgafDx {

/**
 * �t���[���A�j���[�V�����t�����b�V���A�N�^�[.
 * FigureActor ���p�����AX�t�@�C����`��
 * �t���[���A�j���[�V�������b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł�<BR>
 * �A�j���[�V�����̓p�y�b�^�[(Puppeteer)�ɂ��肢���܂��B<BR>
 * @version 1.00
 * @since 2019/11/26
 * @author Masatoshi Tsuge
 */
class BoneAniMeshActor : public FigureActor {

public:
    static DWORD FVF;
    /** ���f�� */
    BoneAniMeshModel* _pBoneAniMeshModel;
    /** �G�t�F�N�g���� */
    BoneAniMeshEffect* _pBoneAniMeshEffect;
    /** �p�y�b�^�[�i�A�j���[�V��������I�u�W�F�N�g) */
    Puppeteer* _pPuppeteer;

    BoneAniMeshWorldMatStack _stackWorldMat;

    LPD3DXANIMATIONSET* _papAnimationSet;

public:
    BoneAniMeshActor(const char* prm_name,
                 const char* prm_model_id,
                 const char* prm_effect_id,
                 const char* prm_technique,
                 Checker* prm_pChecker);

    virtual void processDraw() override;

    virtual Puppeteer* getPuppeteer() {
        return _pPuppeteer;
    }

    virtual ~BoneAniMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_BONEANIMESHACTOR_H_*/
