#ifndef GGAF_CORE_TRANSITIONVALUESET_H_
#define GGAF_CORE_TRANSITIONVALUESET_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include "jp/ggaf/core/util/Util.h"

namespace GgafCore {

/**
 * 値の遷移ヘルパー .
 * 終に念願の共通化。
 * @tparam VAL_TYPE 遷移値のデータ型
 * @tparam N インデックス(軸等)の数
 * @version 1.00
 * @since 2014/02/19
 * @author Masatoshi Tsuge
 */
template<class VAL_TYPE, int N>
class ValueTransitioner : public Object {

public:
    enum TransitionMethod {
        NO_TRANSITION,                 //!< 値遷移なし
        TARGET_LINEAR_UNTIL,           //!< 目標値まで片道等速で遷移（フレーム数指定）
        TARGET_LINEAR_STEP,            //!< 目標値まで片道等速で遷移（速度指定）
        BEAT_LINEAR,                   //!< 等速値遷移で目標値まで到達した、また元に戻る（フレーム数指定）
        BEAT_TRIANGLEWAVE,             //!< 台形波の波形で値を遷移
        R_BEAT_TRIANGLEWAVE,           //!< 逆台形波の波形で値を遷移
        TARGET_ACCELERATION_UNTIL,     //!< 片道加速値遷移（遷移目標値指定）
        TARGET_ACCELERATION_UNTIL_VELO,//!< 片道加速値遷移（目標速度値指定）
    };

    struct Parameter {
        /** [r/w]目標の遷移 */
        VAL_TYPE _target;
        /** [r/w]遷移上限 */
        VAL_TYPE _top;
        /** [r/w]遷移下限 */
        VAL_TYPE _bottom;
        /** [r/w]毎フレームの遷移の増分 */
        VAL_TYPE _velo;
        /** [r/w]毎フレームの遷移の増分の増分 */
        VAL_TYPE _acce;
        /** [r]値遷移方法 */
        TransitionMethod _method;
        /** [r]ビート時、台形波のアタック終了時のフレーム */
        frame _beat_frame_of_attack_finish;
        /** [r]ビート時、台形波の維持終了時のフレーム */
        frame _beat_frame_of_sustain_finish;
        /** [r]ビート時、台形波の減衰(余韻)終了時のフレーム */
        frame _beat_frame_of_release_finish;
        /** [r]ビート時、台形波の波形での１周期のフレーム数 */
        frame _beat_cycle_frames;
        /** [r]ビート時、値遷移に費やすフレーム数 */
        frame _beat_target_frames;
        /** [r]ビート時、内部ループ数カウンター */
        frame _beat_frame_count_in_roop;
        /** [r]ビート時、内部カウンター */
        frame _beat_frame_count;
    };
    Parameter _parameter[N];

public:
    /**
     * 値を取得する（要実装） .
     * @param idx インデックス
     * @return 値
     */
    virtual VAL_TYPE getValue(int idx) = 0;

    /**
     * 値を設定する（要実装） .
     * @param idx インデックス
     * @param value 値
     */
    virtual void setValue(int idx, VAL_TYPE value) = 0;

public:
    /**
     * コンストラクタ<BR>
     */
    ValueTransitioner() : Object() {
        Parameter* p = _parameter;
        for (int i = 0; i < N; i++) {
            p->_velo = 0;
            p->_acce = 0;
            p->_target = 0;
            p->_top = 0;
            p->_bottom = 0;
            p->_beat_frame_of_attack_finish = 0;
            p->_beat_frame_of_sustain_finish = 0;
            p->_beat_frame_of_release_finish = 0;
            p->_beat_cycle_frames = 0;
            p->_beat_target_frames = 0;
            p->_beat_frame_count_in_roop = 0;
            p->_beat_frame_count = 0;
            p->_method = NO_TRANSITION;
            ++p;
        }
    }

    /**
     * 値遷移の上限下限を設定（全対象インデックス指定） .
     * 引数の大小は気にせず渡して(内部で自動判別)
     * @param prm1 遷移値1
     * @param prm2 遷移値2
     */
    virtual void setRange(VAL_TYPE prm1, VAL_TYPE prm2) {
        for (int i = 0; i < N; i++) {
            setRange(i, prm1, prm2);
        }
    }

    /**
     * 値遷移の上限下限値を設定（対象インデックス単位で指定） .
     * @param prm_idx 対象インデックス
     * @param prm1 遷移値1
     * @param prm2 遷移値2
     */
    virtual void setRange(int prm_idx, VAL_TYPE prm1, VAL_TYPE prm2) {
        if (prm1 < prm2) {
            setBottom(prm_idx, prm1);
            setTop(prm_idx, prm2);
        } else {
            setBottom(prm_idx, prm2);
            setTop(prm_idx, prm1);
        }
    }

