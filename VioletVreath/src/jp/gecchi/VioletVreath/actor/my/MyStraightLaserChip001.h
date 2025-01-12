#ifndef MYSTRAIGHTLASERCHIP001_H_
#define MYSTRAIGHTLASERCHIP001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvMyActor.hpp"
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"

namespace VioletVreath {


class MyStraightLaserChip001 : public VvMyActor<GgafLib::StraightLaserChip> {

public:
    MyShip* pOrg_;
    int default_stamina_;

    static int tex_no_;
    static GgafDx::Model* pModel_;
    /** [r/w]���[�U�[���ˎ��̏������x */
    static const velo MAX_VELO;
public:
    MyStraightLaserChip001(const char* prm_name);

    void initialize() override;

    void onCreateModel() override;

    void processBehavior() override;

    void processJudgement() override;

    void onActive() override;

    void onInactive() override;

    void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override;

    /**
     * ���[�U�[�̃e�N�X�`����ς���
     * @param prm_tex_no
     */
    static void chengeTex(int prm_tex_no);

    virtual ~MyStraightLaserChip001();

};

}
#endif /*MYSTRAIGHTLASERCHIP001_H_*/

