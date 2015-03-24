#ifndef STAGE04_H_
#define STAGE04_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController/Stage.h"

namespace VioletVreath {

/**
 * �X�e�[�W04 .
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class Stage04 : public Stage {

public:
    Stage04(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~Stage04();
};

}
#endif /*STAGE04_H_*/
