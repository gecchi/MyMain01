#ifndef GGAFDX9MORPHER_H_
#define GGAFDX9MORPHER_H_
namespace GgafDx9Core {

enum GgafDx9MorphMethod {
    NOMORPH,
    TARGET_LINER,
    LOOP_LINER,
    LOOP_TRIANGLEWAVE,
    TARGET_SIN,
    LOOP_SIN,
    TARGET_PARABOLA,
    LOOP_PARABOLA,
    TARGET_PARABOLA_REV,
    LOOP_PARABOLA_REV
};

class GgafDx9Morpher : public GgafCore::GgafObject {

public:
    /** 対象アクター */
    GgafDx9MorphMeshActor* _pActor;

    float _inc_weight[10];
    float _target_weight[10];
    float _top_weight[10];
    float _bottom_weight[10];
    DWORD _loop_attack_frame[10];
    DWORD _loop_rest_frame[10];
    DWORD _loop_spend_frame[10];
    DWORD _loop_begin_frame[10];
    int _halfloop_cnt[10];
    int _stop_halfloop_num[10];

    GgafDx9MorphMethod _method[10];

    /**
     * コンストラクタ<BR>
     * @param	prm_pActor	適用Actor
     */
    GgafDx9Morpher(GgafDx9MorphMeshActor* prm_pActor);

    void stopImmediately(int prm_target_mesh);

    /**
     * ターゲットへ一定速度でモーフする（フレーム数指定） .
     * @param prm_target_mesh ターゲットメッシュNO
     * @param prm_target_weight ターゲットメッシュの目標重み
     * @param prm_spend_frame 費やすフレーム数
     */
    void intoTargetLinerUntil(int prm_target_mesh, float prm_target_weight, DWORD prm_spend_frame);

    /**
     * ターゲットへ一定速度でモーフする（重み差分指定） .
     * @param prm_target_mesh ターゲットメッシュNO
     * @param prm_target_weight ターゲットメッシュの目標重み
     * @param prm_inc_weight 毎フレーム加算する重み差分(>0.0)。正の重みを指定する事。加算か減算かは自動判断する。
     */
    void intoTargetLinerStep(int prm_target_mesh, float prm_target_weight, float prm_inc_weight);

    /**
     * ターゲットへ一定速度でモーフし、一定速度で元に戻る。これをループ指定する。（１ループのフレーム数指定） .
     * @param prm_target_mesh ターゲットメッシュNO
     * @param prm_loop_spend_frame １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_loop_num ループする回数(0.5 回単位で指定可能)
     */
    void loopLiner(int prm_target_mesh, DWORD prm_loop_spend_frame, float prm_loop_num = -1);

    /**
     * 三角波の波形でモーフする。.
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
     * ④ 重み上限(_top_weight[prm_target_mesh] が保持)<BR>
     * ⑤ 重み下限(_bottom_weight[prm_target_mesh] が保持)<BR>
     * <BR>
     * @param prm_target_mesh ターゲットメッシュNO
     * @param prm_loop_spend_frame 上図で①のフレーム数
     * @param prm_attack_frame 上図で②のフレーム数
     * @param prm_rest_frame 上図で③のフレーム数
     * @param prm_loop_num ループ数(-1で無限)
     */
    void loopTriangleWave(int prm_target_mesh,
                          DWORD prm_loop_spend_frame,
                          DWORD prm_attack_frame,
                          DWORD prm_rest_frame,
                          float prm_loop_num = -1);

    /**
     * 毎フレームのActorの振る舞い。<BR>
     */
    virtual void behave();

    virtual ~GgafDx9Morpher();
};

}
#endif /*GGAFDX9MORPHER_H_*/

