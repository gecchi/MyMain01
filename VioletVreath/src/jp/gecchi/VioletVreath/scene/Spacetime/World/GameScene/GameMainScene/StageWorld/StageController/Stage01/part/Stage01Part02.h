#ifndef STAGE01PART02_H_
#define STAGE01PART02_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "Stage01Part.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * �X�e�[�W�f�o�b�O�|�Q .
 * @version 1.00
 * @since 2018/09/18
 * @author Masatoshi Tsuge
 */
class Stage01Part02 : public Stage01Part<GgafLib::DefaultScene> {


public:
    Stage01Part02(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~Stage01Part02();
};

}
#endif /*STAGE01PART02_H_*/
