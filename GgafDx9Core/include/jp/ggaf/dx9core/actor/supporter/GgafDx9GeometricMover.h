#ifndef GGAFDX9GEOMETRICMOVER_H_
#define GGAFDX9GEOMETRICMOVER_H_
namespace GgafDx9Core {

//軸X
#define AXIS_X 0
//軸Y
#define AXIS_Y 1
//軸Z
#define AXIS_Z 2


/**
 * 座標計算支援クラス .
 * GgafDx9GeometricActor のメンバの<BR>
 *  _X ,  _Y,  _Z  ・・・ アクターの座標<BR>
 * _RX , _RY, _RZ  ・・・ アクターの軸回転角度<BR>
 * を、簡単に操作するために設計。<BR>
 * TODO:いつの間にか肥大化。分割せよ。
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class GgafDx9GeometricMover : public GgafCore::GgafObject {
    float _dummy1, _dummy2, _dummy3;

public:
    /** 対象アクター */
    GgafDx9GeometricActor* _pActor;
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用Actor
     */
    GgafDx9GeometricMover(GgafDx9GeometricActor* prm_pActor);



public: //_RX , _RY, _RZ 操作関連 //////////////////////////////////////////////

    /** キャラの軸回転方角の方角(0～360,000) */
    angle _angFace[3];
    /** 軸回転方角の角速度（軸回転方角に毎フレーム加算する方角） */
    angvelo _angveloFace[3];
    /** 軸回転方角の角速度上限(最高値は360,000) */
    angvelo _angveloTopFace[3];
    /** 軸回転方角の角速度下限(最高値は-360,000) */
    angvelo _angveloBottomFace[3];
    /** 軸回転方角の角加速度（角速度に毎フレーム加算する値） */
    angacce _angacceFace[3];
    /** 軸回転方角の角躍度（角加速度に毎フレーム加算する値） */
    angjerk _angjerkFace[3];
    /** 目標の軸回転方角自動停止機能有効フラグ */
    bool _face_ang_targeting_flg[3];
    /** 目標とするキャラの軸回転方角の方角(0～360,000) */
    angle _angTargetFace[3];
    /** 目標の軸回転方角自動停止機能が有効になる回転方向 */
    int _face_ang_target_allow_way[3]; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** 目標の軸回転方角自動停止機能が有効になる角速度（回転正負共通） */
    angvelo _face_ang_target_allow_velo[3]; //この角速度より小さい値の場合機能有効とするz

    /**
     * Actorの軸の回転方角を設定。<BR>
     * @param	prm_axis	回転軸(AXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angFace	方角のアングル値(-360,000～360,000)
     */
    void setFaceAng(int prm_axis, angle prm_angFace);

    /**
     * Actorの軸の回転方角を対象座標に向ける。<BR>
     * @param prm_tX 対象X座標
     * @param prm_tY 対象Y座標
     * @param prm_tZ 対象Z座標
     */
    void setFaceAng(int prm_tX, int prm_tY, int prm_tZ);

    /**
     * 現在の Actor の軸回転方角へ加算（負で減算）。<BR>
     *
     * 引数に渡すのは、軸回転方角の増分です。Actorの軸回転方角（_angFace）を相対指定でるメソッドです。<BR>
     * 加算後の軸回転方角のアングル値はが単純化されます。
     * 引数である加算（減算）する軸回転方角は、軸回転角角速度の上限と下限の間の範囲に限ります。<BR>
     * つまり、引数の有効な範囲は以下の通りとなります。<BR>
     *
     *   _iBottom_RotVeloAngle ≦ 引数の回転軸方角値の増分 ≦ _angveloTopRot  です。<BR>
     *
     * もし加算（減算）後、範囲外になった場合、直近の範囲内の値に強制的に抑えられます。<BR>
     * 【補足：】<BR>
     * デフォルトの回転加速度の上限と下限（_iBottom_RotVeloAngle、_angveloTopRot) は<BR>
     *
     *  -360,000 ≦ 引数の動方角増分 ≦ 360,000<BR>
     *
     * @param	prm_axis	回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angDistance	回転軸方角値の増分アングル値(範囲：_iBottom_RotVeloAngle ～ _angveloTopRot)
     */
    void addFaceAng(int prm_axis, angle prm_angDistance);

    /**
     * Actorの目標の軸回転方角自動停止機能を有効(目標の軸回転方角設定)<BR>
     * 引数に設定された軸回転方角になると、軸回転方角角速度及び軸回転方角角加速度を 0 にし、回転を停止させます。<BR>
     * 軸回転方角角速度等の設定を併せて実行して、まずは軸回転も行なってください。<BR>
     * 軸回転方角角速度が 0 の場合、何も起こりません。本メソッドを実行したからと言って勝手に向きが変わるとという意味ではありません。 <BR>
     * 内部的には、addFaceAng(prm_axis, int) が毎フレーム行われる仕組みです。<BR>
     * 目標の回転方角に到達したならば、この目標の軸回転方角自動停止機能は解除(内部のフラグをアンセット)されます。<BR>
     * @param	prm_axis	回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angTargetRot	到達目標の回転方角(0～360,000)
     * @param	prm_way_allow  自動停止を許可する進入方向(TURN_CLOCKWISE/TURN_COUNTERCLOCKWISE/TURN_BOTH)
     * @param	prm_angveloAllow 自動停止機能が有効になる回転角速度
     */
    void setStopTarget_FaceAng(int prm_axis,
                                 angle prm_angTargetRot,
                                 int prm_way_allow = TURN_BOTH,
                                 angvelo prm_angveloAllow = ANGLE180);

