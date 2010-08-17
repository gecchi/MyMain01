#ifndef STAGE01CONTROLLER_H_
#define STAGE01CONTROLLER_H_
namespace MyStg2nd {

class Stage01Controller : public GgafDx9LibStg::DefaultScene {

    GgafDx9Core::GgafDx9Bgm* _bgm_st1;

public:

    Stage01Controller(const char* prm_name);
    /**
     * èâä˙èàóù
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~Stage01Controller();
};

}
#endif /*STAGE01CONTROLLER_H_*/
