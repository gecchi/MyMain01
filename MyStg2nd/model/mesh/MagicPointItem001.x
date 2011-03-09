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
  1.725625,0.000000,-0.000000,0.000000,-0.000000,1.725625,-0.000000,0.000000,0.000000,0.000000,1.725625,0.000000,3.656287,-3.582069,3.434651,1.000000;;
 }

 Mesh {
  20;
  -1.327765;-1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;-1.327765;,
  -1.327765;1.346465;1.327765;,
  1.327765;1.346466;1.327765;,
  1.327765;-1.346466;1.327765;,
  1.327765;1.346466;-1.327765;,
  1.327765;-1.346466;-1.327765;,
  1.327765;1.346466;1.327765;,
  1.327765;1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;1.327765;,
  1.327765;1.346466;1.327765;,
  -1.327765;-1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;-1.327765;,
  1.327765;1.346466;-1.327765;,
  -1.327765;-1.346466;-1.327765;,
  1.327765;-1.346466;-1.327765;;
  12;
  3;0,1,2;,
  3;3,2,1;,
  3;4,5,6;,
  3;7,6,5;,
  3;3,8,2;,
  3;9,2,8;,
  3;10,11,12;,
  3;13,12,11;,
  3;14,7,15;,
  3;5,15,7;,
  3;16,17,18;,
  3;19,18,17;;

  MeshNormals {
   6;
   -1.000000;-0.000000;0.000000;,
   1.000000;0.000000;-0.000000;,
   -0.000000;1.000000;0.000000;,
   -0.000000;-0.000000;1.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;0.000000;-1.000000;;
   12;
   3;0,0,0;,
   3;0,0,0;,
   3;1,1,1;,
   3;1,1,1;,
   3;2,2,2;,
   3;2,2,2;,
   3;3,3,3;,
   3;3,3,3;,
   3;4,4,4;,
   3;4,4,4;,
   3;5,5,5;,
   3;5,5,5;;
  }

  MeshTextureCoords {
   20;
   0.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;;
  }

  MeshMaterialList {
   1;
   12;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;

   Material {
    0.588235;0.588235;0.588235;1.000000;;
    0.100000;
    0.900000;0.900000;0.900000;;
    0.000000;0.000000;0.000000;;

    TextureFilename {
     "tile01.jpg";
    }
   }
  }
 }
}

Frame Box02 {
 

 FrameTransformMatrix {
  1.725625,0.000000,-0.000000,0.000000,-0.000000,1.725625,-0.000000,0.000000,0.000000,0.000000,1.725625,0.000000,3.656287,-3.582070,-3.569223,1.000000;;
 }

 Mesh {
  20;
  -1.327765;-1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  -1.327765;1.346466;-1.327765;,
  -1.327765;1.346466;1.327765;,
  1.327765;1.346466;1.327765;,
  1.327765;-1.346466;1.327765;,
  1.327765;1.346466;-1.327765;,
  1.327765;-1.346466;-1.327765;,
  1.327765;1.346466;1.327765;,
  1.327765;1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  1.327765;-1.346466;1.327765;,
  -1.327765;1.346466;1.327765;,
  1.327765;1.346466;1.327765;,
  -1.327765;-1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  -1.327765;1.346466;-1.327765;,
  1.327765;1.346466;-1.327765;,
  -1.327765;-1.346466;-1.327765;,
  1.327765;-1.346466;-1.327765;;
  12;
  3;0,1,2;,
  3;3,2,1;,
  3;4,5,6;,
  3;7,6,5;,
  3;3,8,2;,
  3;9,2,8;,
  3;10,11,12;,
  3;13,12,11;,
  3;14,7,15;,
  3;5,15,7;,
  3;16,17,18;,
  3;19,18,17;;

  MeshNormals {
   6;
   -1.000000;-0.000000;0.000000;,
   1.000000;0.000000;-0.000000;,
   -0.000000;1.000000;0.000000;,
   -0.000000;-0.000000;1.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;0.000000;-1.000000;;
   12;
   3;0,0,0;,
   3;0,0,0;,
   3;1,1,1;,
   3;1,1,1;,
   3;2,2,2;,
   3;2,2,2;,
   3;3,3,3;,
   3;3,3,3;,
   3;4,4,4;,
   3;4,4,4;,
   3;5,5,5;,
   3;5,5,5;;
  }

  MeshTextureCoords {
   20;
   0.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;;
  }

  MeshMaterialList {
   1;
   12;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;

   Material {
    0.588235;0.588235;0.588235;1.000000;;
    0.100000;
    0.900000;0.900000;0.900000;;
    0.000000;0.000000;0.000000;;

    TextureFilename {
     "bloack01.jpg";
    }
   }
  }
 }
}