    /**
     * Actorの目標回転方向自動停止機能を有効(現在XY座標からの対象XY座標で設定)<BR>
     * @param	prm_axis	回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_tX	対象X座標
     * @param	prm_tY	対象Y座標
     * @param	prm_way_allow  自動停止機能が有効になる回転方向
     * @param	prm_angveloAllowRyMv 自動停止機能が有効になる回転角速度
     */
    void setStopTarget_FaceAngV(int prm_axis,
                                  int prm_tX,
                                  int prm_tY,
                                  int prm_way_allow = TURN_BOTH,
                                  angvelo prm_angveloAllowRyMv = ANGLE180);

    void setFaceAngVelo(int prm_axis, angvelo prm_angveloRot);

    void forceFaceAngVeloRange(int prm_axis,
                                  angvelo prm_angveloRot01,
                                  angvelo prm_angveloRot02);

    void setFaceAngAcce(int prm_axis, angacce prm_angacceRot);

    angle getFaceAngDistance(int prm_axis, int prm_tX, int prm_tY, int prm_way);

    angle getFaceAngDistance(int prm_axis, angle prm_angTargetRot, int prm_way);

    ////////////////////////////////////////////////////MOVER

public: //_X , _Y, _Z 操作関連 //////////////////////////////////////////////
    /** キャラの移動方角単位ベクトル */
    float _vX, _vY, _vZ;
    /** 移動方角のZ軸回転角 */
    angle _angRzMv;
    /** 移動方角のY軸回転角 */
    angle _angRyMv;
    /** 移動速度 */
    velo _veloMv;
    /** 移動速度上限 */
    velo _veloTopMv;
    /** 移動速度下限 */
    velo _veloBottomMv;
    /** 移動加速度 */
    acce _accMv;
    /** 移動躍度 */
    jerk _jerkMv;

    /** 移動方角（Z軸回転）の角速度（移動方角（Z軸回転）に毎フレーム加算する方角） */
    angvelo _angveloRzMv;
    /** 移動方角（Z軸回転）の角速度上限(最高値は360,000) */
    angvelo _angveloRzTopMv;
    /** 移動方角（Z軸回転）の角速度下限(最高値は-360,000) */
    angvelo _angveloRzBottomMv;
    /** 移動方角（Z軸回転）の角加速度（角速度に毎フレーム加算する値） */
    angacce _angacceRzMv;
    /** 移動方角（Z軸回転）の角躍度（角加速度に毎フレーム加算する値） */
    angjerk _angjerkRzMv;
    /** 目標の移動方角（Z軸回転）自動停止機能有効フラグ */
    bool _mv_ang_rz_target_flg;
    /** 目標とするキャラの移動方角（Z軸回転）の方角(0～360,000) */
    angle _angTargetRzMv;
    /** 目標の移動方角（Z軸回転）自動停止機能が有効になる進入回転方向 */
    int _mv_ang_rz_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** 目標の移動方角（Z軸回転）自動停止機能が有効になる移動方角角速度 */
    angvelo _mv_ang_rz_target_allow_velo;
    /** 自動前方向き機能有効フラグ */
    bool _relate_RzFaceAng_to_RzMvAng_flg;
    //true  : 移動方角（Z軸回転）を変更すると、それに伴い同じ方角が軸回転方角(Z軸)にも設定される
    //false : 移動方角（Z軸回転）とZ軸軸回転方角は独立

    /** 移動方角（Y軸回転）の角速度（移動方角（Y軸回転）に毎フレーム加算する方角） */
    angvelo _angveloRyMv;
    /** 移動方角（Y軸回転）の角速度上限(最高値は360,000) */
    angvelo _angveloRyTopMv;
    /** 移動方角（Y軸回転）の角速度下限(最高値は-360,000) */
    angvelo _angveloRyBottomMv;
    /** 移動方角（Y軸回転）の角加速度（角速度に毎フレーム加算する値） */
    angacce _angacceRyMv;
    /** 移動方角（Y軸回転）の角躍度（角加速度に毎フレーム加算する値） */
    angjerk _angjerkRyMv;
    /** 目標の移動方角（Y軸回転）自動停止機能有効フラグ */
    bool _mv_ang_ry_target_flg;
    /** 目標とするキャラの移動方角（Y軸回転）の方角(0～360,000) */
    int _angTargetRyMv;
    /** 目標の移動方角（Y軸回転）自動停止機能が有効になる進入回転方向 */
    int _mv_ang_ry_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** 目標の移動方角（Y軸回転）自動停止機能が有効になる移動方角角速度 */
    int _mv_ang_ry_target_allow_velo;
    /** 自動前方向き機能有効フラグ */
    bool _relate_RyFaceAng_to_RyMvAng_flg;
    //true  : 移動方角（Y軸回転）を変更すると、それに伴い同じ方角が軸回転方角(Y軸)にも設定される
    //false : 移動方角（Y軸回転）とY軸軸回転方角は独立

    /** X軸方向移動速度 */
    velo _veloVxMv;
    /** X軸方向移動速度上限 */
    velo _veloTopVxMv;
    /** X軸方向移動速度下限 */
    velo _veloBottomVxMv;
    /** X軸方向移動加速度 */
    acce _acceVxMv;
    /** X軸方向移動加速度上限*/
    acce _acceTopVxMv;
    /** X軸方向移動加速度下限*/
    acce _acceBottomVxMv;
    /** Y軸方向移動速度 */
    velo _veloVyMv;
    /** Y軸方向移動速度上限 */
    velo _veloTopVyMv;
    /** Y軸方向移動速度下限 */
    velo _veloBottomVyMv;
    /** Y軸方向移動加速度 */
    acce _acceVyMv;
    /** Y軸方向移動加速度上限*/
    acce _acceTopVyMv;
    /** Y軸方向移動加速度下限*/
    acce _acceBottomVyMv;
    /** Z軸方向移動速度 */
    velo _veloVzMv;
    /** Z軸方向移動速度上限 */
    velo _veloTopVzMv;
    /** Z軸方向移動速度下限 */
    velo _veloBottomVzMv;
    /** Z軸方向移動加速度 */
    acce _acceVzMv;
    /** Z軸方向移動加速度上限*/
    acce _acceTopVzMv;
    /** Z軸方向移動加速度下限*/
    acce _acceBottomVzMv;

