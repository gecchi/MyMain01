#ifndef FONTPLATEACTOR_H_
#define FONTPLATEACTOR_H_


class FontPlateActor : public DefaultPlateActor {
	/** 文字数 */
	string _draw_string;
	int _iStrLen;
public:
	FontPlateActor(string prm_name, string prm_model);

	virtual void processDrawMain(); //オーバーライド

	virtual void setString(float prm_x, float prm_y, string prm_draw_string);
	virtual void setString(float prm_x, float prm_y, char* prm_paCString);
	virtual void setString(float prm_x, float prm_y, float prm_z, string prm_draw_string);
	virtual void setString(float prm_x, float prm_y, float prm_z, char* prm_paCString);
	virtual void setString(string prm_draw_string);
	virtual void setString(char* prm_paCString);

	virtual ~FontPlateActor();

};


#endif /*FONTPLATEACTOR_H_*/
