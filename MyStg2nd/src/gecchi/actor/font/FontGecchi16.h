#ifndef FONTGECCHI16_H_
#define FONTGECCHI16_H_
namespace MyStg2nd {

/**
 * 16x16ドットフォント
 * @version 1.00
 * @since 2010/06/23
 * @author Masatoshi Tsuge
 */
class FontGecchi16 : public GgafDx9LibStg::StringBoardActor {

public:
    FontGecchi16(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~FontGecchi16();

};

}
#endif /*FONTGECCHI16_H_*/
