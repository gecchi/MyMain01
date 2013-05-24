#ifndef MYSTRAIGHTLASERCHIP001_H_
#define MYSTRAIGHTLASERCHIP001_H_
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"

namespace VioletVreath {


class MyStraightLaserChip001 : public GgafLib::StraightLaserChip {

public:
    int lockon_st_;
    MyShip* pOrg_;
    int default_stamina_;

    static int tex_no_;
    static GgafDxCore::GgafDxModel* pModel_;

    /** テクスチャ名 */
    static char aaTextureName[3][51];

public:
    MyStraightLaserChip001(const char* prm_name);

    void initialize() override;

    void onCreateModel() override;

    void processBehavior() override;

    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    void onActive() override;
    void onInactive() override;
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    static void updateTex();

    virtual ~MyStraightLaserChip001();

};

}
#endif /*MYSTRAIGHTLASERCHIP001_H_*/

