void settings() {
  fullScreen(P2D);
}
void setup () {
}
My3DPoint eye = new My3DPoint(0, 0, 5000);
My3DPoint origin = new My3DPoint(0, 0, 0);
My3DBox input3DBox = new My3DBox(origin, 100, 150, 300);



void draw() {
  background(255, 255, 255);
  My3DBox box = transformBox(input3DBox, translationMatrix(width/2, height/2, 0));
  strokeWeight(3);
  projectBox(eye, box).render();
}



void keyPressed() {
  float angle = PI/20;
  if (keyCode == UP) {
    input3DBox = transformBox(input3DBox, rotateXMatrix(-angle));
  }
  if (keyCode == RIGHT) {
    input3DBox = transformBox(input3DBox, rotateYMatrix(angle));
  }
  if (keyCode == LEFT) {
    input3DBox = transformBox(input3DBox, rotateYMatrix(-angle));
  }
  if (keyCode == DOWN) {
    input3DBox = transformBox(input3DBox, rotateXMatrix(angle));
  }
}

class My2DPoint {
  float x;
  float y;

  My2DPoint(float x, float y) {
    this.x = x;
    this.y = y;
  }
}

class My3DPoint {
  float x;
  float y;
  float z;

  My3DPoint(float x, float y, float z) {
    this.x = x;
    this.y = y;
    this.z = z;
  }
}
My2DPoint projectPoint(My3DPoint eye, My3DPoint p) {
  float x = (p.x - eye.x)/(1 + (p.z/eye.z));
  float y = (p.y - eye.y)/(1 + (p.z/eye.z));
  return new My2DPoint(x, y);
}

class My2DBox {
  My2DPoint[] s;
  My2DBox(My2DPoint[] s) {
    this.s = s;
  }
  void render() {
    for (int i = 0; i<4; ++i) {
      int j = (i+1)%4;
      stroke(color(0, 100, 200));
      line(s[i].x, s[i].y, s[j].x, s[j].y);
      i = i+4;
      j = j+4;
      stroke(color(200, 0, 100));
      line(s[i].x, s[i].y, s[j].x, s[j].y);
      i = i-4;
      j = j-4;
    }
    for (int i = 0; i < 4; ++i) {
      int j = i+4;
      stroke(color(100, 200, 0));
      line(s[i].x, s[i].y, s[j].x, s[j].y);
    }
  }
}

class My3DBox {
  My3DPoint[] p;
  My3DBox(My3DPoint origin, float dimX, float dimY, float dimZ) {
    float x = origin.x;
    float y = origin.y;
    float z = origin.z;
    this.p = new My3DPoint[]{new My3DPoint(x, y+dimY, z+dimZ), 
      new My3DPoint(x, y, z+dimZ), 
      new My3DPoint(x+dimX, y, z+dimZ), 
      new My3DPoint(x+dimX, y+dimY, z+dimZ), 
      new My3DPoint(x, y+dimY, z), 
      origin, 
      new My3DPoint(x+dimX, y, z), 
      new My3DPoint(x+dimX, y+dimY, z)
    };
  }
  My3DBox(My3DPoint[] p) {
    this.p = p;
  }
}

My2DBox projectBox (My3DPoint eye, My3DBox box) {
  My2DPoint[] points = new My2DPoint[8];
  for (int i = 0; i < box.p.length; ++i) {
    points[i] = projectPoint(eye, box.p[i]);
  }
  return new My2DBox(points);
}

float[] homogeneous3DPoint (My3DPoint p) {
  float[] result = {p.x, p.y, p.z, 1};
  return result;
}

float[][] rotateXMatrix(float angle) {
  return(new float[][] {{1, 0, 0, 0}, 
    {0, cos(angle), sin(angle), 0}, 
    {0, -sin(angle), cos(angle), 0}, 
    {0, 0, 0, 1}});
}
float[][] rotateYMatrix(float angle) {
  return(new float[][] {{cos(angle), 0, sin(angle), 0}, {0, 1, 0, 0}, {-sin(angle), 0, cos(angle), 0}, {0, 0, 0, 1}});
}
float[][] rotateZMatrix(float angle) {
  return(new float[][]{{cos(angle), sin(angle), 0, 0}, {-sin(angle), cos(angle), 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});
}
float[][] scaleMatrix(float x, float y, float z) {
  return(new float[][]{{x, 0, 0, 0}, {0, y, 0, 0}, {0, 0, z, 0}, {0, 0, 0, 1}});
}
float[][] translationMatrix(float x, float y, float z) {
  return(new float[][]{{1, 0, 0, x}, {0, 1, 0, y}, {0, 0, 1, z}, {0, 0, 0, 1}});
}

float[] matrixProduct(float[][] a, float[] b) {
  float[] result = new float[4];
  for (int i = 0; i < 4; ++i) {
    float res = 0.0;
    for (int j = 0; j < 4; ++j) {
      res = res + a[i][j] * b[j];
    }
    result[i] = res;
  }
  return result;
}


My3DPoint euclidian3DPoint (float[] a) {
  My3DPoint result = new My3DPoint(a[0]/a[3], a[1]/a[3], a[2]/a[3]);
  return result;
}

My3DPoint transformPoint (My3DPoint p, float[][] transformMatrix) {
  float[] vec = new float[]{p.x, p.y, p.z, 1};
  return euclidian3DPoint(matrixProduct(transformMatrix, vec));
}

My3DBox transformBox(My3DBox box, float[][] transformMatrix) {
  int l = box.p.length;
  My3DPoint[] p = new My3DPoint[l];
  for (int i = 0; i < l; ++i) {
    p[i] = transformPoint(box.p[i], transformMatrix);
  }
  return new My3DBox(p);
}