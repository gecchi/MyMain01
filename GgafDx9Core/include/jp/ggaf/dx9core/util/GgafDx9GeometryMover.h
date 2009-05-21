#ifndef GGAFDX9GEOMETRYMOVER_H_
#define GGAFDX9GEOMETRYMOVER_H_
namespace GgafDx9Core {

//近い方向に回転
#define TURN_CLOSE_TO 0
//時計回りに回転
#define TURN_CLOCKWISE (-1)
//反時計回りに回転
#define TURN_COUNTERCLOCKWISE 1
//回転どちらでも
#define TURN_BOTH 0

//軸X
#define AXIS_X 0
//軸Y
#define AXIS_Y 1
//軸Z
#define AXIS_Z 2

typedef int velo;
typedef int acce;
typedef int angvelo;
typedef int angacce;


enum ScalingMethod {
    NOSCALE,
    TARGET_SCALE_LINER,
    BEAT_SCALE_LINER,
    BEAT_SCALE_TRIANGLEWAVE,
    TARGET_SCALE_SIN,
    BEAT_SCALE_SIN,
    TARGET_SCALE_ACCELERATION,
    BEAT_SCALE_PARABOLA,
    TARGET_SCALE_PARABOLA_REV,
    BEAT_SCALE_PARABOLA_REV
};

/**
 * 座標計算支援クラス.
 * GgafDx9UntransformedActor のメンバの<BR>
 *  _X ,  _Y,  _Z  ･･･ アクターの座標<BR>
 * _RX , _RY, _RZ  ･･･ アクターの軸回転角度<BR>
 * _SX , _SY, _SZ  ･･･ アクターのスケール<BR>
 * を、簡単に操作するために設計した。<BR>
 */
class GgafDx9GeometryMover : public GgafCore::GgafObject {
    double _dummy1, _dummy2, _dummy3;

public: //_SX , _SY, _SZ 操作関連 //////////////////////////////////////////////
    /** 対象アクター */
    GgafDx9UntransformedActor* _pActor;

    /** スケール(1000 で 1倍) */
    int _scale[3]; //[0]:X軸スケール、[1]:Y軸スケール、[1]:Z軸スケール
    /** 目標のスケール */
    int _target_scale[3];
    /** スケール上限 */
    int _top_scale[3];
    /** スケール下限 */
    int _bottom_scale[3];
    /** 毎フレームのスケールの増分 */
    int _velo_scale[3];
    /** 毎フレームのスケールの増分の増分 */
    int _acce_scale[3];
    /** 三角波の波形でスケーリングのアタックフレーム */
    DWORD _beat_scaling_attack_frame[3];
    /** 三角波の波形でスケーリングのレストフレーム */
    DWORD _beat_scaling_rest_frame[3];
    /** スケーリングに費やすフレーム数 */
    DWORD _beat_scaling_spend_frame[3];
    /** スケーリングを開始したフレーム */
    DWORD _beat_scaling_begin_frame[3];
    /** ループカウント（2で拡大縮小ワンセット、1ならば拡大or縮小の片道） */
    int _one_way_scaling_cnt[3];
    /** ストップする予定のループカウント */
    int _stop_one_way_scaling_num[3];
    /** スケーリング方法 */
    ScalingMethod _scaling_method[3];

    void addScale(int prm_scale_diff) {
        for (int axis = 0; axis < 3; axis++) {
            addScale(axis, prm_scale_diff);
        }
    }

    void addScale(int prm_axis, int prm_scale_diff) {
        setScale(prm_axis, _scale[prm_axis] + prm_scale_diff);
    }


    void setScale(int prm_scale) {
        for (int axis = 0; axis < 3; axis++) {
            setScale(axis, prm_scale);
        }
   }

    void setScale(int prm_axis, int prm_scale) {
        if (_top_scale[prm_axis] < prm_scale) {
            _scale[prm_axis] = _top_scale[prm_axis];
        } else if (_bottom_scale[prm_axis] > prm_scale) {
            _scale[prm_axis] = _bottom_scale[prm_axis];
        } else {
            _scale[prm_axis] = prm_scale;
        }
    }
    /**
     * スケーリングの上限下限を設定（全軸指定）
     * @param prm_scale1
     * @param prm_scale2
     */
    void setScalingRange(int prm_scale1, int prm_scale2) {
        for (int axis = 0; axis < 3; axis++) {
            setScalingRange(axis, prm_scale1, prm_scale2);
        }
    }
    /**
     * スケーリングの上限下限を設定（軸ごとに指定）
     * @param prm_axis 軸
     * @param prm_scale1
     * @param prm_scale2
     */
    void setScalingRange(int prm_axis, int prm_scale1, int prm_scale2) {
        if (prm_scale1 < prm_scale2) {
            _bottom_scale[prm_axis] = prm_scale1;
            _top_scale[prm_axis] = prm_scale2;
        } else {
            _bottom_scale[prm_axis] = prm_scale1;
            _top_scale[prm_axis] = prm_scale2;
        }
    }

