#define _GLIBCXX_USE_CXX11_ABI 0

#include<iostream>
#include<fstream>

#include<opencv2/core/core.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/dnn.hpp>
#include<opencv2/imgproc.hpp>
#include "Darknet/Darknet.hpp"

using namespace std;

Darknet::Darknet(string modelConfig, string modelWeights, string modelNames)
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
        exit(-1);
    }
    cout << "Network Loaded!" << endl;
    
    // Create classNamesVec
    std::vector<std::string> classNamesVec;
    std::ifstream classNamesFile(modelNames.c_str());
    if (classNamesFile.is_open())
    {
        std::string className = "";
        while (std::getline(classNamesFile, className))
            classNamesVec.push_back(className);
    }
}

Darknet::Darknet()
{

}

bool Darknet::Configure(string modelConfig, string modelWeights, string modelNames)
{
  // do stuff
}


vector<pair<string, cv::Rect> > Darknet::Predict(const cv::Mat& image)
{
    vector< pair<string, cv::Rect> > results;

    cv::Mat test_image = image;
    
    // Preprocessing
    if (image.channels() != 3)
    {
        cv::cvtColor(test_image, test_image, cv::COLOR_GRAY2BGR);
    }
    
    cv::Mat inputBlob = cv::dnn::blobFromImage(test_image, 1/255.F, cv::Size(416, 416), cv::Scalar(), true, false);
    net.setInput(inputBlob, "data");

    // Run the network
    cv::Mat detectionMat = net.forward("detection_out");

    for (int i = 0; i < detectionMat.rows; i++)
    {
        const int probability_index = 5;
        const int probability_size = detectionMat.cols - probability_index;
        float *prob_array_ptr = &detectionMat.at<float>(i, probability_index);

        size_t objectClass = max_element(prob_array_ptr, prob_array_ptr+probability_size)-prob_array_ptr;
        float confidence = detectionMat.at<float>(i, (int)objectClass + probability_index);

        if (confidence > confidence_threshold)
        {
            float x_center = detectionMat.at<float>(i, 0) * test_image.cols;
            float y_center = detectionMat.at<float>(i, 1) * test_image.rows;
            float width = detectionMat.at<float>(i, 2) * test_image.cols;
            float height = detectionMat.at<float>(i, 3) * test_image.rows;
            cv::Point p1(cvRound(x_center - width / 2), cvRound(y_center - height / 2));
            cv::Point p2(cvRound(x_center + width / 2), cvRound(y_center + height / 2));
            cv::Rect object(p1, p2);
            string class_name = ""; // TODO: Find class name
            pair<string, cv::Rect> result = make_pair(class_name, object);
            results.push_back(result);
        }
    }

    return results;
}
