#ifndef MAGICMETERCURSOR002_H_
#define MAGICMETERCURSOR002_H_


namespace VioletVreath {

/**
 * 各魔法のレベルカーソル（操作移動用） .
 * @version 1.00
 * @since 2011/12/12
 * @author Masatoshi Tsuge
 */
class MagicMeterCursor002 : public GgafLib::DefaultBoardActor {

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
    MagicMeterCursor002(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic);

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

    virtual ~MagicMeterCursor002();
};

}
#endif /*MAGICMETERCURSOR002_H_*/

