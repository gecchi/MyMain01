#ifndef FONTSPRITEACTOR_H_
#define FONTSPRITEACTOR_H_
namespace GgafDx9LibStg {

/**
 * FontSpriteString �p�X�v���C�g�N���X.
 * FontSpriteString �������ŗ��p����N���X�ł��B<BR>
 */
class FontSpriteActor : public DefaultSpriteActor {

public:
    FontSpriteActor(const char* prm_name, const char* prm_model);

    virtual ~FontSpriteActor();

};

}
#endif /*FONTSPRITEACTOR_H_*/