    /**
     * 上限値を設定（対象インデックス単位で指定） .
     * @param prm_idx 対象インデックス
     * @param prm_top 上限値
     */
    virtual void setTop(int prm_idx, VAL_TYPE prm_top) {
        _parameter[prm_idx]._top = prm_top;
    }

    /**
     * 下限値を設定（対象インデックス単位で指定） .
     * @param prm_bottom 下限値
     */
    virtual void setBottom(int prm_idx, VAL_TYPE prm_bottom) {
        _parameter[prm_idx]._bottom = prm_bottom;
    }

    /**
     * 上限値を設定（全対象インデックス指定） .
     * @param prm_top 上限値
     */
    virtual void setTop(VAL_TYPE prm_top) {
        for (int i = 0; i < N; i++) {
            setTop(i, prm_top);
        }
    }

    /**
     * 下限値を設定（全対象インデックス指定） .
     * @param prm_bottom 下限値
     */
    virtual void setBottom(VAL_TYPE prm_bottom) {
        for (int i = 0; i < N; i++) {
            setBottom(i, prm_bottom);
        }
    }

    /**
     * 値遷移の上限値を取得 .
     * @param prm_idx 対象インデックス
     * @return 上限値
     */
    virtual VAL_TYPE getTop(int prm_idx) const {
        return _parameter[prm_idx]._top;
    }

    /**
     * 値遷移の下限値を取得 .
     * @param prm_idx 対象インデックス
     * @return
     */
    virtual VAL_TYPE getBottom(int prm_idx) const {
        return _parameter[prm_idx]._bottom;
    }

    /**
     * 値遷移の上限値を取得 .
     * 対象インデックスが２以上の場合、全上限値の中で最小を返す。
     * @return 上限値
     */
    virtual VAL_TYPE getTop() const {
        //_topの最小値を返す
        if (N == 1) {
            return _parameter[0]._top;
        } else {
            VAL_TYPE minv = _parameter[0]._top;
            const Parameter* p = &_parameter[1];
            for (int i = 1; i < N; i++) {
                if (minv > p->_top) {
                    minv = p->_top;
                }
                ++p;
            }
            return minv;
        }
    }

    /**
     * 値遷移の下限値を取得 .
     * 対象インデックスが２以上の場合、全下限値の中で最大を返す。
     * @return 上限値
     */
    virtual VAL_TYPE getBottom() const {
        //_bottomの最大値を返す
        if (N == 1) {
            return _parameter[0]._bottom;
        } else {
            VAL_TYPE maxv = _parameter[0]._bottom;
            const Parameter* p = &_parameter[1];
            for (int i = 1; i < N; i++) {
                if (maxv > p->_bottom) {
                    maxv = p->_bottom;
                }
                ++p;
            }
            return maxv;
        }
    }

    /**
     * 値遷移を停止させる。（全対象インデックス指定） .
     */
    virtual void stop() {
        for (int i = 0; i < N; i++) {
            stop(i);
        }
    }

    /**
     * 値遷移を停止させる。 （対象インデックス単位で指定）.
     * @param prm_idx インデックス
     */
    virtual void stop(int prm_idx) {
        Parameter* p = &_parameter[prm_idx];
        p->_velo = 0;
        p->_acce = 0;
        p->_method = NO_TRANSITION;
    }

    /**
     * 片道等速値遷移（全インデックス対象・持続フレーム数指定） .
     * 目標の遷移へ一定速度で値遷移する
     * @param prm_target_T 遷移目標値
     * @param prm_spend_frame 費やすフレーム数
     */
    virtual void transitionLinearUntil(VAL_TYPE prm_target, frame prm_spend_frame) {
        for (int i = 0; i < N; i++) {
            transitionLinearUntil(i, prm_target, prm_spend_frame);
        }
    }

    /**
     * 片道等速値遷移（対象インデックス単位・持続フレーム数指定） .
     * 目標の遷移へ一定速度で値遷移する。
     * @param prm_idx 対象インデックス
     * @param prm_target_T 遷移目標値
     * @param prm_spend_frame 費やすフレーム数
     */
    virtual void transitionLinearUntil(int prm_idx, VAL_TYPE prm_target, frame prm_spend_frame) {
        Parameter* p = &_parameter[prm_idx];
        p->_beat_frame_count = 0;
        p->_beat_target_frames = prm_spend_frame;
        p->_target = prm_target;
        p->_method = TARGET_LINEAR_UNTIL;
        //最初のアタックまでの速度
        const VAL_TYPE val = getValue(prm_idx);
        if (p->_beat_target_frames > 0 ) {
            p->_velo = (VAL_TYPE)( ((double)(p->_target - val)) / ((double)(p->_beat_target_frames)) );
        } else if (p->_beat_target_frames == 0 ) {
            p->_velo = p->_target - val;
        }
    }

