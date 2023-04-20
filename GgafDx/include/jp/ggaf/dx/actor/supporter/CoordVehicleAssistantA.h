#ifndef GGAF_DX_COORDVEHICLEASSISTANT_H_
#define GGAF_DX_COORDVEHICLEASSISTANT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/core/util/TrapezoidalVeloValue.hpp"
#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * 駕籠(平行移動支援) の助手A .
 * 師匠(駕籠(平行移動支援) )の補佐を行います。
 * @version 1.00
 * @since 2013/12/16
 * @author Masatoshi Tsuge
 */
class CoordVehicleAssistantA : public GgafCore::Object {
    friend class CoordVehicle;

private:
    /** [r]師匠 */
    CoordVehicle* _pMaster;
    /** X軸方向加速装置 */
    GgafCore::TrapezoidalVeloValue<coord> _smthVxMv;
    /** Y軸方向加速装置 */
    GgafCore::TrapezoidalVeloValue<coord> _smthVyMv;
    /** Z軸方向加速装置 */
    GgafCore::TrapezoidalVeloValue<coord> _smthVzMv;

    virtual void behave();

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pMaster  師匠
     */
    explicit CoordVehicleAssistantA(CoordVehicle* prm_pMaster);

    /**
     * X軸方向でなめらかな移動速度を変化させるシークエンスを実行(時間・距離指定、速度変動) .
     * 移動に費やされる時間(Te)を3つのセクションに分け、次のような速度制御を自動的に行う。<BR>
     * ・時間 0     ～ 時間 p1*Te まで ・・・ 現在の速度からトップスピードまで加速(or減速)移動<BR>
     * ・時間 p1*Te ～ 時間 p2*Te まで ・・・ トップスピードで等速移動<BR>
     * ・時間 p2*Te ～ 時間 Te    まで ・・・ トップスピードから最終スピードへ減速(or加速)移動<BR>
     * ※下図参照<BR>
     * <pre>
     *
     *    速度(v)
     *     ^
     *     |
     *     |                         V0:現時点の速度
     *     |                         Ve:最終速度
     *     |                          D:目標移動距離
     *   Vt|....___________          Te:目標時間（フレーム数）
     *     |   /:         :＼        p1:トップスピードに達する時刻となるような、Teに対する割合(0.0～1.0)
     *   Ve|../.:.........:..＼      p2:減速を開始時刻となるような、Teに対する割合(0.0～1.0)
     *     | /  :         :    |     Vt:距離・時間から導きだされるトップスピード
     *     |/   :         :    |
     *   V0|    :    D    :    |
     *     |    :         :    |
     *   --+----+---------+----+-----> 時間(t:フレーム)
     *   0 |  p1*Te     p2*Te  Te
     *
     * </pre>
     * 最終スピード(Ve)、目標移動距離(D)、到達目標時間(Te)、及び p1, p2 を指定する。<BR>
     * トップスピード(Vt)は内部で自動計算し決定される。<BR>
     * @param prm_target_distance 目標直線移動距離(D)
     * @param prm_target_frames 費やす時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_p1 トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_p2 減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_end_velo 最終スピード(Ve)
     * @param prm_zero_acc_end_flg true:目標移動距離に達した際に加速度を０に強制設定/false:加速度はそのままにしておく
     */
    void slideVxMvByDt(coord prm_target_distance, int prm_target_frames,
                       double prm_p1, double prm_p2, velo prm_end_velo,
                       bool prm_zero_acc_end_flg);

    /**
     * Y軸方向でなめらかな移動速度を変化させるシークエンスを実行(時間・距離指定、速度変動) .
     * slideVxMvByDt() の説明参照。
     * @param prm_target_distance 目標直線移動距離(D)
     * @param prm_target_frames 費やす時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_p1 トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_p2 減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_end_velo 最終スピード(Ve)
     * @param prm_zero_acc_end_flg true:目標移動距離に達した際に加速度を０に強制設定/false:加速度はそのままにしておく
     */
    void slideVyMvByDt(coord prm_target_distance, int prm_target_frames,
                       double prm_p1, double prm_p2, velo prm_end_velo,
                       bool prm_zero_acc_end_flg);

    /**
     * Z軸方向でなめらかな移動速度を変化させるシークエンスを実行(時間・距離指定、速度変動) .
     * slideVxMvByDt() の説明参照。
     * @param prm_target_distance 目標直線移動距離(D)
     * @param prm_target_frames 費やす時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_p1 トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_p2 減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_end_velo 最終スピード(Ve)
     * @param prm_zero_acc_end_flg true:目標移動距離に達した際に加速度を０に強制設定/false:加速度はそのままにしておく
     */
    void slideVzMvByDt(coord prm_target_distance, int prm_target_frames,
                       double prm_p1, double prm_p2, velo prm_end_velo,
                       bool prm_zero_acc_end_flg);

