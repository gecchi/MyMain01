#ifndef GGAFCORE_GGAFVALUETRANSITIONER_H_
#define GGAFCORE_GGAFVALUETRANSITIONER_H_
#include "jp/ggaf/core/GgafObject.h"
#include "jp/ggaf/core/util/GgafUtil.h"
#include "GgafCommonHeader.h"

namespace GgafCore {

/**
 * 値の遷移ヘルパー .
 * @version 1.00
 * @since 2014/02/19
 * @author Masatoshi Tsuge
 */
template <class VAL_TYPE, int N>
class GgafValueTransitioner : public GgafObject {
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
    /** [r/w]各軸の目標の遷移 */
    VAL_TYPE _target[N];
    /** [r/w]各軸の遷移上限 */
    VAL_TYPE _top[N];
    /** [r/w]各軸の遷移下限 */
    VAL_TYPE _bottom[N];
    /** [r/w]各軸の毎フレームの遷移の増分 */
    VAL_TYPE _velo[N];
    /** [r/w]各軸の毎フレームの遷移の増分の増分 */
    VAL_TYPE _acce[N];
    /** [r]各軸の値遷移方法 */
    TransitionMethod _method[N];
    /** [r]ビート時、各軸の三角波の波形で値遷移のアタックフレーム数 */
    frame _beat_frame_of_attack_finish[N];
    frame _beat_frame_of_sustain_finish[N];
    /** [r]ビート時、各軸のアタックから下限までのフレーム数 */
    frame _beat_frame_of_attenuate_finish[N];
    /** [r]ビート時、各軸の三角波の波形で値遷移のレストフレーム数 */
    frame _beat_roop_frames[N];
    /** [r]ビート時、各軸の値遷移に費やすフレーム数 */
    frame _beat_target_frames[N];
    /** [r]ビート時、内部カウンター */
    frame _beat_frame_count_in_roop[N];
    /** [r]ビート時、内部カウンター */
    frame _beat_frame_count[N];

protected:
    /**
     * 値を取得する（要実装） .
     * @param idx
     * @return
     */
    virtual VAL_TYPE getValue(int idx) = 0;

    /**
     * 値を設定する（要実装） .
     * @param idx
     * @param value
     */
    virtual void setValue(int idx, VAL_TYPE value) = 0;

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用対象のActor
     */
    GgafValueTransitioner() : GgafObject() {
        for (int i = 0; i < N; i++) {
            _velo[i] = 0;
            _acce[i] = 0;
            _target[i] = 0;
            _top[i] = 0;
            _bottom[i] = 0;
            _beat_frame_of_attack_finish[i] = 0;
            _beat_frame_of_sustain_finish[i] = 0;
            _beat_frame_of_attenuate_finish[i] = 0;
            _beat_roop_frames[i] = 0;
            _beat_target_frames[i] = 0;
            _beat_frame_count_in_roop[i] = 0;
            _beat_frame_count[i] = 0;
            _method[i] = NO_TRANSITION;
        }
    }

    /**
     * スケーラーによる遷移の上限下限を設定（全軸指定） .
     * 引数の大小は気にせず渡して(内部で自動判別)
     * @param prm1 遷移値1
     * @param prm2 遷移値2
     */
    void forceRange(VAL_TYPE prm1, VAL_TYPE prm2) {
        for (int i = 0; i < N; i++) {
            forceRange(i, prm1, prm2);
        }
    }

    /**
     * スケーラーによる遷移の上限下限を設定（軸単位で指定）
     * @param prm_idx 軸
     * @param prm1 遷移値1
     * @param prm2 遷移値2
     */
    void forceRange(int prm_idx, VAL_TYPE prm1, VAL_TYPE prm2) {
        if (prm1 < prm2) {
            _bottom[prm_idx] = prm1;
            _top[prm_idx] = prm2;
        } else {
            _bottom[prm_idx] = prm2;
            _top[prm_idx] = prm1;
        }
    }

