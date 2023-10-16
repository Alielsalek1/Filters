#include <bits/stdc++.h>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
char imageFileName[100];

int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};

enum Color {
    BLACK = 0,
    WHITE = 255
};

void loadImage();

void saveImage();

//------------------------------------------------

void blackWhite();

void invert();

void merge();

void flipImage();

void rotate();

void darkenOrLighten();

void shrink();

void blur();

void detectEdges();

void enlarge();

void shuffle();

void skewHorizontally();

void skewVertically();

//-------------------------------------------------

void systemRun();

char menu();

int main() {
    cout << "Ahlan ya User ya habibi\n";
    loadImage();
    while (true)
        systemRun();
}

//--------------------------------------------------------

void loadImage() {
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void saveImage() {
    char imageFileName[100];
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//--------------------------------------------------------

void blackWhite() {
    // loop on all the pixels and for every pixel's Grayscale larger than 115 make it black else it is white
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (image[i][j] > 115) image[i][j] = WHITE;
            else image[i][j] = BLACK;
        }
    }
}

void invert() {
    for (auto &i: image)
        for (auto &j: i)
            j = WHITE - j;
}

void flipImage() {
    cout << "Flip (h)orizontally or (v)ertically ? ";
    char choice;
    cin >> choice;
    // change the number i with SIZE - i - 1 to flip either vertically or horizontally
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < (SIZE - 1) / 2; ++j) {
            if (choice == 'h')
                swap(image[i][j], image[i][SIZE - j - 1]);
            else
                swap(image[j][i], image[SIZE - j - 1][i]);
        }
    }
}

void rotate() {
    cout << "Rotate (90), (180) or (270) degrees?\n";
    int rotate;
    cin >> rotate;
    while (rotate) {
        rotate -= 90;
        unsigned char img[SIZE][SIZE];
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                img[j][SIZE - i - 1] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = img[i][j];
            }
        }
    }
}

void detectEdges() {
    unsigned char temp[SIZE][SIZE];
    /* for every pixel if it has a large difference any of its 4 neighbors (up, down, left and right)
    then mark it as an edge*/
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            temp[i][j] = WHITE;
            // looping on 4 directions using direction array
            for (int k = 0; k < 4; ++k) {
                int nx = i + dx[k], ny = j + dy[k];
                // check that the new index is in range
                if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && abs(image[i][j] - image[nx][ny]) >= 47)
                    temp[i][j] = BLACK;
            }
        }
    }
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            image[i][j] = temp[i][j];
}

void mirrorImage() {
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side ? ";
    char choice;
    cin >> choice;
    // in any of the 4 cases you copy pixels to the other side
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < (SIZE - 1) / 2; ++j) {
            if (choice == 'l') {
                image[i][SIZE - j - 1] = image[i][j];
            } else if (choice == 'r') {
                image[i][j] = image[i][SIZE - j - 1];
            } else if (choice == 'u') {
                image[SIZE - j - 1][i] = image[j][i];
            } else {
                image[j][i] = image[SIZE - j - 1][i];
            }
        }
    }
}

void cropImage() {
    cout << "Please enter x y l w: ";
    int x, y, l, w;
    cin >> x >> y >> l >> w;
    x--, y--;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            // if you are in range leave the image else just
            if (i >= x && i <= x + w && j >= y && j <= y + w) continue;
            image[i][j] = WHITE;
        }
    }
}

