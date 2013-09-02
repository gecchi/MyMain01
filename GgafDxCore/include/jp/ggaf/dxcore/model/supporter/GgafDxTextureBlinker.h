#ifndef GGAFDXCORE_GGAFDXTEXTUREBLINKER_H_
#define GGAFDXCORE_GGAFDXTEXTUREBLINKER_H_
#include "jp/ggaf/core/GgafObject.h"

namespace GgafDxCore {

/**
 * 特定カラー点滅支援クラス.
 * GgafDxModel のメンバの _power_blink <BR>
 * を、簡単に操作するために設計した。<BR>
 * 最終的にピクセルシェーダーで色(float4)に乗ずる値となる。
 * 色強度 1.0 は色強度無し、
 * 色強度 2.0 は色強度２倍。明るくなる。
 * 色強度 0.5 は色強度1/２倍。暗くなる。
 * TODO:GgafDxScaler,GgafDxMorpher,GgafDxTextureBlinker を共通化する。
 * @version 1.00
 * @since 2009/05/22
 * @author Masatoshi Tsuge
 */
class GgafDxTextureBlinker : public GgafCore::GgafObject {

public:
    /** 対象アクター */
    GgafDxModel* _pModel;

    /** 色強度(0.0 ～ 100.0) */
    float _power_blink;
    /** 目標の色強度 */
    float _target_power_blink;
    /** 色強度上限 */
    float _top_power_blink;
    /** 色強度下限 */
    float _bottom_power_blink;
    /** 毎フレームの色強度の増分 */
    float _velo_power_blink;
    /** 毎フレームの色強度の増分の増分 */
    float _acce_power_blink;
    /** 三角波の波形で点滅のアタックフレーム */
    frame _beat_attack_frames;
    /** 三角波の波形で点滅のレストフレーム */
    frame _beat_rest_frames;
    /** 点滅に費やすフレーム数 */
    frame _beat_target_frames;
    /** 点滅を開始したフレーム */
    frame _frame_of_beat_begin;
    /** ビート時、各軸のアタックから下限までのフレーム数 */
    frame _beat_down_frames;
    /** ビート時、内部カウンター */
    frame _beat_frame_count;
    /** ビート時、内部進捗番号 */
    int _beat_progres;
    /** ループカウント（2で点滅ワンセット、1ならば点灯o消灯の片道） */
    int _one_way_cnt;
    /** ストップする予定のループカウント */
    int _stop_one_way_num;
    /** 点滅方法 */
    GgafDxBlinkingMethod _method;

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pModel  適用対象のModel
     */
    GgafDxTextureBlinker(GgafDxModel* prm_pModel);

    /**
     * 色強度を相対指定
     * @param prm_power_blink_diff 色強度値増分
     */
    void addPower(float prm_power_blink_diff) {
        setPower(_power_blink + prm_power_blink_diff);
    }

    /**
     * 色強度を絶対指定
     * @param prm_power_blink 色強度値
     */
    void setPower(float prm_power_blink) {
        //_TRACE_("setPower ["<<prm_<<"]prm_power_blink="<<prm_power_blink);
        //_TRACE_("setPower _bottom_power_blink["<<prm_<<"]="<<_bottom_power_blink<<"/_top_power_blink["<<prm_<<"]="<<_top_power_blink<<"");
        if (_top_power_blink < prm_power_blink) {
            _power_blink = _top_power_blink;
        } else if (_bottom_power_blink > prm_power_blink) {
            _power_blink = _bottom_power_blink;
        } else {
            _power_blink = prm_power_blink;
        }
        //_TRACE_("setPower _power_blink ["<<prm_<<"] _power_blink="<<prm_power_blink);
    }

