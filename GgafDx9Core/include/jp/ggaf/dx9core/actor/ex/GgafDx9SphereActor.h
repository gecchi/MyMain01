#ifndef GGAFDX9SPHEREACTOR_H_
#define GGAFDX9SPHEREACTOR_H_
namespace GgafDx9Core {

/**
 * 球アクター.
 * GgafDx9GeometricActor を継承し、球を表示するためのアクターです。<BR>
 * Xファイルは、直径１px相当の球(中心は(0,0,0))のメッシュを読み込ませてください。
 * @version 1.00
 * @since 2010/10/21
 * @author Masatoshi Tsuge
 */
class GgafDx9SphereActor : public GgafDx9MeshActor {

public:
    GgafDx9SphereActor(const char* prm_name,
                     GgafDx9Checker* prm_pChecker);

///**
//     * ＜OverRide です＞<BR>
//     */
//    virtual void processDraw();
//
    void drawSphere(int prm_x, int prm_y, int prm_z, int prm_r);

    virtual ~GgafDx9SphereActor(); //デストラクタ
};

}
#endif /*GGAFDX9SPHEREACTOR_H_*/
