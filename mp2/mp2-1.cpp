#include "Image.h"

using namespace cs225;

int main() {
  Image alma;

  alma.readFromFile("alma.png");
  alma.lighten(0.2);
  alma.writeToFile("lighten.png");

  alma.readFromFile("alma.png");
  alma.saturate(0.2);
  alma.writeToFile("saturate.png");

  alma.readFromFile("alma.png");
  alma.scale(2);
  cout<<alma.width()<<endl;
  alma.writeToFile("scale2x.png");

  alma.readFromFile("alma.png");
  alma.scale(450,300);
  cout<<alma.width()<<alma.height()<<endl;
  alma.writeToFile("scale100.png");

  return 0;
}
