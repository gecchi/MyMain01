#ifndef GGAFDX9MESHSETACTOR_H_
#define GGAFDX9MESHSETACTOR_H_
namespace GgafDx9Core {

/**
 * ���b�V���A�N�^�[.
 * GgafDx9DrawableActor ���p�����AX�t�@�C����`�̃��b�V���\���@�\��<BR>
 * �ǉ��A����ɓ��ꃂ�f�������I�u�W�F�N�g�̒��_�o�b�t�@�������A��ʕ\���ɍœK�������A�N�^�[�ł�<BR>
 * @version 1.00
 * @since 2009/06/16
 * @author Masatoshi Tsuge
 */
class GgafDx9MeshSetActor : public GgafDx9DrawableActor {
private:

public:

    /** ���f������ */
    GgafDx9MeshSetModel* _pMeshSetModel;
    /** �G�t�F�N�g���� */
    GgafDx9MeshSetEffect* _pMeshSetEffect;

    /** �`�掞�̃I�u�W�F�N�g�� */
    int _draw_set_num;
    //int _draw_object_num;


    /**
     * �R���X�g���N�^
     * @param prm_name  ���f�����́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model ���f����`���A������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g(GgafDx9MeshSetEffect.fx) �̃e�N�j�b�N�B
     * @param prm_pChecker   �l�X�Ȕ�����s�Ȃ��`�F�b�J�[�N���X�̃C���X�^���X��n��
     */
    GgafDx9MeshSetActor(const char* prm_name,
                        const char* prm_model_id,
                        const char* prm_effect_id,
                        const char* prm_technique,
                        GgafDx9Checker* prm_pChecker );

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processDraw() override;

    /**
     * ���ݒ�.
     * ���I�[�o�[���C�g��
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha) override;


//    int chkSequenceOfTheSameDrawDepth() {
//
//
//    }

    virtual ~GgafDx9MeshSetActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9MESHSETACTOR_H_*/
