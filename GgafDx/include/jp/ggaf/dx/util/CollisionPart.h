#ifndef GGAF_DX_COLLISIONPART_H_
#define GGAF_DX_COLLISIONPART_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

namespace GgafDx {

/**
 * 当たり判定要素クラス .
 * 当たり判定要素、当たり判定領域、という２つの言葉を次のように定義します。<BR>
 * a)当たり判定要素 ・・・ １つの 球 or AAB or プリズム の当たり判定の立体図形。<BR>
 * b)当たり判定領域 ・・・ 上記の複数の当たり判定要素が集まって、グループ化した物。<BR>
 * 本クラスは a) 当たり判定「要素」を実装したクラスです。<BR>
 * 形状は AAB または プリズム または 球 をサポート。（今後増えるかもしれない）<BR>
 * 当たり判定のローカル軸回転平行移動をサポート .
 * @version 1.00
 * @since 2010/01/21
 * @author Masatoshi Tsuge
 */
class CollisionPart : public GgafCore::Object {

public:
    /** 当たり判定種別(COLLI_AABOX / COLLI_AAPRISM / COLLI_AAPYRAMID / COLLI_SPHERE) */
    int _shape_kind;
//    /** 有効フラグ */
//    bool _is_valid_flg;
    /** 当たり判定境界直方体のローカル座標 */
    coord _x1, _y1, _z1, _x2, _y2, _z2;
    /** 当たり判定境界直方体のX軸方向幅 */
    coord _dx;
    /** 当たり判定境界直方体のY軸方向幅 */
    coord _dy;
    /** 当たり判定境界直方体のZ軸方向幅 */
    coord _dz;
    /** 当たり判定境界直方体の中心のローカルX座標 */
    coord _cx;
    /** 当たり判定境界直方体の中心のローカルY座標 */
    coord _cy;
    /** 当たり判定境界直方体の中心のローカルZ座標 */
    coord _cz;
    /** 当たり判定境界直方体の中心のローカルX座標（回転する前の初期値） */
    coord _base_cx;
    /** 当たり判定境界直方体の中心のローカルY座標（回転する前の初期値） */
    coord _base_cy;
    /** 当たり判定境界直方体の中心のローカルZ座標（回転する前の初期値） */
    coord _base_cz;

    /** _dx の半分（計算用）*/
    coord _hdx;
    /** _dy の半分（計算用）*/
    coord _hdy;
    /** _dz の半分（計算用）*/
    coord _hdz;
    /** 本体のローカル座標(0,0,0)を中心にX軸回転の軌跡に平行移動をさせるかどうか（※軸回転軌跡の平行移動であり、要素が軸回転するのではない） */
    bool _rot_x;
    /** 本体のローカル座標(0,0,0)を中心にY軸回転の軌跡に平行移動をさせるかどうか（※軸回転軌跡の平行移動であり、要素が軸回転するのではない） */
    bool _rot_y;
    /** 本体のローカル座標(0,0,0)を中心にZ軸回転の軌跡に平行移動をさせるかどうか（※軸回転軌跡の平行移動であり、要素が軸回転するのではない） */
    bool _rot_z;
    /** 軸回転の軌跡に平行移動するのかどうか */
    bool _rot;

public:
    CollisionPart();

    /**
     * 判定領域の軸回平行移動を行う。
     * @param rx ローカルX軸回転アングル値(0~360000)
     * @param ry ローカルY軸回転アングル値(0~360000)
     * @param rz ローカルZ軸回転アングル値(0~360000)
     * @return
     */
    virtual void rotateRxRzRy(angle rx, angle ry, angle rz) = 0;

    virtual ~CollisionPart();
};

}
#endif /*GGAF_DX_COLLISIONPART_H_*/
