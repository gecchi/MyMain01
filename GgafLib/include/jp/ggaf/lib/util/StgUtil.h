#ifndef GGAF_LIB_STGUTIL_H_
#define GGAF_LIB_STGUTIL_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/util/Util.h"

#include "jp/ggaf/lib/util/ColliAABox.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"

#ifdef UTIL
    #undef UTIL
#endif
#define UTIL GgafLib::StgUtil

namespace GgafLib {

/**
 * ユーティリティ .
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class StgUtil: public GgafDx::Util {
public:

    static bool _was_StgUtil_inited_flg;

    static void init();

    /**
     * 半径 1000 の 1/4 円の解テーブル .
     * <pre><code>
     *      ______________
     * y = √(1000^2-x^2)
     * </code></pre>
     * の 要素[x] に対する y
     */
    static float ROOT_1_MINUS_XX[1000];

    static uint32_t BITNUM[];
    /** POS_R_TRIANGLE の X要素反転テーブル */
    static std::map<pos_t,pos_t> POS_R_TRIANGLE_inv_X;
    /** POS_R_TRIANGLE の Y要素反転テーブル */
    static std::map<pos_t,pos_t> POS_R_TRIANGLE_inv_Y;

    static GgafDx::CollisionChecker* createCollisionChecker(GgafDx::GeometricActor* prm_pActor);

