#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

struct Pixel
{
    int r, g, b;
};

class Image
{
private:
    int width, height;
    vector<vector<Pixel>> pixels;

public:

    Image()
    {
        width = 0;
        height = 0;
    }

    // Load PPM Image
    bool loadImage(string filename)
    {
        ifstream file(filename);

        if (!file)
        {
            cout << "Error: Cannot open image!\n";
            return false;
        }

        string format;
        file >> format;

        if (format != "P3")
        {
            cout << "Only PPM P3 images are supported.\n";
            return false;
        }

        int maxValue;
        file >> width >> height >> maxValue;

        pixels.resize(height, vector<Pixel>(width));

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                file >> pixels[i][j].r;
                file >> pixels[i][j].g;
                file >> pixels[i][j].b;
            }
        }

        file.close();

        cout << "Image loaded successfully!\n";
        return true;
    }

    // Display Image Information
    void displayImage()
    {
        cout << "\nImage Information\n";
        cout << "Width  : " << width << endl;
        cout << "Height : " << height << endl;

        cout << "\nFirst few pixels:\n";

        for (int i = 0; i < min(height, 5); i++)
        {
            for (int j = 0; j < min(width, 5); j++)
            {
                cout << "("
                     << pixels[i][j].r << ","
                     << pixels[i][j].g << ","
                     << pixels[i][j].b << ") ";
            }
            cout << endl;
        }
    }

    // Grayscale
    void grayscale()
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int gray =
                    0.299 * pixels[i][j].r +
                    0.587 * pixels[i][j].g +
                    0.114 * pixels[i][j].b;

                pixels[i][j].r = gray;
                pixels[i][j].g = gray;
                pixels[i][j].b = gray;
            }
        }

        cout << "Grayscale applied!\n";
    }

    // Brightness
    void adjustBrightness(int value)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                pixels[i][j].r =
                    clamp(pixels[i][j].r + value, 0, 255);

                pixels[i][j].g =
                    clamp(pixels[i][j].g + value, 0, 255);

                pixels[i][j].b =
                    clamp(pixels[i][j].b + value, 0, 255);
            }
        }

        cout << "Brightness adjusted!\n";
    }

    // Contrast
    void adjustContrast(double factor)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                pixels[i][j].r =
                    clamp((int)((pixels[i][j].r - 128)
                    * factor + 128), 0, 255);

                pixels[i][j].g =
                    clamp((int)((pixels[i][j].g - 128)
                    * factor + 128), 0, 255);

                pixels[i][j].b =
                    clamp((int)((pixels[i][j].b - 128)
                    * factor + 128), 0, 255);
            }
        }

        cout << "Contrast adjusted!\n";
    }

    // Blur
    void blur()
    {
        vector<vector<Pixel>> temp = pixels;

        for (int i = 1; i < height - 1; i++)
        {
            for (int j = 1; j < width - 1; j++)
            {
                int r = 0, g = 0, b = 0;

                for (int x = -1; x <= 1; x++)
                {
                    for (int y = -1; y <= 1; y++)
                    {
                        r += pixels[i + x][j + y].r;
                        g += pixels[i + x][j + y].g;
                        b += pixels[i + x][j + y].b;
                    }
                }

                temp[i][j].r = r / 9;
                temp[i][j].g = g / 9;
                temp[i][j].b = b / 9;
            }
        }

        pixels = temp;

        cout << "Blur applied!\n";
    }

    // Sharpen
    void sharpen()
    {
        vector<vector<Pixel>> temp = pixels;

        for (int i = 1; i < height - 1; i++)
        {
            for (int j = 1; j < width - 1; j++)
            {
                int r =
                    5 * pixels[i][j].r
                    - pixels[i - 1][j].r
                    - pixels[i + 1][j].r
                    - pixels[i][j - 1].r
                    - pixels[i][j + 1].r;

                int g =
                    5 * pixels[i][j].g
                    - pixels[i - 1][j].g
                    - pixels[i + 1][j].g
                    - pixels[i][j - 1].g
                    - pixels[i][j + 1].g;

                int b =
                    5 * pixels[i][j].b
                    - pixels[i - 1][j].b
                    - pixels[i + 1][j].b
                    - pixels[i][j - 1].b
                    - pixels[i][j + 1].b;

                temp[i][j].r = clamp(r, 0, 255);
                temp[i][j].g = clamp(g, 0, 255);
                temp[i][j].b = clamp(b, 0, 255);
            }
        }

        pixels = temp;

        cout << "Sharpen applied!\n";
    }

    // Crop
    void crop(int x, int y, int newWidth, int newHeight)
    {
        if (x < 0 || y < 0 ||
            x + newWidth > width ||
            y + newHeight > height)
        {
            cout << "Invalid crop dimensions!\n";
            return;
        }

        vector<vector<Pixel>> cropped(
            newHeight,
            vector<Pixel>(newWidth));

        for (int i = 0; i < newHeight; i++)
        {
            for (int j = 0; j < newWidth; j++)
            {
                cropped[i][j] =
                    pixels[y + i][x + j];
            }
        }

        pixels = cropped;

        width = newWidth;
        height = newHeight;

        cout << "Image cropped!\n";
    }

    // Resize
    void resizeImage(int newWidth, int newHeight)
    {
        vector<vector<Pixel>> resized(
            newHeight,
            vector<Pixel>(newWidth));

        for (int i = 0; i < newHeight; i++)
        {
            for (int j = 0; j < newWidth; j++)
            {
                int oldX = j * width / newWidth;
                int oldY = i * height / newHeight;

                resized[i][j] =
                    pixels[oldY][oldX];
            }
        }

        pixels = resized;

        width = newWidth;
        height = newHeight;

        cout << "Image resized!\n";
    }

    // Save Image
    void saveImage(string filename)
    {
        ofstream file(filename);

        file << "P3\n";
        file << width << " " << height << "\n";
        file << "255\n";

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                file << pixels[i][j].r << " "
                     << pixels[i][j].g << " "
                     << pixels[i][j].b << " ";
            }

            file << "\n";
        }

        file.close();

        cout << "Image saved successfully!\n";
    }
};

