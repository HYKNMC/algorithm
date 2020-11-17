#include <cstdio>
#include <iostream>
using namespace std;

int maxSubSum(int num[], int n) {
  int max = 0;
  int temp[n] = {0};
  temp[0] = num[0];
  /* 求到当前数为止的最大字段和 */
  for (int i = 1; i < n; i++) {
    temp[i] = temp[i - 1] > 0 ? temp[i - 1] + num[i] : num[i];
  }
  for (int i = 0; i < n; i++) {
    max = temp[i] > max ? temp[i] : max;
  }
  return max;
}

int main() {
  int n;
  cin >> n;
  int num[n];
  for (int i = 0; i < n; i++)
    cin >> num[i];
  cout << maxSubSum(num, n) << endl;
  system("pause");
  return 0;
}