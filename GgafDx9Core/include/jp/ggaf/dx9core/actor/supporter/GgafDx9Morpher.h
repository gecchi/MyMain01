#ifndef GGAFDX9MORPHER_H_
#define GGAFDX9MORPHER_H_
namespace GgafDx9Core {


/**
 * モーフィング支援クラス .
 * GgafDx9MorphMeshActor のメンバの<BR>
 * 重み _weight[] <BR>
 * を簡単に操作するために設計。<BR>
 * 尚 _weight[] は、[0]は未使用、[1]〜[n]がモーフターゲット1〜nの重み <BR>
 * TODO:GgafDx9Scaler,GgafDx9Morpher,GgafDx9TextureBlinker を共通化する。
 * @version 1.00
 * @since 2009/05/11
 * @author Masatoshi Tsuge
 */
class GgafDx9Morpher : public GgafCore::GgafObject {

public:
    /** 対象アクター */
    GgafDx9MorphMeshActor* _pActor;
    /** 各モーフターゲットの重み(0.0 〜 1.0) */
    float _weight[MAX_MORPH_TARGET+1];
    /** 各モーフターゲットへ設定された目標の重み(0.0 〜 1.0) */
    float _target_weight[MAX_MORPH_TARGET+1];
    /** 各モーフターゲットへ重み上限(0.0 〜 1.0) */
    float _top_weight[MAX_MORPH_TARGET+1];
    /** 各モーフターゲットへ重み下限(0.0 〜 1.0) */
    float _bottom_weight[MAX_MORPH_TARGET+1];
    /** 各モーフターゲットへの毎フレーム重み速度 */
    float _velo_weight[MAX_MORPH_TARGET+1];
    /** 各モーフターゲットへの毎フレーム重み加速度 */
    float _acce_weight[MAX_MORPH_TARGET+1];
    int _halfloop_cnt[MAX_MORPH_TARGET+1];
    /** 停止予定の片道ループ数 */
    int _stop_halfloop_num[MAX_MORPH_TARGET+1];
    /** ループの振る舞い種別 */
    GgafDx9MorphingMethod _method[MAX_MORPH_TARGET+1];


    /** ループ重みの１ループフレーム幅 */
    frame _beat_target_frames[MAX_MORPH_TARGET+1];
    /** ループ重みの開始相対フレーム */
    frame _frame_of_beat_begin[MAX_MORPH_TARGET+1];
    /** 三角波ループ重みのアタックまでのフレーム */
    frame _beat_attack_frames[MAX_MORPH_TARGET+1];
    /** 三角波ループ重みの休息フレーム幅 */
    frame _beat_rest_frames[MAX_MORPH_TARGET+1];
    /** ビート時、各軸のアタックから下限までのフレーム数 */
    frame _beat_down_frames[MAX_MORPH_TARGET+1];
    /** ビート時、内部カウンター */
    frame _beat_frame_count[MAX_MORPH_TARGET+1];
    /** ビート時、内部進捗番号 */
    int _beat_progres[MAX_MORPH_TARGET+1];

    /**
     * コンストラクタ<BR>
     * @param	prm_pActor	適用Actor
     */
    GgafDx9Morpher(GgafDx9MorphMeshActor* prm_pActor);

    /**
     * モーフターゲットの重みの上限と下限を設定し重みの値を制限する .
     * @param prm_target_mesh モーフターゲットメッシュNO
     * @param prm_weight1 重み１(上限 or 下限)
     * @param prm_weight2 重み２(下限 or 上限)
     */
    void forceWeightRange(int prm_target_mesh, float prm_weight1, float prm_weight2) {
        if (prm_weight1 < prm_weight2) {
            _top_weight[prm_target_mesh] = prm_weight2;
            _bottom_weight[prm_target_mesh] = prm_weight1;
        } else {
            _top_weight[prm_target_mesh] = prm_weight1;
            _bottom_weight[prm_target_mesh] = prm_weight2;
        }
    }

