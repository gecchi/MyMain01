#ifndef EFFECTENTRY_H_
#define EFFECTENTRY_H_
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
    frame scale_in_frames_;
    frame duration_frames_;
    frame scale_out_frames_;

    enum {
        PROG_INIT ,
        PROG_IN   ,
        PROG_STAY ,
        PROG_OUT  ,
        PROG_BANPEI,
    };
    /** エフェクト対象のアクター */
    GgafDxCore::GgafDxGeometricActor* pTarget_;
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* pScaler_;

public:
    EffectEntry(const char* prm_name, const char* prm_model);

    virtual void onInactive() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    /**
     * 引数のアクターと同じ座標を継続 .
     * @param prm_pTarget
     */
    void positionFollow(GgafDxCore::GgafDxGeometricActor* prm_pTarget);

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
     * @param prm_scale_in_frames 上記①のフレーム数
     * @param prm_duration_frames 上記②のフレーム数
     * @param prm_scale_out_frames 上記③のフレーム数
     */
    void config(frame prm_scale_in_frames, frame prm_duration_frames, frame prm_scale_out_frames);

    virtual ~EffectEntry();
};

}
#endif /*EFFECTENTRY_H_*/