Frame Box03 {
 

 FrameTransformMatrix {
  1.725625,0.000000,-0.000000,0.000000,-0.000000,1.725625,-0.000000,0.000000,0.000000,0.000000,1.725625,0.000000,-3.388512,-3.582069,-3.569223,1.000000;;
 }

 Mesh {
  20;
  -1.327765;-1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;-1.327765;,
  -1.327765;1.346465;1.327765;,
  1.327765;1.346465;1.327765;,
  1.327765;-1.346466;1.327765;,
  1.327765;1.346465;-1.327765;,
  1.327765;-1.346466;-1.327765;,
  1.327765;1.346465;1.327765;,
  1.327765;1.346465;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;1.327765;,
  1.327765;1.346465;1.327765;,
  -1.327765;-1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;-1.327765;,
  1.327765;1.346465;-1.327765;,
  -1.327765;-1.346466;-1.327765;,
  1.327765;-1.346466;-1.327765;;
  12;
  3;0,1,2;,
  3;3,2,1;,
  3;4,5,6;,
  3;7,6,5;,
  3;3,8,2;,
  3;9,2,8;,
  3;10,11,12;,
  3;13,12,11;,
  3;14,7,15;,
  3;5,15,7;,
  3;16,17,18;,
  3;19,18,17;;

  MeshNormals {
   6;
   -1.000000;-0.000000;0.000000;,
   1.000000;0.000000;-0.000000;,
   -0.000000;1.000000;0.000000;,
   -0.000000;-0.000000;1.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;0.000000;-1.000000;;
   12;
   3;0,0,0;,
   3;0,0,0;,
   3;1,1,1;,
   3;1,1,1;,
   3;2,2,2;,
   3;2,2,2;,
   3;3,3,3;,
   3;3,3,3;,
   3;4,4,4;,
   3;4,4,4;,
   3;5,5,5;,
   3;5,5,5;;
  }

  MeshTextureCoords {
   20;
   0.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;;
  }

  MeshMaterialList {
   1;
   12;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;

   Material {
    0.588235;0.588235;0.588235;1.000000;;
    0.100000;
    0.900000;0.900000;0.900000;;
    0.000000;0.000000;0.000000;;

    TextureFilename {
     "ice01.jpg";
    }
   }
  }
 }
}

Frame Box04 {
 

 FrameTransformMatrix {
  1.725625,0.000000,-0.000000,0.000000,-0.000000,1.725625,-0.000000,0.000000,0.000000,0.000000,1.725625,0.000000,-3.388512,-3.582069,3.434653,1.000000;;
 }

 Mesh {
  20;
  -1.327765;-1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;-1.327765;,
  -1.327765;1.346465;1.327765;,
  1.327765;1.346465;1.327765;,
  1.327765;-1.346466;1.327765;,
  1.327765;1.346465;-1.327765;,
  1.327765;-1.346466;-1.327765;,
  1.327765;1.346465;1.327765;,
  1.327765;1.346465;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;1.327765;,
  1.327765;1.346465;1.327765;,
  -1.327765;-1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;-1.327765;,
  1.327765;1.346465;-1.327765;,
  -1.327765;-1.346466;-1.327765;,
  1.327765;-1.346466;-1.327765;;
  12;
  3;0,1,2;,
  3;3,2,1;,
  3;4,5,6;,
  3;7,6,5;,
  3;3,8,2;,
  3;9,2,8;,
  3;10,11,12;,
  3;13,12,11;,
  3;14,7,15;,
  3;5,15,7;,
  3;16,17,18;,
  3;19,18,17;;

  MeshNormals {
   6;
   -1.000000;-0.000000;0.000000;,
   1.000000;0.000000;-0.000000;,
   -0.000000;1.000000;0.000000;,
   -0.000000;-0.000000;1.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;0.000000;-1.000000;;
   12;
   3;0,0,0;,
   3;0,0,0;,
   3;1,1,1;,
   3;1,1,1;,
   3;2,2,2;,
   3;2,2,2;,
   3;3,3,3;,
   3;3,3,3;,
   3;4,4,4;,
   3;4,4,4;,
   3;5,5,5;,
   3;5,5,5;;
  }

  MeshTextureCoords {
   20;
   0.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;;
  }

  MeshMaterialList {
   1;
   12;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;

   Material {
    0.588235;0.588235;0.588235;1.000000;;
    0.100000;
    0.900000;0.900000;0.900000;;
    0.000000;0.000000;0.000000;;

    TextureFilename {
     "ice02.jpg";
    }
   }
  }
 }
}

