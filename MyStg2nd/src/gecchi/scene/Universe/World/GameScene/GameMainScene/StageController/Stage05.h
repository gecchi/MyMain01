#ifndef STAGE05_H_
#define STAGE05_H_
namespace MyStg2nd {

class Stage05 : public StageScene {

public:

    Stage05(const char* prm_name);
    /**
     * ‰Šúˆ—
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~Stage05();
};

}
#endif /*STAGE05_H_*/