    /**
     * X,Y,Z軸方向でなめらかな移動速度を変化させるシークエンスを実行(時間・距離指定、速度変動) .
     * 内部で slideVxMvByDt(), slideVyMvByDt(), slideVzMvByDt() を実行する。
     * 距離の引数だけ変えてほかの引数は共通。
     * @param prm_x_target_distance X軸方向目標移動距離(Dx)
     * @param prm_y_target_distance Y軸方向目標移動距離(Dy)
     * @param prm_z_target_distance Z軸方向目標移動距離(Dz)
     * @param prm_target_frames 費やす時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_p1 トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_p2 減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_end_velo 最終スピード(Ve)
     * @param prm_zero_acc_end_flg true:目標移動距離に達した際に加速度を０に強制設定/false:加速度はそのままにしておく
     */
    void slideVxyzMvByDt(coord prm_x_target_distance, coord prm_y_target_distance, coord prm_z_target_distance,
                         int prm_target_frames,
                         double prm_p1, double prm_p2, velo prm_end_velo,
                         bool prm_zero_acc_end_flg) {
        slideVxMvByDt(prm_x_target_distance, prm_target_frames,
                      prm_p1, prm_p2, prm_end_velo,
                      prm_zero_acc_end_flg);
        slideVyMvByDt(prm_y_target_distance, prm_target_frames,
                      prm_p1, prm_p2, prm_end_velo,
                      prm_zero_acc_end_flg);
        slideVzMvByDt(prm_z_target_distance, prm_target_frames,
                      prm_p1, prm_p2, prm_end_velo,
                      prm_zero_acc_end_flg);
    }

    /**
     * X,Y,Z軸方向でなめらかな移動速度を変化させるシークエンスを実行(時間・距離指定、速度変動) .
     * 内部で slideVxMvByDt(), slideVyMvByDt(), slideVzMvByDt() を実行する。
     * 費やす時間(prm_target_frames),prm_zero_acc_end_flgのみ共通。
     * @param prm_x_target_distance X軸方向目標移動距離(Dx)
     * @param prm_y_target_distance Y軸方向目標移動距離(Dy)
     * @param prm_z_target_distance Z軸方向目標移動距離(Dz)
     * @param prm_target_frames 費やす時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_x_p1 X軸方向トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_x_p2 X軸方向減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_x_end_velo X軸方向最終スピード(Ve)
     * @param prm_y_p1 Y軸方向トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_y_p2 Y軸方向減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_y_end_velo Y軸方向最終スピード(Ve)
     * @param prm_z_p1 Z軸方向トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_z_p2 Z軸方向減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_z_end_velo Z軸方向最終スピード(Ve)
     * @param prm_zero_acc_end_flg true:目標移動距離に達した際に加速度を０に強制設定/false:加速度はそのままにしておく
     */
    void slideVxyzMvByDt(coord prm_x_target_distance, coord prm_y_target_distance, coord prm_z_target_distance,
                         int prm_target_frames,
                         double prm_x_p1, double prm_x_p2, velo prm_x_end_velo,
                         double prm_y_p1, double prm_y_p2, velo prm_y_end_velo,
                         double prm_z_p1, double prm_z_p2, velo prm_z_end_velo,
                         bool prm_zero_acc_end_flg) {
        slideVxMvByDt(prm_x_target_distance, prm_target_frames,
                      prm_x_p1, prm_x_p2, prm_x_end_velo,
                      prm_zero_acc_end_flg);
        slideVyMvByDt(prm_y_target_distance, prm_target_frames,
                      prm_y_p1, prm_y_p2, prm_y_end_velo,
                      prm_zero_acc_end_flg);
        slideVzMvByDt(prm_z_target_distance, prm_target_frames,
                      prm_z_p1, prm_z_p2, prm_z_end_velo,
                      prm_zero_acc_end_flg);


    }

    /**
     * X,Y,Z軸方向でなめらかな移動速度を変化させるシークエンスを実行(時間・距離(目標座標)指定、速度変動) .
     * 目標座標を指定。移動距離は内部計算。その他はslideVxyzMvByDt() の説明参照。
     * @param prm_x_target X軸方向到達目標座標値
     * @param prm_y_target Y軸方向到達目標座標値
     * @param prm_z_target Z軸方向到達目標座標値
     * @param prm_target_frames 費やす時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_p1 トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_p2 減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_end_velo 最終スピード(Ve)
     * @param prm_zero_acc_end_flg true:目標移動距離に達した際に加速度を０に強制設定/false:加速度はそのままにしておく
     */
    void slideVxyzMvByDtTo(coord prm_x_target, coord prm_y_target, coord prm_z_target,
                           int prm_target_frames,
                           double prm_p1, double prm_p2, velo prm_end_velo,
                           bool prm_zero_acc_end_flg);

