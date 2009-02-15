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
/**
 * 移動のための座標計算機能をもつクラス.
 */
class GgafDx9GeometryMover : public GgafCore::GgafObject {
    double _dummy1, _dummy2, _dummy3;

public:
    /** 対象アクター */
    GgafDx9UntransformedActor* _pActor;
    /** キャラの軸回転方角の方角値(0〜360,000) */
    angle _angRot[3];
    /** 軸回転方角の角速度（軸回転方角値に毎フレーム加算する方角値） */
    angvelo _angveloRot[3];
    /** 軸回転方角値の角速度上限(最高値は360,000) */
    angvelo _angveloTopRot[3];
    /** 軸回転方角値の角速度下限(最高値は-360,000) */
    angvelo _angveloBottomRot[3];
    /** 軸回転方角の角加速度（角速度に毎フレーム加算する値） */
    angacce _angacceRot[3];
    /** 目標の軸回転方角自動停止機能有効フラグ */
    bool _auto_rot_angle_target_Flg[3];
    /** 目標とするキャラの軸回転方角の方角値(0〜360,000) */
    angle _angAutoTargetRot[3];
    /** 目標の軸回転方角自動停止機能が有効になる回転方向 */
    int _auto_rot_angle_target_allow_way[3]; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** 目標の軸回転方角自動停止機能が有効になる角速度（回転正負共通） */
    angvelo _auto_rot_angle_target_allow_velocity[3]; //この角速度より小さい値の場合機能有効とする
    /**
     * コンストラクタ<BR>
     * @param	prm_pActor	適用Actor
     */
    GgafDx9GeometryMover(GgafDx9UntransformedActor* prm_pActor);

    /**
     * 方角値を簡単にする。
     * @param prm_ang 方角値
     * @return 簡単にされた方角値
     */
    angle simplifyAngle(angle prm_ang);

    /**
     * Actorの軸の回転方角値を設定。<BR>
     *
     * @param	prm_axis	回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angRot	方角値(-360,000〜360,000)
     */
    void setRotAngle(int prm_axis, angle prm_angRot);

    /**
     * Actorの軸の回転方角値を対象座標に向ける。<BR>
     * 引数の座標をに向くようにZ軸Y軸（Rz と Ry）の回転値を設定します。
     * @param prm_tX 対象X座標
     * @param prm_tY 対象Y座標
     * @param prm_tZ 対象Z座標
     */
    void setRotAngle(int prm_tX, int prm_tY, int prm_tZ);

    /**
     * 現在の Actor の軸の回転方角値へ加算（負で減算）。<BR>
     *
     * 引数に渡すのは、軸と回転方角値増分です。Actorの回転方角値（_angRot）を相対指定でるメソッドです。<BR>
     * 加算後の回転方角値が範囲外（0〜360,000）の値になっても、最終的には setRotAngle(int) を呼び出しますので<BR>
     * 正しい 0〜360,000 の範囲内の値に設定されます。<BR>
     * 引数である加算（減算）する回転方角値は、回転加速度の上限と下限の間の範囲に限ります。<BR>
     * つまり、引数の有効な範囲は以下の通りとなります。<BR>
     *
     *   _iBottom_RotVelocityAngle ≦ 引数の回転角値増分 ≦ _angveloTopRot  です。<BR>
     *
     * もし範囲外の引数の回転方角値増分を指定した場合は、直近の範囲内の値に強制的に抑えられ、その値が加算されます。<BR>
     * また、自動前方向き機能が有効(synchronize_ZaxisRotAngle_to_RotAngle_Flg)の場合、<BR>
     * 加算後の回転方角値の値が、Z軸の目標の回転方角値として設定されます。（自動で前方を向くに設定されます。但し前方＝アングル0のキャラの場合ですけど；）<BR>
     *
     * 【補足：】<BR>
     * 引数の回転方角値が、数直線上の 0 に、より近い値を加算し続けた場合は、ゆっくりな軸回転することを意味します。<BR>
     * 逆に、引数の回転方角値が、0 から、より離れた値を加算し続けた場合は、速く軸回転することを意味します。<BR>
     * デフォルトの回転加速度の上限と下限（_iBottom_RotVelocityAngle、_angveloTopRot) は<BR>
     *
     *  -360,000 ≦ 引数の動方角値増分 ≦ 360,000<BR>
     *
     * となっています。これは瞬時に（1フレームで）指定軸についてどんな回転方角にも向きを変えれることを意味します。<BR>
     *
     * @param	prm_axis	回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angDistance	回転方角値増分(範囲：_iBottom_RotVelocityAngle 〜 _angveloTopRot)
     */
    void addRotAngle(int prm_axis, angle prm_angDistance);