    void resetScaling() {
        for (int axis = 0; axis < 3; axis++) {
            resetScaling(axis);
        }
    }
    void resetScaling(int prm_axis) {
        _scale[prm_axis] = _bottom_scale[prm_axis];
    }

    void resetTopScaling() {
        for (int axis = 0; axis < 3; axis++) {
            resetTopScaling(axis);
        }
    }
    void resetTopScaling(int prm_axis) {
        _scale[prm_axis] = _top_scale[prm_axis];
    }


    void stopScalingImmediately();
    void stopScalingImmediately(int prm_axis);

    /**
     * 目標のスケールへ一定速度でスケーリングする（フレーム数指定） .
     * @param prm_target_scale 目標スケール
     * @param prm_spend_frame 費やすフレーム数
     */
    void intoTargetScaleLinerUntil(int prm_target_scale, DWORD prm_spend_frame);

    /**
     * 目標のスケールへ一定速度でスケーリングする（フレーム数指定） .
     * @param prm_axis 軸
     * @param prm_target_scale 目標スケール
     * @param prm_spend_frame 費やすフレーム数
     */
    void intoTargetScaleLinerUntil(int prm_axis, int prm_target_scale, DWORD prm_spend_frame);

    /**
     * 目標のスケールへ一定速度でスケーリングする（スケール差分指定） .
     * @param prm_target_scale 目標スケール
     * @param prm_velo_scale 毎フレーム加算するスケール差分(>0.0)。正のスケールを指定する事。加算か減算かは自動判断する。
     */
    void intoTargetScaleLinerStep(int prm_target_scale, int prm_velo_scale);

    /**
     * 目標のスケールへ一定速度でスケーリングする（スケール差分指定） .
     * @param prm_axis 軸
     * @param prm_target_scale 目標スケール
     * @param prm_velo_scale 毎フレーム加算するスケール差分(>0.0)。正のスケールを指定する事。加算か減算かは自動判断する。
     */
    void intoTargetScaleLinerStep(int prm_axis, int prm_target_scale, int prm_velo_scale);

    /**
     * 目標のスケールへ加速指定でスケーリングする（スケール速度、スケール加速度差指定） .
     * スケール加速度を0に指定すると intoTargetScaleLinerStep とほぼ同じ意味になる。
     * intoTargetScaleLinerStep の第３引数は正負を気にすること無いが、本メソッドは正負の自動判定はしない（できない）。
     * @param prm_target_scale 目標スケール
     * @param prm_velo_scale 初期スケール速度
     * @param prm_acce_scale スケール加速度
     */
    void intoTargetScaleAccelerationStep(int prm_target_scale, int prm_velo_scale, int prm_acce_scale);

    /**
     * 目標のスケールへ加速指定でスケーリングする（スケール速度、スケール加速度差指定） .
     * スケール加速度を0に指定すると intoTargetScaleLinerStep とほぼ同じ意味になる。
     * intoTargetScaleLinerStep の第３引数は正負を気にすること無いが、本メソッドは正負の自動判定はしない（できない）。
     * @param prm_axis 軸
     * @param prm_target_scale 目標スケール
     * @param prm_velo_scale 初期スケール速度
     * @param prm_acce_scale スケール加速度
     */
    void intoTargetScaleAccelerationStep(int prm_axis, int prm_target_scale, int prm_velo_scale, int prm_acce_scale);

    /**
     * 目標のスケールへ一定速度でスケーリングし、一定速度で元に戻る。これをループ指定する。（１ループのフレーム数指定） .
     * @param prm_beat_scaling_spend_frame １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_beat_num ループする回数(0.5 回単位で指定可能)
     */
    void beatScalingLiner(DWORD prm_beat_scaling_spend_frame, float prm_beat_num);

    /**
     * 目標のスケールへ一定速度でスケーリングし、一定速度で元に戻る。これをループ指定する。（１ループのフレーム数指定） .
     * @param prm_axis 軸
     * @param prm_beat_scaling_spend_frame １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_beat_num ループする回数(0.5 回単位で指定可能)
     */
    void beatScalingLiner(int prm_axis, DWORD prm_beat_scaling_spend_frame, float prm_beat_num);

