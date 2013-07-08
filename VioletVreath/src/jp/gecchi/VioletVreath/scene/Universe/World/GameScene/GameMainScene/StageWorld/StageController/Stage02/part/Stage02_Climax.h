#ifndef STAGE02_CLIMAX_H_
#define STAGE02_CLIMAX_H_
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * �X�e�[�W�P�|�Ō� .
 * @version 1.00
 * @since 2010/08/23
 * @author Masatoshi Tsuge
 */
class Stage02_Climax : public GgafLib::DefaultScene {

public:
    bool waiting_;

    EnemyStraea* pBoss_;

public:
    Stage02_Climax(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~Stage02_Climax();
};

}
#endif /*STAGE02_CLIMAX_H_*/
