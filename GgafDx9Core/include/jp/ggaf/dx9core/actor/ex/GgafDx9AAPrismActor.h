#ifndef GGAFDX9AAPRISMACTOR_H_
#define GGAFDX9AAPRISMACTOR_H_

                                  //   XYZxx
#define POS_PRISM_XY_nn   (0x18)  //0b 11000
#define POS_PRISM_XY_np   (0x19)  //0b 11001
#define POS_PRISM_XY_pn   (0x1a)  //0b 11010
#define POS_PRISM_XY_pp   (0x1b)  //0b 11011
#define POS_PRISM_YZ_nn   (0xc)   //0b 01100
#define POS_PRISM_YZ_np   (0xd)   //0b 01101
#define POS_PRISM_YZ_pn   (0xe)   //0b 01110
#define POS_PRISM_YZ_pp   (0xf)   //0b 01111
#define POS_PRISM_ZX_nn   (0x14)  //0b 10100
#define POS_PRISM_ZX_np   (0x15)  //0b 10101
#define POS_PRISM_ZX_pn   (0x16)  //0b 10110
#define POS_PRISM_ZX_pp   (0x17)  //0b 10111

#define POS_PRISM_nn      (0x0)    //0b 00000
#define POS_PRISM_np      (0x1)    //0b 00001
#define POS_PRISM_pn      (0x2)    //0b 00010
#define POS_PRISM_pp      (0x3)    //0b 00011
#define POS_PRISM_XY      (0x18)   //0b 11000
#define POS_PRISM_YZ      (0xc)    //0b 01100
#define POS_PRISM_ZX      (0x14)   //0b 10100

//補足
//プリズム位置を表す定数は以下のようになっている
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

namespace GgafDx9Core {

/**
 * AAプリズム.
 * GgafDx9GeometricActor を継承し、プリズムを表示するためのアクターです。<BR>
 * Xファイルは、長さ１px相当の立方体(中心は(0,0,0))のメッシュを読み込ませてください。
 * @version 1.00
 * @since 2010/12/29
 * @author Masatoshi Tsuge
 */
class GgafDx9AAPrismActor : public GgafDx9MeshActor {
public:
    class RotPosPrism : public GgafCore::GgafObject {
    public:
        angle _rx;
        angle _rz;
        angle _ry;
        RotPosPrism() {}
        RotPosPrism(angle rx, angle rz, angle ry) : GgafCore::GgafObject(), _rx(rx), _rz(rz), _ry(ry) {
        }
    };


    static boolean init;
    static _MAP_<int, GgafDx9AAPrismActor::RotPosPrism> pos2r;

    GgafDx9AAPrismActor(const char* prm_name,
                        GgafDx9Checker* prm_pChecker);

///**
//     * ＜OverRide です＞<BR>
//     */
//    virtual void processDraw();
//
    void drawPrism(int prm_x1, int prm_y1, int prm_z1, int prm_x2, int prm_y2, int prm_z2, int pos_prism);

    virtual ~GgafDx9AAPrismActor(); //デストラクタ
};

}
#endif /*GGAFDX9BOXACTOR_H_*/
