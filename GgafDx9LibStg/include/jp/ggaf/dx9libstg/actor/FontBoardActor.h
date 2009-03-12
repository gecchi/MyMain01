#ifndef FONTBOARDACTOR_H_
#define FONTBOARDACTOR_H_
namespace GgafDx9LibStg {

/**
 * �����\���N���X(���W�ϊ��ς�).
 * DefaultBoardActor ���p�����A�����Z�b�g�e�N�X�`���[���當���\���@�\��ǉ������A�N�^�[�ł��B
 */
class FontBoardActor : public DefaultBoardActor {
    /** ������50�����܂� */
    char* _buf;
    char* _draw_string;
    int _len;
public:
    FontBoardActor(const char* prm_name, const char* prm_model);

    virtual void processDrawMain(); //�I�[�o�[���C�h
    virtual void setString(float prm_x, float prm_y, const char* prm_str);
    virtual void setString(float prm_x, float prm_y, char* prm_str);
    virtual void setString(float prm_x, float prm_y, float prm_z, const char* prm_str);
    virtual void setString(float prm_x, float prm_y, float prm_z, char* prm_str);
    virtual void setString(const char* prm_str);
    virtual void setString(char* prm_str);

    virtual ~FontBoardActor();

};

}
#endif /*FONTBOARDACTOR_H_*/
