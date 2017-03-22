#include <iostream>
#include <cstdlib>
using std::cin;
using std::cout;
using std::endl;

int a[1005][1005];

void search_number(int num, int &h_raw, int &h_col, int low) {
    if (h_raw < low || h_col < low) {
        cout << "false" << endl;
        return;
    }
    int mid;
    int l = low;
    for (mid = l + (h_raw - l)/2; l <= h_raw; mid = l + (h_raw - l)/2) {
        if (a[low][mid] == num) {
            cout << "true" << endl;
            return;
        } else if (a[low][mid] > num) {
            h_raw = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    l = low;
    for (mid = l + (h_col - l)/2; l <= h_col; mid = l + (h_col - l)/2) {
        if (a[mid][low] == num) {
            cout << "true" << endl;
            return;
        } else if (a[mid][low] > num) {
            h_col = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    search_number(num, h_raw, h_col, low+1);
}

void findNumber(int n, int m, int b[]) {
    int raw = n - 1;
    int col = n - 1;
    for (int i = 0; i < m; i++) {
        search_number(b[i], raw, col, 0);
    }
}

void quick_sort(int low, int hig, int arr[]) {
    if (low < hig) {
        int l = low, h = hig, num = arr[low];
        while (l < h) {
            while (l < h && num > arr[h]) h--;
            if (l < h) arr[l++] = arr[h];
            while (l < h && num < arr[l]) ++l;
            if (l < h) arr[h--] = arr[l];
        }
        arr[l] = num;
        quick_sort(low, l - 1, arr);
        quick_sort(l + 1, hig, arr);
    }
}

int main() {
    int b[10005];
    int t, n, m;
    cin >> t;
    while (t-- > 0) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> a[i][j];
            }
        }
        for (int i = 0; i < m; i++) {
            cin >> b[i];
        }
        quick_sort(0, m - 1, b);     // increase sort
        findNumber(n, m, b);
    }
    return 0;
}

