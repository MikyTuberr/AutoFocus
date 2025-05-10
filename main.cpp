#include <opencv2/opencv.hpp>
#include <iostream>

double calculateFocusScore(const cv::Mat& image) {
    cv::Mat gray, laplacian;

    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    cv::Laplacian(gray, laplacian, CV_64F);

    cv::Scalar mean, stddev;
    cv::meanStdDev(laplacian, mean, stddev);
    return stddev[0] * stddev[0];
}

int main() {
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT); // turning off opencv logs

    const char* filenames[] = {
        "images/1.png",
        "images/1b.png",
        "images/1c.png",
        "images/1d.png",
        "images/1e.png"
    };

    int n = sizeof(filenames) / sizeof(filenames[0]);

    for (int i = 0; i < n; i++) {
        const char* filename = filenames[i];
        cv::Mat image = cv::imread(filename);
        if (image.empty()) {
            std::cerr << "Error loading file: " << filename << "\n";
            continue;
        }

        double focus = calculateFocusScore(image);
        std::cout << filename << "Focus: " << focus << std::endl;
    }

    return 0;
}