void enlarge() {
    // loops on the specific quadrant and makes all the uncolored adjacent pixels the same color.
    unsigned char enlarged[SIZE][SIZE];
    cout << "Which quarter to enlarge 1, 2, 3 or 4?\n";
    int x;
    cin >> x;
    vector<int> posx{0, 1, 1, 0}, posy{1, 0, 1, 0};
    int h1, h2, v1, v2;
    switch (x) {
        case 1:
            h1 = 0, h2 = SIZE / 2, v1 = 0, v2 = SIZE / 2;
            break;
        case 2:
            h1 = 0, h2 = SIZE / 2, v1 = SIZE / 2, v2 = SIZE;
            break;
        case 3:
            h1 = SIZE / 2, h2 = SIZE, v1 = 0, v2 = SIZE / 2;
            break;
        case 4:
            h1 = SIZE / 2, h2 = SIZE, v1 = SIZE / 2, v2 = SIZE;
            break;
    }
    for (int i = h1; i < h2; ++i) {
        for (int j = v1; j < v2; ++j) {
            for (int k = 0; k < 4; ++k) {
                enlarged[(i - h1) * 2 + posx[k]][(j - v1) * 2 + posy[k]] = image[i][j];
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = enlarged[i][j];
        }
    }
}

void shuffle() {
    // This function stores quadrants in an image vector with their new given order.
    cout << "New order of quarters ? 4 3 2 1\n";
    vector<int> order(4);
    for (auto &i: order)cin >> i;

    // this is the image vector and the position vectors so we can reorder the image.
    const int half = SIZE / 2;
    unsigned char img [4][SIZE][SIZE];
    vector<int>
            x1{0, 0, half, half}
    , x2{half, half, SIZE, SIZE}
    , y1{0, half, 0, half}
    , y2{half, SIZE, half, SIZE};

    for (int k = 0; k < 4; k++) {
        int h1, h2, v1, v2;
        switch (order[k]) {
            case 1:
                h1 = 0, h2 = half, v1 = 0, v2 = half;
                break;
            case 2:
                h1 = 0, h2 = half, v1 = half, v2 = SIZE;
                break;
            case 3:
                h1 = half, h2 = SIZE, v1 = 0, v2 = half;
                break;
            case 4:
                h1 = half, h2 = SIZE, v1 = half, v2 = SIZE;
                break;
        }
        // this part is where each quadrant is stored in the image vector.
        vector<vector<unsigned char>> quadrant(half, vector<unsigned char>(SIZE / 2));
        int x = 0, y = 0;
        for (int i = h1; i < h2; ++i, ++x) {
            y = 0;
            for (int j = v1; j < v2; ++j, ++y) {
                quadrant[x][y] = image[i][j];
            }
        }
        for(int i=0;i<half;i++){
            for(int j=0;j<half;j++){
                img[k][i][j]=quadrant[i][j];
            }
        }
    }
    // here we overwrite the image with the quadrants we saved.
    for (int i = 0; i < 4; i++) {
        int x = 0, y = 0;
        for (int j = x1[i]; j < x2[i]; ++j, ++x) {
            y = 0;
            for (int k = y1[i]; k < y2[i]; ++k, ++y) {
                if (x < half && y < half) {
                    image[j][k] = img[i][x][y];
                }
            }
        }
    }
}

// Merge two grayscale images by averaging their pixel values.
void merge() {
    char filename2[100];

    cout << "Enter the filename of the image that you want to merge with: ";
    cin >> filename2;
    unsigned char image2[SIZE][SIZE];
    strcat(filename2, ".bmp");
    readGSBMP(filename2, image2);

    // Iterate over pixels and calculate the average.
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
}

// Allow the user to either darken or lighten the image based on their choice.
void darkenOrLighten() {
    cout << "(d)arken or (l)ighten the image ? ";
    char option;
    cin >> option;

    // Iterate over each pixel in the image and apply the chosen operation.
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (option == 'l') image[i][j] = min(255, int(1.5 * image[i][j]));
            else if (option == 'd') image[i][j] *= 0.5;
        }
    }
}

void shrink() {
    cout << "Shrink the image to (1/2), (1/3) or (1/4) of the original image ? ";
    string s;
    cin >> s;

    // Extract the desired shrink ratio from user input
    int ratio = s.back() - '0';
    int newImageSize = (SIZE + (ratio - 1)) / ratio;

    unsigned char newImage[newImageSize][newImageSize];

    // Copy the pixels from the original image and skip number of pixels based on the desired ratio
    for (int i = 0; i < SIZE; i += ratio)
        for (int j = 0; j < SIZE; j += ratio)
            newImage[i / ratio][j / ratio] = image[i][j];

    // Update the original image with the resized image, filling the remaining area with white
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            image[i][j] = i >= newImageSize or j >= newImageSize ? WHITE : newImage[i][j];

}

// Apply a simple blur effect to the image.
void blur() {
    unsigned char newImage[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int sum = image[i][j];
            int count = 1;

            // Iterate over neighboring pixels to calculate the average value of them
            for (int k = 0; k < 8; ++k) {
                int x = i + dx[k];
                int y = j + dy[k];

                // Check if neighboring pixel coordinates are within image boundaries.
                if (x >= 0 and x < SIZE and y >= 0 and y < SIZE) sum += image[x][y], ++count;
            }
            // Store the average pixel value in the new image.
            newImage[i][j] = sum / count;
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = newImage[i][j];
        }
    }
}

