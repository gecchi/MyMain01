#include "stdafx.h"
using namespace VVViewer;
using namespace std;

VvvWorld::VvvWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    getDirector()->addSubGroup(NEW VvvCamWorker("VvvCamWorker"));
    DefaultPointSpriteTestActor* p = new DefaultPointSpriteTestActor("hoehoe");

    getDirector()->addSubGroup(p);

    vb_ = NEW GgafLib::VirtualButton();
    GgafLib::VirtualButton::_tagKeymap.BUTTON1 = DIK_SPACE; //ボタン１=スペースキー とする。

}

void VvvWorld::initialize() {
}

void VvvWorld::processBehavior() {
    vb_->update(); //入力状況更新
    if (VvvGod::is_wm_dropfiles_) {
        char drive[16];
        char folder[256];
        char filename[256];
        char extention[256];
        //パスを分割
        _splitpath( VvvGod::dropfiles_, drive, folder, filename, extention );
        _TRACE_("drive="<<drive<<" folder="<<folder<<" filename="<<filename<<" extention="<<extention);
        string model_id = filename;
        string model_type = extention;


        string dir_mesh_model0 = GGAF_PROPERTY(DIR_MESH_MODEL[0]);
        string dir_mesh_model1 = GGAF_PROPERTY(DIR_MESH_MODEL[1]);
        string dir_sprite_model0 = GGAF_PROPERTY(DIR_SPRITE_MODEL[0]);
        string dir_sprite_model1 = GGAF_PROPERTY(DIR_SPRITE_MODEL[1]);
        string dir_texture0 = GGAF_PROPERTY(DIR_TEXTURE[0]);
        string dir_texture1 = GGAF_PROPERTY(DIR_TEXTURE[1]);
        GGAF_PROPERTY(DIR_MESH_MODEL[0])   = string(drive) + string(folder);
        GGAF_PROPERTY(DIR_MESH_MODEL[1])   = string(drive) + string(folder);
        GGAF_PROPERTY(DIR_SPRITE_MODEL[0]) = string(drive) + string(folder);
        GGAF_PROPERTY(DIR_SPRITE_MODEL[1]) = string(drive) + string(folder);
        GGAF_PROPERTY(DIR_TEXTURE[0])      = string(drive) + string(folder);
        GGAF_PROPERTY(DIR_TEXTURE[1])      = string(drive) + string(folder) + "/../" + GGAF_PROPERTY(DIRNAME_RESOURCE_SKIN_XXX_TEXTURE) + "/";
        ::transform(model_type.begin(), model_type.end(), model_type.begin(), toupper);
        ::transform(model_id.begin(), model_id.end(), model_id.begin(), toupper);
        GgafDxCore::GgafDxDrawableActor* pActor = NULL;
        if (model_type == ".X") {
//            if (model_id.find("WORLDBOUND") == std::string::npos) {
//                pActor = createInFactory2(GgafLib::WorldBoundActor, "actor", filename);
//            } else {
                pActor = createInFactory2(GgafLib::DefaultMeshActor, "actor", filename);
//            }
        } else if (model_type == ".SPRX") {
            pActor = createInFactory2(GgafLib::DefaultSpriteActor, "actor", filename);
        } else if (model_type == ".PSPRX") {
            pActor = createInFactory2(GgafLib::DefaultPointSpriteActor, "actor", filename);
        } else {
        }

        if (pActor) {
            getDirector()->addSubGroup(pActor);
            _list.addLast(pActor, false);
        }

        GGAF_PROPERTY(DIR_MESH_MODEL[0])   = dir_mesh_model0;
        GGAF_PROPERTY(DIR_MESH_MODEL[1])   = dir_mesh_model1;
        GGAF_PROPERTY(DIR_SPRITE_MODEL[0]) = dir_sprite_model0;
        GGAF_PROPERTY(DIR_SPRITE_MODEL[1]) = dir_sprite_model1;
        GGAF_PROPERTY(DIR_TEXTURE[0])      = dir_texture0;
        GGAF_PROPERTY(DIR_TEXTURE[1])      = dir_texture1;


        VvvGod::is_wm_dropfiles_ = false;
    }
}

VvvWorld::~VvvWorld() {
}
