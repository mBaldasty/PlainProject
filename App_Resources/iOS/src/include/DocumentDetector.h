#ifndef DOCUMENT_DETECTOR_H
#define DOCUMENT_DETECTOR_H

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

template <class T>
T& make_ref(T&& x) { return x; }

namespace detector {

    class DocumentDetector {
    public:

        DocumentDetector(cv::Mat &bitmap, int resizeThreshold, int imageRotation);
        DocumentDetector(int resizeThreshold, int imageRotation);


        virtual ~DocumentDetector();

        vector<vector<cv::Point>> scanPoint(Mat &edged);
        vector<vector<cv::Point>> scanPoint();
        cv::Mat image;

    private:
        float resizeScale = 1.0f;
        int resizeThreshold = 500;
        int imageRotation = 0;
        int areaScaleMinFactor = 6;
        double contoursApproxEpsilonFactor = 0.03;
        bool isHisEqual = false;

        cv::Mat resizeImage();

        void preProcess(Mat src, Mat &dst);


        void findThreshSquares(cv::Mat srcGray, double scaledWidth, double scaledHeight,
                               std::vector<std::vector<cv::Point>> &threshSquares);

        void findCannySquares(
                cv::Mat srcGray,
                double scaledWidth,
                double scaledHeight,
                std::vector<std::vector<cv::Point>> &cannySquares,
                int indice,
                std::vector<int> &indices);
        void findSquares(
                cv::Mat srcGray,
                double scaledWidth,
                double scaledHeight,
                std::vector<std::pair<std::vector<cv::Point>, double>> &squares);

        cv::Mat preprocessedImage(cv::Mat &image, int cannyValue, int blurValue);

        cv::Point choosePoint(cv::Point center, std::vector<cv::Point> &points, int type);

        std::vector<cv::Point> selectPoints(std::vector<cv::Point> points);

        std::vector<cv::Point> sortPointClockwise(std::vector<cv::Point> vector);

        long long pointSideLine(cv::Point &lineP1, cv::Point &lineP2, cv::Point &point);
    };

}

#endif //CROPPER_DOC_SCANNER_H
