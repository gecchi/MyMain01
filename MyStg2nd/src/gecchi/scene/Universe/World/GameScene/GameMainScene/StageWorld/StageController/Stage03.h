#ifndef STAGE03_H_
#define STAGE03_H_
namespace MyStg2nd {

class Stage03 : public Stage {

public:

    Stage03(const char* prm_name);
    /**
     * ‰Šúˆ—
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~Stage03();
};

}
#endif /*STAGE03_H_*/
