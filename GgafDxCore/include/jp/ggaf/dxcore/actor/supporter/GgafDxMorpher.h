#ifndef GGAFDXMORPHER_H_
#define GGAFDXMORPHER_H_
namespace GgafDxCore {


/**
 * モーフィング支援クラス .
 * GgafDxMorphMeshActor のメンバの<BR>
 * 重み _weight[] <BR>
 * を簡単に操作するために設計。<BR>
 * 尚 _weight[] は、[0]は未使用、[1]～[n]がモーフターゲット1～nの重み <BR>
 * TODO:GgafDxScaler,GgafDxMorpher,GgafDxTextureBlinker を共通化する。
 * @version 1.00
 * @since 2009/05/11
 * @author Masatoshi Tsuge
 */
class GgafDxMorpher : public GgafCore::GgafObject {

public:
    /** [r]対象アクター */
    GgafDxMorphMeshActor* _pActor;
    /** [r/w]各モーフターゲットの重み(0.0 ～ 1.0) */
    float _weight[MAX_MORPH_TARGET+1];
    /** [r/w]各モーフターゲットへ設定された目標の重み(0.0 ～ 1.0) */
    float _target_weight[MAX_MORPH_TARGET+1];
    /** [r/w]各モーフターゲットへ重み上限(0.0 ～ 1.0) */
    float _top_weight[MAX_MORPH_TARGET+1];
    /** [r/w]各モーフターゲットへ重み下限(0.0 ～ 1.0) */
    float _bottom_weight[MAX_MORPH_TARGET+1];
    /** [r/w]各モーフターゲットへの毎フレーム重み速度 */
    float _velo_weight[MAX_MORPH_TARGET+1];
    /** [r/w]各モーフターゲットへの毎フレーム重み加速度 */
    float _acce_weight[MAX_MORPH_TARGET+1];
    int _halfloop_cnt[MAX_MORPH_TARGET+1];
    /** [r]停止予定の片道ループ数 */
    int _stop_halfloop_num[MAX_MORPH_TARGET+1];
    /** [r]ループの振る舞い種別 */
    GgafDxMorphingMethod _method[MAX_MORPH_TARGET+1];

    /** [r]ループ重みの１ループフレーム幅 */
    frame _beat_target_frames[MAX_MORPH_TARGET+1];
    /** [r]ループ重みの開始相対フレーム */
    frame _frame_of_beat_begin[MAX_MORPH_TARGET+1];
    /** [r]三角波ループ重みのアタックまでのフレーム */
    frame _beat_attack_frames[MAX_MORPH_TARGET+1];
    /** [r]三角波ループ重みの休息フレーム幅 */
    frame _beat_rest_frames[MAX_MORPH_TARGET+1];
    /** [r]ビート時、各軸のアタックから下限までのフレーム数 */
    frame _beat_down_frames[MAX_MORPH_TARGET+1];
    /** [r]ビート時、内部カウンター */
    frame _beat_frame_count[MAX_MORPH_TARGET+1];
    /** [r]ビート時、内部進捗番号 */
    int _beat_progres[MAX_MORPH_TARGET+1];

public:
    /**
     * コンストラクタ<BR>
     * @param	prm_pActor	適用Actor
     */
    GgafDxMorpher(GgafDxMorphMeshActor* prm_pActor);

    /**
     * リセット
     */
    void reset();

    /**
     * モーフターゲットの重みの上限と下限を設定し重みの値を制限する .
     * @param prm_target_mesh_no モーフターゲットメッシュNO
     * @param prm_weight1 重み１(上限 or 下限)
     * @param prm_weight2 重み２(下限 or 上限)
     */
    void forceWeightRange(int prm_target_mesh_no, float prm_weight1, float prm_weight2) {
        if (prm_weight1 < prm_weight2) {
            _top_weight[prm_target_mesh_no] = prm_weight2;
            _bottom_weight[prm_target_mesh_no] = prm_weight1;
        } else {
            _top_weight[prm_target_mesh_no] = prm_weight1;
            _bottom_weight[prm_target_mesh_no] = prm_weight2;
        }
    }

    /**
     * モーフターゲットの重みを直接指定 .
     * @param prm_target_mesh_no モーフターゲットメッシュNO
     * @param prm_weight 重み
     */
    void setWeight(int prm_target_mesh_no, float prm_weight) {
        if (_top_weight[prm_target_mesh_no] < prm_weight) {
            _weight[prm_target_mesh_no] = _top_weight[prm_target_mesh_no];
        } else if (_bottom_weight[prm_target_mesh_no] > prm_weight) {
            _weight[prm_target_mesh_no] = _bottom_weight[prm_target_mesh_no];
        } else {
            _weight[prm_target_mesh_no] = prm_weight;
        }
    }

