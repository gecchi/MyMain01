#ifndef GGAFDXCORE_GGAFDXAAPYRAMIDACTOR_H_
#define GGAFDXCORE_GGAFDXAAPYRAMIDACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMeshActor.h"

namespace GgafDxCore {

/**
 * AAピラミッド.
 * GgafDxGeometricActor を継承し、ピラミッドを表示するためのアクターです。<BR>
 * Xファイルは、長さ１px相当の立方体(中心は(0,0,0))で、
 * (-0.5, -0.5, -0.5) が３直角の頂点となる直角三角錐を読み込ませてください。
 * @version 1.00
 * @since 2016/01/15
 * @author Masatoshi Tsuge
 */
class GgafDxAAPyramidActor : public GgafDxMeshActor {
public:
    class RotPosPyramid : public GgafCore::GgafObject {
    public:
        angle _rx;
        angle _rz;
        angle _ry;
    public:
        RotPosPyramid() : _rx(0), _rz(0), _ry(0) {
        };
        RotPosPyramid(angle rx, angle rz, angle ry) :
            GgafCore::GgafObject(), _rx(rx), _rz(rz), _ry(ry) {
        }
    };

    static std::map<int, GgafDxAAPyramidActor::RotPosPyramid> pos2r;

public:
    GgafDxAAPyramidActor(const char* prm_name,
                        GgafCore::GgafStatus* prm_pStat,
                        GgafDxChecker* prm_pChecker);

    static bool initStatic();

    void drawPyramid(coord prm_x1, coord prm_y1, coord prm_z1,
                     coord prm_x2, coord prm_y2, coord prm_z2, pos_t pos_info);

    virtual ~GgafDxAAPyramidActor(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXAAPYRAMIDACTOR_H_*/

//補足
//ピラミッド位置(pos_info)を、表す定数(GgafDxCommonHeader.hで定義)は以下のような命名がなされている。
//＜例＞
//POS_PYRAMID_npn
//
//＜意味＞
//"POS_PYRAMID_" + どの頂点が３直角の頂点か
//スライスされる前の立方体が原点にあったとして、
//スライスされて出来上がった直角三角柱の３直角の頂点の位置を表している。
//n(negative)は負方向、p(positive)は正方向、という意味を持たしている
//POS_PYRAMID_npn の "npn" の３文字の部分は、
//１文字目はX軸の正負,２文字目はY軸の正負、３文字目はZ軸の正負
//を表し、例の "npn" は (x, y, z) = (-, +, -) の象限に３直角の頂点があるよ
//という意味
