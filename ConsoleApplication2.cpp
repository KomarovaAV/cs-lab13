#include <iostream> 
#include <vector> 
#include <iomanip> 
#include <cmath>
#include <string>
#include "Console.h"

using namespace std;

void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'> " << text << "</text>" << '\n';
}

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black") {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='red' fill='#ffeeee'/>" << '\n';
}

void svg_end() {
    cout << "</svg>\n";
}
size_t find_max_count(const vector<size_t>& bins, const size_t bin_count) {
    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    return max_count;
}
void show_histogram_svg(const vector<size_t>bins) {
    const auto IMAGE_WIDTH = 1000;
    const auto IMAGE_HEIGHT = 500;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 20;
    const auto BINS_LIM = 80;

    int max_bin = bins[0];
    for (size_t bin : bins)
        if (bin > max_bin)
            max_bin = bin;
    bool scaling;
    if (max_bin > BINS_LIM)
        scaling = true;
    else
        scaling = false;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins) {
        double bin_width = BLOCK_WIDTH * bin;
        if (scaling)
            bin_width = BLOCK_WIDTH * bin / (max_bin / BINS_LIM);
        else
            bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
        top += BIN_HEIGHT;
    }
    svg_end();
}

vector<double> input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

/*void find_minmax(const vector<double>& numbers, double& min, double& max) {
    min = numbers[0];
    max = numbers[0];
    for (double x : numbers) {
        if (x < min) {
            min = x;
        }
        else if (x > max) {
            max = x;
        }
    }
}*/

vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count) {
    double min, max;
    find_minmax(numbers, min, max);

    vector<size_t> bins(bin_count);
    double bin_size = (max - min) / bin_count;

    for (size_t i = 0; i < numbers.size(); i++) {
        bool found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++) {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= numbers[i]) && (numbers[i] < hi)) {
                bins[j]++;
                found = true;
            }
        }
        if (!found) {
            bins[bin_count - 1]++;
        }
    }
    return bins;
}

void show_histogram_text(const vector<size_t>& bins) {
    for (int i = 0; i < bins.size() - 1; i++) {
        cout << bins[i] << "-";
    }
    cout << bins.back() << endl;
    vector<size_t> cumulativeTotal(bins.size());
    cumulativeTotal[0] = bins[0];
    for (int i = 1; i < bins.size(); i++) {
        cumulativeTotal[i] = cumulativeTotal[i - 1] + bins[i];
    }

    for (size_t bin : cumulativeTotal) {
        cout << setw(3) << bin << "|";
        for (int j = 0; j < bin; j++) {
            cout << "*";
        }
        cout << endl;
    }
}

int main() {
    size_t number_count;
    cin >> number_count;
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cin >> bin_count;

    const auto bins = make_histogram(numbers, bin_count);
    show_histogram_svg(bins);

    return 0;
}