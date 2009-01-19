#ifndef GGAFDX9CUBEACTORD_H_
#define GGAFDX9CUBEACTORD_H_
namespace GgafDx9Core {


class GgafDx9CubeActor : public GgafDx9MeshActor {
private:

public:
	GgafDx9CubeActor(string prm_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

 	/**
	 * ＜OverRide です＞<BR>
	 */
	virtual void processDrawMain();

	virtual ~GgafDx9CubeActor();		//デストラクタ
};


}
#endif /*GGAFDX9CUBEACTORD_H_*/
