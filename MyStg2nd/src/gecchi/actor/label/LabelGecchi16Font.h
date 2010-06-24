#ifndef LABELGECCHI16FONT_H_
#define LABELGECCHI16FONT_H_
namespace MyStg2nd {

/**
 * 16x16ドットフォント
 * @version 1.00
 * @since 2010/06/23
 * @author Masatoshi Tsuge
 */
class LabelGecchi16Font : public GgafDx9LibStg::StringBoardActor {

public:
    LabelGecchi16Font(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~LabelGecchi16Font();

};

}
#endif /*LABELGECCHI16FONT_H_*/
