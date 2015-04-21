#ifndef EFFECTENTRY_H_
#define EFFECTENTRY_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * またたきエフェクト基底 .
 * 入退場時のエフェクトなどを想定。
 * @version 1.00
 * @since 2013/06/28
 * @author Masatoshi Tsuge
 */
class EffectBlink : public GgafLib::DefaultMeshSetActor {

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
    EffectBlink(const char* prm_name, const char* prm_model);

    virtual void onInactive() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    /**
     * またたかせる .
     * エフェクトの発生、持続、消滅を行う。
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
     * Top スケール,Bottom スケールは pScaler_->setRange(TOP,BOTTOM) で上書き設定可能。
     * @param prm_scale_in_frames 発生時間、上記①のフレーム数 (1～)
     * @param prm_duration_frames 持続時間、上記②のフレーム数 (0～)
     * @param prm_scale_out_frames 消滅時間、上記③のフレーム数 (1～)
     * @param prm_pFollowTarget エフェクト座標を引数のアクターと同じ座標に同期をとる(追従させる)。 不要の場合は nullptr .
     */
    void blink(frame prm_scale_in_frames, frame prm_duration_frames, frame prm_scale_out_frames,
               const GgafDxCore::GgafDxGeometricActor* prm_pFollowTarget);

    /**
     * またたきフレーム数を取得 .
     */
    frame getBlinkFrames() {
        return (scale_in_frames_+duration_frames_+scale_out_frames_);
    }

    /**
     * 入場エフェクトとして使用した場合の、アクターの入場開始フレームを取得 .
     * @return 入場開始フレーム
     */
    frame getFrameOfSummonsBegin() {
        return (scale_in_frames_/2);
    }

    /**
     * 入場エフェクトとして使用した場合の、入場に費やすフレーム数を取得 .
     * @return 入場に費やすフレーム数
     */
    frame getSummoningFrames() {
        return ( (scale_in_frames_/2) + duration_frames_ + (scale_out_frames_/2) );
    }

    virtual ~EffectBlink();
};

}
#endif /*EFFECTENTRY_H_*/

