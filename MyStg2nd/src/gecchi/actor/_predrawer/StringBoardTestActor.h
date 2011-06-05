#ifndef STRINGBOARDEFFECTACTOR_H_
#define STRINGBOARDEFFECTACTOR_H_
namespace MyStg2nd {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class StringBoardTestActor : public GgafDx9LibStg::StringBoardActor {

public:
    StringBoardTestActor(const char* prm_name);

    virtual void processBehavior() override;

    virtual ~StringBoardTestActor();

};

}
#endif /*LABELGECCHI8FONT_H_*/
