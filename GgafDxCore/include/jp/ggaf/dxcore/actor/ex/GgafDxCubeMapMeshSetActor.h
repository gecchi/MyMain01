#ifndef GGAFDXCORE_GGAFDXCUBEMAPMESHSETACTOR_H_
#define GGAFDXCORE_GGAFDXCUBEMAPMESHSETACTOR_H_
#include "jp/ggaf/dxcore/actor/GgafDxMeshSetActor.h"
#include "jp/ggaf/dxcore/actor/interface/GgafDxICubeMapActor.h"

namespace GgafDxCore {

/**
 * ���}�b�v���b�V���Z�b�g�A�N�^�[.
 * GgafDxMeshActor ���p�����A���}�b�v�e�N�X�`�������������A�N�^�[�ł��B<BR>
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDxCubeMapMeshSetActor : public GgafDxMeshSetActor, public GgafDxICubeMapActor {

public:

    /** ���f������ */
    GgafDxCubeMapMeshSetModel* _pCubeMapMeshSetModel;
    /** �G�t�F�N�g���� */
    GgafDxCubeMapMeshSetEffect* _pCubeMapMeshSetEffect;

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
    GgafDxCubeMapMeshSetActor(const char* prm_name,
                               const char* prm_model_id,
                               const char* prm_effect_id,
                               const char* prm_technique,
                               GgafCore::GgafStatus* prm_pStat,
                               GgafDxChecker* prm_pChecker );

    virtual void processDraw() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual ~GgafDxCubeMapMeshSetActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXCUBEMAPMESHSETACTOR_H_*/