    /**
     * 上限遷移へ片道等速値遷移（全インデックス対象・持続フレーム数指定） .
     * @param prm_spend_frame 費やすフレーム数
     */
    virtual void transitionLinearToTop(frame prm_spend_frame) {
        transitionLinearUntil(getTop(), prm_spend_frame);
    }

    /**
     * 上限遷移へ片道等速値遷移（対象インデックス単位・持続フレーム数指定） .
     * @param prm_idx 対象インデックス
     * @param prm_spend_frame 費やすフレーム数
     */
    virtual void transitionLinearToTop(int prm_idx, frame prm_spend_frame) {
        transitionLinearUntil(prm_idx, getTop(), prm_spend_frame);
    }

    /**
     * 下限遷移へ片道等速値遷移（全インデックス対象・持続フレーム数指定） .
     * @param prm_spend_frame 費やすフレーム数
     */
    virtual void transitionLinearToBottom(frame prm_spend_frame) {
        transitionLinearUntil(getBottom(), prm_spend_frame);
    }

    /**
     * 下限遷移へ片道等速値遷移（対象インデックス単位・持続フレーム数指定） .
     * @param prm_idx 対象インデックス
     * @param prm_spend_frame 費やすフレーム数
     */
    virtual void transitionLinearToBottom(int prm_idx, frame prm_spend_frame) {
        transitionLinearUntil(prm_idx, getBottom(), prm_spend_frame);
    }


    /**
     * 片道等速値遷移（全インデックス対象・遷移速度指定） .
     * 目標の遷移へ一定速度で値遷移する
     * @param prm_target 遷移目標値
     * @param prm_velo 毎フレーム加算する遷移差分(>0.0)。正の遷移を指定する事。加算か減算かは自動判断する。
     */
    virtual void transitionLinearStep(VAL_TYPE prm_target, VAL_TYPE prm_velo) {
        for (int i = 0; i < N; i++) {
            transitionLinearStep(i, prm_target, prm_velo);
        }
    }

    /**
     * 片道等速値遷移（対象インデックス単位・遷移速度指定） .
     * 目標の遷移へ一定速度で値遷移する（遷移差分指定） .
     * @param prm_idx 対象インデックス
     * @param prm_target 遷移目標値
     * @param prm_velo 毎フレーム加算する遷移差分(>0.0)。正の遷移を指定する事。加算か減算かは自動判断する。
     */
    virtual void transitionLinearStep(int prm_idx, VAL_TYPE prm_target, VAL_TYPE prm_velo) {
        Parameter* p = &_parameter[prm_idx];
        p->_method = TARGET_LINEAR_STEP;
        p->_velo = prm_velo;
        p->_target = prm_target;
        p->_beat_frame_count = 0;
        p->_beat_target_frames = MAX_FRAME;
    }

    /**
     * 片道加速値遷移（全インデックス対象・遷移目標値指定） .
     * 目標の遷移へ加速指定で値遷移する。
     * 遷移加速度を0に指定すると transitionLinearStep とほぼ同じ意味になる。
     * transitionLinearStep の第３引数は正負を気にすること無いが、本メソッドは正負の自動判定はしない（できない）。
     * 遷移速度が正の場合、遷移目標値を超えると値遷移終了。
     * 遷移速度が負の場合、遷移目標値を下回ると値遷移終了。
     * 遷移目標値に到達する前に、速度の正負が逆転すると、たぶん永遠に到達できないので注意。
     * @param prm_target_T 遷移目標値
     * @param prm_init_velo 初期遷移速度
     * @param prm_acce_T 遷移加速度
     */
    virtual void transitionAcceUntil(VAL_TYPE prm_target, VAL_TYPE prm_init_velo, VAL_TYPE prm_acce) {
        for (int i = 0; i < N; i++) {
            transitionAcceUntil(i, prm_target, prm_init_velo, prm_acce);
        }
    }

    /**
     * 片道加速値遷移（対象インデックス単位・遷移目標値指定） .
     * 目標の遷移へ加速指定で値遷移する。
     * 遷移加速度を0に指定すると transitionLinearStep とほぼ同じ意味になる。
     * transitionLinearStep の第３引数は正負を気にすること無いが、本メソッドは正負の自動判定はしない（できない）。
     * 遷移速度が正の場合、遷移目標値を超えると値遷移終了。
     * 遷移速度が負の場合、遷移目標値を下回ると値遷移終了。
     * 遷移目標値に到達する前に、速度の正負が逆転すると、たぶん永遠に到達できないので注意。
     * @param prm_idx 対象インデックス
     * @param prm_target 遷移目標値
     * @param prm_init_velo 初期遷移速度
     * @param prm_acce 遷移加速度
     */
    virtual void transitionAcceUntil(int prm_idx, VAL_TYPE prm_target, VAL_TYPE prm_init_velo, VAL_TYPE prm_acce) {
        Parameter* p = &_parameter[prm_idx];
        p->_method = TARGET_ACCELERATION_UNTIL;
        p->_target = prm_target;
        p->_velo = prm_init_velo;
        p->_acce = prm_acce;
        p->_beat_frame_count = 0;
        p->_beat_target_frames = MAX_FRAME;
    }

