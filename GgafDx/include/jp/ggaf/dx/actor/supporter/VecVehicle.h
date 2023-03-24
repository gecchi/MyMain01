#ifndef GGAF_DX_VECVEHICLE_H_
#define GGAF_DX_VECVEHICLE_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "ActorVehicle.h"

#include "jp/ggaf/dx/util/GeoElem.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * アクターの移動支援の力車(前進、後退、旋回) .
 * それはさて置き、つまりは座標計算支援（共通化）クラスです。<BR>
 * GeometricActor のメンバの<BR>
 *  _x,  _y,  _z  ・・・ アクターの座標<BR>
 * _rx, _ry, _rz  ・・・ アクターの軸回転角度<BR>
 * を変化させます。方向ベクトル、速度、距離、時間、によって管理操作するために作成したクラス。<BR>
 * 共通の基本的な移動、回転は力車に任せて、<BR>
 * アクター固有の特殊な移動回転動作を processBehave() に直接記述。という設計思想。<BR>
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class VecVehicle : public ActorVehicle {

private:
    /** [r]力車の助手A(移動速度の補佐) */
    VecVehicleMvAssistant* _pAsstMv;
    /** [r]力車の助手B(軸回転方角角速度の補佐) */
    VecVehicleFaceAngAssistant* _pAsstFaceAng;
    /** [r]力車の助手C(移動方角角速度の補佐) */
    VecVehicleMvAngAssistant* _pAsstMvAng;

public:
    /** [r]対象アクター */
   // GeometricActor* const _pActor;

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用Actor
     */
    explicit VecVehicle(GeometricActor* prm_pActor);

    /**
     * 力車の助手A(移動速度の補佐)を取得 .
     * @return 力車の助手A
     */
    VecVehicleMvAssistant* asstMv();

    /**
     * 力車の助手B(軸回転方角角速度の補佐)を取得 .
     * @return 力車の助手B
     */
    VecVehicleFaceAngAssistant* asstFaceAng();

    /**
     * 力車の助手C(移動方角角速度の補佐)を取得 .
     * @return 力車の助手C
     */
    VecVehicleMvAngAssistant* asstMvAng();

    void reset();

public: //_rx , _ry, _rz 操作関連 //////////////////////////////////////////////
    /** [r]対象キャラの向き(_rx, _ry, _rz)への参照 */
    angle* _actor_face[3];
    /** [r/w]軸回転方角の角速度（軸回転方角に毎フレーム加算する方角） */
    angvelo _angvelo_face[3];
    /** [r/w]軸回転方角の角速度上限(最高値は360,000) */
    angvelo _top_angvelo_face[3];
    /** [r/w]軸回転方角の角速度下限(最高値は-360,000) */
    angvelo _bottom_angvelo_face[3];
    /** [r/w]軸回転方角の角加速度（角速度に毎フレーム加算する値） */
    angacce _angacce_face[3];
    /** [r/w]軸回転方角の角躍度（角加速度に毎フレーム加算する値） */
    angjerk _angjerk_face[3];
    /** [r/w]目標の軸回転方角自動向き有効フラグ */
    bool _is_targeting_face[3];
    /** [r/w]目標の軸回転方角自動停止機能有効フラグ */
    bool _face_targeting_stop_flg[3];
    /** [r/w]目標とするキャラの軸回転方角の方角(0～360,000) */
    angle _target_face[3];
    /** [r/w]目標の軸回転方角自動停止機能が有効になる回転方向 */
    int _face_stop_allow_way[3]; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** [r/w]目標の軸回転方角自動停止機能が有効になる角速度（回転正負共通） */
    angvelo _face_stop_allow_angvelo[3]; //この角速度より小さい値の場合機能有効とするz

public:
    void setMvAngByFaceAng() {
        setRzRyMvAng(_pActor->_rz, _pActor->_ry);
    }
    /**
     * Actorの目標の軸回転方角自動停止機能を有効(目標の軸回転方角設定)<BR>
     * 引数に設定された軸回転方角になると、軸回転方角角速度及び軸回転方角角加速度を 0 にし、回転を停止させます。<BR>
     * 軸回転方角角速度が 0 の場合、何も起こりません。本メソッドを実行したからと言って勝手に向きが変わるとという意味ではありません。 <BR>
     * 軸回転方角角速度等の設定を併せて実行して、別途軸回転も行なってください。<BR>
     * 内部的には、addFaceAng(prm_axis, int) が毎フレーム行われる仕組みです。<BR>
     * 目標の回転方角に到達したならば、この目標の軸回転方角自動停止機能は解除(内部のフラグをアンセット)されます。<BR>
     * @param   prm_axis    回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param   prm_target    到達目標の回転方角(0～360,000)
     * @param   prm_allow_way  自動停止を許可する進入方向(TURN_CLOCKWISE/TURN_COUNTERCLOCKWISE/TURN_BOTH)
     * @param   prm_allow_angvelo 自動停止機能が有効になる回転角速度
     */
    void setStopTargetFaceAng(axis prm_axis,
                              angle prm_target,
                              int prm_allow_way = TURN_BOTH,
                              angvelo prm_allow_angvelo = D360ANG);

    /**
     * Actorの目標回転方向自動停止機能を有効(現在XY座標からの対象XY座標で設定)<BR>
     * @param   prm_axis    回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param   prm_tx  対象X座標
     * @param   prm_ty  対象Y座標
     * @param   prm_allow_way  自動停止機能が有効になる回転方向
     * @param   prm_allow_angvelo 自動停止機能が有効になる回転角速度
     */
    void setStopTargetFaceAngTwd(axis prm_axis,
                                 coord prm_tx,
                                 coord prm_ty,
                                 int prm_allow_way = TURN_BOTH,
                                 angvelo prm_allow_angvelo = D360ANG);
    /**
     * 軸回転方角の角速度（軸回転方角に毎フレーム加算する値）を設定 .
     * @param prm_axis 回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param prm_angvelo 角速度
     */
    void setFaceAngVelo(axis prm_axis, angvelo prm_angvelo);

    /**
     * 軸回転方角の角速度（軸回転方角に毎フレーム加算する値）を設定 .
     * @param prm_axis_x_angvelo X軸回転の角速度
     * @param prm_axis_z_angvelo Z軸回転の角速度
     * @param prm_axis_y_angvelo Y軸回転の角速度
     */
    void setRollPitchYawFaceAngVelo(angvelo prm_axis_x_angvelo,
                                    angvelo prm_axis_z_angvelo,
                                    angvelo prm_axis_y_angvelo);

    /**
     * Rolling(X軸回転方角)の角速度を設定 .
     * setFaceAngVelo(AXIS_X, prm_angvelo); と等価。
     * @param prm_axis_x_angvelo X軸回転の角速度
     */
    inline void setRollFaceAngVelo(angvelo prm_axis_x_angvelo) {
        setFaceAngVelo(AXIS_X, prm_axis_x_angvelo);
    }
    inline void setRxFaceAngVelo(angvelo prm_axis_x_angvelo) {
        setFaceAngVelo(AXIS_X, prm_axis_x_angvelo);
    }

    /**
     * Pitching(Z軸回転方角)の角速度を設定 .
     * setFaceAngVelo(AXIS_Z, prm_angvelo); と等価。
     * @param prm_axis_z_angvelo Z軸回転の角速度
     */
    inline void setPitchFaceAngVelo(angvelo prm_axis_z_angvelo) {
        setFaceAngVelo(AXIS_Z, prm_axis_z_angvelo);
    }
    inline void setRzFaceAngVelo(angvelo prm_axis_z_angvelo) {
        setFaceAngVelo(AXIS_Z, prm_axis_z_angvelo);
    }

    /**
     * Yawing(Y軸回転方角)の角速度を設定 .
     * setFaceAngVelo(AXIS_Y, prm_angvelo); と等価。
     * @param prm_axis_y_angvelo Y軸回転の角速度
     */
    inline void setYawFaceAngVelo(angvelo prm_axis_y_angvelo) {
        setFaceAngVelo(AXIS_Y, prm_axis_y_angvelo);
    }
    inline void setRyFaceAngVelo(angvelo prm_axis_y_angvelo) {
        setFaceAngVelo(AXIS_Y, prm_axis_y_angvelo);
    }


    void forceFaceAngVeloRange(axis prm_axis,
                               angvelo prm_angvelo01,
                               angvelo prm_angvelo02);
    /**
     * 軸回転方角の角加速度（軸回転方角の角速度に毎フレーム加算する値）を設定 .
     * @param prm_axis 回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param prm_angacce 角加速度
     */
    void setFaceAngAcce(axis prm_axis, angacce prm_angacce);

    /**
     * Rolling(X軸回転方角)の角加速度を設定 .
     * setFaceAngAcce(AXIS_X, prm_angacce); と等価。
     * @param prm_axis_x_angacce X軸回転方角の角加速度
     */
    inline void setRollFaceAngAcce(angvelo prm_axis_x_angacce) {
        setFaceAngAcce(AXIS_X, prm_axis_x_angacce);
    }
    inline void setRxFaceAngAcce(angvelo prm_axis_x_angacce) {
        setFaceAngAcce(AXIS_X, prm_axis_x_angacce);
    }

    /**
     * Pitching(Z軸回転方角)の角加速度を設定 .
     * setFaceAngAcce(AXIS_Z, prm_angacce); と等価。
     * @param prm_axis_z_angacce Z軸回転方角の角加速度
     */
    inline void setPitchFaceAngAcce(angvelo prm_axis_z_angacce) {
        setFaceAngAcce(AXIS_Z, prm_axis_z_angacce);
    }

    inline void setRzFaceAngAcce(angvelo prm_axis_z_angacce) {
        setFaceAngAcce(AXIS_Z, prm_axis_z_angacce);
    }

    /**
     * Yawing(Y軸回転方角)の角加速度を設定 .
     * setFaceAngAcce(AXIS_Y, prm_angacce); と等価。
     * @param prm_axis_y_angacce Y軸回転方角の角加速度
     */
    inline void setYawFaceAngAcce(angvelo prm_axis_y_angacce) {
        setFaceAngAcce(AXIS_Y, prm_axis_y_angacce);
    }

    inline void setRyFaceAngAcce(angvelo prm_axis_y_angacce) {
        setFaceAngAcce(AXIS_Y, prm_axis_y_angacce);
    }

    angle getFaceAngDistance(axis prm_axis, coord prm_tx, coord prm_ty, int prm_way);

    angle getFaceAngDistance(axis prm_axis, angle prm_target, int prm_way);

    ////////////////////////////////////////////////////MOVER

public: //_x, _y, _z 操作関連 //////////////////////////////////////////////
    /** [r]キャラの移動方角単位ベクトル */
    double _vX, _vY, _vZ;
    /** [r/w]移動方角のZ軸回転角 */
    angle _rz_mv;
    /** [r/w]移動方角のY軸回転角 */
    angle _ry_mv;
    /** [r/w]移動速度 */
    velo _velo_mv;
    /** [r/w]移動速度上限 */
    velo _top_velo_mv;
    /** [r/w]移動速度下限 */
    velo _bottom_velo_mv;
    /** [r/w]移動加速度 */
    acce _acc_mv;

    /** [r/w]移動方角（Z軸回転）の角速度（移動方角（Z軸回転）に毎フレーム加算する方角） */
    angvelo _angvelo_rz_mv;
    /** [r/w]移動方角（Z軸回転）の角速度上限(最高値は360,000) */
    angvelo _top_angvelo_rz_mv;
    /** [r/w]移動方角（Z軸回転）の角速度下限(最高値は-360,000) */
    angvelo _bottom_angvelo_rz_mv;
    /** [r/w]移動方角（Z軸回転）の角加速度（角速度に毎フレーム加算する値） */
    angacce _angacce_rz_mv;
    /** [r/w]移動方角（Z軸回転）の角躍度（角加速度に毎フレーム加算する値） */
    angjerk _angjerk_rz_mv;
    /** [r/w]目標の移動方角（Z軸回転）向き有効フラグ */
    bool _is_targeting_rz_mv;
    /** [r/w]目標の移動方角（Z軸回転）自動停止機能有効フラグ */
    bool _rz_mv_targeting_stop_flg;
    /** 目標とするキャラの移動方角（Z軸回転）の方角(0～360,000) */
    angle _target_rz_mv;
    /** [r/w]目標の移動方角（Z軸回転）自動停止機能が有効になる進入回転方向 */
    int _rz_mv_stop_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** [r/w]目標の移動方角（Z軸回転）自動停止機能が有効になる移動方角角速度 */
    angvelo _rz_mv_stop_allow_angvelo;
    /** [r/w]自動前方向き機能有効フラグ */
    bool _relate_RzFaceAng_with_RzMvAng_flg;
    //true  : 移動方角（Z軸回転）を変更すると、それに伴い同じ方角が軸回転方角(Z軸)にも設定される
    //false : 移動方角（Z軸回転）とZ軸軸回転方角は独立

    /** [r/w]移動方角（Y軸回転）の角速度（移動方角（Y軸回転）に毎フレーム加算する方角） */
    angvelo _angvelo_ry_mv;
    /** [r/w]移動方角（Y軸回転）の角速度上限(最高値は360,000) */
    angvelo _top_angvelo_ry_mv;
    /** [r/w]移動方角（Y軸回転）の角速度下限(最高値は-360,000) */
    angvelo _bottom_angvelo_ry_mv;
    /** [r/w]移動方角（Y軸回転）の角加速度（角速度に毎フレーム加算する値） */
    angacce _angacce_ry_mv;
    /** [r/w]移動方角（Y軸回転）の角躍度（角加速度に毎フレーム加算する値） */
    angjerk _angjerk_ry_mv;
    /** [r/w]目標の移動方角（Y軸回転）自動向き有効フラグ */
    bool _is_targeting_ry_mv;
    /** [r/w]目標の移動方角（Y軸回転）自動停止機能有効フラグ */
    bool _ry_mv_targeting_stop_flg;
    /** [r/w]目標とするキャラの移動方角（Y軸回転）の方角(0～360,000) */
    angle _target_ry_mv;
    /** [r/w]目標の移動方角（Y軸回転）自動停止機能が有効になる進入回転方向 */
    int _ry_mv_stop_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** [r/w]目標の移動方角（Y軸回転）自動停止機能が有効になる移動方角角速度 */
    angvelo _ry_mv_stop_allow_angvelo;
    /** [r/w]自動前方向き機能有効フラグ */
    bool _relate_RyFaceAng_with_RyMvAng_flg;
    //true  : 移動方角（Y軸回転）を変更すると、それに伴い同じ方角が軸回転方角(Y軸)にも設定される
    //false : 移動方角（Y軸回転）とY軸軸回転方角は独立

    bool _taget_face_alltime_flg;
    const GeometricActor* _taget_face_alltime_pActor;
    coord _taget_face_alltime_tx;
    coord _taget_face_alltime_ty;
    coord _taget_face_alltime_tz;
    angvelo _taget_face_alltime_angvelo;
    angacce _taget_face_alltime_angacce;
    int _taget_face_alltime_way;
    bool _taget_face_alltime_optimize_ang;

public:
    /**
     * 移動速度を設定 .
     * @param   prm_velo_mv  移動速度
     */
    void setMvVelo(velo prm_velo_mv);

    /**
     * 移動速度を加算 .
     * @param prm_velo_mv_Offset 加算移動速度
     */
    void addMvVelo(velo prm_velo_mv_Offset);

    /**
     * 移動速度の上限下限を設定し、移動速度の範囲を制限する .
     * 引数の移動速度１、移動速度２の大小はどちらでもかまわない。（内部で判定する）
     * @param prm_velo_mv01  移動速度１
     * @param prm_velo_mv02  移動速度２
     */
    void forceMvVeloRange(velo prm_velo_mv01, velo prm_velo_mv02);

    /**
     * 移動速度の上限下限を設定し、移動速度の範囲を制限する .
     * 上限下限値は、-prm_velo_mv ～ prm_velo_mv の範囲になる。
     * @param prm_velo_mv 移動速度
     */
    void forceMvVeloRange(velo prm_velo_mv);

    /**
     * 現在の移動速度を取得 .
     * @return 現在の移動速度
     */
    inline velo getMvVelo() const {
        return _velo_mv;
    }

    /**
     * 上限移動速度を取得 .
     * @return 上限移動速度
     */
    inline velo getMvVeloTop() const {
        return _top_velo_mv;
    }

    /**
     * 下限移動速度を取得 .
     * @return 下限移動速度
     */
    inline velo getMvVeloBottom() const {
        return _bottom_velo_mv;
    }

    /**
     * 現在の移動速度を上限移動速度に更新 .
     */
    inline void setMvVeloTop() {
        _velo_mv = _top_velo_mv;
    }

    /**
     * 現在の移動速度を下限移動速度に更新 .
     */
    inline void setMvVeloBottom() {
        _velo_mv = _bottom_velo_mv;
    }

    /**
     * 移動加速度を設定 .
     * @param prm_acceMove 移動加速度
     */
    void setMvAcce(acce prm_acceMove);

    /**
     * 移動加速度を、「停止移動距離」により設定する .
     * <pre><code>
     *
     *    速度(v)
     *     ^       a:減加速度（_acc_mv に設定される）
     *     |       D:停止までの移動距離（引数）
     *     |      V0:現時点の速度（= 現在の _velo_mv が使用される）
     *   V0|      Te:停止するフレーム （戻り値）
     *     |＼
     *     |  ＼
     *     |    ＼ 斜辺の傾きa
     *     |   D  ＼
     *     |        ＼
     *   --+----------＼-----> 時間(t)
     *   0 |          Te
     *
     * </code></pre>
     * 上図のような状態を想定し、引数の距離(D)から、加速度(a)を計算し _acc_mv 設定している。<BR>
     * 停止までのフレーム(Te) は 距離(D) により変化するため指定不可。<BR>
     * @param prm_target_distance 停止時移動距離(D)
     * @return 必要な時間フレーム(Te)。参考値にどうぞ。
     */
    frame setMvAcceToStop(coord prm_target_distance);


    /**
     * 軸回転方角の角加速度を、「停止の距離角」により設定する .
     * @param prm_axis 回転軸(AXIS_X / AXIS_Y / AXIS_Z)
     * @param prm_target_distance 停止の移動角度距離(D)
     * @return 必要な時間フレーム(Te)。参考値にどうぞ。
     */
    frame setFaceAngAcceToStop(axis prm_axis, angle prm_target_distance);


    /**
     * 移動加速度を、「目標到達速度」「移動距離(達するまでに費やす距離)」により設定 .
     * <pre><code>
     *
     *    速度(v)
     *     ^        a:加速度（_acc_mv に設定される）
     *     |        D:移動距離（引数）
     *     |       V0:現時点の速度（= 現在の _velo_mv が使用される）
     *     |       Vt:目標到達速度（引数）
     *     |       Te:目標到達速度に達した時の時間（戻り値）
     *   Vt|........
     *     |      ／|
     *     |    ／  |
     *     |  ／    |   斜辺の傾きa
     *     |／      |
     *   V0|    D   |
     *     |        |
     *   --+--------+---> 時間(t)
     *   0 |        Te
     *
     * </code></pre>
     * 上図のような状態を想定し、目標到達速度(Vt)と、移動距離(D)から、加速度(a)を計算し _acc_mv に設定している。<BR>
     * 目標到達まで必要なフレーム(Te) はパラメータにより変化するため指定不可。<BR>
     * 捕捉：setMvAcceByD(0, D) は setMvAcceToStop(D) と同じである
     * @param prm_target_distance  目標到達速度に達するまでに費やす距離(D)
     * @param prm_target_velo 目標到達速度(Vt)
     * @return 必要な時間フレーム(Te)。参考値にどうぞ。
     */
    frame setMvAcceByD(coord prm_target_distance, velo prm_target_velo);

    /**
     * 軸回転方角の角加速度を「距離角(達するまでに費やす距離)」「目標到達時角速度」により設定 .
     * @param prm_axis 回転軸(AXIS_X / AXIS_Y / AXIS_Z)
     * @param prm_target_distance 目標到達角速度に達するまでに費やす回転距離(D)
     * @param prm_target_angvelo 目標到達角速度(Vt)
     * @return 必要な時間フレーム(Te)。参考値にどうぞ。
     */
    frame setFaceAngAcceByD(axis prm_axis, angle prm_target_distance, angvelo prm_target_angvelo);

    /**
     * 移動加速度を、「目標到達速度」「費やす時間」により設定 .
     * <pre><code>
     *
     *    速度(v)
     *     ^        a:加速度（_acc_mv に設定される)
     *     |        D:移動距離 （戻り値）
     *     |       V0:現時点の速度（= 現在の _velo_mv が使用される）
     *     |       Vt:目標到達速度（引数）
     *     |       Te:目標到達速度に達した時の時間（引数）
     *   Vt|........
     *     |      ／|
     *     |    ／  |
     *     |  ／    |   斜辺の傾きa
     *     |／      |
     *   V0|    D   |
     *     |        |
     *   --+--------+---> 時間(tフレーム)
     *   0 |        Te
     *
     *    a = (Vt-V0) / Te
     * </code></pre>
     * 上図のような状態を想定し、目標到達速度(Vt)と、その到達時間(Te) から、加速度(a)を計算し設定している。<BR>
     * 移動距離(D)は、パラメータにより変化するため指定不可。<BR>
     * @param prm_target_frames 費やす時間(Te)
     * @param prm_target_velo   目標到達速度(Vt)
     * @return 移動距離(D)
     */
    coord setMvAcceByT(frame prm_target_frames, velo prm_target_velo);

    /**
     * 軸回転方角の角加速度を「目標到達角速度」「費やす時間」により設定 .
     * @param prm_axis 回転軸(AXIS_X / AXIS_Y / AXIS_Z)
     * @param prm_target_frames  費やす時間(Te)
     * @param prm_target_angvelo 目標到達速度(Vt)
     * @return 移動角距離(D)
     */
    angle setFaceAngAcceByT(axis prm_axis, frame prm_target_frames, angvelo prm_target_angvelo);

    /**
     * Actorの移動方角（Z軸回転）を設定。<BR>
     * 加算後の移動方角（Z軸回転）が範囲外（0～360,000 以外）の値になっても、正しい 0～360,000 の範囲内の値に再計算されます。<BR>
     * 自動前方向き機能が有効(_relate_RzFaceAng_with_RzMvAng_flg)の場合、<BR>
     * Actorの向きも移動方角（Z軸回転）と同じ方向を向くように setStopTargetFaceAng(int) も実行されます。<BR>
     *
     * @param   prm_ang 移動方角（Z軸回転）(0～360,000)
     */
    void setRzMvAng(angle prm_ang);

    /**
     * 現在の Actor の移動方角（Z軸回転）へ加算（負で減算）。<BR>
     *
     * 引数に渡すのは、移動方角（Z軸回転）の増分です。Actorの移動方角（Z軸回転）（_rz_mv）を相対指定でるメソッドです。<BR>
     * 加算後の移動方角（Z軸回転）が範囲外（0～360,000 以外）の値になっても、最終的には setRzMvAng(int) を呼び出しますので<BR>
     * 正しい 0～360,000 の範囲内の値に再設定されます。<BR>
     * 引数である加算（減算）する移動方角（Z軸回転）は、Z軸移動加速度の上限と下限の間の範囲に限ります。<BR>
     * つまり、引数の有効な範囲は以下の通りとなります。<BR>
     *
     *   _bottom_angvelo_rz_mv ≦ 引数の動方角増分 ≦ _top_angvelo_rz_mv  です。<BR>
     *
     * もし範囲外の引数の移動方角（Z軸回転）増分を指定した場合は、直近の範囲内の値に強制的に抑えられ、その値が加算されます。<BR>
     * また、自動前方向き機能が有効(_relate_RzFaceAng_with_RzMvAng_flg)の場合、<BR>
     * 加算後の移動方角（Z軸回転）の値が、Z軸の目標の軸回転方角として設定されます。（自動で前方を向くに設定されます。但し前方＝アングル0のキャラの場合ですけど；）<BR>
     *
     * 【補足：】<BR>
     * 本メソッド毎フレーム実行することでXY平面の円運動が可能になります。<BR>
     * 引数の移動方角（Z軸回転）が、数直線上の 0 に、より近い値を加算し続けた場合は、緩やかなカーブ描きながら向転換することを意味します。<BR>
     * 逆に、引数の移動方角（Z軸回転）が、0 から、より離れた値を加算し続けた場合は、より鋭角的なカーブ描きながら向転換することを意味します。<BR>
     * デフォルトのZ軸移動加速度の上限と下限（_bottom_angvelo_rz_mv、_top_angvelo_rz_mv) は  -360000 , 360000<BR>
     * となっています。これは瞬時に（1フレームで）どんな移動方角（Z軸回転）にも向きを変えれることを意味します。<BR>
     *
     * @param   prm_ang 移動方角（Z軸回転）増分(範囲：_bottom_angvelo_rz_mv ～ _top_angvelo_rz_mv)
     */
    void addRzMvAng(angle prm_ang);

    angle getRzMvAng() {
        return _rz_mv;
    }
    /**
     * Actorの目標の移動方角（Z軸回転）自動停止機能を有効(目標の移動方角（Z軸回転）設定)<BR>
     * 引数に設定された移動方角（Z軸回転）になるまで、移動方角（Z軸回転）を加算(減算)を毎フレーム行い続けます。<BR>
     * 加算か減算かは、移動方角（Z軸回転）の角速度（_angvelo_rz_mv）の正負で決定されます。<BR>
     * <B>移動方角（Z軸回転）の角速度が 0 ならば、何も起こりません。</B>動作させるには、角速度が必要です。<BR>
     * 内部的には、addRzMvAng(int) が毎フレーム行われる仕組みです。(this->behave()で実行)<BR>
     * 目標の移動方角（Z軸回転）に到達したならば、この目標の移動方角（Z軸回転）自動停止機能は解除されます。<BR>
     *
     * @param   prm_target_rz_mv 到達目標の移動方角（Z軸回転）(-360,000～360,000)
     * @param   prm_allow_way  自動停止機能が有効になる進入回転方向
     * @param   prm_allow_angvelo 停止機能が有効になる移動方角角速度(これ以上の角速度の場合は停止しません)
     */
    void setStopTargetRzMvAng(angle prm_target_rz_mv,
                              int prm_allow_way = TURN_BOTH,
                              angvelo prm_allow_angvelo = D360ANG);

    void setRzMvAngVelo(angvelo prm_angvelo_rz_mv);

    void forceRzMvAngVeloRange(angvelo prm_angvelo_rz_mv01, angvelo prm_angvelo_rz_mv02);

    void setRzMvAngAcce(angacce prm_angacce_rz_mv);

    angle getRzMvAngDistanceTwd(coord prm_tx, coord prm_ty, int prm_way);

    /**
     * 自身の移動方角のZ軸回転角( _rz_mv )と、ターゲットの回転角との差分を取得.
     * TURN_COUNTERCLOCKWISE ・・・回転方向が左回りで差異角取得、正の値で返る。
     * TURN_CLOCKWISE        ・・・回転方向が右回りで差異角取得、負の値に返る。
     * TURN_CLOSE_TO         ・・・ターゲットの回転角と距離が近い方の回転方向で取得、正又は負の値になる。
     * TURN_ANTICLOSE_TO     ・・・ターゲットの回転角と距離が遠い方の回転方向で取得、正又は負の値になる。
     * @param prm_target_rz_mv ターゲット角の値
     * @param prm_way TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @return
     */
    angle getRzMvAngDistance(angle prm_target_rz_mv, int prm_way);

    /**
     * Actorの移動方角（Y軸回転）を設定。<BR>
     * 加算後の移動方角（Y軸回転）が範囲外（0～360,000 以外）の値になっても、正しい 0～360,000 の範囲内の値に再計算されます。<BR>
     * 自動前方向き機能が有効(_relate_RyFaceAng_with_RyMvAng_flg)の場合、<BR>
     * Actorの向きも移動方角（Y軸回転）と同じ方向を向くように setStopTargetFaceAng(int) も実行されます。<BR>
     * @param prm_ang 移動方角（Y軸回転）(0～360,000)
     */
    void setRyMvAng(angle prm_ang);

    /**
     * 現在の Actor の移動方角（Y軸回転）へ加算（負で減算）。<BR>
     *
     * 引数に渡すのは、移動方角（Y軸回転）の増分です。Actorの移動方角（Y軸回転）（_ry_mv）を相対指定でるメソッドです。<BR>
     * 加算後の移動方角（Y軸回転）が範囲外（0～360,000 以外）の値になっても、最終的には setRyMvAng(int) を呼び出しますので<BR>
     * 正しい 0～360,000 の範囲内の値に再設定されます。<BR>
     * 引数である加算（減算）する移動方角（Y軸回転）は、Y軸移動加速度の上限と下限の間の範囲に限ります。<BR>
     * つまり、引数の有効な範囲は以下の通りとなります。<BR>
     *
     *   _bottom_angvelo_ry_mv ≦ 引数の動方角増分 ≦ _top_angvelo_ry_mv  です。<BR>
     *
     * もし範囲外の引数の移動方角（Y軸回転）増分を指定した場合は、直近の範囲内の値に強制的に抑えられ、その値が加算されます。<BR>
     * また、自動前方向き機能が有効(_relate_RyFaceAng_with_RyMvAng_flg)の場合、<BR>
     * 加算後の移動方角（Y軸回転）の値が、Z軸の目標の軸回転方角として設定されます。（自動で前方を向くに設定されます。但し前方＝アングル0のキャラの場合ですけど；）<BR>
     *
     * 【補足：】<BR>
     * 本メソッド毎フレーム実行することでXZ平面の円運動が可能になります。<BR>
     * 引数の移動方角（Y軸回転）が、数直線上の 0 に、より近い値を加算し続けた場合は、緩やかなカーブ描きながら向転換することを意味します。<BR>
     * 逆に、引数の移動方角（Y軸回転）が、0 から、より離れた値を加算し続けた場合は、より鋭角的なカーブ描きながら向転換することを意味します。<BR>
     * デフォルトのY軸移動加速度の上限と下限（_bottom_angvelo_ry_mv、_top_angvelo_ry_mv) は<BR>
     *
     *  -360,000 ≦ 引数の動方角増分 ≦ 360,000<BR>
     *
     * となっています。これは瞬時に（1フレームで）どんな移動方角（Y軸回転）にも向きを変えれることを意味します。<BR>
     *
     * @param   prm_ang 移動方角（Y軸回転）増分(範囲：_bottom_angvelo_ry_mv ～ _top_angvelo_ry_mv)
     */
    void addRyMvAng(angle prm_ang);

    angle getRyMvAng() {
        return _ry_mv;
    }

    /**
     * Actorの目標のY軸回転移動方角の自動停止機能を有効 .
     * 目標の移動方角（Y軸回転）設定する。<BR>
     * 引数に設定された移動方角（Y軸回転）になるまで、移動方角（Y軸回転）を加算(減算)を毎フレーム行い続けます。<BR>
     * 加算か減算かは、移動方角（Y軸回転）の角速度（_angvelo_ry_mv）の正負で決定されます。<BR>
     * <B>移動方角（Y軸回転）の角速度が 0 ならば、何も起こりません。</B>動作させるには、角速度が必要です。<BR>
     * 内部的には、addRyMvAng(int) が毎フレーム行われる仕組みです。(this->behave()で実行)<BR>
     * 目標の移動方角（Y軸回転）に到達したならば、この目標の移動方角（Y軸回転）自動停止機能は解除されます。<BR>
     *
     * @param   prm_target_ry_mv 到達目標の移動方角（Y軸回転）(-360,000～360,000)
     * @param   prm_allow_way  自動停止機能が有効になる進入回転方向
     * @param   prm_allow_angvelo 停止機能が有効になる移動方角角速度(これ以上の角速度の場合は停止しません)
     */
    void setStopTargetRyMvAng(angle prm_target_ry_mv,
                              int prm_allow_way = TURN_BOTH,
                              angvelo prm_allow_angvelo = D360ANG);

    void setRyMvAngVelo(angvelo prm_angvelo_ry_mv);

    void forceRyMvAngVeloRange(angvelo prm_angvelo_ry_mv01, angvelo prm_angvelo_ry_mv02);

    void setRyMvAngAcce(angacce prm_angacce_ry_mv);

    angle getRyMvAngDistanceTwd(coord prm_tx, coord prm_ty, int prm_way);

    angle getRyMvAngDistance(angle prm_target_ry_mv, int prm_way);


    void forceRzRyMvAngVeloRange(angvelo prm_angvelo_rzry_mv01, angvelo prm_angvelo_rzry_mv02);

    void setRzRyMvAngVelo(angvelo prm_angvelo_rz_mv, angvelo prm_angvelo_ry_mv);

    void setRzRyMvAngAcce(angacce prm_angacce_rz_mv, angacce prm_angacce_ry_mv);


    /**
     * 自身の移動方角のZ軸Y軸回転角(_rz_mv, _ry_mv)と、ターゲットの回転角との最適な差分を取得 .
     * 同じ方向を意味するもう一組の RzRy までの距離を割り出し、<BR>
     * 到達アングル数の少ない方の RzRy の組み合わせを自動採用する。<BR>
     * (注意：極地Y軸回転があるため、最小アングル差は必ずしも最短距離にあらず)<BR>
     * 所望の方向に最短フレームでターゲットするが、内部の _rz_mv, _ry_mv は<BR>
     * 引数のターゲットアングル値と一致しないかもしれない。(姿勢が異なる可能性有り)<BR>
     * 一致しないことが困る場合は、Z軸Y軸個別に距離を求めて下さい。<BR>
     * @param prm_target_rz
     * @param prm_target_ry
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param out_d_rz
     * @param out_d_ry
     */
    void getRzRyMvAngDistanceTwd(angle prm_target_rz, angle prm_target_ry,int prm_way,
                                 angle& out_d_rz, angle& out_d_ry);

    /**
     * 自身の軸回転方角のZ軸Y軸回転角(_face[AXIS_Z], _face[AXIS_Y])と、ターゲットの回転角との最適な差分を取得 .
     * 同じ方向を意味するもう一組の RzRy までの距離を割り出し、<BR>
     * 到達アングル数の少ない方の RzRy の組み合わせを自動採用する。<BR>
     * (注意：極地Y軸回転があるため、最小アングル差は必ずしも最短距離にあらず)<BR>
     * 所望の方向に最短フレームでターゲットするが、内部の _rz_mv, _ry_mv は<BR>
     * 引数のターゲットアングル値と一致しないかもしれない。(姿勢が異なる可能性有り)<BR>
     * 一致しないことが困る場合は、Z軸Y軸個別に距離を求めて下さい。<BR>
     * @param prm_target_rz
     * @param prm_target_ry
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param out_d_rz
     * @param out_d_ry
     */
    void getRzRyFaceAngDistanceTwd(angle prm_target_rz, angle prm_target_ry,int prm_way,
                                   angle& out_d_rz, angle& out_d_ry);
    /**
     * 移動方向(RzRy)を設定 .
     * @param prm_rz
     * @param prm_ry
     */
    void setRzRyMvAng(angle prm_rz, angle prm_ry);

    /**
     * 移動方向(RzRy)を方向ベクトルにより設定 .
     * @param prm_vx 方向ベクトルX軸要素
     * @param prm_vy 方向ベクトルY軸要素
     * @param prm_vz 方向ベクトルZ軸要素
     * @param prm_opt 最適化フラグ（true:RzRyの差が最小になるように最適化する／false:普通のコンバート)
     */
    void setRzRyMvAng(double prm_vx, double prm_vy, double prm_vz, bool prm_opt = false);

    /**
     *  移動方向(RzRy)を、RyRzで設定。
     * @param prm_ry
     * @param prm_rz
     */
    void setRzRyMvAngByRyRz(angle prm_ry, angle prm_rz);

    /**
     * 目標座標点を座標指定で移動方角(RzRy)を設定。.
     * 方向ベクトル正規化も内部で行なう。
     * @param prm_tx 目標X座標
     * @param prm_ty 目標Y座標
     * @param prm_tz 目標Z座標
     */
    void setMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz);

    /**
     * 目標座標点を座標指定で移動方角(RzRy)を設定。.
     * 但し奥行き(Z座標は)無視して計算を行う。
     * 方向ベクトル正規化も内部で行なう。
     * @param prm_tx 目標X座標
     * @param prm_ty 目標Y座標
     */
    inline void setMvAngTwd(coord prm_tx, coord prm_ty) {
        setMvAngTwd(prm_tx, prm_ty, _pActor->_z);
    }

    /**
     * 目標座標点指を対象アクターの座標指定で移動方角(RzRy)を設定。.
     * 方向ベクトル正規化も内部で行なう。
     * @param prm_pActor_target 目標対象アクター
     */
    inline void setMvAngTwd(const GeometricActor* prm_pActor_target) {
        setMvAngTwd(
            prm_pActor_target->_x,
            prm_pActor_target->_y,
            prm_pActor_target->_z
        );
    }

    inline void setMvAngTwd(const GeoElem* prm_pGeoElem) {
        setMvAngTwd(
            prm_pGeoElem->x,
            prm_pGeoElem->y,
            prm_pGeoElem->z
        );
    }

    void reverseMvAng();

    void setStopTargetMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz);

    void setStopTargetMvAngTwd(const GeometricActor* prm_pActor_target);

    /**
     * 軸回転方角(Z軸とY軸)を目標にターゲットするシークエンスを実行 .
     * @param prm_rz_target 目標軸回転方角(Z軸)
     * @param prm_ry_target 目標軸回転方角(Y軸)
     * @param prm_angvelo ターゲッティング遂行中に加算される角度、つまり角速度（正の角速度で指定。内部で正負自動判定）
     * @param prm_angacce 角加速度（正の角加速度で指定。内部で正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_optimize_ang ターゲットアングルを最適化するかどうかを指定。
     *                         true: 引数の prm_rz_target, prm_ry_target までの距離と、<BR>
     *                               同じ方向を意味するもう一組の RzRy までの距離を割り出し、<BR>
     *                               到達フレーム数の少ない方の RzRy の組み合わせを自動採用する。<BR>
     *                               (注意：極地Y軸回転があるため、最短フレームは必ずしも最短距離にあらず)<BR>
     *                               所望の方向に最短フレームでターゲットするが、内部の _rz_mv, _ry_mv は<BR>
     *                               引数のターゲットアングル値と一致しないかもしれない。(姿勢が異なる可能性有り)<BR>
     *                         false:引数の prm_rz_target, prm_ry_target をそのままターゲートとする。<BR>
     */
    void turnRzRyFaceAngTo(angle prm_rz_target, angle prm_ry_target,
                           angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                           int prm_way = TURN_CLOSE_TO,
                           bool prm_optimize_ang = false);

    /**
     * 軸回転方角を目標にターゲットするシークエンスを実行 .
     * @param prm_tx 目標X座標
     * @param prm_ty 目標Y座標
     * @param prm_tz 目標Z座標
     * @param prm_angvelo ターゲッティング遂行中に加算される角度、つまり角速度（正の角速度で指定。内部で正負自動判定）
     * @param prm_angacce 角加速度（正の角加速度で指定。内部で正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang ターゲットアングルを最適化するかどうかを指定。<BR>
     *                         true: 引数の prm_rz_target, prm_ry_target までの距離と、<BR>
     *                               同じ方向を意味するもう一組の RzRy までの距離を割り出し、<BR>
     *                               到達フレーム数の少ない方の RzRy の組み合わせを自動採用する。<BR>
     *                               所望の方向に最短フレームでターゲットするが、内部の _rz_mv, _ry_mv は<BR>
     *                               引数のターゲットアングル値と一致しないかもしれない。(姿勢が異なる可能性有り)<BR>
     *                               (注意：極地Y軸回転があるため、最短フレームは必ずしも最短距離にあらず)<BR>
     *                         false:引数の prm_rz_target, prm_ry_target をそのままターゲートとする。<BR>
     */
    void turnFaceAngTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                        angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                        int prm_way = TURN_CLOSE_TO,
                        bool prm_optimize_ang = false);


    /**
     * 軸回転方角(Z軸とY軸)を目標にターゲットの方向を向くようなシークエンスを実行
     * @param prm_pActor_target 目標オブジェクト
     * @param prm_angvelo ターゲッティング遂行中に加算される角度、つまり角速度（正の角速度で指定。内部で正負自動判定）
     * @param prm_angacce 角加速度（正の角加速度で指定。内部で正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_optimize_ang ターゲットアングルを最適化するかどうかを指定。<BR>
     *                         true: 引数の prm_rz_target, prm_ry_target までの距離と、<BR>
     *                               同じ方向を意味するもう一組の RzRy までの距離を割り出し、<BR>
     *                               到達フレーム数の少ない方の RzRy の組み合わせを自動採用する。<BR>
     *                               所望の方向に最短フレームでターゲットするが、内部の _rz_mv, _ry_mv は<BR>
     *                               引数のターゲットアングル値と一致しないかもしれない。(姿勢が異なる可能性有り)<BR>
     *                               (注意：極地Y軸回転があるため、最短フレームは必ずしも最短距離にあらず)<BR>
     *                         false:引数の prm_rz_target, prm_ry_target をそのままターゲートとする。<BR>
     */
    inline void turnFaceAngTwd(const GeometricActor* prm_pActor_target,
                               angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                               int prm_way = TURN_CLOSE_TO,
                               bool prm_optimize_ang = false) {
        turnFaceAngTwd(
                prm_pActor_target->_x,
                prm_pActor_target->_y,
                prm_pActor_target->_z,
                prm_angvelo,
                prm_angacce,
                prm_way,
                prm_optimize_ang
        );
    }
    inline void turnFaceAngTwd(const GeoElem* prm_pGeoElem,
                               angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                               int prm_way = TURN_CLOSE_TO,
                               bool prm_optimize_ang = false) {
        turnFaceAngTwd(
                prm_pGeoElem->x,
                prm_pGeoElem->y,
                prm_pGeoElem->z,
                prm_angvelo,
                prm_angacce,
                prm_way,
                prm_optimize_ang
        );
    }

    /**
     * 軸回転方角を目標の角距離回転させるシークエンスを実行 .
     * @param prm_axis  軸 (AXIS_X or AXIS_Y or AXIS_Z)
     * @param prm_distance 角距離（正：TURN_COUNTERCLOCKWISE、負：TURN_CLOCKWISE）
     * @param prm_angvelo 角速度（prm_distanceの正負に依存）
     * @param prm_angacce 角加速度（prm_distanceの正負に依存）
     */
    void turnFaceAng(axis prm_axis,
                     angle prm_distance,
                     angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0);

    /**
     * 軸回転方角(Z軸)を目標にターゲットするシークエンスを実行 .
     * @param prm_rz_target 目標軸回転方角(Z軸)
     * @param prm_angvelo ターゲッティング遂行中に加算される角度、つまり角速度（正の角速度で指定。内部で正負自動判定）
     * @param prm_angacce 角加速度（正の角加速度で指定。内部で正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void turnRzFaceAngTo(angle prm_rz_target,
                         angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                         int prm_way = TURN_CLOSE_TO);

    /**
     * 軸回転方角(Y軸)を目標にターゲットするシークエンスを実行 .
     * @param prm_ry_target 目標軸回転方角(Y軸)
     * @param prm_angvelo ターゲッティング遂行中に加算される角度、つまり角速度（正の角速度で指定。内部で正負自動判定）
     * @param prm_angacce 角加速度（正の角加速度で指定。内部で正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void turnRyFaceAngTo(angle prm_ry_target,
                         angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                         int prm_way = TURN_CLOSE_TO);

    /**
     * 軸回転方角(X軸)を目標にターゲットするシークエンスを実行 .
     * @param prm_rx_target 目標軸回転方角(X軸)
     * @param prm_angvelo ターゲッティング遂行中に加算される角度、つまり角速度（正の角速度で指定。内部で正負自動判定）
     * @param prm_angacce 角加速度（正の角加速度で指定。内部で正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void rollFaceAngTo(angle prm_rx_target,
                       angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                       int prm_way = TURN_CLOSE_TO);

    /**
     * 移動方角を目標にターゲットするシークエンスを実行 .
     * @param prm_rz_target 目標移動方角(Z軸)
     * @param prm_ry_target 目標移動方角(Y軸)
     * @param prm_angvelo ターゲッティング遂行中に加算される角度、つまり角速度（正の角速度で指定。内部で正負自動判定）
     * @param prm_angacce 角加速度（正の角加速度で指定。内部で正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang ターゲットアングルを最適化するかどうかを指定。<BR>
     *                         true: 引数の prm_rz_target, prm_ry_target までの距離と、<BR>
     *                               同じ方向を意味するもう一組の RzRy までの距離を割り出し、<BR>
     *                               到達フレーム数の少ない方の RzRy の組み合わせを自動採用する。<BR>
     *                               所望の方向に最短フレームでターゲットするが、内部の _rz_mv, _ry_mv は<BR>
     *                               引数のターゲットアングル値と一致しないかもしれない。(姿勢が異なる可能性有り)<BR>
     *                               (注意：極地Y軸回転があるため、最短フレームは必ずしも最短距離にあらず)<BR>
     *                         false:引数の prm_rz_target, prm_ry_target をそのままターゲートとする。<BR>
     */
    void turnRzRyMvAngTo(angle prm_rz_target, angle prm_ry_target,
                         angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                         int prm_way = TURN_CLOSE_TO,
                         bool prm_optimize_ang = false);

    /**
     * 移動方角を目標にターゲットするシークエンスを実行 .
     * @param prm_tx 目標X座標
     * @param prm_ty 目標Y座標
     * @param prm_tz 目標Z座標
     * @param prm_angvelo ターゲッティング遂行中に加算される角度、つまり角速度（正の角速度で指定。内部で正負自動判定）
     * @param prm_angacce 角加速度（正の角加速度で指定。内部で正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang ターゲットアングルを最適化するかどうかを指定。<BR>
     *                         true: 引数の prm_rz_target, prm_ry_target までの距離と、<BR>
     *                               同じ方向を意味するもう一組の RzRy までの距離を割り出し、<BR>
     *                               到達フレーム数の少ない方の RzRy の組み合わせを自動採用する。<BR>
     *                               所望の方向に最短フレームでターゲットするが、内部の _rz_mv, _ry_mv は<BR>
     *                               引数のターゲットアングル値と一致しないかもしれない。(姿勢が異なる可能性有り)<BR>
     *                               (注意：極地Y軸回転があるため、最短フレームは必ずしも最短距離にあらず)<BR>
     *                         false:引数の prm_rz_target, prm_ry_target をそのままターゲートとする。<BR>
     */
    void turnMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                      angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                      int prm_way = TURN_CLOSE_TO,
                      bool prm_optimize_ang = false);

    /**
     * 移動方角を常に目標にターゲットするシークエンスを実行 .
     * @param prm_tx 目標X座標
     * @param prm_ty 目標Y座標
     * @param prm_tz 目標Z座標
     * @param prm_angvelo ターゲッティング遂行中に加算される角度、つまり角速度（正の角速度で指定。内部で正負自動判定）
     * @param prm_angacce 角加速度（正の角加速度で指定。内部で正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang ターゲットアングルを最適化するかどうかを指定。<BR>
     *                         true: 引数の prm_rz_target, prm_ry_target までの距離と、<BR>
     *                               同じ方向を意味するもう一組の RzRy までの距離を割り出し、<BR>
     *                               到達フレーム数の少ない方の RzRy の組み合わせを自動採用する。<BR>
     *                               所望の方向に最短フレームでターゲットするが、内部の _rz_mv, _ry_mv は<BR>
     *                               引数のターゲットアングル値と一致しないかもしれない。(姿勢が異なる可能性有り)<BR>
     *                               (注意：極地Y軸回転があるため、最短フレームは必ずしも最短距離にあらず)<BR>
     *                         false:引数の prm_rz_target, prm_ry_target をそのままターゲートとする。<BR>
     */
    void keepOnTurningFaceAngTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                                 angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                                 int prm_way = TURN_CLOSE_TO,
                                 bool prm_optimize_ang = false) {
        turnFaceAngTwd(prm_tx, prm_ty, prm_tz,
                       prm_angvelo,  prm_angacce,
                       prm_way, prm_optimize_ang );
        _taget_face_alltime_flg = true;
        _taget_face_alltime_pActor = nullptr;
        _taget_face_alltime_tx = prm_tx;
        _taget_face_alltime_ty = prm_ty;
        _taget_face_alltime_tz = prm_tz;
        _taget_face_alltime_angvelo = prm_angvelo;
        _taget_face_alltime_angacce = prm_angacce;
        _taget_face_alltime_way = prm_way;
        _taget_face_alltime_optimize_ang = prm_optimize_ang;
    }

    /**
     * 移動方角を常に目標にターゲットするシークエンスを実行 .
     * @param prm_pActor_target 目標オブジェクト
     * @param prm_angvelo ターゲッティング遂行中に加算される角度、つまり角速度（正の角速度で指定。内部で正負自動判定）
     * @param prm_angacce 角加速度（正の角加速度で指定。内部で正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang ターゲットアングルを最適化するかどうかを指定。<BR>
     *                         true: 引数の prm_rz_target, prm_ry_target までの距離と、<BR>
     *                               同じ方向を意味するもう一組の RzRy までの距離を割り出し、<BR>
     *                               到達フレーム数の少ない方の RzRy の組み合わせを自動採用する。<BR>
     *                               所望の方向に最短フレームでターゲットするが、内部の _rz_mv, _ry_mv は<BR>
     *                               引数のターゲットアングル値と一致しないかもしれない。(姿勢が異なる可能性有り)<BR>
     *                               (注意：極地Y軸回転があるため、最短フレームは必ずしも最短距離にあらず)<BR>
     *                         false:引数の prm_rz_target, prm_ry_target をそのままターゲートとする。<BR>
     */
    void keepOnTurningFaceAngTwd(const GeometricActor* prm_pActor_target,
                                 angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                                 int prm_way = TURN_CLOSE_TO,
                                 bool prm_optimize_ang = false) {
        keepOnTurningFaceAngTwd(
                prm_pActor_target->_x,
                prm_pActor_target->_y,
                prm_pActor_target->_z,
                prm_angvelo, prm_angacce,
                prm_way, prm_optimize_ang);
        _taget_face_alltime_pActor = prm_pActor_target;
    }

    /**
     * 移動方角を目標にターゲットの座標にするシークエンスを実行
     * @param prm_pActor_target 目標オブジェクト
     * @param prm_angvelo ターゲッティング遂行中に加算される角度、つまり角速度（正の角速度で指定。内部で正負自動判定）
     * @param prm_angacce 角加速度（正の角加速度で指定。内部で正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang ターゲットアングルを最適化するかどうかを指定。<BR>
     *                         true: 引数の prm_rz_target, prm_ry_target までの距離と、<BR>
     *                               同じ方向を意味するもう一組の RzRy までの距離を割り出し、<BR>
     *                               到達フレーム数の少ない方の RzRy の組み合わせを自動採用する。<BR>
     *                               所望の方向に最短フレームでターゲットするが、内部の _rz_mv, _ry_mv は<BR>
     *                               引数のターゲットアングル値と一致しないかもしれない。(姿勢が異なる可能性有り)<BR>
     *                               (注意：極地Y軸回転があるため、最短フレームは必ずしも最短距離にあらず)<BR>
     *                         false:引数の prm_rz_target, prm_ry_target をそのままターゲートとする。<BR>
     */
    inline void turnMvAngTwd(const GeometricActor* prm_pActor_target,
                             angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                             int prm_way = TURN_CLOSE_TO,
                             bool prm_optimize_ang = false) {
        turnMvAngTwd(
                prm_pActor_target->_x,
                prm_pActor_target->_y,
                prm_pActor_target->_z,
                prm_angvelo,
                prm_angacce,
                prm_way,
                prm_optimize_ang
        );
    }

    inline void turnMvAngTwd(const GeoElem* prm_pGeoElem,
                             angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                             int prm_way = TURN_CLOSE_TO,
                             bool prm_optimize_ang = false) {
        turnMvAngTwd(
                prm_pGeoElem->x,
                prm_pGeoElem->y,
                prm_pGeoElem->z,
                prm_angvelo,
                prm_angacce,
                prm_way,
                prm_optimize_ang
        );
    }

    /**
     * 移動方角(Z軸)を目標の角距離回転させるシークエンスを実行 .
     * @param prm_rz_distance  移動方角の回転角距離(Z軸)
     * @param prm_angvelo ターゲットへ移動方角を回転移動中に適用する角速度（正負はprm_distanceの正負に依存）
     * @param prm_angacce 角加速度（正負はprm_distanceの正負に依存）
     */
    void turnRzMvAng(angle prm_rz_distance,
                     angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0);

    /**
     * 移動方角(Y軸)を目標の角距離回転させるシークエンスを実行 .
     * @param prm_ry_distance  移動方角の回転角距離(Y軸)
     * @param prm_angvelo ターゲットへ移動方角を回転移動中に適用する角速度（正負はprm_distanceの正負に依存）
     * @param prm_angacce 角加速度（正負はprm_distanceの正負に依存）
     */
    void turnRyMvAng(angle prm_ry_distance,
                     angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0);

    /**
     * 移動方角(Z軸)を目標にターゲットするシークエンスを実行 .
     * @param prm_rz_target 目標移動方角(Z軸)
     * @param prm_angvelo ターゲットへ移動方角を回転移動中に適用する角速度（正の角速度で指定。内部で正負自動判定）
     * @param prm_angacce 角加速度（正の角加速度で指定。内部で正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void turnRzMvAngTo(angle prm_rz_target,
                       angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                       int prm_way = TURN_CLOSE_TO);

    /**
     * 移動方角(Y軸)を目標にターゲットするシークエンスを実行 .
     * @param prm_ry_target 目標移動方角(Y軸)
     * @param prm_angvelo ターゲットへ移動方角を回転移動中に適用する目標移動方角回転移動角速度（正の角速度で指定。内部で正負自動判定）
     * @param prm_angacce 角加速度（正の角加速度で指定。内部で正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void turnRyMvAngTo(angle prm_ry_target,
                       angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                       int prm_way = TURN_CLOSE_TO);

    void stopTurningMvAng();

    void stopTurningFaceAng();

    /**
     * 目標軸回転方角にターゲットするシークエンスが実行中か .
     * turn**FaceAng**() を実行後、所望の目標移動方角に回転中の場合 true。
     * @return true:実行中/false:実行中でない
     */
    bool isTurningFaceAng() const;

    /**
     * 目標移動方角にターゲットするシークエンスが実行中か .
     * turn**MvAng**() を実行後、所望の目標移動方角に回転中の場合 true。
     * @return true:実行中/false:実行中でない
     */
    bool isTurningMvAng() const;

    /**
     * 移動方角に伴って軸回転方角を更新（Z軸回転と、Y軸回転両方） .
     * true を設定すると、自動的に移動方角の方に向きが変わる。<BR>
     * false を設定すると、移動方角と向きは独立、デフォルトはこちら。<BR>
     * @param prm_b true:移動方角に伴って軸回転方角を更新/false:移動方角と軸回転方角は独立
     */
    void linkFaceAngByMvAng(bool prm_b) {
        _relate_RyFaceAng_with_RyMvAng_flg = prm_b;
        _relate_RzFaceAng_with_RzMvAng_flg = prm_b;
        if (prm_b) {
            _pActor->_rz = _rz_mv;
            _pActor->_ry = _ry_mv;
        }
    }

    /**
     * 移動方角に伴って軸回転方角を更新（Z軸回転のみ） .
     * true を設定すると、Z軸回転のみ自動的に移動方角の方に向きが変わる。<BR>
     * false を設定すると、移動方角と向きは独立、デフォルトはこちら。<BR>
     * @param prm_b true:Z軸回転について移動方角に伴って軸回転方角を更新/false:移動方角と軸回転方角は独立
     */
    void linkRzFaceAngByMvAng(bool prm_b) {
        _relate_RzFaceAng_with_RzMvAng_flg = prm_b;
        if (prm_b) {
            _pActor->_rz = _rz_mv;
        }
    }

    /**
     * 移動方角に伴って軸回転方角を更新（Y軸回転のみ） .
     * true を設定すると、Y軸回転のみ自動的に移動方角の方に向きが変わる。<BR>
     * false を設定すると、移動方角と向きは独立、デフォルトはこちら。<BR>
     * @param prm_b true:Y軸回転について移動方角に伴って軸回転方角を更新/false:移動方角と軸回転方角は独立
     */
    void linkRyFaceAngByMvAng(bool prm_b) {
        _relate_RyFaceAng_with_RyMvAng_flg = prm_b;
        if (prm_b) {
            _pActor->_ry = _ry_mv;
        }
    }

    /**
     * 力車の仕事を引継ぐ .
     * 他の VecVehicle オブジェクトを状態を自身に引継ぐ .
     * @param prm_pVecVehicle 引継元
     */
    void takeoverFrom(VecVehicle* const prm_pVecVehicle);

    /**
     * 移動を停止します。
     */
    void stop();

    /**
     * 力車が振る舞う .
     * 力車機能を利用する場合は、このメソッドを毎フレーム呼び出し実行してください。<BR>
     * 逆に力車を必要としない場合は、このメソッドを呼び出さないことで、パフォーマンスに影響を与えません。<BR>
     */
    virtual void behave();

    virtual ~VecVehicle();
};

}
#endif /*GGAF_DX_VECVEHICLE_H_*/

