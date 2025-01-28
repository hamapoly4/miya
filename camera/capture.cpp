#include <opencv2/opencv.hpp>
#include <stdio.h>

int main() {
    cv::VideoCapture cap(0); // カメラデバイスをオープン（0はデフォルトカメラ）
    if (!cap.isOpened()) {
        printf("カメラが開けませんでした。");
        return -1;
    }

    cv::Mat frame;
    while (true) {
        cap >> frame; // カメラからフレームを取得
        if (frame.empty()) {
            printf("フレームが取得できませんでした。");
            break;
        }

        cv::imshow("カメラ画像", frame); // フレームを表示

        if (cv::waitKey(1) == 27) { // ESCキーが押されたらループを終了
            break;
        }
    }

    cap.release(); // カメラデバイスを解放
    cv::destroyAllWindows(); // すべてのウィンドウを閉じる

    return 0;
}
