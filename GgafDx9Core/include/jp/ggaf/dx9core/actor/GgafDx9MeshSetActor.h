#ifndef GGAFDX9MESHSETACTOR_H_
#define GGAFDX9MESHSETACTOR_H_
namespace GgafDx9Core {

/**
 * ���b�V���A�N�^�[.
 * GgafDx9DrawableUntransformedActor ���p�����AX�t�@�C����`�̃��b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł�<BR>
 */
class GgafDx9MeshSetActor : public GgafDx9DrawableUntransformedActor {
private:

public:

    /** ���f������ */
    GgafDx9MeshSetModel* _pMeshSetModel;
    /** �G�t�F�N�g���� */
    GgafDx9MeshSetEffect* _pMeshSetEffect;

    D3DXMATRIX _aMatWorld[16];
    int _set_index;
    int _draw_object_num;


    /**
     * �R���X�g���N�^
     * @param prm_name  ���f�����́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model ���f����`���A������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g(GgafDx9MeshSetEffect.fx) �̃e�N�j�b�N�B
     * @param prm_pChecker   �l�X�Ȕ�����s�Ȃ��`�F�b�J�[�N���X�̃C���X�^���X��n��
     */
    GgafDx9MeshSetActor(const char* prm_name,
                     const char* prm_model,
                     const char* prm_effect,
                     const char* prm_technique,
                     GgafDx9Checker* prm_pChecker );

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processDrawMain();

    /**
     * ���ݒ�.
     * ���I�[�o�[���C�g��
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha);


    int chkSequenceOfTheSameDrawDepth() {


    }

    virtual ~GgafDx9MeshSetActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9MESHSETACTOR_H_*/