    /**
     * 三角波の波形でスケーリングする。.
     * <PRE>
     * ④  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
     *            /＼                     /＼
     *           /   ＼                  /   ＼
     *          /      ＼               /      ＼
     *         /         ＼            /         ＼
     *        /            ＼         /            ＼
     * ⑤  ＿/               ＼＿＿＿/               ＼＿
     *
     *       ←②→            ←③→
     *       ←──── ① ────→
     * </PRE>
     * ＜必要な設定値＞<BR>
     * ① １ループのフレーム数<BR>
     * ② アタックまでのフレーム数<BR>
     * ③ 休憩フレーム数<BR>
     * ④ スケール上限(_top_scale[prm_axis] が保持)<BR>
     * ⑤ スケール下限(_bottom_scale[prm_axis] が保持)<BR>
     * <BR>
     * @param prm_beat_scaling_spend_frame 上図で①のフレーム数
     * @param prm_attack_frame 上図で②のフレーム数
     * @param prm_rest_frame 上図で③のフレーム数
     * @param prm_beat_num ループ数(-1で無限)
     */
    void beatScalingAlongTriangleWave(
                          DWORD prm_beat_scaling_spend_frame,
                          DWORD prm_attack_frame,
                          DWORD prm_rest_frame,
                          float prm_beat_num);
    /**
     * 三角波の波形でスケーリングする。.
     * @param prm_axis 軸
     * @param prm_beat_scaling_spend_frame 上図で①のフレーム数
     * @param prm_attack_frame 上図で②のフレーム数
     * @param prm_rest_frame 上図で③のフレーム数
     * @param prm_beat_num ループ数(-1で無限)
     */
    void beatScalingAlongTriangleWave(int prm_axis,
                          DWORD prm_beat_scaling_spend_frame,
                          DWORD prm_attack_frame,
                          DWORD prm_rest_frame,
                          float prm_beat_num);


public: //_RX , _RY, _RZ 操作関連 //////////////////////////////////////////////

    /** キャラの軸回転方角の方角(0～360,000) */
    angle _angRot[3];
    /** 軸回転方角の角速度（軸回転方角に毎フレーム加算する方角） */
    angvelo _angveloRot[3];
    /** 軸回転方角の角速度上限(最高値は360,000) */
    angvelo _angveloTopRot[3];
    /** 軸回転方角の角速度下限(最高値は-360,000) */
    angvelo _angveloBottomRot[3];
    /** 軸回転方角の角加速度（角速度に毎フレーム加算する値） */
    angacce _angacceRot[3];
    /** 目標の軸回転方角自動停止機能有効フラグ */
    bool _rot_angle_targeting_flg[3];
    /** 目標とするキャラの軸回転方角の方角(0～360,000) */
    angle _angTargetRot[3];
    /** 目標の軸回転方角自動停止機能が有効になる回転方向 */
    int _rot_angle_target_allow_way[3]; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** 目標の軸回転方角自動停止機能が有効になる角速度（回転正負共通） */
    angvelo _rot_angle_target_allow_velocity[3]; //この角速度より小さい値の場合機能有効とするz

    /**
     * コンストラクタ<BR>
     * @param	prm_pActor	適用Actor
     */
    GgafDx9GeometryMover(GgafDx9UntransformedActor* prm_pActor);

    /**
     * アングル値を単純化する。
     * 負のアングル値、又は360,000以上のアングル値を、0～269,999 に変換します。
     * @param prm_ang 方角
     * @return 単純化されたアングル値
     */
    static angle simplifyAngle(angle prm_ang);

    /**
     * Actorの軸の回転方角を設定。<BR>
     *
     * @param	prm_axis	回転軸(AXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angRot	方角のアングル値(-360,000～360,000)
     */
    void setRotAngle(int prm_axis, angle prm_angRot);

    /**
     * Actorの軸の回転方角を対象座標に向ける。<BR>
     * 引数の座標をに向くようにZ軸Y軸（Rz と Ry）の回転値を設定します。
     * @param prm_tX 対象X座標
     * @param prm_tY 対象Y座標
     * @param prm_tZ 対象Z座標
     */
    void setRotAngle(int prm_tX, int prm_tY, int prm_tZ);

    /**
     * 現在の Actor の軸回転方角へ加算（負で減算）。<BR>
     *
     * 引数に渡すのは、軸回転方角の増分です。Actorの軸回転方角（_angRot）を相対指定でるメソッドです。<BR>
     * 加算後の軸回転方角のアングル値はが単純化されます。
     * 引数である加算（減算）する軸回転方角は、軸回転角角速度の上限と下限の間の範囲に限ります。<BR>
     * つまり、引数の有効な範囲は以下の通りとなります。<BR>
     *
     *   _iBottom_RotVelocityAngle ≦ 引数の回転軸方角値の増分 ≦ _angveloTopRot  です。<BR>
     *
     * もし加算（減算）後、範囲外になった場合、直近の範囲内の値に強制的に抑えられます。<BR>
     * 【補足：】<BR>
     * デフォルトの回転加速度の上限と下限（_iBottom_RotVelocityAngle、_angveloTopRot) は<BR>
     *
     *  -360,000 ≦ 引数の動方角増分 ≦ 360,000<BR>
     *
     * @param	prm_axis	回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angDistance	回転軸方角値の増分アングル値(範囲：_iBottom_RotVelocityAngle ～ _angveloTopRot)
     */
    void addRotAngle(int prm_axis, angle prm_angDistance);

