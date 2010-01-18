#ifndef STAGE03SCENE_H_
#define STAGE03SCENE_H_
namespace MyStg2nd {

class Stage03Scene : public StageScene {

public:

    Stage03Scene(const char* prm_name);
    /**
     * ‰Šúˆ—
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~Stage03Scene();
};

}
#endif /*STAGE03SCENE_H_*/
