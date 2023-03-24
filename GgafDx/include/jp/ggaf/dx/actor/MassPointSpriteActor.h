#ifndef GGAF_DX_MASSPOINTSPRITEACTOR_H_
#define GGAF_DX_MASSPOINTSPRITEACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MassActor.h"
#include "jp/ggaf/dx/model/MassPointSpriteModel.h"

namespace GgafDx {

/**
 * TODO:���ݎg���܂���B�r�f�I�J�[�h�ˑ��������ׁB
 * @version 1.00
 * @since 2016/05/16
 * @author Masatoshi Tsuge
 */
class MassPointSpriteActor : public MassActor {

public:
    /** [r]���f������ */
    MassPointSpriteModel* _pMassPointSpriteModel;
    /** [r]�G�t�F�N�g���� */
    MassPointSpriteEffect* const _pMassPointSpriteEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    UvFlipper* const _pUvFlipper;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model ���f����`���A������ ".psprx" ���������f����`�t�@�C�����ǂݍ��܂��B
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     * @return
     */
    MassPointSpriteActor(const char* prm_name,
                         const char* prm_model,
                         const char* prm_effect_id,
                         const char* prm_technique,
                         CollisionChecker* prm_pChecker );

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    /**
     * ���f������(MeshModel)��؂�ւ���i�\�����؂�ւ��܂��j .
     * @param prm_model_index ���f�������ێ����X�g�̃C���f�b�N�X�B
     *                        �ŏ���   addModel() �ɐ؂�ւ� => 0 ��ݒ�
     *                        �Q��ڂ� addModel() �ɐ؂�ւ� => 1 ��ݒ�
     *                        �R��ڂ� addModel() �ɐ؂�ւ� => 2 ��ݒ�
     *                         �c
     */
    virtual void changeModelByIndex(int prm_model_index) override;

    virtual ~MassPointSpriteActor();
};

}
#endif /*GGAF_DX_MASSSPRITEACTOR_H_*/
