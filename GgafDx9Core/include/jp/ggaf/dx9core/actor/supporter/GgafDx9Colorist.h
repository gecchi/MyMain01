#ifndef GGAFDX9COLORIST_H_
#define GGAFDX9COLORIST_H_
namespace GgafDx9Core {

/**
 * 拡大縮小支援クラス.
 * GgafDx9GeometricActor のメンバの<BR>
 * _SX , _SY, _SZ  ・・・ アクターの強度<BR>
 * を、簡単に操作するために設計した。<BR>
 * 拡大縮小1.0倍（強度無し）は、本クラスでの強度値1000に相当する。
 * [日本語]     → [本クラスの強度値]
 * 等倍         → 1000
 * 2.5倍拡大    → 2500
 * 半分の大きさ → 500
 * 縮小率80%    → 800
 * 本クラスでは、強度とスケーリングという単語を次の意味で使用している箇所がある。
 * 強度・・・現在（のフレーム）の拡大縮小状態、強度値
 * スケーリング・・・フレーム間の拡大縮小状態の遷移
 * 2009/05/22 GgafDx9KurokoA から分割した。
 * TODO:GgafDx9Colorist,GgafDx9Morpher,GgafDx9TextureBlinker を共通化する。
 * @version 1.00
 * @since 2009/05/22
 * @author Masatoshi Tsuge
 */
class GgafDx9Colorist : public GgafCore::GgafObject {

public: //_SX , _SY, _SZ 操作関連 //////////////////////////////////////////////
    /** 対象アクター */
    GgafDx9GeometricActor* _pActor;

    /** 各色要素の強度(1000 で 1倍) */
    int _color[4]; //[0]:R色要素、[1]:G色要素、[2]:B色要素。以降同様に  [4]・・・X色要素、Y色要素、Z色要素の意
    /** 各色要素の目標の強度 */
    int _target_color[4];
    /** 各色要素の強度上限 */
    int _top_color[4];
    /** 各色要素の強度下限 */
    int _bottom_color[4];
    /** 各色要素の毎フレームの強度の増分 */
    int _velo_color[4];
    /** 各色要素の毎フレームの強度の増分の増分 */
    int _acce_color[4];
    /** 各色要素のループカウント（2で拡大縮小ワンセット、1ならば拡大or縮小の片道） */
    int _one_way_cnt[4];
    /** 各色要素のストップする予定のループカウント */
    int _stop_one_way_num[4];
    /** 各色要素のスケーリング方法 */
    GgafDx9ColoringMethod _method[4];

    /** ビート時、各色要素の三角波の波形でスケーリングのアタックフレーム数 */
    frame _beat_attack_frames[4];
    /** ビート時、各色要素の三角波の波形でスケーリングのレストフレーム数 */
    frame _beat_rest_frames[4];
    /** ビート時、各色要素のスケーリングに費やすフレーム数 */
    frame _beat_target_frames[4];
    /** ビート時、各色要素のアタックから下限までのフレーム数 */
    frame _beat_down_frames[4];
    /** ビート時、内部カウンター */
    frame _beat_frame_count[4];
    /** ビート時、内部進捗番号 */
    int _beat_progres[4];

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用対象のActor
     */
    GgafDx9Colorist(GgafDx9GeometricActor* prm_pActor);

    /**
     * 強度を相対指定（全色要素指定）
     * @param prm_color_diff 強度値増分
     */
    void addColor(int prm_color_diff) {
        for (int c = 0; c < 3; c++) {
            addColor(c, prm_color_diff);
        }
    }
    /**
     * 強度を相対指定（色要素単位で指定）
     * @param prm_c 色要素
     * @param prm_color_diff 強度値増分
     */
    void addColor(int prm_c, int prm_color_diff) {
        setColor(prm_c, _color[prm_c] + prm_color_diff);
    }

    /**
     * 強度を絶対指定（全色要素指定）
     * @param prm_color 強度値
     */
    void setColor(int prm_color) {
        for (int c = 0; c < 3; c++) {
            setColor(c, prm_color);
        }
    }

