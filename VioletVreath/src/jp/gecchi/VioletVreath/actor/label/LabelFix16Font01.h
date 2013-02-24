#ifndef LABELFIX16FONT01_H_
#define LABELFIX16FONT01_H_
namespace VioletVreath {

/**
 * 16x16ドットFIXフォントのラベル .
 * @version 1.00
 * @since 2013/03/21
 * @author Masatoshi Tsuge
 */
class LabelFix16Font01 : public GgafLib::StringBoardActor {

public:
    LabelFix16Font01(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~LabelFix16Font01();

};

}
#endif /*LABELFIX16FONT01_H_*/