    /** なめらかな移動シークエンスを実行中はtrue */
    bool _smooth_mv_velo_seq_flg;
    /** なめらかな移動シークエンスを実行完了時の加速度設定（true：加速度0に設定／false:加速度をそのままにしておく） */
    bool _smooth_mv_velo_seq_endacc_flg;
    /** なめらかな移動シークエンスで設定されたトップスピード（等速移動時速度） */
    velo _smooth_mv_velo_seq_top_velo;
    /** なめらかな移動シークエンスで設定された終了時の速度 */
    velo _smooth_mv_velo_seq_end_velo;
    /** なめらかな移動シークエンスで設定された目標移動距離 */
    int  _smooth_mv_velo_seq_distance_of_target;
    /** なめらかな移動シークエンスに開始から現在までの移動距離 */
    int  _smooth_mv_velo_seq_mv_distance;
    /** なめらかな移動シークエンスで設定された加速～等速へ切り替わる距離の位置 */
    int  _smooth_mv_velo_seq_distance_of_p1;
    /** なめらかな移動シークエンスで設定された等速～減速へ切り替わる距離の位置 */
    int  _smooth_mv_velo_seq_distance_of_p2;
    /** なめらかな移動シークエンスの進捗状況 */
    int  _smooth_mv_velo_seq_progress;


    /**
     * 移動速度を設定 .
     * @param	prm_veloMv	移動速度
     */
    void setMvVelo(velo prm_veloMv);

    /**
     * 移動速度を加算 .
     * @param prm_veloMv_Offset 加算移動速度
     */
    void addMvVelo(velo prm_veloMv_Offset);

    /**
     * 移動速度の上限下限を設定し、移動速度の範囲を制限する .
     * 引数の移動速度１、移動速度２の大小はどちらでもかまわない。（内部で判定する）
     * @param prm_veloMv01  移動速度１
     * @param prm_veloMv02  移動速度２
     */
    void forceMvVeloRange(velo prm_veloMv01, velo prm_veloMv02);

    /**
     * 移動加速度を設定 .
     * @param prm_acceMove 移動加速度
     */
    void setMvAcce(acce prm_acceMove);

    /**
     * 移動加速度を、「停止移動距離」により設定する .
     * <pre><code>
     *    速度
     *     ^       a:減加速度
     *     |       S:移動距離（停止に費やす距離）
     *     |      v0:現時点の速度
     *   v0|       t:停止するフレーム
     *     |＼
     *     |  ＼
     *     |    ＼ 傾きはa
     *     | S    ＼
     *   --+--------＼-----> 時間(フレーム)
     *   0 |         t
     *
     *    S = (1/2) v0 t  ・・・①
     *    a = -v0 / t     ・・・②
     *    ①より
     *    t = 2S / v0
     *    これを②へ代入
     *    a = -v0 / (2S / v0)
     *    ∴ a = -(v0^2) / 2S
     * </code></pre>
     * 具体的には、の上図のような状態を想定し、加速度(a)を計算し設定している。<BR>
     * @param prm_distance_of_target 停止移動距離
     */
    void setMvAcceToStop(int prm_distance_of_target);

    /**
     * 移動加速度を、「目標到達速度」「移動距離」に達するまでに費やす距離、により設定 .
     * <pre><code>
     *
     *    速度
     *     ^        a:加速度
     *     |        S:移動距離（目標到達速度に達するまでに費やす距離）
     *     |       v0:現時点の速度
     *     |       vx:目標到達速度
     *     |       t:目標到達速度に達した時の時間（フレーム数）
     *   vx|........
     *     |      ／|
     *     |    ／  |
     *     |  ／    |   傾きはa
     *     |／      |
     *   v0|  S     |
     *     |        |
     *   --+--------+---> 時間(フレーム)
     *   0 |        t
     *
     *    S = (1/2) (v0 + vx) t   ・・・①
     *    a = (vx-v0) / t         ・・・②
     *    ①より
     *    t = (vx-v0) / a
     *    これを②へ代入
     *    S = (vx^2 - v0^2) / 2a
     *    ∴ a = (vx^2 - v0^2) / 2S
     * </code></pre>
     * 具体的には、の上図のような状態を想定し、加速度(a)を計算し設定している。<BR>
     * 捕捉：setMvAcce(0, d) は setMvAcceToStop(d) と同じである
     * @param prm_velo_target 目標到達速度
     * @param prm_distance_of_target  目標到達速度に達するまでに費やす距離
     */
    void setMvAcce(int prm_distance_of_target, velo prm_velo_target);


    /**
     * Actorの移動方角（Z軸回転）を設定。<BR>
     * 加算後の移動方角（Z軸回転）が範囲外（0～360,000 以外）の値になっても、正しい 0～360,000 の範囲内の値に再計算されます。<BR>
     * 自動前方向き機能が有効(_relate_RzFaceAng_to_RzMvAng_flg)の場合、<BR>
     * Actorの向きも移動方角（Z軸回転）と同じ方向を向くように setStopTarget_FaceAng(int) も実行されます。<BR>
     *
     * @param	prm_ang	移動方角（Z軸回転）(0～360,000)
     */
    void setRzMvAng(angle prm_ang);

    /**
     * Actorの移動方角（Z軸回転）を現在XY座標からの対象XY座標への方向を割り出し、設定する。<BR>
     * 自動前方向き機能が有効(_relate_RzFaceAng_to_RzMvAng_flg)の場合、<BR>
     * ActorのZ軸方角（向き）も移動方角（Z軸回転）と同じ方向を向くように setStopTarget_FaceAng(int) が実行されます。<BR>
     *
     * @param	prm_tX	対象xZ軸座標
     * @param	prm_tY	対象yZ軸座標
     */
    void setRzMvAng(int prm_tX, int prm_tY);

