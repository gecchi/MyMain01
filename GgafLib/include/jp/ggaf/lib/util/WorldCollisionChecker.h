#ifndef GGAF_LIB_WORLDCOLLISIONCHECKER_H_
#define GGAF_LIB_WORLDCOLLISIONCHECKER_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/util/CollisionChecker.h"

namespace GgafLib {

/**
 * ワールド空間の衝突チェッカークラス.
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
class WorldCollisionChecker : public GgafDx::CollisionChecker {

public:
#ifdef MY_DEBUG
    /** １フレームの当たり判定要素同士の判定回数 */
    static unsigned int _num_check;
    static unsigned int _num_otoku_check;
    static unsigned int _num_otoku_check_actors;
    static unsigned int _num_zannen_check;
    static unsigned int _num_check_actors;

#endif

    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  当たり判定機能を追加するActor
     */
    explicit WorldCollisionChecker(GgafDx::GeometricActor* prm_pActor);

    static bool initStatic();

    void changeColliSphereR(int prm_index, coord r);

    /**
     * 当たり判定領域要素を球として定義 .
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定の球の中心X座標（Actorローカル座標）
     * @param y 当たり判定の球の中心Y座標（Actorローカル座標）
     * @param z 当たり判定の球の中心Z座標（Actorローカル座標）
     * @param r 当たり判定の球の半径
     * @param rot_x 当たり判定の球を、Actorの向きに伴ってActorローカルX軸を中心に回転平行移動を行う場合 true
     * @param rot_y 当たり判定の球を、Actorの向きに伴ってActorローカルY軸を中心に回転平行移動を行う場合 true
     * @param rot_z 当たり判定の球を、Actorの向きに伴ってActorローカルZ軸を中心に回転平行移動を行う場合 true
     */
    void setColliSphere(int prm_index, coord x, coord y, coord z, coord r, bool rot_x, bool rot_y, bool rot_z);

    /**
     * 当たり判定領域要素を球として定義 .
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定の球の中心X座標（Actorローカル座標）
     * @param y 当たり判定の球の中心Y座標（Actorローカル座標）
     * @param z 当たり判定の球の中心Z座標（Actorローカル座標）
     * @param r 当たり判定の球の半径
     */
    void setColliSphere(int prm_index, coord x, coord y, coord z, coord r) {
        setColliSphere(prm_index, x, y, z, r, false, false, false);
    }

    /**
     * 当たり判定領域要素を球として定義 .
     * 当たり判定の球の中心座標は、Actorローカル座標の原点に設定される。
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index 当たり判定領域の要素番号
     * @param r 当たり判定の球の半径
     */
    void setColliSphere(int prm_index, coord r) {
        setColliSphere(prm_index, 0, 0, 0, r, false, false, false);
    }

    /**
     * 当たり判定領域要素を軸平行直方体として定義 .
     * @param prm_index 当たり判定領域の要素番号
     * @param x1 当たり判定直方体の左下手前X座標（Actorローカル座標）
     * @param y1 当たり判定直方体の左下手前Y座標（Actorローカル座標）
     * @param z1 当たり判定直方体の左下手前Z座標（Actorローカル座標）
     * @param x2 当たり判定直方体の右上奥X座標（Actorローカル座標）
     * @param y2 当たり判定直方体の右上奥Y座標（Actorローカル座標）
     * @param z2 当たり判定直方体の右上奥Z座標（Actorローカル座標）
     * @param rot_x 当たり判定の直方体を、Actorの向きに伴ってActorローカルX軸を中心に回転平行移動を行う場合 true
     * @param rot_y 当たり判定の直方体を、Actorの向きに伴ってActorローカルY軸を中心に回転平行移動を行う場合 true
     * @param rot_z 当たり判定の直方体を、Actorの向きに伴ってActorローカルZ軸を中心に回転平行移動を行う場合 true
     */
    void setColliAABox(int prm_index,
                       coord x1, coord y1, coord z1,
                       coord x2, coord y2, coord z2,
                       bool rot_x, bool rot_y, bool rot_z);

    /**
     * 当たり判定領域要素を軸平行直方体として定義 .
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index 当たり判定領域の要素番号
     * @param x1 当たり判定直方体の左下手前X座標（Actorローカル座標）
     * @param y1 当たり判定直方体の左下手前Y座標（Actorローカル座標）
     * @param z1 当たり判定直方体の左下手前Z座標（Actorローカル座標）
     * @param x2 当たり判定直方体の右上奥X座標（Actorローカル座標）
     * @param y2 当たり判定直方体の右上奥Y座標（Actorローカル座標）
     * @param z2 当たり判定直方体の右上奥Z座標（Actorローカル座標）
     */
    void setColliAABox(int prm_index,
                       coord x1, coord y1, coord z1,
                       coord x2, coord y2, coord z2) {
        setColliAABox(prm_index, x1, y1, z1, x2, y2, z2, false, false, false);
    }

