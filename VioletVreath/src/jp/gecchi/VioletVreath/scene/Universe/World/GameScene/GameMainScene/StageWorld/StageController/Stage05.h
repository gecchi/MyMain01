#ifndef STAGE05_H_
#define STAGE05_H_
namespace VioletVreath {

class Stage05 : public Stage {

public:

    Stage05(const char* prm_name);
    /**
     * ‰Šúˆ—
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~Stage05();
};

}
#endif /*STAGE05_H_*/