    /**
     * 片道加速値遷移（対象インデックス単位・目標速度値指定） .
     * 目標速度になるまでへ加速指定で値遷移します。
     * 目標速度に到達すると停止します。
     * 加速度が正の場合、速度がターゲット速度より大きくなれば終了
     * 加速度が負の場合、速度がターゲット速度より小さくなれば終了
     * 遷移加速度を0に指定すると 永遠に終わらないので注意。
     * @param prm_idx  対象インデックス
     * @param prm_target_velo  目標速度
     * @param prm_init_velo  初期速度
     * @param prm_acce   加速度
     */
    virtual void transitionAcceUntilVelo(int prm_idx, VAL_TYPE prm_target_velo, VAL_TYPE prm_init_velo, VAL_TYPE prm_acce) {
        Parameter* p = &_parameter[prm_idx];
        p->_method = TARGET_ACCELERATION_UNTIL_VELO;
        p->_target = prm_target_velo;
        p->_velo = prm_init_velo;
        p->_acce = prm_acce;
        p->_beat_frame_count = 0;
        p->_beat_target_frames = MAX_FRAME;
    }

    /**
     * 片道加速値遷移（全インデックス対象・目標速度値指定） .
     * 目標速度になるまでへ加速指定で値遷移します。
     * 目標速度に到達すると停止します。
     * 加速度が正の場合、速度がターゲット速度より大きくなれば終了
     * 加速度が負の場合、速度がターゲット速度より小さくなれば終了
     * 遷移加速度を0に指定すると 永遠に終わらないので注意。
     * @param prm_target_velo  目標速度
     * @param prm_init_velo  初期速度
     * @param prm_acce   加速度
     */
    virtual void transitionAcceUntilVelo(VAL_TYPE prm_target_velo, VAL_TYPE prm_init_velo, VAL_TYPE prm_acce) {
        for (int i = 0; i < N; i++) {
            transitionAcceUntilVelo(i, prm_target_velo, prm_init_velo, prm_acce);
        }
    }

    /**
     * 反復等速値遷移（全インデックス対象・フレーム数指定） .
     * 上限遷移へ一定速度で値遷移し、一定速度で下遷移へ戻る。これをループ指定する。（１ループのフレーム数指定） .
     * @param prm_cycle_frames １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_beat_num ループする回数(1.2回など少数で指定可能、-1 でほぼ無限ループ)
     * @param prm_is_to_top true:初めはTOPに遷移する／false:初めはBOTTOMに遷移
     */
    void transitionLinearLoop(frame prm_cycle_frames, double prm_beat_num, bool prm_is_to_top) {
        for (int i = 0; i < N; i++) {
            transitionLinearLoop(i, prm_cycle_frames, prm_beat_num, prm_is_to_top);
        }
    }

    /**
     * 反復等速値遷移（対象インデックス単位・フレーム数指定）
     * 上限遷移へ一定速度で値遷移し、一定速度で下遷移へ戻る。
     * これをループ指定する。（１ループのフレーム数指定） .
     * @param prm_idx 対象インデックス
     * @param prm_cycle_frames １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_beat_num ループする回数(1.2回など少数で指定可能、-1 でほぼ無限ループ)
     * @param prm_is_to_top true:初めはTOPに遷移する／false:初めはBOTTOMに遷移
     */
    virtual void transitionLinearLoop(int prm_idx, frame prm_cycle_frames, double prm_beat_num, bool prm_is_to_top) {
        Parameter* p = &_parameter[prm_idx];
        const VAL_TYPE val = getValue(prm_idx);
        p->_method = BEAT_LINEAR;
        p->_beat_frame_count = 0;
        p->_beat_frame_count_in_roop = 0;
        p->_beat_cycle_frames = prm_cycle_frames;
        if (prm_beat_num < 0) {
            p->_beat_target_frames = MAX_FRAME;
        } else {
            p->_beat_target_frames = (frame)(prm_cycle_frames * prm_beat_num);
        }
        if (prm_is_to_top) {
            p->_velo = (VAL_TYPE)(1.0*(p->_top - val) / ((int)prm_cycle_frames * 0.5));
            if (ZEROd_EQ(p->_velo)) {
                p->_velo = 1; //正であればよい
            }
        } else {
            p->_velo = (VAL_TYPE)(1.0*(p->_bottom - val) / ((int)prm_cycle_frames * 0.5));
            if (ZEROd_EQ(p->_velo)) {
                p->_velo = -1; //負であればよい
            }
        }
    }