    /**
     * AAB 対 AAB 当たり判定(現在直接埋め込んだので未使用) .
     * @param pActor01
     * @param pAABox01
     * @param pActor02
     * @param pAABox02
     * @return
     */
    static inline bool isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAABox* const pAABox01,
                               const GgafDx::GeometricActor* const pActor02, const ColliAABox* const pAABox02 ) {
        //＜AAB と AAB＞
        //軸が一致しない確率が高そうな順番(X>Z>Y)に判定
//        if (pActor01->_x + pAABox01->_x2 >= pActor02->_x + pAABox02->_x1) {
//            if (pActor01->_x + pAABox01->_x1 <= pActor02->_x + pAABox02->_x2) {
//                if (pActor01->_z + pAABox01->_z2 >= pActor02->_z + pAABox02->_z1) {
//                    if (pActor01->_z + pAABox01->_z1 <= pActor02->_z + pAABox02->_z2) {
//                        if (pActor01->_y + pAABox01->_y2 >= pActor02->_y + pAABox02->_y1) {
//                            if (pActor01->_y + pAABox01->_y1 <= pActor02->_y + pAABox02->_y2) {
//                                return true;
//                            }
//                        }
//                    }
//                }
//            }
//        }

//        coord max_dx = pAABox01->_hdx + pAABox02->_hdx;
//        if (ABS(pActor02->_x + pAABox02->_cx) - (pActor01->_x + pAABox01->_cx)) < max_dx) ) {
//        }
//    	を変形。

        coord max_dx = pAABox01->_hdx + pAABox02->_hdx;
        if ((ucoord)( (pActor02->_x + pAABox02->_cx) - (pActor01->_x + pAABox01->_cx) + max_dx ) < (ucoord)(2*max_dx)) {
            //↑左辺計算が0より小さい場合 unsigned キャストにより正の大きな数になるので条件成立しない事を利用し、ABSの判定を一つ除去してる。
            coord max_dz = pAABox01->_hdz + pAABox02->_hdz;
            if ((ucoord)( (pActor02->_z + pAABox02->_cz) - (pActor01->_z + pAABox01->_cz) + max_dz ) < (ucoord)(2*max_dz)) {
                coord max_dy = pAABox01->_hdy + pAABox02->_hdy;
                if ((ucoord)( (pActor02->_y + pAABox02->_cy) - (pActor01->_y + pAABox01->_cy) + max_dy ) < (ucoord)(2*max_dy)) {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * 球 対 球 当たり判定 .
     * @param pActor01
     * @param pSphere01
     * @param pActor02
     * @param pSphere02
     * @return
     */
    static bool isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliSphere* const pSphere01 ,
                        const GgafDx::GeometricActor* const pActor02, const ColliSphere* const pSphere02 );

    /**
     * AAB 対 球 当たり判定 .
     * @param pActor01
     * @param pAABox01
     * @param pActor02
     * @param pSphere02
     * @return
     */
    static bool isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAABox*  pAABox01,
                        const GgafDx::GeometricActor* const pActor02, const ColliSphere* pSphere02);

    /**
     * AAプリズム 対 AAB 当たり判定 .
     * @param pActor01
     * @param pAAPrism01
     * @param pActor02
     * @param pAABox02
     * @return
     */
    static bool isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                        const GgafDx::GeometricActor* const pActor02, const ColliAABox*   const pAABox02   );

    /**
     * AAプリズム 対 球 当たり判定 .
     * @param pActor01
     * @param pAAPrism01
     * @param pActor02
     * @param pSphere02
     * @return
     */
    static bool isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                        const GgafDx::GeometricActor* const pActor02, const ColliSphere*  const pSphere02  );

    /**
     * AAピラミッド 対 AAB 当たり判定 .
     * @param pActor01
     * @param pAAPyramid01
     * @param pActor02
     * @param pAABox02
     * @return
     */
    static bool isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAAPyramid* const pAAPyramid01,
                        const GgafDx::GeometricActor* const pActor02, const ColliAABox*     const pAABox02     );

    /**
     * AAピラミッド 対 球 当たり判定 .
     * @param pActor01
     * @param pAAPyramid01
     * @param pActor02
     * @param pSphere02
     * @return
     */
    static bool isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAAPyramid* const pAAPyramid01,
                        const GgafDx::GeometricActor* const pActor02, const ColliSphere*    const pSphere02    );


    /**
     * 2D 長方形 対 長方形 当たり判定 .
     * @param pActor01
     * @param pAABox01
     * @param pActor02
     * @param pAABox02
     * @return
     */
    static inline bool isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliAABox* const pAABox01,
                               const GgafDx::GeometricActor* const pActor02, const ColliAABox* const pAABox02 ) {
        //＜AAB と AAB＞
//        //軸が一致しない確率が高そうな順番(X>Y)に判定
//        if (pActor01->_x + pAABox01->_x2 >= pActor02->_x + pAABox02->_x1) {
//            if (pActor01->_x + pAABox01->_x1 <= pActor02->_x + pAABox02->_x2) {
//                if (pActor01->_y + pAABox01->_y2 >= pActor02->_y + pAABox02->_y1) {
//                    if (pActor01->_y + pAABox01->_y1 <= pActor02->_y + pAABox02->_y2) {
//                        return true;
//                    }
//                }
//            }
//        }

        coord max_dx = pAABox01->_hdx + pAABox02->_hdx;
        if ((ucoord)( (pActor02->_x + pAABox02->_cx) - (pActor01->_x + pAABox01->_cx) + max_dx ) < (ucoord)(2*max_dx)) {
            coord max_dy = pAABox01->_hdy + pAABox02->_hdy;
            if ((ucoord)( (pActor02->_y + pAABox02->_cy) - (pActor01->_y + pAABox01->_cy) + max_dy ) < (ucoord)(2*max_dy)) {
                return true;
            }
        }

        return false;
    }

    /**
     * 2D 円 対 円 当たり判定 .
     * @param pActor01
     * @param pSphere01
     * @param pActor02
     * @param pSphere02
     * @return
     */
    static bool isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliSphere* const pSphere01 ,
                        const GgafDx::GeometricActor* const pActor02, const ColliSphere* const pSphere02 );

    /**
     * 2D 長方形 対 円 当たり判定 .
     * @param pActor01
     * @param pAABox01
     * @param pActor02
     * @param pSphere02
     * @return
     */
    static bool isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliAABox*  pAABox01,
                        const GgafDx::GeometricActor* const pActor02, const ColliSphere* pSphere02);

    /**
     * 2D 直角三角形 対 長方形 当たり判定 .
     * @param pActor01
     * @param pAAPrism01
     * @param pActor02
     * @param pAABox02
     * @return
     */
    static bool isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                        const GgafDx::GeometricActor* const pActor02, const ColliAABox*   const pAABox02   );

    /**
     * 2D 直角三角形 対 円 当たり判定 .
     * @param pActor01
     * @param pAAPrism01
     * @param pActor02
     * @param pSphere02
     * @return
     */
    static bool isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                        const GgafDx::GeometricActor* const pActor02, const ColliSphere*  const pSphere02  );
    /**
     * 2D 直角三角形 対 円 直角三角形 .
     * @param pActor01
     * @param pAAPrism01
     * @param pActor02
     * @param pAAPrism02
     * @return
     */
    static bool isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                        const GgafDx::GeometricActor* const pActor02, const ColliAAPrism* const pAAPrism02  );

    /**
     * 単発弾を複数個撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDx::VecVehicle の移動方向、移動速度、加速度<BR>
     * @param prm_x               発射元X座標
     * @param prm_y               発射元Y座標
     * @param prm_z               発射元Z座標
     * @param prm_rz              発射方向Rz
     * @param prm_ry              発射方向Ry
     * @param prm_pDepo_shot      発射するショットのデポジトリ
     * @param prm_r               発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_velo_first      初弾のショット初期速度
     * @param prm_acce            初弾のショット初期加速度
     * @param prm_set_num         撃つ弾の合計数
     * @param prm_interval_frames 弾と弾の出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全弾一斉発射。）
     * @param prm_attenuated      初弾セット以降のセット毎のショット初期速度へ乗率。速度減衰(< 1.0)或いは速度増加(>1.0)。1.0は全セット速度が同じ。
     * @param pFunc_call_back_dispatched 弾がデポジトリから dispach() された時に呼び出すコールバック。
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDx::FigureActor* shotWay001(coord prm_x, coord prm_y, coord prm_z,
                                           angle prm_rz, angle prm_ry,
                                           GgafCore::ActorDepository* prm_pDepo_shot,
                                           coord prm_r,
                                           velo prm_velo_first, acce prm_acce,
                                           int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                           void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int) = nullptr);

    /**
     * 発射元が向いている方向（_rz > _ry）に向かって 単発弾を複数個撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDx::VecVehicle の移動方向、移動速度、加速度<BR>
     * @param prm_from_x          発射元X座標
     * @param prm_from_y          発射元Y座標
     * @param prm_from_z          発射元Z座標
     * @param prm_to_x            目標X座標
     * @param prm_to_y            目標Y座標
     * @param prm_to_z            目標Z座標
     * @param prm_pDepo_shot      発射するショットのデポジトリ
     * @param prm_r               発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_velo_first      初弾のショット初期速度。初弾以降の初期速度は prm_attenuated を乗じていく。
     * @param prm_acce            ショット初期加速度
     * @param prm_set_num         撃つ弾の合計数
     * @param prm_interval_frames 弾と弾の出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全弾一斉発射。）
     * @param prm_attenuated      初弾セット以降のセット毎のショット初期速度へ乗率。速度減衰(< 1.0)或いは速度増加(>1.0)。1.0は全セット速度が同じ。
     * @param pFunc_call_back_dispatched
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDx::FigureActor* shotWay001(coord prm_from_x, coord prm_from_y, coord prm_from_z,
                                           coord prm_to_x, coord prm_to_y, coord prm_to_z,
                                           GgafCore::ActorDepository* prm_pDepo_shot,
                                           coord prm_r,
                                           velo prm_velo_first, acce prm_acce,
                                           int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                           void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int) = nullptr);

    /**
     * 発射元が向いている方向（_rz > _ry）に向かって 単発弾を複数個撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDx::VecVehicle の移動方向、移動速度、加速度<BR>
     * @param prm_pFrom           発射元
     * @param prm_pDepo_shot      発射するショットのデポジトリ
     * @param prm_r               発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_velo_first      初弾のショット初期速度。初弾以降の初期速度は prm_attenuated を乗じていく。
     * @param prm_acce            ショット初期加速度
     * @param prm_set_num         撃つ弾の合計数
     * @param prm_interval_frames 弾と弾の出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全弾一斉発射。）
     * @param prm_attenuated      初弾セット以降のセット毎のショット初期速度へ乗率。速度減衰(< 1.0)或いは速度増加(>1.0)。1.0は全セット速度が同じ。
     * @param pFunc_call_back_dispatched
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDx::FigureActor* shotWay001(const GgafDx::GeometricActor* prm_pFrom,
                                           GgafCore::ActorDepository* prm_pDepo_shot,
                                           coord prm_r,
                                           velo prm_velo_first, acce prm_acce,
                                           int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                           void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int) = nullptr);


    /**
     * N-Way弾（Rz変化）を複数セット撃つ .
     * prm_rx, prm_rz, prm_ry = (0,0,0) で、XY平面上にRz変化の N-Way弾 を放ちます。
     * @param prm_x                発射元X座標
     * @param prm_y                発射元Y座標
     * @param prm_z                発射元Z座標
     * @param prm_rx               N Wayの回転角
     * @param prm_rz               発射方向Rz
     * @param prm_ry               発射方向Ry
     * @param prm_pDepo_shot       発射するショットのデポジトリ
     * @param prm_r                発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_way_N            N-Way数（Rz変化）
     * @param prm_ang_clearance_N  N-Wayの間隔角度
     * @param prm_velo_first       N-Way弾初弾セットのショット初期速度。初弾セット以降の初期速度は prm_attenuated を乗じていく。
     * @param prm_acce             N-Way弾各セットのショット初期加速度
     * @param prm_set_num          発射する N-Way弾セットの合計セット数
     * @param prm_interval_frames  弾セットと弾セットの出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全セット一斉発射。）
     * @param prm_attenuated       初弾セット以降のセット毎のショット初期速度へ乗率。速度減衰(< 1.0)或いは速度増加(>1.0)。1.0は全セット速度が同じ。
     * @param pFunc_call_back_dispatched
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDx::FigureActor* shotWay002(coord prm_x, coord prm_y, coord prm_z,
                                           angle prm_rx, angle prm_rz, angle prm_ry,
                                           GgafCore::ActorDepository* prm_pDepo_shot,
                                           coord prm_r,
                                           int prm_way_N,
                                           angle prm_ang_clearance_N,
                                           velo prm_velo_first, acce prm_acce,
                                           int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                           void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int) = nullptr);

    /**
     * 発射元が向いている方向（_rx, _rz > _ry）N-Way弾（Rz変化）を複数セット撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDx::VecVehicle の移動方向、移動速度、加速度<BR>
     * @param prm_pFrom                  発射元
     * @param prm_pDepo_shot             発射するショットのデポジトリ
     * @param prm_r                      発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_way_N                  N-Way数（Rz変化）
     * @param prm_ang_clearance_N        N-Wayの間隔角度
     * @param prm_velo_first             N-Way弾初弾セットのショット初期速度。初弾セット以降の初期速度は prm_attenuated を乗じていく。
     * @param prm_acce                   N-Way弾各セットのショット初期加速度
     * @param prm_set_num                発射する N-Way弾セットの合計セット数
     * @param prm_interval_frames        弾セットと弾セットの出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全セット一斉発射。）
     * @param prm_attenuated             初弾セット以降のセット毎のショット初期速度へ乗率。速度減衰(< 1.0)或いは速度増加(>1.0)。1.0は全セット速度が同じ。
     * @param pFunc_call_back_dispatched
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDx::FigureActor* shotWay002(const GgafDx::GeometricActor* prm_pFrom,
                                           GgafCore::ActorDepository* prm_pDepo_shot,
                                           coord prm_r,
                                           int prm_way_N,
                                           angle prm_ang_clearance_N,
                                           velo prm_velo_first, acce prm_acce,
                                           int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                           void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int) = nullptr);

    /**
     * N*M-Way弾を複数セット撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDx::VecVehicle の移動方向、移動速度、加速度<BR>
     * @param prm_x                発射元X座標
     * @param prm_y                発射元Y座標
     * @param prm_z                発射元Z座標
     * @param prm_rx               N*M 長方形の回転角
     * @param prm_rz               発射方向Rz
     * @param prm_ry               発射方向Ry
     * @param prm_pDepo_shot1      発射するショットのデポジトリその１
     * @param prm_paUint32_dotmat1 ショットその１を使用するドットマトリックス
     * @param prm_pDepo_shot2      発射するショットのデポジトリその２
     * @param prm_paUint32_dotmat2 ショットその２を使用するドットマトリックス
     * @param prm_pDepo_shot3      発射するショットのデポジトリその３
     * @param prm_paUint32_dotmat3 ショットその３を使用するドットマトリックス
     * @param prm_r                発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_way_N            N-Way数（Rz変化）
     * @param prm_way_M            M-Way数（Ry変化）
     * @param prm_ang_clearance_N   N-Wayの間隔角度
     * @param prm_ang_clearance_M   M-Wayの間隔角度
     * @param prm_velo_first       N*M-Way弾初弾セットのショット初期速度。初弾セット以降の初期速度は prm_attenuated を乗じていく。
     * @param prm_acce             N*M-Way弾各セットのショット初期加速度
     * @param prm_set_num          発射する N*M-Way弾セットの合計セット数
     * @param prm_interval_frames  弾セットと弾セットの出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全セット一斉発射。）
     * @param prm_attenuated       初弾セット以降のセット毎のショット初期速度へ乗率。速度減衰(< 1.0)或いは速度増加(>1.0)。1.0は全セット速度が同じ。
     * @param pFunc_call_back_dispatched
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDx::FigureActor* shotWay003(coord prm_x, coord prm_y, coord prm_z,
                                           angle prm_rx, angle prm_rz, angle prm_ry,
                                           GgafCore::ActorDepository* prm_pDepo_shot1, uint32_t* prm_paUint32_dotmat1,
                                           GgafCore::ActorDepository* prm_pDepo_shot2, uint32_t* prm_paUint32_dotmat2,
                                           GgafCore::ActorDepository* prm_pDepo_shot3, uint32_t* prm_paUint32_dotmat3,
                                           coord prm_r,
                                           int prm_way_N, int prm_way_M,
                                           angle prm_ang_clearance_N, angle prm_ang_clearance_M,
                                           velo prm_velo_first, acce prm_acce,
                                           int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                           void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int, int, int) = nullptr);


    /**
     * 発射元が向いている方向（_rx > _rz > _ry）に向かって N*M-Way弾を複数セット撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDx::VecVehicle の移動方向、移動速度、加速度<BR>
     * @param prm_pFrom            発射元
     * @param prm_pDepo_shot1      発射するショットのデポジトリその１
     * @param prm_paUint32_dotmat1 ショットその１を使用するドットマトリックス
     * @param prm_pDepo_shot2      発射するショットのデポジトリその２
     * @param prm_paUint32_dotmat2 ショットその２を使用するドットマトリックス
     * @param prm_pDepo_shot3      発射するショットのデポジトリその３
     * @param prm_paUint32_dotmat3 ショットその３を使用するドットマトリックス
     * @param prm_r                発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_way_N            N-Way数（Rz変化）
     * @param prm_way_M            M-Way数（Ry変化）
     * @param prm_ang_clearance_N  N-Wayの間隔角度
     * @param prm_ang_clearance_M  M-Wayの間隔角度
     * @param prm_velo_first       N*M-Way弾初弾セットのショット初期速度。初弾セット以降の初期速度は prm_attenuated を乗じていく。
     * @param prm_acce             N*M-Way弾各セットのショット初期加速度
     * @param prm_set_num          発射する N*M-Way弾セットの合計セット数
     * @param prm_interval_frames  弾セットと弾セットの出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全セット一斉発射。）
     * @param prm_attenuated       初弾セット以降のセット毎のショット初期速度へ乗率。速度減衰(< 1.0)或いは速度増加(>1.0)。1.0は全セット速度が同じ。
     * @param pFunc_call_back_dispatched
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDx::FigureActor* shotWay003(const GgafDx::GeometricActor* prm_pFrom,
                                           GgafCore::ActorDepository* prm_pDepo_shot1, uint32_t* prm_paUint32_dotmat1,
                                           GgafCore::ActorDepository* prm_pDepo_shot2, uint32_t* prm_paUint32_dotmat2,
                                           GgafCore::ActorDepository* prm_pDepo_shot3, uint32_t* prm_paUint32_dotmat3,
                                           coord prm_r,
                                           int prm_way_N, int prm_way_M,
                                           angle prm_ang_clearance_N, angle prm_ang_clearance_M,
                                           velo prm_velo_first, acce prm_acce,
                                           int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                           void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int, int, int) = nullptr);

    /**
     * 拡散放射状弾を複数セット同時に撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDx::VecVehicle の移動方向、移動速度、加速度<BR>
     * @param prm_x               発射元X座標
     * @param prm_y               発射元Y座標
     * @param prm_z               発射元Z座標
     * @param prm_rz              発射方向Rz
     * @param prm_ry              発射方向Ry
     * @param prm_pDepo_shot      発射するショットのデポジトリ
     * @param prm_r               発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_radial_way_num  １セット放射状Way数
     * @param prm_expanse_angle   発射方向への放射状弾の照射角(0 ～ D180ANG。懐中電灯の光の広がり角のようなイメージ。小さいと弾の間隔が狭い)
     * @param prm_velo_first      初弾セットのショット初期速度。初弾セット以降の初期速度は prm_attenuated を乗じていく。
     * @param prm_acce            各セットのショット初期加速度
     * @param prm_set_num         撃つ放射状WAY弾の合計セット数
     * @param prm_interval_frames 弾セットと弾セットの出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全セット一斉発射。）
     * @param prm_attenuated      初弾セット以降のセット毎のショット初期速度へ乗率。速度減衰(< 1.0)或いは速度増加(>1.0)。1.0は全セット速度が同じ。
     * @param pFunc_call_back_dispatched デポジトリ(prm_pDepo_shot)から dispatch() されて、
     *                                 移動方向、初期速度、加速度が設定された後にコールバックされる関数を設定。
     *                                 引数には次の値が引き渡される。
     *                                 void f(GgafDx::FigureActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index)
     *                                 prm_pActor         dispatch()された弾のアクター
     *                                 prm_dispatch_num   何回目の dispatch() の弾か  (1～)
     *                                 prm_set_index      放射状WAY弾何セット目であるか (0～)
     *                                 prm_way_index      何WAY目の弾であるか         (0～)
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDx::FigureActor* shotWay004(coord prm_x, coord prm_y, coord prm_z,
                                           angle prm_rz, angle prm_ry,
                                           GgafCore::ActorDepository* prm_pDepo_shot,
                                           coord prm_r,
                                           int prm_radial_way_num, angle prm_expanse_angle,
                                           velo prm_velo_first, acce prm_acce,
                                           int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                           void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int) = nullptr);

    /**
     * 発射元が向いている方向（_rz > _ry）に向かって拡散放射状弾を複数セット同時に撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDx::VecVehicle の移動方向、移動速度、加速度<BR>
     * @param prm_pFrom           発射元
     * @param prm_pDepo_shot      発射するショットのデポジトリ
     * @param prm_r               発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_radial_way_num  １セット放射状Way数
     * @param prm_expanse_angle   発射方向への放射状弾の照射中心角(0 ～ D180ANG。懐中電灯の光の広がりの成す角のようなイメージ。小さいと弾の間隔が狭い)
     * @param prm_velo_first      初弾セットのショット初期速度
     * @param prm_acce            初弾セットのショット初期加速度
     * @param prm_set_num         撃つ放射状WAY弾の合計セット数
     * @param prm_interval_frames 弾セットと弾セットの出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全セット一斉発射。）
     * @param prm_attenuated      初弾セット以降のセット毎のショット初期速度へ乗率。速度減衰(< 1.0)或いは速度増加(>1.0)。1.0は全セット速度が同じ。
     * @param pFunc_call_back_dispatched デポジトリ(prm_pDepo_shot)から dispatch() されて、
     *                                 移動方向、初期速度、加速度が設定された後にコールバックされる関数を設定。
     *                                 引数には次の値が引き渡される。
     *                                 void f(GgafDx::FigureActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index)
     *                                 prm_pActor         dispatch()された弾のアクター
     *                                 prm_dispatch_num   何回目の dispatch() の弾か  (1～)
     *                                 prm_set_index      放射状WAY弾何セット目であるか (0～)
     *                                 prm_way_index      何WAY目の弾であるか         (0～)
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDx::FigureActor* shotWay004(const GgafDx::GeometricActor* prm_pFrom,
                                           GgafCore::ActorDepository* prm_pDepo_shot,
                                           coord prm_r,
                                           int prm_radial_way_num, angle prm_expanse_angle,
                                           velo prm_velo_first, acce prm_acce,
                                           int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                           void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int) = nullptr);


};

}
#endif /*GGAF_LIB_STGUTIL_H_*/



