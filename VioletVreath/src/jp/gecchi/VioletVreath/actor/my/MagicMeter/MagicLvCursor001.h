#ifndef MAGICLVCURSOR001_H_
#define MAGICLVCURSOR001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor.h"

namespace VioletVreath {

/**
 * 各魔法のユーザーレベル選択(操作移動用)カーソル .
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

    void moveSmoothTo(int prm_lv) { //意図的に 上位の moveSmoothTo を hiding
        MagicLvCursor::moveSmoothTo(prm_lv, 12, 0.3f, 0.7f);
    }

    /**
     * 操作不可状態表示 .
     */
    void dispDisable();
    /**
     * 操作可状態表示 .
     */
    void dispEnable();

    virtual ~MagicLvCursor001();
};

}
#endif /*MAGICLVCURSOR001_H_*/

