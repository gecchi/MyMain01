#ifndef GGAFDX9DYNAD3DXMESHACTOR_H_
#define GGAFDX9DYNAD3DXMESHACTOR_H_
namespace GgafDx9Core {

//���ӁF���̃N���X�͌��ݖ��g�p�ł��B�폜�\��B
//     �Œ�@�\�p�C�v���C�����Ɏg�p���Ă������A���͂����g��Ȃ��B
//     GgafDx9MeshActor���g���ĉ������B
/**
 * ���b�V���A�N�^�[.
 * GgafDx9DrawableActor ���p�����AX�t�@�C����`�̃��b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł��B<BR>
 * GgafDx9D3DXMeshActor �Ƃ̈Ⴂ�́A���_�o�b�t�@�ɒ��ڃA�N�Z�X�����Ƃɍl�����āA<BR>
 * D3DXMESH_DYNAMIC �I�v�V�������g�p���Ă���Ƃ��낾���ł��B<BR>
 * ���_�����b�N����ꍇ��GgafDx9D3DXMeshActor�ł͂Ȃ��A��������p�����Ă��������B<BR>
 * @version 1.00
 * @since 2008/11/17
 * @author Masatoshi Tsuge
 */
class GgafDx9DynaD3DXMeshActor : public GgafDx9DrawableActor {
private:

public:

    static DWORD FVF;
    GgafDx9D3DXMeshModel* _pD3DXMeshModel;
    /** �G�t�F�N�g���� */
    GgafDx9MeshEffect* _pMeshEffect;

    GgafDx9DynaD3DXMeshActor(const char* prm_name,
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

    virtual ~GgafDx9DynaD3DXMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9DYNAD3DXMESHACTOR_H_*/