//ピラミッドと球
//  平面 a*x + b*y + c*z + d = 0
//  点D(x0,y0,z0)
//  点から平面に下ろした足の根元を点H(x,y,z) とすると
//
//  ベクトル HD=(x0-x ,y0-y, z0-z) = t(a,b,c)  (tは実数)  ・・・①
//
//  ①より
//  x0 - x = t*a
//  y0 - y = t*b
//  z0 - z = t*c
//  なので
//  x = x0 - t*a
//  y = y0 - t*b
//  z = z0 - t*c
//
//  を平面の式へ代入
//  a*(x0-t*a) + b*(y0-t*b) + c*(z0-t*c) + d = 0
//
//  これをtについて解くと
//  t = (a*x0+b*y0+c*z0+d)/(a^2+b^2+c^2)  ・・・②
//
//  よって
//  x =  x0 - t*a
//    =  x0 - ((a*x0+b*y0+c*z0+d)/(a^2+b^2+c^2))*a
//
//  y = y0 - t*b
//    = y0 - ((a*x0+b*y0+c*z0+d)/(a^2+b^2+c^2))*b
//
//  z = z0 - t*c
//    = z0 - ((a*x0+b*y0+c*z0+d)/(a^2+b^2+c^2))*c
//
//  また、HDの距離は
//  |HD|= |t(a,b,c)| = |t|*|(a,b,c)| = abs(t)*sqrt(a^2+b^2+c^2)  ・・・③
//
//  ②のtを③へ代入
//
//  |HD| = abs((c*z0+b*y0+a*x0+d)/(c^2+b^2+a^2))*sqrt(a^2+b^2+c^2)
//
//  |HD| = abs(a*x0+b*y0+c*z0+d) / sqrt(a^2+b^2+c^2)






