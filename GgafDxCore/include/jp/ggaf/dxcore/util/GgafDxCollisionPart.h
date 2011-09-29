#ifndef GGAFDXCOLLISIONPART_H_
#define GGAFDXCOLLISIONPART_H_
namespace GgafDxCore {

/**
 * 当たり判定領域要素 .
 * 当たり判定要素、当たり判定領域、という２つの言葉を次のように定義します。<BR>
 * 当たり判定要素 ・・・ １つの 球、或いはAAB の当たり判定。<BR>
 * 当たり判定領域 ・・・ 複数の当たり判定要素が集まって、グループ化した物<BR>
 * 本クラスは当たり判定「要素」を実装したクラスです。<BR>
 * 形状は AAB または 球 をサポート。（今後増えるかもしれない）<BR>
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

    /** 軸並行直方体のx幅 */
    coord _dx;
    /** 軸並行直方体のy幅 */
    coord _dy;
    /** 軸並行直方体のz幅 */
    coord _dz;
    /** 初期軸並行直方体中心のX座標 */
    coord _base_cx;
    /** 初期軸並行直方体中心のY座標 */
    coord _base_cy;
    /** 初期軸並行直方体中心のZ座標 */
    coord _base_cz;
    /** 軸並行直方体中心のX座標 */
    coord _cx;
    /** 軸並行直方体中心のY座標  */
    coord _cy;
    /** 軸並行直方体中心のZ座標  */
    coord _cz;

    /** x幅の半分 */
    coord _hdx;
    /** y幅の半分 */
    coord _hdy;
    /** z幅の半分 */
    coord _hdz;
    /** 中心点を、オブジェクトの(0,0)を中心にX軸回転の移動をさせるかどうか（直方体が軸回転するのではない） */
    bool _rotX;
    /** 中心点を、オブジェクトの(0,0)を中心にY軸回転の移動をさせるかどうか（直方体が軸回転するのではない） */
    bool _rotY;
    /** 中心点を、オブジェクトの(0,0)を中心にZ軸回転の移動をさせるかどうか（直方体が軸回転するのではない） */
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
