#ifndef STAGE01MAINSCENE_H_
#define STAGE01MAINSCENE_H_
namespace MyStg2nd {

class Stage01MainScene : public GgafDx9LibStg::DefaultScene {

    GgafDx9Core::GgafDx9Bgm* _bgm_st1;

public:

    Stage01MainScene(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~Stage01MainScene();
};

}
#endif /*STAGE01MAINSCENE_H_*/