//// 特定の点(a,b,c)を通り、方向ベクトルが(p,q,r)の直線は。
//(x,y,z) = (a,b,c) + t(p,q,r)  (tは媒介変数)
//
//x = a + t*p ・・・ ①
//y = b + t*q ・・・ ②
//z = c + t*r ・・・ ③
//
//t = (x-a) /p = (y-b)/q = (z-c)/r
//
//
//点D(x0,y0,z0)
//点から直線に下ろした足の根元を点H(x,y,z) とすると
//ベクトル HD = (x0-x,y0-y, z0-z)
//    = (x0-(a+t*p), y0-(b+t*q), z0-(c+t*r))  ・・・④
//
//これが、(p,q,r) と直交するので、内積=0
//(x0-(a+t*p), y0-(b+t*q), z0-(c+t*r))・(p,q,r) = 0
//p*(x0-(a+t*p)) + q*(y0-(b+t*q)) + r*(z0-(c+t*r)) = 0
//
//tについて解くと
//
//t=(r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2)
//
//④のt に代入し、したがって HD は
//HD = ( x0-(a+( (r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2) )*p),
//y0-(b+( (r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2) )*q),
//z0-(c+( (r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2) )*r)    )
//
//|HD| = sqrt( (x0-(a+( (r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2) )*p))^2 +
//     (y0-(b+( (r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2) )*q))^2 +
//     (z0-(c+( (r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2) )*r))^2   )
//
//|HD| = sqrt((q^2+p^2)*z0^2+(-2*q*r*y0-2*p*r*x0+(2*b*q+2*a*p)*r-2*c*q^2-2*c*p^2)*z0+(r^2+p^2)*y0^2+
//(-2*p*q*x0-2*b*r^2+2*c*q*r+2*a*p*q-2*b*p^2)*y0+(r^2+q^2)*x0^2+(-2*a*r^2+2*c*p*r-2*a*q^2+2*b*p*q)*x0+(b^2+a^2)*r^2+
//(-2*b*c*q-2*a*c*p)*r+(c^2+a^2)*q^2-2*a*b*p*q+(c^2+b^2)*p^2)/(sqrt(r^2+q^2+p^2))





