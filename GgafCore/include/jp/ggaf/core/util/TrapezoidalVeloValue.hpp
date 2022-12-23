#ifndef GGAF_CORE_TRAPEZOIDALVELOVALUE_H_
#define GGAF_CORE_TRAPEZOIDALVELOVALUE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include "jp/ggaf/core/Config.h"
#include "jp/ggaf/core/util/Util.h"

namespace GgafCore {

/**
 * 何かの値の台形駆動速度 .
 * 何かの値を簡易的にヌメっと滑らかに変化させる。
 * @tparam VAL_TYPE 遷移値のデータ型
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
template<class VAL_TYPE>
class TrapezoidalVeloValue : public Object {

private:
    enum {
        TVMOVE_ZERO_END = -9,        /** 距離が 0 の場合のフェーズ定数。                                                     */
        TVMOVE_RECOVERY_BEGIN = 0,   /** 回復フェーズ Ts へ向けての加速度設定                                            */
        TVMOVE_RECOVERING_to_Ts = 1, /** 回復中  ～ Ts                                                                   */
        TVMOVE_on_Ts = 2,            /** Ts～T1 が 0 ならば TVMOVE_T1_to_T2 へ、そうでなければ TVMOVE_acc_for_T1 */
        TVMOVE_acc_for_T1 = 3,       /** T1 へ向けての加速度設定                                                         */
        TVMOVE_Ts_to_T1 = 4,         /** 加速中 Ts～T1 、T1に到達すれば、T2へ向けての等速度設定                          */
        TVMOVE_T1_to_T2 = 5,         /** 等速中 T1～T2 、T2に到達すれば、Teへ向けての減速度設定                          */
        TVMOVE_T2_to_Te = 6,         /** 減速中 T2～Te 、Teに到達すれば終了。あるいは補正で１フレーム追加                */
        TVMOVE_BACCHIRI = 7,         /** 残距離バッチリ合わせ（１フレーム）                                              */
        TVMOVE_DONE = -1,            /** 加速処理が完全に終了した時のフェーズ定数                                            */
    };

    /** [r]なめらか移動シークエンスを実行中はtrue */
    bool _is_accelerating;
    /** [r]なめらか移動シークエンスを実行完了時の加速度設定（true：加速度0に設定／false:加速度をそのままにしておく） */
    bool _zero_acc_end_flg;
    /** [r]なめらか移動シークエンスで設定されたトップスピード（等速移動時速度） */
    VAL_TYPE _top_velo;
    /** [r]なめらか移動シークエンスで設定された終了時の速度 */
    VAL_TYPE _end_velo;
    /** [r]なめらか移動シークエンスで設定された目標位置到達までに必要な実質の移動距離（正のみ。負の移動も加算した場合のいdぽう距離総和） */
    VAL_TYPE _target_distance;
    /** [r]なめらか移動シークエンスで設定された目標位置までの直線距離（正負有り） */
    VAL_TYPE _target_distance2;
    /** [r]なめらか移動シークエンスで今までに実質移動した移動距離合計（今までの移動速度の絶対値の加算合計） */
    VAL_TYPE _moved;
    /** [r]なめらか移動シークエンスで今までの移動距離の和（今までの移動速度（正負そのままの加算合計） */
    VAL_TYPE _moved2;
    /** [r]なめらか移動シークエンスで移動速度正負を反転するまでの設定された回復時加速度 */
    VAL_TYPE _acce_a0;
    /** [r]なめらか移動シークエンスで設定された目標移動方向の正負 */
    int _target_sgn;
    /** [r]なめらか移動シークエンスで設定された目標時間 */
    int  _frame_of_target;
    /** [r]なめらか移動シークエンスに開始から現在までの経過時間 */
    int  _spent_frames;
    /** [r]なめらか移動シークエンスで設定された角速度の正負が切り替わるポイント */
    double  _p0;
    /** [r]なめらか移動シークエンスで設定された加速～等速へ切り替わる位置 */
    double  _p1;
    /** [r]なめらか移動シークエンスで設定された等速～減速へ切り替わる位置 */
    double  _p2;
    /** [r]なめらか移動シークエンスのフェーズ状況 */
    int  _phase_no;

public:
    /** 何かの値 */
    VAL_TYPE _t_value;
    /** 何かの値の速度 */
    VAL_TYPE _t_velo;
    /** 何かの値の加速度 */
    VAL_TYPE _t_acce;