    /**
     * 当たり判定領域要素を軸平行直方体として定義 .
     * 当たり判定直方体の中心座標と、幅、高さ、奥行で指定。
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定直方体の中心X座標（Actorローカル座標）
     * @param y 当たり判定直方体の中心Y座標（Actorローカル座標）
     * @param z 当たり判定直方体の中心Z座標（Actorローカル座標）
     * @param prm_width 当たり判定直方体の幅（X軸方向の長さ）
     * @param prm_height 当たり判定直方体の高さ（Y軸方向の長さ）
     * @param prm_depth 当たり判定直方体の深さ（奥行・Z軸方向の長さ）
     * @param rot_x 当たり判定の直方体を、Actorの向きに伴ってActorローカルX軸を中心に回転平行移動を行う場合 true
     * @param rot_y 当たり判定の直方体を、Actorの向きに伴ってActorローカルY軸を中心に回転平行移動を行う場合 true
     * @param rot_z 当たり判定の直方体を、Actorの向きに伴ってActorローカルZ軸を中心に回転平行移動を行う場合 true
     */
    void setColliAABox_WHD(int prm_index, coord x, coord y, coord z, coord prm_width, coord prm_height, coord prm_depth, bool rot_x, bool rot_y, bool rot_z) {
        int hw = prm_width  / 2;
        int hh = prm_height / 2;
        int hd = prm_depth  / 2;
        setColliAABox(prm_index, x-hw, y-hh, z-hd, x+hw, y+hh, z+hd, rot_x, rot_y, rot_z);
    }

    /**
     * 当たり判定領域要素を軸平行直方体として定義 .
     * 当たり判定直方体の中心座標と、幅、高さ、奥行で指定。
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index
     * @param x 当たり判定直方体の中心X座標（Actorローカル座標）
     * @param y 当たり判定直方体の中心Y座標（Actorローカル座標）
     * @param z 当たり判定直方体の中心Z座標（Actorローカル座標）
     * @param prm_width 当たり判定直方体の幅（X軸方向の長さ）
     * @param prm_height 当たり判定直方体の高さ（Y軸方向の長さ）
     * @param prm_depth 当たり判定直方体の深さ（奥行・Z軸方向の長さ）
     */
    void setColliAABox_WHD(int prm_index, coord x, coord y, coord z, coord prm_width, coord prm_height, coord prm_depth) {
        setColliAABox_WHD(prm_index, x, y, z, prm_width, prm_height, prm_depth, false, false, false);
    }

    /**
     * 当たり判定領域要素を軸平行直方体として定義 .
     * 当たり判定直方体の幅、高さ、奥行で指定。
     * 当たり判定直方体の中心座標は、Actorローカル座標の原点に設定される。
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index 当たり判定領域の要素番号
     * @param prm_width 当たり判定直方体の幅（X軸方向の長さ）
     * @param prm_height 当たり判定直方体の高さ（Y軸方向の長さ）
     * @param prm_depth 当たり判定直方体の深さ（奥行・Z軸方向の長さ）
     */
    void setColliAABox_WHD(int prm_index, coord prm_width, coord prm_height, coord prm_depth) {
        setColliAABox_WHD(prm_index, 0, 0, 0, prm_width, prm_height, prm_depth);
    }

    /**
     * 当たり判定領域要素を軸平行立方体として定義 .
     * 当たり判定立方体の中心座標と、１辺の長さで指定。
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定立方体の中心X座標（Actorローカル座標）
     * @param y 当たり判定立方体の中心Y座標（Actorローカル座標）
     * @param z 当たり判定立方体の中心Z座標（Actorローカル座標）
     * @param prm_edge 当たり判定立方体の１辺の長さ
     * @param rot_x 当たり判定の立方体を、Actorの向きに伴ってActorローカルX軸を中心に回転平行移動を行う場合 true
     * @param rot_y 当たり判定の立方体を、Actorの向きに伴ってActorローカルY軸を中心に回転平行移動を行う場合 true
     * @param rot_z 当たり判定の立方体を、Actorの向きに伴ってActorローカルZ軸を中心に回転平行移動を行う場合 true
     */
    void setColliAACube(int prm_index, coord x, coord y, coord z, coord prm_edge, bool rot_x, bool rot_y, bool rot_z) {
        int h = prm_edge / 2;
        setColliAABox(prm_index, x-h, y-h, z-h, x+h, y+h, z+h, rot_x, rot_y, rot_z);
    }

