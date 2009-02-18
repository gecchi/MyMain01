#ifndef GGAFDX9PRIMITIVEACTOR_H_
#define GGAFDX9PRIMITIVEACTOR_H_
namespace GgafDx9Core {

/**
 * ���b�V���A�N�^�[.
 * GgafDx9UntransformedActor ���p�����AX�t�@�C����`�̃��b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł�<BR>
 */
class GgafDx9PrimitiveActor : public GgafDx9UntransformedActor {
private:

public:
    /** ���f�� */
    GgafDx9ModelConnection* _pModelCon;
    GgafDx9PrimitiveModel* _pPrimitiveModel;

    GgafDx9PrimitiveActor(const char* prm_name,
                     const char* prm_meshmodel_name,
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

    virtual ~GgafDx9PrimitiveActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9PRIMITIVEACTOR_H_*/
