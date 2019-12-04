#ifndef GGAF_DX_ANIMESHACTOR_H_
#define GGAF_DX_ANIMESHACTOR_H_
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
class AniMeshActor : public FigureActor {

public:
    static DWORD FVF;
    /** ���f�� */
    AniMeshModel* _pAniMeshModel;
    /** �G�t�F�N�g���� */
    AniMeshEffect* _pAniMeshEffect;
    /** �p�y�b�^�[�i�A�j���[�V��������I�u�W�F�N�g) */
    Puppeteer* _pPuppeteer;

    LPD3DXANIMATIONSET* _papAnimationSet;

public:
    AniMeshActor(const char* prm_name,
                     const char* prm_model_id,
                     const char* prm_effect_id,
                     const char* prm_technique,
                     Checker* prm_pChecker);

    virtual void processDraw() override;

    virtual ~AniMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_ANIMESHACTOR_H_*/
