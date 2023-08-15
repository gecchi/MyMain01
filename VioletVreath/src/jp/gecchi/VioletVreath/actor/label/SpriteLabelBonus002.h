#ifndef SPRITELABELBONUS002_H_
#define SPRITELABELBONUS002_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/FontSpriteActor.h"

namespace VioletVreath {

/**
 * 編隊全滅時のボーナスポイント表示用フォント .
 * @version 1.00
 * @since 2023/08/15
 * @author Masatoshi Tsuge
 */
class SpriteLabelBonus002 : public GgafLib::FontSpriteActor {

public:
    SpriteLabelBonus002(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;
    /**
     * デポジトリから取得された時のコールバック .
     * SpriteLabelBonus002 の活動を開始サせるには本メソッドを呼び出してください。
     * @param prm_pOrgActor
     */
    void onDispatched(GgafDx::GeometricActor* prm_pOrgActor);

    virtual ~SpriteLabelBonus002();

};

}
#endif /*SPRITELABELBONUS002_H_*/
