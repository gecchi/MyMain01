#ifndef FONTPLATEACTOR_H_
#define FONTPLATEACTOR_H_


class FontPlateActor : public DefaultPlateActor {
	/** ������ */
	string _draw_string;
public:
	FontPlateActor(string prm_name, string prm_xname);

	virtual void processDrawMain(); //�I�[�o�[���C�h

	virtual void setStringPlate(float prm_x, float prm_y, string prm_draw_string);

	virtual ~FontPlateActor();

};


#endif /*FONTPLATEACTOR_H_*/
