#ifndef STAGE01MAIN_H_
#define STAGE01MAIN_H_
namespace MyStg2nd {

class Stage01_02 : public GgafDx9LibStg::DefaultScene {

    GgafDx9Core::GgafDx9Bgm* _bgm_st1;

public:

    Stage01_02(const char* prm_name);
    /**
     * ‰Šúˆ—
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~Stage01_02();
};

}
#endif /*STAGE01MAIN_H_*/