public:
    TrapezoidalVeloValue() {
        _is_accelerating = false;
        _zero_acc_end_flg = true;
        _top_velo = 0;
        _end_velo = 0;
        _target_distance = 0;
        _target_distance2 = 0;
        _moved = 0;
        _moved2 = 0;
        _acce_a0 = 0;
        _target_sgn = 1;
        _frame_of_target = 0;
        _spent_frames = 0;
        _p0 = 0;
        _p1 = 0;
        _p2 = 0;
        _phase_no = TVMOVE_DONE;

        _t_value = 0;
        _t_velo = 0;
        _t_acce = 0;
    }

    void moveByDt(VAL_TYPE prm_target_value_distance,
                  frame prm_frame_of_target,
                  double prm_p1, double prm_p2, VAL_TYPE prm_end_velo,
                  bool prm_zero_acc_end_flg) {
        //目標時間指定の場合
        int s_d = SGN(prm_target_value_distance);
        int sgn_W0 = SGN(_t_velo);
        if (ZEROd_EQ(prm_target_value_distance)) {
            //距離が0なので、_frame_of_target 停止して終了
            _is_accelerating = true;
            _target_distance = 0;
            _target_distance2 = 0;
            _moved = 0;
            _moved2 = 0;
            _target_sgn = s_d;
            _p1 = 0;
            _p2 = 0;
            _top_velo = 0;
            _end_velo = prm_end_velo;
            _frame_of_target = prm_frame_of_target;
            _spent_frames = 0;
            _zero_acc_end_flg = prm_zero_acc_end_flg;
            _phase_no = TVMOVE_ZERO_END; //いきなり終了
            return;
        }
        //_TRACE_(FUNC_NAME<<" COME!");
        //_TRACE_("prm_target_value_distance="<<prm_target_value_distance);
        //_TRACE_("prm_frame_of_target="<<prm_frame_of_target);
        //_TRACE_("prm_p1="<<prm_p1);
        //_TRACE_("prm_p2="<<prm_p2);
        //_TRACE_("prm_end_velo="<<prm_end_velo);
        //_TRACE_("prm_zero_acc_end_flg="<<prm_zero_acc_end_flg);

        if (sgn_W0 == 0 || s_d == sgn_W0) {  //正負が一致
            //＜トップスピード(Vt) を計算＞
            //
            //    速度(v)
            //     ^
            //     |                          D:目標移動距離
            //     |                         V0:現時点の速度
            //     |                         Vt:トップスピード
            //     |                         Ve:最終速度
            //   Vt|....＿＿＿＿＿           Te:目標時間（フレーム数）
            //     |   /:         :＼        p1:トップスピードに達する時刻となるような、Teに対する割合
            //   Ve|../.:.........:..＼      p2:減速を開始時刻となるような、Teに対する割合
            //     | /  :         :    |        (0.0 < p1 < p2 < 1.0)
            //     |/   :         :    |
            //   V0|    :    D    :    |
            //     |    :         :    |
            //   --+----+---------+----+-----> 時間(t:フレーム)
            //   0 |    T1        T2   Te
            //
            // 移動距離Dは、左の台形＋中央の長方形＋右の台形 の面積である、
            // D = (1/2)*(V0+Vt)*T1 + Vt*(T2-T1)  +  (1/2)*(Ve+Vt)*(Te-T2);
            // これをVtについて解く
            // Vt=-(T1*V0-Ve*T2-2*D+Te*Ve)/(T2-T1+Te)
            const double V0 = _t_velo;
            const double Ve = ABS(prm_end_velo) * s_d;
            const double T1 = prm_frame_of_target*prm_p1;
            const double T2 = prm_frame_of_target*prm_p2;
            const double Te = prm_frame_of_target;
            const double D  = prm_target_value_distance;
            const double Vt = -(T1*V0-Ve*T2-2.0*D+Te*Ve)/(T2-T1+Te);

            //_TRACE_("V0="<<V0);
            //_TRACE_("Ve="<<Ve);
            //_TRACE_("T1="<<T1);
            //_TRACE_("T2="<<T2);
            //_TRACE_("Te="<<Te);
            //_TRACE_("D="<<D);
            //_TRACE_("Vt="<<Vt);

            _is_accelerating = true;
            _target_distance = ABS(D);
            _target_distance2 = D;
            _moved = 0;
            _moved2 = 0;
            _target_sgn = s_d;
            _p1 = T1;
            _p2 = T2;
            _top_velo = Vt;
            _end_velo = Ve;
            _frame_of_target = Te;
            _spent_frames = 0;
            _zero_acc_end_flg = prm_zero_acc_end_flg;
            _phase_no = TVMOVE_acc_for_T1;

        } else {
            //        速度(v)
            //         ^
            //         |                                   D2-D1:目標移動距離
            //         |                                      V0:現時点の速度
            //         |                                      Vt:トップスピード
            //         |                                      Ve:最終速度
            //       Vt|................＿＿＿＿＿＿          Te:目標時間（フレーム数）
            //         |               /:  |       :＼        p1:トップスピードに達する時刻となるような、Teに対する割合
            //       Ve|............../.:..|.......:..＼      p2:減速を開始時刻となるような、Teに対する割合
            //         |             /  :  |       :    |        (0.0 < p1 < p2 < 1.0)
            //         |         a  /   :  |       :    |
            //         |           /    s  |  D    :    |
            //         |          /     :  |       :    |
            //       --+---------/------+--+-------+----+-----> 時間(t:フレーム)
            //       0 |        /Ts    T1         T2   Te
            //         |   -s  /
            //         |      /
            //         |     /
            //         |    /
            //         |   /
            //         |  /
            //         | /
            //       V0|/
            //         |
            //
            //    時間 t が 0 ～ T1 時の角速度を w とすると
            //    直線 V = a*t + V0 より
            //    t = T1 の時  V = Vt  であるので
            //    Vt = a*T1 + V0
            //    a = -(V0-Vt)/T1 ・・・(1)
            //
            //    t = Ts の時  V = 0  であるので
            //    0 = a*Ts + V0  ・・・(2)
            //    (1)を(2)へ代入
            //    0 = (-(V0-Vt)/T1)*Ts + V0
            //    Ts = (T1*V0)/(V0-Vt) ・・・(3)
            //
            //    よってsは
            //    s = (1/2)*Ts*-V0
            //    (3)を代入
            //    s = (1/2)*( (T1*V0)/(V0-Vt) )*-V0
            //    s = -(T1*V0^2)/(2*(V0-Vt))  ・・・(4)
            //
            //    Vtを求める
            //    D+s = 左の三角形＋中央の長方形＋右の台形 の面積である、
            //    D+s =  ( (1/2)*(T1-Ts)*Vt )  +  ( (T2-T1) * Vt )  +  ( (1/2)*(Vt+Ve)*(Te-T2) )   ・・・(5)
            //    (3)(4)を(5)へ代入
            //    D+(-(T1*V0^2)/(2*(V0-Vt))) =  ( (1/2)*(T1-((T1*V0)/(V0-Vt)))*Vt )  +  ( (T2-T1) * Vt )  +  ( (1/2)*(Vt+Ve)*(Te-T2) )
            //    Vtについて解く
            //    Vt=-(T1*V0-Ve*T2-2*D+Te*Ve)/(T2-T1+Te)
            const double V0 = _t_velo;
            const double Ve = ABS(prm_end_velo) * s_d;
            const double T1 = prm_frame_of_target*prm_p1;
            const double T2 = prm_frame_of_target*prm_p2;
            const double Te = prm_frame_of_target;
            const double D = prm_target_value_distance;
            const double Vt = -(T1*V0-Ve*T2-2.0*D+Te*Ve)/(T2-T1+Te);
            const double Ts = (T1*V0)/(V0-Vt);
            const double s = (1.0/2.0)*Ts*-V0;

            //_TRACE_("V0="<<V0);
            //_TRACE_("Ve="<<Ve);
            //_TRACE_("T1="<<T1);
            //_TRACE_("T2="<<T2);
            //_TRACE_("Te="<<Te);
            //_TRACE_("D="<<D);
            //_TRACE_("Vt="<<Vt);
            //_TRACE_("Ts="<<Ts);
            //_TRACE_("s="<<s);
            _is_accelerating = true;
            _p0 = Ts;
            _p1 = T1;
            _p2 = T2;
            _target_distance = ABS(s)+ ABS(s) + ABS(D);
            _target_distance2 = D;
            _target_sgn = s_d;
            _moved = 0;
            _moved2 = 0;
            _top_velo = Vt;
            _end_velo = Ve;
            _frame_of_target = Te;
            _spent_frames = 0;
            _zero_acc_end_flg = prm_zero_acc_end_flg;
            _phase_no = TVMOVE_acc_for_T1;
        }


        //_TRACE_("_is_accelerating ="<<_is_accelerating);
        //_TRACE_("_p0 ="<<_p0);
        //_TRACE_("_p1 ="<<_p1);
        //_TRACE_("_p2 ="<<_p2);
        //_TRACE_("_target_distance ="<<_target_distance);
        //_TRACE_("_target_distance2 ="<<_target_distance2);
        //_TRACE_("_target_sgn ="<<_target_sgn);
        //_TRACE_("_moved ="<<_moved);
        //_TRACE_("_moved2 ="<<_moved2);
        //_TRACE_("_top_velo ="<<_top_velo);
        //_TRACE_("_end_velo ="<<_end_velo);
        //_TRACE_("_frame_of_target ="<<_frame_of_target);
        //_TRACE_("_spent_frames ="<<_spent_frames);
        //_TRACE_("_phase_no ="<<_phase_no);
    }

    void moveByVd(VAL_TYPE prm_top_velo,
                  VAL_TYPE prm_target_value_distance,
                  double prm_p1, double prm_p2, VAL_TYPE prm_end_velo,
                  bool prm_zero_acc_end_flg) {
        //目標TOPスピード指定の場合
        //_TRACE_("prm_target_value_distance="<<prm_target_value_distance<<" _t_velo="<<_t_velo);
        int s_d = SGN(prm_target_value_distance);
        int sgn_W0 = SGN(_t_velo);
        if (ZEROd_EQ(prm_target_value_distance)) {
            //距離が0なので即刻終了
            _is_accelerating = true;
            _top_velo = 0;
            _end_velo = prm_end_velo;
            _target_distance = 0;
            _target_distance2 = 0;
            _moved = 0;
            _moved2 = 0;
            _target_sgn = s_d;
            _frame_of_target = -1; //時間未使用
            _spent_frames = 0;
            _p0 = 0;
            _p1 = 0;
            _p2 = 0;
            _zero_acc_end_flg = prm_zero_acc_end_flg;
            _phase_no = TVMOVE_ZERO_END; //いきなりおしまい
            return;
        }
        //_TRACE_("s_d="<<s_d<<" sgn_W0="<<sgn_W0);
        if (sgn_W0 == 0 || s_d == sgn_W0) {  //正負が一致
            //
            //        角速度(V)                        V0:現時点の速度     (_velo_mv)
            //         ^                               Vt:トップスピード   (prm_top_angvelo)
            //         |                               Ve:最終速度         (prm_end_angvelo)
            //         |                                D:目標回転距離角D  (D1+D2+D3)                     ・・・ 計算して求める
            //         |                               p1:トップスピードに達する角距離となるような、角距離(D)に対する割合
            //         |       D=D1+D2+D3                   つまり    D1 = D*p1 となるような p1 (0.0～1.0)
            //       Vt|....___________                p2:減速を開始距離となるような、距離(D)に対する割合
            //         |   /|         |＼                   つまり D1+D2 = D*p2 となるような p2 (0.0～1.0)
            //       Ve|../.|.........|..＼            T1: D1    = D*p1 に費やされる必要時間フレーム数     ・・・ 計算して求める
            //         | /  |         |    |           T2: D1+D2 = D*p2 に費やされる必要時間フレーム数     ・・・ 計算して求める
            //         |/   |         |    |           Te:費やされる必要時間フレーム数                     ・・・ 計算して求める
            //       V0| D1 |    D2   | D3 |
            //         |    |         |    |
            //       --+----+---------+----+-----> 時間(t:フレーム)
            //       0 |    T1        T2   Te
            const double V0 = _t_velo;
            const double Vt = ABS(prm_top_velo) * s_d;
            const double Ve = ABS(prm_end_velo) * s_d;
            //_TRACE_("V0 = "<<V0);
            //_TRACE_("Vt = "<<Vt);
            //_TRACE_("Ve = "<<Ve);
            _is_accelerating = true;
            _top_velo = Vt;
            _end_velo = Ve;
            _target_distance = ABS(prm_target_value_distance);
            _target_distance2 = prm_target_value_distance;
            _moved = 0;
            _moved2 = 0;
            _target_sgn = s_d;
            _frame_of_target = -1; //時間未使用
            _spent_frames = 0;
            _p0 = 0; //未使用
            _p1 = ABS(_target_distance) * prm_p1;
            _p2 = ABS(_target_distance) * prm_p2;
            _zero_acc_end_flg = prm_zero_acc_end_flg;
            _phase_no = TVMOVE_on_Ts; //回復フェーズを飛ばす
        } else {
            //                                                       V0:現時点の速度      (_velo_mv)
            //        速度(v)                                        Vt:トップスピード    (prm_top_angvelo)
            //        ^                                              Ve:最終速度          (prm_end_angvelo)
            //        |                                               D:スタート時点の角度からの目標回転距離角                     ・・・ 計算して求める
            //        |                                              Dp:角速度０になってからの目標回転距離角(Dp1 + Dp2 + Dp3)   ・・・ 計算して求める
            //        |                                               s:角速度０になるまでの逆回転距離                             ・・・ 計算して求める
            //        |                                              p1:トップスピードに達する角距離となるような、角距離(D)に対する割合
            //        |           D  = (Dp1-s) + Dp2 + Dp3                 つまり Dp1 = Dp*p1 となるような p1 (0.0～1.0)    引数
            //        |           Dp = Dp1 + Dp2 + Dp3               p2:減速を開始距離となるような、距離(D)に対する割合
            //      Vt|...............___________                          つまり Dp1+Dp2 = Dp*p2 となるような p2 (0.0～1.0)  引数
            //        |            A /|         |＼B                 T0: 角速度０になるまでに費やされる必要時間フレーム数  ・・・ 計算して求める
            //        |             / |         |  ＼                T1: Dp1     = Dp*p1 に費やされる必要時間フレーム数  ・・・ 計算して求める
            //        |            /  |         |    ＼              T2: Dp1+Dp2 = Dp*p2 に費やされる必要時間フレーム数  ・・・ 計算して求める
            //        |           /   |         |      ＼            Te:費やされる必要時間フレーム数                        ・・・ 計算して求める
            //        |          / Dp1|    Dp2  |  Dp3   ＼
            //        |         /:    |         |          ＼
            //      Ve|......../.:....|.........|............＼  C
            //        |       /  :    |         |             |
            //        |      / s :    |         |             |
            //   -----+-----+----+----+---------+-------------+----------> 時間(t:フレーム)
            //      0 | s／ Ts       T1        T2            Te
            //        |／
            //      V0| ^    <-s-><------------D-------------->
            //        | |
            //        | |    <---------------Dp--------------->
            //        | |
            //        | |    <---Dp1--><---Dp2--><-----Dp3---->
            //        | |
            //        | 初期回復角加速度(a0)固定
            //
            //        時間 t が 0 ～ Ts 時の角速度を V とすると
            //        直線 V = a0*t + V0 より    (※初期回復角加速度(a0)は定数)
            //        t = Ts の時  V = 0  であるので
            //        0 = a0*Ts + V0
            //        Ts = -V0/a0  ・・・(1)
            //        また
            //        s = (1/2) * Ts * -V0       (∵三角形の面積)
            //        これに(1)を代入
            //        s = (1/2) * (-V0/a0) * -V0
            //        s = V0^2/(2*a0)  ・・・(2)
            //        また
            //
            //        D + s =  Dp = (Dp1 + Dp2 + Dp3) ・・・(3)
            //        より
            //        Dp = D + (V0^2/(2*a0))  ・・・(4)
            const double V0 = _t_velo;
            const double Vt = ABS(prm_top_velo) * s_d;
            const double Ve = ABS(prm_end_velo) * s_d;
            const double a0 = ABS(prm_top_velo)*0.05 * -sgn_W0;
            const double s  = (V0*V0)/(2.0*a0);
            const double Dp = s + prm_target_value_distance;
            //_TRACE_("V0 = "<<V0);
            //_TRACE_("Vt = "<<Vt);
            //_TRACE_("Ve = "<<Ve);
            //_TRACE_("a0 = "<<a0);
            //_TRACE_("s  = "<<s );
            //_TRACE_("Dp = "<<Dp);

            _is_accelerating = true;
            _top_velo = Vt;
            _end_velo = Ve;
            _target_distance = ABS(s) + ABS(Dp);
            _target_distance2 = prm_target_value_distance;
            _moved = 0;
            _moved2 = 0;
            _acce_a0 = a0;
            _target_sgn = s_d;
            _frame_of_target = -1; //時間未使用
            _spent_frames = 0;
            _p0 = ABS(s);
            _p1 = prm_p1;
            _p2 = prm_p2;
            _zero_acc_end_flg = prm_zero_acc_end_flg;
            _phase_no = TVMOVE_RECOVERY_BEGIN; //回復フェーズから
        }

        //_TRACE_("_is_accelerating ="<<_is_accelerating);
        //_TRACE_("_p0 ="<<_p0);
        //_TRACE_("_p1 ="<<_p1);
        //_TRACE_("_p2 ="<<_p2);
        //_TRACE_("_target_distance ="<<_target_distance);
        //_TRACE_("_target_distance2 ="<<_target_distance2);
        //_TRACE_("_target_sgn ="<<_target_sgn);
        //_TRACE_("_moved ="<<_moved);
        //_TRACE_("_moved2 ="<<_moved2);
        //_TRACE_("_top_velo ="<<_top_velo);
        //_TRACE_("_end_velo ="<<_end_velo);
        //_TRACE_("_frame_of_target ="<<_frame_of_target);
        //_TRACE_("_spent_frames ="<<_spent_frames);
        //_TRACE_("_phase_no ="<<_phase_no);
    }

    /**
     * 現在加速処理中であるか否か .
     * @return true:加速処理中/false:停止中
     */
    inline bool isTransitioning() const {
        return _phase_no == TVMOVE_DONE ? false : true;
    }

    /**
     * 丁度加速処理が完了したかどうか調べる .
     * 速処理が完了した時のみ true となる。
     * その後の behave() で false となる。
     * @return true:丁度加速処理が完了/false:現在加速処理中か、或いは以前から停止中
     */
    inline bool hasJustFinishedTransitioning() {
        if (_phase_no != TVMOVE_DONE && _is_accelerating == false) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * 加速処理中を強制終了 .
     */
    inline void stopTransitioning() {
        _is_accelerating = false;
    }

    void behave() {
        //なめらか移動シークエンス起動時
        if (_is_accelerating) {
            //_TRACE_(_frame_of_target<<":_phase_no="<<_phase_no);
            //_TRACE_(_frame_of_target<<":before _t_value="<<_t_value<<" _t_velo="<<_t_velo<<" _t_acce="<<_t_acce<<" _moved="<<_moved<<" _moved2="<<_moved2<<"");
            if (_phase_no == TVMOVE_ZERO_END) {
                //いきなり終了時の処理（距離が０、或いは、時間が０）
                _t_velo = (VAL_TYPE)0.0; //停止
                _t_acce = (VAL_TYPE)0.0;
                if (_frame_of_target < 0) {
                    _t_velo = _end_velo;
                    _t_acce = (VAL_TYPE)0.0; //_zero_acc_end_flg 関係なし
                    _is_accelerating = false; //おしまい
                } else {
                    //目標距離指定の場合
                    if (_spent_frames >= _frame_of_target) { //時間まで何もせずに粘る
                        _t_velo = _end_velo;
                        _t_acce = (VAL_TYPE)0.0; //_zero_acc_end_flg 関係なし
                        _is_accelerating = false; //おしまい
                    }
                }

            } else {

                if (_frame_of_target < 0) {
                    //目標TOPスピード指定の場合
                    if (_phase_no == TVMOVE_RECOVERY_BEGIN) {
                        //回復フェーズ
                        _t_acce = _acce_a0;
                        _phase_no = TVMOVE_RECOVERING_to_Ts;
                    }
                    if (_phase_no == TVMOVE_RECOVERING_to_Ts) {
                        //回復中
                        if (_moved >= _p0) {
                            //加速設定
                            _t_acce = (VAL_TYPE)0.0;
                            _t_velo = (VAL_TYPE)0.0;
                            //再設定
                            _target_distance = _target_distance - _moved;
                            _moved = (VAL_TYPE)0.0;
                            _p1 = _target_distance * _p1;
                            _p2 = _target_distance * _p2;
                            _phase_no = TVMOVE_on_Ts;
                        }
                    }
                    if (_phase_no == TVMOVE_on_Ts) {
                        if (!ZEROd_EQ(_p1)) {
                            _t_acce = (VAL_TYPE)(UTIL::getAcceByVd(_t_velo, _top_velo, _p1*_target_sgn));
                            VAL_TYPE a = ABS(_t_acce);
                            if (a > ABS(_target_distance2)) {
                                _t_acce = _target_distance2;
                            } else if (a > ABS(_top_velo)) {
                                _t_acce = _top_velo;
                            }
                            _phase_no = TVMOVE_acc_for_T1; //T1 へ向けての加速度設定
                        } else {
                            _t_acce = (VAL_TYPE)0.0;
                            _t_velo = _top_velo;
                            _phase_no = TVMOVE_T1_to_T2; //加速スキップ
                        }
                    }
                    if (_phase_no == TVMOVE_acc_for_T1) {
                        //加速中
                        if (_moved >= _p1) {
                            //p1 に到達すれば 等速へ
                            _t_acce = (VAL_TYPE)0.0;
                            _t_velo = _top_velo;
                            const VAL_TYPE diff_to_end = _target_distance2 - _moved2;
                            if (ABS(_t_velo) > ABS(diff_to_end)) {
                                _t_velo = diff_to_end;
                            }
                            _phase_no = TVMOVE_T1_to_T2;
                        }
                    }
                    if (_phase_no == TVMOVE_T1_to_T2) {
                        //_TRACE_("等速中");
                        //等速中
                        if (_moved >= _p2) {
                            //p2 に到達すれば 次回フレームから減速へ
                            //_TRACE_("p2 に到達すれば 次回フレームから減速へ");
                            const VAL_TYPE diff_to_end = _target_distance2 - _moved2;
                            if (!ZEROd_EQ(diff_to_end)) {
                                //_TRACE_("diff_to_end="<<diff_to_end<<" 減速加速度を求めれる");
                                _t_acce = (VAL_TYPE)(UTIL::getAcceByVd(_t_velo, _end_velo, diff_to_end));
                                //_TRACE_("減速加速度 _t_acce="<<acc<<" ????");
                                if (ABS(_t_velo)+ABS(_t_acce) > ABS(diff_to_end)) {
                                    _t_acce = diff_to_end-_t_velo;
                                }
                                //_TRACE_("減速加速度 補正 _t_acce="<<acc<<" ????");
                            }
                            _phase_no = TVMOVE_T2_to_Te;
                        }
                    }
                    if (_phase_no == TVMOVE_T2_to_Te) {
                         //_TRACE_("減速中");
                        //減速中
                        const VAL_TYPE diff_to_end = _target_distance2 - _moved2;
                        //Te=(2*D)/(V0+Vt)

                        //double t = (2.0*diff_to_end)/(_t_velo+_end_velo); //残フレーム数    //＃＃ここもコメント
                        //_TRACE_("double t = (2.0*diff_to_end)/(_t_velo+_end_velo); //残フレーム数");
                        //_TRACE_("double t = (2.0*"<<diff_to_end<<")/("<<_t_velo<<"+"<<_end_velo<<"); //残フレーム数");
                        //_TRACE_("double t = ("<<2.0*diff_to_end<<")/("<<_t_velo+_end_velo<<"); //残フレーム数");
                        //_TRACE_("残フレーム t="<<t<<" ？");
                        //_TRACE_("ABS(_t_velo) < 2.0*ABS(_t_acce) = "<<ABS(_t_velo)<<" < "<<2.0*ABS(_t_acce));
                        if (ABS(_t_velo) < 2.0*ABS(_t_acce)) {
                            //_TRACE_("補正しない （_veloがあまりにも小さいため、t が爆発する。無限小の加速度が設定されてしまうため）");
                            //t = 1;
                            //補正しない(_veloがあまりにも小さいため、t が爆発する)
                        } else {
                            if ((_spent_frames & 1) == 0) { //2回に1回
        //                      if (t > 3 && ABS(diff_to_end) > ABS(_top_velo)*0.0001 && _spent_frames % 4U == 0) {
                                //_TRACE_("t="<<t<<" が爆発してないので、補正・補正・補正");
                                //補正・補正・補正
                                if (!ZEROd_EQ(diff_to_end)) {
                                    _t_acce = (VAL_TYPE)(UTIL::getAcceByVd(_t_velo, _end_velo, diff_to_end));
                                    //_TRACE_("減速加速度再設定 _t_acce="<<acc<<" ????");
                                    if (ABS(_t_velo)+ABS(_t_acce) > ABS(diff_to_end)) {
                                        _t_acce = diff_to_end-_t_velo;
                                    }
                                    //_TRACE_("減速加速度再設定 補正 _t_acce="<<acc<<" ????");
                                }
                            }
                        }
                        const VAL_TYPE end_velo = _end_velo;

                        if ( ZEROd_EQ(diff_to_end)  ||
                             ABS(diff_to_end) <=  ABS(_top_velo)*0.0001 ||
                             (ZEROd_EQ(_top_velo)  || (_top_velo > 0 && diff_to_end <= 0) || (_top_velo < 0  && diff_to_end >= 0) ) || //通り越したか
                             (ZEROd_EQ(_t_velo+end_velo)  || (_t_velo+end_velo > 0 && _t_velo+end_velo+_t_acce < 0 ) || (_t_velo+end_velo <  0 && _t_velo+end_velo+_t_acce > 0) ) //届かず反転したか
                        ) {
                            //目標距離へ到達
                            //_TRACE_("目標距離へ到達");
                            //_TRACE_("ABS(_target_distance2 - _moved2) <=  ABS(_top_velo)*0.00001");
                            //_TRACE_(""<<ABS(_target_distance2 - _moved2)<<" <= "<<ABS(_top_velo)*0.00001<<" ??");
                            //_TRACE_("(ZEROd_EQ(_top_velo)  || (_top_velo > 0  && diff_to_end <= 0) || (_top_velo < 0  && diff_to_end >= 0) ) || //通り越したか");
                            //_TRACE_("_top_velo="<<_top_velo<<" diff_to_end="<<diff_to_end<<"");
                            //_TRACE_("(ZEROd_EQ(_t_velo+end_velo)  || (_t_velo+end_velo  >  0 && _t_velo +end_velo + _t_acce < 0 ) || (_t_velo+end_velo  <  0 && _t_velo +end_velo+_t_acce > 0) ) //届かず反転したか");
                            //_TRACE_("_t_velo="<<_t_velo<<" end_velo="<<end_velo<<" _t_velo+end_velo="<<_t_velo+end_velo<<" _t_acce="<<_t_acce<<" _t_velo +end_velo+_t_acce="<<_t_velo +end_velo + _t_acce <<"");
                            //_TRACE_("おしまいな雰囲気");
                            _t_velo = _end_velo;
                            if (_zero_acc_end_flg) {
                                _t_acce = (VAL_TYPE)0.0;
                            }
                            if (ZEROd_EQ(end_velo)) {
                                //最終速度が0の場合、バッチリ合わせを試みる。
                                if (ZEROd_EQ(diff_to_end)) {
                                    //既にバッチリあっていました
                                    //_TRACE_("既にバッチリあっていました");
                                    //_TRACE_("おしまい11早！!!");
                                    _t_velo = (VAL_TYPE)0.0;
                                    _is_accelerating = false; //おしまい
                                } else {
                                    //ずれてるのでもう１フレーム頑張ってバッチリ合わせる
                                    _t_velo = diff_to_end;   //バッチリ合わせる
                                    //_TRACE_("バッチリ合わせたったよ_velo="<<_target_distance2<<"-"<<_moved2<<"="<<_t_velo);
                                    _phase_no = TVMOVE_BACCHIRI; //もう１フレーム
                                }
                            } else {
                                //最終速度が0ではない。そのまま終了
                                //_TRACE_("おしまい22");
                                _is_accelerating = false; //おしまい
                            }
                        }
                    } else if (_phase_no == TVMOVE_BACCHIRI) {
                        //_TRACE_("よしバッチリ合わせておしまい");
                        _t_velo = (VAL_TYPE)0.0;
                        _is_accelerating = false; //おしまい
                    }
                } else {
                    //目標時間指定の場合
                    if (_phase_no == TVMOVE_acc_for_T1) {
                        if (ZEROd_EQ(_p1)) {
                            _t_acce = 0;
                        } else {
                            //加速設定
                            _t_acce = (VAL_TYPE)(UTIL::getAcceByTv(_p1, _t_velo, _top_velo));
                        }
                        _phase_no = TVMOVE_Ts_to_T1;
                    }
                    if (_phase_no == TVMOVE_Ts_to_T1) {
                        //加速中
                        if (_spent_frames >= (int)(_p1)) {
                            //p1 に到達すれば 等速へ
                            _t_acce = (VAL_TYPE)0.0;
                            _t_velo = _top_velo;
                            _phase_no = TVMOVE_T1_to_T2;
                        }
                    }
                    if (_phase_no == TVMOVE_T1_to_T2) {
                        //_TRACE_("等速中 _spent_frames="<<_spent_frames<<" _p2="<<_p2);
                        //等速中
                        if (_spent_frames >= (int)(_p2)) {
                            //_TRACE_("p2 に到達すれば 次回フレームから減速へ _spent_frames="<<_spent_frames<<" _p2="<<_p2);
                            //p2 に到達すれば 次回フレームから減速へ
                            const double Ve = _end_velo;
                            const double Te = _frame_of_target - _spent_frames;
                            if (Te > 0) {
                                //減速設定
                                _t_acce = (VAL_TYPE)(UTIL::getAcceByTv(Te, _t_velo, Ve));
                                //_TRACE_("減速加速度 _t_acce="<<_t_acce);
                            } else {
                                _t_acce = (VAL_TYPE)0.0;
                            }
                            _phase_no = TVMOVE_T2_to_Te;
                        }
                    }
                    if (_phase_no == TVMOVE_T2_to_Te) {
                        //減速中
                        //_TRACE_("減速中");
                        if ((_spent_frames & 1) == 0) { //2回に1回
                            //_TRACE_("補正・補正・補正");
                            //補正・補正・補正
                            //最後の台形補正
                            //D = (1/2)*(V+Ve)*Te
                            const double Ve = _end_velo;
                            const double Te = _frame_of_target - _spent_frames;
                            //_TRACE_("Ve = "<<Ve);
                            //_TRACE_("Te = "<<Te);
                            if (Te > 0) {
                                const double D = _target_distance2 - _moved2;
                                const double V = (2.0*D-Te*Ve)/Te;
                                //_TRACE_("D = "<<D);
                                //_TRACE_("V = "<<V);
                                _t_velo = (VAL_TYPE)V;
                                //_TRACE_("速度 _t_velo = "<<_t_velo<<" に補正");
                                _t_acce = (VAL_TYPE)(UTIL::getAcceByTv(Te, _t_velo, Ve));
                                //_TRACE_("加速度 _t_acce = "<<_t_acce<<" に補正");
                            }
                        }
                        //_TRACE_("_spent_frames="<<_spent_frames<< " _frame_of_target="<<_frame_of_target);
                        if (_spent_frames >= _frame_of_target) {
                            //_TRACE_("_spent_frames >= _frame_of_target 成立、おしまいな雰囲気");
                            _t_velo = _end_velo;
                            if (_zero_acc_end_flg) {
                                _t_acce = (VAL_TYPE)0.0;
                            }
                            if (ZEROd_EQ(_end_velo)) {
                                //最終速度が0の場合、バッチリ合わせを試みる。
                                if (ZEROd_EQ(_target_distance2 - _moved2)) {
                                    //既にバッチリあっていました
                                    //_TRACE_("既にバッチリあっていました");
                                    //_TRACE_("おしまい1早！");
                                    _t_velo = (VAL_TYPE)0.0;
                                    _is_accelerating = false; //おしまい
                                } else {
                                    //ずれてる。バッチリ合わせるため、もう１フレーム
                                    _t_velo = (_target_distance2 - _moved2); //次はバッチリ0になる
                                    //_TRACE_("バッチリ合わせたったよ_velo="<<_target_distance2<<"-"<<_moved2<<"="<<_t_velo);
                                    _phase_no = TVMOVE_BACCHIRI;
                                }
                            } else {
                                //最終速度が0ではない。そのまま終了
                                //_TRACE_("おしまい2");
                                _is_accelerating = false; //おしまい
                            }
                        }
                    } else if (_phase_no == TVMOVE_BACCHIRI) {
                        //_TRACE_("バッチリ合わせておしまい");
                        _t_velo = (VAL_TYPE)0.0;
                        _is_accelerating = false; //おしまい
                    }
                }
            }

            _t_velo += _t_acce;
            _t_value += _t_velo;

            _moved += ABS(_t_velo);
            _moved2 += _t_velo;

            //_TRACE_(_frame_of_target<<":after _t_value="<<_t_value<<" _t_velo="<<_t_velo<<" _t_acce="<<_t_acce<<" _moved="<<_moved<<" _moved2="<<_moved2<<"");
            ++_spent_frames;
        } else {
            _phase_no = TVMOVE_DONE;
        }
#ifdef MY_DEBUG
        if (_spent_frames > SEC_F(60*60)) {
            throwCriticalException("1時間以上滑りっぱなしなんですが！");
        }
#endif
    }

    virtual ~TrapezoidalVeloValue() {
    }
};

}
#endif /*GGAF_CORE_TRAPEZOIDALVELOVALUE_H_*/

