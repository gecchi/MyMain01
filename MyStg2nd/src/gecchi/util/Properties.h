#ifndef PROPERTIES_H_
#define PROPERTIES_H_

#define PROPERTY(X) (*MyStg2nd::Properties::X)

namespace MyStg2nd {

class Properties: GgafDx9Core::GgafDx9Properties {
public:
    static std::string* MY_KEY_SHOT1;
    static std::string* MY_KEY_SHOT2;
    static std::string* MY_KEY_OPTION;
    static std::string* MY_KEY_ZMOVE;
    static std::string* MY_KEY_BUTTON5;
    static std::string* MY_KEY_BUTTON6;
    static std::string* MY_KEY_PAUSE;
    static std::string* MY_KEY_UP;
    static std::string* MY_KEY_DOWN;
    static std::string* MY_KEY_LEFT;
    static std::string* MY_KEY_RIGHT;
    static std::string* MY_KEY_UI_UP;
    static std::string* MY_KEY_UI_DOWN;
    static std::string* MY_KEY_UI_LEFT;
    static std::string* MY_KEY_UI_RIGHT;
    static std::string* MY_KEY_UI_EXECUTE;
    static std::string* MY_KEY_UI_CANCEL;
    static std::string* MY_KEY_UI_DEBUG;
    static std::string* MY_JOY_SHOT1;
    static std::string* MY_JOY_SHOT2;
    static std::string* MY_JOY_OPTION;
    static std::string* MY_JOY_ZMOVE;
    static std::string* MY_JOY_BUTTON5;
    static std::string* MY_JOY_BUTTON6;
    static std::string* MY_JOY_PAUSE;
    static std::string* MY_JOY_UI_EXECUTE;
    static std::string* MY_JOY_UI_CANCEL;

    static void load(std::string prm_ini_filename);
    static void clean();
};

}
#endif /*PROPERTIES_H_*/

