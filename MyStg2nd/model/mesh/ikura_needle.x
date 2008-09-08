xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 12;
 -0.70000;0.00000;-0.80000;,
 -0.30000;0.50000;-1.00000;,
 -0.20000;0.00000;-1.30000;,
 0.30000;0.50000;-1.00000;,
 0.70000;0.00000;-0.80000;,
 0.20000;0.00000;-1.30000;,
 0.20000;0.00000;1.30000;,
 0.70000;0.00000;0.80000;,
 0.30000;0.50000;1.00000;,
 -0.70000;0.00000;0.80000;,
 -0.20000;0.00000;1.30000;,
 -0.30000;0.50000;1.00000;;
 
 9;
 3;0,1,2;,
 3;3,4,5;,
 3;6,7,8;,
 3;9,10,11;,
 4;10,6,8,11;,
 4;11,8,3,1;,
 4;11,1,0,9;,
 4;8,7,4,3;,
 4;1,3,5,2;;
 
 MeshMaterialList {
  2;
  9;
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0;;
  Material {
   1.000000;0.420000;0.141000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.105000;0.035250;;
  }
  Material {
   1.000000;0.925000;0.651000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.231250;0.162750;;
  }
 }
 MeshNormals {
  13;
  -0.792181;0.486200;-0.368861;,
  -0.573496;0.553902;-0.603568;,
  -0.366484;0.423711;-0.828347;,
  0.573496;0.553902;-0.603568;,
  0.792181;0.486200;-0.368861;,
  0.366484;0.423711;-0.828347;,
  0.366484;0.423711;0.828347;,
  0.792181;0.486200;0.368861;,
  0.573496;0.553902;0.603568;,
  -0.792181;0.486200;0.368861;,
  -0.366484;0.423711;0.828347;,
  -0.573496;0.553902;0.603568;,
  0.000000;1.000000;0.000000;;
  9;
  3;0,1,2;,
  3;3,4,5;,
  3;6,7,8;,
  3;9,10,11;,
  4;10,6,8,11;,
  4;12,12,12,12;,
  4;11,1,0,9;,
  4;8,7,4,3;,
  4;1,3,5,2;;
 }
 MeshTextureCoords {
  12;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;;
 }
}
