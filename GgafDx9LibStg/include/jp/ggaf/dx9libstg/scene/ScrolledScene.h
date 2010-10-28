#ifndef SCROLLEDSCENE_H_
#define SCROLLEDSCENE_H_
namespace GgafDx9LibStg {

/**
 * @version 1.00
 * @since 2010/08/23
 * @author Masatoshi Tsuge
 */
class ScrolledScene : public DefaultScene {

public:
    int _ground_speed;

    /** [r/w]���t���[��processSettlementBehavior()�ŁA�z���A�N�^�[�S�ĂɎ��s�����֐��B*/
    void (*_pFuncWallMove)(GgafCore::GgafObject*, void*, void*);

    ScrolledScene(const char* prm_name);


    virtual void processSettlementBehavior() override;


    virtual ~ScrolledScene();
};

}
#endif /*SCROLLEDSCENE_H_*/