    /**
     * 当たり判定領域要素を軸平行立方体として定義 .
     * 当たり判定立方体の中心座標と、１辺の長さで指定。
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定立方体の中心X座標（Actorローカル座標）
     * @param y 当たり判定立方体の中心Y座標（Actorローカル座標）
     * @param z 当たり判定立方体の中心Z座標（Actorローカル座標）
     * @param prm_edge 当たり判定立方体の１辺の長さ
     */
    void setColliAACube(int prm_index, coord x, coord y, coord z, coord prm_edge) {
        setColliAACube(prm_index, x, y, z, prm_edge, false, false, false);
    }

    /**
     * 当たり判定領域要素を軸平行立方体として定義 .
     * 当たり判定立方体の１辺の長さで指定。
     * 当たり判定立方体の中心座標は、Actorローカル座標の原点に設定される。
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index 当たり判定領域の要素番号
     * @param prm_edge 当たり判定立方体の１辺の長さ
     */
    void setColliAACube(int prm_index, coord prm_edge) {
        setColliAACube(prm_index, 0, 0, 0, prm_edge);
    }

    /**
     * 当たり判定領域要素を軸平行プリズム型として定義 .
     * @param prm_index 当たり判定領域の要素番号
     * @param x1 当たり判定プリズム型の境界直方体の左下手前X座標（Actorローカル座標）
     * @param y1 当たり判定プリズム型の境界直方体の左下手前Y座標（Actorローカル座標）
     * @param z1 当たり判定プリズム型の境界直方体の左下手前Z座標（Actorローカル座標）
     * @param x2 当たり判定プリズム型の境界直方体の右上奥X座標（Actorローカル座標）
     * @param y2 当たり判定プリズム型の境界直方体の右上奥Y座標（Actorローカル座標）
     * @param z2 当たり判定プリズム型の境界直方体の右上奥Z座標（Actorローカル座標）
     * @param pos_info プリズム位置（POS_PRISM_**_**)
     * @param rot_x 当たり判定のプリズム型を、Actorの向きに伴ってActorローカルX軸を中心に回転平行移動を行う場合 true
     * @param rot_y 当たり判定のプリズム型を、Actorの向きに伴ってActorローカルY軸を中心に回転平行移動を行う場合 true
     * @param rot_z 当たり判定のプリズム型を、Actorの向きに伴ってActorローカルZ軸を中心に回転平行移動を行う場合 true
     */
    void setColliAAPrism(int prm_index, coord x1, coord y1, coord z1, coord x2, coord y2, coord z2, pos_t pos_info, bool rot_x, bool rot_y, bool rot_z);

    /**
     * 当たり判定領域要素を軸平行プリズム型として定義 .
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index 当たり判定領域の要素番号
     * @param x1 当たり判定プリズム型の境界直方体の左下手前X座標（Actorローカル座標）
     * @param y1 当たり判定プリズム型の境界直方体の左下手前Y座標（Actorローカル座標）
     * @param z1 当たり判定プリズム型の境界直方体の左下手前Z座標（Actorローカル座標）
     * @param x2 当たり判定プリズム型の境界直方体の右上奥X座標（Actorローカル座標）
     * @param y2 当たり判定プリズム型の境界直方体の右上奥Y座標（Actorローカル座標）
     * @param z2 当たり判定プリズム型の境界直方体の右上奥Z座標（Actorローカル座標）
     * @param pos_info プリズム位置（GgafDx::AAPrismActor の #define 定義参照)
     */
    void setColliAAPrism(int prm_index, coord x1, coord y1, coord z1, coord x2, coord y2, coord z2, pos_t pos_info) {
        setColliAAPrism(prm_index, x1, y1, z1, x2, y2, z2, pos_info, false, false, false);
    }