    /**
     * Actorの目標の軸回転方角自動停止機能を有効(目標の軸回転方角設定)<BR>
     * 引数に設定された軸回転方角になると、軸回転方角角速度及び軸回転方角角加速度を 0 にし、回転を停止させます。<BR>
     * 軸回転方角角速度等の設定を併せて実行して、まずは軸回転も行なってください。<BR>
     * 軸回転方角角速度が 0 の場合、何も起こりません。本メソッドを実行したからと言って勝手に向きが変わるとという意味ではありません。 <BR>
     * 内部的には、addRotAngle(prm_axis, int) が毎フレーム行われる仕組みです。<BR>
     * 目標の回転方角に到達したならば、この目標の軸回転方角自動停止機能は解除(内部のフラグをアンセット)されます。<BR>
     * @param	prm_axis	回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angRzMove	到達目標の回転方角(0～360,000)
     * @param	prm_way_allow  自動停止を許可する進入方向(TURN_CLOCKWISE/TURN_COUNTERCLOCKWISE/TURN_BOTH)
     * @param	prm_angveloAllowRyMove 自動停止機能が有効になる回転角速度
     */
    void setTargetRotAngle(int prm_axis,
                           angle prm_angTargetRot,
                           int prm_way_allow = TURN_BOTH,
                           angvelo prm_angveloAllow = ANGLE180);

    /**
     * Actorの目標回転方向自動停止機能を有効(現在XY座標からの対象XY座標で設定)<BR>
     * @param	prm_axis	回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_tX	対象X座標
     * @param	prm_tY	対象Y座標
     * @param	prm_way_allow  自動停止機能が有効になる回転方向
     * @param	prm_angveloAllowRyMove 自動停止機能が有効になる回転角速度
     */
    void setTargetRotAngleV(int prm_axis,
                                int prm_tX,
                                int prm_tY,
                                int prm_way_allow = TURN_BOTH,
                                angvelo prm_angveloAllowRyMove = ANGLE180);

    void setRotAngleVelocity(int prm_axis, angvelo prm_angveloRot);

    void setRotAngleVelocityRenge(int prm_axis,
                                  angvelo prm_angveloRot01,
                                  angvelo prm_angveloRot02);

    void setRotAngleAcceleration(int prm_axis, angacce prm_angacceRot);

    angle getDifferenceFromRotAngleTo(int prm_axis, int prm_tX, int prm_tY, int prm_way);

    angle getDifferenceFromRotAngleTo(int prm_axis, angle prm_angTargetRot, int prm_way);

    ////////////////////////////////////////////////////MOVER

public: //_X , _Y, _Z 操作関連 //////////////////////////////////////////////
    /** キャラの移動方角単位ベクトル */
    double _vX, _vY, _vZ;
    /** 移動方角のZ軸回転角 */
    angle _angRzMove;
    /** 移動方角のY軸回転角 */
    angle _angRyMove;
    /** 移動速度 */
    velo _veloMove;
    /** 移動速度上限 */
    velo _veloTopMove;
    /** 移動速度下限 */
    velo _veloBottomMove;
    /** 移動加速度 */
    acce _accMove;

    ///////コピー元begin
    /** 移動方角（Z軸回転）の角速度（移動方角（Z軸回転）に毎フレーム加算する方角） */
    angvelo _angveloRzMove;
    /** 移動方角（Z軸回転）の角速度上限(最高値は360,000) */
    angvelo _angveloRzTopMove;
    /** 移動方角（Z軸回転）の角速度下限(最高値は-360,000) */
    angvelo _angveloRzBottomMove;
    /** 移動方角（Z軸回転）の角加速度（角速度に毎フレーム加算する値） */
    angacce _angacceRzMove;
    /** 目標の移動方角（Z軸回転）自動停止機能有効フラグ */
    bool _move_angle_rz_target_flg;
    /** 目標とするキャラの移動方角（Z軸回転）の方角(0～360,000) */
    angle _angTargetRzMove;
    /** 目標の移動方角（Z軸回転）自動停止機能が有効になる進入回転方向 */
    int _move_angle_rz_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** 目標の移動方角（Z軸回転）自動停止機能が有効になる移動方角角速度 */
    angvelo _move_angle_rz_target_allow_velocity;
    /** 自動前方向き機能有効フラグ */
    bool _synchronize_ZRotAngle_to_RzMoveAngle_flg;
    //true  : 移動方角（Z軸回転）を変更すると、それに伴い同じ方角が軸回転方角(Z軸)にも設定される
    //false : 移動方角（Z軸回転）とZ軸軸回転方角は独立

