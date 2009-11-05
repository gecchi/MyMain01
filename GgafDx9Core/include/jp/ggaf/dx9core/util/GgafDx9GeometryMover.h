#ifndef GGAFDX9GEOMETRYMOVER_H_
#define GGAFDX9GEOMETRYMOVER_H_
namespace GgafDx9Core {

//近い方向に回転
#define TURN_CLOSE_TO 0
//遠い方向に回転
#define TURN_ANTICLOSE_TO 2
//時計回りに回転
#define TURN_CLOCKWISE (-1)
//反時計回りに回転
#define TURN_COUNTERCLOCKWISE 1
//どちらの回転でも受け入れる
#define TURN_BOTH 0

//軸X
#define AXIS_X 0
//軸Y
#define AXIS_Y 1
//軸Z
#define AXIS_Z 2


/**
 * 座標計算支援クラス.
 * GgafDx9GeometricActor のメンバの<BR>
 *  _X ,  _Y,  _Z  ･･･ アクターの座標<BR>
 * _RX , _RY, _RZ  ･･･ アクターの軸回転角度<BR>
 * を、簡単に操作するために設計。<BR>
 */
class GgafDx9GeometryMover : public GgafCore::GgafObject {
    float _dummy1, _dummy2, _dummy3;

public:
    /** 対象アクター */
    GgafDx9GeometricActor* _pActor;
    /** スプラインプログラム  */
    GgafDx9SplineProgram* _progSP;

    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用Actor
     */
    GgafDx9GeometryMover(GgafDx9GeometricActor* prm_pActor);



public: //_RX , _RY, _RZ 操作関連 //////////////////////////////////////////////

    /** キャラの軸回転方角の方角(0～360,000) */
    angle _angFace[3];
    /** 軸回転方角の角速度（軸回転方角に毎フレーム加算する方角） */
    angvelo _angveloRotFace[3];
    /** 軸回転方角の角速度上限(最高値は360,000) */
    angvelo _angveloRotTopFace[3];
    /** 軸回転方角の角速度下限(最高値は-360,000) */
    angvelo _angveloRotBottomFace[3];
    /** 軸回転方角の角加速度（角速度に毎フレーム加算する値） */
    angacce _angacceRotFace[3];
    /** 目標の軸回転方角自動停止機能有効フラグ */
    bool _face_angle_targeting_flg[3];
    /** 目標とするキャラの軸回転方角の方角(0～360,000) */
    angle _angTargetRotFace[3];
    /** 目標の軸回転方角自動停止機能が有効になる回転方向 */
    int _face_angle_target_allow_way[3]; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** 目標の軸回転方角自動停止機能が有効になる角速度（回転正負共通） */
    angvelo _face_angle_target_allow_velocity[3]; //この角速度より小さい値の場合機能有効とするz



    /**
     * アングル値を単純化する。
     * 負のアングル値、又は360,000以上のアングル値を、0～269,999 に変換します。
     * @param prm_ang 方角
     * @return 単純化されたアングル値
     */
    static angle simplifyAngle(angle prm_ang);

    /**
     * Actorの軸の回転方角を設定。<BR>
     * @param	prm_axis	回転軸(AXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angFace	方角のアングル値(-360,000～360,000)
     */
    void setFaceAngle(int prm_axis, angle prm_angFace);

    /**
     * Actorの軸の回転方角を対象座標に向ける。<BR>
     * @param prm_tX 対象X座標
     * @param prm_tY 対象Y座標
     * @param prm_tZ 対象Z座標
     */
    void setFaceAngle(int prm_tX, int prm_tY, int prm_tZ);

    /**
     * 現在の Actor の軸回転方角へ加算（負で減算）。<BR>
     *
     * 引数に渡すのは、軸回転方角の増分です。Actorの軸回転方角（_angFace）を相対指定でるメソッドです。<BR>
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
    void addFaceAngle(int prm_axis, angle prm_angDistance);

    /**
     * Actorの目標の軸回転方角自動停止機能を有効(目標の軸回転方角設定)<BR>
     * 引数に設定された軸回転方角になると、軸回転方角角速度及び軸回転方角角加速度を 0 にし、回転を停止させます。<BR>
     * 軸回転方角角速度等の設定を併せて実行して、まずは軸回転も行なってください。<BR>
     * 軸回転方角角速度が 0 の場合、何も起こりません。本メソッドを実行したからと言って勝手に向きが変わるとという意味ではありません。 <BR>
     * 内部的には、addFaceAngle(prm_axis, int) が毎フレーム行われる仕組みです。<BR>
     * 目標の回転方角に到達したならば、この目標の軸回転方角自動停止機能は解除(内部のフラグをアンセット)されます。<BR>
     * @param	prm_axis	回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angRzMove	到達目標の回転方角(0～360,000)
     * @param	prm_way_allow  自動停止を許可する進入方向(TURN_CLOCKWISE/TURN_COUNTERCLOCKWISE/TURN_BOTH)
     * @param	prm_angveloAllowRyMove 自動停止機能が有効になる回転角速度
     */
    void setStopTarget_FaceAngle(int prm_axis,
                           angle prm_angTargetRot,
                           int prm_way_allow = TURN_BOTH,
                           angvelo prm_angveloAllow = ANGLE180);

