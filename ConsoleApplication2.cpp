#include <iostream>  
#include <vector>  
#include <iomanip>  

using namespace std;

vector<double> input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

void find_minmax(const vector<double>& numbers, double& min, double& max) {
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
}

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
    const auto /*vector<double>*/ numbers = input_numbers(number_count);

    size_t bin_count;
    cin >> bin_count;

    const auto /*vector<size_t>*/ bins = make_histogram(numbers, bin_count);
    show_histogram_text(bins);

    return 0;
}