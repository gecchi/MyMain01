#ifndef GGAFCORE_GGAFVALUEACCELERATOR_H_
#define GGAFCORE_GGAFVALUEACCELERATOR_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include "jp/ggaf/core/util/GgafUtil.h"

namespace GgafCore {

/**
 * 値の加速器 .
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
template<class VAL_TYPE>
class GgafValueAccelerator : public GgafObject {
public:


    class SmoothPrm {
     public:
         /** [r]なめらか移動シークエンスを実行中はtrue */
         bool _flg;
         /** [r]なめらか移動シークエンスを実行完了時の加速度設定（true：加速度0に設定／false:加速度をそのままにしておく） */
         bool _endacc_flg;
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
         int  _target_frames;
         /** [r]なめらか移動シークエンスに開始から現在までの経過時間 */
         int  _frame_of_spent;
         /** [r]なめらか移動シークエンスで設定された角速度の正負が切り替わるポイント */
         double  _p0;
         /** [r]なめらか移動シークエンスで設定された加速～等速へ切り替わる位置 */
         double  _p1;
         /** [r]なめらか移動シークエンスで設定された等速～減速へ切り替わる位置 */
         double  _p2;
         /** [r]なめらか移動シークエンスの進捗状況 */
         int  _progress;
     public:
         SmoothPrm() {
             _flg = false;
             _endacc_flg = true;
             _top_velo = 0;
             _end_velo = 0;
             _target_distance = 0;
             _target_distance2 = 0;
             _moved = 0;
             _moved2 = 0;
             _acce_a0 = 0;
             _target_sgn = 1;
             _target_frames = 0;
             _frame_of_spent = 0;
             _p0 = 0;
             _p1 = 0;
             _p2 = 0;
             _progress = -1;
         }
    };
    VAL_TYPE _value;
    VAL_TYPE _velo;
    VAL_TYPE _acce;
    SmoothPrm _prm;