    //【自分メモ】
    //＜軸回転方角、移動方角について＞
    //「軸回転方角」はキャラの向きのみを表せる。
    //「移動方角」はキャラの進行方向のみを表せる。
    //画面でキャラクタが上から下へ移動しても、下を向くとは限らない。
    //右にキャラを向かせてから移動開始としても、左に移動するかもしれない。それぞれ設定が必要。
    //
    //＜Z軸回転角、Y軸回転角という言葉について＞
    //「移動方角」の方向は、原点から単位球の表面に向かって伸びるベクトルで表す。
    //方向ベクトルは単位球の表面を座標指定(_vX, _vY, _vZ)と、緯度経度の座標のどちらでも指定するこできるようにしている。
    //ここで緯度経度表現の場合、緯度＝Z軸回転角、経度＝Y軸回転角、となるため、の２つの成分を伴って「移動方角」とできる。
    //したがって、「移動方角（Y軸）」という言葉の語彙は、キャラの進行方向ベクトルのY軸回転角の成分（経度）を指していることとする。
    //一方、「軸回転方角（Y軸）」はキャラの向きのY軸回転角成分を指している。
    //「移動方角（Z軸）」は存在しないが、「軸回転方角（Z軸）」は当然存在する。混乱しないように。
    //緯度経度指定(_angRzMove, _angRyMove)と座標指定(_vX, _vY, _vZ) の内部保持メンバで最終的にワールド変換で使用されるのは
    //座標指定(_vX, _vY, _vZ)の方である。
    //本クラスのメソッドを使用する限り、この(_angRzMove, _angRyMove)と(_vX, _vY, _vZ) は、同期はとれている。
    //
    //＜自動前方向き機能＞
    //自動前方向き機能とは「移動方角」を設定すると、それに伴って自動的に「軸回転方角」を設定する事を意味している。
    //具体的には、以下のようにフレーム毎に、アングル値を上書きコピーしているだけ。
    // ・移動方角（Z軸） → 軸回転方角(Z軸)
    // ・移動方角（Y軸） → 軸回転方角(Y軸)
    //しかし「軸回転方角」を設定ても「移動方角」変化しない（は関係ない）。

    ////////コピー元end

    ///////コピー元begin
    /** 移動方角（Y軸回転）の角速度（移動方角（Y軸回転）に毎フレーム加算する方角） */
    angle _angveloRyMove;
    /** 移動方角（Y軸回転）の角速度上限(最高値は360,000) */
    angle _angveloRyTopMove;
    /** 移動方角（Y軸回転）の角速度下限(最高値は-360,000) */
    angle _angveloRyBottomMove;
    /** 移動方角（Y軸回転）の角加速度（角速度に毎フレーム加算する値） */
    angacce _angacceRyMove;
    /** 目標の移動方角（Y軸回転）自動停止機能有効フラグ */
    bool _move_angle_ry_target_flg;
    /** 目標とするキャラの移動方角（Y軸回転）の方角(0～360,000) */
    int _angTargetRyMove;
    /** 目標の移動方角（Y軸回転）自動停止機能が有効になる進入回転方向 */
    int _move_angle_ry_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** 目標の移動方角（Y軸回転）自動停止機能が有効になる移動方角角速度 */
    int _move_angle_ry_target_allow_velocity;
    /** 自動前方向き機能有効フラグ */
    bool _synchronize_YRotAngle_to_RyMoveAngle_flg;
    //true  : 移動方角（Y軸回転）を変更すると、それに伴い同じ方角が軸回転方角(Y軸)にも設定される
    //false : 移動方角（Y軸回転）とY軸軸回転方角は独立
    ////////コピー元end

    /** X軸方向移動速度 */
    velo _veloVxMove;
    /** X軸方向移動速度上限 */
    velo _veloTopVxMove;
    /** X軸方向移動速度下限 */
    velo _veloBottomVxMove;
    /** X軸方向移動加速度 */
    acce _acceVxMove;
    /** Y軸方向移動速度 */
    velo _veloVyMove;
    /** Y軸方向移動速度上限 */
    velo _veloTopVyMove;
    /** Y軸方向移動速度下限 */
    velo _veloBottomVyMove;
    /** Y軸方向移動加速度 */
    acce _acceVyMove;
    /** Z軸方向移動速度 */
    velo _veloVzMove;
    /** Z軸方向移動速度上限 */
    velo _veloTopVzMove;
    /** Z軸方向移動速度下限 */
    velo _veloBottomVzMove;
    /** Z軸方向移動加速度 */
    acce _acceVzMove;

    /**
     * ActorのZ軸移動スピードを設定<BR>
     * @param	prm_veloMove	Z軸移動スピード
     */
    void setMoveVelocity(velo prm_veloMove);

    void addMoveVelocity(velo prm_veloMove_Offset);

    void setMoveVelocityRenge(velo prm_veloMove01, velo prm_veloMove02);

    void setMoveAcceleration(acce prm_acceMove);

    ///////コピー元begin

    /**
     * Actorの移動方角（Z軸回転）を設定。<BR>
     * 加算後の移動方角（Z軸回転）が範囲外（0～360,000 以外）の値になっても、正しい 0～360,000 の範囲内の値に再計算されます。<BR>
     * 自動前方向き機能が有効(_synchronize_ZRotAngle_to_RzMoveAngle_flg)の場合、<BR>
     * Actorの向きも移動方角（Z軸回転）と同じ方向を向くように setTargetRotAngle(int) も実行されます。<BR>
     *
     * @param	prm_angRzMove	移動方角（Z軸回転）(0～360,000)
     */
    void setRzMoveAngle(angle prm_angle);

