#ifndef MAGICLVCURSOR003_H_
#define MAGICLVCURSOR003_H_


namespace VioletVreath {

/**
 * 各魔法の詠唱中発動中レベル強調表示カーソル .
 * @version 1.00
 * @since 2012/04/24
 * @author Masatoshi Tsuge
 */
class MagicLvCursor003 : public MagicLvCursor {

public:

    /**
     * コンストラクタ .
     * @param prm_name 名称
     * @param prm_pMagicMeter メーター
     * @param prm_pMagic レベルカーソルの対象の魔法
     */
    MagicLvCursor003(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic);

    void initialize() override;
    void processPreDraw() override;

    void markOff();
    void markOnLevelUpCast(int prm_lv);
    void markOnLevelDownCast(int prm_lv);
    void markOnInvoke(int prm_lv);
    virtual ~MagicLvCursor003();
};

}
#endif /*MAGICLVCURSOR003_H_*/

