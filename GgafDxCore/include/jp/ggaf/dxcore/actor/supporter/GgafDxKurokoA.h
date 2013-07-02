#ifndef GGAFDXMVNAVIGATOR_H_
#define GGAFDXMVNAVIGATOR_H_
#include "jp/ggaf/core/GgafObject.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

namespace GgafDxCore {

/**
 * 黒衣A .
 * 黒衣Aは舞台には見えないですが、演者(アクター)を持ち上げ、「方向移動」「向きの回転」を行わせる世話人です。<BR>
 * 演者は自らの意思で動作せずとも、黒衣Aのおかげで舞台を飛び回まわることもできます。<BR>
 * 基本的な移動動作は黒衣Aでほとんどカバーできます。<BR>
 * 演者(アクター)自身も協力して移動・回転を行うと、黒衣Aが対応できないより複雑な移動動作も可能でしょう。<BR>
 * 演者一人につき、黒衣Aが標準で一人付属しています。<BR>
 * <BR>
 * それはさて置き、つまりは座標計算支援（共通化）クラスです。<BR>
 * GgafDxGeometricActor のメンバの<BR>
 *  _X,  _Y,  _Z  ・・・ アクターの座標<BR>
 * _RX, _RY, _RZ  ・・・ アクターの軸回転角度<BR>
 * を変化させます。方向ベクトル、速度、距離、時間、によって管理操作するために作成したクラス。<BR>
 * 共通の基本的な移動、回転は黒衣Aに任せて、<BR>
 * アクター固有の特殊な移動回転動作を processBehave() に直接記述。という設計思想。<BR>
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class GgafDxKurokoA : public GgafCore::GgafObject {

public:
    /** [r]対象アクター */
    GgafDxGeometricActor* _pActor;

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用Actor
     */
    GgafDxKurokoA(GgafDxGeometricActor* prm_pActor);



public: //_RX , _RY, _RZ 操作関連 //////////////////////////////////////////////
    /** [r/w]キャラの向き(各軸回転方角の方角(0～360,000)) */
    angle _angFace[3];
    /** [r/w]軸回転方角の角速度（軸回転方角に毎フレーム加算する方角） */
    angvelo _angveloFace[3];
    /** [r/w]軸回転方角の角速度上限(最高値は360,000) */
    angvelo _angveloTopFace[3];
    /** [r/w]軸回転方角の角速度下限(最高値は-360,000) */
    angvelo _angveloBottomFace[3];
    /** [r/w]軸回転方角の角加速度（角速度に毎フレーム加算する値） */
    angacce _angacceFace[3];
    /** [r/w]軸回転方角の角躍度（角加速度に毎フレーム加算する値） */
    angjerk _angjerkFace[3];
    /** [r/w]目標の軸回転方角自動向き有効フラグ */
    bool _face_ang_targeting_flg[3];
    /** [r/w]目標の軸回転方角自動停止機能有効フラグ */
    bool _face_ang_targeting_stop_flg[3];
    /** [r/w]目標とするキャラの軸回転方角の方角(0～360,000) */
    angle _angTargetFace[3];
    /** [r/w]目標の軸回転方角自動停止機能が有効になる回転方向 */
    int _face_ang_target_allow_way[3]; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** [r/w]目標の軸回転方角自動停止機能が有効になる角速度（回転正負共通） */
    angvelo _face_ang_target_allow_velo[3]; //この角速度より小さい値の場合機能有効とするz

public:
    /**
     * Actorの正面方角（軸単位）を設定。<BR>
     * @param   prm_axis    回転軸(AXIS_X / AXIS_Y / AXIS_Z)
     * @param   prm_angFace 方角のアングル値(-360,000～360,000)
     */
    void setFaceAng(axis prm_axis, angle prm_angFace);
    /**
     * Actorの正面方角を設定。<BR>
     * @param prm_axis_X_angFace X軸方角のアングル値(-360,000～360,000)
     * @param prm_axis_Y_angFace Y軸方角のアングル値(-360,000～360,000)
     * @param prm_axis_Z_angFace Z軸方角のアングル値(-360,000～360,000)
     */
    void setFaceAng(angle prm_axis_X_angFace,
                    angle prm_axis_Y_angFace,
                    angle prm_axis_Z_angFace) {
        setFaceAng(AXIS_X, prm_axis_X_angFace);
        setFaceAng(AXIS_Y, prm_axis_Y_angFace);
        setFaceAng(AXIS_Z, prm_axis_Z_angFace);
    }

    void setFaceAngByMvAng() {
        setFaceAng(AXIS_Z, _angRzMv);
        setFaceAng(AXIS_Y, _angRyMv);
    }
    /**
     * Actorの自身の座標から対象座標点に向いた方向に、Z軸回転方角とY軸回転方角を設定<BR>
     * @param prm_tX 対象点X座標
     * @param prm_tY 対象点Y座標
     * @param prm_tZ 対象点Z座標
     */
    void setFaceAngTwd(coord prm_tX, coord prm_tY, coord prm_tZ);

