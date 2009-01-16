#ifndef FONTSPRITESTRING_H_
#define FONTSPRITESTRING_H_

class FontSpriteString : public GgafCore::GgafObject {
	string _font_modelname;
	int _iStrLen;
	FontSpriteActor** _papFontSpriteActor;

public:
	FontSpriteString(string prm_font_modelname, int prm_iStrLen);

	virtual void draw(int prm_X, int prm_Y, int prm_Z, string prm_string);

	virtual ~FontSpriteString();
};

#endif /*FONTSPRITESTRING_H_*/