    virtual VAL_TYPE getTop(int prm_idx)  {
        return _top[prm_idx];
    }
    virtual VAL_TYPE getBottom(int prm_idx)  {
        return _bottom[prm_idx];
    }

    virtual VAL_TYPE getTop() {
        return MIN3(_top[0], _top[1], _top[2]);
    }
    virtual VAL_TYPE getBottom() {
        return MAX3(_bottom[0],_bottom[1],_bottom[2]);
    }
    /**
     * 値遷移を停止させる。 （全軸指定） .
     */
    virtual void stop() {
        for (int i = 0; i < N; i++) {
            stop(i);
        }
    }

    /**
     * 値遷移を停止させる。 （軸単位で指定）.
     * @param prm_idx
     */
    virtual void stop(int prm_idx) {
        _velo[prm_idx] = 0;
        _acce[prm_idx] = 0;
        _method[prm_idx] = NO_TRANSITION;
    }

    /**
     * 片道等速値遷移（全軸・持続フレーム数指定） .
     * 目標の遷移へ一定速度で値遷移する
     * @param prm_target_T 目標遷移
     * @param prm_spend_frame 費やすフレーム数
     */
    virtual void transitionLinerUntil(VAL_TYPE prm_target, frame prm_spend_frame) {
        for (int i = 0; i < N; i++) {
            transitionLinerUntil(i, prm_target, prm_spend_frame);
        }
    }

    /**
     * 片道等速値遷移（軸単位・持続フレーム数指定） .
     * 目標の遷移へ一定速度で値遷移する。
     * @param prm_idx 軸
     * @param prm_target_T 目標遷移
     * @param prm_spend_frame 費やすフレーム数
     */
    virtual void transitionLinerUntil(int prm_idx, VAL_TYPE prm_target, frame prm_spend_frame) {
        _beat_frame_count[prm_idx] = 0;
        _beat_target_frames[prm_idx] = prm_spend_frame;
        _target[prm_idx] = prm_target;
        _method[prm_idx] = TARGET_LINER_TO;
        //最初のアタックまでの速度
        VAL_TYPE val = getValue(prm_idx);
        if (_beat_target_frames[prm_idx] > 0 ) {
            _velo[prm_idx] = (VAL_TYPE)( ((double)(_target[prm_idx] - val)) / ((double)(_beat_target_frames[prm_idx])) );
        } else if (_beat_target_frames[prm_idx] == 0 ) {
            _velo[prm_idx] = _target[prm_idx] - val;
        }
    }

    /**
     * 上限遷移へ片道等速値遷移（全軸・持続フレーム数指定） .
     * @param prm_spend_frame 費やすフレーム数
     */
    virtual void transitionLinerToTop(frame prm_spend_frame) {
        transitionLinerUntil(MIN3(_top[0],_top[1],_top[2]), prm_spend_frame);
    }

    /**
     * 下限遷移へ片道等速値遷移（全軸・持続フレーム数指定） .
     * @param prm_spend_frame 費やすフレーム数
     */
    virtual void transitionLinerToBottom(frame prm_spend_frame) {
        transitionLinerUntil(MAX3(_bottom[0],_bottom[1],_bottom[2]), prm_spend_frame);
    }


    /**
     * 片道等速値遷移（全軸・遷移速度指定） .
     * 目標の遷移へ一定速度で値遷移する
     * @param prm_target_T 目標遷移
     * @param prm_velo_T 毎フレーム加算する遷移差分(>0.0)。正の遷移を指定する事。加算か減算かは自動判断する。
     */
    virtual void transitionLinerStep(VAL_TYPE prm_target, VAL_TYPE prm_velo) {
        for (int i = 0; i < N; i++) {
            transitionLinerStep(i, prm_target, prm_velo);
        }
    }

