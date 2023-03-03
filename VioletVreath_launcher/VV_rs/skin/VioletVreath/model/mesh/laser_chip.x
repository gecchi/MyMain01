xof 0303txt 0032
template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}


Frame Box01 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh {
  16;
  0.000000;0.000000;0.000000;,
  0.000010;0.000000;0.000000;,
  0.000000;0.000000;0.050000;,
  0.000010;0.000000;0.050000;,
  0.000000;0.000000;0.000000;,
  0.000010;0.000000;0.000000;,
  0.000000;0.050000;0.000000;,
  0.000010;0.050000;0.000000;,
  0.000000;0.000000;0.000000;,
  0.000010;0.000000;0.000000;,
  0.000000;-0.050000;0.000000;,
  0.000010;-0.050000;0.000000;,
  0.000000;0.000000;0.000000;,
  0.000010;0.000000;0.000000;,
  0.000000;0.000000;-0.050000;,
  0.000010;0.000000;-0.050000;;

  8;
  3;0,1,2;,
  3;3,2,1;,
  3;4,5,6;,
  3;7,6,5;,
  3;8,9,10;,
  3;11,10,9;,
  3;12,13,14;,
  3;15,14,13;;

  MeshNormals {
   16;
   0.000000;-1.000000;0.000000;,
   0.000000;-1.000000;0.000000;,
   0.000000;-1.000000;0.000000;,
   0.000000;-1.000000;0.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;-1.000000;,
   0.000000;0.000000;-1.000000;,
   0.000000;0.000000;-1.000000;,
   0.000000;0.000000;-1.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;;
   8;
   3;0,1,2;,
   3;3,2,1;,
   3;4,5,6;,
   3;7,6,5;,
   3;8,9,10;,
   3;11,10,9;,
   3;12,13,14;,
   3;15,14,13;;
  }

  MeshTextureCoords {
   16;
   0.501000;0.501000;,
   0.999000;0.501000;,
   0.501000;0.999000;,
   0.999000;0.999000;,
   0.501000;0.501000;,
   0.999000;0.501000;,
   0.501000;0.999000;,
   0.999000;0.999000;,
   0.501000;0.501000;,
   0.999000;0.501000;,
   0.501000;0.999000;,
   0.999000;0.999000;,
   0.501000;0.501000;,
   0.999000;0.501000;,
   0.501000;0.999000;,
   0.999000;0.999000;;
  }

  MeshMaterialList {
   1;
   8;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;

   Material {
    1.000000;1.000000;1.000000;1.000000;;
    5.000000;
    0.000000;0.000000;0.000000;;
    0.000000;0.000000;0.000000;;
    TextureFilename {
     "laserchip128_hosoi.png";
    }
   }
  }
 }
}