    /**
     * 台形波の波形で値を遷移する。（全対象インデックス指定）.
     * <PRE>
     * ⑤  _ _ _   ＿＿＿   _ _ _ _ _ _ _ _ _    ＿＿＿   _ _ _ _ _ _ _ _ _
     *            /:    :＼                     /      ＼
     *           / :    :  ＼                  /         ＼
     *          /  :    :    ＼               /            ＼
     *         /   :    :      ＼            /               ＼
     *        /    :    :        ＼         /                  ＼
     * ⑥＿＿/  _ _:_ _ : _ _ _ _  ＼＿＿＿/  _ _ _ _ _ _ _ _ _  ＼＿＿＿/
     *       ←──①──────────→
     *       ←②→←③→←──④─→
     * </PRE>
     * ＜必要な設定値＞<BR>
     * ① １ループ(変化して元に戻るまで)に費やすフレーム数<BR>
     * ② アタックまでのフレーム数<BR>
     * ③ 維持フレーム数<BR>
     * ④ 減衰(余韻)フレーム数<BR>
     * ⑤ 遷移上限(_top[対象インデックス] 配列が保持)<BR>
     * ⑥ 遷移下限(_bottom[対象インデックス] 配列が保持)<BR>
     * この内 ①～④を引数で設定、⑤⑥はsetRange()の設定値が使用される。<BR>
     * @param prm_cycle_frames 上図で①のフレーム数
     * @param prm_attack_frames 上図で②のフレーム数
     * @param prm_sustain_frames 上図で③のフレーム数
     * @param prm_release_frames 上図で④のフレーム数
     * @param prm_beat_num ループ数(-1で無限)
     */
    virtual void beat(frame prm_cycle_frames,
                      frame prm_attack_frames,
                      frame prm_sustain_frames,
                      frame prm_release_frames,
                      double prm_beat_num) {
        for (int i = 0; i < N; i++) {
            beat(i, prm_cycle_frames, prm_attack_frames, prm_sustain_frames, prm_release_frames, prm_beat_num);
        }
    }

    /**
     * 台形波の波形で値を遷移する。（対象インデックス別指定）.
     * <PRE>
     * ⑤  _ _ _   ＿＿＿   _ _ _ _ _ _ _ _ _    ＿＿＿   _ _ _ _ _ _ _ _ _
     *            /:    :＼                     /      ＼
     *           / :    :  ＼                  /         ＼
     *          /  :    :    ＼               /            ＼
     *         /   :    :      ＼            /               ＼
     *        /    :    :        ＼         /                  ＼
     * ⑥＿＿/  _ _:_ _ : _ _ _ _  ＼＿＿＿/  _ _ _ _ _ _ _ _ _  ＼＿＿＿/
     *       ←──①──────────→
     *       ←②→←③→←──④─→
     * </PRE>
     * ＜必要な設定値＞<BR>
     * ① １周期(変化して元に戻るまで)に費やすフレーム数<BR>
     * ② アタックまでのフレーム数<BR>
     * ③ 維持フレーム数<BR>
     * ④ 減衰(余韻)フレーム数<BR>
     * ⑤ 遷移上限(_top[対象インデックス] 配列が保持)<BR>
     * ⑥ 遷移下限(_bottom[対象インデックス] 配列が保持)<BR>
     * この内 ①～④を引数で設定、⑤⑥はsetRange()の設定値が使用される。<BR>
     * @param prm_idx 対象インデックス
     * @param prm_cycle_frames 上図で①のフレーム数
     * @param prm_attack_frames 上図で②のフレーム数
     * @param prm_sustain_frames 上図で③のフレーム数
     * @param prm_release_frames 上図で④のフレーム数
     * @param prm_beat_num ループ数(-1で無限)
     */
    virtual void beat(int prm_idx,
                      frame prm_cycle_frames,
                      frame prm_attack_frames,
                      frame prm_sustain_frames,
                      frame prm_release_frames,
                      double prm_beat_num) {
        Parameter* p = &_parameter[prm_idx];
        p->_method = BEAT_TRIANGLEWAVE;
        p->_beat_frame_count = 0;
        p->_beat_frame_count_in_roop = 0;
        p->_beat_frame_of_attack_finish = prm_attack_frames;
        p->_beat_frame_of_sustain_finish = p->_beat_frame_of_attack_finish + prm_sustain_frames;
        p->_beat_frame_of_release_finish = p->_beat_frame_of_sustain_finish + prm_release_frames;
        p->_beat_cycle_frames = prm_cycle_frames; //同じ
        if (prm_beat_num < 0) {
            p->_beat_target_frames = MAX_FRAME;
        } else {
            p->_beat_target_frames = (frame)(p->_beat_cycle_frames * prm_beat_num);
        }
        //最初のアタックまでの速度
        const VAL_TYPE val = getValue(prm_idx);
        if (p->_beat_frame_of_attack_finish > 0 ) {
            p->_velo = (VAL_TYPE)( ((double)(p->_top - val)) / ((double)(p->_beat_frame_of_attack_finish)) );
        } else if (p->_beat_frame_of_attack_finish == 0 ) {
            p->_velo = p->_top - val;
        }
    }



