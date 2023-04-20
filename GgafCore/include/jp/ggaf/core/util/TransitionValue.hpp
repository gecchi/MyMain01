#ifndef GGAF_CORE_TRANSITIONVALUE_H_
#define GGAF_CORE_TRANSITIONVALUE_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include "jp/ggaf/core/util/Util.h"

namespace GgafCore {

/**
 * 遷移する値型 .
 * 終に念願の共通化。
 * @tparam VAL_TYPE 遷移値のデータ型
 * @version 1.00
 * @since 2021/12/07
 * @author Masatoshi Tsuge
 */
template<class VAL_TYPE>
class TransitionValue : public Object {

public:

    /**
     * 遷移方法
     */
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
    /** [r/w]値 */
    VAL_TYPE _t_value;
    /** [r/w]目標の遷移 */
    VAL_TYPE _target;
    /** [r/w]遷移上限値 */
    VAL_TYPE _top;
    /** [r/w]遷移下限値 */
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

public:
    /**
     * コンストラクタ<BR>
     */
    TransitionValue() : Object() {
        _velo = 0;
        _acce = 0;
        _target = 0;
        _top = 0;
        _bottom = 0;
        _beat_frame_of_attack_finish = 0;
        _beat_frame_of_sustain_finish = 0;
        _beat_frame_of_release_finish = 0;
        _beat_cycle_frames = 0;
        _beat_target_frames = 0;
        _beat_frame_count_in_roop = 0;
        _beat_frame_count = 0;
        _method = NO_TRANSITION;
    }

    /**
     * 値遷移の上限下限値を設定 .
     * @param prm1 遷移値1
     * @param prm2 遷移値2
     */
    virtual void setRange(VAL_TYPE prm1, VAL_TYPE prm2) {
        if (prm1 < prm2) {
            setBottom(prm1);
            setTop(prm2);
        } else {
            setBottom(prm2);
            setTop(prm1);
        }
    }

    /**
     * 上限値を設定 .
     * @param prm_top 上限値
     */
    virtual void setTop(VAL_TYPE prm_top) {
        _top = prm_top;
    }

    /**
     * 下限値を設定 .
     * @param prm_bottom 下限値
     */
    virtual void setBottom(VAL_TYPE prm_bottom) {
        _bottom = prm_bottom;
    }

    /**
     * 値に上限値を設定 .
     */
    virtual void setValueTop() {
        _t_value = _top;
    }

    /**
     * 値に下限値を設定 .
     */
    virtual void setValueBottom() {
        _t_value = _bottom;
    }

    /**
     * 値遷移の上限値を取得 .
     * @param prm_idx 対象インデックス
     * @return 上限値
     */
    virtual VAL_TYPE getTop() const {
        return _top;
    }

    /**
     * 値遷移の下限値を取得 .
     * @return
     */
    virtual VAL_TYPE getBottom() const {
        return _bottom;
    }

    /**
     * 値遷移を停止させる .
     */
    virtual void stop() {
        _velo = 0;
        _acce = 0;
        _method = NO_TRANSITION;
    }

    /**
     * 片道等速値遷移（持続フレーム数指定） .
     * 目標の遷移へ一定速度で値遷移する。
     * @param prm_target_T 遷移目標値
     * @param prm_spend_frame 費やすフレーム数
     */
    virtual void transitionLinearUntil(VAL_TYPE prm_target, frame prm_spend_frame) {
        _beat_frame_count = 0;
        _beat_target_frames = prm_spend_frame;
        _target = prm_target;
        _method = TARGET_LINEAR_UNTIL;
        //最初のアタックまでの速度
        if (_beat_target_frames > 0 ) {
            _velo = (VAL_TYPE)( ((double)(_target - _t_value)) / ((double)(_beat_target_frames)) );
        } else if (_beat_target_frames == 0 ) {
            _velo = _target - _t_value;
        }
    }

    /**
     * 上限遷移へ片道等速値遷移（持続フレーム数指定） .
     * @param prm_spend_frame 費やすフレーム数
     */
    virtual void transitionLinearToTop(frame prm_spend_frame) {
        transitionLinearUntil(getTop(), prm_spend_frame);
    }