    /**
     * 片道等速値遷移（軸単位・遷移速度指定） .
     * 目標の遷移へ一定速度で値遷移する（遷移差分指定） .
     * @param prm_idx 軸
     * @param prm_target_T 目標遷移
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
     * 片道加速値遷移（全軸・遷移速度・遷移加速度指定） .
     * 目標の遷移へ加速指定で値遷移する
     * 遷移加速度を0に指定すると transitionLinerStep とほぼ同じ意味になる。
     * transitionLinerStep の第３引数は正負を気にすること無いが、本メソッドは正負の自動判定はしない（できない）。
     * 遷移加速度が正の場合、目標遷移を超えると値遷移終了。
     * 遷移加速度が負の場合、目標遷移を下回ると値遷移終了。
     * @param prm_target_T 目標遷移
     * @param prm_velo_T 初期遷移速度
     * @param prm_acce_T 遷移加速度
     */
    virtual void transitionAcceStep(VAL_TYPE prm_target, VAL_TYPE prm_velo, VAL_TYPE prm_acce) {
        for (int i = 0; i < N; i++) {
            transitionAcceStep(i, prm_target, prm_velo, prm_acce);
        }
    }

    /**
     * 片道加速値遷移（軸単位・遷移速度・遷移加速度指定） .
     * 目標の遷移へ加速指定で値遷移する（遷移速度、遷移加速度差指定） .
     * 遷移加速度を0に指定すると transitionLinerStep とほぼ同じ意味になる。
     * transitionLinerStep の第３引数は正負を気にすること無いが、本メソッドは正負の自動判定はしない（できない）。
     * @param prm_idx 軸
     * @param prm_target_T 目標遷移
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
     * 反復等速値遷移（全軸・フレーム数指定） .
     * 上限遷移へ一定速度で値遷移し、一定速度で下遷移へ戻る。これをループ指定する。（１ループのフレーム数指定） .
     * @param prm_roop_frames １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_beat_num ループする回数(1.2回など少数で指定可能、-1 でほぼ無限ループ)
     * @param prm_is_to_top true:初めはTOPに遷移する／false:初めはBOTTOMに遷移
     */
    void transitionLinerLoop(frame prm_roop_frames, double prm_beat_num, bool prm_is_to_top) {
        for (int i = 0; i < N; i++) {
            transitionLinerLoop(i, prm_roop_frames, prm_beat_num, prm_is_to_top);
        }
    }

    /**
     * 反復等速値遷移（軸単位・フレーム数指定）
     * 上限遷移へ一定速度で値遷移し、一定速度で下遷移へ戻る。
     * これをループ指定する。（１ループのフレーム数指定） .
     * @param prm_idx 軸
     * @param prm_roop_frames １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_beat_num ループする回数(1.2回など少数で指定可能、-1 でほぼ無限ループ)
     * @param prm_is_to_top true:初めはTOPに遷移する／false:初めはBOTTOMに遷移
     */
    virtual void transitionLinerLoop(int prm_idx, frame prm_roop_frames, double prm_beat_num, bool prm_is_to_top) {
        VAL_TYPE val = getValue(prm_idx);
        _method[prm_idx] = BEAT_LINER;
        _beat_frame_count[prm_idx] = 0;
        _beat_frame_count_in_roop[prm_idx] = 0;
        _beat_roop_frames[prm_idx] = prm_roop_frames;
        if (prm_beat_num < 0) {
            _beat_target_frames[prm_idx] = MAX_FRAME;
        } else {
            _beat_target_frames[prm_idx] = prm_roop_frames * prm_beat_num;
        }
        if (prm_is_to_top) {
            _velo[prm_idx] = 1.0*(_top[prm_idx] - val) / ((int)prm_roop_frames / 2.0);
            if (ZEROd_EQ(_velo[prm_idx])) {
                _velo[prm_idx] = 1; //正であればよい
            }
        } else {
            _velo[prm_idx] = 1.0*(_bottom[prm_idx] - val) / ((int)prm_roop_frames / 2.0);
            if (ZEROd_EQ(_velo[prm_idx])) {
                _velo[prm_idx] = -1; //負であればよい
            }
        }
    }


//    virtual void transitionTrigonometricLoop(int prm_idx, frame prm_roop_frames, double prm_beat_num, bool prm_is_to_top) {
//        VAL_TYPE val = getValue(prm_idx);
//        _method[prm_idx] = BEAT_TRIGONOMETRIC;
//        _beat_frame_count[prm_idx] = 0;
//        _beat_frame_count_in_roop[prm_idx] = 0;
//        _beat_roop_frames[prm_idx] = prm_roop_frames;
//        if (prm_beat_num < 0) {
//            _beat_target_frames[prm_idx] = MAX_FRAME;
//        } else {
//            _beat_target_frames[prm_idx] = prm_roop_frames * prm_beat_num;
//        }
//        if (prm_is_to_top) {
//            _velo[prm_idx] = 1.0*(_top[prm_idx] - val) / ((int)prm_roop_frames / 2.0);
//            if (ZEROd_EQ(_velo[prm_idx])) {
//                _velo[prm_idx] = 1; //正であればよい
//            }
//        } else {
//            _velo[prm_idx] = 1.0*(_bottom[prm_idx] - val) / ((int)prm_roop_frames / 2.0);
//            if (ZEROd_EQ(_velo[prm_idx])) {
//                _velo[prm_idx] = -1; //負であればよい
//            }
//        }
//    }