    /**
     * Actorの目標回転方向自動停止機能を有効(現在XY座標からの対象XY座標で設定)<BR>
     * @param	prm_axis	回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param	　　prm_tX	対象X座標
     * @param	prm_tY	対象Y座標
     * @param	prm_way_allow  自動停止機能が有効になる回転方向
     * @param	prm_angveloAllowRyMove 自動停止機能が有効になる回転角速度
     */
    void setStopTarget_FaceAngleV(int prm_axis,
                                int prm_tX,
                                int prm_tY,
                                int prm_way_allow = TURN_BOTH,
                                angvelo prm_angveloAllowRyMove = ANGLE180);

    void setFaceAngleVelocity(int prm_axis, angvelo prm_angveloRot);

    void setFaceAngleVeloRenge(int prm_axis,
                                  angvelo prm_angveloRot01,
                                  angvelo prm_angveloRot02);

    void setFaceAngleVeloAcceleration(int prm_axis, angacce prm_angacceRot);

    angle getFaceAngleDistance(int prm_axis, int prm_tX, int prm_tY, int prm_way);

    angle getFaceAngleDistance(int prm_axis, angle prm_angTargetRot, int prm_way);

    ////////////////////////////////////////////////////MOVER

public: //_X , _Y, _Z 操作関連 //////////////////////////////////////////////
    /** キャラの移動方角単位ベクトル */
    float _vX, _vY, _vZ;
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
    bool _synchronize_RzFaceAngle_to_RzMoveAngle_flg;
    //true  : 移動方角（Z軸回転）を変更すると、それに伴い同じ方角が軸回転方角(Z軸)にも設定される
    //false : 移動方角（Z軸回転）とZ軸軸回転方角は独立

    /** 移動方角（Y軸回転）の角速度（移動方角（Y軸回転）に毎フレーム加算する方角） */
    angvelo _angveloRyMove;
    /** 移動方角（Y軸回転）の角速度上限(最高値は360,000) */
    angvelo _angveloRyTopMove;
    /** 移動方角（Y軸回転）の角速度下限(最高値は-360,000) */
    angvelo _angveloRyBottomMove;
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
    bool _synchronize_RyFaceAngle_to_RyMoveAngle_flg;
    //true  : 移動方角（Y軸回転）を変更すると、それに伴い同じ方角が軸回転方角(Y軸)にも設定される
    //false : 移動方角（Y軸回転）とY軸軸回転方角は独立

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

    void setMoveVeloRenge(velo prm_veloMove01, velo prm_veloMove02);

    void setMoveVeloAcceleration(acce prm_acceMove);


    /**
     * Actorの移動方角（Z軸回転）を設定。<BR>
     * 加算後の移動方角（Z軸回転）が範囲外（0～360,000 以外）の値になっても、正しい 0～360,000 の範囲内の値に再計算されます。<BR>
     * 自動前方向き機能が有効(_synchronize_RzFaceAngle_to_RzMoveAngle_flg)の場合、<BR>
     * Actorの向きも移動方角（Z軸回転）と同じ方向を向くように setStopTarget_FaceAngle(int) も実行されます。<BR>
     *
     * @param	prm_angRzMove	移動方角（Z軸回転）(0～360,000)
     */
    void setRzMoveAngle(angle prm_angle);

