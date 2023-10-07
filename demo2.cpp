#include <bits/stdc++.h>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
char imageFileName[100];

int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};

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
    // loop on all of the pixels and every pixel's Grayscale larger than 115 make it black else it is white
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (image[i][j] > 115) image[i][j] = 255;
            else image[i][j] = 0;
        }
    }
}

void invert() {
    for (auto &i: image)
        for (auto &j: i)
            j = 255 - j;
}

void flipImage() {
    cout << "Flip (h)orizontally or (v)ertically ? ";
    char choice;
    cin >> choice;
    // change the number i with SIZE - i - 1 to flip (math)
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
        unsigned char zeft[SIZE][SIZE];
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                zeft[j][SIZE - i - 1] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = zeft[i][j];
            }
        }
    }
}

void detectEdges() {
    unsigned char temp[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            temp[i][j] = 255;
            for (int k = 0; k < 4; ++k) {
                int nx = i + dx[k], ny = j + dy[k];
                if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && abs(image[i][j] - image[nx][ny]) >= 47)
                    temp[i][j] = 0;
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
            if (i >= x && i <= x + w && j >= y && j <= y + w) continue;
            image[i][j] = 255;
        }
    }
}

void enlarge() {
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
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {

        }
    }
}

void merge() {
    char filename2[100];

    cout << "Enter the filename of the image that you want to merge with: ";
    cin >> filename2;
    unsigned char image2[SIZE][SIZE];
    strcat(filename2, ".bmp");
    readGSBMP(filename2, image2);

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
}

void darkenOrLighten() {
    cout << "(d)arken or (l)ighten the image ? ";
    char option;
    cin >> option;
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

    int ratio = s.back() - '0';
    int newImageSize = (SIZE + (ratio - 1)) / ratio;
    unsigned char newImage[newImageSize][newImageSize];

    for (int i = 0; i < SIZE; i += ratio)
        for (int j = 0; j < SIZE; j += ratio)
            newImage[i / ratio][j / ratio] = image[i][j];


    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            image[i][j] = i >= newImageSize or j >= newImageSize ? 255 : newImage[i][j];

}

void blur() {
    unsigned char newImage[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int sum = image[i][j];
            int count = 1;
            for (int k = 0; k < 8; ++k) {
                int x = i + dx[k];
                int y = j + dy[k];
                if (x >= 0 and x < SIZE and y >= 0 and y < SIZE) sum += image[x][y], ++count;
            }
            newImage[i][j] = sum / count;
        }
    }
}

void skewHorizontally() {
    cout << "Please enter the degree to skew right: ";
    long double degree;
    cin >> degree;

    long double pi = 3.1415926535897932384626433832795;

    long double rad = (degree > 45 ? int(degree) % 45 : degree) * pi / 180;

    int whiteSpace = SIZE * tan(rad);
    int newImageSize = SIZE - whiteSpace;

    if(degree == 45){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = 255;
            }
        }
        return;
    }

    unsigned char newImage[SIZE][newImageSize];

    double ratio = double(SIZE) / double(newImageSize);


    for (int i = 0; i < SIZE; ++i) {
        for (double j = 0; j < SIZE; j += ratio) {
            newImage[i][int(j / ratio)] = image[i][int(j)];
        }
    }



//
//    for (int i = 0; i < SIZE; ++i) {
//        for (int j = 0; j < SIZE; ++j) {
//            if (j % ratio == 0) continue;
//            else newImage[i][j - j / ratio ] = image[i][j];
//        }
//    }

    for (int i = 0; i < SIZE; i++) {
        int empty = (SIZE - i) * tan(rad);
        int count = 0;
        for (int j = 0; j < SIZE; j++) {
            if (j < empty)
                image[i][j] = 255;
            else if (count < newImageSize)
                image[i][j] = newImage[i][count++];
            else
                image[i][j] = 255;
        }
    }
}

void skewVertically() {
    cout << "Please enter the degree to skew up: ";
    long double degree;
    cin >> degree;
    long double pi = 3.1415926535897932384626433832795;
    long double rad = degree * pi / 180;

    int whiteSpace = SIZE * tan(rad);
    int newImageSize = SIZE - whiteSpace;

    unsigned char newImage[newImageSize][SIZE];

    int mod = SIZE / newImageSize;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (j % mod == 0) continue;
            else newImage[j - j / mod][i] = image[i][j];
        }
    }

    for (int i = 0; i < SIZE; i++) {
        int empty = (SIZE - i) * tan(rad);
        int count = 0;
        for (int j = 0; j < SIZE; j++) {
            if (j < empty)
                image[i][j] = 255;
            else if (count < newImageSize)
                image[i][j] = newImage[i][count++];
            else
                image[i][j] = 255;
        }
    }

}

//--------------------------------------------
char menu() {
    cout << "Please select a filter to apply or 0 to exit:\n";
    cout << "1 - Black & White filter\n";
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