    /**
     * X,Y,Z軸方向でなめらかな移動速度を変化させるシークエンスを実行(時間・距離(目標座標)指定、速度変動) .
     * 目標座標を指定。移動距離は内部計算。その他はslideVxyzMvByDt() の説明参照。
     * @param prm_x_target X軸方向到達目標座標値
     * @param prm_y_target Y軸方向到達目標座標値
     * @param prm_z_target Z軸方向到達目標座標値
     * @param prm_target_frames 費やす時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_x_p1 X軸方向トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_x_p2 X軸方向減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_x_end_velo X軸方向最終スピード(Ve)
     * @param prm_y_p1 Y軸方向トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_y_p2 Y軸方向減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_y_end_velo Y軸方向最終スピード(Ve)
     * @param prm_z_p1 Z軸方向トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_z_p2 Z軸方向減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_z_end_velo Z軸方向最終スピード(Ve)
     * @param prm_zero_acc_end_flg true:目標移動距離に達した際に加速度を０に強制設定/false:加速度はそのままにしておく
     */
    void slideVxyzMvByDtTo(coord prm_x_target, coord prm_y_target, coord prm_z_target,
                           int prm_target_frames,
                           double prm_x_p1, double prm_x_p2, velo prm_x_end_velo,
                           double prm_y_p1, double prm_y_p2, velo prm_y_end_velo,
                           double prm_z_p1, double prm_z_p2, velo prm_z_end_velo,
                           bool prm_zero_acc_end_flg);


    /**
     * なめらかな移動速度を変化させるシークエンスを実行(速度・距離指定、時間変動) .
     * 移動距離を3つのセクション(d1,d2,d3)に分け、次のような速度制御を自動的に行う。<BR>
     * ・距離 0     ～ 距離 d1       まで ・・・ 現在の速度からトップスピードまで加速(or減速)移動<BR>
     * ・距離 d1    ～ 距離 d1+d2    まで ・・・ トップスピードで等速移動<BR>
     * ・距離 d1+d2 ～ 距離 d1+d2+d3 まで ・・・ トップスピードから最終スピードへ減速(or加速)移動<BR>
     * ※下図参照<BR>
     * <pre>
     *    速度(v)
     *     ^
     *     |                         V0:現時点の速度
     *     |                         Vt:トップスピード
     *     |                         Ve:最終速度
     *     |         D=d1+d2+d3       D:目標移動距離(D=d1+d2+d3)
     *   Vt|....___________          p1:トップスピードに達する距離となるような、距離(D)に対する割合
     *     |   /|         |＼            つまり    d1 = D*p1 となるような p1 (0.0～1.0)
     *   Ve|../.|.........|..＼      p2:減速を開始距離となるような、距離(D)に対する割合
     *     | /  |         |    |         つまり d1+d2 = D*p2 となるような p2 (0.0～1.0)
     *     |/   |         |    |     Te:費やされる必要時間（フレーム数）
     *   V0| d1 |    d2   | d3 |
     *     |    |         |    |
     *   --+----+---------+----+-----> 時間(t:フレーム)
     *   0 |                  Te
     *
     * </pre>
     * トップスピード(Vt)、最終スピード(Ve)、目標移動距離(D)、及び p1, p2 を指定する。<BR>
     * 費やされる時間(Te)は内部で自動計し決定される。<BR>
     * <BR>
     * @param prm_top_velo トップスピード(Vt)
     * @param prm_target_distance 目標直線移動距離(D)
     * @param prm_p1 トップスピードに達する距離となるような、距離(D)に対する割合。(d1 = D*prm_p1)
     * @param prm_p2 減速を開始距離となるような、距離(D)に対する割合 (d1+d2 = D*p2)
     * @param prm_end_velo 最終スピード(Ve)
     * @param prm_zero_acc_end_flg true:目標時間に達した際に加速度を０に強制設定/false:加速度はそのままにしておく
     */
    void slideVxMvByVd(velo prm_top_velo, coord prm_target_distance,
                       double prm_p1, double prm_p2, velo prm_end_velo,
                       bool prm_zero_acc_end_flg);

    void slideVyMvByVd(velo prm_top_velo, coord prm_target_distance,
                       double prm_p1, double prm_p2, velo prm_end_velo,
                       bool prm_zero_acc_end_flg);

    void slideVzMvByVd(velo prm_top_velo, coord prm_target_distance,
                       double prm_p1, double prm_p2, velo prm_end_velo,
                       bool prm_zero_acc_end_flg);

    void slideVxyzMvByVd(velo prm_top_velo,
                         coord prm_x_target_distance, coord prm_y_target_distance, coord prm_z_target_distance,
                         double prm_p1, double prm_p2, velo prm_end_velo,
                         bool prm_zero_acc_end_flg);

    void slideVxyzMvByVdTo(velo prm_top_velo,
                           coord prm_x_target, coord prm_y_target, coord prm_z_target,
                           double prm_p1, double prm_p2, velo prm_end_velo,
                           bool prm_zero_acc_end_flg);

    /**
     * なめらかな移動シークエンスが作動中か（注意：移動しているか否かではない）.
     * @return true:作動中 / false:作動中ではない
     */
    bool isSliding() {
        if (_smthVxMv.isTransitioning() || _smthVyMv.isTransitioning() || _smthVzMv.isTransitioning()) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * なめらかな移動シークエンスを停止（注意：移動（速度）を停止させるという事は行っていない）.
     */
    void stopSliding() {
        _smthVxMv.stopTransitioning();
        _smthVyMv.stopTransitioning();
        _smthVzMv.stopTransitioning();
    }

    virtual ~CoordVehicleAssistantA();
};

}
#endif /*GGAF_DX_COORDVEHICLEASSISTANT_H_*/

