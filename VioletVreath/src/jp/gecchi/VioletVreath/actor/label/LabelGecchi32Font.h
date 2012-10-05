#ifndef LABELGECCHI32FONT_H_
#define LABELGECCHI32FONT_H_
namespace VioletVreath {

/**
 * �I���W�i��32x32�h�b�g�t�H���g�̃��x�� .
 * @version 1.00
 * @since 2012/10/05
 * @author Masatoshi Tsuge
 */
class LabelGecchi32Font : public GgafLib::StringBoardActor {

public:
    LabelGecchi32Font(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~LabelGecchi32Font();

};

}
#endif /*LABELGECCHI32FONT_H_*/
