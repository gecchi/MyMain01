#ifndef SPRITELABELBONUS001_H_
#define SPRITELABELBONUS001_H_
#include "jp/ggaf/lib/actor/StringSpriteActor.h"

namespace VioletVreath {

/**
 * 編隊全滅時のボーナスポイント表示用フォント .
 * @version 1.00
 * @since 2012/11/02
 * @author Masatoshi Tsuge
 */
class SpriteLabelBonus001 : public GgafLib::StringSpriteActor {
public:
    enum {
        PROG_INIT   ,
        PROG_MOVE01 ,
        PROG_MOVE02 ,
        PROG_LEAVE ,
        _BANPEI_,
    };

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
    void onDispatched(GgafDxCore::GgafDxGeometricActor* prm_pOrgActor);

    virtual ~SpriteLabelBonus001();

};

}
#endif /*SPRITELABELBONUS001_H_*/
