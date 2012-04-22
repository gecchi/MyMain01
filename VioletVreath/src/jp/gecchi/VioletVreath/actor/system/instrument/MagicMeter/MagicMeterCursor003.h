#ifndef MAGICMETERCURSOR003_H_
#define MAGICMETERCURSOR003_H_


namespace VioletVreath {

/**
 * 各魔法のレベルカーソル（現在のレベル強調） .
 * @version 1.00
 * @since 2012/04/19
 * @author Masatoshi Tsuge
 */
class MagicMeterCursor003 : public GgafLib::DefaultBoardActor {

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

    coord tmp_Y_;

    /**
     * コンストラクタ .
     * @param prm_name 名称
     * @param prm_pMagicMeter メーター
     * @param prm_pMagic レベルカーソルの対象の魔法
     */
    MagicMeterCursor003(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;


    void processPreDraw() override;

    void processAfterDraw() override;

    void disable();
    void enable();

    void moveToLv(int prm_lv);

    void beginBlinking();
    void stopBlinking();

    virtual ~MagicMeterCursor003();
};

}
#endif /*MAGICMETERCURSOR003_H_*/

