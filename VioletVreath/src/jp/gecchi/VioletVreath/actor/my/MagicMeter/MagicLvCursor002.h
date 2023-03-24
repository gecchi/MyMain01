#ifndef MAGICLVCURSOR002_H_
#define MAGICLVCURSOR002_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor.h"



namespace VioletVreath {

/**
 * 各魔法の現行レベル強調表示カーソル（） .
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

    void moveSmoothTo(int prm_lv, frame prm_spent=10) { //意図的に 上位の moveSmoothTo を hiding
        MagicLvCursor::moveSmoothTo(prm_lv, prm_spent, 0.3f, 0.7f); //じわ～っと移動
    }

    /**
     * 操作不可状態表示 .
     */
    void dispDisable();
    /**
     * 操作可能状態表示 .
     */
    void dispEnable();

    virtual ~MagicLvCursor002();
};

}
#endif /*MAGICLVCURSOR002_H_*/

