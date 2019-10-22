#ifndef DARKNET_HPP
#define DARKNET_HPP

#include<opencv2/core/core.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/dnn.hpp>
#include<opencv2/imgproc.hpp>

using namespace std;

class Darknet
{
  public:
    Darknet();
    Darknet(string modelConfig, string modelWeights, string modelNames);
    bool Configure(string modelConfig, string modelWeights, string modelNames);
    std::vector<std::pair<std::string, cv::Rect> > Predict(const cv::Mat& image);
  private:
    cv::dnn::Net net;
    vector<string> classNamesVec;
    float confidence_threshold;
    cv::Mat Preprocess(const cv::Mat& image);
    std::vector<std::pair<std::string, cv::Rect>> Postprocess(const cv::Mat& image, const vector<cv::Mat>& outs);
};

#endif
