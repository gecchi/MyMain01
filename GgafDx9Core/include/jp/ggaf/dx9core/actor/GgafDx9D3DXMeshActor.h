#ifndef GGAFDX9D3DXMESHACTOR_H_
#define GGAFDX9D3DXMESHACTOR_H_
namespace GgafDx9Core {

/**
 * ���b�V���A�N�^�[.
 * GgafDx9UntransformedActor ���p�����AX�t�@�C����`�̃��b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł�<BR>
 */
class GgafDx9D3DXMeshActor : public GgafDx9UntransformedActor {
private:

public:
    /** ���f�� */
    GgafDx9ModelConnection* _pModelCon;
    GgafDx9D3DXMeshModel* _pD3DXMeshModel;

    GgafDx9D3DXMeshActor(const char* prm_name,
                     const char* prm_model,
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

    virtual ~GgafDx9D3DXMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9D3DXMESHACTOR_H_*/
