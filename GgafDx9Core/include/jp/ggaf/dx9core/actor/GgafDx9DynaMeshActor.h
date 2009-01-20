#ifndef GGAFDX9DYNAMESHACTOR_H_
#define GGAFDX9DYNAMESHACTOR_H_
namespace GgafDx9Core {


class GgafDx9DynaMeshActor : public GgafDx9UntransformedActor {
private:

public:
	/** ���f���I�u�W�F�N�g�ւ̃|�C���^ */
	GgafDx9MeshModel* _pMeshModel;
	/** �L�����S�̂̃� */
	float _fAlpha;


	GgafDx9DynaMeshActor(std::string prm_name, std::string prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

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

	virtual ~GgafDx9DynaMeshActor();		//�f�X�g���N�^
};


}
#endif /*GGAFDX9DYNAMESHACTOR_H_*/