int main()
{
    Image image;

    string filename;

    cout << "====================================\n";
    cout << "       IMAGE PROCESSING TOOL\n";
    cout << "====================================\n";

    cout << "Enter PPM image filename: ";
    cin >> filename;

    if (!image.loadImage(filename))
    {
        return 0;
    }

    int choice;

    do
    {
        cout << "\n========== MENU ==========\n";
        cout << "1. Display Image Information\n";
        cout << "2. Grayscale\n";
        cout << "3. Blur\n";
        cout << "4. Sharpen\n";
        cout << "5. Brightness\n";
        cout << "6. Contrast\n";
        cout << "7. Crop\n";
        cout << "8. Resize\n";
        cout << "9. Save Image\n";
        cout << "10. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            image.displayImage();
            break;

        case 2:
            image.grayscale();
            break;

        case 3:
            image.blur();
            break;

        case 4:
            image.sharpen();
            break;

        case 5:
        {
            int value;

            cout << "Enter brightness (-255 to 255): ";
            cin >> value;

            image.adjustBrightness(value);

            break;
        }

        case 6:
        {
            double factor;

            cout << "Enter contrast factor: ";
            cin >> factor;

            image.adjustContrast(factor);

            break;
        }

        case 7:
        {
            int x, y, w, h;

            cout << "Enter X: ";
            cin >> x;

            cout << "Enter Y: ";
            cin >> y;

            cout << "Enter Width: ";
            cin >> w;

            cout << "Enter Height: ";
            cin >> h;

            image.crop(x, y, w, h);

            break;
        }

        case 8:
        {
            int w, h;

            cout << "Enter new width: ";
            cin >> w;

            cout << "Enter new height: ";
            cin >> h;

            image.resizeImage(w, h);

            break;
        }

        case 9:
        {
            string output;

            cout << "Enter output filename: ";
            cin >> output;

            image.saveImage(output);

            break;
        }

        case 10:
            cout << "Thank you for using Image Processing Tool!\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 10);

    return 0;
}
