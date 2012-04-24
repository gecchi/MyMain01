#ifndef MAGICLVCURSOR002_H_
#define MAGICLVCURSOR002_H_


namespace VioletVreath {

/**
 * 各魔法のレベルカーソル（現在のレベル強調） .
 * @version 1.00
 * @since 2012/04/19
 * @author Masatoshi Tsuge
 */
class MagicLvCursor002 : public MagicLvCursor {

public:
    /**
     * コンストラクタ .
     * @param prm_name 名称
     * @param prm_pMagicMeter メーター
     * @param prm_pMagic レベルカーソルの対象の魔法
     */
    MagicLvCursor002(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic);

    void initialize() override;
    void moveTo(int prm_lv);
    void disable();
    void enable();

    void beginBlinking();
    void stopBlinking();

    virtual ~MagicLvCursor002();
};

}
#endif /*MAGICLVCURSOR002_H_*/

