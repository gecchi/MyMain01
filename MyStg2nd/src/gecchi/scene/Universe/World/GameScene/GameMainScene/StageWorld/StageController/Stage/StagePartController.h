#ifndef STAGEPARTCONTROLLER_H_
#define STAGEPARTCONTROLLER_H_

namespace MyStg2nd {

class StagePartController : public GgafLib::DefaultScene {

public:

    StagePartController(const char* prm_name);

//�����ō��܁B���j�ύX
//    /**
//     * �X���[
//     * @param prm_pScene
//     */
//    virtual void addSubLast(GgafScene* prm_pScene) override;

    virtual ~StagePartController();
};

}
#endif /*STAGEPARTCONTROLLER_H_*/