public:
    GgafValueAccelerator() {
        _value = 0;
        _velo = 0;
        _acce = 0;
    }

    void accelerateByDt(VAL_TYPE prm_target_value_distance,
                        frame prm_target_frames,
                        double prm_p1, double prm_p2, VAL_TYPE prm_end_velo,
                        bool prm_endacc_flg) {
        int s_d = SGN(prm_target_value_distance);
        int sgn_W0 = SGN(_velo);
        if (ZEROd_EQ(prm_target_value_distance)) {
            //距離が0なので即刻終了
            _velo = ABS(prm_end_velo) * s_d;
            if (prm_endacc_flg) {
                _acce = (VAL_TYPE)0.0;
            }
            _prm._progress = -9;
            _prm._endacc_flg = false;
            return;
        }
        //_TRACE_("GgafValueAccelerator::accelerateByDt COME!");
        //_TRACE_("prm_target_value_distance="<<prm_target_value_distance);
        //_TRACE_("prm_target_frames="<<prm_target_frames);
        //_TRACE_("prm_p1="<<prm_p1);
        //_TRACE_("prm_p2="<<prm_p2);
        //_TRACE_("prm_end_velo="<<prm_end_velo);
        //_TRACE_("prm_endacc_flg="<<prm_endacc_flg);

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
            double V0 = _velo;
            double Ve = ABS(prm_end_velo) * s_d;
            double T1 = prm_target_frames*prm_p1;
            double T2 = prm_target_frames*prm_p2;
            double Te = prm_target_frames;
            double D  = prm_target_value_distance;
            double Vt = -(T1*V0-Ve*T2-2.0*D+Te*Ve)/(T2-T1+Te);


            //_TRACE_("V0="<<V0);
            //_TRACE_("Ve="<<Ve);
            //_TRACE_("T1="<<T1);
            //_TRACE_("T2="<<T2);
            //_TRACE_("Te="<<Te);
            //_TRACE_("D="<<D);
            //_TRACE_("Vt="<<Vt);

            _prm._flg = true;
            _prm._target_distance = ABS(D);
            _prm._target_distance2 = D;
            _prm._moved = 0;
            _prm._moved2 = 0;
            _prm._target_sgn = s_d;
            _prm._p1 = T1;
            _prm._p2 = T2;
            _prm._top_velo = Vt;
            _prm._end_velo = Ve;
            _prm._target_frames = Te;
            _prm._frame_of_spent = 0;
            _prm._endacc_flg = prm_endacc_flg;
            _prm._progress = 0;


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
            double V0 = _velo;
            double Ve = ABS(prm_end_velo) * s_d;
            double T1 = prm_target_frames*prm_p1;
            double T2 = prm_target_frames*prm_p2;
            double Te = prm_target_frames;
            double D = prm_target_value_distance;
            double Vt = -(T1*V0-Ve*T2-2.0*D+Te*Ve)/(T2-T1+Te);
            double Ts = (T1*V0)/(V0-Vt);
            double s = (1.0/2.0)*Ts*-V0;

            //_TRACE_("V0="<<V0);
            //_TRACE_("Ve="<<Ve);
            //_TRACE_("T1="<<T1);
            //_TRACE_("T2="<<T2);
            //_TRACE_("Te="<<Te);
            //_TRACE_("D="<<D);
            //_TRACE_("Vt="<<Vt);
            //_TRACE_("Ts="<<Ts);
            //_TRACE_("s="<<s);
            _prm._flg = true;
            _prm._p0 = Ts;
            _prm._p1 = T1;
            _prm._p2 = T2;
            _prm._target_distance = ABS(s)+ ABS(s) + ABS(D);
            _prm._target_distance2 = D;
            _prm._target_sgn = s_d;
            _prm._moved = 0;
            _prm._moved2 = 0;
            _prm._top_velo = Vt;
            _prm._end_velo = Ve;
            _prm._target_frames = Te;
            _prm._frame_of_spent = 0;
            _prm._endacc_flg = prm_endacc_flg;
            _prm._progress = 0;
        }


        //_TRACE_("_prm._flg ="<<_prm._flg);
        //_TRACE_("_prm._p0 ="<<_prm._p0);
        //_TRACE_("_prm._p1 ="<<_prm._p1);
        //_TRACE_("_prm._p2 ="<<_prm._p2);
        //_TRACE_("_prm._target_distance ="<<_prm._target_distance);
        //_TRACE_("_prm._target_distance2 ="<<_prm._target_distance2);
        //_TRACE_("_prm._target_sgn ="<<_prm._target_sgn);
        //_TRACE_("_prm._moved ="<<_prm._moved);
        //_TRACE_("_prm._moved2 ="<<_prm._moved2);
        //_TRACE_("_prm._top_velo ="<<_prm._top_velo);
        //_TRACE_("_prm._end_velo ="<<_prm._end_velo);
        //_TRACE_("_prm._target_frames ="<<_prm._target_frames);
        //_TRACE_("_prm._frame_of_spent ="<<_prm._frame_of_spent);
        //_TRACE_("_prm._progress ="<<_prm._progress);

    }

    void accelerateByVd(VAL_TYPE prm_top_velo,
                        VAL_TYPE prm_target_value_distance,
                        double prm_p1, double prm_p2, VAL_TYPE prm_end_velo,
                        bool prm_endacc_flg) {
        //_TRACE_("prm_target_value_distance="<<prm_target_value_distance<<" _velo="<<_velo);
        int s_d = SGN(prm_target_value_distance);
        int sgn_W0 = SGN(_velo);
        if (ZEROd_EQ(prm_target_value_distance)) {
            //距離が0なので即刻終了
            _velo = ABS(prm_end_velo) * s_d;
            if (prm_endacc_flg) {
                _acce = (VAL_TYPE)0.0;
            }
            _prm._progress = -9;
            _prm._endacc_flg = false;
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
            double V0 = _velo;
            double Vt = ABS(prm_top_velo) * s_d;
            double Ve = ABS(prm_end_velo) * s_d;
            //_TRACE_("V0 = "<<V0);
            //_TRACE_("Vt = "<<Vt);
            //_TRACE_("Ve = "<<Ve);
            _prm._flg = true;
            _prm._top_velo = Vt;
            _prm._end_velo = Ve;
            _prm._target_distance = ABS(prm_target_value_distance);
            _prm._target_distance2 = prm_target_value_distance;
            _prm._moved = 0;
            _prm._moved2 = 0;
            _prm._target_sgn = s_d;
            _prm._target_frames = -1; //時間未使用
            _prm._frame_of_spent = 0;
            _prm._p0 = 0; //未使用
            _prm._p1 = ABS(_prm._target_distance) * prm_p1;
            _prm._p2 = ABS(_prm._target_distance) * prm_p2;
            _prm._endacc_flg = prm_endacc_flg;
            _prm._progress = 2; //回復フェーズを飛ばす
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
            double V0 = _velo;
            double Vt = ABS(prm_top_velo) * s_d;
            double Ve = ABS(prm_end_velo) * s_d;
            double a0 = ABS(prm_top_velo)*0.05 * -sgn_W0;
            double s  = (V0*V0)/(2.0*a0);
            double Dp = s + prm_target_value_distance;
            //_TRACE_("V0 = "<<V0);
            //_TRACE_("Vt = "<<Vt);
            //_TRACE_("Ve = "<<Ve);
            //_TRACE_("a0 = "<<a0);
            //_TRACE_("s  = "<<s );
            //_TRACE_("Dp = "<<Dp);

            _prm._flg = true;
            _prm._top_velo = Vt;
            _prm._end_velo = Ve;
            _prm._target_distance = ABS(s) + ABS(Dp);
            _prm._target_distance2 = prm_target_value_distance;
            _prm._moved = 0;
            _prm._moved2 = 0;
            _prm._acce_a0 = a0;
            _prm._target_sgn = s_d;
            _prm._target_frames = -1; //時間未使用
            _prm._frame_of_spent = 0;
            _prm._p0 = ABS(s);
            _prm._p1 = prm_p1;
            _prm._p2 = prm_p2;
            _prm._endacc_flg = prm_endacc_flg;
            _prm._progress = 0; //回復フェーズから

        }


        //_TRACE_("_prm._flg ="<<_prm._flg);
        //_TRACE_("_prm._p0 ="<<_prm._p0);
        //_TRACE_("_prm._p1 ="<<_prm._p1);
        //_TRACE_("_prm._p2 ="<<_prm._p2);
        //_TRACE_("_prm._target_distance ="<<_prm._target_distance);
        //_TRACE_("_prm._target_distance2 ="<<_prm._target_distance2);
        //_TRACE_("_prm._target_sgn ="<<_prm._target_sgn);
        //_TRACE_("_prm._moved ="<<_prm._moved);
        //_TRACE_("_prm._moved2 ="<<_prm._moved2);
        //_TRACE_("_prm._top_velo ="<<_prm._top_velo);
        //_TRACE_("_prm._end_velo ="<<_prm._end_velo);
        //_TRACE_("_prm._target_frames ="<<_prm._target_frames);
        //_TRACE_("_prm._frame_of_spent ="<<_prm._frame_of_spent);
        //_TRACE_("_prm._progress ="<<_prm._progress);
    }

    bool isAcce() {
        return _prm._flg;
    }

    void behave() {
        //なめらか移動シークエンス起動時
        if (_prm._flg) {
            //_TRACE_(_prm._target_frames<<":_prm._progress="<<_prm._progress);
            //_TRACE_(_prm._target_frames<<":before _value="<<_value<<" _velo="<<_velo<<" _acce="<<_acce<<" _prm._moved="<<_prm._moved<<" _prm._moved2="<<_prm._moved2<<"");
            if (_prm._progress == -9) {
                _prm._flg = false; //おしまい
            } else {

                if (_prm._target_frames < 0) {
                    //目標距離指定の場合
                    if (_prm._progress == 0) {
                        //回復フェーズ
                        _acce = _prm._acce_a0;
                        _prm._progress++;
                    }
                    if (_prm._progress == 1) {
                        //回復中
                        if (_prm._moved >= _prm._p0) {
                            //加速設定
                            _acce = 0.0;
                            _velo = 0.0;
                            //再設定
                            _prm._target_distance = _prm._target_distance - _prm._moved;
                            _prm._moved = 0.0;
                            _prm._p1 = _prm._target_distance * _prm._p1;
                            _prm._p2 = _prm._target_distance * _prm._p2;
                            _prm._progress++;
                        }
                    }
                    if (_prm._progress == 2) {
                        if (!ZEROd_EQ(_prm._p1)) {
                            VAL_TYPE acc = UTIL::getAcceByVd(_velo, _prm._top_velo, _prm._p1*_prm._target_sgn);
                            _acce = acc;
                            if (ABS(_acce) > ABS(_prm._target_distance2)) {
                                _acce = _prm._target_distance2;
                            } else if (ABS(_acce) > ABS(_prm._top_velo)) {
                                _acce = _prm._top_velo;
                            }
                            _prm._progress++;
                        } else {
                            _acce = 0;
                            _velo = _prm._top_velo;
                            _prm._progress+=2; //加速スキップ
                        }
                    }
                    if (_prm._progress == 3) {
                        //加速中
                        if (_prm._moved >= _prm._p1) {
                            //p1 に到達すれば 等速へ
                            _acce = 0;
                            _velo = _prm._top_velo;
                            VAL_TYPE diff_to_end = _prm._target_distance2 - _prm._moved2;
                            if (ABS(_velo) > ABS(diff_to_end)) {
                                _velo = diff_to_end;
                            }
                            _prm._progress++;
                        }
                    }
                    if (_prm._progress == 4) {
                        //_TRACE_("等速中");
                        //等速中
                        if (_prm._moved >= _prm._p2) {
                            //p2 に到達すれば 次回フレームから減速へ
                            //_TRACE_("p2 に到達すれば 次回フレームから減速へ");
                            VAL_TYPE diff_to_end = _prm._target_distance2 - _prm._moved2;
                            if (!ZEROd_EQ(diff_to_end)) {
                                //_TRACE_("diff_to_end="<<diff_to_end<<" 減速加速度を求めれる");
                                VAL_TYPE acc = UTIL::getAcceByVd(_velo, _prm._end_velo, diff_to_end);
                                _acce = acc;
                                //_TRACE_("減速加速度 _acce="<<acc<<" ????");
                                if (ABS(_velo)+ABS(acc) > ABS(diff_to_end)) {
                                    _acce = diff_to_end-_velo;
                                }
                                //_TRACE_("減速加速度 補正 _acce="<<acc<<" ????");
                            }
                            _prm._progress++;
                        }
                    }
                    if (_prm._progress == 5) {
                         //_TRACE_("減速中");
                        //減速中
                        VAL_TYPE diff_to_end = _prm._target_distance2 - _prm._moved2;
                        //Te=(2*D)/(V0+Vt)

                        //double t = (2.0*diff_to_end)/(_velo+_prm._end_velo); //残フレーム数    //＃＃ここもコメント
                        //_TRACE_("double t = (2.0*diff_to_end)/(_velo+_prm._end_velo); //残フレーム数");
                        //_TRACE_("double t = (2.0*"<<diff_to_end<<")/("<<_velo<<"+"<<_prm._end_velo<<"); //残フレーム数");
                        //_TRACE_("double t = ("<<2.0*diff_to_end<<")/("<<_velo+_prm._end_velo<<"); //残フレーム数");
                        //_TRACE_("残フレーム t="<<t<<" ？");
                        //_TRACE_("ABS(_velo) < 2.0*ABS(_acce) = "<<ABS(_velo)<<" < "<<2.0*ABS(_acce));
                        if (ABS(_velo) < 2.0*ABS(_acce)) {
                            //_TRACE_("補正しない （_veloがあまりにも小さいため、t が爆発する。無限小の加速度が設定されてしまうため）");
                            //t = 1;
                            //補正しない(_veloがあまりにも小さいため、t が爆発する)
                        } else {
                            if (_prm._frame_of_spent & 1) { //2回に1回
        //                      if (t > 3 && ABS(diff_to_end) > ABS(_prm._top_velo)*0.0001 && _prm._frame_of_spent % 4U == 0) {
                                //_TRACE_("t="<<t<<" が爆発してないので、補正・補正・補正");
                                //補正・補正・補正
                                if (!ZEROd_EQ(diff_to_end)) {
                                    VAL_TYPE acc = UTIL::getAcceByVd(_velo, _prm._end_velo, diff_to_end);
                                    _acce = acc;
                                    //_TRACE_("減速加速度再設定 _acce="<<acc<<" ????");
                                    if (ABS(_velo)+ABS(acc) > ABS(diff_to_end)) {
                                        _acce = diff_to_end-_velo;
                                    }
                                    //_TRACE_("減速加速度再設定 補正 _acce="<<acc<<" ????");
                                }
                            }
                        }
                        VAL_TYPE end_velo = _prm._end_velo;

                        if ( ZEROd_EQ(diff_to_end)  ||
                             ABS(diff_to_end) <=  ABS(_prm._top_velo)*0.0001 ||
                             (ZEROd_EQ(_prm._top_velo)  || (_prm._top_velo > 0 && diff_to_end <= 0) || (_prm._top_velo < 0  && diff_to_end >= 0) ) || //通り越したか
                             (ZEROd_EQ(_velo+end_velo)  || (_velo+end_velo > 0 && _velo+end_velo+_acce < 0 ) || (_velo+end_velo <  0 && _velo+end_velo+_acce > 0) ) //届かず反転したか
                        ) {
                            //目標距離へ到達
                            //_TRACE_("目標距離へ到達");
                            //_TRACE_("ABS(_prm._target_distance2 - _prm._moved2) <=  ABS(_prm._top_velo)*0.00001");
                            //_TRACE_(""<<ABS(_prm._target_distance2 - _prm._moved2)<<" <= "<<ABS(_prm._top_velo)*0.00001<<" ??");
                            //_TRACE_("(ZEROd_EQ(_prm._top_velo)  || (_prm._top_velo > 0  && diff_to_end <= 0) || (_prm._top_velo < 0  && diff_to_end >= 0) ) || //通り越したか");
                            //_TRACE_("_prm._top_velo="<<_prm._top_velo<<" diff_to_end="<<diff_to_end<<"");
                            //_TRACE_("(ZEROd_EQ(_velo+end_velo)  || (_velo+end_velo  >  0 && _velo +end_velo + _acce < 0 ) || (_velo+end_velo  <  0 && _velo +end_velo+_acce > 0) ) //届かず反転したか");
                            //_TRACE_("_velo="<<_velo<<" end_velo="<<end_velo<<" _velo+end_velo="<<_velo+end_velo<<" _acce="<<_acce<<" _velo +end_velo+_acce="<<_velo +end_velo + _acce <<"");
                            //_TRACE_("おしまいな雰囲気");
                            _velo = _prm._end_velo;
                            if (_prm._endacc_flg) {
                                _acce = (VAL_TYPE)0.0;
                            }
                            if (ZEROd_EQ(end_velo)) {
                                //最終速度が0の場合、バッチリ合わせを試みる。
                                if (ZEROd_EQ(diff_to_end)) {
                                    //既にバッチリあっていました
                                    //_TRACE_("既にバッチリあっていました");
                                    //_TRACE_("おしまい11早！!!");
                                    _velo = (VAL_TYPE)0.0;
                                    _prm._flg = false; //おしまい
                                } else {
                                    //ずれてるのでもう１フレーム頑張ってバッチリ合わせる
                                    _velo = diff_to_end;   //バッチリ合わせる
                                    //_TRACE_("バッチリ合わせたったよ_velo="<<_prm._target_distance2<<"-"<<_prm._moved2<<"="<<_velo);
                                    _prm._progress++; //もう１フレーム
                                }
                            } else {
                                //最終速度が0ではない。そのまま終了
                                //_TRACE_("おしまい22");
                                _prm._flg = false; //おしまい
                            }
                        }
                    } else if (_prm._progress == 6) {
                        //_TRACE_("よしバッチリ合わせておしまい");
                        _velo = (VAL_TYPE)0.0;
                        _prm._flg = false; //おしまい
                    }
                } else {
                    //目標時間指定の場合
                    if (_prm._progress == 0) {
                        if (ZEROd_EQ(_prm._p1)) {
                            _acce = 0;
                            _prm._progress++;
                        } else {
                            //加速設定
                            VAL_TYPE acc = UTIL::getAcceByTv(_prm._p1, _velo, _prm._top_velo);
                            _acce = acc;
                            _prm._progress++;
                        }
                    }
                    if (_prm._progress == 1) {
                        //加速中
                        if (_prm._frame_of_spent >= (int)(_prm._p1)) {
                            //p1 に到達すれば 等速へ
                            _acce = 0;
                            _velo = _prm._top_velo;
                            _prm._progress++;
                        }
                    }
                    if (_prm._progress == 2) {
                        //_TRACE_("等速中 _prm._frame_of_spent="<<_prm._frame_of_spent<<" _prm._p2="<<_prm._p2);
                        //等速中
                        if (_prm._frame_of_spent >= (int)(_prm._p2)) {
                            //_TRACE_("p2 に到達すれば 次回フレームから減速へ _prm._frame_of_spent="<<_prm._frame_of_spent<<" _prm._p2="<<_prm._p2);
                            //p2 に到達すれば 次回フレームから減速へ
                            VAL_TYPE acc = UTIL::getAcceByTv(_prm._target_frames - _prm._frame_of_spent, _velo, _prm._end_velo);
                            _acce = acc;
                            //_TRACE_("減速加速度 _acce="<<_acce);
                            _prm._progress++;
                        }
                    }
                    if (_prm._progress == 3) {
                        //減速中
                        //_TRACE_("減速中");
                        if (_prm._frame_of_spent & 1 == 0) { //2回に1回
                            //_TRACE_("補正・補正・補正");
                            //補正・補正・補正
                            //最後の台形補正
                            //D = (1/2)*(V+Ve)*Te
                            double Ve = _prm._end_velo;
                            double Te = _prm._target_frames - _prm._frame_of_spent;
                            //_TRACE_("Ve = "<<Ve);
                            //_TRACE_("Te = "<<Te);
                            if (Te > 0) {
                                double D = _prm._target_distance2 - _prm._moved2;
                                double V =(2.0*D-Te*Ve)/Te;
                                //_TRACE_("D = "<<D);
                                //_TRACE_("V = "<<V);
                                _velo = V;
                                //_TRACE_("速度 _velo = "<<_velo<<" に補正");
                                VAL_TYPE acc = UTIL::getAcceByTv(_prm._target_frames - _prm._frame_of_spent, _velo, _prm._end_velo);
                                _acce = acc;
                                //_TRACE_("加速度 _acce = "<<_acce<<" に補正");
                            }
                        }
                        //_TRACE_("_prm._frame_of_spent="<<_prm._frame_of_spent<< " _prm._target_frames="<<_prm._target_frames);
                        if (_prm._frame_of_spent >= _prm._target_frames) {
                            //_TRACE_("_prm._frame_of_spent >= _prm._target_frames 成立、おしまいな雰囲気");
                            _velo = _prm._end_velo;
                            if (_prm._endacc_flg) {
                                _acce = (VAL_TYPE)0.0;
                            }
                            if (ZEROd_EQ(_prm._end_velo)) {
                                //最終速度が0の場合、バッチリ合わせを試みる。
                                if (ZEROd_EQ(_prm._target_distance2 - _prm._moved2)) {
                                    //既にバッチリあっていました
                                    //_TRACE_("既にバッチリあっていました");
                                    //_TRACE_("おしまい1早！");
                                    _velo = (VAL_TYPE)0.0;
                                    _prm._flg = false; //おしまい
                                } else {
                                    //ずれてる。
                                    _velo = (_prm._target_distance2 - _prm._moved2); //バッチリ合わせるて、もう１フレーム
                                    //_TRACE_("バッチリ合わせたったよ_velo="<<_prm._target_distance2<<"-"<<_prm._moved2<<"="<<_velo);
                                    _prm._progress++;
                                }
                            } else {
                                //最終速度が0ではない。そのまま終了
                                //_TRACE_("おしまい2");
                                _prm._flg = false; //おしまい
                            }
                        }
                    } else if (_prm._progress == 4) {
                        //_TRACE_("バッチリ合わせておしまい");
                        _velo = (VAL_TYPE)0.0;
                        _prm._flg = false; //おしまい
                    }
                }
            }

            _velo += _acce;
            _value += _velo;

            _prm._moved += ABS(_velo);
            _prm._moved2 += _velo;

            //_TRACE_(_prm._target_frames<<":after _value="<<_value<<" _velo="<<_velo<<" _acce="<<_acce<<" _prm._moved="<<_prm._moved<<" _prm._moved2="<<_prm._moved2<<"");
            _prm._frame_of_spent++;
        } else {
            _prm._progress = -1;
        }
#ifdef MY_DEBUG
        if (_prm._frame_of_spent > 60*60*10) {
            throwGgafCriticalException("GgafValueAccelerator::behave() 10分以上滑りっぱなしなんですが！");
        }
#endif

    }

    virtual ~GgafValueAccelerator() {
    }
};

}
#endif /*GGAFCORE_GGAFVALUEACCELERATOR_H_*/

