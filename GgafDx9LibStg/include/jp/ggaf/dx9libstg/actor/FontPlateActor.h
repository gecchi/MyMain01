#ifndef FONTPLATEACTOR_H_
#define FONTPLATEACTOR_H_


class FontPlateActor : public DefaultPlateActor {
	/** 文字数 */
	string _draw_string;
public:
	FontPlateActor(string prm_name, string prm_xname);

	virtual void processDrawMain(); //オーバーライド

	virtual void setStringPlate(float prm_x, float prm_y, string prm_draw_string);

	virtual ~FontPlateActor();

};


#endif /*FONTPLATEACTOR_H_*/