    /**
     * 下限遷移へ片道等速値遷移（持続フレーム数指定） .
     * @param prm_spend_frame 費やすフレーム数
     */
    virtual void transitionLinearToBottom(frame prm_spend_frame) {
        transitionLinearUntil(getBottom(), prm_spend_frame);
    }

    /**
     * 片道等速値遷移（遷移速度指定） .
     * 目標の遷移へ一定速度で値遷移する（遷移差分指定） .
     * @param prm_target 遷移目標値
     * @param prm_velo 毎フレーム加算する遷移差分(>0.0)。正の遷移を指定する事。加算か減算かは自動判断する。
     */
    virtual void transitionLinearStep(VAL_TYPE prm_target, VAL_TYPE prm_velo) {
        _method = TARGET_LINEAR_STEP;
        _velo = prm_velo;
        _target = prm_target;
        _beat_frame_count = 0;
        _beat_target_frames = MAX_FRAME;
    }

    /**
     * 片道加速値遷移（遷移目標値指定） .
     * 目標の遷移へ加速指定で値遷移する。
     * 遷移加速度を0に指定すると transitionLinearStep とほぼ同じ意味になる。
     * transitionLinearStep の第３引数は正負を気にすること無いが、本メソッドは正負の自動判定はしない（できない）。
     * 遷移速度が正の場合、遷移目標値を超えると値遷移終了。
     * 遷移速度が負の場合、遷移目標値を下回ると値遷移終了。
     * 遷移目標値に到達する前に、速度の正負が逆転すると、たぶん永遠に到達できないので注意。
     * @param prm_target 遷移目標値
     * @param prm_init_velo 初期遷移速度
     * @param prm_acce 遷移加速度
     */
    virtual void transitionAcceUntil(VAL_TYPE prm_target, VAL_TYPE prm_init_velo, VAL_TYPE prm_acce) {
        _method = TARGET_ACCELERATION_UNTIL;
        _target = prm_target;
        _velo = prm_init_velo;
        _acce = prm_acce;
        _beat_frame_count = 0;
        _beat_target_frames = MAX_FRAME;
    }

    /**
     * 片道加速値遷移（目標速度値指定） .
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
        _method = TARGET_ACCELERATION_UNTIL_VELO;
        _target = prm_target_velo;
        _velo = prm_init_velo;
        _acce = prm_acce;
        _beat_frame_count = 0;
        _beat_target_frames = MAX_FRAME;
    }

    /**
     * 反復等速値遷移（フレーム数指定）
     * 上限遷移へ一定速度で値遷移し、一定速度で下遷移へ戻る。
     * これをループ指定する。（１ループのフレーム数指定） .
     * @param prm_cycle_frames １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_beat_num ループする回数(1.2回など少数で指定可能、-1 でほぼ無限ループ)
     * @param prm_is_to_top true:初めはTOPに遷移する／false:初めはBOTTOMに遷移
     */
    virtual void transitionLinearLoop(frame prm_cycle_frames, double prm_beat_num, bool prm_is_to_top) {
        _method = BEAT_LINEAR;
        _beat_frame_count = 0;
        _beat_frame_count_in_roop = 0;
        _beat_cycle_frames = prm_cycle_frames;
        if (prm_beat_num < 0) {
            _beat_target_frames = MAX_FRAME;
        } else {
            _beat_target_frames = (frame)(prm_cycle_frames * prm_beat_num);
        }
        if (prm_is_to_top) {
            _velo = (VAL_TYPE)(1.0*(_top - _t_value) / ((int)prm_cycle_frames * 0.5));
            if (ZEROd_EQ(_velo)) {
                _velo = 1; //正であればよい
            }
        } else {
            _velo = (VAL_TYPE)(1.0*(_bottom - _t_value) / ((int)prm_cycle_frames * 0.5));
            if (ZEROd_EQ(_velo)) {
                _velo = -1; //負であればよい
            }
        }
    }