    /**
     * Actorの移動方角（Z軸回転）を現在XY座標からの対象XY座標への方向を割り出し、設定する。<BR>
     * 自動前方向き機能が有効(_synchronize_ZRotAngle_to_RzMoveAngle_flg)の場合、<BR>
     * ActorのZ軸方角（向き）も移動方角（Z軸回転）と同じ方向を向くように setTargetRotAngle(int) が実行されます。<BR>
     *
     * @param	prm_tX	対象xZ軸座標
     * @param	prm_tY	対象yZ軸座標
     */
    void setRzMoveAngle(int prm_tX, int prm_tY);

    /**
     * 現在の Actor の移動方角（Z軸回転）へ加算（負で減算）。<BR>
     *
     * 引数に渡すのは、移動方角（Z軸回転）の増分です。Actorの移動方角（Z軸回転）（_angRzMove）を相対指定でるメソッドです。<BR>
     * 加算後の移動方角（Z軸回転）が範囲外（0～360,000 以外）の値になっても、最終的には setRzMoveAngle(int) を呼び出しますので<BR>
     * 正しい 0～360,000 の範囲内の値に再設定されます。<BR>
     * 引数である加算（減算）する移動方角（Z軸回転）は、Z軸移動加速度の上限と下限の間の範囲に限ります。<BR>
     * つまり、引数の有効な範囲は以下の通りとなります。<BR>
     *
     *   _angveloRzBottomMove ≦ 引数の動方角増分 ≦ _angveloRzTopMove  です。<BR>
     *
     * もし範囲外の引数の移動方角（Z軸回転）増分を指定した場合は、直近の範囲内の値に強制的に抑えられ、その値が加算されます。<BR>
     * また、自動前方向き機能が有効(_synchronize_ZRotAngle_to_RzMoveAngle_flg)の場合、<BR>
     * 加算後の移動方角（Z軸回転）の値が、Z軸の目標の軸回転方角として設定されます。（自動で前方を向くに設定されます。但し前方＝アングル0のキャラの場合ですけど；）<BR>
     *
     * 【補足：】<BR>
     * 引数の移動方角（Z軸回転）が、数直線上の 0 に、より近い値を加算し続けた場合は、緩やかなカーブ描きながら向転換することを意味します。<BR>
     * 逆に、引数の移動方角（Z軸回転）が、0 から、より離れた値を加算し続けた場合は、より鋭角的なカーブ描きながら向転換することを意味します。<BR>
     * デフォルトのZ軸移動加速度の上限と下限（_angveloRzBottomMove、_angveloRzTopMove) は<BR>
     *
     *  -360,000 ≦ 引数の動方角増分 ≦ 360,000<BR>
     *
     * となっています。これは瞬時に（1フレームで）どんな移動方角（Z軸回転）にも向きを変えれることを意味します。<BR>
     *
     * @param	prm_angDistance	移動方角（Z軸回転）増分(範囲：_angveloRzBottomMove ～ _angveloRzTopMove)
     */
    void addRzMoveAngle(angle prm_angDistance);

    /**
     * Actorの目標の移動方角（Z軸回転）自動停止機能を有効(目標の移動方角（Z軸回転）設定)<BR>
     * 引数に設定された移動方角（Z軸回転）になるまで、移動方角（Z軸回転）を加算(減算)を毎フレーム行い続けます。<BR>
     * 加算か減算かは、移動方角（Z軸回転）の角速度（_angveloRzMove）の正負で決定されます。<BR>
     * <B>移動方角（Z軸回転）の角速度が 0 ならば、何も起こりません。</B>動作さえるには、角速度が必要です。<BR>
     * 内部的には、addRzMoveAngle(int) が毎フレーム行われる仕組みです。(this->behave()で実行)<BR>
     * 目標の移動方角（Z軸回転）に到達したならば、この目標の移動方角（Z軸回転）自動停止機能は解除されます。<BR>
     *
     * @param	prm_angRzMove	到達目標の移動方角（Z軸回転）(-360,000～360,000)
     * @param	prm_way_allow  自動停止機能が有効になる進入回転方向
     * @param	prm_angveloAllowRyMove 停止機能が有効になる移動方角角速度
     */
    void setTargetRzMoveAngle(angle prm_angRzMove,
                                  int prm_way_allow = TURN_BOTH,
                                  angvelo prm_angveloAllowRyMove = ANGLE180);