    /**
     * 現在の Actor の移動方角（Z軸回転）へ加算（負で減算）。<BR>
     *
     * 引数に渡すのは、移動方角（Z軸回転）の増分です。Actorの移動方角（Z軸回転）（_angRzMv）を相対指定でるメソッドです。<BR>
     * 加算後の移動方角（Z軸回転）が範囲外（0～360,000 以外）の値になっても、最終的には setRzMvAng(int) を呼び出しますので<BR>
     * 正しい 0～360,000 の範囲内の値に再設定されます。<BR>
     * 引数である加算（減算）する移動方角（Z軸回転）は、Z軸移動加速度の上限と下限の間の範囲に限ります。<BR>
     * つまり、引数の有効な範囲は以下の通りとなります。<BR>
     *
     *   _angveloRzBottomMv ≦ 引数の動方角増分 ≦ _angveloRzTopMv  です。<BR>
     *
     * もし範囲外の引数の移動方角（Z軸回転）増分を指定した場合は、直近の範囲内の値に強制的に抑えられ、その値が加算されます。<BR>
     * また、自動前方向き機能が有効(_relate_RzFaceAng_to_RzMvAng_flg)の場合、<BR>
     * 加算後の移動方角（Z軸回転）の値が、Z軸の目標の軸回転方角として設定されます。（自動で前方を向くに設定されます。但し前方＝アングル0のキャラの場合ですけど；）<BR>
     *
     * 【補足：】<BR>
     * 本メソッド毎フレーム実行することでXY平面の円運動が可能になります。<BR>
     * 引数の移動方角（Z軸回転）が、数直線上の 0 に、より近い値を加算し続けた場合は、緩やかなカーブ描きながら向転換することを意味します。<BR>
     * 逆に、引数の移動方角（Z軸回転）が、0 から、より離れた値を加算し続けた場合は、より鋭角的なカーブ描きながら向転換することを意味します。<BR>
     * デフォルトのZ軸移動加速度の上限と下限（_angveloRzBottomMv、_angveloRzTopMv) は<BR>
     *
     *  -360,000 ≦ 引数の動方角増分 ≦ 360,000<BR>
     *
     * となっています。これは瞬時に（1フレームで）どんな移動方角（Z軸回転）にも向きを変えれることを意味します。<BR>
     *
     * @param	prm_angDistance	移動方角（Z軸回転）増分(範囲：_angveloRzBottomMv ～ _angveloRzTopMv)
     */
    void addRzMvAng(angle prm_angDistance);

    /**
     * Actorの目標の移動方角（Z軸回転）自動停止機能を有効(目標の移動方角（Z軸回転）設定)<BR>
     * 引数に設定された移動方角（Z軸回転）になるまで、移動方角（Z軸回転）を加算(減算)を毎フレーム行い続けます。<BR>
     * 加算か減算かは、移動方角（Z軸回転）の角速度（_angveloRzMv）の正負で決定されます。<BR>
     * <B>移動方角（Z軸回転）の角速度が 0 ならば、何も起こりません。</B>動作させるには、角速度が必要です。<BR>
     * 内部的には、addRzMvAng(int) が毎フレーム行われる仕組みです。(this->behave()で実行)<BR>
     * 目標の移動方角（Z軸回転）に到達したならば、この目標の移動方角（Z軸回転）自動停止機能は解除されます。<BR>
     *
     * @param	prm_angRzMv	到達目標の移動方角（Z軸回転）(-360,000～360,000)
     * @param	prm_way_allow  自動停止機能が有効になる進入回転方向
     * @param	prm_angveloAllowRyMv 停止機能が有効になる移動方角角速度
     */
    void setStopTarget_RzMvAng(angle prm_angRzMv,
                               int prm_way_allow = TURN_BOTH,
                               angvelo prm_angveloAllowRyMv = ANGLE180);

    /**
     * Actorの目標の移動方角（Z軸回転）自動停止機能を有効(目標の移動方角（Z軸回転）を現在Z軸座標からの対象Z軸座標で設定)<BR>
     * 機能はsetStopTarget_RzMvAng(int)と同じ<BR>
     *
     * @param	prm_tX	xRz座標
     * @param	prm_tY	yRy座標
     * @param	prm_way_allow  自動停止機能が有効になる進入回転方向
     * @param	prm_angveloAllowRyMv 停止機能が有効になる移動方角角速度
     */
    void setStopTarget_RzMvAngV(int prm_tX,
                                       int prm_tY,
                                       int prm_way_allow = TURN_BOTH,
                                       angvelo prm_angveloAllowRyMv = ANGLE180);

    void setRzMvAngVelo(angvelo prm_angveloRzMv);

    void forceRzMvAngVeloRange(angvelo prm_angveloRzMv01, angvelo prm_angveloRzMv02);

    void setRzMvAngAcce(angacce prm_angacceRzMv);

    angle getRzMvAngDistance(int prm_tX, int prm_tY, int prm_way);

    /**
     * 自身の移動方角のZ軸回転角( _angRzMv )と、ターゲットの回転角との差分を取得.
     * TURN_COUNTERCLOCKWISE ・・・ 回転方向が左回りで差異角取得、正の値で返る。
     * TURN_CLOCKWISE        ・・・ 回転方向が右回りで差異角取得、負の値に返る。
     * TURN_CLOSE_TO         ・・・ ターゲットの回転角と距離が近い方の回転方向で取得、正又は負の値になる。
     * TURN_ANTICLOSE_TO     ・・・ターゲットの回転角と距離が遠い方の回転方向で取得、正又は負の値になる。
     * @param prm_angTargetRzMv ターゲット角の値
     * @param prm_way TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @return
     */
    angle getRzMvAngDistance(angle prm_angTargetRzMv, int prm_way);

