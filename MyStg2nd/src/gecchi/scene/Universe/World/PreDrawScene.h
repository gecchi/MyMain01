#ifndef PREDRAWSCENE_H_
#define PREDRAWSCENE_H_

namespace MyStg2nd {

class PreDrawScene : public GgafDx9LibStg::DefaultScene {

public:
    TurboMeter* _pTurboMeter001;

    PreDrawScene(const char* prm_name);
    void processReset() override;
    void ready();
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processFinal() override;
    virtual ~PreDrawScene();
};

}
#endif /*PREDRAWSCENE_H_*/
