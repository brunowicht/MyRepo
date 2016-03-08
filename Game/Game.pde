float depth = 500;
float side = 200;
float high = 20;
void settings() {
  size(500, 500, P3D);
}
void setup() {
  noStroke();
}
void draw() {
  camera(width/2, height/2, depth, 250, 250, 0, 0, 1, 0);
  directionalLight(50, 100, 125, 0, -1, 0);
  ambientLight(102, 102, 102);
  background(200);
  translate(width/2, height/2, 0);
  float rz = map(mouseY, 0, height, 0, PI);
  float ry = map(mouseX, 0, width, 0, PI);
  rotateZ(rz);
  rotateY(ry);
  box(side, high, side);
}