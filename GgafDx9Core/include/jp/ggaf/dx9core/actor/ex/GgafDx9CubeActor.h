#ifndef GGAFDX9CUBEACTORD_H_
#define GGAFDX9CUBEACTORD_H_
namespace GgafDx9Core {

/**
 * キューブアクター.
 * GgafDx9GeometricActor を継承し、キューブ（直方体）を表示するためのアクターです。<BR>
 * Xファイルは、長さ１px相当の立方体(中心は(0,0,0))のメッシュを読み込ませてください。
 * @version 1.00
 * @since 2008/10/10
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeActor : public GgafDx9MeshActor {

public:
    GgafDx9CubeActor(const char* prm_name,
                     GgafDx9Checker* prm_pChecker);

///**
//     * ＜OverRide です＞<BR>
//     */
//    virtual void processDraw();
//
    void drawBox(int prm_x1, int prm_y1, int prm_z1, int prm_x2, int prm_y2, int prm_z2);

    virtual ~GgafDx9CubeActor(); //デストラクタ
};

}
#endif /*GGAFDX9CUBEACTORD_H_*/
