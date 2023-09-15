#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    do {
        swapped = false;
        for (int i = 1; i < n; ++i) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        --n;
    } while (swapped);
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void shellSort(vector<int>& arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void optimizedBubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    do {
        swapped = false;
        for (int i = 1; i < n; ++i) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        --n;
    } while (swapped);
}

void insertionSortShift(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = key;
    }
}

void insertionSortBinary(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int left = 0;
        int right = i - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] > key) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        for (int j = i - 1; j >= left; --j) {
            arr[j + 1] = arr[j];
        }

        arr[left] = key;
    }
}

vector<int> shellSedgewick(int n) {
    vector<int> gaps;
    int k = 0;
    int gap = 0;

    while (gap < n) {
        if (k % 2 == 0) {
            gap = 9 * (1 << k) - 9 * (1 << (k / 2)) + 1;
        } else {
            gap = 8 * (1 << k) - 6 * (1 << ((k + 1) / 2)) + 1;
        }

        gaps.push_back(gap);
        ++k;
    }

    return gaps;
}

vector<int> shellPratt(int n) {
    vector<int> gaps;
    int gap = 1;

    while (gap <= n) {
        gaps.push_back(gap);
        gap = 2 * gap;
    }

    return gaps;
}

void shellSortGaps(vector<int>& arr, const vector<int>& gaps) {
    int n = arr.size();
    for (int gap : gaps) {
        for (int i = gap; i < n; ++i) {
            int key = arr[i];
            int j = i;

            while (j >= gap && arr[j - gap] > key) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = key;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    double N = 100000;

    vector<int> arr(N);

    // Генерация случайных чисел и заполнение массива
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1, N); // Замените 1 и 100 на желаемый диапазон
    for (int i = 0; i < N; ++i) {
        arr[i] = distribution(gen);
    }

    // BubbleSort
    auto start = chrono::high_resolution_clock::now();

    bubbleSort(arr);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "BubbleSort time: " << duration.count() << " ms." << endl;
    // Сброс массива
    random_shuffle(arr.begin(), arr.end());

    // InsertionSort
    start = chrono::high_resolution_clock::now();

    insertionSort(arr);

    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "InsertionSort time: " << duration.count() << " ms." << endl;
    random_shuffle(arr.begin(), arr.end());

    // shellSort
    start = chrono::high_resolution_clock::now();

    shellSort(arr);

    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "shellSort time: " << duration.count() << " ms." << endl;
    random_shuffle(arr.begin(), arr.end());

    // optimizedBubbleSort
    start = chrono::high_resolution_clock::now();

    optimizedBubbleSort(arr);

    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "optimizedBubbleSort time: " << duration.count() << " ms." << endl;
    random_shuffle(arr.begin(), arr.end());

    // insertionSortShift
    start = chrono::high_resolution_clock::now();

    insertionSortShift(arr);

    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "insertionSortShift time: " << duration.count() << " ms." << endl;
    random_shuffle(arr.begin(), arr.end());

    // insertionSortBinary
    start = chrono::high_resolution_clock::now();

    insertionSortBinary(arr);

    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "insertionSortBinary time: " << duration.count() << " ms." << endl;
    random_shuffle(arr.begin(), arr.end());

    // shellSedgewick
    start = chrono::high_resolution_clock::now();

    vector<int> gaps = shellSedgewick(arr.size());
    shellSortGaps(arr, gaps);

    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "shellSedgewick1 time: " << duration.count() << " ms." << endl;
    random_shuffle(arr.begin(), arr.end());

    // shellPratt
    start = chrono::high_resolution_clock::now();

    gaps = shellPratt(arr.size());
    shellSortGaps(arr, gaps);

    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "shellPratt time: " << duration.count() << " ms." << endl;

//    for (int num : arr) {
//        cout << num << " ";
//    }

    return 0;
}
