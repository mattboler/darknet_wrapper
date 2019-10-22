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

  return inputBlob;
}


vector<pair<string, cv::Rect> > Darknet::Predict(const cv::Mat& image)
{
  // Prepare image to be fed into network
  cv::Mat inputBlob = Preprocess(image);

  // Connect image to network
  net.setInput(inputBlob, "data");

  // Run the network
  std::vector<cv::String> outNames = net.getUnconnectedOutLayersNames();
  std::vector<int> outLayers = net.getUnconnectedOutLayers();
  std::string outLayerType = net.getLayer(outLayers[0])->type;
  std::cout << "Type: " << outLayerType << std::endl;


  std::vector<cv::Mat> outs;
  net.forward(outs, outNames);
  std::vector<std::pair<std::string, cv::Rect>> results;
  results = Postprocess(image, outs);

  return results;
}

std::vector<std::pair<std::string, cv::Rect>> Darknet::Postprocess(const cv::Mat& image, const vector<cv::Mat>& outs)
{
  std::vector<std::pair<std::string, cv::Rect>> results;
  
  for (size_t i = 0; i < outs.size(); ++i)
  {
    float* data = (float*)outs[i].data;
    for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
    {
      cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
      cv::Point classIdPoint;
      double confidence;
      cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
      if (confidence > confidence_threshold)
      {
        int centerX = (int)(data[0] * image.cols);
        int centerY = (int)(data[1] * image.rows);
        int width = (int)(data[2] * image.cols);
        int height = (int)(data[3] * image.rows);
        int left = centerX - width / 2;
        int top = centerY - height / 2;

        cv::Rect temp_rect = cv::Rect(left, top, width, height);
        std::string temp_name = classNamesVec[classIdPoint.x];
        std::pair<std::string, cv::Rect> temp_pair = std::make_pair(temp_name, temp_rect);
        results.push_back(temp_pair);
      }
    }
  }

  return results;
}
