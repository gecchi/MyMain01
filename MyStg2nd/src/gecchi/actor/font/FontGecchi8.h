#ifndef FONTGECCHI8_H_
#define FONTGECCHI8_H_
namespace MyStg2nd {

/**
 * 8x8ドットフォント
 * @version 1.00
 * @since 2010/06/23
 * @author Masatoshi Tsuge
 */
class FontGecchi8 : public GgafDx9LibStg::StringBoardActor {

public:
    FontGecchi8(const char* prm_name);

    virtual void processBehavior() override;

    virtual ~FontGecchi8();

};

}
#endif /*FONTGECCHI8_H_*/
