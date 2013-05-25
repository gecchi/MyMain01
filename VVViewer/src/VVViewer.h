#ifndef VVVIEWER_H_
#define VVVIEWER_H_
#include "VVViewer.h"

/**
 * モデルビューワー
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */

#include "GgafLibCommonHeader.h"

#undef P_GOD
#define P_GOD ((VVViewer::VvvGod*)VVViewer::VvvGod::_pGod)
#undef P_UNIVERSE
#define P_UNIVERSE ((VVViewer::VvvUniverse*)(P_GOD->_pUniverse))

namespace VVViewer {
class VvvGod;
class VvvUniverse;
class VvvWorld;
class VvvCamera;
class VvvCursor;
class VvvGrid;
class VvvCamWorker;
}

#endif /*VVVIEWER_H_*/
