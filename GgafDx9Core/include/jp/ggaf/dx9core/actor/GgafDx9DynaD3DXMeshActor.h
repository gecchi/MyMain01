#ifndef GGAFDX9DYNAD3DXMESHACTOR_H_
#define GGAFDX9DYNAD3DXMESHACTOR_H_
namespace GgafDx9Core {

/**
 * ���b�V���A�N�^�[.
 * GgafDx9UntransformedActor ���p�����AX�t�@�C����`�̃��b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł��B<BR>
 * GgafDx9D3DXMeshActor �Ƃ̈Ⴂ�́A���_�o�b�t�@�ɒ��ڃA�N�Z�X�����Ƃɍl�����āA<BR>
 * D3DXMESH_DYNAMIC �I�v�V�������g�p���Ă���Ƃ��낾���ł��B<BR>
 * ���_�����b�N����ꍇ��GgafDx9D3DXMeshActor�ł͂Ȃ��A��������p�����Ă��������B<BR>
 */
class GgafDx9DynaD3DXMeshActor : public GgafDx9UntransformedActor {
private:

public:

	char* _technique;
    static DWORD FVF;
    /** �}�e���A���z�� */
    D3DMATERIAL9* _paD3DMaterial9;
    /** ���f���I�u�W�F�N�g�ւ̃|�C���^ */
    GgafDx9ModelConnection* _pModelCon;
    GgafDx9D3DXMeshModel* _pD3DXMeshModel;
    /** �G�t�F�N�g�����ڑ� */
    GgafDx9EffectConnection* _pEffectCon;
    /** �G�t�F�N�g���� */
    GgafDx9MeshEffect* _pMeshEffect;

    GgafDx9DynaD3DXMeshActor(const char* prm_name,
                             const char* prm_model,
                             const char* prm_effect,
                             const char* prm_technique,
                             GgafDx9GeometryMover* prm_pGeoMover,
                             GgafDx9GeometryChecker* prm_pGeoChecker );

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

    virtual ~GgafDx9DynaD3DXMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9DYNAD3DXMESHACTOR_H_*/