    /**
     * Actorの目標の移動方角（Z軸回転）自動停止機能を有効(目標の移動方角（Z軸回転）を現在Z軸座標からの対象Z軸座標で設定)<BR>
     * 機能はsetTargetRzMoveAngle(int)と同じ<BR>
     *
     * @param	prm_tX	xRz座標
     * @param	prm_tY	yRy座標
     * @param	prm_way_allow  自動停止機能が有効になる進入回転方向
     * @param	prm_angveloAllowRyMove 停止機能が有効になる移動方角角速度
     */
    void setTargetRzMoveAngleV(int prm_tX,
                                   int prm_tY,
                                   int prm_way_allow = TURN_BOTH,
                                   angvelo prm_angveloAllowRyMove = ANGLE180);

    void setRzMoveAngleVelocity(angvelo prm_angveloRzMove);

    void setRzMoveAngleVelocityRenge(angvelo prm_angveloRzMove01, angvelo prm_angveloRzMove02);

    void setRzMoveAngleAcceleration(angacce prm_angacceRzMove);

    angle getDifferenceFromRzMoveAngleTo(int prm_tX, int prm_tY, int prm_way);

    /**
     * 自身の移動方角のZ軸回転角( _angRzMove )と、ターゲットの回転角との差分を取得.
     * TURN_COUNTERCLOCKWISE ･･･ 回転方向が左回りで差異角取得、正の値で返る。
     * TURN_CLOCKWISE        ･･･ 回転方向が右回りで差異角取得、負の値に返る。
     * TURN_CLOSE_TO         ･･･ ターゲットの回転角と距離が近いほうの回転方向で取得、正又は負の値になる。
     * @param prm_angTargetRzMove ターゲット角の値
     * @param prm_way TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO
     * @return
     */
    angle getDifferenceFromRzMoveAngleTo(angle prm_angTargetRzMove, int prm_way);
    ///コピー元end

    ///////コピー元begin

    /**
     * Actorの移動方角（Y軸回転）を設定。<BR>
     * 加算後の移動方角（Y軸回転）が範囲外（0～360,000 以外）の値になっても、正しい 0～360,000 の範囲内の値に再計算されます。<BR>
     * 自動前方向き機能が有効(_synchronize_YRotAngle_to_RyMoveAngle_flg)の場合、<BR>
     * Actorの向きも移動方角（Y軸回転）と同じ方向を向くように setTargetRotAngle(int) も実行されます。<BR>
     *
     * @param	prm_angRyMove	移動方角（Y軸回転）(0～360,000)
     */
    void setRyMoveAngle(angle prm_angle);

    /**
     * Actorの移動方角（Y軸回転）を現在Y軸座標からの対象Y軸座標への方向を割り出し、設定する。<BR>
     * 自動前方向き機能が有効(_synchronize_YRotAngle_to_RyMoveAngle_flg)の場合、<BR>
     * ActorのZ軸方角（向き）も移動方角（Y軸回転）と同じ方向を向くように setTargetRotAngle(int) が実行されます。<BR>
     *
     * @param	prm_tX	対象xY軸座標
     * @param	prm_tY	対象yY軸座標
     */
    void setRyMoveAngle(int prm_tX, int prm_tY);

    /**
     * 現在の Actor の移動方角（Y軸回転）へ加算（負で減算）。<BR>
     *
     * 引数に渡すのは、移動方角（Y軸回転）の増分です。Actorの移動方角（Y軸回転）（_angRyMove）を相対指定でるメソッドです。<BR>
     * 加算後の移動方角（Y軸回転）が範囲外（0～360,000 以外）の値になっても、最終的には setRyMoveAngle(int) を呼び出しますので<BR>
     * 正しい 0～360,000 の範囲内の値に再設定されます。<BR>
     * 引数である加算（減算）する移動方角（Y軸回転）は、Y軸移動加速度の上限と下限の間の範囲に限ります。<BR>
     * つまり、引数の有効な範囲は以下の通りとなります。<BR>
     *
     *   _angveloRyBottomMove ≦ 引数の動方角増分 ≦ _angveloRyTopMove  です。<BR>
     *
     * もし範囲外の引数の移動方角（Y軸回転）増分を指定した場合は、直近の範囲内の値に強制的に抑えられ、その値が加算されます。<BR>
     * また、自動前方向き機能が有効(_synchronize_YRotAngle_to_RyMoveAngle_flg)の場合、<BR>
     * 加算後の移動方角（Y軸回転）の値が、Z軸の目標の軸回転方角として設定されます。（自動で前方を向くに設定されます。但し前方＝アングル0のキャラの場合ですけど；）<BR>
     *
     * 【補足：】<BR>
     * 引数の移動方角（Y軸回転）が、数直線上の 0 に、より近い値を加算し続けた場合は、緩やかなカーブ描きながら向転換することを意味します。<BR>
     * 逆に、引数の移動方角（Y軸回転）が、0 から、より離れた値を加算し続けた場合は、より鋭角的なカーブ描きながら向転換することを意味します。<BR>
     * デフォルトのY軸移動加速度の上限と下限（_angveloRyBottomMove、_angveloRyTopMove) は<BR>
     *
     *  -360,000 ≦ 引数の動方角増分 ≦ 360,000<BR>
     *
     * となっています。これは瞬時に（1フレームで）どんな移動方角（Y軸回転）にも向きを変えれることを意味します。<BR>
     *
     * @param	prm_angDistance	移動方角（Y軸回転）増分(範囲：_angveloRyBottomMove ～ _angveloRyTopMove)
     */
    void addRyMoveAngle(angle prm_angDistance);