    /**
     * 当たり判定領域要素を軸平行プリズム型として定義 .
     * 当たり判定プリズム型の境界直方体の中心座標と、幅、高さ、奥行で指定。
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定プリズム型の境界直方体の中心X座標（Actorローカル座標）
     * @param y 当たり判定プリズム型の境界直方体の中心Y座標（Actorローカル座標）
     * @param z 当たり判定プリズム型の境界直方体の中心Z座標（Actorローカル座標）
     * @param prm_width 当たり判定プリズム型の境界直方体の幅（X軸方向の長さ）
     * @param prm_height 当たり判定プリズム型の境界直方体の高さ（Y軸方向の長さ）
     * @param prm_depth 当たり判定プリズム型の境界直方体の深さ（奥行・Z軸方向の長さ）
     * @param pos_info プリズム位置（GgafDx::AAPrismActor の #define 定義参照)
     */
    void setColliAAPrism_WHD(int prm_index, coord x, coord y, coord z, coord prm_width, coord prm_height, coord prm_depth, pos_t pos_info) {
        int hw = prm_width  / 2;
        int hh = prm_height / 2;
        int hd = prm_depth  / 2;
        setColliAAPrism(prm_index, x-hw, y-hh, z-hd, x+hw, y+hh, z+hd, pos_info);
    }

    /**
     * 当たり判定領域要素を軸平行プリズム型として定義 .
     * 当たり判定プリズム型の境界直方体の幅、高さ、奥行で指定。
     * 当たり判定プリズム型の境界直方体の中心座標は、Actorローカル座標の原点に設定される。
     * (必ず斜面がActorローカル座標の原点に接することになる)
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index 当たり判定領域の要素番号
     * @param prm_width 当たり判定プリズム型の境界直方体の幅（X軸方向の長さ）
     * @param prm_height 当たり判定プリズム型の境界直方体の高さ（Y軸方向の長さ）
     * @param prm_depth 当たり判定プリズム型の境界直方体の深さ（奥行・Z軸方向の長さ）
     * @param pos_info プリズム位置（GgafDx::AAPrismActor の #define 定義参照)
     */
    void setColliAAPrism_WHD(int prm_index, coord prm_width, coord prm_height, coord prm_depth, pos_t pos_info) {
        setColliAAPrism_WHD(prm_index, 0, 0, 0, prm_width, prm_height, prm_depth, pos_info);
    }

    /**
     * 当たり判定領域要素を軸平行プリズム型として定義 .
     * 当たり判定プリズム型の境界立方体の中心座標と、１辺の長さで指定。
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定プリズム型の境界立方体の中心X座標（Actorローカル座標）
     * @param y 当たり判定プリズム型の境界立方体の中心Y座標（Actorローカル座標）
     * @param z 当たり判定プリズム型の境界立方体の中心Z座標（Actorローカル座標）
     * @param prm_edge 当たり判定プリズム型の境界立方体の１辺の長さ
     * @param rot_x 当たり判定のプリズム型を、Actorの向きに伴ってActorローカルX軸を中心に回転平行移動を行う場合 true
     * @param rot_y 当たり判定のプリズム型を、Actorの向きに伴ってActorローカルY軸を中心に回転平行移動を行う場合 true
     * @param rot_z 当たり判定のプリズム型を、Actorの向きに伴ってActorローカルZ軸を中心に回転平行移動を行う場合 true
     * @param pos_info プリズム位置（GgafDx::AAPrismActor の #define 定義参照)
     */
    void setColliAAPrism_Cube(int prm_index, coord x, coord y, coord z, coord prm_edge, pos_t pos_info, bool rot_x, bool rot_y, bool rot_z) {
        int h = prm_edge / 2;
        setColliAAPrism(prm_index, x-h, y-h, z-h, x+h, y+h, z+h, pos_info, rot_x, rot_y, rot_z);
    }

    /**
     * 当たり判定領域要素を軸平行プリズム型として定義 .
     * 当たり判定プリズム型の境界立方体の中心座標と、１辺の長さで指定。
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定プリズム型の境界立方体の中心X座標（Actorローカル座標）
     * @param y 当たり判定プリズム型の境界立方体の中心Y座標（Actorローカル座標）
     * @param z 当たり判定プリズム型の境界立方体の中心Z座標（Actorローカル座標）
     * @param prm_edge 当たり判定プリズム型の境界立方体の１辺の長さ
     * @param pos_info プリズム位置（GgafDx::AAPrismActor の #define 定義参照)
     */
    void setColliAAPrism_Cube(int prm_index, coord x, coord y, coord z, coord prm_edge, pos_t pos_info) {
        setColliAAPrism_Cube(prm_index, x, y, z, prm_edge, pos_info, false, false, false);
    }

    /**
     * 当たり判定領域要素を軸平行プリズム型として定義 .
     * 当たり判定プリズム型の境界立方体の１辺の長さで指定。
     * 当たり判定プリズム型の境界立方体の中心座標は、Actorローカル座標の原点に設定される。
     * (必ず斜面がActorローカル座標の原点に接することになる)
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index 当たり判定領域の要素番号
     * @param prm_edge 当たり判定プリズム型の境界立方体の１辺の長さ
     * @param pos_info プリズム位置（GgafDx::AAPrismActor.h の、捕捉コメント参照)
     */
    void setColliAAPrism_Cube(int prm_index, coord prm_edge, pos_t pos_info) {
        setColliAAPrism_Cube(prm_index, 0, 0, 0, prm_edge, pos_info);
    }

