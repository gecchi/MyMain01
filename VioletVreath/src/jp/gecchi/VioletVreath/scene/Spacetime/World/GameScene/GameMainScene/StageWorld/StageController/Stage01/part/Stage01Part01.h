#ifndef STAGE01PART01_H_
#define STAGE01PART01_H_
#include "VioletVreath.h"
#include "Stage01Part.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * �X�e�[�W�f�o�b�O�|�P .
 * @version 1.00
 * @since 2018/09/18
 * @author Masatoshi Tsuge
 */
class Stage01Part01 : public Stage01Part<GgafLib::DefaultScene> {


public:
    Stage01Part01(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~Stage01Part01();
};

}
#endif /*STAGE01PART01_H_*/
