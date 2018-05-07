#ifndef GGAFDXCORE_GGAFDXMASSMESHACTOR_H_
#define GGAFDXCORE_GGAFDXMASSMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassActor.h"
#include "jp/ggaf/dxcore/model/GgafDxMassMeshModel.h"

namespace GgafDxCore {

/**
 * ���b�V���A�N�^�[.
 * GgafDxFigureActor ���p�����AX�t�@�C����`�̃��b�V���\���@�\��<BR>
 * �C���X�^���V���O�ɂ��A��ʕ\���ɍœK�������A�N�^�[�ł�<BR>
 * @version 1.00
 * @since 2016/02/09
 * @author Masatoshi Tsuge
 */
class GgafDxMassMeshActor : public GgafDxMassActor {

public:
    /** [r]���f������ */
    GgafDxMassMeshModel* const _pMassMeshModel;
    /** [r]�G�t�F�N�g���� */
    GgafDxMassMeshEffect* const _pMassMeshEffect;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model_id ���f����`���A������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� nullptr�ł悢)
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     * @return
     */
    GgafDxMassMeshActor(const char* prm_name,
                        const char* prm_model_id,
                        const char* prm_effect_id,
                        const char* prm_technique,
                        GgafCore::GgafStatus* prm_pStat,
                        GgafDxChecker* prm_pChecker );


    /**
     * ���ʌp���p�R���X�g���N�^
     * @param prm_name �A�N�^�[���́i�C�Ӂj
     * @param prm_model_id ���f����`��
     * @param prm_model_type ���f���^�C�v
     * @param prm_effect_id �G�t�F�N�g��`��
     * @param prm_effect_type �G�t�F�N�g�^�C�v
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� nullptr�ł悢)
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     * @return
     */
    GgafDxMassMeshActor(const char* prm_name,
                        const char* prm_model_id,
                        const char prm_model_type,
                        const char* prm_effect_id,
                        const char prm_effect_type,
                        const char* prm_technique,
                        GgafCore::GgafStatus* prm_pStat,
                        GgafDxChecker* prm_pChecker);

    virtual ~GgafDxMassMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXMASSMESHACTOR_H_*/