    /**
     * 当たり判定領域要素を軸平行直角三角錐として定義 .
     * @param prm_index 当たり判定領域の要素番号
     * @param x1 当たり判定直角三角錐の境界直方体の左下手前X座標（Actorローカル座標）
     * @param y1 当たり判定直角三角錐の境界直方体の左下手前Y座標（Actorローカル座標）
     * @param z1 当たり判定直角三角錐の境界直方体の左下手前Z座標（Actorローカル座標）
     * @param x2 当たり判定直角三角錐の境界直方体の右上奥X座標（Actorローカル座標）
     * @param y2 当たり判定直角三角錐の境界直方体の右上奥Y座標（Actorローカル座標）
     * @param z2 当たり判定直角三角錐の境界直方体の右上奥Z座標（Actorローカル座標）
     * @param pos_info ピラミッド位置（POS_PYRAMID_***)
     * @param rot_x 当たり判定の直角三角錐の境界直方体を、Actorの向きに伴ってActorローカルX軸を中心に回転平行移動を行う場合 true
     * @param rot_y 当たり判定の直角三角錐の境界直方体を、Actorの向きに伴ってActorローカルY軸を中心に回転平行移動を行う場合 true
     * @param rot_z 当たり判定の直角三角錐の境界直方体を、Actorの向きに伴ってActorローカルZ軸を中心に回転平行移動を行う場合 true
     */
    void setColliAAPyramid(int prm_index, coord x1, coord y1, coord z1, coord x2, coord y2, coord z2, pos_t pos_info, bool rot_x, bool rot_y, bool rot_z);

    /**
     * 当たり判定領域要素を軸平行の三直角三角錐として定義 .
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index 当たり判定領域の要素番号
     * @param x1 当たり判定直角三角錐の境界直方体の左下手前X座標（Actorローカル座標）
     * @param y1 当たり判定直角三角錐の境界直方体の左下手前Y座標（Actorローカル座標）
     * @param z1 当たり判定直角三角錐の境界直方体の左下手前Z座標（Actorローカル座標）
     * @param x2 当たり判定直角三角錐の境界直方体の右上奥X座標（Actorローカル座標）
     * @param y2 当たり判定直角三角錐の境界直方体の右上奥Y座標（Actorローカル座標）
     * @param z2 当たり判定直角三角錐の境界直方体の右上奥Z座標（Actorローカル座標）
     * @param pos_info ピラミッド位置（POS_PYRAMID_***)
     */
    void setColliAAPyramid(int prm_index, coord x1, coord y1, coord z1, coord x2, coord y2, coord z2, pos_t pos_info) {
        setColliAAPyramid(prm_index, x1, y1, z1, x2, y2, z2, pos_info, false, false, false);
    }

    /**
     * 当たり判定領域要素を軸平行の三直角三角錐として定義 .
     * 当たり判定三直角三角錐の境界直方体の中心座標と、幅、高さ、奥行で指定。
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり三直角三角錐の境界直方体の中心X座標（Actorローカル座標）
     * @param y 当たり三直角三角錐の境界直方体の中心Y座標（Actorローカル座標）
     * @param z 当たり三直角三角錐の境界直方体の中心Z座標（Actorローカル座標）
     * @param prm_width 当たり三直角三角錐の境界直方体の幅（X軸方向の長さ）
     * @param prm_height 当たり三直角三角錐の境界直方体の高さ（Y軸方向の長さ）
     * @param prm_depth 当たり三直角三角錐の境界直方体の深さ（奥行・Z軸方向の長さ）
     * @param pos_info ピラミッド位置（POS_PYRAMID_***)
     */
    void setColliAAPyramid_WHD(int prm_index, coord x, coord y, coord z, coord prm_width, coord prm_height, coord prm_depth, pos_t pos_info) {
        int hw = prm_width  / 2;
        int hh = prm_height / 2;
        int hd = prm_depth  / 2;
        setColliAAPyramid(prm_index, x-hw, y-hh, z-hd, x+hw, y+hh, z+hd, pos_info);
    }

