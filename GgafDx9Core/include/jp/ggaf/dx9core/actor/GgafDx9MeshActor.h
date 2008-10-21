#ifndef GGAFDX9MESHACTORD_H_
#define GGAFDX9MESHACTORD_H_


class GgafDx9MeshActor : public GgafDx9UntransformedActor {
private:
	GgafDx9MeshModel* _pMeshModel;

public:
	GgafDx9MeshActor(string prm_name, string prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

	/**
	 * _Z�̒l�ɂ��A��܂��Ƀ����_�����O������ݒ肷��B
	 * �C�ӂ̗D�揇�ʂŃ����_�����O�������ꍇ�́A���̃��\�b�h���I�[�o�[���C�h��
	 * GgafWorld::_apActorDrawOrder[n] �̍D���� n �� addSubLast(this) ���s���ĉ������B
	 * �A�� 0 �� n �� MAX_DEPTH_LEVEL
	 */
	virtual void processDrawPrior();

	/**
	 * ��OverRide �ł���<BR>
	 */
	virtual void processDrawMain();

	virtual ~GgafDx9MeshActor();		//�f�X�g���N�^
};

#endif /*GGAFDX9MESHACTORD_H_*/
