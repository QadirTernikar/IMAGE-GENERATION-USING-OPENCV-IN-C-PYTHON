#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class ImageProcessor {
public:
    static void applyGrayscale(Mat& image) {
        cvtColor(image, image, COLOR_BGR2GRAY);
        cvtColor(image, image, COLOR_GRAY2BGR);  // Convert back to BGR for consistency
    }

    static void applySobelEdgeDetection(Mat& image) {
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);

        Mat grad_x, grad_y;
        Mat abs_grad_x, abs_grad_y;

        Sobel(gray, grad_x, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);
        convertScaleAbs(grad_x, abs_grad_x);

        Sobel(gray, grad_y, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);
        convertScaleAbs(grad_y, abs_grad_y);

        Mat grad;
        addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

        cvtColor(grad, image, COLOR_GRAY2BGR);
    }
};

void displayMenu() {
    cout << "\nImage Processing Application\n";
    cout << "1. Load Image\n";
    cout << "2. Save Image\n";
    cout << "3. Apply Grayscale Filter\n";
    cout << "4. Apply Sobel Edge Detection\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Mat img;
    string filename;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter filename to load: ";
            cin >> filename;
            img = imread(filename);
            if (img.empty()) {
                cerr << "Error loading image " << filename << endl;
            } else {
                cout << "Image loaded successfully.\n";
            }
            break;
        case 2:
            if (!img.empty()) {
                cout << "Enter filename to save: ";
                cin >> filename;
                if (imwrite(filename, img)) {
                    cout << "Image saved successfully to " << filename << endl;
                } else {
                    cerr << "Error saving image " << filename << endl;
                }
            } else {
                cout << "No image loaded.\n";
            }
            break;
        case 3:
            if (!img.empty()) {
                ImageProcessor::applyGrayscale(img);
                cout << "Applied grayscale filter.\n";
            } else {
                cout << "No image loaded.\n";
            }
            break;
        case 4:
            if (!img.empty()) {
                ImageProcessor::applySobelEdgeDetection(img);
                cout << "Applied Sobel edge detection.\n";
            } else {
                cout << "No image loaded.\n";
            }
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}