    /**
     * Actorの移動方角（Z軸回転）を現在XY座標からの対象XY座標への方向を割り出し、設定する。<BR>
     * 自動前方向き機能が有効(_synchronize_RzFaceAngle_to_RzMoveAngle_flg)の場合、<BR>
     * ActorのZ軸方角（向き）も移動方角（Z軸回転）と同じ方向を向くように setStopTarget_FaceAngle(int) が実行されます。<BR>
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
     * また、自動前方向き機能が有効(_synchronize_RzFaceAngle_to_RzMoveAngle_flg)の場合、<BR>
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
     * <B>移動方角（Z軸回転）の角速度が 0 ならば、何も起こりません。</B>動作させるには、角速度が必要です。<BR>
     * 内部的には、addRzMoveAngle(int) が毎フレーム行われる仕組みです。(this->behave()で実行)<BR>
     * 目標の移動方角（Z軸回転）に到達したならば、この目標の移動方角（Z軸回転）自動停止機能は解除されます。<BR>
     *
     * @param	prm_angRzMove	到達目標の移動方角（Z軸回転）(-360,000～360,000)
     * @param	prm_way_allow  自動停止機能が有効になる進入回転方向
     * @param	prm_angveloAllowRyMove 停止機能が有効になる移動方角角速度
     */
    void setStopTarget_RzMoveAngle(angle prm_angRzMove,
                                      int prm_way_allow = TURN_BOTH,
                                      angvelo prm_angveloAllowRyMove = ANGLE180);

    /**
     * Actorの目標の移動方角（Z軸回転）自動停止機能を有効(目標の移動方角（Z軸回転）を現在Z軸座標からの対象Z軸座標で設定)<BR>
     * 機能はsetStopTarget_RzMoveAngle(int)と同じ<BR>
     *
     * @param	prm_tX	xRz座標
     * @param	prm_tY	yRy座標
     * @param	prm_way_allow  自動停止機能が有効になる進入回転方向
     * @param	prm_angveloAllowRyMove 停止機能が有効になる移動方角角速度
     */
    void setStopTarget_RzMoveAngleV(int prm_tX,
                                       int prm_tY,
                                       int prm_way_allow = TURN_BOTH,
                                       angvelo prm_angveloAllowRyMove = ANGLE180);

    void setRzMoveAngleVelocity(angvelo prm_angveloRzMove);

    void setRzMoveAngleVeloRenge(angvelo prm_angveloRzMove01, angvelo prm_angveloRzMove02);

    void setRzMoveAngleVeloAcceleration(angacce prm_angacceRzMove);

    angle getRzMoveAngleDistance(int prm_tX, int prm_tY, int prm_way);

    /**
     * 自身の移動方角のZ軸回転角( _angRzMove )と、ターゲットの回転角との差分を取得.
     * TURN_COUNTERCLOCKWISE ･･･ 回転方向が左回りで差異角取得、正の値で返る。
     * TURN_CLOCKWISE        ･･･ 回転方向が右回りで差異角取得、負の値に返る。
     * TURN_CLOSE_TO         ･･･ ターゲットの回転角と距離が近い方の回転方向で取得、正又は負の値になる。
     * TURN_ANTICLOSE_TO     ・・・ターゲットの回転角と距離が遠い方の回転方向で取得、正又は負の値になる。
     * @param prm_angTargetRzMove ターゲット角の値
     * @param prm_way TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @return
     */
    angle getRzMoveAngleDistance(angle prm_angTargetRzMove, int prm_way);

    /**
     * Actorの移動方角（Y軸回転）を設定。<BR>
     * 加算後の移動方角（Y軸回転）が範囲外（0～360,000 以外）の値になっても、正しい 0～360,000 の範囲内の値に再計算されます。<BR>
     * 自動前方向き機能が有効(_synchronize_RyFaceAngle_to_RyMoveAngle_flg)の場合、<BR>
     * Actorの向きも移動方角（Y軸回転）と同じ方向を向くように setStopTarget_FaceAngle(int) も実行されます。<BR>
     *
     * @param	prm_angRyMove	移動方角（Y軸回転）(0～360,000)
     */
    void setRyMoveAngle(angle prm_angle);