    /**
     * Actorの移動方角（Y軸回転）を設定。<BR>
     * 加算後の移動方角（Y軸回転）が範囲外（0～360,000 以外）の値になっても、正しい 0～360,000 の範囲内の値に再計算されます。<BR>
     * 自動前方向き機能が有効(_relate_RyFaceAng_to_RyMvAng_flg)の場合、<BR>
     * Actorの向きも移動方角（Y軸回転）と同じ方向を向くように setStopTarget_FaceAng(int) も実行されます。<BR>
     * @param prm_ang 移動方角（Y軸回転）(0～360,000)
     */
    void setRyMvAng(angle prm_ang);

    /**
     * Actorの移動方角（Y軸回転）を現在Y軸座標からの対象Y軸座標への方向を割り出し、設定する。<BR>
     * 自動前方向き機能が有効(_relate_RyFaceAng_to_RyMvAng_flg)の場合、<BR>
     * ActorのZ軸方角（向き）も移動方角（Y軸回転）と同じ方向を向くように setStopTarget_FaceAng(int) が実行されます。<BR>
     *
     * @param	prm_tX	対象xY軸座標
     * @param	prm_tY	対象yY軸座標
     */
    void setRyMvAng(int prm_tX, int prm_tY);

    /**
     * 現在の Actor の移動方角（Y軸回転）へ加算（負で減算）。<BR>
     *
     * 引数に渡すのは、移動方角（Y軸回転）の増分です。Actorの移動方角（Y軸回転）（_angRyMv）を相対指定でるメソッドです。<BR>
     * 加算後の移動方角（Y軸回転）が範囲外（0～360,000 以外）の値になっても、最終的には setRyMvAng(int) を呼び出しますので<BR>
     * 正しい 0～360,000 の範囲内の値に再設定されます。<BR>
     * 引数である加算（減算）する移動方角（Y軸回転）は、Y軸移動加速度の上限と下限の間の範囲に限ります。<BR>
     * つまり、引数の有効な範囲は以下の通りとなります。<BR>
     *
     *   _angveloRyBottomMv ≦ 引数の動方角増分 ≦ _angveloRyTopMv  です。<BR>
     *
     * もし範囲外の引数の移動方角（Y軸回転）増分を指定した場合は、直近の範囲内の値に強制的に抑えられ、その値が加算されます。<BR>
     * また、自動前方向き機能が有効(_relate_RyFaceAng_to_RyMvAng_flg)の場合、<BR>
     * 加算後の移動方角（Y軸回転）の値が、Z軸の目標の軸回転方角として設定されます。（自動で前方を向くに設定されます。但し前方＝アングル0のキャラの場合ですけど；）<BR>
     *
     * 【補足：】<BR>
     * 本メソッド毎フレーム実行することでXZ平面の円運動が可能になります。<BR>
     * 引数の移動方角（Y軸回転）が、数直線上の 0 に、より近い値を加算し続けた場合は、緩やかなカーブ描きながら向転換することを意味します。<BR>
     * 逆に、引数の移動方角（Y軸回転）が、0 から、より離れた値を加算し続けた場合は、より鋭角的なカーブ描きながら向転換することを意味します。<BR>
     * デフォルトのY軸移動加速度の上限と下限（_angveloRyBottomMv、_angveloRyTopMv) は<BR>
     *
     *  -360,000 ≦ 引数の動方角増分 ≦ 360,000<BR>
     *
     * となっています。これは瞬時に（1フレームで）どんな移動方角（Y軸回転）にも向きを変えれることを意味します。<BR>
     *
     * @param	prm_angDistance	移動方角（Y軸回転）増分(範囲：_angveloRyBottomMv ～ _angveloRyTopMv)
     */
    void addRyMvAng(angle prm_angDistance);

    /**
     * Actorの目標のY軸回転移動方角の自動停止機能を有効 .
     * 目標の移動方角（Y軸回転）設定する。<BR>
     * 引数に設定された移動方角（Y軸回転）になるまで、移動方角（Y軸回転）を加算(減算)を毎フレーム行い続けます。<BR>
     * 加算か減算かは、移動方角（Y軸回転）の角速度（_angveloRyMv）の正負で決定されます。<BR>
     * <B>移動方角（Y軸回転）の角速度が 0 ならば、何も起こりません。</B>動作させるには、角速度が必要です。<BR>
     * 内部的には、addRyMvAng(int) が毎フレーム行われる仕組みです。(this->behave()で実行)<BR>
     * 目標の移動方角（Y軸回転）に到達したならば、この目標の移動方角（Y軸回転）自動停止機能は解除されます。<BR>
     *
     * @param	prm_angRyMv	到達目標の移動方角（Y軸回転）(-360,000～360,000)
     * @param	prm_mv_ang_ry_target_allow_way  自動停止機能が有効になる進入回転方向
     * @param	prm_angveloAllowRyMv 停止機能が有効になる移動方角角速度
     */
    void setStopTarget_RyMvAng(angle prm_angRyMv,
                               int prm_mv_ang_ry_target_allow_way = TURN_BOTH,
                               angvelo prm_angveloAllowRyMv = ANGLE180);

    /**
     * Actorの目標のY軸回転移動方角自動停止機能を有効 .
     * 目標の移動方角（Y軸回転）を現在Y軸座標からの対象Y軸座標で設定<BR>
     * 機能はsetStopTarget_RyMvAng(int)と同じ<BR>
     * @param	prm_tX	xRy座標
     * @param	prm_tY	yRy座標
     * @param	prm_mv_ang_ry_target_allow_way  自動停止機能が有効になる進入回転方向
     * @param	prm_angveloAllowRyMv 停止機能が有効になる移動方角角速度
     */
    void setStopTarget_RyMvAngV(int prm_tX,
                                int prm_tY,
                                int prm_mv_ang_ry_target_allow_way = TURN_BOTH,
                                angvelo prm_angveloAllowRyMv = ANGLE180);

