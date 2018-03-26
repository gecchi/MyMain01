#ifndef GGAFDXCORE_GGAFDXAAPRISMACTOR_H_
#define GGAFDXCORE_GGAFDXAAPRISMACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMeshActor.h"

namespace GgafDxCore {

/**
 * AAプリズム.
 * GgafDxGeometricActor を継承し、プリズムを表示するためのアクターです。<BR>
 * Xファイルは、長さ１px相当の立方体(中心は(0,0,0))のプリズムを読み込ませてください。
 * @version 1.00
 * @since 2010/12/29
 * @author Masatoshi Tsuge
 */
class GgafDxAAPrismActor : public GgafDxMeshActor {
public:
    class RotPosPrism : public GgafCore::GgafObject {
    public:
        angle _rx;
        angle _rz;
        angle _ry;
    public:
        RotPosPrism() : _rx(0), _rz(0), _ry(0) {
        };
        RotPosPrism(angle rx, angle rz, angle ry) :
            GgafCore::GgafObject(), _rx(rx), _rz(rz), _ry(ry) {
        }
    };

    static std::map<int, GgafDxAAPrismActor::RotPosPrism> pos2r;

public:
    GgafDxAAPrismActor(const char* prm_name,
                        GgafCore::GgafStatus* prm_pStat,
                        GgafDxChecker* prm_pChecker);

    static bool initStatic();

    void drawPrism(coord prm_x1, coord prm_y1, coord prm_z1,
                   coord prm_x2, coord prm_y2, coord prm_z2, pos_t pos_info);

    virtual ~GgafDxAAPrismActor(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXBOXACTOR_H_*/

//補足
//プリズム位置(pos_info)を、表す定数(GgafDxCommonHeader.hで定義)は以下のような命名がなされている。
//＜例＞
//POS_PRISM_YZ_NN
//＜意味＞
//"POS_PRISM_" + どの平面にスライスを入れるか + "_" + スライスの仕方
//[どの平面にスライスを入れるか]
//XY ・・・ AABのXY平面に垂直にスライス
//YZ ・・・ AABのYZ平面に垂直にスライス
//ZX ・・・ AABのZX平面に垂直にスライス
//[スライスの仕方]
// n(negative)は負方向、p(positive)は正方向、という意味を持たしている
//nn ・・・ 直角三角形の直角の部分が先の平面座標系の (負方向, 負方向) と言う意味
//np ・・・ 直角三角形の直角の部分が先の平面座標系の (負方向, 正方向) と言う意味
//pn ・・・ 直角三角形の直角の部分が先の平面座標系の (正方向, 負方向) と言う意味
//pp ・・・ 直角三角形の直角の部分が先の平面座標系の (正方向, 正方向) と言う意味