    /**
     * Actorの移動方角（Y軸回転）を現在Y軸座標からの対象Y軸座標への方向を割り出し、設定する。<BR>
     * 自動前方向き機能が有効(_synchronize_RyFaceAngle_to_RyMoveAngle_flg)の場合、<BR>
     * ActorのZ軸方角（向き）も移動方角（Y軸回転）と同じ方向を向くように setStopTarget_FaceAngle(int) が実行されます。<BR>
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
     * また、自動前方向き機能が有効(_synchronize_RyFaceAngle_to_RyMoveAngle_flg)の場合、<BR>
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
     * <B>移動方角（Y軸回転）の角速度が 0 ならば、何も起こりません。</B>動作させるには、角速度が必要です。<BR>
     * 内部的には、addRyMoveAngle(int) が毎フレーム行われる仕組みです。(this->behave()で実行)<BR>
     * 目標の移動方角（Y軸回転）に到達したならば、この目標の移動方角（Y軸回転）自動停止機能は解除されます。<BR>
     *
     * @param	prm_angRyMove	到達目標の移動方角（Y軸回転）(-360,000～360,000)
     * @param	prm_way_allow  自動停止機能が有効になる進入回転方向
     * @param	prm_angveloAllowRyMove 停止機能が有効になる移動方角角速度
     */
    void setStopTarget_RyMoveAngle(angle prm_angRyMove,
                                      int _move_angle_ry_target_allow_way = TURN_BOTH,
                                      angvelo prm_angveloAllowRyMove = ANGLE180);

    /**
     * Actorの目標の移動方角（Y軸回転）自動停止機能を有効(目標の移動方角（Y軸回転）を現在Y軸座標からの対象Y軸座標で設定)<BR>
     * 機能はsetStopTarget_RyMoveAngle(int)と同じ<BR>
     *
     * @param	prm_tX	xRy座標
     * @param	prm_tY	yRy座標
     * @param	prm_way_allow  自動停止機能が有効になる進入回転方向
     * @param	prm_angveloAllowRyMove 停止機能が有効になる移動方角角速度
     */
    void setStopTarget_RyMoveAngleV(int prm_tX,
                                       int prm_tY,
                                       int _move_angle_ry_target_allow_way = TURN_BOTH,
                                       angvelo prm_angveloAllowRyMove = ANGLE180);

    void setRyMoveAngleVelocity(angvelo prm_angveloRyMove);

    void setRyMoveAngleVeloRenge(angvelo prm_angveloRyMove01, angvelo prm_angveloRyMove02);

    void setRyMoveAngleVeloAcceleration(angacce prm_angacceRyMove);

    angle getRyMoveAngleDistance(int prm_tX, int prm_tY, int prm_way);

    angle getRyMoveAngleDistance(angle prm_angTargetRyMove, int prm_way);

    /**
     * 緯度経度指定で移動方向を設定。.
     * @param prm_angRz
     * @param prm_angRy
     */
    void setRzRyMoveAngle(angle prm_angRz, angle prm_angRy);

    /**
     * 目標座標指定で移動方角を設定。.
     * 方向ベクトル正規化も内部で行なう。
     * @param prm_tX
     * @param prm_tY
     * @param prm_tZ
     */
    void setMoveAngle(int prm_tX, int prm_tY, int prm_tZ);

    void setMoveAngle(GgafDx9GeometricActor* prm_pActor_Target);

    void setStopTarget_RzRyMoveAngle(int prm_tX, int prm_tY, int prm_tZ);

    void setStopTarget_RzRyMoveAngle(GgafDx9GeometricActor* prm_pActor_Target);

    //virtual void behave();

    void setVxMoveVelocity(velo prm_veloVxMove);
    void setVxMoveVeloRenge(velo prm_veloVxMove01, velo prm_veloVxMove02);
    void setVxMoveVeloAcceleration(acce prm_acceVxMove);

    void setVyMoveVelocity(velo prm_veloVyMove);
    void setVyMoveVeloRenge(velo prm_veloVyMove01, velo prm_veloVyMove02);
    void setVyMoveVeloAcceleration(acce prm_acceVyMove);

    void setVzMoveVelocity(velo prm_veloVzMove);
    void setVzMoveVeloRenge(velo prm_veloVzMove01, velo prm_veloVzMove02);
    void setVzMoveVeloAcceleration(acce prm_acceVzMove);


    /**
     * スプラインプログラム実行
     * @param prm_progSP スプラインプログラム
     * @param prm_option オプション。GgafDx9SplineProgram実オブジェクトに依存する。GgafDx9SplineProgram継承クラスを参照せよ。
     */
    void executeSplineMoveProgram(GgafDx9SplineProgram* prm_progSP, int prm_option);