    /**
     * 当たり判定領域要素を軸平行の三直角三角錐として定義 .
     * 当たり三直角三角錐の境界直方体の幅、高さ、奥行で指定。
     * 当たり三直角三角錐の境界直方体の中心座標は、Actorローカル座標の原点に設定される。
     * (必ず斜面がActorローカル座標の原点に接することになる)
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index 当たり判定領域の要素番号
     * @param prm_width 当たり三直角三角錐の境界直方体の幅（X軸方向の長さ）
     * @param prm_height 当たり三直角三角錐の境界直方体の高さ（Y軸方向の長さ）
     * @param prm_depth 当たり三直角三角錐の境界直方体の深さ（奥行・Z軸方向の長さ）
     * @param pos_info プリズム位置（GgafDx::AAPrismActor の #define 定義参照)
     */
    void setColliAAPyramid_WHD(int prm_index, coord prm_width, coord prm_height, coord prm_depth, pos_t pos_info) {
        setColliAAPyramid_WHD(prm_index, 0, 0, 0, prm_width, prm_height, prm_depth, pos_info);
    }

    /**
     * 当たり判定領域要素を軸平行プリズム型として定義 .
     * 当たり判定三直角三角錐の境界立方体の中心座標と、１辺の長さで指定。
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定三直角三角錐の境界立方体の中心X座標（Actorローカル座標）
     * @param y 当たり判定三直角三角錐の境界立方体の中心Y座標（Actorローカル座標）
     * @param z 当たり判定三直角三角錐の境界立方体の中心Z座標（Actorローカル座標）
     * @param prm_edge 当たり判定三直角三角錐の境界立方体の１辺の長さ
     * @param rot_x 当たり判定の三直角三角錐を、Actorの向きに伴ってActorローカルX軸を中心に回転平行移動を行う場合 true
     * @param rot_y 当たり判定の三直角三角錐を、Actorの向きに伴ってActorローカルY軸を中心に回転平行移動を行う場合 true
     * @param rot_z 当たり判定の三直角三角錐を、Actorの向きに伴ってActorローカルZ軸を中心に回転平行移動を行う場合 true
     * @param pos_info ピラミッド位置（GgafDx::AAPyramidActor の #define 定義参照)
     */
    void setColliAAPyramid_Cube(int prm_index, coord x, coord y, coord z, coord prm_edge, pos_t pos_info, bool rot_x, bool rot_y, bool rot_z) {
        int h = prm_edge / 2;
        setColliAAPyramid(prm_index, x-h, y-h, z-h, x+h, y+h, z+h, pos_info, rot_x, rot_y, rot_z);
    }

    /**
     * 当たり判定領域要素を軸平行立方体として定義 .
     * 当たり判定三直角三角錐の境界立方体の中心座標と、１辺の長さで指定。
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定三直角三角錐の境界立方体の中心X座標（Actorローカル座標）
     * @param y 当たり判定三直角三角錐の境界立方体の中心Y座標（Actorローカル座標）
     * @param z 当たり判定三直角三角錐の境界立方体の中心Z座標（Actorローカル座標）
     * @param prm_edge 当たり判定三直角三角錐の境界立方体の１辺の長さ
     * @param pos_info ピラミッド位置（GgafDx::AAPyramidActor の #define 定義参照)
     */
    void setColliAAPyramid_Cube(int prm_index, coord x, coord y, coord z, coord prm_edge, pos_t pos_info) {
        setColliAAPyramid_Cube(prm_index, x, y, z, prm_edge, pos_info, false, false, false);
    }

    /**
     * 当たり判定領域要素を軸平行立方体として定義 .
     * 当たり判定三直角三角錐の境界立方体の１辺の長さで指定。
     * 当たり判定三直角三角錐の境界立方体の中心座標は、Actorローカル座標の原点に設定される。
     * (必ず斜面がActorローカル座標の原点に接することになる)
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index 当たり判定領域の要素番号
     * @param prm_edge 当たり三直角三角錐型の境界立方体の１辺の長さ
     * @param pos_info ピラミッド位置（GgafDx::AAPyramidActor.h の、捕捉コメント参照)
     */
    void setColliAAPyramid_Cube(int prm_index, coord prm_edge, pos_t pos_info) {
        setColliAAPyramid_Cube(prm_index, 0, 0, 0, prm_edge, pos_info);
    }


    void moveColliAABoxPos(int prm_index, coord cx, coord cy, coord cz);

/////////////////////////////////////////////////////////

    /**
     * 当たり判定領域要素を円として定義 .
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定の円の中心X座標（Actorローカル座標）
     * @param y 当たり判定の円の中心Y座標（Actorローカル座標）
     * @param r 当たり判定の円の半径
     * @param rot_z 当たり判定の円を、Actorの向きに伴ってActorローカルZ軸を中心に回転平行移動を行う場合 true
     */
    void set2DColliCircle(int prm_index, coord x, coord y, coord r, bool rot_z=false) {
        setColliSphere(prm_index, x, y, 0, r, false, false, rot_z);
    }