    /**
     * 台形波の波形で値を遷移する。（全軸指定）.
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
     * ④ 減衰フレーム数<BR>
     * ⑤ 遷移上限(_top[軸] 配列が保持)<BR>
     * ⑥ 遷移下限(_bottom[軸] 配列が保持)<BR>
     * この内 ①～④を引数で設定、⑤⑥はforceRange()の設定値が使用される。<BR>
     * @param prm_roop_frames 上図で①のフレーム数
     * @param prm_attack_frames 上図で②のフレーム数
     * @param prm_sustain_frames 上図で③のフレーム数
     * @param prm_attenuate_frames 上図で④のフレーム数
     * @param prm_beat_num ループ数(-1で無限)
     */
    virtual void beat(frame prm_roop_frames,
                      frame prm_attack_frames,
                      frame prm_sustain_frames,
                      frame prm_attenuate_frames,
                      double prm_beat_num) {
        for (int i = 0; i < N; i++) {
            beat(i, prm_roop_frames, prm_attack_frames, prm_sustain_frames, prm_attenuate_frames, prm_beat_num);
        }
    }

    /**
     * 台形波の波形で値を遷移する。（軸別指定）.
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
     * ④ 減衰フレーム数<BR>
     * ⑤ 遷移上限(_top[軸] 配列が保持)<BR>
     * ⑥ 遷移下限(_bottom[軸] 配列が保持)<BR>
     * この内 ①～④を引数で設定、⑤⑥はforceRange()の設定値が使用される。<BR>
     * @param prm_idx 軸
     * @param prm_roop_frames 上図で①のフレーム数
     * @param prm_attack_frames 上図で②のフレーム数
     * @param prm_sustain_frames 上図で③のフレーム数
     * @param prm_attenuate_frames 上図で④のフレーム数
     * @param prm_beat_num ループ数(-1で無限)
     */
    virtual void beat(int prm_idx,
                      frame prm_roop_frames,
                      frame prm_attack_frames,
                      frame prm_sustain_frames,
                      frame prm_attenuate_frames,
                      double prm_beat_num) {
        _method[prm_idx] = BEAT_TRIANGLEWAVE;
        _beat_frame_count[prm_idx] = 0;
        _beat_frame_count_in_roop[prm_idx] = 0;
        _beat_frame_of_attack_finish[prm_idx] = prm_attack_frames;
        _beat_frame_of_sustain_finish[prm_idx] = _beat_frame_of_attack_finish[prm_idx] + prm_sustain_frames;
        _beat_frame_of_attenuate_finish[prm_idx] = _beat_frame_of_sustain_finish[prm_idx] + prm_attenuate_frames;
        _beat_roop_frames[prm_idx] = prm_roop_frames; //同じ
        if (prm_beat_num < 0) {
            _beat_target_frames[prm_idx] = MAX_FRAME;
        } else {
            _beat_target_frames[prm_idx] = _beat_roop_frames[prm_idx] * prm_beat_num;
        }
        //最初のアタックまでの速度
        VAL_TYPE val = getValue(prm_idx);
        if (_beat_frame_of_attack_finish[prm_idx] > 0 ) {
            _velo[prm_idx] = (VAL_TYPE)( ((double)(_top[prm_idx] - val)) / ((double)(_beat_frame_of_attack_finish[prm_idx])) );
        } else if (_beat_frame_of_attack_finish[prm_idx] == 0 ) {
            _velo[prm_idx] = _top[prm_idx] - val;
        }
    }

