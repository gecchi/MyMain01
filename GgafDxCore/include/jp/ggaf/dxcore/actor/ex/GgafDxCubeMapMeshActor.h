#ifndef GGAFDXCUBEMAPMESHACTOR_H_
#define GGAFDXCUBEMAPMESHACTOR_H_
namespace GgafDxCore {

/**
 * ���}�b�v���b�V���A�N�^�[.
 * GgafDxMeshActor ���p�����A���}�b�v�e�N�X�`�������������A�N�^�[�ł��B<BR>
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class GgafDxCubeMapMeshActor : public GgafDxMeshActor, public GgafDxICubeMapActor  {

public:

    /** ���f������ */
    GgafDxCubeMapMeshModel* _pCubeMapMeshModel;
    /** �G�t�F�N�g���� */
    GgafDxCubeMapMeshEffect* _pCubeMapMeshEffect;

    /**
     * �R���X�g���N�^
     * @param prm_name ���f�����́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model_id ���f����`���B������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� NULL�ł悢)
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����NULL�ł悢�j
     */
    GgafDxCubeMapMeshActor(const char* prm_name,
                            const char* prm_model_id,
                            const char* prm_effect_id,
                            const char* prm_technique,
                            GgafCore::GgafStatus* prm_pStat,
                            GgafDxChecker* prm_pChecker );


    virtual void processDraw() override;


    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }
//    /**
//     * �f�o�C�X���X�g�Ή��C�x���g���� .
//     * ���f���Ƃ͕ʊǗ��̃L���[�u�}�b�v�e�N�X�`���̉���ƍč\�z���������s���܂��B
//     * ���ʂ� onCatchEvent(UINT32, void*) �I�[�o�[���C�h�������ꍇ�́A��ʂ��Ăяo���ĉ������B
//     * @param prm_no
//     * @param prm_pSource
//     */
//    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
//        if (prm_no == GGAF_EVENT_ON_DEVICE_LOST) {
//            _TRACE_("GgafDxCubeMapMeshActor::onCatchEvent "<<getName()<<" GGAF_EVENT_ON_DEVICE_LOST �L���b�`");
//            releaseCubeMapTex();
//        } else if (prm_no == GGAF_EVENT_DEVICE_LOST_REDEPOSITORY) {
//            restoreCubeMapTex();
//        }
//    }

    virtual ~GgafDxCubeMapMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCUBEMAPMESHACTOR_H_*/
