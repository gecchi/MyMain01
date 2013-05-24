/////////////////////////////////////////////////////////
// TBox_Textures.h
// Toolbox for converting textures formats
//
/////////////////////////////////////////////////////////

/* IMPORTANT NOTE:
Before loading, 16 bit textures should be converted to RGB
since all texture conversion function accept a 24 bit texture
as an entry.
*/
#ifndef TBOX_TEXTURES_H
#define TBOX_TEXTURES_H

#include "jp/ggaf/dxcore/util/XFile/framework/frm_types.h"

namespace ToolBox {

class ConvText {
    public:
       ConvText(void): _tColor(0) {};
      void SetTranspColor(uint8_t pr, uint8_t pg, uint8_t pb){_tColor = (pr<<16)+(pg<<8)+pb;};
      void Convert(TEXTURE* pText, uint8_t pType);
   private:
      uint32_t _tColor; //32 bit color
      //Conversion functions
      void RGB2RGBA(TEXTURE* pText);
      void RGB2A(TEXTURE* pText);
      void RGB2LA(TEXTURE* pText);
};/**/

};

#endif