    /**
     * 当たり判定領域要素を円として定義 .
     * 当たり判定の円の中心座標は、Actorローカル座標の原点に設定される。
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index 当たり判定領域の要素番号
     * @param r 当たり判定の円の半径
     */
    void set2DColliCircle(int prm_index, coord r) {
        set2DColliCircle(prm_index, 0, 0, r, false);
    }

    /**
     * 当たり判定領域要素を軸平行長方形として定義 .
     * @param prm_index 当たり判定領域の要素番号
     * @param x1 当たり判定直方体の左下X座標（Actorローカル座標）
     * @param y1 当たり判定直方体の左下Y座標（Actorローカル座標）
     * @param x2 当たり判定直方体の右上X座標（Actorローカル座標）
     * @param y2 当たり判定直方体の右上Y座標（Actorローカル座標）
     * @param rot_z 当たり判定の直方体を、Actorの向きに伴ってActorローカル原点を中心に回転平行移動を行う場合 true
     */
    void set2DColliRectangle(int prm_index,
                             coord x1, coord y1,
                             coord x2, coord y2,
                             bool rot_z = false) {
        setColliAABox(prm_index,
                      x1, y1, 0,
                      x2, y2, 0,
                      false, false, rot_z);
    }

    /**
     * 当たり判定領域要素を軸平行正方形として定義 .
     * 当たり判定正方形の中心座標と、１辺の長さで指定。
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定正方形の中心X座標（Actorローカル座標）
     * @param y 当たり判定正方形の中心Y座標（Actorローカル座標）
     * @param prm_edge 当たり判定正方形の１辺の長さ
     * @param rot_z 当たり判定の正方形を、Actorの向きに伴ってActorローカル原点を中心に回転平行移動を行う場合 true
     */
    void set2DColliSquare(int prm_index, coord x, coord y, coord prm_edge, bool rot_z = false) {
        coord h = prm_edge / 2;
        set2DColliRectangle(prm_index, x-h, y-h, x+h, y+h, rot_z);
    }

    /**
     * 当たり判定領域要素を軸平行正方形として定義 .
     * 当たり判定正方形の１辺の長さで指定。
     * 当たり判定正方形の中心座標は、Actorローカル座標の原点に設定される。
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index 当たり判定領域の要素番号
     * @param prm_edge 当たり判定正方形の１辺の長さ
     */
    void set2DColliSquare(int prm_index, coord prm_edge) {
        set2DColliSquare(prm_index, 0, 0, prm_edge, false);
    }

    /**
     * 当たり判定領域要素を軸平行長方形して定義 .
     * 当たり判定長方形の中心座標と、幅、高さで指定。
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定長方形の中心X座標（Actorローカル座標）
     * @param y 当たり判定長方形の中心Y座標（Actorローカル座標）
     * @param prm_width 当たり判定長方形の幅（X軸方向の長さ）
     * @param prm_height 当たり判定長方形の高さ（Y軸方向の長さ）
     * @param rot_z 当たり判定の長方形を、Actorの向きに伴ってActorローカルZ軸を中心に回転平行移動を行う場合 true
     */
    void set2DColliRectangle_WH(int prm_index, coord x, coord y, coord prm_width, coord prm_height, bool rot_z = false) {
        int hw = prm_width  / 2;
        int hh = prm_height / 2;
        set2DColliRectangle(prm_index, x-hw, y-hh, x+hw, y+hh, rot_z);
    }

    /**
     * 当たり判定領域要素を軸平行長方形として定義 .
     * 当たり判定長方形の幅、高さ、奥行で指定。
     * 当たり判定長方形の中心座標は、Actorローカル座標の原点に設定される。
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index 当たり判定領域の要素番号
     * @param prm_width 当たり判定長方形の幅（X軸方向の長さ）
     * @param prm_height 当たり判定長方形の高さ（Y軸方向の長さ）
     */
    void set2DColliRectangle_WH(int prm_index, coord prm_width, coord prm_height) {
        set2DColliRectangle_WH(prm_index, 0, 0, prm_width, prm_height);
    }