    /**
     * 強度を絶対指定（色要素単位で指定）
     * @param prm_c 色要素
     * @param prm_color 強度値
     */
    void setColor(int prm_c, int prm_color) {
        //_TRACE_("setColor ["<<prm_c<<"]prm_color="<<prm_color);
        //_TRACE_("setColor _bottom_color["<<prm_c<<"]="<<_bottom_color[prm_c]<<"/_top_color["<<prm_c<<"]="<<_top_color[prm_c]<<"");
        if (_top_color[prm_c] < prm_color) {
            _color[prm_c] = _top_color[prm_c];
        } else if (_bottom_color[prm_c] > prm_color) {
            _color[prm_c] = _bottom_color[prm_c];
        } else {
            _color[prm_c] = prm_color;
        }
        //_TRACE_("setColor _color ["<<prm_c<<"] _color[prm_c]="<<prm_color);
    }
    /**
     * 強度の上限下限を設定（全色要素指定） .
     * 引数の大小は気にせず渡して(内部で自動判別)
     * @param prm_color1 強度値1
     * @param prm_color2 強度値2
     */
    void forceColorRange(int prm_color1, int prm_color2) {
        for (int c = 0; c < 3; c++) {
            forceColorRange(c, prm_color1, prm_color2);
            setColor(c, _color[c]);
        }
    }
    /**
     * 強度の上限下限を設定（色要素単位で指定）
     * @param prm_c 色要素
     * @param prm_color1 強度値1
     * @param prm_color2 強度値2
     */
    void forceColorRange(int prm_c, int prm_color1, int prm_color2) {
        if (prm_color1 < prm_color2) {
            _bottom_color[prm_c] = prm_color1;
            _top_color[prm_c] = prm_color2;
        } else {
            _bottom_color[prm_c] = prm_color2;
            _top_color[prm_c] = prm_color1;
        }
        //_TRACE_("forceColorRange _bottom_color["<<prm_c<<"]="<<_bottom_color[prm_c]<<"/_top_color["<<prm_c<<"]="<<_top_color[prm_c]<<"");
    }
    /**
     * 強度をリセット （全色要素指定） .
     * 本オブジェクト(GgafDx9Colorist)によって変化さえる前の
     * 初期の大きさに戻す。
     */
    void setColorToBottom() {
        for (int c = 0; c < 3; c++) {
            setColorToBottom(c);
        }
    }
    /**
     * 強度をリセット （色要素単位で指定）
     * 本オブジェクト(GgafDx9Colorist)によって変化さえる前の
     * 初期の大きさに戻す。
     * @param prm_c 色要素
     */
    void setColorToBottom(int prm_c) {
        _color[prm_c] = _bottom_color[prm_c];
    }

    void setColorToTop() {
        for (int c = 0; c < 3; c++) {
            setColorToTop(c);
        }
    }
    void setColorToTop(int prm_c) {
        _color[prm_c] = _top_color[prm_c];
    }

    /**
     * スケーリングを停止させる。 （全色要素指定） .
     */
    void stopImmediately();
    /**
     * スケーリングを停止させる。 （色要素単位で指定）.
     * @param prm_c
     */
    void stopImmediately(int prm_c);

    /**
     * 片道等速スケーリング（全色要素・持続フレーム数指定） .
     * 目標の強度へ一定速度でスケーリングする
     * @param prm_target_color 目標強度
     * @param prm_spend_frame 費やすフレーム数
     */
    void intoTargetColorLinerUntil(int prm_target_color, frame prm_spend_frame);

    /**
     * 片道等速スケーリング（色要素単位・持続フレーム数指定） .
     * 目標の強度へ一定速度でスケーリングする。
     * @param prm_c 色要素
     * @param prm_target_color 目標強度
     * @param prm_spend_frame 費やすフレーム数
     */
    void intoTargetColorLinerUntil(int prm_c, int prm_target_color, frame prm_spend_frame);

    /**
     * 片道等速スケーリング（全色要素・強度速度指定） .
     * 目標の強度へ一定速度でスケーリングする
     * @param prm_target_color 目標強度
     * @param prm_velo_color 毎フレーム加算する強度差分(>0.0)。正の強度を指定する事。加算か減算かは自動判断する。
     */
    void intoTargetColorLinerStep(int prm_target_color, int prm_velo_color);

    /**
     * 片道等速スケーリング（色要素単位・強度速度指定） .
     * 目標の強度へ一定速度でスケーリングする（強度差分指定） .
     * @param prm_c 色要素
     * @param prm_target_color 目標強度
     * @param prm_velo_color 毎フレーム加算する強度差分(>0.0)。正の強度を指定する事。加算か減算かは自動判断する。
     */
    void intoTargetColorLinerStep(int prm_c, int prm_target_color, int prm_velo_color);

