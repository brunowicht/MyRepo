void settings() {
  size(500, 500, P3D);
}
void setup() {
  noStroke();
}
void draw() {
  background(200);
  translate(width/2, height/2, 0);
  rotateX(PI/8);
  rotateY(PI/8);
  box(100, 80, 60);
  translate(100, 0, 0);
  sphere(50);
}