    /**
     * Actorの目標の移動方角（Y軸回転）自動停止機能を有効(目標の移動方角（Y軸回転）設定)<BR>
     * 引数に設定された移動方角（Y軸回転）になるまで、移動方角（Y軸回転）を加算(減算)を毎フレーム行い続けます。<BR>
     * 加算か減算かは、移動方角（Y軸回転）の角速度（_angveloRyMove）の正負で決定されます。<BR>
     * <B>移動方角（Y軸回転）の角速度が 0 ならば、何も起こりません。</B>動作さえるには、角速度が必要です。<BR>
     * 内部的には、addRyMoveAngle(int) が毎フレーム行われる仕組みです。(this->behave()で実行)<BR>
     * 目標の移動方角（Y軸回転）に到達したならば、この目標の移動方角（Y軸回転）自動停止機能は解除されます。<BR>
     *
     * @param	prm_angRyMove	到達目標の移動方角（Y軸回転）(-360,000～360,000)
     * @param	prm_way_allow  自動停止機能が有効になる進入回転方向
     * @param	prm_angveloAllowRyMove 停止機能が有効になる移動方角角速度
     */
    void setTargetRyMoveAngle(angle prm_angRyMove,
                              int _move_angle_ry_target_allow_way = TURN_BOTH,
                              angvelo prm_angveloAllowRyMove = ANGLE180);

    /**
     * Actorの目標の移動方角（Y軸回転）自動停止機能を有効(目標の移動方角（Y軸回転）を現在Y軸座標からの対象Y軸座標で設定)<BR>
     * 機能はsetTargetRyMoveAngle(int)と同じ<BR>
     *
     * @param	prm_tX	xRy座標
     * @param	prm_tY	yRy座標
     * @param	prm_way_allow  自動停止機能が有効になる進入回転方向
     * @param	prm_angveloAllowRyMove 停止機能が有効になる移動方角角速度
     */
    void setTargetRyMoveAngleV(int prm_tX,
                               int prm_tY,
                               int _move_angle_ry_target_allow_way = TURN_BOTH,
                               angvelo prm_angveloAllowRyMove = ANGLE180);

    void setRyMoveAngleVelocity(angvelo prm_angveloRyMove);

    void setRyMoveAngleVelocityRenge(angvelo prm_angveloRyMove01, angvelo prm_angveloRyMove02);

    void setRyMoveAngleAcceleration(angacce prm_angacceRyMove);

    angle getDifferenceFromRyMoveAngleTo(int prm_tX, int prm_tY, int prm_way);

    angle getDifferenceFromRyMoveAngleTo(angle prm_angTargetRyMove, int prm_way);
    ///コピー元end
    /**
     * 緯度経度で移動方向を設定。.
     * @param prm_angRz
     * @param prm_angRy
     */
    void setRzRyMoveAngle(angle prm_angRz, angle prm_angRy);
    /**
     * 座標指定で移動方向を設定。.
     * 正規化は内部で行なうため、移動させたい座標を指定するだけでよい。
     * @param prm_tX
     * @param prm_tY
     * @param prm_tZ
     */
    void setMoveAngle(int prm_tX, int prm_tY, int prm_tZ);

    void setMoveAngle(GgafDx9UntransformedActor* prm_pActor_Target);

    void setTargetRzRyMoveAngle(int prm_tX, int prm_tY, int prm_tZ);

    void setTargetRzRyMoveAngle(GgafDx9UntransformedActor* prm_pActor_Target);

    //virtual void behave();

    void setVxMoveVelocity(velo prm_veloVxMove);
    void setVxMoveVelocityRenge(velo prm_veloVxMove01, velo prm_veloVxMove02);
    void setVxMoveAcceleration(acce prm_acceVxMove);

    void setVyMoveVelocity(velo prm_veloVyMove);
    void setVyMoveVelocityRenge(velo prm_veloVyMove01, velo prm_veloVyMove02);
    void setVyMoveAcceleration(acce prm_acceVyMove);

    void setVzMoveVelocity(velo prm_veloVzMove);
    void setVzMoveVelocityRenge(velo prm_veloVzMove01, velo prm_veloVzMove02);
    void setVzMoveAcceleration(acce prm_acceVzMove);

    /**
     * 毎フレームのActorの振る舞い。<BR>
     * 本クラスを利用する場合は、このbehave() を毎フレーム実行します。<BR>
     */
    virtual void behave();

    virtual ~GgafDx9GeometryMover();
};

}
#endif /*GGAFDX9GEOMETRYMOVER_H_*/

