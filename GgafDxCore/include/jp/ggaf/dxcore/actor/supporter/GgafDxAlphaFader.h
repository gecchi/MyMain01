#ifndef GGAFDXCORE_GGAFDXALPHAFADER_H_
#define GGAFDXCORE_GGAFDXALPHAFADER_H_
#include "jp/ggaf/core/GgafObject.h"

namespace GgafDxCore {

/**
 * フェーディング支援クラス .
 * GgafDxDrawableActor のメンバの
 * _alpha(アクターのα強度)をなめらかに変化させ、<BR>
 * フェーディングを行うことを主な目的<BR>
 * @version 1.00
 * @since 2010/07/28
 * @author Masatoshi Tsuge
 */
class GgafDxAlphaFader : public GgafCore::GgafObject {

public:
    /** [r]対象アクター */
    GgafDxDrawableActor* const _pActor;

    /** [r/w]αの強度(0:透明～1.0:不透明) */
    float _alpha;
    /** [r/w]αの目標の強度 */
    float _target_alpha;
    /** [r/w]αの強度上限 */
    float _top_alpha;
    /** [r/w]αの強度下限 */
    float _bottom_alpha;
    /** [r/w]αの毎フレームの強度の増分 */
    float _velo_alpha;
    /** [r/w]αの毎フレームの強度の増分の増分 */
    float _acce_alpha;
    /** [r]αのループカウント、2で１ループ（1はアルファ強度増大→終了(片道)、2はアルファ強度増大～減少の1ループ） */
    int _one_way_cnt;
    /** [r]αのストップする予定のループカウント */
    int _stop_one_way_num;
    /** [r]αのフェーディング方法 */
    GgafDxAlphaFadingMethod _method;

    /** [r]ビート時、αの台形波の波形でフェーディングのアタックフレーム数 */
    frame _beat_attack_frames;
    /** [r]ビート時、αの台形波の波形でフェーディングのレストフレーム数 */
    frame _beat_rest_frames;
    /** [r]ビート時、αの台形波の波形でアタックからの持続フレーム数 */
    frame _beat_duration_frames;
    /** [r]ビート時、αのフェーディングに費やすフレーム数 */
    frame _beat_target_frames;
    /** [r]ビート時、αのアタックから下限までのフレーム数 */
    frame _beat_down_frames;
    /** [r]ビート時、内部カウンター */
    frame _beat_frame_count;
    /** [r]ビート時、内部進捗番号 */
    int _beat_progres;

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用対象のActor
     */
    GgafDxAlphaFader(GgafDxDrawableActor* prm_pActor);

    /**
     * 強度を相対指定 .
     * @param prm_alpha_diff 強度値増分
     */
    inline void addAlpha(float prm_alpha_diff) {
        setAlpha(_alpha+prm_alpha_diff);
    }

    /**
     * 強度を絶対指定
     * @param prm_alpha 強度値
     */
    inline void setAlpha(float prm_alpha) {
        if (_top_alpha < prm_alpha) {
            _alpha = _top_alpha;
        } else if (_bottom_alpha > prm_alpha) {
            _alpha = _bottom_alpha;
        } else {
            _alpha = prm_alpha;
        }
    }

    /**
     * 強度の上限下限を設定
     * @param prm_alpha1 強度値1
     * @param prm_alpha2 強度値2
     */
    inline void forceRange(float prm_alpha1, float prm_alpha2) {
        if (prm_alpha1 < prm_alpha2) {
            _bottom_alpha = prm_alpha1;
            _top_alpha = prm_alpha2;
        } else {
            _bottom_alpha = prm_alpha2;
            _top_alpha = prm_alpha1;
        }
    }

    /**
     * 強度をリセット
     * 本オブジェクト(GgafDxAlphaFader)によって変化さえる前の
     * 初期の大きさに戻す。
     */
    inline void setToBottom() {
        _alpha = _bottom_alpha;
    }

    inline void setToTop() {
        _alpha = _top_alpha;
    }