    /**
     * 現在の Actor の軸回転方角へ加算（負で減算）。<BR>
     *
     * 引数に渡すのは、軸回転方角の増分です。Actorの軸回転方角（_angFace）を相対指定できるメソッドです。<BR>
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
     *  -360000 , 360000<BR>
     *
     *  です。
     *  <BR>
     *
     * @param   prm_axis    回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param   prm_angDistance 回転軸方角値の増分アングル値(範囲：_iBottom_RotVeloAngle ～ _angveloTopRot)
     */
    void addFaceAng(axis prm_axis, angle prm_angDistance);


    /**
     * Actorの目標の軸回転方角自動停止機能を有効(目標の軸回転方角設定)<BR>
     * 引数に設定された軸回転方角になると、軸回転方角角速度及び軸回転方角角加速度を 0 にし、回転を停止させます。<BR>
     * 軸回転方角角速度等の設定を併せて実行して、まずは軸回転も行なってください。<BR>
     * 軸回転方角角速度が 0 の場合、何も起こりません。本メソッドを実行したからと言って勝手に向きが変わるとという意味ではありません。 <BR>
     * 内部的には、addFaceAng(prm_axis, int) が毎フレーム行われる仕組みです。<BR>
     * 目標の回転方角に到達したならば、この目標の軸回転方角自動停止機能は解除(内部のフラグをアンセット)されます。<BR>
     * @param   prm_axis    回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param   prm_angTargetRot    到達目標の回転方角(0～360,000)
     * @param   prm_way_allow  自動停止を許可する進入方向(TURN_CLOCKWISE/TURN_COUNTERCLOCKWISE/TURN_BOTH)
     * @param   prm_angveloAllow 自動停止機能が有効になる回転角速度
     */
    void setStopTargetFaceAng(axis prm_axis,
                              angle prm_angTargetRot,
                              int prm_way_allow = TURN_BOTH,
                              angvelo prm_angveloAllow = D180ANG);

    /**
     * Actorの目標回転方向自動停止機能を有効(現在XY座標からの対象XY座標で設定)<BR>
     * @param   prm_axis    回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param   prm_tX  対象X座標
     * @param   prm_tY  対象Y座標
     * @param   prm_way_allow  自動停止機能が有効になる回転方向
     * @param   prm_angveloAllowRyMv 自動停止機能が有効になる回転角速度
     */
    void setStopTargetFaceAngTwd(axis prm_axis,
                                 coord prm_tX,
                                 coord prm_tY,
                                 int prm_way_allow = TURN_BOTH,
                                 angvelo prm_angveloAllowRyMv = D180ANG);
    /**
     * 軸回転方角の角速度（軸回転方角に毎フレーム加算する値）を設定 .
     * @param prm_axis 回転軸（AXIS_X / AXIS_Y / AXIS_Z)
     * @param prm_angveloRot 角速度
     */
    void setFaceAngVelo(axis prm_axis, angvelo prm_angveloRot);

    /**
     * 軸回転方角の角速度（軸回転方角に毎フレーム加算する値）を設定 .
     * @param prm_axis_X_angveloRot X軸回転の角速度
     * @param prm_axis_Y_angveloRot Y軸回転の角速度
     * @param prm_axis_Z_angveloRot Z軸回転の角速度
     */
    void setFaceAngVelo(angvelo prm_axis_X_angveloRot,
                        angvelo prm_axis_Y_angveloRot,
                        angvelo prm_axis_Z_angveloRot);

    void forceFaceAngVeloRange(axis prm_axis,
                               angvelo prm_angveloRot01,
                               angvelo prm_angveloRot02);

    void setFaceAngAcce(axis prm_axis, angacce prm_angacceRot);

    angle getFaceAngDistance(axis prm_axis, coord prm_tX, coord prm_tY, int prm_way);

    angle getFaceAngDistance(axis prm_axis, angle prm_angTargetRot, int prm_way);

    ////////////////////////////////////////////////////MOVER

public: //_X, _Y, _Z 操作関連 //////////////////////////////////////////////
    /** [r]キャラの移動方角単位ベクトル */
    float _vX, _vY, _vZ;
    /** [r/w]移動方角のZ軸回転角 */
    angle _angRzMv;
    /** [r/w]移動方角のY軸回転角 */
    angle _angRyMv;
    /** [r/w]移動速度 */
    velo _veloMv;
    /** [r/w]移動速度上限 */
    velo _veloTopMv;
    /** [r/w]移動速度下限 */
    velo _veloBottomMv;
    /** [r/w]移動加速度 */
    acce _accMv;

