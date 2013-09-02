#ifndef GGAFDXCORE_GGAFDXSCALER_H_
#define GGAFDXCORE_GGAFDXSCALER_H_
#include "jp/ggaf/core/GgafObject.h"

namespace GgafDxCore {

/**
 * 拡大縮小支援クラス.
 * GgafDxGeometricActor のメンバの<BR>
 * _SX , _SY, _SZ  ・・・ アクターのスケール<BR>
 * を、簡単に操作するために設計した。<BR>
 * 拡大縮小1.0倍（スケール無し）は、本クラスでのスケール値1000に相当する。
 * [日本語]     → [本クラスのスケール値]
 * 等倍         → 1000
 * 2.5倍拡大    → 2500
 * 半分の大きさ → 500
 * 縮小率80%    → 800
 * 本クラスでは、スケールとスケーリングという単語を次の意味で使用している箇所がある。
 * スケール・・・現在（のフレーム）の拡大縮小状態、スケール値
 * スケーリング・・・フレーム間の拡大縮小状態の遷移
 * 2009/05/22 GgafDxKurokoA から分割した。
 * TODO:GgafDxScaler,GgafDxMorpher,GgafDxTextureBlinker を共通化する。
 * @version 1.00
 * @since 2009/05/22
 * @author Masatoshi Tsuge
 */
class GgafDxScaler : public GgafCore::GgafObject {

public: //_SX , _SY, _SZ 操作関連 //////////////////////////////////////////////
    /** [r]対象アクター */
    GgafDxGeometricActor* _pActor;
    /** [r/w]各軸のスケール(1000 で 1倍) */
    int _scale[3]; //[0]:X軸、[1]:Y軸、[2]:Z軸。以降同様に  [3]・・・X軸、Y軸、Z軸の意
    /** [r/w]各軸の目標のスケール */
    int _target_scale[3];
    /** [r/w]各軸のスケール上限 */
    int _top_scale[3];
    /** [r/w]各軸のスケール下限 */
    int _bottom_scale[3];
    /** [r/w]各軸の毎フレームのスケールの増分 */
    int _velo_scale[3];
    /** [r/w]各軸の毎フレームのスケールの増分の増分 */
    int _acce_scale[3];
    /** [r]各軸のループカウント（2で拡大縮小ワンセット、1ならば拡大or縮小の片道） */
    int _one_way_cnt[3];
    /** [r]各軸のストップする予定のループカウント */
    int _stop_one_way_num[3];
    /** [r]各軸のスケーリング方法 */
    GgafDxScalingMethod _method[3];
    /** [r]ビート時、各軸の三角波の波形でスケーリングのアタックフレーム数 */
    frame _beat_attack_frames[3];
    /** [r]ビート時、各軸の三角波の波形でスケーリングのレストフレーム数 */
    frame _beat_rest_frames[3];
    /** [r]ビート時、各軸のスケーリングに費やすフレーム数 */
    frame _beat_target_frames[3];
    /** [r]ビート時、各軸のアタックから下限までのフレーム数 */
    frame _beat_down_frames[3];
    /** [r]ビート時、内部カウンター */
    frame _beat_frame_count[3];
    /** [r]ビート時、内部進捗番号 */
    int _beat_progres[3];

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用対象のActor
     */
    GgafDxScaler(GgafDxGeometricActor* prm_pActor);

    /**
     * スケールを相対指定（全軸指定）
     * @param prm_scale_diff スケール値増分
     */
    inline void addScale(int prm_scale_diff) {
        for (int a = 0; a < 3; a++) {
            addScale((axis)a, prm_scale_diff);
        }
    }

    /**
     * スケールを相対指定（軸単位で指定）
     * @param prm_axis 軸
     * @param prm_scale_diff スケール値増分
     */
    inline void addScale(axis prm_axis, int prm_scale_diff) {
        setScale(prm_axis, _scale[prm_axis] + prm_scale_diff);
    }

    /**
     * スケールを絶対指定（全軸指定）
     * @param prm_scale スケール値
     */
    inline void setScale(int prm_scale) {
        for (int a = 0; a < 3; a++) {
            setScale((axis)a, prm_scale);
        }
    }

    /**
     * スケールを絶対指定（軸単位で指定）
     * @param prm_axis 軸
     * @param prm_scale スケール値
     */
    inline void setScale(axis prm_axis, int prm_scale) {
        if (_top_scale[prm_axis] < prm_scale) {
            _scale[prm_axis] = _top_scale[prm_axis];
        } else if (_bottom_scale[prm_axis] > prm_scale) {
            _scale[prm_axis] = _bottom_scale[prm_axis];
        } else {
            _scale[prm_axis] = prm_scale;
        }
    }

