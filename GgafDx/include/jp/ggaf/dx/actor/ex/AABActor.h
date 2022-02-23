#ifndef GGAF_DX_AABACTOR_H_
#define GGAF_DX_AABACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MeshActor.h"

namespace GgafDx {

/**
 * キューブアクター.
 * キューブ（直方体）を表示するためのアクターです。<BR>
 * Xファイルは、長さ１px相当の立方体(中心は(0,0,0))のメッシュを読み込ませてください。
 * @version 1.00
 * @since 2008/10/10
 * @author Masatoshi Tsuge
 */
class AABActor : public MeshActor {

public:
    AABActor(const char* prm_name, Checker* prm_pChecker);

    void drawBox(coord prm_x1, coord prm_y1, coord prm_z1, coord prm_x2, coord prm_y2, coord prm_z2);

    virtual ~AABActor(); //デストラクタ
};

}
#endif /*GGAF_DX_BOXACTOR_H_*/
