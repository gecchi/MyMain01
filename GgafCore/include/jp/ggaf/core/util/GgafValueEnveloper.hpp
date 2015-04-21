#ifndef GGAFCORE_GGAFVALUEENVELOPER_H_
#define GGAFCORE_GGAFVALUEENVELOPER_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include "jp/ggaf/core/util/GgafUtil.h"

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
class GgafValueEnveloper : public GgafObject {
    enum TransitionMethod {
        NO_TRANSITION,
        TARGET_LINER_TO,
        TARGET_LINER_STEP,
        BEAT_LINER,
        BEAT_TRIANGLEWAVE,
        BEAT_TRIGONOMETRIC,
        TARGET_ACCELERATION_STEP,
    };
public:
    /** [r/w]各対象インデックスの目標の遷移 */
    VAL_TYPE _target[N];
    /** [r/w]各対象インデックスの遷移上限 */
    VAL_TYPE _top[N];
    /** [r/w]各対象インデックスの遷移下限 */
    VAL_TYPE _bottom[N];
    /** [r/w]各対象インデックスの毎フレームの遷移の増分 */
    VAL_TYPE _velo[N];
    /** [r/w]各対象インデックスの毎フレームの遷移の増分の増分 */
    VAL_TYPE _acce[N];
    /** [r]各対象インデックスの値遷移方法 */
    TransitionMethod _method[N];
    /** [r]ビート時、各対象インデックスの台形波の波形での値遷移のアタックフレーム数 */
    frame _beat_frame_of_attack_finish[N];
    /** [r]ビート時、各対象インデックスの台形波の波形での値遷移の維持フレーム数 */
    frame _beat_frame_of_sustain_finish[N];
    /** [r]ビート時、各対象インデックスの台形波の波形での減衰(余韻)フレーム数 */
    frame _beat_frame_of_release_finish[N];
    /** [r]ビート時、各対象インデックスの台形波の波形での１周期のフレーム数 */
    frame _beat_cycle_frames[N];
    /** [r]ビート時、各対象インデックスの値遷移に費やすフレーム数 */
    frame _beat_target_frames[N];
    /** [r]ビート時、内部カウンター */
    frame _beat_frame_count_in_roop[N];
    /** [r]ビート時、内部カウンター */
    frame _beat_frame_count[N];

protected:
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
    GgafValueEnveloper() : GgafObject() {
        for (int i = 0; i < N; i++) {
            _velo[i] = 0;
            _acce[i] = 0;
            _target[i] = 0;
            _top[i] = 0;
            _bottom[i] = 0;
            _beat_frame_of_attack_finish[i] = 0;
            _beat_frame_of_sustain_finish[i] = 0;
            _beat_frame_of_release_finish[i] = 0;
            _beat_cycle_frames[i] = 0;
            _beat_target_frames[i] = 0;
            _beat_frame_count_in_roop[i] = 0;
            _beat_frame_count[i] = 0;
            _method[i] = NO_TRANSITION;
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
        _top[prm_idx] = prm_top;
    }

    /**
     * 下限値を設定（対象インデックス単位で指定） .
     * @param prm_bottom 下限値
     */
    virtual void setBottom(int prm_idx, VAL_TYPE prm_bottom) {
        _bottom[prm_idx] = prm_bottom;
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
        return _top[prm_idx];
    }

    /**
     * 値遷移の下限値を取得 .
     * @param prm_idx 対象インデックス
     * @return
     */
    virtual VAL_TYPE getBottom(int prm_idx) const {
        return _bottom[prm_idx];
    }

    /**
     * 値遷移の上限値を取得 .
     * 対象インデックスが２以上の場合、全上限値の中で最小を返す。
     * @return 上限値
     */
    virtual VAL_TYPE getTop() const {
        //_topの最小値を返す
        VAL_TYPE minv = _top[0];
        for (int i = 1; i < N; i++) {
            if (minv > _top[i]) {
                minv = _top[i];
            }
        }
        return minv;
    }

    /**
     * 値遷移の下限値を取得 .
     * 対象インデックスが２以上の場合、全下限値の中で最大を返す。
     * @return 上限値
     */
    virtual VAL_TYPE getBottom() const {
        //_bottomの最大値を返す
        VAL_TYPE maxv = _bottom[0];
        for (int i = 1; i < N; i++) {
            if (maxv > _bottom[i]) {
                maxv = _bottom[i];
            }
        }
        return maxv;
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
        _velo[prm_idx] = 0;
        _acce[prm_idx] = 0;
        _method[prm_idx] = NO_TRANSITION;
    }

    /**
     * 片道等速値遷移（全対象インデックス・持続フレーム数指定） .
     * 目標の遷移へ一定速度で値遷移する
     * @param prm_target_T 遷移目標値
     * @param prm_spend_frame 費やすフレーム数
     */
    virtual void transitionLinerUntil(VAL_TYPE prm_target, frame prm_spend_frame) {
        for (int i = 0; i < N; i++) {
            transitionLinerUntil(i, prm_target, prm_spend_frame);
        }
    }

    /**
     * 片道等速値遷移（対象インデックス単位・持続フレーム数指定） .
     * 目標の遷移へ一定速度で値遷移する。
     * @param prm_idx 対象インデックス
     * @param prm_target_T 遷移目標値
     * @param prm_spend_frame 費やすフレーム数
     */
    virtual void transitionLinerUntil(int prm_idx, VAL_TYPE prm_target, frame prm_spend_frame) {
        _beat_frame_count[prm_idx] = 0;
        _beat_target_frames[prm_idx] = prm_spend_frame;
        _target[prm_idx] = prm_target;
        _method[prm_idx] = TARGET_LINER_TO;
        //最初のアタックまでの速度
        const VAL_TYPE val = getValue(prm_idx);
        if (_beat_target_frames[prm_idx] > 0 ) {
            _velo[prm_idx] = (VAL_TYPE)( ((double)(_target[prm_idx] - val)) / ((double)(_beat_target_frames[prm_idx])) );
        } else if (_beat_target_frames[prm_idx] == 0 ) {
            _velo[prm_idx] = _target[prm_idx] - val;
        }
    }

    /**
     * 上限遷移へ片道等速値遷移（全対象インデックス・持続フレーム数指定） .
     * @param prm_spend_frame 費やすフレーム数
     */
    virtual void transitionLinerToTop(frame prm_spend_frame) {
        transitionLinerUntil(getTop(), prm_spend_frame);
    }

    /**
     * 下限遷移へ片道等速値遷移（全対象インデックス・持続フレーム数指定） .
     * @param prm_spend_frame 費やすフレーム数
     */
    virtual void transitionLinerToBottom(frame prm_spend_frame) {
        transitionLinerUntil(getBottom(), prm_spend_frame);
    }

    /**
     * 片道等速値遷移（全対象インデックス・遷移速度指定） .
     * 目標の遷移へ一定速度で値遷移する
     * @param prm_target_T 遷移目標値
     * @param prm_velo_T 毎フレーム加算する遷移差分(>0.0)。正の遷移を指定する事。加算か減算かは自動判断する。
     */
    virtual void transitionLinerStep(VAL_TYPE prm_target, VAL_TYPE prm_velo) {
        for (int i = 0; i < N; i++) {
            transitionLinerStep(i, prm_target, prm_velo);
        }
    }

    /**
     * 片道等速値遷移（対象インデックス単位・遷移速度指定） .
     * 目標の遷移へ一定速度で値遷移する（遷移差分指定） .
     * @param prm_idx 対象インデックス
     * @param prm_target_T 遷移目標値
     * @param prm_velo_T 毎フレーム加算する遷移差分(>0.0)。正の遷移を指定する事。加算か減算かは自動判断する。
     */
    virtual void transitionLinerStep(int prm_idx, VAL_TYPE prm_target, VAL_TYPE prm_velo) {
        _method[prm_idx] = TARGET_LINER_STEP;
        _velo[prm_idx] = prm_velo;
        _target[prm_idx] = prm_target;
        _beat_frame_count[prm_idx] = 0;
        _beat_target_frames[prm_idx] = MAX_FRAME;
    }

    /**
     * 片道加速値遷移（全対象インデックス・遷移速度・遷移加速度指定） .
     * 目標の遷移へ加速指定で値遷移する
     * 遷移加速度を0に指定すると transitionLinerStep とほぼ同じ意味になる。
     * transitionLinerStep の第３引数は正負を気にすること無いが、本メソッドは正負の自動判定はしない（できない）。
     * 遷移加速度が正の場合、遷移目標値を超えると値遷移終了。
     * 遷移加速度が負の場合、遷移目標値を下回ると値遷移終了。
     * @param prm_target_T 遷移目標値
     * @param prm_velo_T 初期遷移速度
     * @param prm_acce_T 遷移加速度
     */
    virtual void transitionAcceStep(VAL_TYPE prm_target, VAL_TYPE prm_velo, VAL_TYPE prm_acce) {
        for (int i = 0; i < N; i++) {
            transitionAcceStep(i, prm_target, prm_velo, prm_acce);
        }
    }

    /**
     * 片道加速値遷移（対象インデックス単位・遷移速度・遷移加速度指定） .
     * 目標の遷移へ加速指定で値遷移する（遷移速度、遷移加速度差指定） .
     * 遷移加速度を0に指定すると transitionLinerStep とほぼ同じ意味になる。
     * transitionLinerStep の第３引数は正負を気にすること無いが、本メソッドは正負の自動判定はしない（できない）。
     * @param prm_idx 対象インデックス
     * @param prm_target_T 遷移目標値
     * @param prm_velo_T 初期遷移速度
     * @param prm_acce_T 遷移加速度
     */
    virtual void transitionAcceStep(int prm_idx, VAL_TYPE prm_target, VAL_TYPE prm_velo, VAL_TYPE prm_acce) {
        _method[prm_idx] = TARGET_ACCELERATION_STEP;
        _target[prm_idx] = prm_target;
        _velo[prm_idx] = prm_velo;
        _acce[prm_idx] = prm_acce;
        _beat_frame_count[prm_idx] = 0;
        _beat_target_frames[prm_idx] = MAX_FRAME;
    }

    /**
     * 反復等速値遷移（全対象インデックス・フレーム数指定） .
     * 上限遷移へ一定速度で値遷移し、一定速度で下遷移へ戻る。これをループ指定する。（１ループのフレーム数指定） .
     * @param prm_cycle_frames １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_beat_num ループする回数(1.2回など少数で指定可能、-1 でほぼ無限ループ)
     * @param prm_is_to_top true:初めはTOPに遷移する／false:初めはBOTTOMに遷移
     */
    void transitionLinerLoop(frame prm_cycle_frames, double prm_beat_num, bool prm_is_to_top) {
        for (int i = 0; i < N; i++) {
            transitionLinerLoop(i, prm_cycle_frames, prm_beat_num, prm_is_to_top);
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
    virtual void transitionLinerLoop(int prm_idx, frame prm_cycle_frames, double prm_beat_num, bool prm_is_to_top) {
        const VAL_TYPE val = getValue(prm_idx);
        _method[prm_idx] = BEAT_LINER;
        _beat_frame_count[prm_idx] = 0;
        _beat_frame_count_in_roop[prm_idx] = 0;
        _beat_cycle_frames[prm_idx] = prm_cycle_frames;
        if (prm_beat_num < 0) {
            _beat_target_frames[prm_idx] = MAX_FRAME;
        } else {
            _beat_target_frames[prm_idx] = prm_cycle_frames * prm_beat_num;
        }
        if (prm_is_to_top) {
            _velo[prm_idx] = 1.0*(_top[prm_idx] - val) / ((int)prm_cycle_frames / 2.0);
            if (ZEROd_EQ(_velo[prm_idx])) {
                _velo[prm_idx] = 1; //正であればよい
            }
        } else {
            _velo[prm_idx] = 1.0*(_bottom[prm_idx] - val) / ((int)prm_cycle_frames / 2.0);
            if (ZEROd_EQ(_velo[prm_idx])) {
                _velo[prm_idx] = -1; //負であればよい
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
        _method[prm_idx] = BEAT_TRIANGLEWAVE;
        _beat_frame_count[prm_idx] = 0;
        _beat_frame_count_in_roop[prm_idx] = 0;
        _beat_frame_of_attack_finish[prm_idx] = prm_attack_frames;
        _beat_frame_of_sustain_finish[prm_idx] = _beat_frame_of_attack_finish[prm_idx] + prm_sustain_frames;
        _beat_frame_of_release_finish[prm_idx] = _beat_frame_of_sustain_finish[prm_idx] + prm_release_frames;
        _beat_cycle_frames[prm_idx] = prm_cycle_frames; //同じ
        if (prm_beat_num < 0) {
            _beat_target_frames[prm_idx] = MAX_FRAME;
        } else {
            _beat_target_frames[prm_idx] = _beat_cycle_frames[prm_idx] * prm_beat_num;
        }
        //最初のアタックまでの速度
        const VAL_TYPE val = getValue(prm_idx);
        if (_beat_frame_of_attack_finish[prm_idx] > 0 ) {
            _velo[prm_idx] = (VAL_TYPE)( ((double)(_top[prm_idx] - val)) / ((double)(_beat_frame_of_attack_finish[prm_idx])) );
        } else if (_beat_frame_of_attack_finish[prm_idx] == 0 ) {
            _velo[prm_idx] = _top[prm_idx] - val;
        }
    }

    /**
     * 値遷移中かどうか調べる .
     * @param prm_idx 対象インデックス
     * @return true/false
     */
    virtual bool isTransitioning(int prm_idx) const {
        if (_method[prm_idx] == NO_TRANSITION) {
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
        for (int i = 0; i < N; i++) {
            _velo[i] = 0;
            _acce[i] = 0;
            _target[i] = 0;
            _top[i] = 0;
            _bottom[i] = 1;
            _beat_frame_of_attack_finish[i] = 0;
            _beat_frame_of_sustain_finish[i] = 0;
            _beat_frame_of_release_finish[i] = 0;
            _beat_cycle_frames[i] = 0;
            _beat_target_frames[i] = 0;
            _beat_frame_count_in_roop[i] = 0;
            _beat_frame_count[i] = 0;
            _method[i] = NO_TRANSITION;
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

        for (int i = s; i < s+n; i++) {
            const TransitionMethod method = _method[i];
            VAL_TYPE val = getValue(i);
            const VAL_TYPE top = _top[i];
            const VAL_TYPE bottom = _bottom[i];
            _beat_frame_count[i]++;
            _velo[i] += _acce[i];
            val += _velo[i];

            if (method == NO_TRANSITION) {
                //何もしない
            } else {
                if (method == TARGET_LINER_TO) {
                    if (_beat_frame_count[i] == _beat_target_frames[i]) {
                        val = _target[i];
                        stop(i);//終了
                    }
                } else if (method == TARGET_LINER_STEP || method == TARGET_ACCELERATION_STEP) {
                    if ((_velo[i] > 0  && val >= _target[i]) || (_velo[i] < 0  && val <= _target[i])) {
                        val = _target[i];
                        stop(i);//終了
                    }
                } else if (method == BEAT_LINER) {
                    _beat_frame_count_in_roop[i]++;
                    frame cnt = _beat_frame_count_in_roop[i];
                    if (cnt == _beat_cycle_frames[i]/2) {
                        //折り返し
                        if (_velo[i] > 0) { //山
                            val = top;
                            _velo[i] = (VAL_TYPE)( (2.0*(bottom-top)) / ((double)_beat_cycle_frames[i]) ); //下りの速度
                        } else if (_velo[i] < 0) { //谷
                            val = bottom;
                            _velo[i] = (VAL_TYPE)( (2.0*(top-bottom)) / ((double)_beat_cycle_frames[i]) ); //上りの速度
                        }
                    }
                    if (cnt == _beat_cycle_frames[i]) {
                        //１ループ終了
                        if (_velo[i] > 0) { //山
                            val = top;
                            _velo[i] = (VAL_TYPE)( (2.0*(bottom-top)) / ((double)_beat_cycle_frames[i]) ); //下りの速度
                        } else if (_velo[i] < 0) { //谷
                            val = bottom;
                            _velo[i] = (VAL_TYPE)( (2.0*(top-bottom)) / ((double)_beat_cycle_frames[i]) ); //上りの速度
                        }
                        _beat_frame_count_in_roop[i] = 0;
                    }
                } else if (method == BEAT_TRIANGLEWAVE) {
                    _beat_frame_count_in_roop[i]++;
                    frame cnt = _beat_frame_count_in_roop[i];
                    //アタック終了時
                    if (cnt == _beat_frame_of_attack_finish[i]) {
                        val = top;
                        _velo[i] = 0;
                    }
                    //維持終時
                    if (cnt == _beat_frame_of_sustain_finish[i]) {
                        val = top;
                        frame attenuate_frames = _beat_frame_of_release_finish[i] - _beat_frame_of_sustain_finish[i]; //減衰(余韻)時間
                        //下限までの減衰(余韻)速度設定
                        if (attenuate_frames > 0)  {
                            _velo[i] = (VAL_TYPE)( (double)(bottom-top) / ((double)attenuate_frames) );
                        } else {
                            _velo[i] = bottom-top;
                        }
                    }
                    //減衰(余韻)終了
                    if (cnt == _beat_frame_of_release_finish[i]) {
                        val = bottom;
                        _velo[i] = 0;
                    }
                    //休憩終了
                    if (cnt == _beat_cycle_frames[i]) {
                        val = bottom;
                        _beat_frame_count_in_roop[i] = 0;
                        //次のアタックへの速度設定
                        if (_beat_frame_of_attack_finish[i] > 0 ) {
                            _velo[i] = (VAL_TYPE)( ((double)(top - val)) / ((double)_beat_frame_of_attack_finish[i]) );
                        } else if (_beat_frame_of_attack_finish[i] == 0 ) {
                            _velo[i] = 0;
                            val = top;
                        }
                    }
                }
            }

            if (top < val) {
                val = top;
            } else if (bottom >  val) {
                val =  bottom;
            }

            setValue(i, val); //反映

            if (_beat_frame_count[i] == _beat_target_frames[i]) {
                stop(i);//終了
            }
        }
    }

    virtual ~GgafValueEnveloper() {
    }
};


}
#endif /*GGAFCORE_GGAFVALUEENVELOPER_H_*/

