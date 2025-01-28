#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

// 抽出する画像の輝度値の範囲を指定
#define B_MAX 255
#define B_MIN 100
#define G_MAX 100
#define G_MIN 0
#define R_MAX 100
#define R_MIN 0

int main() {
    VideoCapture cap(0); // カメラデバイスをオープン（0はデフォルトカメラ）
    if (!cap.isOpened()) {
        printf("カメラが開けませんでした。");
        return -1;
    }

    Mat frame;
    while (true) {
        cap >> frame; // カメラからフレームを取得
        if (frame.empty()) {
            printf("フレームが取得できませんでした。");
            break;
        }

        imshow("カメラ画像", frame); // フレームを表示
        
        // 結果保存用Matを定義
        Mat mask_image, output_image_rgb;

        // inRangeを用いてフィルタリング
        Scalar s_min = Scalar(B_MIN, G_MIN, R_MIN);
        Scalar s_max = Scalar(B_MAX, G_MAX, R_MAX);
        inRange(frame, s_min, s_max, mask_image);

        // マスク画像を表示
        namedWindow("mask");
        imshow("mask", mask_image);
        imwrite("mask.jpg", mask_image);

        // マスクを基に入力画像をフィルタリング
        frame.copyTo(output_image_rgb, mask_image);

        // 結果の表示と保存
        // ウィンドウを作成
        namedWindow("output");
        // outputウィンドウに画像を表示
        imshow("output", output_image_rgb);
        // フィルタリングされた画像をoutput.jpgという名前で保存
        imwrite("output.jpg", output_image_rgb);

        if (cv::waitKey(10) == 27) { // ESCキーが押されたらループを終了
            break;
        }
    }

    cap.release(); // カメラデバイスを解放
    destroyAllWindows(); // すべてのウィンドウを閉じる

	return 0;
}

