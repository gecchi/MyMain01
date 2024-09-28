#ifndef GGAF_DX_AAPRISMACTOR_H_
#define GGAF_DX_AAPRISMACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MeshActor.h"

namespace GgafDx {

/**
 * AAプリズム.
 * プリズムを表示するためのアクターです。<BR>
 * Xファイルは、長さ１px相当の立方体(中心は(0,0,0))のプリズムを読み込ませてください。
 * @version 1.00
 * @since 2010/12/29
 * @author Masatoshi Tsuge
 */
class AAPrismActor : public MeshActor {
public:

    /**
     * 軸回転情報の構造体
     */
    class RotPosPrism : public GgafCore::Object {
    public:
        angle _rx;
        angle _rz;
        angle _ry;
    public:
        RotPosPrism() : _rx(0), _rz(0), _ry(0) {
        };
        RotPosPrism(angle rx, angle rz, angle ry) :
            GgafCore::Object(), _rx(rx), _rz(rz), _ry(ry) {
        }
    };

    /** プリズムの姿勢マップ（AABBのプリズム位置：対応する軸回転） */
    static std::map<int, AAPrismActor::RotPosPrism> pos2r;

public:
    AAPrismActor(const char* prm_name);

    /**
     * プリズムの姿勢マップを設定
     * @return
     */
    static bool initStatic();

    void drawPrism(coord prm_x1, coord prm_y1, coord prm_z1,
                   coord prm_x2, coord prm_y2, coord prm_z2, pos_t pos_info);

    virtual ~AAPrismActor();
};

}
#endif /*GGAF_DX_AAPRISMACTOR_H_*/
