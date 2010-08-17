#ifndef STAGE01_01_H_
#define STAGE01_01_H_
namespace MyStg2nd {

class Stage01_01 : public GgafDx9LibStg::DefaultScene {

    GgafDx9Core::GgafDx9Bgm* _bgm_st1;

public:

    Stage01_01(const char* prm_name);
    /**
     * ‰Šúˆ—
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~Stage01_01();
};

}
#endif /*STAGE01_01_H_*/
