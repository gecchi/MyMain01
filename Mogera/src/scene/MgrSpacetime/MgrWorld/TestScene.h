#ifndef TESTSCENE_H_
#define TESTSCENE_H_
#include "Mogera.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace Mogera {

class TestScene : public GgafLib::DefaultScene {

public:
    int order_id_begin_;
    int order_id_end_;
    int _id_;
public:
    TestScene(const char* prm_name);
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual ~TestScene();
};

}
#endif /*TESTSCENE_H_*/