    /**
     * モーフターゲットの重みを直接指定 .
     * @param prm_target_mesh モーフターゲットメッシュNO
     * @param prm_weight 重み
     */
    void setWeight(int prm_target_mesh, float prm_weight) {
        if (_top_weight[prm_target_mesh] < prm_weight) {
            _weight[prm_target_mesh] = _top_weight[prm_target_mesh];
        } else if (_bottom_weight[prm_target_mesh] > prm_weight) {
            _weight[prm_target_mesh] = _bottom_weight[prm_target_mesh];
        } else {
            _weight[prm_target_mesh] = prm_weight;
        }
    }

    /**
     * モーフターゲットの重みを下限値に設定 .
     * @param prm_target_mesh モーフターゲットメッシュNO
     */
    void setWeightToBottom(int prm_target_mesh) {
        _weight[prm_target_mesh] = _bottom_weight[prm_target_mesh];
    }

    /**
     * モーフターゲットの重みを上限値に設定 .
     * @param prm_target_mesh モーフターゲットメッシュNO
     */
    void setWeightToTop(int prm_target_mesh) {
        _weight[prm_target_mesh] = _top_weight[prm_target_mesh];
    }

    /**
     * モーフィングを停止する
     * @param prm_target_mesh モーフィング中のモーフターゲットメッシュNO
     */
    void stopImmediately(int prm_target_mesh);

    /**
     * モーフターゲットへ一定速度でモーフィングする（フレーム数指定） .
     * @param prm_target_mesh モーフターゲットメッシュNO
     * @param prm_target_weight ターゲットメッシュの目標重み(0.0〜1.0)
     * @param prm_spend_frame 費やすフレーム数
     */
    void intoTargetLinerUntil(int prm_target_mesh, float prm_target_weight, frame prm_spend_frame);

    /**
     * モーフターゲットへ一定速度でモーフィングする（重み差分指定） .
     * @param prm_target_mesh モーフターゲットメッシュNO
     * @param prm_target_weight ターゲットメッシュの目標重み(0.0〜1.0)
     * @param prm_velo_weight 毎フレーム加算する重み差分(>0.0)。正の重みを指定する事。加算か減算かは自動判断する。
     */
    void intoTargetLinerStep(int prm_target_mesh, float prm_target_weight, float prm_velo_weight);

    /**
     * モーフターゲットへ加速指定でモーフィングする（重み速度、重み加速度差指定） .
     * 重み加速度を0に指定すると intoTargetLinerStep とほぼ同じ意味になる。
     * intoTargetLinerStep の第３引数は正負を気にすること無いが、本メソッドは正負の自動判定はしない（できない）。
     * @param prm_target_mesh モーフターゲットメッシュNO
     * @param prm_target_weight ターゲットメッシュの目標重み(0.0〜1.0)
     * @param prm_velo_weight 初期重み速度
     * @param prm_acce_weight 重み加速度
     */
    void intoTargetAcceStep(int prm_target_mesh, float prm_target_weight, float prm_velo_weight, float prm_acce_weight);

    /**
     * モーフターゲットへ一定速度でモーフィングし、一定速度で元に戻る。これをループ指定する。（１ループのフレーム数指定） .
     * @param prm_target_mesh モーフターゲットメッシュNO
     * @param prm_beat_target_frames １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_beat_num ループする回数(0.5 回単位で指定可能)
     */
    void loopLiner(int prm_target_mesh, frame prm_beat_target_frames, float prm_beat_num = -1);

    /**
     * 三角波の波形を重みとしてモーフィングする。 .
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
     * �C 重み上限(_top_weight[prm_target_mesh] が保持)<BR>
     * �D 重み下限(_bottom_weight[prm_target_mesh] が保持)<BR>
     * <BR>
     * @param prm_target_mesh モーフターゲットメッシュNO
     * @param prm_beat_target_frames 上図で�@のフレーム数
     * @param prm_attack_frames 上図で�Aのフレーム数
     * @param prm_rest_frames 上図で�Bのフレーム数
     * @param prm_beat_num ループ数(-1で無限)
     */
    void beat(int prm_target_mesh,
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

    virtual ~GgafDx9Morpher();
};

}
#endif /*GGAFDX9MORPHER_H_*/

