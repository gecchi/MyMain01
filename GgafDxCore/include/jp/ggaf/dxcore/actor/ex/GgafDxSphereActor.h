#ifndef GGAFDXCORE_GGAFDXSPHEREACTOR_H_
#define GGAFDXCORE_GGAFDXSPHEREACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMeshActor.h"

namespace GgafDxCore {

/**
 * 球アクター.
 * GgafDxGeometricActor を継承し、球を表示するためのアクターです。<BR>
 * Xファイルは、直径１px相当の球(中心は(0,0,0))のメッシュを読み込ませてください。
 * @version 1.00
 * @since 2010/10/21
 * @author Masatoshi Tsuge
 */
class GgafDxSphereActor : public GgafDxMeshActor {

public:
    GgafDxSphereActor(const char* prm_name,
                       GgafCore::GgafStatus* prm_pStat,
                       GgafDxChecker* prm_pChecker);

    void drawSphere(coord prm_x, coord prm_y, coord prm_z, coord prm_r);

    virtual ~GgafDxSphereActor(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXSPHEREACTOR_H_*/
