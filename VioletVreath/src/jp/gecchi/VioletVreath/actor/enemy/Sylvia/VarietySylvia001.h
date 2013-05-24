#ifndef VARIETYSYLVIA001_H_
#define VARIETYSYLVIA001_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Sylvia/EnemySylvia.h"

namespace VioletVreath {

/**
 * 地形トーラスのバリエーション001 .
 * @version 1.00
 * @since 2010/05/23
 * @author Masatoshi Tsuge
 */
class VarietySylvia001 : public EnemySylvia {

public:
    EnemySylviaEye* pEnemySylviaEye_;

public:
    VarietySylvia001(const char* prm_name);

    void initialize() override;
    void processBehavior() override;
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    virtual ~VarietySylvia001();
};

}
#endif /*VARIETYSYLVIA001_H_*/

