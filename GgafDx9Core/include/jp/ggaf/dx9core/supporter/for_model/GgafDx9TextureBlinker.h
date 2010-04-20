#ifndef GGAFDX9TEXTUREBLINKER_H_
#define GGAFDX9TEXTUREBLINKER_H_
namespace GgafDx9Core {

/**
 * 特定カラー点滅支援クラス.
 * GgafDx9Model のメンバの _fPowerBlink <BR>
 * を、簡単に操作するために設計した。<BR>
 * 最終的にピクセルシェーダーで色(float4)に乗ずる値となる。
 * 色強度 1.0 は色強度無し、
 * 色強度 2.0 は色強度２倍。明るくなる。
 * 色強度 0.5 は色強度1/２倍。暗くなる。
 * @version 1.00
 * @since 2009/05/22
 * @author Masatoshi Tsuge
 */
class GgafDx9TextureBlinker : public GgafCore::GgafObject {

public: //_SX , _SY, _SZ 操作関連 //////////////////////////////////////////////
    /** 対象アクター */
    GgafDx9Model* _pModel;

    /** 色強度(0.0 〜 100.0) */
    float _fPowerBlink;
    /** 目標の色強度 */
    float _target_fPowerBlink;
    /** 色強度上限 */
    float _top_fPowerBlink;
    /** 色強度下限 */
    float _bottom_fPowerBlink;
    /** 毎フレームの色強度の増分 */
    float _velo_fPowerBlink;
    /** 毎フレームの色強度の増分の増分 */
    float _acce_fPowerBlink;
    /** 三角波の波形で点滅のアタックフレーム */
    DWORD _beat_attack_frame;
    /** 三角波の波形で点滅のレストフレーム */
    DWORD _beat_rest_frame;
    /** 点滅に費やすフレーム数 */
    DWORD _beat_spend_frame;
    /** 点滅を開始したフレーム */
    DWORD _beat_begin_frame;
    /** ループカウント（2で点滅ワンセット、1ならば拡大or縮小の片道） */
    int _one_way_cnt;
    /** ストップする予定のループカウント */
    int _stop_one_way_num;
    /** 点滅方法 */
    GgafDx9BlinkerMethod _method;

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pModel  適用対象のModel
     */
    GgafDx9TextureBlinker(GgafDx9Model* prm_pModel);

    /**
     * 色強度を相対指定
     * @param prm_fPowerBlink_diff 色強度値増分
     */
    void addBlink(float prm_fPowerBlink_diff) {
        setBlink(_fPowerBlink + prm_fPowerBlink_diff);
    }

    /**
     * 色強度を絶対指定
     * @param prm_fPowerBlink 色強度値
     */
    void setBlink(float prm_fPowerBlink) {
        //_TRACE_("setBlink ["<<prm_<<"]prm_fPowerBlink="<<prm_fPowerBlink);
        //_TRACE_("setBlink _bottom_fPowerBlink["<<prm_<<"]="<<_bottom_fPowerBlink<<"/_top_fPowerBlink["<<prm_<<"]="<<_top_fPowerBlink<<"");
        if (_top_fPowerBlink < prm_fPowerBlink) {
            _fPowerBlink = _top_fPowerBlink;
        } else if (_bottom_fPowerBlink > prm_fPowerBlink) {
            _fPowerBlink = _bottom_fPowerBlink;
        } else {
            _fPowerBlink = prm_fPowerBlink;
        }
        //_TRACE_("setBlink _fPowerBlink ["<<prm_<<"] _fPowerBlink="<<prm_fPowerBlink);
    }
    /**
     * 色強度の上限下限を設定
     * @param prm_fPowerBlink1 色強度値1
     * @param prm_fPowerBlink2 色強度値2
     */
    void forceBlinkRange(float prm_fPowerBlink1, float prm_fPowerBlink2) {
        if (prm_fPowerBlink1 < prm_fPowerBlink2) {
            _bottom_fPowerBlink = prm_fPowerBlink1;
            _top_fPowerBlink = prm_fPowerBlink2;
        } else {
            _bottom_fPowerBlink = prm_fPowerBlink2;
            _top_fPowerBlink = prm_fPowerBlink1;
        }
        //_TRACE_("forceBlinkRange _bottom_fPowerBlink["<<prm_<<"]="<<_bottom_fPowerBlink<<"/_top_fPowerBlink["<<prm_<<"]="<<_top_fPowerBlink<<"");
    }
    /**
     * 色強度をリセット
     * 本オブジェクト(GgafDx9TextureBlinker)によって変化さえる前の
     * 初期の大きさに戻す。
     */
    void setBlinkToBottom() {
        _fPowerBlink = _bottom_fPowerBlink;
    }

