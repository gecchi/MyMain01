#ifndef GGAFDX9CUBEACTORD_H_
#define GGAFDX9CUBEACTORD_H_
namespace GgafDx9Core {

/**
 * キューブアクター.
 * GgafDx9UntransformedActor を継承し、キューブ（直方体）を表示するためのアクターです。<BR>
 * Xファイルは、長さ１の立方体(中心は(0,0,0))のメッシュを読み込ませてください。
 */
class GgafDx9CubeActor : public GgafDx9MeshActor {
private:

public:
	GgafDx9CubeActor(char* prm_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

 	/**
	 * ＜OverRide です＞<BR>
	 */
	virtual void processDrawMain();

	void drawBox(int prm_x1, int prm_y1, int prm_z1, int prm_x2, int prm_y2, int prm_z2);

	virtual ~GgafDx9CubeActor();		//デストラクタ
};


}
#endif /*GGAFDX9CUBEACTORD_H_*/