    /**
     * 台形波の波形で値を遷移する。（全対象インデックス指定）.
     * <PRE>
     * ⑤  ＿＿ _ _ _ _ _ _ _ _ _ _ _  ＿＿＿ _ _ _ _ _ _ _ _ _ _ _  ＿＿＿
     *        :＼                     /:    :＼                     /:
     *        :  ＼                  / :    :  ＼                  / :
     *        :    ＼               /  :    :    ＼               /  :
     *        :      ＼            /   :    :      ＼            /   :
     *        :        ＼         /    :    :        ＼         /    :
     * ⑥  _ _:_ _ _ _ _ ＼＿＿＿/  _ _:_ _ :_ _ _ _ _ ＼＿＿＿/  _ _:_ _
     *         ←──①──────────→
     *         ←──②─→←③→←②→
     * </PRE>
     * ＜必要な設定値＞<BR>
     * ① １周期(変化して元に戻るまで)に費やすフレーム数<BR>
     * ② アタック(減衰)までのフレーム数<BR>
     * ③ 下限維持フレーム数<BR>
     * ④ 復帰フレーム数<BR>
     * ⑤ 遷移上限(_top[対象インデックス] 配列が保持)<BR>
     * ⑥ 遷移下限(_bottom[対象インデックス] 配列が保持)<BR>
     * この内 ①～④を引数で設定、⑤⑥はsetRange()の設定値が使用される。<BR>
     * @param prm_cycle_frames 上図で①のフレーム数
     * @param prm_attack_frames 上図で②のフレーム数
     * @param prm_sustain_frames 上図で③のフレーム数
     * @param prm_release_frames 上図で④のフレーム数
     * @param prm_beat_num ループ数(-1で無限)
     */
    virtual void rbeat(frame prm_cycle_frames,
                       frame prm_attack_frames,
                       frame prm_sustain_frames,
                       frame prm_release_frames,
                       double prm_beat_num) {
        for (int i = 0; i < N; i++) {
            rbeat(i, prm_cycle_frames, prm_attack_frames, prm_sustain_frames, prm_release_frames, prm_beat_num);
        }
    }


    /**
     * 台形波の波形で値を遷移する。（対象インデックス別指定）.
     * <PRE>
     * ⑤  ＿＿ _ _ _ _ _ _ _ _ _ _ _  ＿＿＿ _ _ _ _ _ _ _ _ _ _ _  ＿＿＿
     *        :＼                     /:    :＼                     /:
     *        :  ＼                  / :    :  ＼                  / :
     *        :    ＼               /  :    :    ＼               /  :
     *        :      ＼            /   :    :      ＼            /   :
     *        :        ＼         /    :    :        ＼         /    :
     * ⑥  _ _:_ _ _ _ _ ＼＿＿＿/  _ _:_ _ :_ _ _ _ _ ＼＿＿＿/  _ _:_ _
     *         ←──①──────────→
     *         ←──②─→←③→←②→
     * </PRE>
     * ＜必要な設定値＞<BR>
     * ① １周期(変化して元に戻るまで)に費やすフレーム数<BR>
     * ② アタック(減衰)までのフレーム数<BR>
     * ③ 下限維持フレーム数<BR>
     * ④ 復帰フレーム数<BR>
     * ⑤ 遷移上限(_top[対象インデックス] 配列が保持)<BR>
     * ⑥ 遷移下限(_bottom[対象インデックス] 配列が保持)<BR>
     * この内 ①～④を引数で設定、⑤⑥はsetRange()の設定値が使用される。<BR>
     * @param prm_idx 対象インデックス
     * @param prm_cycle_frames 上図で①のフレーム数
     * @param prm_attack_frames 上図で②のフレーム数
     * @param prm_sustain_frames 上図で③のフレーム数
     * @param prm_release_frames 上図で④のフレーム数
     * @param prm_beat_num ループ数(-1で無限)
     */
    virtual void rbeat(int prm_idx,
                       frame prm_cycle_frames,
                       frame prm_attack_frames,
                       frame prm_sustain_frames,
                       frame prm_release_frames,
                       double prm_beat_num) {
        Parameter* p = &_parameter[prm_idx];
        p->_method = R_BEAT_TRIANGLEWAVE;
        p->_beat_frame_count = 0;
        p->_beat_frame_count_in_roop = 0;
        p->_beat_frame_of_attack_finish = prm_attack_frames;
        p->_beat_frame_of_sustain_finish = p->_beat_frame_of_attack_finish + prm_sustain_frames;
        p->_beat_frame_of_release_finish = p->_beat_frame_of_sustain_finish + prm_release_frames;
        p->_beat_cycle_frames = prm_cycle_frames; //同じ
        if (prm_beat_num < 0) {
            p->_beat_target_frames = MAX_FRAME;
        } else {
            p->_beat_target_frames = (frame)(p->_beat_cycle_frames * prm_beat_num);
        }
        //最初のアタックまでの速度
        const VAL_TYPE val = getValue(prm_idx);
        if (p->_beat_frame_of_attack_finish > 0 ) {
            p->_velo = (VAL_TYPE)( ((double)(p->_bottom - val)) / ((double)(p->_beat_frame_of_attack_finish)) );
        } else if (p->_beat_frame_of_attack_finish == 0 ) {
            p->_velo = p->_bottom - val;
        }
    }

