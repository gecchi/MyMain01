#ifndef STAGE04_H_
#define STAGE04_H_
namespace MyStg2nd {

class Stage04 : public StageScene {

public:

    Stage04(const char* prm_name);
    /**
     * ‰Šúˆ—
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~Stage04();
};

}
#endif /*STAGE04_H_*/