Frame Box05 {
 

 FrameTransformMatrix {
  1.725625,0.000000,-0.000000,0.000000,-0.000000,1.725625,-0.000000,0.000000,0.000000,0.000000,1.725625,0.000000,3.656287,3.527359,-3.569225,1.000000;;
 }

 Mesh {
  20;
  -1.327765;-1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;-1.327765;,
  -1.327765;1.346465;1.327765;,
  1.327765;1.346466;1.327765;,
  1.327765;-1.346466;1.327765;,
  1.327765;1.346466;-1.327765;,
  1.327765;-1.346466;-1.327765;,
  1.327765;1.346466;1.327765;,
  1.327765;1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;1.327765;,
  1.327765;1.346466;1.327765;,
  -1.327765;-1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;-1.327765;,
  1.327765;1.346466;-1.327765;,
  -1.327765;-1.346466;-1.327765;,
  1.327765;-1.346466;-1.327765;;
  12;
  3;0,1,2;,
  3;3,2,1;,
  3;4,5,6;,
  3;7,6,5;,
  3;3,8,2;,
  3;9,2,8;,
  3;10,11,12;,
  3;13,12,11;,
  3;14,7,15;,
  3;5,15,7;,
  3;16,17,18;,
  3;19,18,17;;

  MeshNormals {
   6;
   -1.000000;-0.000000;0.000000;,
   1.000000;0.000000;-0.000000;,
   -0.000000;1.000000;0.000000;,
   -0.000000;-0.000000;1.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;0.000000;-1.000000;;
   12;
   3;0,0,0;,
   3;0,0,0;,
   3;1,1,1;,
   3;1,1,1;,
   3;2,2,2;,
   3;2,2,2;,
   3;3,3,3;,
   3;3,3,3;,
   3;4,4,4;,
   3;4,4,4;,
   3;5,5,5;,
   3;5,5,5;;
  }

  MeshTextureCoords {
   20;
   0.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;;
  }

  MeshMaterialList {
   1;
   12;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;

   Material {
    0.588235;0.588235;0.588235;1.000000;;
    0.100000;
    0.900000;0.900000;0.900000;;
    0.000000;0.000000;0.000000;;

    TextureFilename {
     "tile02.jpg";
    }
   }
  }
 }
}

Frame Box06 {
 

 FrameTransformMatrix {
  1.725625,0.000000,-0.000000,0.000000,-0.000000,1.725625,-0.000000,0.000000,0.000000,0.000000,1.725625,0.000000,-3.388512,3.527359,-3.569223,1.000000;;
 }

 Mesh {
  20;
  -1.327765;-1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;-1.327765;,
  -1.327765;1.346465;1.327765;,
  1.327765;1.346465;1.327765;,
  1.327765;-1.346466;1.327765;,
  1.327765;1.346465;-1.327765;,
  1.327765;-1.346466;-1.327765;,
  1.327765;1.346465;1.327765;,
  1.327765;1.346465;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;1.327765;,
  1.327765;1.346465;1.327765;,
  -1.327765;-1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;-1.327765;,
  1.327765;1.346465;-1.327765;,
  -1.327765;-1.346466;-1.327765;,
  1.327765;-1.346466;-1.327765;;
  12;
  3;0,1,2;,
  3;3,2,1;,
  3;4,5,6;,
  3;7,6,5;,
  3;3,8,2;,
  3;9,2,8;,
  3;10,11,12;,
  3;13,12,11;,
  3;14,7,15;,
  3;5,15,7;,
  3;16,17,18;,
  3;19,18,17;;

  MeshNormals {
   6;
   -1.000000;-0.000000;0.000000;,
   1.000000;0.000000;-0.000000;,
   -0.000000;1.000000;0.000000;,
   -0.000000;-0.000000;1.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;0.000000;-1.000000;;
   12;
   3;0,0,0;,
   3;0,0,0;,
   3;1,1,1;,
   3;1,1,1;,
   3;2,2,2;,
   3;2,2,2;,
   3;3,3,3;,
   3;3,3,3;,
   3;4,4,4;,
   3;4,4,4;,
   3;5,5,5;,
   3;5,5,5;;
  }

  MeshTextureCoords {
   20;
   0.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;;
  }

  MeshMaterialList {
   1;
   12;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;

   Material {
    0.588235;0.588235;0.588235;1.000000;;
    0.100000;
    0.900000;0.900000;0.900000;;
    0.000000;0.000000;0.000000;;

    TextureFilename {
     "tile03.jpg";
    }
   }
  }
 }
}

