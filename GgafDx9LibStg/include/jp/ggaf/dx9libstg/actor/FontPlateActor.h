#ifndef FONTPLATEACTOR_H_
#define FONTPLATEACTOR_H_
namespace GgafDx9LibStg {

/**
 * 文字表示クラス(座標変換済み).
 * DefaultPlateActor を継承し、文字セットテクスチャーから文字表示機能を追加したアクターです。
 */
class FontPlateActor : public DefaultPlateActor {
	/** 文字数 */
	std::string _draw_string;
	int _iStrLen;
public:
	FontPlateActor(const char* prm_name, const char* prm_model);

	virtual void processDrawMain(); //オーバーライド

	virtual void setString(float prm_x, float prm_y, std::string prm_draw_string);
	virtual void setString(float prm_x, float prm_y, char* prm_paCString);
	virtual void setString(float prm_x, float prm_y, float prm_z, std::string prm_draw_string);
	virtual void setString(float prm_x, float prm_y, float prm_z, char* prm_paCString);
	virtual void setString(std::string prm_draw_string);
	virtual void setString(char* prm_paCString);

	virtual ~FontPlateActor();

};


}
#endif /*FONTPLATEACTOR_H_*/