    /**
     * スケールの上限下限を設定（全軸指定） .
     * 引数の大小は気にせず渡して(内部で自動判別)
     * @param prm_scale1 スケール値1
     * @param prm_scale2 スケール値2
     */
    void forceRange(int prm_scale1, int prm_scale2) {
        for (int a = 0; a < 3; a++) {
            forceRange((axis)a, prm_scale1, prm_scale2);
            setScale((axis)a, _scale[a]);
        }
    }

    /**
     * スケールの上限下限を設定（軸単位で指定）
     * @param prm_axis 軸
     * @param prm_scale1 スケール値1
     * @param prm_scale2 スケール値2
     */
    void forceRange(axis prm_axis, int prm_scale1, int prm_scale2) {
        if (prm_scale1 < prm_scale2) {
            _bottom_scale[prm_axis] = prm_scale1;
            _top_scale[prm_axis] = prm_scale2;
        } else {
            _bottom_scale[prm_axis] = prm_scale2;
            _top_scale[prm_axis] = prm_scale1;
        }
    }

    /**
     * スケールをリセット （全軸指定） .
     * 本オブジェクト(GgafDxScaler)によって変化さえる前の
     * 初期の大きさに戻す。
     */
    void setScaleToBottom() {
        for (int a = 0; a < 3; a++) {
            setScaleToBottom((axis)a);
        }
    }

    /**
     * スケールをリセット （軸単位で指定）
     * 本オブジェクト(GgafDxScaler)によって変化さえる前の
     * 初期の大きさに戻す。
     * @param prm_axis 軸
     */
    void setScaleToBottom(axis prm_axis) {
        _scale[prm_axis] = _bottom_scale[prm_axis];
    }

    void setScaleToTop() {
        for (int a = 0; a < 3; a++) {
            setScaleToTop((axis)a);
        }
    }
    void setScaleToTop(axis prm_axis) {
        _scale[prm_axis] = _top_scale[prm_axis];
    }

    /**
     * スケーリングを停止させる。 （全軸指定） .
     */
    void stopImmed();

    /**
     * スケーリングを停止させる。 （軸単位で指定）.
     * @param prm_axis
     */
    void stopImmed(axis prm_axis);

    /**
     * 片道等速スケーリング（全軸・持続フレーム数指定） .
     * 目標のスケールへ一定速度でスケーリングする
     * @param prm_target_scale 目標スケール
     * @param prm_spend_frame 費やすフレーム数
     */
    void scaleLinerUntil(int prm_target_scale, frame prm_spend_frame);

    /**
     * 上限スケールへ片道等速スケーリング（全軸・持続フレーム数指定） .
     * @param prm_spend_frame 費やすフレーム数
     */
    void scaleLinerTop(frame prm_spend_frame);

    /**
     * 下限スケールへ片道等速スケーリング（全軸・持続フレーム数指定） .
     * @param prm_spend_frame 費やすフレーム数
     */
    void scaleLinerBottom(frame prm_spend_frame);

    /**
     * 片道等速スケーリング（軸単位・持続フレーム数指定） .
     * 目標のスケールへ一定速度でスケーリングする。
     * @param prm_axis 軸
     * @param prm_target_scale 目標スケール
     * @param prm_spend_frame 費やすフレーム数
     */
    void scaleLinerUntil(axis prm_axis, int prm_target_scale, frame prm_spend_frame);

    /**
     * 片道等速スケーリング（全軸・スケール速度指定） .
     * 目標のスケールへ一定速度でスケーリングする
     * @param prm_target_scale 目標スケール
     * @param prm_velo_scale 毎フレーム加算するスケール差分(>0.0)。正のスケールを指定する事。加算か減算かは自動判断する。
     */
    void scaleLinerStep(int prm_target_scale, int prm_velo_scale);

    /**
     * 片道等速スケーリング（軸単位・スケール速度指定） .
     * 目標のスケールへ一定速度でスケーリングする（スケール差分指定） .
     * @param prm_axis 軸
     * @param prm_target_scale 目標スケール
     * @param prm_velo_scale 毎フレーム加算するスケール差分(>0.0)。正のスケールを指定する事。加算か減算かは自動判断する。
     */
    void scaleLinerStep(axis prm_axis, int prm_target_scale, int prm_velo_scale);

