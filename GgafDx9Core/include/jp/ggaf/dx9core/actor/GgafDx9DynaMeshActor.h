#ifndef GGAFDX9DYNAMESHACTOR_H_
#define GGAFDX9DYNAMESHACTOR_H_
namespace GgafDx9Core {

/**
 * ���b�V���A�N�^�[.
 * GgafDx9UntransformedActor ���p�����AX�t�@�C����`�̃��b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł��B<BR>
 * GgafDx9MeshActor �Ƃ̈Ⴂ�́A���_�o�b�t�@�ɒ��ڃA�N�Z�X�����Ƃɍl�����āA<BR>
 * D3DXMESH_DYNAMIC �I�v�V�������g�p���Ă���Ƃ��낾���ł��B<BR>
 * ���_�����b�N����ꍇ��GgafDx9MeshActor�ł͂Ȃ��A��������p�����Ă��������B<BR>
 */
class GgafDx9DynaMeshActor : public GgafDx9UntransformedActor {
private:

public:
	/** ���f���I�u�W�F�N�g�ւ̃|�C���^ */
	GgafDx9ModelLead* _pModelLead;
	GgafDx9MeshModel* _pMeshModel;
	/** �L�����S�̂̃� */
	float _fAlpha;


	GgafDx9DynaMeshActor(char* prm_name, char* prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

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

	virtual ~GgafDx9DynaMeshActor();		//�f�X�g���N�^
};


}
#endif /*GGAFDX9DYNAMESHACTOR_H_*/
