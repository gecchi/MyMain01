#ifndef EFFECTENTRANCE001_H_
#define EFFECTENTRANCE001_H_
#include "jp/gecchi/VioletVreath/actor/effect/Entry/EffectEntry.h"

namespace VioletVreath {

/**
 * 登場エフェクト、その1 .
 * @version 1.00
 * @since 2012/06/11
 * @author Masatoshi Tsuge
 */
class EffectEntry001 : public EffectEntry {

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

    EffectEntry001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    /**
     * エフェクトの発生、持続、消滅の時間を設定。.
     * </PRE>
     *       ＿＿＿＿               ← スケール率 1.0
     *      /:      :＼
     *     / :      :  ＼
     *    /  :      :    ＼
     *   /   :      :      ＼
     *  /    :      :        ＼
     * /     :      :          ＼   ← スケール率 0
     * ----------------------------------------------->時間（フレーム）
     * ←①→|←②→|←─ ③ ─→|
     *
     * </PRE>
     *
     * @param prm_scale_in_frames 上記①のフレーム数
     * @param prm_duration_frames 上記②のフレーム数
     * @param prm_scale_out_frames 上記③のフレーム数
     */
    void config(frame prm_scale_in_frames, frame prm_duration_frames, frame prm_scale_out_frames);

    virtual ~EffectEntry001();
};

}
#endif /*EFFECTENTRANCE001_H_*/