    /** [r/w]移動方角（Z軸回転）の角速度（移動方角（Z軸回転）に毎フレーム加算する方角） */
    angvelo _angveloRzMv;
    /** [r/w]移動方角（Z軸回転）の角速度上限(最高値は360,000) */
    angvelo _angveloRzTopMv;
    /** [r/w]移動方角（Z軸回転）の角速度下限(最高値は-360,000) */
    angvelo _angveloRzBottomMv;
    /** [r/w]移動方角（Z軸回転）の角加速度（角速度に毎フレーム加算する値） */
    angacce _angacceRzMv;
    /** [r/w]移動方角（Z軸回転）の角躍度（角加速度に毎フレーム加算する値） */
    angjerk _angjerkRzMv;
    /** [r/w]目標の移動方角（Z軸回転）向き有効フラグ */
    bool _mv_ang_rz_target_flg;
    /** [r/w]目標の移動方角（Z軸回転）自動停止機能有効フラグ */
    bool _mv_ang_rz_target_stop_flg;
    /** 目標とするキャラの移動方角（Z軸回転）の方角(0～360,000) */
    angle _angTargetRzMv;
    /** [r/w]目標の移動方角（Z軸回転）自動停止機能が有効になる進入回転方向 */
    int _mv_ang_rz_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** [r/w]目標の移動方角（Z軸回転）自動停止機能が有効になる移動方角角速度 */
    angvelo _mv_ang_rz_target_allow_velo;
    /** [r/w]自動前方向き機能有効フラグ */
    bool _relate_RzFaceAng_with_RzMvAng_flg;
    //true  : 移動方角（Z軸回転）を変更すると、それに伴い同じ方角が軸回転方角(Z軸)にも設定される
    //false : 移動方角（Z軸回転）とZ軸軸回転方角は独立

    /** [r/w]移動方角（Y軸回転）の角速度（移動方角（Y軸回転）に毎フレーム加算する方角） */
    angvelo _angveloRyMv;
    /** [r/w]移動方角（Y軸回転）の角速度上限(最高値は360,000) */
    angvelo _angveloRyTopMv;
    /** [r/w]移動方角（Y軸回転）の角速度下限(最高値は-360,000) */
    angvelo _angveloRyBottomMv;
    /** [r/w]移動方角（Y軸回転）の角加速度（角速度に毎フレーム加算する値） */
    angacce _angacceRyMv;
    /** [r/w]移動方角（Y軸回転）の角躍度（角加速度に毎フレーム加算する値） */
    angjerk _angjerkRyMv;
    /** [r/w]目標の移動方角（Y軸回転）自動向き有効フラグ */
    bool _mv_ang_ry_target_flg;
    /** [r/w]目標の移動方角（Y軸回転）自動停止機能有効フラグ */
    bool _mv_ang_ry_target_stop_flg;
    /** [r/w]目標とするキャラの移動方角（Y軸回転）の方角(0～360,000) */
    angle _angTargetRyMv;
    /** [r/w]目標の移動方角（Y軸回転）自動停止機能が有効になる進入回転方向 */
    int _mv_ang_ry_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** [r/w]目標の移動方角（Y軸回転）自動停止機能が有効になる移動方角角速度 */
    angvelo _mv_ang_ry_target_allow_velo;
    /** [r/w]自動前方向き機能有効フラグ */
    bool _relate_RyFaceAng_with_RyMvAng_flg;
    //true  : 移動方角（Y軸回転）を変更すると、それに伴い同じ方角が軸回転方角(Y軸)にも設定される
    //false : 移動方角（Y軸回転）とY軸軸回転方角は独立


    /** [r]なめらかな移動シークエンスを実行中はtrue */
    bool _slide_mv_flg;
    /** [r]なめらかな移動シークエンスを実行完了時の加速度設定（true：加速度0に設定／false:加速度をそのままにしておく） */
    bool _slide_mv_endacc_flg;
    /** [r]なめらかな移動シークエンスで設定されたトップスピード（等速移動時速度） */
    velo _slide_mv_top_velo;
    /** [r]なめらかな移動シークエンスで設定された終了時の速度 */
    velo _slide_mv_end_velo;
    /** [r]なめらかな移動シークエンスで設定された目標移動距離 */
    coord _slide_mv_target_distance;
    /** [r]なめらかな移動シークエンスに開始から現在までの移動距離 */
    coord _slide_mv_mv_distance;
    /** [r]なめらかな移動シークエンスで設定された目標時間 */
    int  _slide_mv_target_frames;
    /** [r]なめらかな移動シークエンスに開始から現在までの経過時間 */
    int  _slide_mv_frame_of_spent;
    /** [r]なめらかな移動シークエンスで設定された加速～等速へ切り替わる位置 */
    int  _slide_mv_p1;
    /** [r]なめらかな移動シークエンスで設定された等速～減速へ切り替わる位置 */
    int  _slide_mv_p2;

    /** [r]なめらかな移動シークエンスの進捗状況 */
    int  _slide_mv_progress;

