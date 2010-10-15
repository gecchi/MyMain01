#ifndef GROUNDBOXACTOR_H_
#define GROUNDBOXACTOR_H_


namespace MyStg2nd {

/**
 */
class GroundBoxActor : public GgafDx9LibStg::WallActor {

public:

    GroundBoxActor(const char* prm_name);

    virtual void onCreateModel() override {
    }
    virtual void initialize() override;

    virtual ~GroundBoxActor();
};

}
#endif /*GROUNDBOXACTOR_H_*/
