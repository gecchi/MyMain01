#ifndef GGAFDXCUBEMAPMESHSETACTOR_H_
#define GGAFDXCUBEMAPMESHSETACTOR_H_
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

    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model_id ���f����`���A������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� NULL�ł悢)
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����NULL�ł悢�j
     * @return
     */
    GgafDxCubeMapMeshSetActor(const char* prm_name,
                               const char* prm_model_id,
                               const char* prm_effect_id,
                               const char* prm_technique,
                               GgafCore::GgafStatus* prm_pStat,
                               GgafDxChecker* prm_pChecker );

    virtual void processDraw() override;

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual ~GgafDxCubeMapMeshSetActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCUBEMAPMESHSETACTOR_H_*/