Frame Box07 {
 

 FrameTransformMatrix {
  1.725625,0.000000,-0.000000,0.000000,-0.000000,1.725625,-0.000000,0.000000,0.000000,0.000000,1.725625,0.000000,-3.388512,3.527359,3.434651,1.000000;;
 }

 Mesh {
  20;
  -1.327765;-1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;-1.327765;,
  -1.327765;1.346465;1.327765;,
  1.327765;1.346465;1.327765;,
  1.327765;-1.346466;1.327765;,
  1.327765;1.346465;-1.327765;,
  1.327765;-1.346466;-1.327765;,
  1.327765;1.346465;1.327765;,
  1.327765;1.346465;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;1.327765;,
  1.327765;1.346465;1.327765;,
  -1.327765;-1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;-1.327765;,
  1.327765;1.346465;-1.327765;,
  -1.327765;-1.346466;-1.327765;,
  1.327765;-1.346466;-1.327765;;
  12;
  3;0,1,2;,
  3;3,2,1;,
  3;4,5,6;,
  3;7,6,5;,
  3;3,8,2;,
  3;9,2,8;,
  3;10,11,12;,
  3;13,12,11;,
  3;14,7,15;,
  3;5,15,7;,
  3;16,17,18;,
  3;19,18,17;;

  MeshNormals {
   6;
   -1.000000;-0.000000;0.000000;,
   1.000000;0.000000;-0.000000;,
   -0.000000;1.000000;0.000000;,
   -0.000000;-0.000000;1.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;0.000000;-1.000000;;
   12;
   3;0,0,0;,
   3;0,0,0;,
   3;1,1,1;,
   3;1,1,1;,
   3;2,2,2;,
   3;2,2,2;,
   3;3,3,3;,
   3;3,3,3;,
   3;4,4,4;,
   3;4,4,4;,
   3;5,5,5;,
   3;5,5,5;;
  }

  MeshTextureCoords {
   20;
   0.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;;
  }

  MeshMaterialList {
   1;
   12;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;

   Material {
    0.588235;0.588235;0.588235;1.000000;;
    0.100000;
    0.900000;0.900000;0.900000;;
    0.000000;0.000000;0.000000;;

    TextureFilename {
     "wood01.jpg";
    }
   }
  }
 }
}

Frame Box08 {
 

 FrameTransformMatrix {
  1.725625,0.000000,-0.000000,0.000000,-0.000000,1.725625,-0.000000,0.000000,0.000000,0.000000,1.725625,0.000000,3.656287,3.527360,3.434651,1.000000;;
 }

 Mesh {
  20;
  -1.327765;-1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;-1.327765;,
  -1.327765;1.346465;1.327765;,
  1.327765;1.346466;1.327765;,
  1.327765;-1.346466;1.327765;,
  1.327765;1.346466;-1.327765;,
  1.327765;-1.346466;-1.327765;,
  1.327765;1.346466;1.327765;,
  1.327765;1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;1.327765;,
  1.327765;1.346466;1.327765;,
  -1.327765;-1.346466;-1.327765;,
  -1.327765;-1.346466;1.327765;,
  -1.327765;1.346465;-1.327765;,
  1.327765;1.346466;-1.327765;,
  -1.327765;-1.346466;-1.327765;,
  1.327765;-1.346466;-1.327765;;
  12;
  3;0,1,2;,
  3;3,2,1;,
  3;4,5,6;,
  3;7,6,5;,
  3;3,8,2;,
  3;9,2,8;,
  3;10,11,12;,
  3;13,12,11;,
  3;14,7,15;,
  3;5,15,7;,
  3;16,17,18;,
  3;19,18,17;;

  MeshNormals {
   6;
   -1.000000;-0.000000;0.000000;,
   1.000000;0.000000;-0.000000;,
   -0.000000;1.000000;0.000000;,
   -0.000000;-0.000000;1.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;0.000000;-1.000000;;
   12;
   3;0,0,0;,
   3;0,0,0;,
   3;1,1,1;,
   3;1,1,1;,
   3;2,2,2;,
   3;2,2,2;,
   3;3,3,3;,
   3;3,3,3;,
   3;4,4,4;,
   3;4,4,4;,
   3;5,5,5;,
   3;5,5,5;;
  }

  MeshTextureCoords {
   20;
   0.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   0.000000;0.000000;;
  }

  MeshMaterialList {
   1;
   12;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;

   Material {
    0.588235;0.588235;0.588235;1.000000;;
    0.100000;
    0.900000;0.900000;0.900000;;
    0.000000;0.000000;0.000000;;

    TextureFilename {
     "wood02.jpg";
    }
   }
  }
 }
}