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
	/** ���f�� */
	GgafDx9MeshModel* _pMeshModel;
	/** �}�e���A�� */
	D3DMATERIAL9* 	_paD3DMaterial9;
	/** �L�����S�̂̃� */
	float _fAlpha;


	GgafDx9MeshActor(std::string prm_name, std::string prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

	/**
	 * ��OverRide �ł���<BR>
	 */
	virtual void processDrawMain();

	void setAlpha(float prm_fAlpha);

	float getAlpha() {
		return _fAlpha;
	}

	virtual ~GgafDx9MeshActor();		//�f�X�g���N�^
};


}
#endif /*GGAFDX9MESHACTOR_H_*/
