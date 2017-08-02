#ifndef TEST01_H_
#define TEST01_H_
#include "Hogera.h"

#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace Hogera {

/**
 * ƒeƒXƒg
 * @author Masatoshi Tsuge
 */
class Test01 : public GgafLib::DefaultSpriteActor {

public:
    enum {
        LOCKON001_PROG_FIRST_LOCK ,
        LOCKON001_PROG_LOCK       ,
        LOCKON001_PROG_RELEASE    ,
        PROG_BANPEI,
    };

public:
    Test01(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void onActive() override;

    virtual void onReset() override;

    virtual void onInactive() override;

    virtual void processJudgement() override;

    virtual ~Test01();


};

}
#endif /*TEST01_H_*/

