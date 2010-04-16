#ifndef FONTSPRITEACTOR_H_
#define FONTSPRITEACTOR_H_
namespace GgafDx9LibStg {

/**
 * FontSpriteString 用スプライトクラス.
 * FontSpriteString が内部で利用するクラスです。<BR>
 * @version 1.00
 * @since 2008/04/09
 * @author Masatoshi Tsuge
 */
class FontSpriteActor : public DefaultSpriteActor {

public:
    FontSpriteActor(const char* prm_name, const char* prm_model);

    virtual ~FontSpriteActor();

};

}
#endif /*FONTSPRITEACTOR_H_*/
