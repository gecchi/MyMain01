#ifndef FONTPLATEACTOR_H_
#define FONTPLATEACTOR_H_
namespace GgafDx9LibStg {

/**
 * �����\���N���X(���W�ϊ��ς�).
 * DefaultPlateActor ���p�����A�����Z�b�g�e�N�X�`���[���當���\���@�\��ǉ������A�N�^�[�ł��B
 */
class FontPlateActor : public DefaultPlateActor {
	/** ������ */
	std::string _draw_string;
	int _iStrLen;
public:
	FontPlateActor(const char* prm_name, const char* prm_model);

	virtual void processDrawMain(); //�I�[�o�[���C�h

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