    /**
     * 当たり判定領域要素を軸平行直角三角形として定義 .
     * @param prm_index 当たり判定領域の要素番号
     * @param x1 当たり判定直角三角形の境界長方形の左下X座標（Actorローカル座標）
     * @param y1 当たり判定直角三角形の境界長方形の左下Y座標（Actorローカル座標）
     * @param x2 当たり判定直角三角形の境界長方形の右上X座標（Actorローカル座標）
     * @param y2 当たり判定直角三角形の境界長方形の右上Y座標（Actorローカル座標）
     * @param pos_info 直角位置（POS_R_TRIANGLE_**)
     * @param rot_z 当たり判定の直角三角形を、Actorの向きに伴ってActorローカルZ軸を中心に回転平行移動を行う場合 true
     */
    void set2DColliRightTriangle(int prm_index, coord x1, coord y1, coord x2, coord y2, pos_t pos_info, bool rot_z=false) {
        setColliAAPrism(prm_index, x1, y1, 0, x2, y2, 0, pos_info, false, false, rot_z);
    }

    /**
     * 当たり判定領域要素を軸平行直角三角形として定義 .
     * 当たり判定直角三角形の境界長方形の中心座標と、幅、高さ、奥行で指定。
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定直角三角形の境界長方形の中心X座標（Actorローカル座標）
     * @param y 当たり判定直角三角形の境界長方形の中心Y座標（Actorローカル座標）
     * @param prm_width 当たり判定直角三角形の境界長方形の幅（X軸方向の長さ）
     * @param prm_height 当たり判定直角三角形の境界長方形の高さ（Y軸方向の長さ）
     * @param pos_info 直角位置（POS_R_TRIANGLE_**)
     * @param rot_z 当たり判定の直角三角形を、Actorの向きに伴ってActorローカルZ軸を中心に回転平行移動を行う場合 true
     */
    void set2DColliRightTriangle_WH(int prm_index, coord x, coord y, coord prm_width, coord prm_height, pos_t pos_info, bool rot_z=false) {
        int hw = prm_width  / 2;
        int hh = prm_height / 2;
        set2DColliRightTriangle(prm_index, x-hw, y-hh, x+hw, y+hh, pos_info, rot_z);
    }

    /**
     * 当たり判定領域要素を軸平行直角二等辺三角形として定義 .
     * 当たり判定直角三角形の境界正方形の中心座標と、１辺の長さで指定
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定直角三角形の境界正方形の中心X座標（Actorローカル座標）
     * @param y 当たり判定直角三角形の境界正方形の中心Y座標（Actorローカル座標）
     * @param prm_width 当たり判定直角三角形の境界正方形の１辺の長さ（斜辺ではありません）
     * @param pos_info 直角位置（POS_R_TRIANGLE_**)
     * @param rot_z 当たり判定の直角三角形を、Actorの向きに伴ってActorローカルZ軸を中心に回転平行移動を行う場合 true
     */
    void set2DColliIsoRightTriangle(int prm_index, coord x, coord y, coord prm_edge, pos_t pos_info, bool rot_z=false) {
        int h = prm_edge / 2;
        set2DColliRightTriangle(prm_index, x-h, y-h, x+h, y+h, pos_info, rot_z);
    }

    /**
     * 当たり判定領域要素を軸平行直角二等辺三角形として定義 .
     * 当たり判定直角三角形の境界正方形の中心座標と、１辺の長さで指定。
     * 当たり判定直角三角形の境界正方形の中心座標は、Actorローカル座標の原点に設定される。
     * (必ず斜辺がActorローカル座標の原点に接することになる)
     * Actorの向きに伴って当たり判定の回転平行移動機能は無し。
     * @param prm_index 当たり判定領域の要素番号
     * @param x 当たり判定直角三角形の境界正方形の中心X座標（Actorローカル座標）
     * @param y 当たり判定直角三角形の境界正方形の中心Y座標（Actorローカル座標）
     * @param prm_width 当たり判定直角三角形の境界正方形の１辺の長さ（斜辺ではありません）
     * @param pos_info 直角位置（POS_R_TRIANGLE_**)
     * @param rot_z 当たり判定の直角三角形を、Actorの向きに伴ってActorローカルZ軸を中心に回転平行移動を行う場合 true
     */
    void set2DColliIsoRightTriangle(int prm_index, coord prm_edge, pos_t pos_info) {
        set2DColliIsoRightTriangle(prm_index, 0, 0, prm_edge, pos_info, false);
    }

    GgafDx::CollisionPart* getLastHitCollisionPart();

    static void drawHitArea(GgafDx::CollisionChecker* prm_pChecker);
    static void releaseHitArea();

    virtual ~WorldCollisionChecker();
};

}
#endif /*GGAF_LIB_WORLDCOLLISIONCHECKER_H_*/

