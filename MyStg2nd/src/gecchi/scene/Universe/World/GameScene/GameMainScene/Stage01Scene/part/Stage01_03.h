#ifndef STAGE01_03_H_
#define STAGE01_03_H_
namespace MyStg2nd {

class Stage01_03 : public GgafDx9LibStg::DefaultScene {

    GgafDx9Core::GgafDx9Bgm* _bgm_st1;

public:

    Stage01_03(const char* prm_name);
    /**
     * ‰Šúˆ—
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~Stage01_03();
};

}
#endif /*STAGE01_03_H_*/
