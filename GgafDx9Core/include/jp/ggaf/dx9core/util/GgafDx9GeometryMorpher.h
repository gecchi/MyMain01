#ifndef GGAFDX9GEOMETRYMORPHER_H_
#define GGAFDX9GEOMETRYMORPHER_H_
namespace GgafDx9Core {

enum GgafDx9MorphMethod {
    NOMORPH,
    TARGET_LINER,
    LOOP_LINER,
    LOOP_TRIANGLEWAVE,
    TARGET_SIN,
    LOOP_SIN,
    TARGET_ACCELERATION,
    LOOP_PARABOLA,
    TARGET_PARABOLA_REV,
    LOOP_PARABOLA_REV
};


/**
 * モーフ支援クラス .
 * GgafDx9MorphMeshActor のメンバの<BR>
 * _weight[] <BR>
 * を簡単に操作するために設計。<BR>
 * @version 1.00
 * @since 2009/05/11
 * @author Masatoshi Tsuge
 */
class GgafDx9GeometryMorpher : public GgafCore::GgafObject {

public:
    /** 対象アクター */
    GgafDx9MorphMeshActor* _pActor;

    float _target_weight[MAX_MORPH_TARGET+1];
    float _top_weight[MAX_MORPH_TARGET+1];
    float _bottom_weight[MAX_MORPH_TARGET+1];
    float _velo_weight[MAX_MORPH_TARGET+1];
    float _acce_weight[MAX_MORPH_TARGET+1];
    DWORD _loop_attack_frame[MAX_MORPH_TARGET+1];
    DWORD _loop_rest_frame[MAX_MORPH_TARGET+1];
    DWORD _loop_spend_frame[MAX_MORPH_TARGET+1];
    DWORD _loop_begin_frame[MAX_MORPH_TARGET+1];
    int _halfloop_cnt[MAX_MORPH_TARGET+1];
    int _stop_halfloop_num[MAX_MORPH_TARGET+1];

    GgafDx9MorphMethod _method[MAX_MORPH_TARGET+1];

    /**
     * コンストラクタ<BR>
     * @param	prm_pActor	適用Actor
     */
    GgafDx9GeometryMorpher(GgafDx9MorphMeshActor* prm_pActor);

    void setWeightRange(int prm_target_mesh, float prm_weight1, float prm_weight2) {
        if (prm_weight1 < prm_weight2) {
            _top_weight[prm_target_mesh] = prm_weight2;
            _bottom_weight[prm_target_mesh] = prm_weight1;
        } else {
            _top_weight[prm_target_mesh] = prm_weight1;
            _bottom_weight[prm_target_mesh] = prm_weight2;
        }
    }

    void resetWeight(int prm_target_mesh) {
        _pActor->_weight[prm_target_mesh] = _bottom_weight[prm_target_mesh];
    }
    void resetTopWeight(int prm_target_mesh) {
        _pActor->_weight[prm_target_mesh] = _top_weight[prm_target_mesh];
    }


    void stopImmediately(int prm_target_mesh);

    /**
     * ターゲットへ一定速度でモーフする（フレーム数指定） .
     * @param prm_target_mesh ターゲットメッシュNO
     * @param prm_target_weight ターゲットメッシュの目標重み(0.0～1.0)
     * @param prm_spend_frame 費やすフレーム数
     */
    void intoTargetLinerUntil(int prm_target_mesh, float prm_target_weight, DWORD prm_spend_frame);

    /**
     * ターゲットへ一定速度でモーフする（重み差分指定） .
     * @param prm_target_mesh ターゲットメッシュNO
     * @param prm_target_weight ターゲットメッシュの目標重み(0.0～1.0)
     * @param prm_velo_weight 毎フレーム加算する重み差分(>0.0)。正の重みを指定する事。加算か減算かは自動判断する。
     */
    void intoTargetLinerStep(int prm_target_mesh, float prm_target_weight, float prm_velo_weight);

    /**
     * ターゲットへ加速指定でモーフする（重み速度、重み加速度差指定） .
     * 重み加速度を0に指定すると intoTargetLinerStep とほぼ同じ意味になる。
     * intoTargetLinerStep の第３引数は正負を気にすること無いが、本メソッドは正負の自動判定はしない（できない）。
     * @param prm_target_mesh ターゲットメッシュNO
     * @param prm_target_weight ターゲットメッシュの目標重み(0.0～1.0)
     * @param prm_velo_weight 初期重み速度
     * @param prm_acce_weight 重み加速度
     */
    void intoTargetAccelerationStep(int prm_target_mesh, float prm_target_weight, float prm_velo_weight, float prm_acce_weight);

    /**
     * ターゲットへ一定速度でモーフし、一定速度で元に戻る。これをループ指定する。（１ループのフレーム数指定） .
     * @param prm_target_mesh ターゲットメッシュNO
     * @param prm_loop_spend_frame １ループ(変化して元に戻るまで)に費やすフレーム
     * @param prm_loop_num ループする回数(0.5 回単位で指定可能)
     */
    void loopLiner(int prm_target_mesh, DWORD prm_loop_spend_frame, float prm_loop_num = -1);

    /**
     * 三角波の波形を重みとしてモーフする。.
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

    virtual ~GgafDx9GeometryMorpher();
};

}
#endif /*GGAFDX9GEOMETRYMORPHER_H_*/

