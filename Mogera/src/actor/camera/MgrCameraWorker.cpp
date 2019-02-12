#include "MgrCameraWorker.h"



using namespace GgafLib;
using namespace Mogera;

MgrCameraWorker::MgrCameraWorker(const char* prm_name, MgrCamera* prm_pCamera) : AroundViewCamWorker(prm_name, (DefaultCamera*)prm_pCamera) {
    _class_name = "MgrCameraWorker";
}

MgrCameraWorker::~MgrCameraWorker() {

}
