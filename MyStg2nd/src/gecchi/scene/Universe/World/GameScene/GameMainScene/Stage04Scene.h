#ifndef STAGE04SCENE_H_
#define STAGE04SCENE_H_
namespace MyStg2nd {

class Stage04Scene : public StageScene {

public:

    Stage04Scene(const char* prm_name);
    /**
     * ‰Šúˆ—
     */
    void initialize();

    virtual void processBehavior();

    virtual void processFinal();

    virtual ~Stage04Scene();
};

}
#endif /*STAGE04SCENE_H_*/
