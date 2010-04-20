#ifndef STAGE02SCENE_H_
#define STAGE02SCENE_H_
namespace MyStg2nd {

class Stage02Scene : public StageScene {

public:

    Stage02Scene(const char* prm_name);
    /**
     * ‰Šúˆ—
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~Stage02Scene();
};

}
#endif /*STAGE02SCENE_H_*/
