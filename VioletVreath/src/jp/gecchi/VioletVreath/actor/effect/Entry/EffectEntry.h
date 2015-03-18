#ifndef EFFECTENTRY_H_
#define EFFECTENTRY_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 登場エフェクト基底 .
 * @version 1.00
 * @since 2013/06/28
 * @author Masatoshi Tsuge
 */
class EffectEntry : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        PROG_INIT ,
        PROG_IN   ,
        PROG_STAY ,
        PROG_OUT  ,
        PROG_BANPEI,
    };

    /** [r]エフェクト発生～最大の大きさまで拡大、までのフレーム数 */
    frame scale_in_frames_;
    /** [r]エフェクト持続フレーム数 */
    frame duration_frames_;
    /** [r]エフェクト持続完了～消滅までのフレーム数 */
    frame scale_out_frames_;
    /** [r]エフェクト対象のアクター */
    const GgafDxCore::GgafDxGeometricActor* pTarget_;
    /** [r]拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* pScaler_;

public:
    /**
     * コンストラクタ .
     * @param prm_name 識別名
     * @param prm_model モデルID
     */
    EffectEntry(const char* prm_name, const char* prm_model);

    virtual void onInactive() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    /**
     * エフェクトの座標を引数のアクターと同じ座標に継続させる .
     * @param prm_pTarget エフェクトの座標になるアクター
     */
    void positionFollow(const GgafDxCore::GgafDxGeometricActor* prm_pTarget);

    /**
     * エフェクトの発生、持続、消滅の時間を設定。.
     * </PRE>
     *       ＿＿＿＿               ← Top スケール
     *      /:      :＼
     *     / :      :  ＼
     *    /  :      :    ＼
     *   /   :      :      ＼
     *  /    :      :        ＼
     * /     :      :          ＼   ← Bottom スケール
     * ----------------------------------------------->時間（フレーム）
     * ←①→|←②→|←─ ③ ─→|
     *
     * </PRE>
     * Top スケール,Bottom スケールは pScaler_->forceRange(TOP,BOTTOM) で上書き設定可能。
     * @param prm_scale_in_frames 上記①のフレーム数 (1～)
     * @param prm_duration_frames 上記②のフレーム数 (0～)
     * @param prm_scale_out_frames 上記③のフレーム数 (1～)
     */
    void config(frame prm_scale_in_frames, frame prm_duration_frames, frame prm_scale_out_frames);

    virtual ~EffectEntry();
};

}
#endif /*EFFECTENTRY_H_*/

