#ifndef GGAFDXBOXACTOR_H_
#define GGAFDXBOXACTOR_H_
namespace GgafDxCore {

/**
 * キューブアクター.
 * GgafDxGeometricActor を継承し、キューブ（直方体）を表示するためのアクターです。<BR>
 * Xファイルは、長さ１px相当の立方体(中心は(0,0,0))のメッシュを読み込ませてください。
 * @version 1.00
 * @since 2008/10/10
 * @author Masatoshi Tsuge
 */
class GgafDxAABActor : public GgafDxMeshActor {

public:
    GgafDxAABActor(const char* prm_name,
                    GgafCore::GgafStatus* prm_pStat,
                    GgafDxChecker* prm_pChecker);

///**
//     * ＜OverRide です＞<BR>
//     */
//    virtual void processDraw();
//
    void drawBox(coord prm_x1, coord prm_y1, coord prm_z1, coord prm_x2, coord prm_y2, coord prm_z2);

    virtual ~GgafDxAABActor(); //デストラクタ
};

}
#endif /*GGAFDXBOXACTOR_H_*/