//// 点 A(a,b,c) B(d,e,f) を通る直線は
//AB = (d-a, e-b, f-c)
//(x,y,z) = (a,b,c) + t(d-a, e-b, f-c)  (tは媒介変数)
//
//x = a + t*(d-a) ・・・ ①
//y = b + t*(e-b) ・・・ ②
//z = c + t*(f-c) ・・・ ③
//
//点D(x0,y0,z0)
//点から直線に下ろした足の根元を点H(x,y,z) とすると
//ベクトル HD = (x0-x,y0-y, z0-z)
//            = (x0-(a+t*(d-a)), y0-(b+t*(e-b)), z0-(c+t*(f-c)))  ・・・④
//
//
//これが、AB=(d-a, e-b, f-c) と直交するので、内積=0
//(x0-(a+t*(d-a)), y0-(b+t*(e-b)), z0-(c+t*(f-c)))・(d-a, e-b, f-c) = 0
//なので
//(x0-(a+t*(d-a)))*(d-a) + (y0-(b+t*(e-b)))*(e-b) + (z0-(c+t*(f-c)))*(f-c) = 0
//
//tについて解くと
//
//t = ((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2)
//
//④の t に代入し、したがって HD は
//HD = ( x0-(a+(((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))*(d-a)) ,
//       y0-(b+(((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))*(e-b)) ,
//       z0-(c+(((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))*(f-c))   )
//
//|HD| = sqrt( (x0-(a+(((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))*(d-a)))^2 +
//             (y0-(b+(((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))*(e-b)))^2 +
//             (z0-(c+(((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))*(f-c)))^2    )
//
//=sqrt(((e^2-2*b*e+d^2-2*a*d+b^2+a^2)*z0^2+(((2*b-2*e)*f+2*c*e-2*b*c)*y0+((2*a-2*d)*f+2*c*d-2*a*c)*x0+
//(2*b*e+2*a*d-2*b^2-2*a^2)*f-2*c*e^2+2*b*c*e-2*c*d^2+2*a*c*d)*z0+(f^2-2*c*f+d^2-2*a*d+c^2+a^2)*y0^2+
//(((2*a-2*d)*e+2*b*d-2*a*b)*x0-2*b*f^2+(2*c*e+2*b*c)*f+(2*a*d-2*c^2-2*a^2)*e-2*b*d^2+2*a*b*d)*y0+
//(f^2-2*c*f+e^2-2*b*e+c^2+b^2)*x0^2+(-2*a*f^2+(2*c*d+2*a*c)*f-2*a*e^2+(2*b*d+2*a*b)*e+(-2*c^2-2*b^2)*d)*x0+(b^2+a^2)*
//f^2+(-2*b*c*e-2*a*c*d)*f+(c^2+a^2)*e^2-2*a*b*d*e+(c^2+b^2)*d^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))












