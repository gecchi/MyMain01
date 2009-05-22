#ifndef GGAFDX9GEOMETRYSCALER_H_
#define GGAFDX9GEOMETRYSCALER_H_
namespace GgafDx9Core {

enum Method {
    NOSCALE,
    TARGET_SCALE_LINER,
    BEAT_SCALE_LINER,
    BEAT_SCALE_TRIANGLEWAVE,
    TARGET_SCALE_SIN,
    BEAT_SCALE_SIN,
    TARGET_SCALE_ACCELERATION,
    BEAT_SCALE_PARABOLA,
    TARGET_SCALE_PARABOLA_REV,
    BEAT_SCALE_PARABOLA_REV
};

/**
 * 拡大縮小支援クラス.
 * GgafDx9UntransformedActor のメンバの<BR>
 * _SX , _SY, _SZ  ･･･ アクターのスケール<BR>
 * を、簡単に操作するために設計した。<BR>
 */
class GgafDx9GeometryScaler : public GgafCore::GgafObject {

public: //_SX , _SY, _SZ 操作関連 //////////////////////////////////////////////
    /** 対象アクター */
    GgafDx9UntransformedActor* _pActor;

    /** スケール(1000 で 1倍) */
    int _scale[3]; //[0]:X軸スケール、[1]:Y軸スケール、[1]:Z軸スケール
    /** 目標のスケール */
    int _target_scale[3];
    /** スケール上限 */
    int _top_scale[3];
    /** スケール下限 */
    int _bottom_scale[3];
    /** 毎フレームのスケールの増分 */
    int _velo_scale[3];
    /** 毎フレームのスケールの増分の増分 */
    int _acce_scale[3];
    /** 三角波の波形でスケーリングのアタックフレーム */
    DWORD _beat_attack_frame[3];
    /** 三角波の波形でスケーリングのレストフレーム */
    DWORD _beat_rest_frame[3];
    /** スケーリングに費やすフレーム数 */
    DWORD _beat_spend_frame[3];
    /** スケーリングを開始したフレーム */
    DWORD _beat_begin_frame[3];
    /** ループカウント（2で拡大縮小ワンセット、1ならば拡大or縮小の片道） */
    int _one_way_cnt[3];
    /** ストップする予定のループカウント */
    int _stop_one_way_num[3];
    /** スケーリング方法 */
    Method _method[3];

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用Actor
     */
    GgafDx9GeometryScaler(GgafDx9UntransformedActor* prm_pActor);

    void increaseScale(int prm_scale_diff) {
        for (int axis = 0; axis < 3; axis++) {
            increaseScale(axis, prm_scale_diff);
        }
    }

    void increaseScale(int prm_axis, int prm_scale_diff) {
        setScale(prm_axis, _scale[prm_axis] + prm_scale_diff);
    }


    void setScale(int prm_scale) {
        for (int axis = 0; axis < 3; axis++) {
            setScale(axis, prm_scale);
        }
   }

    void setScale(int prm_axis, int prm_scale) {
        if (_top_scale[prm_axis] < prm_scale) {
            _scale[prm_axis] = _top_scale[prm_axis];
        } else if (_bottom_scale[prm_axis] > prm_scale) {
            _scale[prm_axis] = _bottom_scale[prm_axis];
        } else {
            _scale[prm_axis] = prm_scale;
        }
    }
    /**
     * スケーリングの上限下限を設定（全軸指定）
     * @param prm_scale1
     * @param prm_scale2
     */
    void setScaleRange(int prm_scale1, int prm_scale2) {
        for (int axis = 0; axis < 3; axis++) {
            setScaleRange(axis, prm_scale1, prm_scale2);
        }
    }
    /**
     * スケーリングの上限下限を設定（軸ごとに指定）
     * @param prm_axis 軸
     * @param prm_scale1
     * @param prm_scale2
     */
    void setScaleRange(int prm_axis, int prm_scale1, int prm_scale2) {
        if (prm_scale1 < prm_scale2) {
            _bottom_scale[prm_axis] = prm_scale1;
            _top_scale[prm_axis] = prm_scale2;
        } else {
            _bottom_scale[prm_axis] = prm_scale1;
            _top_scale[prm_axis] = prm_scale2;
        }
    }

    void resetScale() {
        for (int axis = 0; axis < 3; axis++) {
            resetScale(axis);
        }
    }
    void resetScale(int prm_axis) {
        _scale[prm_axis] = _bottom_scale[prm_axis];
    }

    void resetScaleTop() {
        for (int axis = 0; axis < 3; axis++) {
            resetScaleTop(axis);
        }
    }
    void resetScaleTop(int prm_axis) {
        _scale[prm_axis] = _top_scale[prm_axis];
    }


