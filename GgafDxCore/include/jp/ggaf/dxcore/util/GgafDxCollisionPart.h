#ifndef GGAFDXCOLLISIONPART_H_
#define GGAFDXCOLLISIONPART_H_
namespace GgafDxCore {

/**
 * 当たり判定要素クラス .
 * 当たり判定要素、当たり判定領域、という２つの言葉を次のように定義します。<BR>
 * 当たり判定要素 ・・・ １つの 球、或いはAAB、或いはプリズムの当たり判定。<BR>
 * 当たり判定領域 ・・・ 複数の当たり判定要素が集まって、グループ化した物<BR>
 * 本クラスは当たり判定「要素」を実装したクラスです。<BR>
 * 形状は AAB または プリズム または 球 をサポート。（今後増えるかもしれない）<BR>
 * 当たり判定のローカル軸回転平行移動をサポート .
 * @version 1.00
 * @since 2010/01/21
 * @author Masatoshi Tsuge
 */
class GgafDxCollisionPart : public GgafCore::GgafObject {

public:
    /** 当たり判定種別(COLLI_AAB:辺が各軸に並行な直方体 / COLLI_AAPRISM:辺が各軸に並行なプリズム/COLLI_SPHERE:球) */
    int _shape_kind;
    /** 有効フラグ */
    bool _is_valid_flg;
    /** 軸並行直方体 */
    coord _aab_x1, _aab_y1, _aab_z1, _aab_x2, _aab_y2, _aab_z2;

    /** 当たり判定要素のX軸方向幅 */
    coord _dx;
    /** 当たり判定要素のY軸方向幅 */
    coord _dy;
    /** 当たり判定要素のZ軸方向幅 */
    coord _dz;
    /** 当たり判定要素の中心のローカルX座標 */
    coord _cx;
    /** 当たり判定要素の中心のローカルY座標 */
    coord _cy;
    /** 当たり判定要素の中心のローカルZ座標 */
    coord _cz;
    /** 当たり判定要素の中心のローカルX座標（回転する前の初期値） */
    coord _base_cx;
    /** 当たり判定要素の中心のローカルY座標（回転する前の初期値） */
    coord _base_cy;
    /** 当たり判定要素の中心のローカルZ座標（回転する前の初期値） */
    coord _base_cz;

    /** 当たり判定要素のX軸方向幅の半分 */
    coord _hdx;
    /** 当たり判定要素のY軸方向幅の半分 */
    coord _hdy;
    /** 当たり判定要素のZ軸方向幅の半分 */
    coord _hdz;
    /** 本体のローカル座標(0,0,0)を中心にX軸回転の平行移動をさせるかどうか（※軸回転軌跡の平行移動であり、要素が軸回転するのではない） */
    bool _rotX;
    /** 本体のローカル座標(0,0,0)を中心にY軸回転の平行移動をさせるかどうか（※軸回転軌跡の平行移動であり、要素が軸回転するのではない） */
    bool _rotY;
    /** 本体のローカル座標(0,0,0)を中心にZ軸回転の平行移動をさせるかどうか（※軸回転軌跡の平行移動であり、要素が軸回転するのではない） */
    bool _rotZ;


    GgafDxCollisionPart();

    /**
     * 判定領域の軸回平行移動を行う。
     * @param rX ローカルX軸回転アングル値(0~360000)
     * @param rY ローカルY軸回転アングル値(0~360000)
     * @param rZ ローカルZ軸回転アングル値(0~360000)
     * @return
     */
    virtual void rotateRxRzRy(angle rX, angle rY, angle rZ) {
    }

    virtual ~GgafDxCollisionPart();
};

}
#endif /*GGAFDXCOLLISIONPART_H_*/
