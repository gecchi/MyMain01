#ifndef STAGE05SCENE_H_
#define STAGE05SCENE_H_
namespace MyStg2nd {

class Stage05Scene : public StageScene {

public:

    Stage05Scene(const char* prm_name);
    /**
     * ‰Šúˆ—
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~Stage05Scene();
};

}
#endif /*STAGE05SCENE_H_*/
