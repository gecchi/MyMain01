#ifndef MAGICLVCURSOR_H_
#define MAGICLVCURSOR_H_


namespace VioletVreath {

/**
 * メーターカーソル基底 .
 * @version 1.00
 * @since 2011/12/12
 * @author Masatoshi Tsuge
 */
class MagicLvCursor : public GgafLib::DefaultBoardSetActor {

public:
    /** 移動目標X座標 */
    coord tX_;
    /** 移動目標Y座標 */
    coord tY_;

    /** [r]カーソル対象の魔法 */
    Magic* pMagic_;
    /** [r]魔法メーター */
    MagicMeter* pMagicMeter_;

    int magic_index_;

    int point_lv_;
    coord tmp_Y_;

    MagicLvCursor(const char* prm_name, const char* prm_model, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic);

    virtual void processBehavior() override;
    virtual void processPreDraw() override;
    virtual void processAfterDraw() override;
    virtual void setLv(int prm_lv);
    virtual void moveTo(int prm_lv, int prm_target_frames, float prm_p1, float prm_p2);
    virtual ~MagicLvCursor();
};

}
#endif /*MAGICLVCURSOR_H_*/

