#ifndef FONTSPRITEACTOR_H_
#define FONTSPRITEACTOR_H_
namespace GgafDx9LibStg {

/**
 * FontSpriteString 用スプライトクラス.
 * FontSpriteString が内部で利用するクラスです。<BR>
 */
class FontSpriteActor : public DefaultSpriteActor {

public:
    FontSpriteActor(const char* prm_name, const char* prm_model);

    virtual ~FontSpriteActor();

};

}
#endif /*FONTSPRITEACTOR_H_*/
