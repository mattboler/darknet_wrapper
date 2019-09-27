//#define _GLIBCXX_USE_CXX11_ABI 0

#include<iostream>
#include<fstream>

#include<opencv2/core/core.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/dnn.hpp>
#include<opencv2/imgproc.hpp>
#include "Darknet/Darknet.hpp"

using namespace std;

Darknet::Darknet()
{

}

Darknet::Darknet(string modelConfig, string modelWeights, string modelNames)
{
  bool success = Configure(modelConfig, modelWeights, modelNames);
  // TODO: Handle failure
}


bool Darknet::Configure(string modelConfig, string modelWeights, string modelNames)
{
  confidence_threshold = 0.5;

  // Create net
  cout << "Loading Network..." << endl;

  net = cv::dnn::readNetFromDarknet(modelConfig, modelWeights);
  if (net.empty())
  {
    cerr << "Can't load network by using the following files: " << endl;
    cerr << "cfg-file:     " << modelConfig << endl;
    cerr << "weights-file: " << modelWeights << endl;
    cerr << "Models can be downloaded here:" << endl;
    cerr << "https://pjreddie.com/darknet/yolo/" << endl;
    cout << "OOPS" << endl;
    return false;
  }
  cout << "Network Loaded!" << endl;

  std::ifstream classNamesFile(modelNames.c_str());
  if (classNamesFile.is_open())
  {
    std::string className = "";
    while (std::getline(classNamesFile, className))
    {
      classNamesVec.push_back(className);
    }
  }

  return true;
}

cv::Mat Darknet::Preprocess(const cv::Mat& image)
{
  cv::Mat test_image = image;
  if (image.channels() != 3)
  {
    cv::cvtColor(test_image, test_image, cv::COLOR_GRAY2BGR);
  }
  cv::Mat inputBlob = cv::dnn::blobFromImage(test_image, 1/255.F, cv::Size(416, 416), cv::Scalar(), true, false);
}


vector<pair<string, cv::Rect> > Darknet::Predict(const cv::Mat& image)
{
  vector< pair<string, cv::Rect> > results;
  // Prepare image to be fed into network
  cv::Mat inputBlob = Preprocess(image);

  // Connect image to network
  net.setInput(inputBlob, "data");

  // Run the network
  std::vector<cv::String> outNames = net.getUnconnectedOutLayersNames();
  std::vector<cv::Mat> outs;

  net.forward(outs, outNames);

  return results;
}