    /**
     * 片道加速スケーリング（全色要素・強度速度・強度加速度指定） .
     * 目標の強度へ加速指定でスケーリングする
     * 強度加速度を0に指定すると intoTargetColorLinerStep とほぼ同じ意味になる。
     * intoTargetColorLinerStep の第３引数は正負を気にすること無いが、本メソッドは正負の自動判定はしない（できない）。
     * 強度加速度が正の場合、目標強度を超えるとスケーリング終了。
     * 強度加速度が負の場合、目標強度を下回るとスケーリング終了。
     * @param prm_target_color 目標強度
     * @param prm_velo_color 初期強度速度
     * @param prm_acce_color 強度加速度
     */
    void intoTargetColorAcceStep(int prm_target_color, int prm_velo_color, int prm_acce_color);

    /**
     * 片道加速スケーリング（色要素単位・強度速度・強度加速度指定） .
     * 目標の強度へ加速指定でスケーリングする（強度速度、強度加速度差指定） .
     * 強度加速度を0に指定すると intoTargetColorLinerStep とほぼ同じ意味になる。
     * intoTargetColorLinerStep の第３引数は正負を気にすること無いが、本メソッドは正負の自動判定はしない（できない）。
     * @param prm_c 色要素
     * @param prm_target_color 目標強度
     * @param prm_velo_color 初期強度速度
     * @param prm_acce_color 強度加速度
     */
    void intoTargetColorAcceStep(int prm_c, int prm_target_color, int prm_velo_color, int prm_acce_color);

    /**
     * 反復等速スケーリング（全色要素・フレーム数指定） .
     * 目標の強度へ一定速度でスケーリングし、一定速度で元に戻る。これをループ指定する。（１ループのフレーム数指定） .
     * @param prm_beat_target_frames １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_beat_num ループする回数(0.5 回単位で指定可能)
     */
    void loopLiner(frame prm_beat_target_frames, float prm_beat_num);

    /**
     * 反復等速スケーリング（色要素単位・フレーム数指定）
     * 目標の強度へ一定速度でスケーリングし、一定速度で元に戻る。
     * これをループ指定する。（１ループのフレーム数指定） .
     * @param prm_c 色要素
     * @param prm_beat_target_frames １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_beat_num ループする回数(0.5 回単位で指定可能)
     */
    void loopLiner(int prm_c, frame prm_beat_target_frames, float prm_beat_num);

    /**
     * 三角波の波形でスケーリングする。（全色要素指定）.
     * <PRE>
     * �C  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
     *            /＼                     /＼
     *           /   ＼                  /   ＼
     *          /      ＼               /      ＼
     *         /         ＼            /         ＼
     *        /            ＼         /            ＼
     * �D  ＿/               ＼＿＿＿/               ＼＿
     *
     *       ←�A→            ←�B→
     *       ←──── �@ ────→
     * </PRE>
     * ＜必要な設定値＞<BR>
     * �@ １ループのフレーム数<BR>
     * �A アタックまでのフレーム数<BR>
     * �B 休憩フレーム数<BR>
     * �C 強度上限(_top_color[色要素] 配列が保持)<BR>
     * �D 強度下限(_bottom_color[色要素] 配列が保持)<BR>
     * @param prm_beat_target_frames 上図で�@のフレーム数
     * @param prm_attack_frames 上図で�Aのフレーム数
     * @param prm_rest_frames 上図で�Bのフレーム数
     * @param prm_beat_num ループ数(-1で無限)
     */
    void beat(frame prm_beat_target_frames,
              frame prm_attack_frames,
              frame prm_rest_frames,
              float prm_beat_num);
    /**
     * 三角波の波形でスケーリングする。（色要素指定）.
     * @param prm_c 色要素
     * @param prm_beat_target_frames 上図で�@のフレーム数
     * @param prm_attack_frames 上図で�Aのフレーム数
     * @param prm_rest_frames 上図で�Bのフレーム数
     * @param prm_beat_num ループ数(-1で無限)
     */
    void beat(int prm_c,
              frame prm_beat_target_frames,
              frame prm_attack_frames,
              frame prm_rest_frames,
              float prm_beat_num);

    /**
     * 毎フレームの振る舞いメソッド。<BR>
     * 本クラスの機能を利用する場合は、このメソッドを<BR>
     * 毎フレーム実行することが必要。
     */
    virtual void behave();

    virtual ~GgafDx9Colorist();
};

}
#endif /*GGAFDX9COLORIST_H_*/