    /**
     * フェーディングを停止させる。
     */
    inline void stopImmed() {
        _method = NO_ALPHAFADE;
    }

    /**
     * 状態をリセットする .
     * フェード中の場合は停止する。
     * 注意：但し、内部アルファ値は変更されません。
     */
    void reset();

    /**
     * 現在フェーディング中かどうか .
     * @return
     */
    inline bool isFading() {
        if (_method == NO_ALPHAFADE) {
            return false;
        } else {
            return true;
        }
    }

    /**
     * 片道等速フェーディング（持続フレーム数指定） .
     * 目標の強度へ一定速度でフェーディングする。
     * @param prm_target_alpha 目標強度
     * @param prm_spend_frame 費やすフレーム数
     */
    void fadeLinerUntil(float prm_target_alpha, frame prm_spend_frame);

    /**
     * 片道等速フェーディング（強度速度指定） .
     * 目標の強度へ一定速度でフェーディングする（強度差分指定） .
     * @param prm_target_alpha 目標強度
     * @param prm_velo_alpha 毎フレーム加算する強度差分(>0.0)。正の強度を指定する事。加算か減算かは自動判断する。
     */
    void fadeLinerStep(float prm_target_alpha, float prm_velo_alpha);

    /**
     * 片道加速フェーディング（強度速度・強度加速度指定） .
     * 目標の強度へ加速指定でフェーディングする（強度速度、強度加速度差指定） .
     * 強度加速度を0に指定すると fadeLinerStep とほぼ同じ意味になる。
     * fadeLinerStep の第３引数は正負を気にすること無いが、本メソッドは正負の自動判定はしない（できない）。
     * @param prm_target_alpha 目標強度
     * @param prm_velo_alpha 初期強度速度
     * @param prm_acce_alpha 強度加速度
     */
    void fadeAcceStep(float prm_target_alpha, float prm_velo_alpha, float prm_acce_alpha);

    /**
     * 反復等速フェーディング（フレーム数指定）
     * 目標の強度へ一定速度でフェーディングし、一定速度で元に戻る。
     * これをループ指定する。（１ループのフレーム数指定） .
     * @param prm_beat_target_frames １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_beat_num ループする回数(0.5 回単位で指定可能)
     */
    void loopLiner(frame prm_beat_target_frames, float prm_beat_num);

    /**
     * 台形波でフェーディングする。 .
     * <PRE>
     *             ←③→
     * ⑤  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
     *            /      ＼                     /      ＼
     *           /         ＼                  /         ＼
     *          /            ＼               /            ＼
     *         /               ＼            /               ＼
     *        /                  ＼         /                  ＼
     * ⑥  ＿/                     ＼＿＿＿/                     ＼＿
     *
     *       ←②→                  ←④→
     *       ←──────── ① ────→
     * </PRE>
     * ＜必要な設定値＞<BR>
     * ① １ループのフレーム数<BR>
     * ② アタックまでのフレーム数<BR>
     * ③ 持続フレーム数<BR>
     * ④ 休憩フレーム数<BR>
     * ⑤ 強度上限(_top_alpha、保持するαの強度上限)<BR>
     * ⑥ 強度下限(_bottom_alpha、保持するαの強度下限)<BR>
     * @param prm_beat_target_frames 上図で①のフレーム数
     * @param prm_attack_frames 上図で②のフレーム数
     * @param prm_duration_frames 上図で③のフレーム数
     * @param prm_rest_frames 上図で④のフレーム数
     * @param prm_beat_num ループ数(-1で無限)
     */
    void beat(frame prm_beat_target_frames,
              frame prm_attack_frames,
              frame prm_duration_frames,
              frame prm_rest_frames,
              float prm_beat_num);

    /**
     * 毎フレームの振る舞いメソッド。<BR>
     * 本クラスの機能を利用する場合は、このメソッドを<BR>
     * 毎フレーム実行することが必要。
     */
    virtual void behave();

    virtual ~GgafDxAlphaFader();
};

}
#endif /*GGAFDXCORE_GGAFDXALPHAFADER_H_*/

