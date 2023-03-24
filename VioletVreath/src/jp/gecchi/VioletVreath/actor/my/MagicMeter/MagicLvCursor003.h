#ifndef MAGICLVCURSOR003_H_
#define MAGICLVCURSOR003_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor.h"



namespace VioletVreath {

/**
 * 各魔法のレベルの状況（詠唱開始～詠唱中/発動中/発動開始)エフェクト表示カーソル .
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
    void processAfterDraw() override;
    void markOff();

    /**
     * 詠唱開始～詠唱中（レベルアップ時）のエフェクト開始 .
     * @param prm_lv レベル
     */
    void markOnLevelUpCast(int prm_lv);

    /**
     * レベルダウン発動のエフェクト開始 .
     * @param prm_lv レベル
     */
    void markOnLevelDownCast(int prm_lv);

    /**
     * 発動中エフェクト開始 .
     * @param prm_lv レベル
     */
    void markOnInvoke(int prm_lv);

    /**
     * 発動開始エフェクト開始 .
     * @param prm_lv
     */
    void markOnEffect(int prm_lv);

    virtual ~MagicLvCursor003();
};

}
#endif /*MAGICLVCURSOR003_H_*/

