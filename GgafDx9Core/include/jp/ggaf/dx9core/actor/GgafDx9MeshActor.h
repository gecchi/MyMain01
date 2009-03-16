#ifndef GGAFDX9MESHACTOR_H_
#define GGAFDX9MESHACTOR_H_
namespace GgafDx9Core {

/**
 * ���b�V���A�N�^�[.
 * GgafDx9UntransformedActor ���p�����AX�t�@�C����`�̃��b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł�<BR>
 */
class GgafDx9MeshActor : public GgafDx9UntransformedActor {
private:

public:

    char* _technique;

    /** ���f�������ڑ� */
    GgafDx9ModelConnection* _pModelCon;
    /** ���f������ */
    GgafDx9MeshModel* _pMeshModel;
    /** �G�t�F�N�g�����ڑ� */
    GgafDx9EffectConnection* _pEffectCon;
    /** �G�t�F�N�g���� */
    GgafDx9MeshEffect* _pMeshEffect;


    /**
     * �R���X�g���N�^
     * @param prm_name  ���f�����́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model ���f����`���A������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g(GgafDx9MeshEffect.fx) �̃e�N�j�b�N�B
     * @param prm_pGeoMover ���W�𑀍삷��Mover�N���X�̃C���X�^���X��n��
     * @param prm_pGeoChecker   �l�X�Ȕ�����s�Ȃ��`�F�b�J�[�N���X�̃C���X�^���X��n��
     */
    GgafDx9MeshActor(const char* prm_name,
                         const char* prm_model,
                         const char* prm_technique,
                         GgafDx9GeometryMover* prm_pGeoMover,
                         GgafDx9GeometryChecker* prm_pGeoChecker);

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

    virtual ~GgafDx9MeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9MESHACTOR_H_*/
