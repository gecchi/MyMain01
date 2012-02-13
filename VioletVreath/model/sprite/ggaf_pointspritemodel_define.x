xof 0303txt 0032

template Vector {
  <3d82ab5e-62da-11cf-ab39-0020af71e433>
  FLOAT x;
  FLOAT y;
  FLOAT z;
}

template ColorRGBA {
  <35ff44e0-6c7c-11cf-8f52-0040333594a3>
  FLOAT red;
  FLOAT green;
  FLOAT blue;
  FLOAT alpha;
}

template PointSpriteDef {
  <E4EECE4C-E106-11DC-9B62-346D55D89593>
  FLOAT  SquareSize;
  STRING TextureFile;
  DWORD  TextureSplitRowCol;
  DWORD  VerticesNum;
  array  Vector    Vertices[VerticesNum];
  array  ColorRGBA VertexColors[VerticesNum];
  array  DWORD     InitUvPtnNo[VerticesNum];
  array  FLOAT     InitScale[VerticesNum];
}

