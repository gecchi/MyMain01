#ifndef GGAFDX9COMMONHEADER_H_
#define GGAFDX9COMMONHEADER_H_

#include "GgafCommonHeader.h"



#define DIRECTINPUT_VERSION 0x0800
#define ANGLE0 (0)
#define ANGLE360 (360000)
#define ANGLE45 (45000)
#define ANGLE90 (90000)
#define ANGLE135 (135000)
#define ANGLE180 (180000)
#define ANGLE225 (225000)
#define ANGLE270 (270000)
#define ANGLE315 (315000)


#define S_ANG0 (0)
#define S_ANG360 (3600)
#define S_ANG45 (450)
#define S_ANG90 (900)
#define S_ANG135 (1350)
#define S_ANG180 (1800)
#define S_ANG225 (2250)
#define S_ANG270 (2700)
#define S_ANG315 (3150)

#define ANGLE_RATE (100)

#define ANGLE_PI (180000)
#define ANGLE_2PI (360000)

#define LEN_UNIT (1000)
#define PX_UNIT (10)
#define PI (3.14159265358979)

#include <dxerr9.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <dsound.h>
#include <dxfile.h>


class CmRandomNumberGenerator;


#include "ogg/os_types.h"
#include "ogg/ogg.h"
#include "vorbis/codec.h"
#include "vorbis/vorbisenc.h"
#include "vorbis/vorbisfile.h"

//class CWaveDecorder;
//class CC3DSound;
//class CC3DSoundBufferSE;
//class CC3DSoundSE;

//
//#include "jp/ggaf/dx9core/sound/wavedecorder.h"
//#include "jp/ggaf/dx9core/sound/c3dsound.h"

class GgafDx9CriticalException;
class GgafDx9God;
class GgafDx9Input;
class GgafDx9Sound;
class GgafDx9ModelManager;
class GgafDx9MainActor;
class GgafDx9UntransformedActor;
class GgafDx9MeshActor;
class GgafDx9DynaMeshActor;
class GgafDx9CubeActor;
class GgafDx9SpriteActor;
class GgafDx9SquareActor;
class GgafDx9TransformedActor;
class GgafDx9PlateActor;
class GgafDx9Model;
class GgafDx9MeshModel;
class GgafDx9SpriteModel;
class GgafDx9SquareModel;
class GgafDx9PlateModel;
class GgafDx9Scene;
class GgafDx9World;
class GgafDx9Util;
class GgafDx9SphereRadiusVectors;
class GgafDx9Properties;
class GgafDx9GeometryMover;
class GgafDx9GeometryChecker;
class GgafDx9RectUV;


class CWaveDecorder;
class GgafDx9Sound;
class GgafDx9Se;
class GgafDx9Bgm;
class GgafDx9SeManager;
class GgafDx9BgmManager;

class DixComPtr;
class DixSmartPtr;
class PCMDecoder;
class PCMPlayer;
class OggDecoder;
class OggVorbisResource;
class OggVorbisFile;
class OggVorbisMemory;


#include "jp/ggaf/dx9core/exception/GgafDx9CriticalException.h"
#include "jp/ggaf/dx9core/util/CmRandomNumberGenerator.h"
#include "jp/ggaf/dx9core/GgafDx9God.h"
#include "jp/ggaf/dx9core/util/GgafDx9Input.h"
#include "jp/ggaf/dx9core/model/GgafDx9ModelManager.h"
#include "jp/ggaf/dx9core/actor/GgafDx9MainActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9UntransformedActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9MeshActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9DynaMeshActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9CubeActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9SpriteActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9SquareActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9TransformedActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9PlateActor.h"
#include "jp/ggaf/dx9core/model/GgafDx9Model.h"
#include "jp/ggaf/dx9core/model/GgafDx9MeshModel.h"
#include "jp/ggaf/dx9core/model/GgafDx9SpriteModel.h"
#include "jp/ggaf/dx9core/model/GgafDx9SquareModel.h"
#include "jp/ggaf/dx9core/model/GgafDx9PlateModel.h"
#include "jp/ggaf/dx9core/scene/GgafDx9Scene.h"
#include "jp/ggaf/dx9core/scene/GgafDx9World.h"
#include "jp/ggaf/dx9core/util/GgafDx9Util.h"
#include "jp/ggaf/dx9core/util/GgafDx9SphereRadiusVectors.h"
#include "jp/ggaf/dx9core/util/GgafDx9Properties.h"
#include "jp/ggaf/dx9core/util/GgafDx9GeometryMover.h"
#include "jp/ggaf/dx9core/util/GgafDx9GeometryChecker.h"

#include "jp/ggaf/dx9core/model/GgafDx9RectUV.h"
//#include "jp/ggaf/dx9core/sound/c3dsound.hpp"
//#include "jp/ggaf/dx9core/sound/oggdecorder.hpp"
//#include "jp/ggaf/dx9core/sound/wavedecorder.hpp"
//




#include "jp/ggaf/dx9core/sound/PCMDecoder.h"
#include "jp/ggaf/dx9core/sound/PCMPlayer.h"
#include "jp/ggaf/dx9core/sound/OggDecoder.h"
#include "jp/ggaf/dx9core/sound/OggVorbisResource.h"
#include "jp/ggaf/dx9core/sound/OggVorbisFile.h"
#include "jp/ggaf/dx9core/sound/OggVorbisMemory.h"
#include "jp/ggaf/dx9core/sound/CWaveDecorder.h"



#include "jp/ggaf/dx9core/sound/GgafDx9Sound.h"
#include "jp/ggaf/dx9core/sound/GgafDx9Se.h"
#include "jp/ggaf/dx9core/sound/GgafDx9Bgm.h"
#include "jp/ggaf/dx9core/sound/GgafDx9SeManager.h"
#include "jp/ggaf/dx9core/sound/GgafDx9BgmManager.h"
#endif /*GGAFDX9COMMONHEADER_H_*/
