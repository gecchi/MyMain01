#ifndef GGAFDXCORE_GGAFDXKUROKOHELPERB_H_
#define GGAFDXCORE_GGAFDXKUROKOHELPERB_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"
#include "jp/ggaf/core/util/GgafValueAccelerator.hpp"

namespace GgafDxCore {

/**
 * 黒衣の助手B .
 * 師匠(黒衣)の軸回転方角角速度の補佐を行います。
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
class GgafDxKurokoAssistantB : public GgafCore::GgafObject {

public:
    /** [r]師匠 */
    GgafDxKuroko* _pMaster;
    GgafCore::GgafValueAccelerator<int> _smthFaceAng[3];

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pMaster  師匠
     */
    explicit GgafDxKurokoAssistantB(GgafDxKuroko* prm_pMaster);


    /**
     * 軸回転方角を滑らかに回転するシークエンスを実行(角距離指定、時間指定、角速度変動) .
     * 角回転移動に費やされる時間(Te)を3つのセクションに分け、次のような角速度制御を自動的に行う。<BR>
     * ・時間 0     〜 時間 p1*Te まで ・・・ 現在の角速度からトップ角速度まで回転速度を加速<BR>
     * ・時間 p1*Te 〜 時間 p2*Te まで ・・・ トップスピードで等速角速度で等速回転<BR>
     * ・時間 p2*Te 〜 時間 Te    まで ・・・ トップスピードから最終角速度へ回転速度を減速<BR>
     * ※下図参照<BR>
     * <pre>
     *
     *    角速度(ω)
     *     ^
     *     |                         θ:目標移動角（距離）    ・・・引数 prm_angular_distance
     *     |                        ω0:現時点の角速度        ・・・_angvelo_face[prm_axis]
     *     |                        ωt:トップ角速度          ・・・変動、計算される
     *     |                        ωe:最終速度              ・・・引数 prm_end_angvelo
     *  ωt|....___________          Te:目標時間（フレーム数）・・・引数 prm_target_frames
     *     |   /:         :＼        p1:トップ角速度に達する時刻となるような、Teに対する割合・・・引数 prm_p1
     *  ωe|../.:.........:..＼      p2:回転の減速を開始する時刻となるような、Teに対する割合・・・引数 prm_p2
     *     | /  :         :    |
     *     |/   :         :    |
     *  ω0|    :    θ   :    |
     *     |    :         :    |
     *   --+----+---------+----+-----> 時間(t:フレーム)
     *   0 |  p1*Te     p2*Te  Te
     *
     * </pre>
     * @param prm_axis 回転方角軸(AXIS_X or AXIS_Y or AXIS_Z)
     * @param prm_angular_distance 目標角距離(θ)（正負により回転方向有り。正：TURN_COUNTERCLOCKWISE、負：TURN_CLOCKWISE）
     * @param prm_target_frames 費やす時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_p1 トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_p2 減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_end_angvelo 目標到達時の最終角速度(ωe) （内部で正負がprm_angular_distanceの正負に合わせられる）
     * @param prm_endacc_flg true:目標移動距離に達した際に角加速度を０に強制設定/false:角加速度はそのままにしておく
     */
    void turnFaceAngByDt(axis prm_axis,
                             angle prm_angular_distance, int prm_target_frames,
                             float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                             bool prm_endacc_flg);

    /**
     * 目標の軸回転方角(Z軸)へ滑らかに回転するシークエンスを実行(時間指定、角速度変動) .
     * @param prm_ang_rz_target 到達目標のZ軸回転方角
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_target_frames 費やす時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_p1 トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_p2 減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_end_angvelo 目標到達時の最終角速度(ωe) （内部で正負がprm_angular_distanceの正負に合わせられる）
     * @param prm_endacc_flg true:目標移動距離に達した際に角加速度を０に強制設定/false:角加速度はそのままにしておく
     */
    void turnRzFaceAngByDtTo(angle prm_ang_rz_target, int prm_way, int prm_target_frames,
                                 float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                 bool prm_endacc_flg);

