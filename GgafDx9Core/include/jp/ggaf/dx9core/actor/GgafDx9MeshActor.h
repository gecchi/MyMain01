#ifndef GGAFDX9MESHACTORD_H_
#define GGAFDX9MESHACTORD_H_


class GgafDx9MeshActor : public GgafDx9UntransformedActor {
private:

public:
	/** ���f���I�u�W�F�N�g�ւ̃|�C���^ */
	GgafDx9MeshModel* _pMeshModel;
	/** �L�����S�̂̃� */
	float _fAlpha;


	GgafDx9MeshActor(string prm_name, string prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

	/**
	 * ��OverRide �ł���<BR>
	 */
	virtual void processDrawMain();

	void setAlpha(float prm_fAlpha) {
		_fAlpha = prm_fAlpha;
	}

	float getAlpha() {
		return _fAlpha;
	}

	virtual ~GgafDx9MeshActor();		//�f�X�g���N�^
};

#endif /*GGAFDX9MESHACTORD_H_*/