    /**
     * モーフターゲットの重みを加算(負で減算) .
     * 上限下限は保証される。
     * @param prm_target_mesh_no
     * @param prm_weight
     */
    void addWeight(int prm_target_mesh_no, float prm_weight_offset) {
        setWeight(prm_target_mesh_no, _weight[prm_target_mesh_no] + prm_weight_offset);
    }

    /**
     * モーフターゲットの重みを下限値に設定 .
     * @param prm_target_mesh_no モーフターゲットメッシュNO
     */
    void setWeightToBottom(int prm_target_mesh_no) {
        _weight[prm_target_mesh_no] = _bottom_weight[prm_target_mesh_no];
    }

    /**
     * モーフターゲットの重みを上限値に設定 .
     * @param prm_target_mesh_no モーフターゲットメッシュNO
     */
    void setWeightToTop(int prm_target_mesh_no) {
        _weight[prm_target_mesh_no] = _top_weight[prm_target_mesh_no];
    }

    /**
     * モーフィングを停止する .
     * @param prm_target_mesh_no モーフィング中のモーフターゲットメッシュNO
     */
    void stopImmed(int prm_target_mesh_no);

    /**
     * モーフしているか調べる .
     * 各モーフターゲットへの重みが、1つでも0より大きければ true
     * @return true:モーフしている/false:モーフしない
     */
    bool isMorph();

    /**
     * モーフターゲットへ一定速度でモーフィングする（フレーム数指定） .
     * @param prm_target_mesh_no モーフターゲットメッシュNO
     * @param prm_target_weight ターゲットメッシュの目標重み(0.0～1.0)
     * @param prm_spend_frame 費やすフレーム数
     */
    void intoTargetLinerUntil(int prm_target_mesh_no, float prm_target_weight, frame prm_spend_frame);

    /**
     * モーフターゲットへ一定速度でモーフィングする（重み差分指定） .
     * @param prm_target_mesh_no モーフターゲットメッシュNO
     * @param prm_target_weight ターゲットメッシュの目標重み(0.0～1.0)
     * @param prm_velo_weight 毎フレーム加算する重み差分(>0.0)。正の重みを指定する事。加算か減算かは自動判断する。
     */
    void intoTargetLinerStep(int prm_target_mesh_no, float prm_target_weight, float prm_velo_weight);

    /**
     * モーフターゲットへ加速指定でモーフィングする（重み速度、重み加速度差指定） .
     * 重み加速度を0に指定すると intoTargetLinerStep とほぼ同じ意味になる。
     * intoTargetLinerStep の第３引数は正負を気にすること無いが、本メソッドは正負の自動判定はしない（加速度だからできない）。
     * @param prm_target_mesh_no モーフターゲットメッシュNO
     * @param prm_target_weight ターゲットメッシュの目標重み(0.0～1.0)
     * @param prm_velo_weight 初期重み速度
     * @param prm_acce_weight 重み加速度
     */
    void intoTargetAcceStep(int prm_target_mesh_no, float prm_target_weight, float prm_velo_weight, float prm_acce_weight);

    /**
     * モーフターゲットへ一定速度でモーフィングし、一定速度で元に戻る。これをループ指定する。（１ループのフレーム数指定） .
     * @param prm_target_mesh_no モーフターゲットメッシュNO
     * @param prm_beat_target_frames １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_beat_num ループする回数(0.5 回単位で指定可能)
     */
    void loopLiner(int prm_target_mesh_no, frame prm_beat_target_frames, float prm_beat_num = -1);

    /**
     * 三角波の波形を重みとしてモーフィングする。 .
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
     * ④ 重み上限(_top_weight[prm_target_mesh_no] が保持)<BR>
     * ⑤ 重み下限(_bottom_weight[prm_target_mesh_no] が保持)<BR>
     * <BR>
     * @param prm_target_mesh_no モーフターゲットメッシュNO
     * @param prm_beat_target_frames 上図で①のフレーム数
     * @param prm_attack_frames 上図で②のフレーム数
     * @param prm_rest_frames 上図で③のフレーム数
     * @param prm_beat_num ループ数(-1で無限)
     */
    void beat(int prm_target_mesh_no,
              frame prm_beat_target_frames,
              frame prm_attack_frames,
              frame prm_rest_frames,
              float prm_beat_num = -1);

    /**
     * 毎フレームの振る舞いメソッド。<BR>
     * 本クラスのモーフィング機能を利用する場合は、<BR>
     * このメソッドを毎フレーム実行することが必要です。 <BR>
     */
    virtual void behave();

    virtual ~GgafDxMorpher();
};

}
#endif /*GGAFDXMORPHER_H_*/

