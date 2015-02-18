#ifndef GGAFLIB_COLLISIONCHECKER_H_
#define GGAFLIB_COLLISIONCHECKER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxChecker.h"

namespace GgafLib {

/**
 * 3D用衝突チェッカークラス.
 * アクターに当たり判定チェック等機能を追加するクラス。
 * １つの「当たり判定領域」は、複数の「当たり判定領域要素」から形成されています。<BR>
 * 各「当たり判定領域要素」は、BOX型と球型の２種類の内から選べます。<BR>
 * 「当たり判定領域」「当たり判定領域要素」と言葉の意味を区別し、次のようにな意味と定義する。<BR>
 * 「当たり判定領域の要素」・・・１キャラクタの当たり判定の一つ。球状か、あるいはBOX状の閉じた立体領域１つを指す。<BR>
 * 「当たり判定領域」      ・・・１つ以上の判定領域の要素が合わさった、１キャラクタの当たり判定全体を表す。<BR>
 *
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class CollisionChecker3D : public GgafDxCore::GgafDxChecker {

    LinearOctreeForActor* _pLinearOctree; //TODO:どこに持たせようか悩むがとりあえずココに

public:

    /** １フレームの当たり判定要素同士の判定回数 */
    static int _num_check;
    /** 当たり判定領域の境界領域(AABB)を再計算するかどうかのフラグ */
    bool _need_update_aabb;
    /** 線形八分木登録用要素 */
    LinearOctreeActorElem* _pElem;

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  当たり判定機能を追加するActor
     */
    explicit CollisionChecker3D(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * 当たり判定領域BOXの回転平行移動と、八分木登録を行います .
     * 当たり判定機能を使用するには、このメソッドを毎フレーム実行する必要があります。<br>
     * しかし、フレームワークに組み込まれているため、実装者は特に気にする必要がない。<br>
     * 現在は GgafDxGeometricActor::processSettlementBehavior から毎フレームコールされている。<br>
     * もし processSettlementBehavior() を下位でオーバーライドする場合は気を付けるべし！<br>
     */
    virtual void updateHitArea() override;


    /**
     * 当たり判定領域要素を球として定義 .
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定の球の中心ローカルX座標
     * @param y 当たり判定の球の中心ローカルY座標
     * @param z 当たり判定の球の中心ローカルZ座標
     * @param r 当たり判定の球の半径
     * @param rot_x 当たり判定の球を、向きに伴ってローカルX軸での回転平行移動を行う場合 true
     * @param rot_y 当たり判定の球を、向きに伴ってローカルY軸での回転平行移動を行う場合 true
     * @param rot_z 当たり判定の球を、向きに伴ってローカルZ軸での回転平行移動を行う場合 true
     */
    void setColliSphere(int prm_index, coord x, coord y, coord z, coord r, bool rot_x, bool rot_y, bool rot_z);

    /**
     * 当たり判定領域要素を球として定義 .
     * 向きに伴っての当たり判定の球の回転平行移動機能は無し
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定の球の中心ローカルX座標
     * @param y 当たり判定の球の中心ローカルY座標
     * @param z 当たり判定の球の中心ローカルZ座標
     * @param r 当たり判定の球の半径
     */
    void setColliSphere(int prm_index, coord x, coord y, coord z, coord r) {
        setColliSphere(prm_index, x, y, z, r, false, false, false);
    }

    /**
     * 当たり判定領域要素を球として定義 .
     * オブジェクトの基点を球の中心とする。<br>
     * 向きに伴っての当たり判定の球の回転平行移動機能は無し。<br>
     * @param prm_index 当たり判定領域の要素番号
     * @param r 当たり判定の球の半径
     */
    void setColliSphere(int prm_index, coord r) {
        setColliSphere(prm_index, 0, 0, 0, r, false, false, false);
    }

    /**
     * 当たり判定領域要素を軸平行直方体として定義 .
     * @param prm_index 当たり判定領域の要素番号
     * @param x1 左上手前X座標
     * @param y1 左上手前Y座標
     * @param z1 左上手前Z座標
     * @param x2 右下奥X座標
     * @param y2 右下奥Y座標
     * @param z2 右下奥Z座標
     * @param rot_x 当たり判定の直方体を、向きに伴ってローカルX軸での回転平行移動を行う場合 true
     * @param rot_y 当たり判定の直方体を、向きに伴ってローカルY軸での回転平行移動を行う場合 true
     * @param rot_z 当たり判定の直方体を、向きに伴ってローカルZ軸での回転平行移動を行う場合 true
     */
    void setColliAAB(int prm_index,
                     coord x1, coord y1, coord z1,
                     coord x2, coord y2, coord z2,
                     bool rot_x, bool rot_y, bool rot_z);

    /**
     * 当たり判定領域要素を軸平行直方体として定義 .
     * 向きに伴っての当たり判定の球の回転平行移動機能は無し
     * @param prm_index 当たり判定領域の要素番号
     * @param x1 左上手前X座標
     * @param y1 左上手前Y座標
     * @param z1 左上手前Z座標
     * @param x2 右下奥X座標
     * @param y2 右下奥Y座標
     * @param z2 右下奥Z座標
     */
    void setColliAAB(int prm_index,
                     coord x1, coord y1, coord z1,
                     coord x2, coord y2, coord z2) {
        setColliAAB(prm_index, x1, y1, z1, x2, y2, z2, false, false, false);
    }

    /**
     * 当たり判定領域要素を軸平行直方体として定義 .
     * Zの厚みは、1px相当
     * @param prm_index 当たり判定領域の要素番号
     * @param x1 左上手前X座標
     * @param y1 左上手前Y座標
     * @param x2 右下奥X座標
     * @param y2 右下奥Y座標
     */
    void setColliAAB(int prm_index, coord x1, coord y1, coord x2, coord y2) {
        setColliAAB(prm_index, x1, y1, -1 * PX_C(1) / 2, x2, y2, PX_C(1) / 2, false, false, false);
    }

    /**
     * 当たり判定領域要素を軸平行直方体として定義 .
     * BOX中心座標と、幅、高さ、奥行で指定
     * @param prm_index
     * @param x 中心X座標
     * @param y 中心Y座標
     * @param z 中心Z座標
     * @param prm_width 幅(X軸方向)
     * @param prm_height 高さ(Y軸方向)
     * @param prm_depth 深さ（奥行・Y軸方向）
     */
    void setColliAAB_WHD(int prm_index, coord x, coord y, coord z, coord prm_width, coord prm_height, coord prm_depth) {
        int hw = prm_width  / 2;
        int hh = prm_height / 2;
        int hd = prm_depth  / 2;

        setColliAAB(prm_index, x-hw, y-hh, z-hd, x+hw, y+hh, z+hd);
    }

    /**
     * 当たり判定領域要素を軸平行直方体として定義 .
     * オブジェクトの基点を中心として、幅、高さ、奥行で指定
     * @param prm_index 当たり判定領域の要素番号
     * @param prm_width 幅(X軸方向)
     * @param prm_height 高さ(Y軸方向)
     * @param prm_depth 深さ（奥行・Y軸方向）
     */
    void setColliAAB_WHD(int prm_index, coord prm_width, coord prm_height, coord prm_depth) {
        setColliAAB_WHD(prm_index, 0, 0, 0, prm_width, prm_height, prm_depth);
    }


    /**
     * 当たり判定領域要素を軸平行立方体として定義 .
     * 引数座標を中心として、１辺の長さで指定
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定の立方体の中心ローカルX座標
     * @param y 当たり判定の立方体の中心ローカルY座標
     * @param z 当たり判定の立方体の中心ローカルZ座標
     * @param prm_edge １辺の長さ
     */
    void setColliAAB_Cube(int prm_index, coord x, coord y, coord z, coord prm_edge) {
        coord h = prm_edge / 2;
        setColliAAB(prm_index, x-h, y-h, z-h, x+h, y+h, z+h);
    }


    /**
     * 当たり判定領域要素を軸平行立方体として定義 .
     * オブジェクトの基点を中心として、１辺の長さで指定
     * @param prm_index 当たり判定領域の要素番号
     * @param prm_edge １辺の長さ
     */
    void setColliAAB_Cube(int prm_index, coord prm_edge) {
        setColliAAB_Cube(prm_index, 0, 0, 0, prm_edge);
    }

    /**
     * 当たり判定領域要素を軸平行立方体として定義 .
     * 引数座標を中心として、１辺の長さで指定
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定の立方体の中心ローカルX座標
     * @param y 当たり判定の立方体の中心ローカルY座標
     * @param z 当たり判定の立方体の中心ローカルZ座標
     * @param prm_edge １辺の長さ
     * @param rot_x 当たり判定の立方体を、向きに伴ってローカルX軸での回転平行移動を行う場合 true
     * @param rot_y 当たり判定の立方体を、向きに伴ってローカルY軸での回転平行移動を行う場合 true
     * @param rot_z 当たり判定の立方体を、向きに伴ってローカルZ軸での回転平行移動を行う場合 true
     */
    void setColliAAB_Cube(int prm_index, coord x, coord y, coord z, coord prm_edge, bool rot_x, bool rot_y, bool rot_z) {
        int h = prm_edge / 2;
        setColliAAB(prm_index, x-h, y-h, z-h, x+h, y+h, z+h, rot_x, rot_y, rot_z);
    }



    /**
     * 当たり判定領域要素を軸平行プリズム型として定義 .
     * @param prm_index 当たり判定領域の要素番号
     * @param x1 左上手前X座標
     * @param y1 左上手前Y座標
     * @param z1 左上手前Z座標
     * @param x2 右下奥X座標
     * @param y2 右下奥Y座標
     * @param z2 右下奥Z座標
     * @param pos_prism プリズム位置（POS_PRISM_**_**)
     * @param rot_x 当たり判定の直方体を、向きに伴ってローカルX軸での回転平行移動を行う場合 true
     * @param rot_y 当たり判定の直方体を、向きに伴ってローカルY軸での回転平行移動を行う場合 true
     * @param rot_z 当たり判定の直方体を、向きに伴ってローカルZ軸での回転平行移動を行う場合 true
     */
    void setColliAAPrism(int prm_index, coord x1, coord y1, coord z1, coord x2, coord y2, coord z2, int pos_prism, bool rot_x, bool rot_y, bool rot_z);

    /**
     * 当たり判定領域要素を軸平行直方体として定義 .
     * 向きに伴っての当たり判定の球の回転平行移動機能は無し
     * @param prm_index 当たり判定領域の要素番号
     * @param x1 左上手前X座標
     * @param y1 左上手前Y座標
     * @param z1 左上手前Z座標
     * @param x2 右下奥X座標
     * @param y2 右下奥Y座標
     * @param z2 右下奥Z座標
     * @param pos_prism プリズム位置（GgafDxAAPrismActor の #define 定義参照)
     */
    void setColliAAPrism(int prm_index, coord x1, coord y1, coord z1, coord x2, coord y2, coord z2, int pos_prism) {
        setColliAAPrism(prm_index, x1, y1, z1, x2, y2, z2, pos_prism, false, false, false);
    }



    void setColliAAPrism_WHD(int prm_index, coord x, coord y, coord z, coord prm_width, coord prm_height, coord prm_depth, int pos_prism) {
        int hw = prm_width  / 2;
        int hh = prm_height / 2;
        int hd = prm_depth  / 2;
        setColliAAPrism(prm_index, x-hw, y-hh, z-hd, x+hw, y+hh, z+hd, pos_prism);
    }

    /**
     * 当たり判定領域要素を軸平行直方体として定義 .
     * オブジェクトの基点を中心として、幅、高さ、奥行で指定
     * @param prm_index 当たり判定領域の要素番号
     * @param prm_width 幅(X軸方向幅)
     * @param prm_height 高さ(Y軸方向幅)
     * @param prm_depth 深さ(Z軸方向幅)
     * @param pos_prism プリズム位置（GgafDxAAPrismActor の #define 定義参照)
     */
    void setColliAAPrism_WHD(int prm_index, coord prm_width, coord prm_height, coord prm_depth, int pos_prism) {
        setColliAAPrism_WHD(prm_index, 0, 0, 0, prm_width, prm_height, prm_depth, pos_prism);
    }

    /**
     * 当たり判定領域要素を軸平行立方体として定義 .
     * 引数座標を中心として、１辺の長さで指定
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定の立方体の中心ローカルX座標
     * @param y 当たり判定の立方体の中心ローカルY座標
     * @param z 当たり判定の立方体の中心ローカルZ座標
     * @param prm_edge １辺の長さ
     * @param pos_prism プリズム位置（GgafDxAAPrismActor の #define 定義参照)
     */
    void setColliAAPrism_Cube(int prm_index, coord x, coord y, coord z, coord prm_edge, int pos_prism) {
        int h = prm_edge / 2;
        setColliAAPrism(prm_index, x-h, y-h, z-h, x+h, y+h, z+h, pos_prism);
    }

    /**
     * 当たり判定領域要素を軸平行立方体として定義 .
     * 引数座標を中心として、１辺の長さで指定
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定の立方体の中心ローカルX座標
     * @param y 当たり判定の立方体の中心ローカルY座標
     * @param z 当たり判定の立方体の中心ローカルZ座標
     * @param prm_edge １辺の長さ
     * @param rot_x 当たり判定の立方体を、向きに伴ってローカルX軸での回転平行移動を行う場合 true
     * @param rot_y 当たり判定の立方体を、向きに伴ってローカルY軸での回転平行移動を行う場合 true
     * @param rot_z 当たり判定の立方体を、向きに伴ってローカルZ軸での回転平行移動を行う場合 true
     * @param pos_prism プリズム位置（GgafDxAAPrismActor の #define 定義参照)
     */
    void setColliAAPrism_Cube(int prm_index, coord x, coord y, coord z, coord prm_edge, int pos_prism, bool rot_x, bool rot_y, bool rot_z) {
        int h = prm_edge / 2;
        setColliAAPrism(prm_index, x-h, y-h, z-h, x+h, y+h, z+h, pos_prism, rot_x, rot_y, rot_z);
    }

    /**
     * 当たり判定領域要素を軸平行立方体として定義 .
     * オブジェクトの基点を中心として、１辺の長さで指定
     * @param prm_index 当たり判定領域の要素番号
     * @param prm_edge １辺の長さ
     * @param pos_prism プリズム位置（GgafDxAAPrismActor.h の、捕捉コメント参照)
     */
    void setColliAAPrism_Cube(int prm_index, coord prm_edge, int pos_prism) {
        setColliAAPrism_Cube(prm_index, 0, 0, 0, prm_edge, pos_prism);
    }


    /**
     * 自身の判定領域と他の当たり判定領域と接触しているか調べる
     * @param prm_pOppChecker 他の当たり判定領域
     * @return true:当たっている / false:当たっていない
     */
    virtual bool isHit(GgafDxCore::GgafDxChecker* prm_pOppChecker) override;

    virtual ~CollisionChecker3D();
};

}
#endif /*GGAFLIB_COLLISIONCHECKER_H_*/