    /**
     * 目標の軸回転方角(Y軸)へ滑らかに回転するシークエンスを実行(時間指定、角速度変動) .
     * @param prm_ang_rt_target 到達目標のY軸回転方角
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_target_frames 費やす時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_p1 トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_p2 減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_end_angvelo 目標到達時の最終角速度(ωe) （内部で正負がprm_angular_distanceの正負に合わせられる）
     * @param prm_endacc_flg true:目標移動距離に達した際に角加速度を０に強制設定/false:角加速度はそのままにしておく
     */
    void turnRyFaceAngByDtTo(angle prm_ang_rt_target, int prm_way, int prm_target_frames,
                             float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                             bool prm_endacc_flg);
    /**
     * 目標の軸回転方角(X軸)へ滑らかに回転するシークエンスを実行(時間指定、角速度変動) .
     * @param prm_ang_rt_target 到達目標のX軸回転方角
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_target_frames 費やす時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_p1 トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_p2 減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_end_angvelo 目標到達時の最終角速度(ωe) （内部で正負がprm_angular_distanceの正負に合わせられる）
     * @param prm_endacc_flg true:目標移動距離に達した際に角加速度を０に強制設定/false:角加速度はそのままにしておく
     */
    void spinRxFaceAngByDtTo(angle prm_ang_rx_target, int prm_way, int prm_target_frames,
                                     float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                     bool prm_endacc_flg);

    /**
     * 目標の軸回転方角へ滑らかに回転するシークエンスを実行(時間指定、角速度変動) .
     * @param prm_ang_rz_target 目標Z軸回転方角
     * @param prm_ang_ry_target 目標Y軸回転方角
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_optimize_ang ターゲットアングルを最適化するかどうかを指定。<BR>
     *                         true: 引数の prm_ang_rz_target, prm_ang_ry_target までの距離と、<BR>
     *                               同じ方向を意味するもう一組の RzRy までの距離を割り出し、<BR>
     *                               到達フレーム数の少ない方の RzRy の組み合わせを自動採用する。<BR>
     *                               所望の方向に最短フレームでターゲットするが、内部の _angMvRz, _angMvRy は<BR>
     *                               引数のターゲットアングル値と一致しないかもしれない。(姿勢が異なる可能性有り)<BR>
     *                               (注意：極地Y軸回転があるため、最短フレームは必ずしも最短距離にあらず)<BR>
     *                         false:引数の prm_ang_rz_target, prm_ang_ry_target をそのままターゲートとする。<BR>
     * @param prm_target_frames 費やす時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_p1 トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_p2 減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_end_angvelo 目標到達時の最終角速度(ωe)
     * @param prm_endacc_flg true:目標移動距離に達した際に角加速度を０に強制設定/false:角加速度はそのままにしておく
     */
    void turnRzRyFaceAngByDtTo(
            angle prm_ang_rz_target, angle prm_ang_ry_target, int prm_way, bool prm_optimize_ang,
            int prm_target_frames,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);

    /**
     * 目標の座標に向くように、滑らかに回転するシークエンスを実行(時間指定、角速度変動) .
     * @param prm_tx 目標X座標
     * @param prm_ty 目標Y座標
     * @param prm_tz 目標Z座標
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_optimize_ang ターゲットアングルを最適化するかどうかを指定。<BR>
     * @param prm_target_frames 費やす時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_p1 トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_p2 減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_end_angvelo 目標到達時の最終角速度(ωe)
     * @param prm_endacc_flg true:目標移動距離に達した際に角加速度を０に強制設定/false:角加速度はそのままにしておく
     */
    void turnFaceAngByDtTwd(
            coord prm_tx, coord prm_ty, coord prm_tz, int prm_way, bool prm_optimize_ang,
            int prm_target_frames,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);

    /**
     * 目標のアクターの座標に向くように、滑らかに回転するシークエンスを実行(時間指定、角速度変動) .
     * @param prm_pActor_target 目標アクター
     * @param prm_way ターゲットするための、回転方向指示。次のいずれかを指定。<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_optimize_ang ターゲットアングルを最適化するかどうかを指定。<BR>
     * @param prm_target_frames 費やす時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_p1 トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_p2 減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_end_angvelo 目標到達時の最終角速度(ωe)
     * @param prm_endacc_flg true:目標移動距離に達した際に角加速度を０に強制設定/false:角加速度はそのままにしておく
     */
    void turnFaceAngByDtTwd(
            GgafDxGeometricActor* prm_pActor_target, int prm_way, bool prm_optimize_ang,
            int prm_target_frames,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);

