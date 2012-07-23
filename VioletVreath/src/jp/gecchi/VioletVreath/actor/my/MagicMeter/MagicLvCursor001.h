#ifndef MAGICLVCURSOR001_H_
#define MAGICLVCURSOR001_H_


namespace VioletVreath {

/**
 * 各魔法のレベルカーソル（操作移動用） .
 * @version 1.00
 * @since 2011/12/12
 * @author Masatoshi Tsuge
 */
class MagicLvCursor001 : public MagicLvCursor {

public:
    /**
     * コンストラクタ .
     * @param prm_name 名称
     * @param prm_pMagicMeter メーター
     * @param prm_pMagic レベルカーソルの対象の魔法
     */
    MagicLvCursor001(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic);

    void initialize() override;


    void moveSmoothTo(int prm_lv); //意図的に 上位の moveSmoothTo を hide してます。

    void dispDisable();
    void dispEnable();

    virtual ~MagicLvCursor001();
};

}
#endif /*MAGICLVCURSOR001_H_*/