    /**
     * 台形波の波形で値を遷移する。 .
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
        _method = BEAT_TRIANGLEWAVE;
        _beat_frame_count = 0;
        _beat_frame_count_in_roop = 0;
        _beat_frame_of_attack_finish = prm_attack_frames;
        _beat_frame_of_sustain_finish = _beat_frame_of_attack_finish + prm_sustain_frames;
        _beat_frame_of_release_finish = _beat_frame_of_sustain_finish + prm_release_frames;
        _beat_cycle_frames = prm_cycle_frames; //同じ
        if (prm_beat_num < 0) {
            _beat_target_frames = MAX_FRAME;
        } else {
            _beat_target_frames = (frame)(_beat_cycle_frames * prm_beat_num);
        }
        //最初のアタックまでの速度
        if (_beat_frame_of_attack_finish > 0 ) {
            _velo = (VAL_TYPE)( ((double)(_top - _t_value)) / ((double)(_beat_frame_of_attack_finish)) );
        } else if (_beat_frame_of_attack_finish == 0 ) {
            _velo = _top - _t_value;
        }
    }

    /**
     * 台形波の波形で値を遷移する .
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
        _method = R_BEAT_TRIANGLEWAVE;
        _beat_frame_count = 0;
        _beat_frame_count_in_roop = 0;
        _beat_frame_of_attack_finish = prm_attack_frames;
        _beat_frame_of_sustain_finish = _beat_frame_of_attack_finish + prm_sustain_frames;
        _beat_frame_of_release_finish = _beat_frame_of_sustain_finish + prm_release_frames;
        _beat_cycle_frames = prm_cycle_frames; //同じ
        if (prm_beat_num < 0) {
            _beat_target_frames = MAX_FRAME;
        } else {
            _beat_target_frames = (frame)(_beat_cycle_frames * prm_beat_num);
        }
        //最初のアタックまでの速度
        if (_beat_frame_of_attack_finish > 0 ) {
            _velo = (VAL_TYPE)( ((double)(_bottom - _t_value)) / ((double)(_beat_frame_of_attack_finish)) );
        } else if (_beat_frame_of_attack_finish == 0 ) {
            _velo = _bottom - _t_value;
        }
    }

    /**
     * 値遷移中かどうか調べる .
     * @return true/false
     */
    virtual bool isTransitioning() const {
        if (_method == NO_TRANSITION) {
            return false;
        } else {
            return true;
        }
    }

    virtual void reset() {
        _velo = 0;
        _acce = 0;
        _target = 0;
        _top = 0;
        _bottom = 1;
        _beat_frame_of_attack_finish = 0;
        _beat_frame_of_sustain_finish = 0;
        _beat_frame_of_release_finish = 0;
        _beat_cycle_frames = 0;
        _beat_target_frames = 0;
        _beat_frame_count_in_roop = 0;
        _beat_frame_count = 0;
        _method = NO_TRANSITION;
    }

