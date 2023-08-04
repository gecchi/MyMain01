#ifndef LABELBONUS001_H_
#define LABELBONUS001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/FontBoardActor.h"

namespace VioletVreath {

/**
 * 編隊全滅時のボーナスポイント表示用フォント .
 * @version 1.00
 * @since 2023/08/04
 * @author Masatoshi Tsuge
 */
class LabelBonus001 : public GgafLib::FontBoardActor {

    GgafDx::GeometricActor* pOrgActor_;
public:
    LabelBonus001(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;
    /**
     * デポジトリから取得された時のコールバック .
     * LabelBonus001 の活動を開始サせるには本メソッドを呼び出してください。
     * @param prm_pOrgActor
     */
    void onDispatched(GgafDx::GeometricActor* prm_pOrgActor);

    virtual ~LabelBonus001();

};

}
#endif /*LABELBONUS001_H_*/
