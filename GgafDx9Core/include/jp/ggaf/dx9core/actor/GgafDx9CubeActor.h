#ifndef GGAFDX9CUBEACTORD_H_
#define GGAFDX9CUBEACTORD_H_
namespace GgafDx9Core {


class GgafDx9CubeActor : public GgafDx9MeshActor {
private:

public:
	GgafDx9CubeActor(string prm_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

 	/**
	 * ��OverRide �ł���<BR>
	 */
	virtual void processDrawMain();

	virtual ~GgafDx9CubeActor();		//�f�X�g���N�^
};


}
#endif /*GGAFDX9CUBEACTORD_H_*/
