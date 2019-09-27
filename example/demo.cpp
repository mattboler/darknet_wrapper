#include <iostream>
#include <vector> // For std::vector
#include <utility> // For std::pair

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "Darknet/Darknet.hpp"


int main(int argc, char** argv)
{
  std::string modelConfig, modelWeights, modelNames, imageName;
  modelConfig = "yolov3-tiny.cfg";
  modelWeights = "yolov3-tiny.weights";
  modelNames = "coco.names";
  imageName = "dog.jpg";


  Darknet net = Darknet();
  net.Configure(modelConfig, modelWeights, modelNames);

  return 0;
}

