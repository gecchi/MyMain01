#ifndef MAGICMETERCURSOR001_H_
#define MAGICMETERCURSOR001_H_


namespace VioletVreath {

/**
 * メーター主カーソル .
 * @version 1.00
 * @since 2011/12/12
 * @author Masatoshi Tsuge
 */
class MagicMeterCursor001 : public GgafLib::DefaultBoardActor {

public:
    /** 移動目標X座標 */
    coord tX_;
    /** 移動目標Y座標 */
    coord tY_;
    /** 退避用 */
    float tmp_alpha_;
    MagicMeter* pMagicMeter_;

public:
   MagicMeterCursor001(const char* prm_name, MagicMeter* prm_pMagicMeter);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;
    void moveTo(int prm_magic_mater_index);

    virtual ~MagicMeterCursor001();
};

}
#endif /*MAGICMETERCURSOR001_H_*/

