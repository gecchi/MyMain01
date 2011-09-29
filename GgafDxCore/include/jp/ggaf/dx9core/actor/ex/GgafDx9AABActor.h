#ifndef GGAFDX9BOXACTOR_H_
#define GGAFDX9BOXACTOR_H_
namespace GgafDx9Core {

/**
 * キューブアクター.
 * GgafDx9GeometricActor を継承し、キューブ（直方体）を表示するためのアクターです。<BR>
 * Xファイルは、長さ１px相当の立方体(中心は(0,0,0))のメッシュを読み込ませてください。
 * @version 1.00
 * @since 2008/10/10
 * @author Masatoshi Tsuge
 */
class GgafDx9AABActor : public GgafDx9MeshActor {

public:
    GgafDx9AABActor(const char* prm_name,
                    GgafCore::GgafStatus* prm_pStat,
                    GgafDx9Checker* prm_pChecker);

///**
//     * ＜OverRide です＞<BR>
//     */
//    virtual void processDraw();
//
    void drawBox(coord prm_x1, coord prm_y1, coord prm_z1, coord prm_x2, coord prm_y2, coord prm_z2);

    virtual ~GgafDx9AABActor(); //デストラクタ
};

}
#endif /*GGAFDX9BOXACTOR_H_*/
