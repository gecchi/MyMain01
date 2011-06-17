#ifndef GGAFDX9CUBEMAPMESHACTOR_H_
#define GGAFDX9CUBEMAPMESHACTOR_H_
namespace GgafDx9Core {

/**
 * ���}�b�v���b�V���A�N�^�[.
 * GgafDx9MeshActor ���p�����A���}�b�v�e�N�X�`�������������A�N�^�[�ł��B<BR>
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeMapMeshActor : public GgafDx9MeshActor, public GgafDx9ICubeMapActor  {

public:

    /** ���f������ */
    GgafDx9CubeMapMeshModel* _pCubeMapMeshModel;
    /** �G�t�F�N�g���� */
    GgafDx9CubeMapMeshEffect* _pCubeMapMeshEffect;

    /**
     * �R���X�g���N�^
     * @param prm_name ���f�����́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model_id ���f����`���B������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����NULL�ł悢�j
     */
    GgafDx9CubeMapMeshActor(const char* prm_name,
                       const char* prm_model_id,
                       const char* prm_effect_id,
                       const char* prm_technique,
                       GgafDx9Checker* prm_pChecker );


    virtual void processDraw() override;

    /**
     * �f�o�C�X���X�g�Ή��C�x���g���� .
     * ���f���Ƃ͕ʊǗ��̃L���[�u�}�b�v�e�N�X�`���̉���ƍč\�z���������s���܂��B
     * ���ʂ� onCatchEvent(UINT32, void*) �I�[�o�[���C�h�������ꍇ�́A��ʂ��Ăяo���ĉ������B
     * @param prm_no
     * @param prm_pSource
     */
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
        if (prm_no == GGAF_EVENT_ON_DEVICE_LOST) {
            releaseCubeMapTex();
        } else if (prm_no == GGAF_EVENT_DEVICE_LOST_RESTORE) {
            restoreCubeMapTex();
        }
    }

    virtual ~GgafDx9CubeMapMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9CUBEMAPMESHACTOR_H_*/
