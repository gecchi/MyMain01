#ifndef GGAFDX9CUBEMAPMORPHMESHACTOR_H_
#define GGAFDX9CUBEMAPMORPHMESHACTOR_H_
namespace GgafDx9Core {

/**
 * ���}�b�v���[�t���b�V���A�N�^�[.
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeMapMorphMeshActor : public GgafDx9MorphMeshActor, public GgafDx9ICubeMapActor {
private:

public:
    /** ���f������ */
    GgafDx9CubeMapMorphMeshModel* _pCubeMapMorphMeshModel;
    /** �G�t�F�N�g���� */
    GgafDx9CubeMapMorphMeshEffect* _pCubeMapMorphMeshEffect;

    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model_id ���f����`���A������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����NULL�ł悢�j
     * @return
     */
    GgafDx9CubeMapMorphMeshActor(const char* prm_name,
                                 const char* prm_model_id,
                                 const char* prm_effect_id,
                                 const char* prm_technique,
                                 GgafCore::GgafStatus* prm_pStat,
                                 GgafDx9Checker* prm_pChecker );


    virtual void processDraw() override;

//    virtual void end(frame prm_offset_frames = 1) override�G

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
        } else if (prm_no == GGAF_EVENT_DEVICE_LOST_REDEPOSITORY) {
            restoreCubeMapTex();
        }
    }

    virtual ~GgafDx9CubeMapMorphMeshActor (); //�f�X�g���N�^
};

}
#endif /*GGAFDX9CUBEMAPMORPHMESHACTOR_H_*/
