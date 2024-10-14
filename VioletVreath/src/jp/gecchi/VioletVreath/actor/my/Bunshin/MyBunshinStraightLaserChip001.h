#ifndef MYBUNSHINSTRAIGHTLASERCHIP001_H_
#define MYBUNSHINSTRAIGHTLASERCHIP001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvMyActor.hpp"
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"

namespace VioletVreath {


class MyBunshinStraightLaserChip001 : public VvMyActor<GgafLib::StraightLaserChip> {

public:
    MyBunshin* pOrg_;
    const LockonCursor001_Main* pLockonCursor_;
    int default_stamina_;

    static int tex_no_;
    static GgafDx::Model* pModel_;
    /** [r/w]レーザー発射時の初期速度 */
    static const velo MAX_VELO;

public:
    MyBunshinStraightLaserChip001(const char* prm_name);

    void initialize() override;

    void onCreateModel() override;

    void processBehavior() override;

    void processSettlementBehavior() override;

    void processJudgement() override;

    void onActive() override;

    void onInactive() override;

    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;

    void setOrg(MyBunshin* prm_pOrg);
    /**
     * レーザーのテクスチャを変える
     * @param prm_tex_no
     */
    static void chengeTex(int prm_tex_no);

    virtual ~MyBunshinStraightLaserChip001();

};

}
#endif /*MYBUNSHINSTRAIGHTLASERCHIP001_H_*/