    /**
     * Actorの目標の軸回転方角自動停止機能を有効(目標の軸回転方角値設定)<BR>
     * 引数に設定された軸の回転方角値になるまで、回転方角値を加算(減算)を毎フレーム行い続けます。<BR>
     * 加算か減算かは、現在の回転方角の角速度（_angveloRot[prm_axis]）の正負で決定されます。<BR>
     * 回転方角の角速度が 0 ならば、何も起こりません。<BR>
     * 内部的には、addRotAngle(prm_axis, int) が毎フレーム行われる仕組みです。<BR>
     * 目標の回転方角に到達したならば、この目標の軸回転方角自動停止機能は解除されます。<BR>
     * @param	prm_axis	回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angRzMove	到達目標の回転方角値(0〜360,000)
     * @param	prm_way_allow  自動停止機能が有効になる回転方向
     * @param	prm_angveloAllowRyMove 自動停止機能が有効になる回転角速度
     */
    void setAutoTargetRotAngle(int prm_axis,
                               angle prm_angAutoTargetRot,
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
    void setAutoTargetRotAngleV(int prm_axis,
                            int prm_tX,
                            int prm_tY,
                            int prm_way_allow = TURN_BOTH,
                            angvelo prm_angveloAllowRyMove = ANGLE180);

    void setRotAngleVelocity(int prm_axis, angvelo prm_angveloRot);

    void setRotAngleVelocityRenge(int prm_axis,
                                  angvelo prm_angveloRot01,
                                  angvelo prm_angveloRot02);

    void setRotAngleAcceleration(int prm_axis, angacce prm_angacceRot);

    angle getDistanceFromRotAngleTo(int prm_axis, int prm_tX, int prm_tY, int prm_way);

    angle getDistanceFromRotAngleTo(int prm_axis, angle prm_angAutoTargetRot, int prm_way);

    ////////////////////////////////////////////////////MOVER
public:
    /** キャラの移動方角単位ベクトル */
    double _vX, _vY, _vZ;
    /** 移動方角のZ軸回転角速度 */
    angle _angRzMove;
    /** 移動方角のY軸回転角速度 */
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
    /** Z軸移動方角の角速度（Z軸移動方角値に毎フレーム加算する方角値） */
    angvelo _angveloRzMove;
    /** Z軸移動方角値の角速度上限(最高値は360,000) */
    angvelo _angveloRzTopMove;
    /** Z軸移動方角値の角速度下限(最高値は-360,000) */
    angvelo _angveloRzBottomMove;
    /** Z軸移動方角の角加速度（角速度に毎フレーム加算する値） */
    angacce _angacceRzMove;
    /** 目標のZ軸移動方角自動停止機能有効フラグ */
    bool _auto_move_angle_rz_target_Flg;
    /** 目標とするキャラのZ軸移動方角の方角値(0〜360,000) */
    angle _angAutoTargetRzMove;
    /** 目標のZ軸移動方角自動停止機能が有効になる進入回転方向 */
    int _auto_move_angle_rz_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** 目標のZ軸移動方角自動停止機能が有効になる移動方角角速度 */
    angvelo _auto_move_angle_rz_target_allow_velocity;
    /** 自動前方向き機能有効フラグ */
    bool _synchronize_ZRotAngle_to_RzMoveAngle_Flg;
    //true  : Z軸移動方角を変更すると、それに伴い同じ方角値がZ軸軸回転方角にも設定される
    //false : Z軸移動方角とZ軸軸回転方角は独立
    ////////コピー元end

    ///////コピー元begin
    /** Y軸移動方角の角速度（Y軸移動方角値に毎フレーム加算する方角値） */
    angle _angveloRyMove;
    /** Y軸移動方角値の角速度上限(最高値は360,000) */
    angle _angveloRyTopMove;
    /** Y軸移動方角値の角速度下限(最高値は-360,000) */
    angle _angveloRyBottomMove;
    /** Y軸移動方角の角加速度（角速度に毎フレーム加算する値） */
    angacce _angacceRyMove;
    /** 目標のY軸移動方角自動停止機能有効フラグ */
    bool _auto_move_angle_ry_target_Flg;
    /** 目標とするキャラのY軸移動方角の方角値(0〜360,000) */
    int _angAutoTargetRyMove;
    /** 目標のY軸移動方角自動停止機能が有効になる進入回転方向 */
    int _auto_move_angle_ry_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** 目標のY軸移動方角自動停止機能が有効になる移動方角角速度 */
    int _auto_move_angle_ry_target_allow_velocity;
    /** 自動前方向き機能有効フラグ */
    bool _synchronize_YRotAngle_to_RyMoveAngle_Flg;
    //true  : Y軸移動方角を変更すると、それに伴い同じ方角値がZ軸軸回転方角にも設定される
    //false : Y軸移動方角とZ軸軸回転方角は独立
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
     * ActorのZ軸移動方角値を設定。<BR>
     * 加算後のZ軸移動方角値が範囲外（0〜360,000 以外）の値になっても、正しい 0〜360,000 の範囲内の値に再計算されます。<BR>
     * 自動前方向き機能が有効(_synchronize_ZRotAngle_to_RzMoveAngle_Flg)の場合、<BR>
     * Actorの向きもZ軸移動方角と同じ方向を向くように setAutoTargetRotAngle(int) も実行されます。<BR>
     *
     * @param	prm_angRzMove	Z軸移動方角値(0〜360,000)
     */
    void setRzMoveAngle(angle prm_angle);

    /**
     * ActorのZ軸移動方角値を現在XY座標からの対象XY座標への方向を割り出し、設定する。<BR>
     * 自動前方向き機能が有効(_synchronize_ZRotAngle_to_RzMoveAngle_Flg)の場合、<BR>
     * ActorのZ軸方角値（向き）もZ軸移動方角と同じ方向を向くように setAutoTargetRotAngle(int) が実行されます。<BR>
     *
     * @param	prm_tX	対象xZ軸座標
     * @param	prm_tY	対象yZ軸座標
     */
    void setRzMoveAngle(int prm_tX, int prm_tY);

    /**
     * 現在の Actor のZ軸移動方角値へ加算（負で減算）。<BR>
     *
     * 引数に渡すのは、Z軸移動方角値の増分です。ActorのZ軸移動方角値（_angRzMove）を相対指定でるメソッドです。<BR>
     * 加算後のZ軸移動方角値が範囲外（0〜360,000 以外）の値になっても、最終的には setRzMoveAngle(int) を呼び出しますので<BR>
     * 正しい 0〜360,000 の範囲内の値に再設定されます。<BR>
     * 引数である加算（減算）するZ軸移動方角値は、Z軸移動加速度の上限と下限の間の範囲に限ります。<BR>
     * つまり、引数の有効な範囲は以下の通りとなります。<BR>
     *
     *   _angveloRzBottomMove ≦ 引数の動方角値増分 ≦ _angveloRzTopMove  です。<BR>
     *
     * もし範囲外の引数のZ軸移動方角値増分を指定した場合は、直近の範囲内の値に強制的に抑えられ、その値が加算されます。<BR>
     * また、自動前方向き機能が有効(_synchronize_ZRotAngle_to_RzMoveAngle_Flg)の場合、<BR>
     * 加算後のZ軸移動方角値の値が、Z軸の目標の軸回転方角値として設定されます。（自動で前方を向くに設定されます。但し前方＝アングル0のキャラの場合ですけど；）<BR>
     *
     * 【補足：】<BR>
     * 引数のZ軸移動方角値が、数直線上の 0 に、より近い値を加算し続けた場合は、緩やかなカーブ描きながら向転換することを意味します。<BR>
     * 逆に、引数のZ軸移動方角値が、0 から、より離れた値を加算し続けた場合は、より鋭角的なカーブ描きながら向転換することを意味します。<BR>
     * デフォルトのZ軸移動加速度の上限と下限（_angveloRzBottomMove、_angveloRzTopMove) は<BR>
     *
     *  -360,000 ≦ 引数の動方角値増分 ≦ 360,000<BR>
     *
     * となっています。これは瞬時に（1フレームで）どんなZ軸移動方角にも向きを変えれることを意味します。<BR>
     *
     * @param	prm_angDistance	Z軸移動方角値増分(範囲：_angveloRzBottomMove 〜 _angveloRzTopMove)
     */
    void addRzMoveAngle(angle prm_angDistance);

    /**
     * Actorの目標のZ軸移動方角自動停止機能を有効(目標のZ軸移動方角値設定)<BR>
     * 引数に設定されたZ軸移動方角値になるまで、Z軸移動方角値を加算(減算)を毎フレーム行い続けます。<BR>
     * 加算か減算かは、Z軸移動方角の角速度（_angveloRzMove）の正負で決定されます。<BR>
     * Z軸移動方角の角速度が 0 ならば、何も起こりません。<BR>
     * 内部的には、addRzMoveAngle(int) が毎フレーム行われる仕組みです。(this->behave()で実行)<BR>
     * 目標のZ軸移動方角に到達したならば、この目標のZ軸移動方角自動停止機能は解除されます。<BR>
     *
     * @param	prm_angRzMove	到達目標のZ軸移動方角値(-360,000〜360,000)
     * @param	prm_way_allow  自動停止機能が有効になる進入回転方向
     * @param	prm_angveloAllowRyMove 停止機能が有効になる移動方角角速度
     */
    void setAutoTargetRzMoveAngle(angle prm_angRzMove,
                                  int _auto_move_angle_rz_target_allow_way = TURN_BOTH,
                                  angvelo prm_angveloAllowRyMove = ANGLE180);

    /**
     * Actorの目標のZ軸移動方角自動停止機能を有効(目標のZ軸移動方角を現在Z軸座標からの対象Z軸座標で設定)<BR>
     * 機能はsetAutoTargetRzMoveAngle(int)と同じ<BR>
     *
     * @param	prm_tX	xRz座標
     * @param	prm_tY	yRy座標
     * @param	prm_way_allow  自動停止機能が有効になる進入回転方向
     * @param	prm_angveloAllowRyMove 停止機能が有効になる移動方角角速度
     */
    void setAutoTargetRzMoveAngleV(int prm_tX,
                               int prm_tY,
                               int _auto_move_angle_rz_target_allow_way = TURN_BOTH,
                               angvelo prm_angveloAllowRyMove = ANGLE180);

    void setRzMoveAngleVelocity(angvelo prm_angveloRzMove);

    void setRzMoveAngleVelocityRenge(angvelo prm_angveloRzMove01, angvelo prm_angveloRzMove02);

    void setRzMoveAngleAcceleration(angacce prm_angacceRzMove);

    angle getDistanceFromRzMoveAngleTo(int prm_tX, int prm_tY, int prm_way);

    angle getDistanceFromRzMoveAngleTo(angle prm_angAutoTargetRzMove, int prm_way);
    ///コピー元end

    ///////コピー元begin

    /**
     * ActorのY軸移動方角値を設定。<BR>
     * 加算後のY軸移動方角値が範囲外（0〜360,000 以外）の値になっても、正しい 0〜360,000 の範囲内の値に再計算されます。<BR>
     * 自動前方向き機能が有効(_synchronize_YRotAngle_to_RyMoveAngle_Flg)の場合、<BR>
     * Actorの向きもY軸移動方角と同じ方向を向くように setAutoTargetRotAngle(int) も実行されます。<BR>
     *
     * @param	prm_angRyMove	Y軸移動方角値(0〜360,000)
     */
    void setRyMoveAngle(angle prm_angle);

    /**
     * ActorのY軸移動方角値を現在Y軸座標からの対象Y軸座標への方向を割り出し、設定する。<BR>
     * 自動前方向き機能が有効(_synchronize_YRotAngle_to_RyMoveAngle_Flg)の場合、<BR>
     * ActorのZ軸方角値（向き）もY軸移動方角と同じ方向を向くように setAutoTargetRotAngle(int) が実行されます。<BR>
     *
     * @param	prm_tX	対象xY軸座標
     * @param	prm_tY	対象yY軸座標
     */
    void setRyMoveAngle(int prm_tX, int prm_tY);

    /**
     * 現在の Actor のY軸移動方角値へ加算（負で減算）。<BR>
     *
     * 引数に渡すのは、Y軸移動方角値の増分です。ActorのY軸移動方角値（_angRyMove）を相対指定でるメソッドです。<BR>
     * 加算後のY軸移動方角値が範囲外（0〜360,000 以外）の値になっても、最終的には setRyMoveAngle(int) を呼び出しますので<BR>
     * 正しい 0〜360,000 の範囲内の値に再設定されます。<BR>
     * 引数である加算（減算）するY軸移動方角値は、Y軸移動加速度の上限と下限の間の範囲に限ります。<BR>
     * つまり、引数の有効な範囲は以下の通りとなります。<BR>
     *
     *   _angveloRyBottomMove ≦ 引数の動方角値増分 ≦ _angveloRyTopMove  です。<BR>
     *
     * もし範囲外の引数のY軸移動方角値増分を指定した場合は、直近の範囲内の値に強制的に抑えられ、その値が加算されます。<BR>
     * また、自動前方向き機能が有効(_synchronize_YRotAngle_to_RyMoveAngle_Flg)の場合、<BR>
     * 加算後のY軸移動方角値の値が、Z軸の目標の軸回転方角値として設定されます。（自動で前方を向くに設定されます。但し前方＝アングル0のキャラの場合ですけど；）<BR>
     *
     * 【補足：】<BR>
     * 引数のY軸移動方角値が、数直線上の 0 に、より近い値を加算し続けた場合は、緩やかなカーブ描きながら向転換することを意味します。<BR>
     * 逆に、引数のY軸移動方角値が、0 から、より離れた値を加算し続けた場合は、より鋭角的なカーブ描きながら向転換することを意味します。<BR>
     * デフォルトのY軸移動加速度の上限と下限（_angveloRyBottomMove、_angveloRyTopMove) は<BR>
     *
     *  -360,000 ≦ 引数の動方角値増分 ≦ 360,000<BR>
     *
     * となっています。これは瞬時に（1フレームで）どんなY軸移動方角にも向きを変えれることを意味します。<BR>
     *
     * @param	prm_angDistance	Y軸移動方角値増分(範囲：_angveloRyBottomMove 〜 _angveloRyTopMove)
     */
    void addRyMoveAngle(angle prm_angDistance);

    /**
     * Actorの目標のY軸移動方角自動停止機能を有効(目標のY軸移動方角値設定)<BR>
     * 引数に設定されたY軸移動方角値になるまで、Y軸移動方角値を加算(減算)を毎フレーム行い続けます。<BR>
     * 加算か減算かは、Y軸移動方角の角速度（_angveloRyMove）の正負で決定されます。<BR>
     * Y軸移動方角の角速度が 0 ならば、何も起こりません。<BR>
     * 内部的には、addRyMoveAngle(int) が毎フレーム行われる仕組みです。(this->behave()で実行)<BR>
     * 目標のY軸移動方角に到達したならば、この目標のY軸移動方角自動停止機能は解除されます。<BR>
     *
     * @param	prm_angRyMove	到達目標のY軸移動方角値(-360,000〜360,000)
     * @param	prm_way_allow  自動停止機能が有効になる進入回転方向
     * @param	prm_angveloAllowRyMove 停止機能が有効になる移動方角角速度
     */
    void setAutoTargetRyMoveAngle(angle prm_angRyMove,
                              int _auto_move_angle_ry_target_allow_way = TURN_BOTH,
                              angvelo prm_angveloAllowRyMove = ANGLE180);

    /**
     * Actorの目標のY軸移動方角自動停止機能を有効(目標のY軸移動方角を現在Y軸座標からの対象Y軸座標で設定)<BR>
     * 機能はsetAutoTargetRyMoveAngle(int)と同じ<BR>
     *
     * @param	prm_tX	xRy座標
     * @param	prm_tY	yRy座標
     * @param	prm_way_allow  自動停止機能が有効になる進入回転方向
     * @param	prm_angveloAllowRyMove 停止機能が有効になる移動方角角速度
     */
    void setAutoTargetRyMoveAngleV(int prm_tX,
                               int prm_tY,
                               int _auto_move_angle_ry_target_allow_way = TURN_BOTH,
                               angvelo prm_angveloAllowRyMove = ANGLE180);

    void setRyMoveAngleVelocity(angvelo prm_angveloRyMove);

    void setRyMoveAngleVelocityRenge(angvelo prm_angveloRyMove01, angvelo prm_angveloRyMove02);

    void setRyMoveAngleAcceleration(angacce prm_angacceRyMove);

    angle getDistanceFromRyMoveAngleTo(int prm_tX, int prm_tY, int prm_way);

    angle getDistanceFromRyMoveAngleTo(angle prm_angAutoTargetRyMove, int prm_way);
    ///コピー元end

    void setRzRyMoveAngle(angle prm_angRz, angle prm_angRy);

    void setMoveAngle(int prm_tX, int prm_tY, int prm_tZ);

    void setAutoTargetMoveAngle(int prm_tX, int prm_tY, int prm_tZ);

    /**
     * 毎フレームのActorの振る舞い。<BR>
     * 本インターフェースを利用する場合は、このbehave() を毎フレーム実行します。<BR>
     * behave() の具体的な毎フレームの処理は以下の通り。<BR>
     * ・加速度(_accMove)が0でない場合、加速度によるスピード増加処理。<BR>
     * 　　→加算後のスピードで setMoveVelocity(int) が毎フレーム実行されます。<BR>
     * ・目標のZ軸移動方角自動停止機能が使用時の場合、Z軸移動方角変更処理<BR>
     * 　　→計算されたZ軸移動方角値で addRzMoveAngle(int) が毎フレーム実行されます。<BR>
     * ・目標のZ軸移動方角自動停止機能使用時ではない場合、一定量Z軸移動方角値加算処理<BR>
     * 　　→addRzMoveAngle(int) が毎フレーム実行されます。<BR>
     * ・目標の軸回転方角自動停止機能使用時の場合、軸回転方角変更処理<BR>
     * 　　→計算された軸回転方角値で addRotAngle(int) が毎フレーム実行されます。<BR>
     * ・目標の軸回転方角自動停止機能が使用時ではない場合、一定量軸回転方角値加算処理<BR>
     * 　　→addRotAngle(int) が毎フレーム実行されます。<BR>
     * 以上の処理を行った後、Actorの以下のメンバへ、座標増分情報、Z軸回転情報を設定します。<BR>
     *  _X ･･･ Z軸移動方角値とZ軸移動スピードからX座標増分計算し加算<BR>
     *  _Y ･･･ Z軸移動方角値とZ軸移動スピードからY座標増分計算し加算<BR>
     *  _Z ･･･_veloVzMove を加算
     *  _RX   ･･･ 軸回転方角値を代入<BR>
     *  _RY   ･･･ 軸回転方角値を代入<BR>
     *  _RZ   ･･･ 軸回転方角値を代入<BR>
     * 【必ず値が設定されるメンバー】<BR>
     * _veloMove,<BR>
     * _pActor->_X += _vX_Move*_veloMove/LEN_UNIT;<BR>
     * _pActor->_Y += _vY_Move*_veloMove/LEN_UNIT;<BR>
     * _pActor->_Z += _veloVzMove
     */
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
     */
    virtual void behave();

    virtual ~GgafDx9GeometryMover();
};

}
#endif /*GGAFDX9GEOMETRYMOVER_H_*/

