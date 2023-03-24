#ifndef CONFIG_H_
#define CONFIG_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/LibConfig.h"

#ifdef CONFIG
    #undef CONFIG
#endif
#define CONFIG VioletVreath::Config

namespace VioletVreath {

class Config: public GgafLib::LibConfig {
public:
    static std::string MY_KEY_SHOT1;
    static std::string MY_KEY_SHOT2;
    static std::string MY_KEY_OPTION;
    static std::string MY_KEY_VIEW;
    static std::string MY_KEY_TURBO;
    static std::string MY_KEY_POWERUP;
    static std::string MY_KEY_BUTTON7;
    static std::string MY_KEY_BUTTON8;
    static std::string MY_KEY_PAUSE;
    static std::string MY_KEY_UP;
    static std::string MY_KEY_DOWN;
    static std::string MY_KEY_LEFT;
    static std::string MY_KEY_RIGHT;
    static std::string MY_KEY_VIEW_UP;
    static std::string MY_KEY_VIEW_DOWN;
    static std::string MY_KEY_VIEW_LEFT;
    static std::string MY_KEY_VIEW_RIGHT;
    static std::string MY_KEY_UI_UP;
    static std::string MY_KEY_UI_DOWN;
    static std::string MY_KEY_UI_LEFT;
    static std::string MY_KEY_UI_RIGHT;
    static std::string MY_KEY_UI_EXECUTE;
    static std::string MY_KEY_UI_CANCEL;
    static std::string MY_KEY_UI_DEBUG;
    static std::string MY_JOY_SHOT1;
    static std::string MY_JOY_SHOT2;
    static std::string MY_JOY_OPTION;
    static std::string MY_JOY_VIEW;
    static std::string MY_JOY_TURBO;
    static std::string MY_JOY_POWERUP;
    static std::string MY_JOY_BUTTON7;
    static std::string MY_JOY_BUTTON8;
    static std::string MY_JOY_PAUSE;
    static std::string MY_JOY_UP;
    static std::string MY_JOY_DOWN;
    static std::string MY_JOY_LEFT;
    static std::string MY_JOY_RIGHT;
    static std::string MY_JOY_VIEW_UP;
    static std::string MY_JOY_VIEW_DOWN;
    static std::string MY_JOY_VIEW_LEFT;
    static std::string MY_JOY_VIEW_RIGHT;
    static std::string MY_JOY_UI_UP;
    static std::string MY_JOY_UI_DOWN;
    static std::string MY_JOY_UI_LEFT;
    static std::string MY_JOY_UI_RIGHT;
    static std::string MY_JOY_UI_EXECUTE;
    static std::string MY_JOY_UI_CANCEL;
    //static std::string MY_JOY_UI_DEBUG;

public:
    static void loadProperties(std::string prm_ini_filename); //shadows
};

}
#endif /*CONFIG_H_*/

