#ifndef DEFAULTSPRITEEFFECTACTOR_H_
#define DEFAULTSPRITEEFFECTACTOR_H_
namespace MyStg2nd {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class DefaultSpriteEffectActor : public GgafDx9LibStg::DefaultSpriteActor {

public:

    DefaultSpriteEffectActor(const char* prm_name);

    virtual ~DefaultSpriteEffectActor();

};

}
#endif /*DEFAULTSPRITEEFFECTACTOR_H_*/