//点 A(x1,y2,z1) B(x2,y1,z1) を通る直線と点D(o_scx,o_scy,o_scz)の距離
//
//(x1,y2,z1) (x2,y1,z1)     (o_scx,o_scy,o_scz)
//
//sqrt(((y1^2-2*y2*y1+x2^2-2*x1*x2+y2^2+x1^2)*o_scz^2+(((2*y2-2*y1)*z1+2*z1*y1-2*y2*z1)*o_scy+((2*x1-2*x2)*z1+2*z1*x2-2*x1*z1)*o_scx+
//(2*y2*y1+2*x1*x2-2*y2^2-2*x1^2)*z1-2*z1*y1^2+2*y2*z1*y1-2*z1*x2^2+2*x1*z1*x2)*o_scz+(z1^2-2*z1*z1+x2^2-2*x1*x2+z1^2+x1^2)*o_scy^2+
//(((2*x1-2*x2)*y1+2*y2*x2-2*x1*y2)*o_scx-2*y2*z1^2+(2*z1*y1+2*y2*z1)*z1+(2*x1*x2-2*z1^2-2*x1^2)*y1-2*y2*x2^2+2*x1*y2*x2)*o_scy+
//(z1^2-2*z1*z1+y1^2-2*y2*y1+z1^2+y2^2)*o_scx^2+(-2*x1*z1^2+(2*z1*x2+2*x1*z1)*z1-2*x1*y1^2+(2*y2*x2+2*x1*y2)*y1+(-2*z1^2-2*y2^2)*x2)*o_scx+(y2^2+x1^2)*
//z1^2+(-2*y2*z1*y1-2*x1*z1*x2)*z1+(z1^2+x1^2)*y1^2-2*x1*y2*x2*y1+(z1^2+y2^2)*x2^2)/(z1^2-2*z1*z1+y1^2-2*y2*y1+x2^2-2*x1*x2+z1^2+y2^2+x1^2))
//
//
//sqrt(((y2^2-2*y1*y2+y1^2+x2^2-2*x1*x2+x1^2)*z1^2+(-2*o_scz*y2^2+4*o_scz*y1*y2-2*o_scz*y1^2-2*o_scz*x2^2+4*o_scz*x1*x2-2*o_scz*x1^2)*z1+
//(x2^2-2*o_scx*x2+o_scz^2+o_scx^2)*y2^2+
//(((2*o_scx-2*x1)*x2+2*o_scx*x1-2*o_scz^2-2*o_scx^2)*y1-2*o_scy*x2^2+(2*o_scy*x1+2*o_scx*o_scy)*x2-2*o_scx*o_scy*x1)*y2+
//(x1^2-2*o_scx*x1+o_scz^2+o_scx^2)*y1^2+((2*o_scy*x1-2*o_scx*o_scy)*x2-2*o_scy*x1^2+2*o_scx*o_scy*x1)*y1+(o_scz^2+o_scy^2)*x2^2+(-2*o_scz^2-2*o_scy^2)*x1*
//x2+(o_scz^2+o_scy^2)*x1^2)/(y2^2-2*y1*y2+y1^2+x2^2-2*x1*x2+x1^2))
//
//
//
//
//t=((z1-z1)*z0+(y1-y2)*y0+(x2-x1)*x0-z1*z1-y2*y1-x1*x2+z1^2+y2^2+x1^2)/(z1^2-2*z1*z1+y1^2-2*y2*y1+x2^2-2*x1*x2+z1^2+y2^2+x1^2)
//
//t=(y2^2+(-y1-y0)*y2+y0*y1+(x0-x1)*x2+x1^2-x0*x1)/(y2^2-2*y1*y2+y1^2+x2^2-2*x1*x2+x1^2)