    void setRyMvAngVelo(angvelo prm_angveloRyMv);

    void forceRyMvAngVeloRange(angvelo prm_angveloRyMv01, angvelo prm_angveloRyMv02);

    void setRyMvAngAcce(angacce prm_angacceRyMv);

    angle getRyMvAngDistance(int prm_tX, int prm_tY, int prm_way);

    angle getRyMvAngDistance(angle prm_angTargetRyMv, int prm_way);


    void getRzRyMvAngDistance(int prm_way,
                              angle prm_target_angRz, angle prm_target_angRy,
                              angle& out_d_angRz, angle& out_d_angRy,
                              angle& out_target_angRz, angle& out_target_angRy);

    void getRzRyFaceAngDistance(int prm_way,
                                angle prm_target_angRz, angle prm_target_angRy,
                                angle& out_d_angRz, angle& out_d_angRy,
                                angle& out_target_angRz, angle& out_target_angRy);
    /**
     * 移動方向(RzRy)を設定。.
     * @param prm_angRz
     * @param prm_angRy
     */
    void setRzRyMvAng(angle prm_angRz, angle prm_angRy);

    /**
     *  移動方向(RzRy)を、RyRzで設定。
     * @param prm_angRy
     * @param prm_angRz
     */
    void setRzRyMvAng_by_RyRz(angle prm_angRy, angle prm_angRz);

    /**
     * 目標座標指定で移動方角を設定。.
     * 方向ベクトル正規化も内部で行なう。
     * @param prm_tX
     * @param prm_tY
     * @param prm_tZ
     */
    void setMvAng(int prm_tX, int prm_tY, int prm_tZ);

    void setMvAng(GgafDx9GeometricActor* prm_pActor_Target);

    void setStopTarget_RzRyMvAng(int prm_tX, int prm_tY, int prm_tZ);

    void setStopTarget_RzRyMvAng(GgafDx9GeometricActor* prm_pActor_Target);

    //virtual void behave();

    void setVxMvVelo(velo prm_veloVxMv);
    void addVxMvVelo(velo prm_veloVxMv);
    void forceVxMvVeloRange(velo prm_veloVxMv01, velo prm_veloVxMv02);
    void setVxMvAcce(acce prm_acceVxMv);
    void addVxMvAcce(acce prm_acceVxMv);
    void forceVxMvAcceRange(acce prm_acceVxMv01, acce prm_acceVxMv02);
    void setVyMvVelo(velo prm_veloVyMv);
    void addVyMvVelo(velo prm_veloVyMv);
    void forceVyMvVeloRange(velo prm_veloVyMv01, velo prm_veloVyMv02);
    void setVyMvAcce(acce prm_acceVyMv);
    void addVyMvAcce(acce prm_acceVyMv);
    void forceVyMvAcceRange(acce prm_acceVyMv01, acce prm_acceVyMv02);
    void setVzMvVelo(velo prm_veloVzMv);
    void addVzMvVelo(velo prm_veloVzMv);
    void forceVzMvVeloRange(velo prm_veloVzMv01, velo prm_veloVzMv02);
    void setVzMvAcce(acce prm_acceVzMv);
    void addVzMvAcce(acce prm_acceVzMv);
    void forceVzMvAcceRange(acce prm_acceVzMv01, acce prm_acceVzMv02);

