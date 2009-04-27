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
    bool _auto_rot_angle_targeting_flg[3];
    /** 目標とするキャラの軸回転方角の方角(0～360,000) */
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
     * 方角を簡単にする。
     * @param prm_ang 方角
     * @return 簡単にされた方角
     */
    static angle simplifyAngle(angle prm_ang);

    /**
     * Actorの軸の回転方角を設定。<BR>
     *
     * @param	prm_axis	回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angRot	方角(-360,000～360,000)
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
     * 現在の Actor の軸の回転方角へ加算（負で減算）。<BR>
     *
     * 引数に渡すのは、軸と回転方角増分です。Actorの回転方角（_angRot）を相対指定でるメソッドです。<BR>
     * 加算後の回転方角が範囲外（0～360,000）の値になっても、最終的には setRotAngle(int) を呼び出しますので<BR>
     * 正しい 0～360,000 の範囲内の値に設定されます。<BR>
     * 引数である加算（減算）する回転方角は、回転加速度の上限と下限の間の範囲に限ります。<BR>
     * つまり、引数の有効な範囲は以下の通りとなります。<BR>
     *
     *   _iBottom_RotVelocityAngle ≦ 引数の回転角値増分 ≦ _angveloTopRot  です。<BR>
     *
     * もし範囲外の引数の回転方角増分を指定した場合は、直近の範囲内の値に強制的に抑えられ、その値が加算されます。<BR>
     * また、自動前方向き機能が有効(synchronize_ZaxisRotAngle_to_RotAngle_Flg)の場合、<BR>
     * 加算後の回転方角の値が、Z軸の目標の回転方角として設定されます。（自動で前方を向くに設定されます。但し前方＝アングル0のキャラの場合ですけど；）<BR>
     *
     * 【補足：】<BR>
     * 引数の回転方角が、数直線上の 0 に、より近い値を加算し続けた場合は、ゆっくりな軸回転することを意味します。<BR>
     * 逆に、引数の回転方角が、0 から、より離れた値を加算し続けた場合は、速く軸回転することを意味します。<BR>
     * デフォルトの回転加速度の上限と下限（_iBottom_RotVelocityAngle、_angveloTopRot) は<BR>
     *
     *  -360,000 ≦ 引数の動方角増分 ≦ 360,000<BR>
     *
     * となっています。これは瞬時に（1フレームで）指定軸についてどんな回転方角にも向きを変えれることを意味します。<BR>
     *
     * @param	prm_axis	回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angDistance	回転方角増分(範囲：_iBottom_RotVelocityAngle ～ _angveloTopRot)
     */
    void addRotAngle(int prm_axis, angle prm_angDistance);

    /**
     * Actorの目標の軸回転方角自動停止機能を有効(目標の軸回転方角設定)<BR>
     * 引数に設定された軸の回転方角になるまで、回転方角を加算(減算)を毎フレーム行い続けます。<BR>
     * 加算か減算かは、現在の回転方角の角速度（_angveloRot[prm_axis]）の正負で決定されます。<BR>
     * 回転方角の角速度が 0 ならば、何も起こりません。<BR>
     * 内部的には、addRotAngle(prm_axis, int) が毎フレーム行われる仕組みです。<BR>
     * 目標の回転方角に到達したならば、この目標の軸回転方角自動停止機能は解除されます。<BR>
     * @param	prm_axis	回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angRzMove	到達目標の回転方角(0～360,000)
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
    bool _auto_move_angle_rz_target_flg;
    /** 目標とするキャラの移動方角（Z軸回転）の方角(0～360,000) */
    angle _angAutoTargetRzMove;
    /** 目標の移動方角（Z軸回転）自動停止機能が有効になる進入回転方向 */
    int _auto_move_angle_rz_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** 目標の移動方角（Z軸回転）自動停止機能が有効になる移動方角角速度 */
    angvelo _auto_move_angle_rz_target_allow_velocity;
    /** 自動前方向き機能有効フラグ */
    bool _synchronize_ZRotAngle_to_RzMoveAngle_flg;
    //true  : 移動方角（Z軸回転）を変更すると、それに伴い同じ方角がZ軸軸回転方角にも設定される
    //false : 移動方角（Z軸回転）とZ軸軸回転方角は独立
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
    bool _auto_move_angle_ry_target_flg;
    /** 目標とするキャラの移動方角（Y軸回転）の方角(0～360,000) */
    int _angAutoTargetRyMove;
    /** 目標の移動方角（Y軸回転）自動停止機能が有効になる進入回転方向 */
    int _auto_move_angle_ry_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** 目標の移動方角（Y軸回転）自動停止機能が有効になる移動方角角速度 */
    int _auto_move_angle_ry_target_allow_velocity;
    /** 自動前方向き機能有効フラグ */
    bool _synchronize_YRotAngle_to_RyMoveAngle_flg;
    //true  : 移動方角（Y軸回転）を変更すると、それに伴い同じ方角がZ軸軸回転方角にも設定される
    //false : 移動方角（Y軸回転）とZ軸軸回転方角は独立
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
     * Actorの向きも移動方角（Z軸回転）と同じ方向を向くように setAutoTargetRotAngle(int) も実行されます。<BR>
     *
     * @param	prm_angRzMove	移動方角（Z軸回転）(0～360,000)
     */
    void setRzMoveAngle(angle prm_angle);

    /**
     * Actorの移動方角（Z軸回転）を現在XY座標からの対象XY座標への方向を割り出し、設定する。<BR>
     * 自動前方向き機能が有効(_synchronize_ZRotAngle_to_RzMoveAngle_flg)の場合、<BR>
     * ActorのZ軸方角（向き）も移動方角（Z軸回転）と同じ方向を向くように setAutoTargetRotAngle(int) が実行されます。<BR>
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
     * 移動方角（Z軸回転）の角速度が 0 ならば、何も起こりません。<BR>
     * 内部的には、addRzMoveAngle(int) が毎フレーム行われる仕組みです。(this->behave()で実行)<BR>
     * 目標の移動方角（Z軸回転）に到達したならば、この目標の移動方角（Z軸回転）自動停止機能は解除されます。<BR>
     *
     * @param	prm_angRzMove	到達目標の移動方角（Z軸回転）(-360,000～360,000)
     * @param	prm_way_allow  自動停止機能が有効になる進入回転方向
     * @param	prm_angveloAllowRyMove 停止機能が有効になる移動方角角速度
     */
    void setAutoTargetRzMoveAngle(angle prm_angRzMove,
                                  int _auto_move_angle_rz_target_allow_way = TURN_BOTH,
                                  angvelo prm_angveloAllowRyMove = ANGLE180);

    /**
     * Actorの目標の移動方角（Z軸回転）自動停止機能を有効(目標の移動方角（Z軸回転）を現在Z軸座標からの対象Z軸座標で設定)<BR>
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
     * Actorの移動方角（Y軸回転）を設定。<BR>
     * 加算後の移動方角（Y軸回転）が範囲外（0～360,000 以外）の値になっても、正しい 0～360,000 の範囲内の値に再計算されます。<BR>
     * 自動前方向き機能が有効(_synchronize_YRotAngle_to_RyMoveAngle_flg)の場合、<BR>
     * Actorの向きも移動方角（Y軸回転）と同じ方向を向くように setAutoTargetRotAngle(int) も実行されます。<BR>
     *
     * @param	prm_angRyMove	移動方角（Y軸回転）(0～360,000)
     */
    void setRyMoveAngle(angle prm_angle);

    /**
     * Actorの移動方角（Y軸回転）を現在Y軸座標からの対象Y軸座標への方向を割り出し、設定する。<BR>
     * 自動前方向き機能が有効(_synchronize_YRotAngle_to_RyMoveAngle_flg)の場合、<BR>
     * ActorのZ軸方角（向き）も移動方角（Y軸回転）と同じ方向を向くように setAutoTargetRotAngle(int) が実行されます。<BR>
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
     * 移動方角（Y軸回転）の角速度が 0 ならば、何も起こりません。<BR>
     * 内部的には、addRyMoveAngle(int) が毎フレーム行われる仕組みです。(this->behave()で実行)<BR>
     * 目標の移動方角（Y軸回転）に到達したならば、この目標の移動方角（Y軸回転）自動停止機能は解除されます。<BR>
     *
     * @param	prm_angRyMove	到達目標の移動方角（Y軸回転）(-360,000～360,000)
     * @param	prm_way_allow  自動停止機能が有効になる進入回転方向
     * @param	prm_angveloAllowRyMove 停止機能が有効になる移動方角角速度
     */
    void setAutoTargetRyMoveAngle(angle prm_angRyMove,
                              int _auto_move_angle_ry_target_allow_way = TURN_BOTH,
                              angvelo prm_angveloAllowRyMove = ANGLE180);

    /**
     * Actorの目標の移動方角（Y軸回転）自動停止機能を有効(目標の移動方角（Y軸回転）を現在Y軸座標からの対象Y軸座標で設定)<BR>
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

    void setMoveAngle(GgafDx9UntransformedActor* prm_pActor_Target);

    void setAutoTargetMoveAngle(int prm_tX, int prm_tY, int prm_tZ);

    void setAutoTargetMoveAngle(GgafDx9UntransformedActor* prm_pActor_Target);

    /**
     * 毎フレームのActorの振る舞い。<BR>
     * 本インターフェースを利用する場合は、このbehave() を毎フレーム実行します。<BR>
     * behave() の具体的な毎フレームの処理は以下の通り。<BR>
     * ・加速度(_accMove)が0でない場合、加速度によるスピード増加処理。<BR>
     * 　　→加算後のスピードで setMoveVelocity(int) が毎フレーム実行されます。<BR>
     * ・目標の移動方角（Z軸回転）自動停止機能が使用時の場合、移動方角（Z軸回転）変更処理<BR>
     * 　　→計算された移動方角（Z軸回転）で addRzMoveAngle(int) が毎フレーム実行されます。<BR>
     * ・目標の移動方角（Z軸回転）自動停止機能使用時ではない場合、一定量移動方角（Z軸回転）加算処理<BR>
     * 　　→addRzMoveAngle(int) が毎フレーム実行されます。<BR>
     * ・目標の軸回転方角自動停止機能使用時の場合、軸回転方角変更処理<BR>
     * 　　→計算された軸回転方角で addRotAngle(int) が毎フレーム実行されます。<BR>
     * ・目標の軸回転方角自動停止機能が使用時ではない場合、一定量軸回転方角加算処理<BR>
     * 　　→addRotAngle(int) が毎フレーム実行されます。<BR>
     * 以上の処理を行った後、Actorの以下のメンバへ、座標増分情報、Z軸回転情報を設定します。<BR>
     *  _X ･･･ 移動方角（Z軸回転）とZ軸移動スピードからX座標増分計算し加算<BR>
     *  _Y ･･･ 移動方角（Z軸回転）とZ軸移動スピードからY座標増分計算し加算<BR>
     *  _Z ･･･_veloVzMove を加算
     *  _RX   ･･･ 軸回転方角を代入<BR>
     *  _RY   ･･･ 軸回転方角を代入<BR>
     *  _RZ   ･･･ 軸回転方角を代入<BR>
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

