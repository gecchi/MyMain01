#ifndef TAMAGOSCENE_H_
#define TAMAGOSCENE_H_

namespace MyStg2nd {

class TamagoScene : public GgafDx9LibStg::DefaultScene {

public:
    TurboMeter* _pTurboMeter001;

    TamagoScene(const char* prm_name);
    void reset() override;
    void ready();
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processFinal() override;
    virtual ~TamagoScene();
};

}
#endif /*TAMAGOSCENE_H_*/