    /**
     * 軸回転方角を目標にターゲットするシークエンスを実行 .
     * @param prm_tX 目標X座標
     * @param prm_tY 目標Y座標
     * @param prm_tZ 目標Z座標
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingFaceAngleSequence(int prm_tX, int prm_tY, int prm_tZ,
                                           angvelo prm_angVelocity,
                                           int prm_way);
    /**
     * 軸回転方角を目標にターゲットするシークエンスを実行 .
     * @param prm_angRz_Target 目標軸回転方角(Z軸)
     * @param prm_angRy_Target 目標軸回転方角(Y軸)
     * @param prm_angVelocity ターゲットへ軸回転方角を回転移動中に適用する目標軸回転方角回転移動角速度
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingFaceAngleSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                           angvelo prm_angVelocity, int prm_way);

    /**
     * 軸回転方角を目標にターゲットの座標にするシークエンスを実行
     * @param prm_pActor_Target 目標オブジェクト
     * @param prm_angVelocity ターゲット遂行中に許される角速度
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingFaceAngleSequence(GgafDx9GeometricActor* prm_pActor_Target,
                                           angvelo prm_angVelocity,
                                           int prm_way = TURN_CLOSE_TO) {
        executeTagettingFaceAngleSequence(
                prm_pActor_Target->_X,
                prm_pActor_Target->_Y,
                prm_pActor_Target->_Z,
                prm_angVelocity,
                prm_way
        );
    }




    /**
     * 軸回転方角(Z軸)を目標にターゲットするシークエンスを実行 .
     * @param prm_angRz_Target 目標軸回転方角(Z軸)
     * @param prm_angVelocity ターゲットへ軸回転方角を回転移動中に適用する目標軸回転方角回転移動角速度
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingRzFaceAngleSequence(angle prm_angRz_Target, angvelo prm_angVelocity, int prm_way);

    /**
     * 軸回転方角(Y軸)を目標にターゲットするシークエンスを実行 .
     * @param prm_angRy_Target 目標軸回転方角(Y軸)
     * @param prm_angVelocity ターゲットへ軸回転方角を回転移動中に適用する目標軸回転方角回転移動角速度
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingRyFaceAngleSequence(angle prm_angRy_Target, angvelo prm_angVelocity, int prm_way);




    void executeTagettingRxSpinAngleSequence(angle prm_angRx_Target, angvelo prm_angVelocity, int prm_way);



    /**
     * 移動方角を目標にターゲットするシークエンスを実行 .
     * @param prm_tX 目標X座標
     * @param prm_tY 目標Y座標
     * @param prm_tZ 目標Z座標
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingMoveAngleSequence(int prm_tX, int prm_tY, int prm_tZ,
                                           angvelo prm_angVelocity,
                                           int prm_way);
    /**
     * 移動方角を目標にターゲットするシークエンスを実行 .
     * @param prm_angRz_Target 目標移動方角(Z軸)
     * @param prm_angRy_Target 目標移動方角(Y軸)
     * @param prm_angVelocity ターゲットへ移動方角を回転移動中に適用する目標移動方角回転移動角速度
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingMoveAngleSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                           angvelo prm_angVelocity, int prm_way);

    /**
     * 移動方角を目標にターゲットの座標にするシークエンスを実行
     * @param prm_pActor_Target 目標オブジェクト
     * @param prm_angVelocity ターゲット遂行中に許される角速度
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingMoveAngleSequence(GgafDx9GeometricActor* prm_pActor_Target,
                                           angvelo prm_angVelocity,
                                           int prm_way = TURN_CLOSE_TO) {
        executeTagettingMoveAngleSequence(
                prm_pActor_Target->_X,
                prm_pActor_Target->_Y,
                prm_pActor_Target->_Z,
                prm_angVelocity,
                prm_way
        );
    }

    /**
     * 移動方角(Z軸)を目標にターゲットするシークエンスを実行 .
     * @param prm_angRz_Target 目標移動方角(Z軸)
     * @param prm_angVelocity ターゲットへ移動方角を回転移動中に適用する目標移動方角回転移動角速度
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingRzMoveAngleSequence(angle prm_angRz_Target, angvelo prm_angVelocity, int prm_way);

    /**
     * 移動方角(Y軸)を目標にターゲットするシークエンスを実行 .
     * @param prm_angRy_Target 目標移動方角(Y軸)
     * @param prm_angVelocity ターゲットへ移動方角を回転移動中に適用する目標移動方角回転移動角速度
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingRyMoveAngleSequence(angle prm_angRy_Target, angvelo prm_angVelocity, int prm_way);

    /**
     * 毎フレームのActorの振る舞い。<BR>
     * 本クラスを利用する場合は、このbehave() を毎フレーム実行します。<BR>
     */
    virtual void behave();

    virtual ~GgafDx9GeometryMover();
};

}
#endif /*GGAFDX9GEOMETRYMOVER_H_*/

