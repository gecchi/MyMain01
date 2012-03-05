#ifndef PREDRAWSCENE_H_
#define PREDRAWSCENE_H_

namespace VioletVreath {

class PreDrawScene : public GgafLib::DefaultScene {

public:
    TurboMeter* pTurboMeter001_;
    int order_id_begin_;
    int order_id_end_;
    int _id;
    PreDrawScene(const char* prm_name);
    void onReset() override;
    void ready();
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual ~PreDrawScene();
};

}
#endif /*PREDRAWSCENE_H_*/