    /**
     * 対象色しきい値と、色強度の上限下限を設定 .
     * 対象色しきい値とは、点滅させる対象のテクスチャの色の強さ具合です。<BR>
     * ピクセルシェーダーにおいて、<BR>
     * ・ここまでの計算した色（テクスチャやライト考慮済み）・・・ colOut.rgba<BR>
     * ・テクスチャの色 ・・・ colTex.rgba<BR>
     * ・対象色しきい値 ・・・ g_tex_blink_threshold<BR>
     * ・現在の色強度値 ・・・ g_tex_blink_power<BR>
     * とした場合、以下の様な処理を行なっています。<BR>
     * <code><pre>
     * <BR>
     * if (colTex.r >= g_tex_blink_threshold || colTex.g >= g_tex_blink_threshold || colTex.b >= g_tex_blink_threshold) {
     *     colOut *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
     * }
     * </pre></code>
     * @param prm_blink_threshold 点滅の対象色しきい値 (0.0 ～ 1.0)
     * @param prm_power_blink1 色強度値1 (負の数 ～ 0:黒 ～ 1.0:等倍強度 ～ )
     * @param prm_power_blink2 色強度値2 (負の数 ～ 0:黒 ～ 1.0:等倍強度 ～ )
     */
    void setBlinkableRange(float prm_blink_threshold, float prm_power_blink1, float prm_power_blink2);

    /**
     * 色強度を下限にリセット
     */
    void setPowerToBottom() {
        _power_blink = _bottom_power_blink;
    }

    /**
     * 色強度を上限にリセット
     */
    void setPowerToTop() {
        _power_blink = _top_power_blink;
    }

    /**
     * 点滅を停止させる。.
     */
    void stopImmed();

    /**
     * 片道等速点灯（全軸・持続フレーム数指定） .
     * 目標の色強度へ一定速度で１回点灯（消灯）する
     * @param prm_target_power_blink 目標色強度
     * @param prm_spend_frame 費やすフレーム数
     */
    void blinkLinerUntil(float prm_target_power_blink, frame prm_spend_frame);

    /**
     * 片道等速点灯（全軸・色強度速度指定） .
     * 目標の色強度へ一定速度で１回点灯（消灯）する
     * @param prm_target_power_blink 目標色強度
     * @param prm_velo_power_blink 毎フレーム加算する色強度差分(>0.0)。正の色強度差分を指定する事。
     *                             色強度の加算か減算かは現在の色強度より目標色強度が高いか低いかで自動判断する。
     */
    void blinkLinerStep(float prm_target_power_blink, float prm_velo_power_blink);

    /**
     * 片道加速点灯（全軸・色強度速度・色強度加速度指定） .
     * 目標の色強度へ加速指定で１回点灯（消灯）する
     * 色強度加速度を0に指定すると blinkLinerStep とほぼ同じ意味になる。
     * blinkLinerStep の第２引数は正負を気にすること無いが、本メソッドは正負の自動判定はしないので注意して設定せよ。
     * @param prm_target_power_blink 目標色強度
     * @param prm_velo_power_blink 初期色強度速度
     * @param prm_acce_power_blink 色強度加速度
     */
    void blinkAcceStep(float prm_target_power_blink, float prm_velo_power_blink, float prm_acce_power_blink);

    /**
     * 反復等速点滅 .
     * 目標の色強度上限（_top_power_blink）へ一定速度で光り、一定速度で色強度下限（_bottom_power_blink）元に戻る。
     * これを１ループとし、費やすフレーム数を指定する。
     * @param prm_beat_target_frames １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_beat_num ループする回数(0.5 回単位で指定可能)
     */
    void loopLiner(frame prm_beat_target_frames, float prm_beat_num);

    /**
     * 三角波の波形で点滅する。.
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
     * ④ 色強度上限(_top_power_blinkが保持)<BR>
     * ⑤ 色強度下限(_bottom_power_blinkが保持)<BR>
     * <BR>
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
     * 毎フレームの振る舞いメソッド。<BR>
     * 本クラスの機能を利用する場合は、このメソッドを<BR>
     * 毎フレーム実行することが必要。
     */
    virtual void behave();

    virtual ~GgafDxTextureBlinker();
};

}
#endif /*GGAFDXCORE_GGAFDXTEXTUREBLINKER_H_*/

