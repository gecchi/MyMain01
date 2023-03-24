#ifndef MAGICLVCURSOR_H_
#define MAGICLVCURSOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

namespace VioletVreath {

/**
 * 魔法メーターの魔法のレベルカーソル基底 .
 * @version 1.00
 * @since 2011/12/12
 * @author Masatoshi Tsuge
 */
class MagicLvCursor : public GgafLib::DefaultBoardActor {

public:
    /** [r]カーソル対象の魔法 */
    Magic* pMagic_;
    /** [r]魔法メーター */
    MagicMeter* pMagicMeter_;
    /** [r]カーソル対象の魔法のインデックス番号 */
    int magic_index_;
    /** [r]現在指しているレベル */
    int point_lv_;

    /** 退避用 */
    coord tmp_y_;
    /** 退避用 */
    float tmp_alpha_;
    /** 移動目標X座標 */
    coord tx_;
    /** 移動目標Y座標 */
    coord ty_;

public:
    /**
     * コンストラクタ .
     * @param prm_name 名称
     * @param prm_model モデル識別名称
     * @param prm_pMagicMeter 魔法メーター
     * @param prm_pMagic カーソル対象の魔法
     */
    MagicLvCursor(const char* prm_name, const char* prm_model, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic);

    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processPreDraw() override;
    virtual void processAfterDraw() override;

    /**
     * カーソルを瞬時に移動。
     * @param prm_lv 移動先レベル
     */
    virtual void moveTo(int prm_lv);

    /**
     * カーソルをなめらかに移動。
     * @param prm_lv 移動先レベル
     * @param prm_target_frames 費やす時間(フレーム数)
     * @param prm_p1 トップスピードに達する時刻割合
     * @param prm_p2 減速を開始時刻となる時刻割合
     */
    virtual void moveSmoothTo(int prm_lv, frame prm_target_frames, float prm_p1, float prm_p2);

    virtual void blink();

    virtual ~MagicLvCursor();
};

}
#endif /*MAGICLVCURSOR_H_*/

