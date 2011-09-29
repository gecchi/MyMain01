#ifndef PREDRAWSCENE_H_
#define PREDRAWSCENE_H_

namespace MyStg2nd {

class PreDrawScene : public GgafLib::DefaultScene {

public:
    TurboMeter* _pTurboMeter001;
    int _order_id_begin;
    int _order_id_end;
    int _id;
    PreDrawScene(const char* prm_name);
    void onReset() override;
    void ready();
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processFinal() override;
    virtual ~PreDrawScene();
};

}
#endif /*PREDRAWSCENE_H_*/