    /**
     * 片道加速スケーリング（全軸・スケール速度・スケール加速度指定） .
     * 目標のスケールへ加速指定でスケーリングする
     * スケール加速度を0に指定すると scaleLinerStep とほぼ同じ意味になる。
     * scaleLinerStep の第３引数は正負を気にすること無いが、本メソッドは正負の自動判定はしない（できない）。
     * スケール加速度が正の場合、目標スケールを超えるとスケーリング終了。
     * スケール加速度が負の場合、目標スケールを下回るとスケーリング終了。
     * @param prm_target_scale 目標スケール
     * @param prm_velo_scale 初期スケール速度
     * @param prm_acce_scale スケール加速度
     */
    void scaleAcceStep(int prm_target_scale, int prm_velo_scale, int prm_acce_scale);

    /**
     * 片道加速スケーリング（軸単位・スケール速度・スケール加速度指定） .
     * 目標のスケールへ加速指定でスケーリングする（スケール速度、スケール加速度差指定） .
     * スケール加速度を0に指定すると scaleLinerStep とほぼ同じ意味になる。
     * scaleLinerStep の第３引数は正負を気にすること無いが、本メソッドは正負の自動判定はしない（できない）。
     * @param prm_axis 軸
     * @param prm_target_scale 目標スケール
     * @param prm_velo_scale 初期スケール速度
     * @param prm_acce_scale スケール加速度
     */
    void scaleAcceStep(axis prm_axis, int prm_target_scale, int prm_velo_scale, int prm_acce_scale);

    /**
     * 反復等速スケーリング（全軸・フレーム数指定） .
     * 目標のスケールへ一定速度でスケーリングし、一定速度で元に戻る。これをループ指定する。（１ループのフレーム数指定） .
     * @param prm_beat_target_frames １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_beat_num ループする回数(0.5 回単位で指定可能)
     */
    void loopLiner(frame prm_beat_target_frames, float prm_beat_num);

    /**
     * 反復等速スケーリング（軸単位・フレーム数指定）
     * 目標のスケールへ一定速度でスケーリングし、一定速度で元に戻る。
     * これをループ指定する。（１ループのフレーム数指定） .
     * @param prm_axis 軸
     * @param prm_beat_target_frames １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_beat_num ループする回数(0.5 回単位で指定可能)
     */
    void loopLiner(axis prm_axis, frame prm_beat_target_frames, float prm_beat_num);

    /**
     * 三角波の波形でスケーリングする。（全軸指定）.
     * <PRE>
     * ④  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
     *            /＼                     /＼
     *           /   ＼                  /   ＼
     *          /      ＼               /      ＼
     *         /         ＼            /         ＼
     *        /            ＼         /            ＼
     * ⑤  ＿/               ＼＿＿＿/               ＼＿
     *
     *       ←②→            ←③→
     *       ←──── ① ────→
     * </PRE>
     * ＜必要な設定値＞<BR>
     * ① １ループのフレーム数<BR>
     * ② アタックまでのフレーム数<BR>
     * ③ 休憩フレーム数<BR>
     * ④ スケール上限(_top_scale[軸] 配列が保持)<BR>
     * ⑤ スケール下限(_bottom_scale[軸] 配列が保持)<BR>
     * @param prm_beat_target_frames 上図で①のフレーム数
     * @param prm_attack_frames 上図で②のフレーム数
     * @param prm_rest_frames 上図で③のフレーム数
     * @param prm_beat_num ループ数(-1で無限)
     */
    void beat(frame prm_beat_target_frames,
              frame prm_attack_frames,
              frame prm_rest_frames,
              float prm_beat_num);

    /**
     * 三角波の波形でスケーリングする。（軸指定）.
     * @param prm_axis 軸
     * @param prm_beat_target_frames 上図で①のフレーム数
     * @param prm_attack_frames 上図で②のフレーム数
     * @param prm_rest_frames 上図で③のフレーム数
     * @param prm_beat_num ループ数(-1で無限)
     */
    void beat(axis prm_axis,
              frame prm_beat_target_frames,
              frame prm_attack_frames,
              frame prm_rest_frames,
              float prm_beat_num);

    /**
     * スケーリング中かどうか調べる .
     * @param prm_axis 軸
     * @return true/false
     */
    bool isScaling(axis prm_axis);

    /**
     * スケーリング中かどうか調べる .
     * @return true/false
     */
    bool isScaling();

    void reset();

    /**
     * 毎フレームの振る舞いメソッド。<BR>
     * 本クラスの機能を利用する場合は、このメソッドを<BR>
     * 毎フレーム実行することが必要。
     */
    virtual void behave();

    virtual ~GgafDxScaler();
};

}
#endif /*GGAFDXCORE_GGAFDXSCALER_H_*/