    bool _taget_face_ang_alltime_flg;
    GgafDxGeometricActor* _taget_face_ang_alltime_pActor;
    coord _taget_face_ang_alltime_tX;
    coord _taget_face_ang_alltime_tY;
    coord _taget_face_ang_alltime_tZ;
    angvelo  _taget_face_ang_alltime_angVelo;
    angacce _taget_face_ang_alltime_angAcce;
    int _taget_face_ang_alltime_way;
    bool _taget_face_ang_alltime_optimize_ang;

public:
    /**
     * 移動速度を設定 .
     * @param   prm_veloMv  移動速度
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
     * 移動速度の上限下限を設定し、移動速度の範囲を制限する .
     * 上限下限値は、-prm_veloMv ～ prm_veloMv の範囲になる。
     * @param prm_veloMv 移動速度
     */
    void forceMvVeloRange(velo prm_veloMv);

    /**
     * 移動加速度を設定 .
     * @param prm_acceMove 移動加速度
     */
    void setMvAcce(acce prm_acceMove);

    /**
     * 移動加速度を、「停止時移動距離」により設定する .
     * <pre><code>
     *
     *    速度(v)
     *     ^       a:減加速度
     *     |       D:移動距離（停止に費やす距離）
     *     |      Vo:現時点の速度
     *   Vo|      Te:停止するフレーム
     *     |＼
     *     |  ＼
     *     |    ＼ 斜辺の傾きa
     *     |   D  ＼
     *     |        ＼
     *   --+----------＼-----> 時間(t)
     *   0 |          Te
     *
     *    D = (1/2) Vo Te  ・・・①
     *    a = -Vo / Te     ・・・②
     *    ①より
     *    Te = 2D / Vo
     *    これを②へ代入
     *    a = -Vo / (2D / Vo)
     *    ∴ a = -(Vo^2) / 2D
     * </code></pre>
     * 上図のような状態を想定し、引数の距離(D)から、加速度(a)を計算し設定している。<BR>
     * 停止までのフレーム(Te) は 距離(D) により変化するため指定不可。<BR>
     * @param prm_target_distance 停止時移動距離(D)
     */
    void setMvAcceToStop(coord prm_target_distance);

    /**
     * 移動加速度を、「目標到達速度」「移動距離(達するまでに費やす距離)」により設定 .
     * <pre><code>
     *
     *    速度(v)
     *     ^        a:加速度
     *     |        D:移動距離（目標到達速度に達するまでに費やす距離）
     *     |       Vo:現時点の速度
     *     |       Vt:目標到達速度
     *     |       Te:目標到達速度に達した時の時間（フレーム数）
     *   Vt|........
     *     |      ／|
     *     |    ／  |
     *     |  ／    |   斜辺の傾きa
     *     |／      |
     *   Vo|    D   |
     *     |        |
     *   --+--------+---> 時間(t)
     *   0 |        Te
     *
     *    D = (1/2) (Vo + Vt) Te   ・・・①
     *    a = (Vt - Vo) / Te         ・・・②
     *    ①より Te = (Vt - Vo) / a
     *    これを②へ代入
     *    D = (Vt^2 - Vo^2) / 2a
     *    ∴ a = (Vt^2 - Vo^2) / 2D
     * </code></pre>
     * 上図のような状態を想定し、目標到達速度(Vt)と、移動距離(D)から、加速度(a)を計算し設定している。<BR>
     * 目標到達まで必要なフレーム(Te) はパラメータにより変化するため指定不可。<BR>
     * 捕捉：setMvAcceByD(0, D) は setMvAcceToStop(D) と同じである
     * @param prm_target_distance  目標到達速度に達するまでに費やす距離(D)
     * @param prm_target_velo 目標到達速度(Vt)
     */
    void setMvAcceByD(coord prm_target_distance, velo prm_target_velo);

