#ifndef MYSTRAIGHTLASERCHIP001_H_
#define MYSTRAIGHTLASERCHIP001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"

namespace VioletVreath {


class MyStraightLaserChip001 : public GgafLib::StraightLaserChip {

public:
    int aim_status_;
    MyShip* pOrg_;
    int default_stamina_;

    static int tex_no_;
    static GgafDxCore::GgafDxModel* pModel_;

public:
    MyStraightLaserChip001(const char* prm_name);

    void initialize() override;

    void onCreateModel() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    /**
     * レーザーのテクスチャを変える
     * @param prm_tex_no
     */
    static void chengeTex(int prm_tex_no);

    virtual ~MyStraightLaserChip001();

};

}
#endif /*MYSTRAIGHTLASERCHIP001_H_*/

