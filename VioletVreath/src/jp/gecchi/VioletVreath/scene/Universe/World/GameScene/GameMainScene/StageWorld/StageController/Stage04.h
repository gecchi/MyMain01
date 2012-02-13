#ifndef STAGE04_H_
#define STAGE04_H_
namespace VioletVreath {

class Stage04 : public Stage {

public:

    Stage04(const char* prm_name);
    /**
     * ‰Šúˆ—
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~Stage04();
};

}
#endif /*STAGE04_H_*/
