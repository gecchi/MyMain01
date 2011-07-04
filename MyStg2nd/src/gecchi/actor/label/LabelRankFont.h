#ifndef RANKFONT_H_
#define RANKFONT_H_
namespace MyStg2nd {

/**
 * ランクフォント .
 * @version 1.00
 * @since 2011/06/04
 * @author Masatoshi Tsuge
 */
class LabelRankFont : public GgafDx9LibStg::StringBoardActor {

public:
    LabelRankFont(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~LabelRankFont();

};

}
#endif /*RANKFONT_H_*/