    void setBlinkToTop() {
        _fPowerBlink = _top_fPowerBlink;
    }

    /**
     * 点滅を停止させる。  .
     */
    void stopImmediately();

    /**
     * 片道等速点滅（全軸・持続フレーム数指定） .
     * 目標の色強度へ一定速度で点滅する
     * @param prm_target_fPowerBlink 目標色強度
     * @param prm_spend_frame 費やすフレーム数
     */
    void intoTargetBlinkLinerUntil(float prm_target_fPowerBlink, DWORD prm_spend_frame);

    /**
     * 片道等速点滅（全軸・色強度速度指定） .
     * 目標の色強度へ一定速度で点滅する
     * @param prm_target_fPowerBlink 目標色強度
     * @param prm_velo_fPowerBlink 毎フレーム加算する色強度差分(>0.0)。正の色強度差分を指定する事。
     *                             色強度の加算か減算かは現在の色強度より目標色強度が高いか低いかで自動判断する。
     */
    void intoTargetBlinkLinerStep(float prm_target_fPowerBlink, float prm_velo_fPowerBlink);

    /**
     * 片道加速点滅（全軸・色強度速度・色強度加速度指定） .
     * 目標の色強度へ加速指定で点滅する
     * 色強度加速度を0に指定すると intoTargetBlinkLinerStep とほぼ同じ意味になる。
     * intoTargetBlinkLinerStep の第２引数は正負を気にすること無いが、本メソッドは正負の自動判定はしないので注意して設定せよ。
     * @param prm_target_fPowerBlink 目標色強度
     * @param prm_velo_fPowerBlink 初期色強度速度
     * @param prm_acce_fPowerBlink 色強度加速度
     */
    void intoTargetBlinkAcceStep(float prm_target_fPowerBlink, float prm_velo_fPowerBlink, float prm_acce_fPowerBlink);

    /**
     * 反復等速点滅 .
     * 目標の色強度上限（_top_fPowerBlink）へ一定速度で光り、一定速度で色強度下限（_bottom_fPowerBlink）元に戻る。
     * これを１ループとし、費やすフレーム数を指定する。
     * @param prm_beat_spend_frame １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_beat_num ループする回数(0.5 回単位で指定可能)
     */
    void loopLiner(DWORD prm_beat_spend_frame, float prm_beat_num);

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
     * ④ 色強度上限(_top_fPowerBlinkが保持)<BR>
     * ⑤ 色強度下限(_bottom_fPowerBlinkが保持)<BR>
     * <BR>
     * @param prm_beat_spend_frame 上図で①のフレーム数
     * @param prm_attack_frame 上図で②のフレーム数
     * @param prm_rest_frame 上図で③のフレーム数
     * @param prm_beat_num ループ数(-1で無限)
     */
    void beat(DWORD prm_beat_spend_frame,
              DWORD prm_attack_frame,
              DWORD prm_rest_frame,
              float prm_beat_num);


    /**
     * 毎フレームの振る舞いメソッド。<BR>
     * 本クラスの機能を利用する場合は、このメソッドを<BR>
     * 毎フレーム実行することが必要。
     */
    virtual void behave();

    virtual ~GgafDx9TextureBlinker();
};

}
#endif /*GGAFDX9TEXTUREBLINKER_H_*/