    /**
     * 移動加速度を、「目標到達速度」「費やす時間」により設定 .
     * <pre><code>
     *
     *    速度(v)
     *     ^        a:加速度
     *     |        D:移動距離
     *     |       Vo:現時点の速度
     *     |       Vt:目標到達速度
     *     |       Te:目標到達速度に達した時の時間（フレーム数）
     *   Vt|........
     *     |      ／|
     *     |    ／  |
     *     |  ／    |   斜辺の傾きa
     *     |／      |
     *   Vo|    D   |
     *     |        |
     *   --+--------+---> 時間(tフレーム)
     *   0 |        Te
     *
     *    a = (Vt-Vo) / Te
     *    Dは無視
     * </code></pre>
     * 上図のような状態を想定し、目標到達速度(Vt)と、その到達時間(Te) から、加速度(a)を計算し設定している。<BR>
     * 移動距離(D)は、パラメータにより変化するため指定不可。<BR>
     * @param prm_target_frames 費やす時間(Te)
     * @param prm_target_velo  目標到達速度(Vt)
     */
    void setMvAcceByT(int prm_target_frames, velo prm_target_velo);

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
     * 引数に渡すのは、移動方角（Z軸回転）の増分です。Actorの移動方角（Z軸回転）（_angRzMv）を相対指定でるメソッドです。<BR>
     * 加算後の移動方角（Z軸回転）が範囲外（0～360,000 以外）の値になっても、最終的には setRzMvAng(int) を呼び出しますので<BR>
     * 正しい 0～360,000 の範囲内の値に再設定されます。<BR>
     * 引数である加算（減算）する移動方角（Z軸回転）は、Z軸移動加速度の上限と下限の間の範囲に限ります。<BR>
     * つまり、引数の有効な範囲は以下の通りとなります。<BR>
     *
     *   _angveloRzBottomMv ≦ 引数の動方角増分 ≦ _angveloRzTopMv  です。<BR>
     *
     * もし範囲外の引数の移動方角（Z軸回転）増分を指定した場合は、直近の範囲内の値に強制的に抑えられ、その値が加算されます。<BR>
     * また、自動前方向き機能が有効(_relate_RzFaceAng_with_RzMvAng_flg)の場合、<BR>
     * 加算後の移動方角（Z軸回転）の値が、Z軸の目標の軸回転方角として設定されます。（自動で前方を向くに設定されます。但し前方＝アングル0のキャラの場合ですけど；）<BR>
     *
     * 【補足：】<BR>
     * 本メソッド毎フレーム実行することでXY平面の円運動が可能になります。<BR>
     * 引数の移動方角（Z軸回転）が、数直線上の 0 に、より近い値を加算し続けた場合は、緩やかなカーブ描きながら向転換することを意味します。<BR>
     * 逆に、引数の移動方角（Z軸回転）が、0 から、より離れた値を加算し続けた場合は、より鋭角的なカーブ描きながら向転換することを意味します。<BR>
     * デフォルトのZ軸移動加速度の上限と下限（_angveloRzBottomMv、_angveloRzTopMv) は<BR>
     *
     *  -360000 , 360000<BR>
     *
     * となっています。これは瞬時に（1フレームで）どんな移動方角（Z軸回転）にも向きを変えれることを意味します。<BR>
     *
     * @param   prm_angDistance 移動方角（Z軸回転）増分(範囲：_angveloRzBottomMv ～ _angveloRzTopMv)
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
     * @param   prm_angRzMv 到達目標の移動方角（Z軸回転）(-360,000～360,000)
     * @param   prm_way_allow  自動停止機能が有効になる進入回転方向
     * @param   prm_angveloAllowRyMv 停止機能が有効になる移動方角角速度
     */
    void setStopTargetRzMvAng(angle prm_angRzMv,
                              int prm_way_allow = TURN_BOTH,
                              angvelo prm_angveloAllowRyMv = D180ANG);

    void setRzMvAngVelo(angvelo prm_angveloRzMv);

    void forceRzMvAngVeloRange(angvelo prm_angveloRzMv01, angvelo prm_angveloRzMv02);

    void setRzMvAngAcce(angacce prm_angacceRzMv);

    angle getRzMvAngDistanceTwd(coord prm_tX, coord prm_tY, int prm_way);

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
     * 自動前方向き機能が有効(_relate_RyFaceAng_with_RyMvAng_flg)の場合、<BR>
     * Actorの向きも移動方角（Y軸回転）と同じ方向を向くように setStopTargetFaceAng(int) も実行されます。<BR>
     * @param prm_ang 移動方角（Y軸回転）(0～360,000)
     */
    void setRyMvAng(angle prm_ang);

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
     * また、自動前方向き機能が有効(_relate_RyFaceAng_with_RyMvAng_flg)の場合、<BR>
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
     * @param   prm_angDistance 移動方角（Y軸回転）増分(範囲：_angveloRyBottomMv ～ _angveloRyTopMv)
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
     * @param   prm_angRyMv 到達目標の移動方角（Y軸回転）(-360,000～360,000)
     * @param   prm_mv_ang_ry_target_allow_way  自動停止機能が有効になる進入回転方向
     * @param   prm_angveloAllowRyMv 停止機能が有効になる移動方角角速度
     */
    void setStopTargetRyMvAng(angle prm_angRyMv,
                              int prm_mv_ang_ry_target_allow_way = TURN_BOTH,
                              angvelo prm_angveloAllowRyMv = D180ANG);

    void setRyMvAngVelo(angvelo prm_angveloRyMv);

    void forceRyMvAngVeloRange(angvelo prm_angveloRyMv01, angvelo prm_angveloRyMv02);

    void setRyMvAngAcce(angacce prm_angacceRyMv);

    angle getRyMvAngDistanceTwd(coord prm_tX, coord prm_tY, int prm_way);

    angle getRyMvAngDistance(angle prm_angTargetRyMv, int prm_way);


    void forceRzRyMvAngVeloRange(angvelo prm_angveloRzRyMv01, angvelo prm_angveloRzRyMv02);

    void setRzRyMvAngVelo(angvelo prm_angveloRzRyMv);

    void setRzRyMvAngAcce(angacce prm_angacceRzRyMv);

    void setRzRyMvAngVelo(angvelo prm_angveloRzMv, angvelo prm_angveloRyMv);

    void setRzRyMvAngAcce(angacce prm_angacceRzMv, angacce prm_angacceRyMv);



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
     * 目標座標点を座標指定で移動方角(RzRy)を設定。.
     * 方向ベクトル正規化も内部で行なう。
     * @param prm_tX 目標X座標
     * @param prm_tY 目標Y座標
     * @param prm_tZ 目標Z座標
     */
    void setMvAngTwd(coord prm_tX, coord prm_tY, coord prm_tZ);

    /**
     * 目標座標点を座標指定で移動方角(RzRy)を設定。.
     * 但し奥行き(Z座標は)無視して計算を行う。
     * 方向ベクトル正規化も内部で行なう。
     * @param prm_tX 目標X座標
     * @param prm_tY 目標Y座標
     */
    inline void setMvAngTwd(coord prm_tX, coord prm_tY) {
        setMvAngTwd(prm_tX, prm_tY, _pActor->_Z);
    }

    /**
     * 目標座標点指を対象アクターの座標指定で移動方角(RzRy)を設定。.
     * 方向ベクトル正規化も内部で行なう。
     * @param prm_pActor_Target 目標対象アクター
     */
    inline void setMvAngTwd(GgafDxGeometricActor* prm_pActor_Target) {
        setMvAngTwd(
            prm_pActor_Target->_X,
            prm_pActor_Target->_Y,
            prm_pActor_Target->_Z
        );
    }

    inline void setMvAngTwd(GgafDxGeoElem* prm_pGeoElem) {
        setMvAngTwd(
            prm_pGeoElem->_X,
            prm_pGeoElem->_Y,
            prm_pGeoElem->_Z
        );
    }

    void reverseMvAng();


    void setStopTargetMvAngTwd(coord prm_tX, coord prm_tY, coord prm_tZ);

    void setStopTargetMvAngTwd(GgafDxGeometricActor* prm_pActor_Target);


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
    void turnRzRyFaceAngTo(angle prm_angRz_Target, angle prm_angRy_Target,
                           angvelo prm_angVelo, angacce prm_angAcce,
                           int prm_way, bool prm_optimize_ang);

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
    void turnFaceAngTwd(coord prm_tX, coord prm_tY, coord prm_tZ,
                        angvelo prm_angVelo, angacce prm_angAcce,
                        int prm_way, bool prm_optimize_ang);


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
    inline void turnFaceAngTwd(GgafDxGeometricActor* prm_pActor_Target,
                        angvelo prm_angVelo, angacce prm_angAcce,
                        int prm_way, bool prm_optimize_ang) {
        turnFaceAngTwd(
                prm_pActor_Target->_X,
                prm_pActor_Target->_Y,
                prm_pActor_Target->_Z,
                prm_angVelo,
                prm_angAcce,
                prm_way,
                prm_optimize_ang
        );
    }
    inline void turnFaceAngTwd(GgafDxGeoElem* prm_pGeoElem,
                        angvelo prm_angVelo, angacce prm_angAcce,
                        int prm_way, bool prm_optimize_ang) {
        turnFaceAngTwd(
                prm_pGeoElem->_X,
                prm_pGeoElem->_Y,
                prm_pGeoElem->_Z,
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
    void turnRzFaceAngTo(angle prm_angRz_Target,
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
    void turnRyFaceAngTo(angle prm_angRy_Target,
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
    void turnRxSpinAngTo(angle prm_angRx_Target,
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
    void turnRzRyMvAngTo(angle prm_angRz_Target, angle prm_angRy_Target,
                         angvelo prm_angVelo, angacce prm_angAcce,
                         int prm_way, bool prm_optimize_ang);


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
    void turnMvAngTwd(coord prm_tX, coord prm_tY, coord prm_tZ,
                      angvelo prm_angVelo, angacce prm_angAcce,
                      int prm_way, bool prm_optimize_ang);

    void keepOnTurningFaceAngTwd(coord prm_tX, coord prm_tY, coord prm_tZ,
                            angvelo prm_angVelo, angacce prm_angAcce,
                            int prm_way, bool prm_optimize_ang) {
        turnFaceAngTwd(prm_tX, prm_tY, prm_tZ,
                       prm_angVelo,  prm_angAcce,
                       prm_way, prm_optimize_ang );
        _taget_face_ang_alltime_flg = true;
        _taget_face_ang_alltime_pActor = nullptr;
        _taget_face_ang_alltime_tX = prm_tX;
        _taget_face_ang_alltime_tY = prm_tY;
        _taget_face_ang_alltime_tZ = prm_tZ;
        _taget_face_ang_alltime_angVelo = prm_angVelo;
        _taget_face_ang_alltime_angAcce = prm_angAcce;
        _taget_face_ang_alltime_way = prm_way;
        _taget_face_ang_alltime_optimize_ang = prm_optimize_ang;
    }


    void keepOnTurningFaceAngTwd(GgafDxGeometricActor* prm_pActor_Target,
                            angvelo prm_angVelo, angacce prm_angAcce,
                            int prm_way, bool prm_optimize_ang) {
        keepOnTurningFaceAngTwd(
                prm_pActor_Target->_X,
                prm_pActor_Target->_Y,
                prm_pActor_Target->_Z,
                prm_angVelo, prm_angAcce,
                prm_way, prm_optimize_ang);
        _taget_face_ang_alltime_pActor = prm_pActor_Target;
    }

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
    inline void turnMvAngTwd(GgafDxGeometricActor* prm_pActor_Target,
                      angvelo prm_angVelo, angacce prm_angAcce,
                      int prm_way, bool prm_optimize_ang) {
        turnMvAngTwd(
                prm_pActor_Target->_X,
                prm_pActor_Target->_Y,
                prm_pActor_Target->_Z,
                prm_angVelo,
                prm_angAcce,
                prm_way,
                prm_optimize_ang
        );
    }

    inline void turnMvAngTwd(GgafDxGeoElem* prm_pGeoElem,
                      angvelo prm_angVelo, angacce prm_angAcce,
                      int prm_way, bool prm_optimize_ang) {
        turnMvAngTwd(
                prm_pGeoElem->_X,
                prm_pGeoElem->_Y,
                prm_pGeoElem->_Z,
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
    void turnRzMvAngTo(angle prm_angRz_Target,
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
    void turnRyMvAngTo(angle prm_angRy_Target,
                       angvelo prm_angVelo, angacce prm_angAcce,
                       int prm_way);


    void stopTurnMvAngSequence() {
        _mv_ang_rz_target_flg = false;
        _mv_ang_rz_target_stop_flg = false;
        _mv_ang_ry_target_flg = false;
        _mv_ang_rz_target_stop_flg = false;
    }

    void stopTurnFaceAngSequence() {
        _face_ang_targeting_flg[AXIS_X] = false;
        _face_ang_targeting_flg[AXIS_Y] = false;
        _face_ang_targeting_flg[AXIS_Z] = false;
        _taget_face_ang_alltime_pActor = nullptr;
        _taget_face_ang_alltime_flg = false;
    }

    /**
     * 目標軸回転方角にターゲットするシークエンスが実行中か .
     * @return true:実行中/false:実行中でない
     */
    bool isTurningFaceAng() {
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
    bool isTurningMvAng() {
        if (_mv_ang_rz_target_flg || _mv_ang_ry_target_flg) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * 移動方角に伴って軸回転方角を更新 .
     * true を設定すると、自動的に移動方角の方に向きが変わる。<BR>
     * false を設定すると、移動方角と向きは独立、デフォルトはこちら。<BR>
     * @param prm_b true:移動方角に伴って軸回転方角を更新/false:移動方角と軸回転方角は独立
     */
    void relateMvFaceAng(bool prm_b) {
        _relate_RyFaceAng_with_RyMvAng_flg = prm_b;
        _relate_RzFaceAng_with_RzMvAng_flg = prm_b;
    }


    /**
     * なめらかな移動速度を変化させるシークエンスを実行(時間・距離指定、速度変動) .
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
     *     |                         Vo:現時点の速度
     *     |                         Ve:最終速度
     *     |                          D:目標移動距離
     *   Vt|....___________          Te:目標時間（フレーム数）
     *     |   /:         :＼        p1:トップスピードに達する時刻となるような、Teに対する割合(0.0～1.0)
     *   Ve|../.:.........:..＼      p2:減速を開始時刻となるような、Teに対する割合(0.0～1.0)
     *     | /  :         :    |     Vt:距離・時間から導きだされるトップスピード
     *     |/   :         :    |
     *   Vo|    :    D    :    |
     *     |    :         :    |
     *   --+----+---------+----+-----> 時間(t:フレーム)
     *   0 |  p1*Te     p2*Te  Te
     *
     * </pre>
     * 最終スピード(Ve)、目標移動距離(D)、到達目標時間(Te)、及び p1, p2 を指定する。<BR>
     * トップスピード(Vt)は内部で自動計算し決定される。<BR>
     * @param prm_end_velo 最終スピード(Ve)
     * @param prm_target_distance 目標直線移動距離(D)
     * @param prm_target_frames 費やす時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_p1 トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_p2 減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_endacc_flg true:目標移動距離に達した際に加速度を０に強制設定/false:加速度はそのままにしておく
     */
    void slideMvByDT(velo prm_end_velo, coord prm_target_distance,
                     int prm_target_frames, float prm_p1, float prm_p2,
                     bool prm_endacc_flg = true);


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
     *     |                         Vo:現時点の速度
     *     |                         Vt:トップスピード
     *     |                         Ve:最終速度
     *     |         D=d1+d2+d3       D:目標移動距離(D=d1+d2+d3)
     *   Vt|....___________          p1:トップスピードに達する距離となるような、距離(D)に対する割合
     *     |   /|         |＼            つまり    d1 = D*p1 となるような p1 (0.0～1.0)
     *   Ve|../.|.........|..＼      p2:減速を開始距離となるような、距離(D)に対する割合
     *     | /  |         |    |         つまり d1+d2 = D*p2 となるような p2 (0.0～1.0)
     *     |/   |         |    |     Te:費やされる必要時間（フレーム数）
     *   Vo| d1 |    d2   | d3 |
     *     |    |         |    |
     *   --+----+---------+----+-----> 時間(t:フレーム)
     *   0 |                  Te
     *
     * </pre>
     * トップスピード(Vt)、最終スピード(Ve)、目標移動距離(D)、及び p1, p2 を指定する。<BR>
     * 費やされる時間(Te)は内部で自動計し決定される。<BR>
     * <BR>
     * @param prm_top_velo トップスピード(Vt)
     * @param prm_end_velo 最終スピード(Ve)
     * @param prm_target_distance 目標直線移動距離(D)
     * @param prm_p1 トップスピードに達する距離となるような、距離(D)に対する割合。(d1 = D*prm_p1)
     * @param prm_p2 減速を開始距離となるような、距離(D)に対する割合 (d1+d2 = D*p2)
     * @param prm_endacc_flg
     */
    void slideMvByVD(velo prm_top_velo, velo prm_end_velo,
                     coord prm_target_distance, float prm_p1, float prm_p2,
                     bool prm_endacc_flg = true);


    /**
     * なめらかな移動速度を変化させるシークエンスを実行(速度・時間指定、距離変動)  .
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
     *     |                         Vo:現時点の速度
     *     |                         Vt:トップスピード
     *     |                         Ve:最終速度
     *   Vt|....___________          Te:到達目標時間（フレーム数）
     *     |   /:         :＼        p1:トップスピードに達する時刻となるような、Teに対する割合(0.0～1.0)
     *   Ve|../.:.........:..＼      p2:減速を開始時刻となるような、Teに対する割合(0.0～1.0)
     *     | /  :         :    |      D:必要な移動距離
     *     |/   :         :    |
     *   Vo|    :    D    :    |
     *     |    :         :    |
     *   --+----+---------+----+-----> 時間(t:フレーム)
     *   0 |  p1*Te     p2*Te  Te
     *
     * </pre>
     * トップスピード(Vt)、最終スピード(Ve)、到達目標時間(Te)、及び p1, p2 を指定する。<BR>
     * 必要な移動距離(D)は内部で自動計算し決定される。<BR>
     * <BR>
     * @param prm_top_velo トップスピード(Vt)
     * @param prm_end_velo 最終スピード(Ve)
     * @param prm_target_frames 到達目標時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_p1 トップスピードに達する時刻となるような、Teに対する割合(0.0～1.0)
     * @param prm_p2 減速を開始時刻となるような、Teに対する割合(0.0～1.0)
     * @param prm_endacc_flg true:目標時間に達した際に加速度を０に強制設定/false:加速度はそのままにしておく
     */
    void slideMvByVT(velo prm_top_velo, velo prm_end_velo,
                     int prm_target_frames, float prm_p1, float prm_p2,
                     bool prm_endacc_flg = true);


//    void slideMv4(velo prm_end_velo, coord prm_target_distance, int prm_target_frames,
//                                   bool prm_endacc_flg = true);


    /**
     * 現在「なめらかな移動速度シークエンス」が実行中か否か .
     * 「なめらかな移動速度シークエンス」とは、<BR>
     * slideMvByDT()<BR>
     * slideMvByVD()<BR>
     * slideMvByVT()<BR>
     * の事。<BR>
     * @return true:現在実行中 / false:そうではない
     */
    bool isSlidingMv();

    /**
     * なめらかな移動速度シークエンスを中止する .
     * @return
     */
    void stopSlidingMv();

    /**
     * 現フレームで「なめらかな移動速度シークエンス」が完了したか否か .
     * 「なめらかな移動速度シークエンス」とは、<BR>
     * slideMvByDT()<BR>
     * slideMvByVD()<BR>
     * slideMvByVT()<BR>
     * の事。<BR>
     * @return true:完了した / false:そうではない
     */
    bool isJustFinishSlidingMv();

    /**
     * 黒衣Aの仕事を引継ぐ .
     * 他の GgafDxKurokoA オブジェクトを状態を自身に引継ぐ .
     * @param prm_pKurokoA 引継元
     */
    void takeoverMvFrom(GgafDxKurokoA* prm_pKurokoA);


    /**
     * 黒衣Aが振る舞う .
     * 黒衣A機能を利用する場合は、このメソッドを毎フレーム呼び出し実行してください。<BR>
     * 逆に黒衣Aを必要としない場合は、このメソッドを呼び出さないことで、パフォーマンスに影響を与えません。<BR>
     */
    virtual void behave();

    virtual ~GgafDxKurokoA();
};

}
#endif /*GGAFDXMVNAVIGATOR_H_*/

