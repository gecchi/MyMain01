#ifndef FONTSPRITESTRING_H_
#define FONTSPRITESTRING_H_
namespace GgafDx9LibStg {

/**
 * FontSpriteActor•\Ž¦ƒNƒ‰ƒX
 */
class FontSpriteString : public GgafCore::GgafObject {
	std::string _font_modelname;
	int _iStrLen;
	FontSpriteActor** _papFontSpriteActor;


public:
	FontSpriteString(char* prm_font_modelname, int prm_iStrLen);

	virtual void draw(int prm_X, int prm_Y, int prm_Z, std::string prm_string);

	virtual ~FontSpriteString();
};

}
#endif /*FONTSPRITESTRING_H_*/
