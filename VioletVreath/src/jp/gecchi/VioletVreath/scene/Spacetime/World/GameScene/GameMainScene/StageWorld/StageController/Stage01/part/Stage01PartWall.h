#ifndef STAGE01PARTWALLSCENE_H_
#define STAGE01PARTWALLSCENE_H_
#include "VioletVreath.h"

#include "Stage01Part.hpp"
#include "jp/ggaf/lib/scene/WallScene.h"

namespace VioletVreath {

/**
 * �X�e�[�W�f�o�b�O�̕� .
 * @version 1.00
 * @since 2018/09/18
 * @author Masatoshi Tsuge
 */
class Stage01PartWall : public Stage01Part<GgafLib::WallScene> {

public:
    Stage01PartWall(const char* prm_name);

    /**
     * ��������
     */
    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void onFinishedAllSection() override;

    virtual ~Stage01PartWall();
};

}
#endif /*STAGE01PARTWALLSCENE_H_*/