    /**
     * 値遷移中かどうか調べる .
     * @param prm_idx 軸
     * @return true/false
     */
    virtual bool isTransitioning(int prm_idx) {
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
    virtual bool isTransitioning() {
        for (int i = 0; i < N; i++) {
            if (_method[i] != NO_TRANSITION) {
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
            _beat_frame_of_attenuate_finish[i] = 0;
            _beat_roop_frames[i] = 0;
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
            TransitionMethod method = _method[i];
            VAL_TYPE val = getValue(i);
            VAL_TYPE top = _top[i];
            VAL_TYPE bottom = _bottom[i];
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
                    if (cnt == _beat_roop_frames[i]/2) {
                        //折り返し
                        if (_velo[i] > 0) { //山
                            val = top;
                            _velo[i] = (VAL_TYPE)( (2.0*(bottom-top)) / ((double)_beat_roop_frames[i]) ); //下りの速度
                        } else if (_velo[i] < 0) { //谷
                            val = bottom;
                            _velo[i] = (VAL_TYPE)( (2.0*(top-bottom)) / ((double)_beat_roop_frames[i]) ); //上りの速度
                        }
                    }
                    if (cnt == _beat_roop_frames[i]) {
                        //１ループ終了
                        if (_velo[i] > 0) { //山
                            val = top;
                            _velo[i] = (VAL_TYPE)( (2.0*(bottom-top)) / ((double)_beat_roop_frames[i]) ); //下りの速度
                        } else if (_velo[i] < 0) { //谷
                            val = bottom;
                            _velo[i] = (VAL_TYPE)( (2.0*(top-bottom)) / ((double)_beat_roop_frames[i]) ); //上りの速度
                        }
                        _beat_frame_count_in_roop[i] = 0;
                    }
                } else if (method == BEAT_TRIGONOMETRIC) {
//                    _beat_frame_count_in_roop[i]++;
//                    frame cnt = _beat_frame_count_in_roop[i];
//                    angle p = (double)cnt / (double)_beat_roop_frames[i]
//                    val =(-ANG_COS(p) + 1.0) * (top-bottom)
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
                        frame attenuate_frames = _beat_frame_of_attenuate_finish[i] - _beat_frame_of_sustain_finish[i]; //減衰時間
                        //下限までの減衰速度設定
                        if (attenuate_frames > 0)  {
                            _velo[i] = (VAL_TYPE)( (double)(bottom-top) / ((double)attenuate_frames) );
                        } else {
                            _velo[i] = bottom-top;
                        }
                    }
                    //減衰終了
                    if (cnt == _beat_frame_of_attenuate_finish[i]) {
                        val = bottom;
                        _velo[i] = 0;
                    }
                    //休憩終了
                    if (cnt == _beat_roop_frames[i]) {
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

    virtual ~GgafValueTransitioner() {

    }
};


}
#endif /*GGAFCORE_GGAFVALUETRANSITIONER_H_*/