    /**
     * 目標の軸回転方角(Z軸)へ滑らかに回転するシークエンスを実行(速度・距離指定、時間変動) .
     * 移動距離を3つのセクション(θ1,θ2,θ3)に分け、次のような角速度制御を自動的に行う。<BR>
     * ・距離角 0       〜 距離角 θ1         まで ・・・ 現在のθ速度からトップスピードまで角加速(or減速)回転<BR>
     * ・距離角 θ1     〜 距離角 θ1+θ2     まで ・・・ トップスピードで等速角回転<BR>
     * ・距離角 θ1+θ2 〜 距離角 θ1+θ2+θ3 まで ・・・ トップスピードから最終スピードへ角減速(or加速)回転<BR>
     * ※下図参照<BR>
     * <pre>
     *    角速度(ω)
     *     ^
     *     |                        ω0:現時点の角速度
     *     |                        ωt:トップ角速度
     *     |                        ωe:最終角速度
     *     |       θ=θ1+θ2+θ3    θ:目標回転距離角
     *  ωt|....___________          p1:トップ角速度に達する角距離となるような、θに対する割合
     *     |   /|         |＼            つまり     θ1 = θ*p1 となるような p1 (0.0〜1.0)
     *  ωe|../.|.........|..＼      p2:減速を開始距離となるような、θ対する割合
     *     | /  |         |    |         つまり θ1+θ2 = θ*p2 となるような p2 (0.0〜1.0)
     *     |/   |         |    |     Te:費やされる必要時間（フレーム数）
     *  ω0|θ1 |   θ2   |θ3 |
     *     |    |         |    |
     *   --+----+---------+----+-----> 時間(t:フレーム)
     *   0 |                  Te
     *
     * </pre>
     * トップスピード(ωt)、最終スピード(ωe)、目標回転距離角(θ)、及び p1, p2 を指定する。<BR>
     * 費やされる時間(Te)は内部で自動計し決定される。<BR>
     * <BR>
     * @param prm_axis 回転方角軸(AXIS_X or AXIS_Y or AXIS_Z)
     * @param prm_top_angvelo トップ角速度(ωt)
     * @param prm_angular_distance 目標角距離(θ)（正負により回転方向有り。正：TURN_COUNTERCLOCKWISE、負：TURN_CLOCKWISE）
     * @param prm_p1 トップスピードに達する距離となるような、回転距離角(θ)に対する割合。(θ1 = θ*prm_p1)
     * @param prm_p2 角回転の減速を開始角となるような、回転距離角(θ)に対する割合 (θ1+θ2 = θ*p2)
     * @param prm_end_angvelo 最終角速度(ωe)
     * @param prm_endacc_flg true:目標時間に達した際に角加速度を０に強制設定/false:角加速度はそのままにしておく
     */
    void turnFaceAngByVd(
            axis prm_axis,
            angvelo prm_top_angvelo, angle prm_angular_distance,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);

    void turnRzFaceAngByVdTo(
            angvelo prm_top_angvelo, angle prm_ang_rz_target, int prm_way,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);

    void turnRyFaceAngByVdTo(
            angvelo prm_top_angvelo, angle prm_ang_ry_target, int prm_way,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);

    void spinRxFaceAngByVdTo(
            angvelo prm_top_angvelo, angle prm_ang_rx_target, int prm_way,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);


    void turnRzRyFaceAngByVdTo(
            angvelo prm_top_angvelo,
            angle prm_ang_rz_target, angle prm_ang_ry_target, int prm_way, bool prm_optimize_ang,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);

    void turnFaceAngByVdTwd(
            angvelo prm_top_angvelo,
            coord prm_tx, coord prm_ty, coord prm_tz, int prm_way, bool prm_optimize_ang,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);

    void turnFaceAngByVdTwd(
            angvelo prm_top_angvelo,
            GgafDxGeometricActor* prm_pActor_target, int prm_way, bool prm_optimize_ang,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);

    inline bool isTurningFaceAng() {
        if (_smthFaceAng[AXIS_X]._prm._flg || _smthFaceAng[AXIS_Y]._prm._flg || _smthFaceAng[AXIS_Z]._prm._flg) {
            return true;
        } else {
            return false;
        }
    }

    inline void stopTurnFaceAng() {
        _smthFaceAng[AXIS_X]._prm._flg = false;
        _smthFaceAng[AXIS_Y]._prm._flg = false;
        _smthFaceAng[AXIS_Z]._prm._flg = false;
    }

    /**
     * 黒衣の助手が振る舞う .
     * 助手が、師匠にいろいろ設定を行いますので、師匠が振る舞う(behave())前に実行しましょう。
     */
    virtual void behave();

    virtual ~GgafDxKurokoAssistantB();
};

}
#endif /*GGAFDXCORE_GGAFDXKUROKOHELPERB_H_*/

