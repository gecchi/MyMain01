#ifndef FORMATIONTHAGORAS_H_
#define FORMATIONTHAGORAS_H_
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * 敵機タゴラス用フォーメーションその１ .
 * @version 1.00
 * @since 2013/07/10
 * @author Masatoshi Tsuge
 */
class FormationThagoras : public GgafLib::TreeFormation {

public:
    const char** xpm_;
    XpmHeader* pXpmHd_;
    int num_Thagoras_;

    int cnt_call_up_row_;
    frame call_up_interval_;
public:
    FormationThagoras(const char* prm_name, const char** prm_xpm);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual void onCallUp(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_row, int prm_col) = 0;

    virtual ~FormationThagoras();
};

}
#endif /*FORMATIONTHAGORAS_H_*/
