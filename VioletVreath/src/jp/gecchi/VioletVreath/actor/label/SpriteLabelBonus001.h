#ifndef SPRITELABELBONUS001_H_
#define SPRITELABELBONUS001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/FontSpriteActor.h"

namespace VioletVreath {

/**
 * 編隊全滅時のボーナスポイント表示用フォント .
 * @version 1.00
 * @since 2012/11/02
 * @author Masatoshi Tsuge
 */
class SpriteLabelBonus001 : public GgafLib::FontSpriteActor {

public:
    SpriteLabelBonus001(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;
    /**
     * デポジトリから取得された時のコールバック .
     * SpriteLabelBonus001 の活動を開始サせるには本メソッドを呼び出してください。
     * @param prm_pOrgActor
     */
    void onDispatched(GgafDx::GeometricActor* prm_pOrgActor);

    virtual ~SpriteLabelBonus001();

};

}
#endif /*SPRITELABELBONUS001_H_*/
