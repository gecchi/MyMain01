#ifndef VVVIEWER_H_
#define VVVIEWER_H_

/**
 * モデルビューワー
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */

#include "GgafLibCommonHeader.h"

#define KIND_2DFIX_MOUSE_POINTER             (0x4U)   // 00000000 00000000 00000000 00000100
#define KIND_ACTOR                 (0x8U)   // 00000000 00000000 00000000 00001000

namespace VVViewer {
class VvvCaretaker;
class VvvSpacetime;
class VvvWorld;
class VvvCamera;
class VvvCameraViewPoint;
class VvvCameraUpVector;
class VvvCursor;
class VvvGrid;
class VvvCamWorker;
class Font01;
class VvvMousePointer;
}

#endif /*VVVIEWER_H_*/