    /**
     * 毎フレームの振る舞いメソッド。<BR>
     * 本クラスの機能を利用する場合は、このメソッドを<BR>
     * 毎フレーム実行することが必要。
     */
    virtual void behave() {
        const TransitionMethod method = _method;
        VAL_TYPE val = _t_value;
        const VAL_TYPE top = _top;
        const VAL_TYPE bottom = _bottom;
        _beat_frame_count++;
        _velo += _acce;
        val += _velo;

        switch (method) {
            case NO_TRANSITION: {
                //何もしない
                break;
            }
            case TARGET_LINEAR_UNTIL: {
                if (_beat_frame_count >= _beat_target_frames) {
                    val = _target;
                    stop();//終了
                }
                break;
            }
            case TARGET_LINEAR_STEP: {
                if ((_velo > 0  && val >= _target) || (_velo < 0  && val <= _target)) {
                    val = _target;
                    stop();//終了
                }
                break;
            }
            case TARGET_ACCELERATION_UNTIL: {
                if ((_velo > 0  && val >= _target) || (_velo < 0  && val <= _target)) {
                    val = _target;
                    stop();//終了
                }
                break;
            }
            case TARGET_ACCELERATION_UNTIL_VELO: {
                if ((_acce > 0  && _velo >= _target) || (_acce < 0  && _velo <= _target)) {
                   //加速度が正の場合、速度がターゲット速度より大きくなれば終了
                   //加速度が負の場合、速度がターゲット速度より小さくなれば終了
                   val -= _velo;
                   _velo = _target;
                   val += _velo;
                   stop();//終了
                }
                break;
            }
            case BEAT_LINEAR: {
                _beat_frame_count_in_roop++;
                const frame cnt = _beat_frame_count_in_roop;
                const frame beat_cycle_frames = _beat_cycle_frames;
                if (cnt == beat_cycle_frames/2) {
                    //折り返し
                    if (_velo > 0) { //山
                        val = top;
                        _velo = (VAL_TYPE)( (2.0*(bottom-top)) / ((double)beat_cycle_frames) ); //下りの速度
                    } else if (_velo < 0) { //谷
                        val = bottom;
                        _velo = (VAL_TYPE)( (2.0*(top-bottom)) / ((double)beat_cycle_frames) ); //上りの速度
                    }
                }
                if (cnt == beat_cycle_frames) {
                    //１ループ終了
                    if (_velo > 0) { //山
                        val = top;
                        _velo = (VAL_TYPE)( (2.0*(bottom-top)) / ((double)beat_cycle_frames) ); //下りの速度
                    } else if (_velo < 0) { //谷
                        val = bottom;
                        _velo = (VAL_TYPE)( (2.0*(top-bottom)) / ((double)beat_cycle_frames) ); //上りの速度
                    }
                    _beat_frame_count_in_roop = 0;
                }
                break;
            }
            case BEAT_TRIANGLEWAVE: {
                _beat_frame_count_in_roop++;
                const frame cnt = _beat_frame_count_in_roop;
                const frame beat_frame_of_attack_finish = _beat_frame_of_attack_finish;
                //アタック終了時
                if (cnt == beat_frame_of_attack_finish) {
                    val = top;
                    _velo = 0;
                }
                //維持終時
                if (cnt == _beat_frame_of_sustain_finish) {
                    val = top;
                    int attenuate_frames = (int)_beat_frame_of_release_finish - (int)_beat_frame_of_sustain_finish; //減衰(余韻)時間
                    //下限までの減衰(余韻)速度設定
                    if (attenuate_frames > 0)  {
                        _velo = (VAL_TYPE)( (double)(bottom-top) / ((double)attenuate_frames) );
                    } else {
                        _velo = bottom-top;
                    }
                }
                //減衰(余韻)終了
                if (cnt == _beat_frame_of_release_finish) {
                    val = bottom;
                    _velo = 0;
                }
                //休憩終了
                if (cnt == _beat_cycle_frames) {
                    val = bottom;
                    _beat_frame_count_in_roop = 0;
                    //次のアタックへの速度設定
                    if (beat_frame_of_attack_finish > 0 ) {
                        _velo = (VAL_TYPE)( ((double)(top - val)) / ((double)beat_frame_of_attack_finish) );
                    } else if (beat_frame_of_attack_finish == 0 ) {
                        _velo = top - val;
                    }
                }
                break;
            }
            case R_BEAT_TRIANGLEWAVE: {
                _beat_frame_count_in_roop++;
                const frame cnt = _beat_frame_count_in_roop;
                const frame beat_frame_of_attack_finish = _beat_frame_of_attack_finish;
                //アタック終了時
                if (cnt == beat_frame_of_attack_finish) {
                    val = bottom;
                    _velo = 0;
                }
                //維持(下限)終時
                if (cnt == _beat_frame_of_sustain_finish) {
                    val = bottom;
                    int attenuate_frames = (int)_beat_frame_of_release_finish - (int)_beat_frame_of_sustain_finish; //復帰時間
                    //上限までの復帰速度設定
                    if (attenuate_frames > 0)  {
                        _velo = (VAL_TYPE)( (double)(top - bottom) / ((double)attenuate_frames) );
                    } else {
                        _velo = top - bottom;
                    }
                }
                //復帰終了
                if (cnt == _beat_frame_of_release_finish) {
                    val = top;
                    _velo = 0;
                }
                //休憩終了
                if (cnt == _beat_cycle_frames) {
                    val = top;
                    _beat_frame_count_in_roop = 0;
                    //次のアタックへの速度設定
                    if (beat_frame_of_attack_finish > 0 ) {
                        _velo = (VAL_TYPE)( ((double)(bottom - val)) / ((double)beat_frame_of_attack_finish) );
                    } else if (beat_frame_of_attack_finish == 0 ) {
                        _velo = bottom - val;
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
        _t_value = val; //反映
        if (_beat_frame_count >= _beat_target_frames) {
            stop();//終了
        }
    }

    virtual ~TransitionValue() {
    }
};

}

#endif /*GGAF_CORE_TRANSITIONVALUE_H_*/

