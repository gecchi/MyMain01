#ifndef STAGE01WALLSCENE_H_
#define STAGE01WALLSCENE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/WallScene.h"

namespace VioletVreath {

/**
 * �X�e�[�W01�̕� .
 * @version 1.00
 * @since 2010/08/23
 * @author Masatoshi Tsuge
 */
class Stage01WallScene : public GgafLib::WallScene {

public:
    Stage01WallScene(const char* prm_name);

    /**
     * ��������
     */
    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void onFinishedAllSection() override;

    virtual ~Stage01WallScene();
};

}
#endif /*STAGE01WALLSCENE_H_*/
