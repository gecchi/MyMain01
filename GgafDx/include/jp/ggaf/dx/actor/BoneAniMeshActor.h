#ifndef GGAF_DX_BONEANIMESHACTOR_H_
#define GGAF_DX_BONEANIMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

#include "jp/ggaf/dx/util/BoneAniMeshWorldMatStack.h"

namespace GgafDx {

/**
 * �t���[���A�j���[�V�����t�����b�V���A�N�^�[.
 * �t���[���A�j���[�V�������b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł�<BR>
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
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model ���f����`���A������ ".meshx" ���������f����`�t�@�C�����ǂݍ��܂��B
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     * @return
     */
    BoneAniMeshActor(const char* prm_name,
                     const char* prm_model,
                     const char* prm_effect_id,
                     const char* prm_technique,
                     CollisionChecker* prm_pChecker);

    virtual void processDraw() override;

    virtual Puppeteer* getPuppeteer() {
        return _pPuppeteer;
    }

    /**
     * ���f������(MeshModel)��؂�ւ���i�\�����؂�ւ��܂��j .
     * @param prm_model_index ���f�������ێ����X�g�̃C���f�b�N�X�B
     *                        �ŏ���   addModel() �ɐ؂�ւ� => 0 ��ݒ�
     *                        �Q��ڂ� addModel() �ɐ؂�ւ� => 1 ��ݒ�
     *                        �R��ڂ� addModel() �ɐ؂�ւ� => 2 ��ݒ�
     *                         �c
     */
    virtual void changeModel(int prm_model_index) override;

    virtual ~BoneAniMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_BONEANIMESHACTOR_H_*/