    void stopImmediately();
    void stopImmediately(int prm_axis);

    /**
     * 目標のスケールへ一定速度でスケーリングする（フレーム数指定） .
     * @param prm_target_scale 目標スケール
     * @param prm_spend_frame 費やすフレーム数
     */
    void intoTargetScaleLinerUntil(int prm_target_scale, DWORD prm_spend_frame);

    /**
     * 目標のスケールへ一定速度でスケーリングする（フレーム数指定） .
     * @param prm_axis 軸
     * @param prm_target_scale 目標スケール
     * @param prm_spend_frame 費やすフレーム数
     */
    void intoTargetScaleLinerUntil(int prm_axis, int prm_target_scale, DWORD prm_spend_frame);

    /**
     * 目標のスケールへ一定速度でスケーリングする（スケール差分指定） .
     * @param prm_target_scale 目標スケール
     * @param prm_velo_scale 毎フレーム加算するスケール差分(>0.0)。正のスケールを指定する事。加算か減算かは自動判断する。
     */
    void intoTargetScaleLinerStep(int prm_target_scale, int prm_velo_scale);

    /**
     * 目標のスケールへ一定速度でスケーリングする（スケール差分指定） .
     * @param prm_axis 軸
     * @param prm_target_scale 目標スケール
     * @param prm_velo_scale 毎フレーム加算するスケール差分(>0.0)。正のスケールを指定する事。加算か減算かは自動判断する。
     */
    void intoTargetScaleLinerStep(int prm_axis, int prm_target_scale, int prm_velo_scale);

    /**
     * 目標のスケールへ加速指定でスケーリングする（スケール速度、スケール加速度差指定） .
     * スケール加速度を0に指定すると intoTargetScaleLinerStep とほぼ同じ意味になる。
     * intoTargetScaleLinerStep の第３引数は正負を気にすること無いが、本メソッドは正負の自動判定はしない（できない）。
     * @param prm_target_scale 目標スケール
     * @param prm_velo_scale 初期スケール速度
     * @param prm_acce_scale スケール加速度
     */
    void intoTargetScaleAccelerationStep(int prm_target_scale, int prm_velo_scale, int prm_acce_scale);

    /**
     * 目標のスケールへ加速指定でスケーリングする（スケール速度、スケール加速度差指定） .
     * スケール加速度を0に指定すると intoTargetScaleLinerStep とほぼ同じ意味になる。
     * intoTargetScaleLinerStep の第３引数は正負を気にすること無いが、本メソッドは正負の自動判定はしない（できない）。
     * @param prm_axis 軸
     * @param prm_target_scale 目標スケール
     * @param prm_velo_scale 初期スケール速度
     * @param prm_acce_scale スケール加速度
     */
    void intoTargetScaleAccelerationStep(int prm_axis, int prm_target_scale, int prm_velo_scale, int prm_acce_scale);

    /**
     * 目標のスケールへ一定速度でスケーリングし、一定速度で元に戻る。これをループ指定する。（１ループのフレーム数指定） .
     * @param prm_beat_spend_frame １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_beat_num ループする回数(0.5 回単位で指定可能)
     */
    void beatLiner(DWORD prm_beat_spend_frame, float prm_beat_num);

    /**
     * 目標のスケールへ一定速度でスケーリングし、一定速度で元に戻る。これをループ指定する。（１ループのフレーム数指定） .
     * @param prm_axis 軸
     * @param prm_beat_spend_frame １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_beat_num ループする回数(0.5 回単位で指定可能)
     */
    void beatLiner(int prm_axis, DWORD prm_beat_spend_frame, float prm_beat_num);

    /**
     * 三角波の波形でスケーリングする。.
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
     * ④ スケール上限(_top_scale[prm_axis] が保持)<BR>
     * ⑤ スケール下限(_bottom_scale[prm_axis] が保持)<BR>
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
     * 三角波の波形でスケーリングする。.
     * @param prm_axis 軸
     * @param prm_beat_spend_frame 上図で①のフレーム数
     * @param prm_attack_frame 上図で②のフレーム数
     * @param prm_rest_frame 上図で③のフレーム数
     * @param prm_beat_num ループ数(-1で無限)
     */
    void beat(int prm_axis,
              DWORD prm_beat_spend_frame,
              DWORD prm_attack_frame,
              DWORD prm_rest_frame,
              float prm_beat_num);



    /**
     * 毎フレームのActorの振る舞い。<BR>
     * 本クラスを利用する場合は、このbehave() を毎フレーム実行します。<BR>
     */
    virtual void behave();

    virtual ~GgafDx9GeometryScaler();
};

}
#endif /*GGAFDX9GEOMETRYSCALER_H_*/

