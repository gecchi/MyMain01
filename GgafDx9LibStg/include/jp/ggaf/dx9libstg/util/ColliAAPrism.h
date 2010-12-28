#ifndef COLLIAAPRISM_H_
#define COLLIAAPRISM_H_
namespace GgafDx9LibStg {

                               //   XYZnp
#define PRISM_XY_pn   (0xd)    //0b 01101
#define PRISM_XY_np   (0xe)    //0b 01110
#define PRISM_XY_pp   (0xd)    //0b 01101
#define PRISM_XY_nn   (0xf)    //0b 01111
#define PRISM_YZ_pn   (0x19)   //0b 11001
#define PRISM_YZ_np   (0x1a)   //0b 11010
#define PRISM_YZ_pp   (0x19)   //0b 11001
#define PRISM_YZ_nn   (0x1b)   //0b 11011
#define PRISM_ZX_pn   (0x15)   //0b 10101
#define PRISM_ZX_np   (0x16)   //0b 10110
#define PRISM_ZX_pp   (0x15)   //0b 10101
#define PRISM_ZX_nn   (0x17)   //0b 10111


#define PRISM_pn      (0x1)    //0b 00001
#define PRISM_np      (0x2)    //0b 00010
#define PRISM_pp      (0x1)    //0b 00001
#define PRISM_nn      (0x3)    //0b 00011
#define PRISM_XY      (0xc)    //0b 01100
#define PRISM_YZ      (0x18)   //0b 11000
#define PRISM_ZX      (0x14)   //0b 10100

/**
 * AAPrism(軸並行プリズム：Axis-Aligned Prism)当たり判定要素クラス
 * 軸並行プリズムとは、AABのある面の対角線でスライスを１回行った立体の事。
 * @version 1.00
 * @since 2010/12/28
 * @author Masatoshi Tsuge
 */
class ColliAAPrism : public GgafDx9Core::GgafDx9CollisionPart {
public:
    /** AABのx座標の小さい方 */
    int _x1;
    /** AABのy座標の小さい方 */
    int _y1;
    /** AABのz座標の小さい方 */
    int _z1;
    /** AABの対角の頂点となるx座標大きい方 */
    int _x2;
    /** AABの対角の頂点となるy座標大きい方 */
    int _y2;
    /** AABの対角の頂点となるz座標大きい方 */
    int _z2;

    int _pos_prism;
    int _slant_x1;
    int _slant_y1;
    int _slant_x2;
    int _slant_y2;
    int _slant_cal;

    ColliAAPrism();

    void set(int x1, int y1, int z1, int x2, int y2, int z2, int pos_prism, bool rotX, bool rotY, bool rotZ);

    bool rotateRxRzRy(angle rX, angle rY, angle rZ) override;

    virtual ~ColliAAPrism();
};

}
#endif /*COLIAAB_H_*/
