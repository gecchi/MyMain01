#ifndef GGAFDX9COLLISIONPART_H_
#define GGAFDX9COLLISIONPART_H_
namespace GgafDx9Core {

/**
 * 当たり判定部品 .
 * AABB または 球 をサポート .
 * 当たり判定のローカル軸回転平行移動をサポート .
 * @version 1.00
 * @since 2010/01/21
 * @author Masatoshi Tsuge
 */
class GgafDx9CollisionPart : public GgafCore::GgafObject {

public:
    /** 種別 */
    int _shape_kind;
    /** 有効フラグ */
    bool _is_valid_flg;


    /** 境界BOX(8分木登録のため) */
    int _aabb_x1, _aabb_y1, _aabb_z1, _aabb_x2, _aabb_y2, _aabb_z2;

    /** 境界BOXのx幅 */
    int _dx;
    /** 境界BOXのy幅 */
    int _dy;
    /** 境界BOXのz幅 */
    int _dz;
    /** 初期境界BOX中心のX座標 */
    int _base_cx;
    /** 初期境界BOX中心のY座標 */
    int _base_cy;
    /** 初期境界BOX中心のZ座標 */
    int _base_cz;
    /** 境界BOX中心のX座標 */
    int _cx;
    /** 境界BOX中心のY座標  */
    int _cy;
    /** 境界BOX中心のZ座標  */
    int _cz;

    /** x幅の半分 */
    int _hdx;
    /** y幅の半分 */
    int _hdy;
    /** z幅の半分 */
    int _hdz;
    /** 中心点を、オブジェクトの(0,0)を中心にX軸回転の移動をさせるかどうか（箱が軸回転するのではない） */
    bool _rotX;
    /** 中心点を、オブジェクトの(0,0)を中心にY軸回転の移動をさせるかどうか（箱が軸回転するのではない） */
    bool _rotY;
    /** 中心点を、オブジェクトの(0,0)を中心にZ軸回転の移動をさせるかどうか（箱が軸回転するのではない） */
    bool _rotZ;


    GgafDx9CollisionPart();

    /**
     * 判定領域の軸回平行移動を行う。
     * @param rX ローカルX軸回転アングル値(0~360000)
     * @param rY ローカルY軸回転アングル値(0~360000)
     * @param rZ ローカルZ軸回転アングル値(0~360000)
     * @return
     */
    virtual bool rotate(angle rX, angle rY, angle rZ) {
        return false;
    }

    virtual ~GgafDx9CollisionPart();
};

}
#endif /*GGAFDX9COLLISIONPART_H_*/