    /**
     * 軸回転方角(Z軸とY軸)を目標にターゲットするシークエンスを実行 .
     * @param prm_angRz_Target 目標軸回転方角(Z軸)
     * @param prm_angRy_Target 目標軸回転方角(Y軸)
     * @param prm_angVelo ターゲッティング遂行中に加算される角度、つまり角速度（正負自動判定）
     * @param prm_angAcce 角加速度（正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_optimize_ang ターゲットアングルを最適化するかどうかを指定。
     *                         true: 引数の prm_angRz_Target, prm_angRy_Target までの距離と、<BR>
     *                               同じ方向を意味するもう一組の RzRy までの距離を割り出し、<BR>
     *                               到達フレーム数の少ない方の RzRy の組み合わせを自動採用する。<BR>
     *                               (注意：極地Y軸回転があるため、最短フレームは必ずしも最短距離にあらず)<BR>
     *                               所望の方向に最短フレームでターゲットするが、内部の _angMvRz, _angMvRy は<BR>
     *                               引数のターゲットアングル値と一致しないかもしれない。(姿勢が異なる可能性有り)<BR>
     *                         false:引数の prm_angRz_Target, prm_angRy_Target をそのままターゲートとする。<BR>
     */
    void execTagettingFaceAngSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                      angvelo prm_angVelo, angacce prm_angAcce,
                                      int prm_way, bool prm_optimize_ang = true);

    /**
     * 軸回転方角を目標にターゲットするシークエンスを実行 .
     * @param prm_tX 目標X座標
     * @param prm_tY 目標Y座標
     * @param prm_tZ 目標Z座標
     * @param prm_angVelo ターゲッティング遂行中に加算される角度、つまり角速度（正負自動判定）
     * @param prm_angAcce 角加速度（正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang ターゲットアングルを最適化するかどうかを指定。<BR>
     *                         true: 引数の prm_angRz_Target, prm_angRy_Target までの距離と、<BR>
     *                               同じ方向を意味するもう一組の RzRy までの距離を割り出し、<BR>
     *                               到達フレーム数の少ない方の RzRy の組み合わせを自動採用する。<BR>
     *                               所望の方向に最短フレームでターゲットするが、内部の _angMvRz, _angMvRy は<BR>
     *                               引数のターゲットアングル値と一致しないかもしれない。(姿勢が異なる可能性有り)<BR>
     *                               (注意：極地Y軸回転があるため、最短フレームは必ずしも最短距離にあらず)<BR>
     *                         false:引数の prm_angRz_Target, prm_angRy_Target をそのままターゲートとする。<BR>
     */
    void execTagettingFaceAngSequence(int prm_tX, int prm_tY, int prm_tZ,
                                      angvelo prm_angVelo, angacce prm_angAcce,
                                      int prm_way, bool prm_optimize_ang = true);


    /**
     * 軸回転方角(Z軸とY軸)を目標にターゲットの方向を向くようなシークエンスを実行
     * @param prm_pActor_Target 目標オブジェクト
     * @param prm_angVelo ターゲッティング遂行中に加算される角度、つまり角速度（正負自動判定）
     * @param prm_angAcce 角加速度（正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_optimize_ang ターゲットアングルを最適化するかどうかを指定。<BR>
     *                         true: 引数の prm_angRz_Target, prm_angRy_Target までの距離と、<BR>
     *                               同じ方向を意味するもう一組の RzRy までの距離を割り出し、<BR>
     *                               到達フレーム数の少ない方の RzRy の組み合わせを自動採用する。<BR>
     *                               所望の方向に最短フレームでターゲットするが、内部の _angMvRz, _angMvRy は<BR>
     *                               引数のターゲットアングル値と一致しないかもしれない。(姿勢が異なる可能性有り)<BR>
     *                               (注意：極地Y軸回転があるため、最短フレームは必ずしも最短距離にあらず)<BR>
     *                         false:引数の prm_angRz_Target, prm_angRy_Target をそのままターゲートとする。<BR>
     */
    void execTagettingFaceAngSequence(GgafDx9GeometricActor* prm_pActor_Target,
                                      angvelo prm_angVelo, angacce prm_angAcce,
                                      int prm_way, bool prm_optimize_ang = true) {
        execTagettingFaceAngSequence(
                prm_pActor_Target->_X,
                prm_pActor_Target->_Y,
                prm_pActor_Target->_Z,
                prm_angVelo,
                prm_angAcce,
                prm_way,
                prm_optimize_ang
        );
    }

    /**
     * 軸回転方角(Z軸)を目標にターゲットするシークエンスを実行 .
     * @param prm_angRz_Target 目標軸回転方角(Z軸)
     * @param prm_angVelo ターゲッティング遂行中に加算される角度、つまり角速度（正負自動判定）
     * @param prm_angAcce 角加速度（正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void execTagettingRzFaceAngSequence(angle prm_angRz_Target,
                                        angvelo prm_angVelo, angacce prm_angAcce,
                                        int prm_way);

    /**
     * 軸回転方角(Y軸)を目標にターゲットするシークエンスを実行 .
     * @param prm_angRy_Target 目標軸回転方角(Y軸)
     * @param prm_angVelo ターゲッティング遂行中に加算される角度、つまり角速度（正負自動判定）
     * @param prm_angAcce 角加速度（正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void execTagettingRyFaceAngSequence(angle prm_angRy_Target,
                                        angvelo prm_angVelo, angacce prm_angAcce,
                                        int prm_way);

    /**
     * 軸回転方角(X軸)を目標にターゲットするシークエンスを実行 .
     * @param prm_angRx_Target 目標軸回転方角(X軸)
     * @param prm_angVelo ターゲッティング遂行中に加算される角度、つまり角速度（正負自動判定）
     * @param prm_angAcce 角加速度（正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void execTagettingRxSpinAngleSequence(angle prm_angRx_Target,
                                          angvelo prm_angVelo, angacce prm_angAcce,
                                          int prm_way);

    /**
     * 移動方角を目標にターゲットするシークエンスを実行 .
     * @param prm_angRz_Target 目標移動方角(Z軸)
     * @param prm_angRy_Target 目標移動方角(Y軸)
     * @param prm_angVelo ターゲッティング遂行中に加算される角度、つまり角速度（正負自動判定）
     * @param prm_angAcce 角加速度（正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang ターゲットアングルを最適化するかどうかを指定。<BR>
     *                         true: 引数の prm_angRz_Target, prm_angRy_Target までの距離と、<BR>
     *                               同じ方向を意味するもう一組の RzRy までの距離を割り出し、<BR>
     *                               到達フレーム数の少ない方の RzRy の組み合わせを自動採用する。<BR>
     *                               所望の方向に最短フレームでターゲットするが、内部の _angMvRz, _angMvRy は<BR>
     *                               引数のターゲットアングル値と一致しないかもしれない。(姿勢が異なる可能性有り)<BR>
     *                               (注意：極地Y軸回転があるため、最短フレームは必ずしも最短距離にあらず)<BR>
     *                         false:引数の prm_angRz_Target, prm_angRy_Target をそのままターゲートとする。<BR>
     */
    void execTagettingMvAngSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                    angvelo prm_angVelo, angacce prm_angAcce,
                                    int prm_way, bool prm_optimize_ang = true);

    /**
     * 移動方角を目標にターゲットするシークエンスを実行 .
     * @param prm_tX 目標X座標
     * @param prm_tY 目標Y座標
     * @param prm_tZ 目標Z座標
     * @param prm_angVelo ターゲッティング遂行中に加算される角度、つまり角速度（正負自動判定）
     * @param prm_angAcce 角加速度（正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang ターゲットアングルを最適化するかどうかを指定。<BR>
     *                         true: 引数の prm_angRz_Target, prm_angRy_Target までの距離と、<BR>
     *                               同じ方向を意味するもう一組の RzRy までの距離を割り出し、<BR>
     *                               到達フレーム数の少ない方の RzRy の組み合わせを自動採用する。<BR>
     *                               所望の方向に最短フレームでターゲットするが、内部の _angMvRz, _angMvRy は<BR>
     *                               引数のターゲットアングル値と一致しないかもしれない。(姿勢が異なる可能性有り)<BR>
     *                               (注意：極地Y軸回転があるため、最短フレームは必ずしも最短距離にあらず)<BR>
     *                         false:引数の prm_angRz_Target, prm_angRy_Target をそのままターゲートとする。<BR>
     */
    void execTagettingMvAngSequence(int prm_tX, int prm_tY, int prm_tZ,
                                    angvelo prm_angVelo, angacce prm_angAcce,
                                    int prm_way, bool prm_optimize_ang = true);


    /**
     * 移動方角を目標にターゲットの座標にするシークエンスを実行
     * @param prm_pActor_Target 目標オブジェクト
     * @param prm_angVelo ターゲッティング遂行中に加算される角度、つまり角速度（正負自動判定）
     * @param prm_angAcce 角加速度（正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang ターゲットアングルを最適化するかどうかを指定。<BR>
     *                         true: 引数の prm_angRz_Target, prm_angRy_Target までの距離と、<BR>
     *                               同じ方向を意味するもう一組の RzRy までの距離を割り出し、<BR>
     *                               到達フレーム数の少ない方の RzRy の組み合わせを自動採用する。<BR>
     *                               所望の方向に最短フレームでターゲットするが、内部の _angMvRz, _angMvRy は<BR>
     *                               引数のターゲットアングル値と一致しないかもしれない。(姿勢が異なる可能性有り)<BR>
     *                               (注意：極地Y軸回転があるため、最短フレームは必ずしも最短距離にあらず)<BR>
     *                         false:引数の prm_angRz_Target, prm_angRy_Target をそのままターゲートとする。<BR>
     */
    void execTagettingMvAngSequence(GgafDx9GeometricActor* prm_pActor_Target,
                                    angvelo prm_angVelo, angacce prm_angAcce,
                                    int prm_way, bool prm_optimize_ang = true) {
        execTagettingMvAngSequence(
                prm_pActor_Target->_X,
                prm_pActor_Target->_Y,
                prm_pActor_Target->_Z,
                prm_angVelo,
                prm_angAcce,
                prm_way,
                prm_optimize_ang
        );
    }

    /**
     * 移動方角(Z軸)を目標にターゲットするシークエンスを実行 .
     * @param prm_angRz_Target 目標移動方角(Z軸)
     * @param prm_angVelo ターゲットへ移動方角を回転移動中に適用する目標移動方角回転移動角速度（正負自動判定）
     * @param prm_angAcce 角加速度（正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void execTagettingRzMvAngSequence(angle prm_angRz_Target,
                                      angvelo prm_angVelo, angacce prm_angAcce,
                                      int prm_way);

    /**
     * 移動方角(Y軸)を目標にターゲットするシークエンスを実行 .
     * @param prm_angRy_Target 目標移動方角(Y軸)
     * @param prm_angVelo ターゲットへ移動方角を回転移動中に適用する目標移動方角回転移動角速度（正負自動判定）
     * @param prm_angAcce 角加速度（正負自動判定）
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void execTagettingRyMvAngSequence(angle prm_angRy_Target,
                                      angvelo prm_angVelo, angacce prm_angAcce,
                                      int prm_way);


    void stopTagettingMvAngSequence() {
        _mv_ang_rz_target_flg = false;
        _mv_ang_ry_target_flg = false;
    }


    /**
     * 目標軸回転方角にターゲットするシークエンスが実行中か .
     * @return true:実行中/false:実行中でない
     */
    bool isTagettingFaceAng() {
        if (_face_ang_targeting_flg[AXIS_X] ||
            _face_ang_targeting_flg[AXIS_Y] ||
            _face_ang_targeting_flg[AXIS_Z]) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * 目標移動方角にターゲットするシークエンスが実行中か .
     * @return true:実行中/false:実行中でない
     */
    bool isTagettingMvAng() {
        if (_mv_ang_rz_target_flg || _mv_ang_rz_target_flg) {
            return true;
        } else {
            return false;
        }
    }


    /**
     * 移動方角に伴って軸回転方角を更新 .
     * true を設定すると、自動的に移動方角の方に向きが変わる。<BR>
     * false を設定すると、移動方角と向きは独立。<BR>
     * @param prm_b true:移動方角に伴って軸回転方角を更新/false:移動方角と軸回転方角は独立
     */
    void relateRzRyFaceAngToMvAng(bool prm_b) {
        _relate_RyFaceAng_to_RyMvAng_flg = prm_b;
        _relate_RzFaceAng_to_RzMvAng_flg = prm_b;
    }

    /**
     * なめらかな移動速度で移動するシークエンスを実行 .
     * 引数の移動距離を４分割し、次のような速度制御を自動的に行う。<BR>
     * 距離 0    ～距離 1/4 まで ・・・ 現在の速度からトップスピードまで加速<BR>
     * 距離 1/4 ～ 距離 3/4 まで ・・・ トップスピードで等速<BR>
     * 距離 3/4 ～ 距離 4/4 まで ・・・ トップスピードから最終スピードへ減速<BR>
     * @param prm_top_velo トップスピード
     * @param prm_end_velo 最終スピード
     * @param prm_distance_of_target 目標移動距離
     * @param prm_endacc_flg true:目標移動距離に達した際に加速度を０にする/false:加速度はそのままにしておく
     */
    void execSmoothMvVeloSequence(velo prm_top_velo, velo prm_end_velo, int prm_distance_of_target,
                                  bool prm_endacc_flg = true);

    bool isMoveingSmooth();



    /**
     * 毎フレームのActorの振る舞い。<BR>
     * 本クラスを機能を利用する場合は、このbehave() を毎フレーム呼び出し実行してください。<BR>
     */
    virtual void behave();

    virtual ~GgafDx9GeometricMover();
};

}
#endif /*GGAFDX9GEOMETRICMOVER_H_*/