// Skew the image horizontally by a specified degree to the right.
void skewHorizontally() {
    cout << "Please enter the degree to skew right: ";
    long double degree;
    cin >> degree;

    long double pi = 3.1415926535897932384626433832795;

    // Convert user-input degree to radians (rad), ensuring it's within 45 degrees.
    long double rad = (degree > 45 ? int(degree) % 45 : degree) * pi / 180;

    // Calculate the amount of whitespace added due to skew
    int whiteSpace = SIZE * tan(rad);
    int newImageSize = SIZE - whiteSpace;

    if (degree == 45) {
        // If the degree is 45, fill the entire image with white pixels
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = (i + j == 255 ? image[i][j] : WHITE);
            }
        }
        return;
    }

    unsigned char newImage[SIZE][newImageSize];

    // Calculate the ratio between the original image size and the skewed image size
    double ratio = double(SIZE) / double(newImageSize);

    // Copy pixels from the original image to the skewed image using the calculated ratio
    int cnt = 0;
    for (double j = 0; j < SIZE; j += ratio, cnt++) {
        for (int i = 0; i < SIZE and cnt < newImageSize; ++i) {
            newImage[i][cnt] = image[i][int(j)];
        }
    }

    // Adjust the skewed image by filling empty spaces with white pixels.
    for (int i = 0; i < SIZE; i++) {
        int empty = (SIZE - i) * tan(rad);
        int count = 0;
        for (int j = 0; j < SIZE; j++) {
            if (j < empty)
                image[i][j] = WHITE;
            else if (count < newImageSize)
                image[i][j] = newImage[i][count++];
            else
                image[i][j] = WHITE;
        }
    }
}

void skewVertically() {
    cout << "Please enter the degree to skew up: ";
    long double degree;
    cin >> degree;

    long double pi = 3.1415926535897932384626433832795;

    // Convert user-input degree to radians (rad), ensuring it's within 45 degrees.
    long double rad = (degree > 45 ? int(degree) % 45 : degree) * pi / 180;

    // Calculate the amount of whitespace added due to skew
    int whiteSpace = SIZE * tan(rad);
    int newImageSize = SIZE - whiteSpace;

    if (degree == 45) {
        // If the degree is 45, fill the diagonal with the centered pixel
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[j][i] = (i + j == 255 ? image[j][i] : WHITE);
            }
        }
        return;
    }

    unsigned char newImage[newImageSize][SIZE];

    // Calculate the ratio between the original image size and the skewed image size
    double ratio = double(SIZE) / double(newImageSize);

    // Copy pixels from the original image to the skewed image using the calculated ratio
    int cnt = 0;
    for (double i = 0; i < SIZE; i += ratio, cnt++) {
        for (int j = 0; j < SIZE and cnt < newImageSize; j++) {
            newImage[cnt][j] = image[int(i)][j];
        }
    }

    // Adjust the skewed image by filling empty spaces with white pixels.
    for (int i = 0; i < SIZE; i++) {
        int empty = (SIZE - i) * tan(rad);
        int count = 0;
        for (int j = 0; j < SIZE; j++) {
            if (j < empty)
                image[j][i] = WHITE;
            else if (count < newImageSize)
                image[j][i] = newImage[count++][i];
            else
                image[j][i] = WHITE;
        }
    }
}

//--------------------------------------------
char menu() {
    cout << "Please select a filter to apply or 0 to exit:\n";
    cout << "1 - BLACK & White filter\n";
    cout << "2 - Invert filter\n";
    cout << "3 - Merge filter\n";
    cout << "4 - Flip Image\n";
    cout << "5 - Rotate Image\n";
    cout << "6 - Darken and Lighten Image\n";
    cout << "7 - Detect Image edges\n";
    cout << "8 - Enlarge Image\n";
    cout << "9 - Shrink Image\n";
    cout << "a - Mirror 1/2 Image\n";
    cout << "b - Shuffle Image\n";
    cout << "c - Blur Image\n";
    cout << "d - Crop Image\n";
    cout << "e - Skew Image Right\n";
    cout << "f - Skew Image Up\n";
    cout << "s - Save the image to a file\n";
    cout << "0 - Exit\n";

    char choice;
    cin >> choice;
    return choice;
}

void systemRun() {
    char choice = menu();
    switch (choice) {
        case '1':
            blackWhite();
            break;
        case '2':
            invert();
            break;
        case '3':
            merge();
            break;
        case '4':
            flipImage();
            break;
        case '5':
            rotate();
            break;
        case '6':
            darkenOrLighten();
            break;
        case '7':
            detectEdges();
            break;
        case '8':
            enlarge();
            break;
        case '9':
            shrink();
            break;
        case 'a':
            mirrorImage();
            break;
        case 'b':
            shuffle();
            break;
        case 'c':
            blur();
            break;
        case 'd':
            cropImage();
            break;
        case 'e':
            skewHorizontally();
            break;
        case 'f':
            skewVertically();
            break;
        case 's':
            saveImage();
            break;
        case '0':
            exit(0);
    }
}