    /**
     * 値遷移中かどうか調べる .
     * @param prm_idx 対象インデックス
     * @return true/false
     */
    virtual bool isTransitioning(int prm_idx) const {
        if (_parameter[prm_idx]._method == NO_TRANSITION) {
            return false;
        } else {
            return true;
        }
    }

    /**
     * 値遷移中かどうか調べる .
     * @return true/false
     */
    virtual bool isTransitioning() const {
        for (int i = 0; i < N; i++) {
            if (isTransitioning(i)) {
                return true;
            }
        }
        return false;
    }

    virtual void reset() {
        Parameter* p = _parameter;
        for (int i = 0; i < N; i++) {
            p->_velo = 0;
            p->_acce = 0;
            p->_target = 0;
            p->_top = 0;
            p->_bottom = 1;
            p->_beat_frame_of_attack_finish = 0;
            p->_beat_frame_of_sustain_finish = 0;
            p->_beat_frame_of_release_finish = 0;
            p->_beat_cycle_frames = 0;
            p->_beat_target_frames = 0;
            p->_beat_frame_count_in_roop = 0;
            p->_beat_frame_count = 0;
            p->_method = NO_TRANSITION;
            ++p;
        }
    }

    /**
     * 毎フレームの振る舞いメソッド。<BR>
     * 本クラスの機能を利用する場合は、このメソッドを<BR>
     * 毎フレーム実行することが必要。
     * @param s 適用開始インデックス
     * @param n 適用インデックス数
     */
    virtual void behave(int s = 0, int n = N) {
        Parameter* p = &_parameter[s];
        for (int i = s; i < s+n; i++) {
            const TransitionMethod method = p->_method;
            VAL_TYPE val = getValue(i);
            const VAL_TYPE top = p->_top;
            const VAL_TYPE bottom = p->_bottom;
            p->_beat_frame_count++;
            p->_velo += p->_acce;
            val += p->_velo;

            switch (method) {
                case NO_TRANSITION: {
                    //何もしない
                    break;
                }
                case TARGET_LINEAR_UNTIL: {
                    if (p->_beat_frame_count >= p->_beat_target_frames) {
                        val = p->_target;
                        stop(i);//終了
                    }
                    break;
                }
                case TARGET_LINEAR_STEP: {
                    if ((p->_velo > 0  && val >= p->_target) || (p->_velo < 0  && val <= p->_target)) {
                        val = p->_target;
                        stop(i);//終了
                    }
                    break;
                }
                case TARGET_ACCELERATION_UNTIL: {
                    if ((p->_velo > 0  && val >= p->_target) || (p->_velo < 0  && val <= p->_target)) {
                        val = p->_target;
                        stop(i);//終了
                    }
                    break;
                }
                case TARGET_ACCELERATION_UNTIL_VELO: {
                    if ((p->_acce > 0  && p->_velo >= p->_target) || (p->_acce < 0  && p->_velo <= p->_target)) {
                       //加速度が正の場合、速度がターゲット速度より大きくなれば終了
                       //加速度が負の場合、速度がターゲット速度より小さくなれば終了
                       val -= p->_velo;
                       p->_velo = p->_target;
                       val += p->_velo;
                       stop(i);//終了
                    }
                    break;
                }
                case BEAT_LINEAR: {
                    p->_beat_frame_count_in_roop++;
                    const frame cnt = p->_beat_frame_count_in_roop;
                    const frame beat_cycle_frames = p->_beat_cycle_frames;
                    if (cnt == beat_cycle_frames/2) {
                        //折り返し
                        if (p->_velo > 0) { //山
                            val = top;
                            p->_velo = (VAL_TYPE)( (2.0*(bottom-top)) / ((double)beat_cycle_frames) ); //下りの速度
                        } else if (p->_velo < 0) { //谷
                            val = bottom;
                            p->_velo = (VAL_TYPE)( (2.0*(top-bottom)) / ((double)beat_cycle_frames) ); //上りの速度
                        }
                    }
                    if (cnt == beat_cycle_frames) {
                        //１ループ終了
                        if (p->_velo > 0) { //山
                            val = top;
                            p->_velo = (VAL_TYPE)( (2.0*(bottom-top)) / ((double)beat_cycle_frames) ); //下りの速度
                        } else if (p->_velo < 0) { //谷
                            val = bottom;
                            p->_velo = (VAL_TYPE)( (2.0*(top-bottom)) / ((double)beat_cycle_frames) ); //上りの速度
                        }
                        p->_beat_frame_count_in_roop = 0;
                    }
                    break;
                }
                case BEAT_TRIANGLEWAVE: {
                    p->_beat_frame_count_in_roop++;
                    const frame cnt = p->_beat_frame_count_in_roop;
                    const frame beat_frame_of_attack_finish = p->_beat_frame_of_attack_finish;
                    //アタック終了時
                    if (cnt == beat_frame_of_attack_finish) {
                        val = top;
                        p->_velo = 0;
                    }
                    //維持終時
                    if (cnt == p->_beat_frame_of_sustain_finish) {
                        val = top;
                        int attenuate_frames = (int)p->_beat_frame_of_release_finish - (int)p->_beat_frame_of_sustain_finish; //減衰(余韻)時間
                        //下限までの減衰(余韻)速度設定
                        if (attenuate_frames > 0)  {
                            p->_velo = (VAL_TYPE)( (double)(bottom-top) / ((double)attenuate_frames) );
                        } else {
                            p->_velo = bottom-top;
                        }
                    }
                    //減衰(余韻)終了
                    if (cnt == p->_beat_frame_of_release_finish) {
                        val = bottom;
                        p->_velo = 0;
                    }
                    //休憩終了
                    if (cnt == p->_beat_cycle_frames) {
                        val = bottom;
                        p->_beat_frame_count_in_roop = 0;
                        //次のアタックへの速度設定
                        if (beat_frame_of_attack_finish > 0 ) {
                            p->_velo = (VAL_TYPE)( ((double)(top - val)) / ((double)beat_frame_of_attack_finish) );
                        } else if (beat_frame_of_attack_finish == 0 ) {
                            p->_velo = top - val;
                        }
                    }
                    break;
                }
                case R_BEAT_TRIANGLEWAVE: {
                    p->_beat_frame_count_in_roop++;
                    const frame cnt = p->_beat_frame_count_in_roop;
                    const frame beat_frame_of_attack_finish = p->_beat_frame_of_attack_finish;
                    //アタック終了時
                    if (cnt == beat_frame_of_attack_finish) {
                        val = bottom;
                        p->_velo = 0;
                    }
                    //維持(下限)終時
                    if (cnt == p->_beat_frame_of_sustain_finish) {
                        val = bottom;
                        int attenuate_frames = (int)p->_beat_frame_of_release_finish - (int)p->_beat_frame_of_sustain_finish; //復帰時間
                        //上限までの復帰速度設定
                        if (attenuate_frames > 0)  {
                            p->_velo = (VAL_TYPE)( (double)(top - bottom) / ((double)attenuate_frames) );
                        } else {
                            p->_velo = top - bottom;
                        }
                    }
                    //復帰終了
                    if (cnt == p->_beat_frame_of_release_finish) {
                        val = top;
                        p->_velo = 0;
                    }
                    //休憩終了
                    if (cnt == p->_beat_cycle_frames) {
                        val = top;
                        p->_beat_frame_count_in_roop = 0;
                        //次のアタックへの速度設定
                        if (beat_frame_of_attack_finish > 0 ) {
                            p->_velo = (VAL_TYPE)( ((double)(bottom - val)) / ((double)beat_frame_of_attack_finish) );
                        } else if (beat_frame_of_attack_finish == 0 ) {
                            p->_velo = bottom - val;
                        }
                    }
                    break;
                }

                default:
                    break;
            }

            if (top < val) {
                val = top;
            } else if (bottom > val) {
                val = bottom;
            }

            setValue(i, val); //反映

            if (p->_beat_frame_count >= p->_beat_target_frames) {
                stop(i);//終了
            }

            ++p;
        }
    }

    virtual ~ValueTransitioner() {
    }
};

}

#endif /*GGAF_CORE_TRANSITIONVALUESET_H_*/

