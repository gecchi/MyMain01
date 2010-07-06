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
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model_id ���f����`���A������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����NULL�ł悢�j
     * @return
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
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha) override;

    /**
     * �����Z .
     * @param prm_fAlpha
     */
    void addAlpha(float prm_fAlpha) override;


//    int chkSequenceOfTheSameDrawDepth() {
//
//
//    }

    virtual ~GgafDx9MeshSetActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9MESHSETACTOR_H_*/
