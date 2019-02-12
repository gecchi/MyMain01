#ifndef MYSTRAIGHTLASERCHIP001_H_
#define MYSTRAIGHTLASERCHIP001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"

namespace VioletVreath {


class MyStraightLaserChip001 : public GgafLib::StraightLaserChip {

public:
    MyShip* pOrg_;
    int default_stamina_;

    static int tex_no_;
    static GgafDx::Model* pModel_;

public:
    MyStraightLaserChip001(const char* prm_name);

    void initialize() override;

    void onCreateModel() override;

    void processBehavior() override;

    void processJudgement() override;

    void onActive() override;

    void onInactive() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    /**
     * ���[�U�[�̃e�N�X�`����ς���
     * @param prm_tex_no
     */
    static void chengeTex(int prm_tex_no);

    virtual ~MyStraightLaserChip001();

};

}
#endif /*MYSTRAIGHTLASERCHIP001_H_*/

