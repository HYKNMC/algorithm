#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 1002;
int length[N][N], stratege[N][N];
char s1[N], s2[N];
int len1, len2;

void LCS() {
  for (int i = 1; i <= len1; i++) {
    for (int j = 1; j <= len2; j++)
      if (s1[i - 1] == s2[j - 1]) {
        length[i][j] = length[i - 1][j - 1] + 1;
        stratege[i][j] = 1;
      } else {
        if (length[i][j - 1] >= length[i - 1][j]) {
          length[i][j] = length[i][j - 1];
          stratege[i][j] = 2;
        } else {
          length[i][j] = length[i - 1][j];
          stratege[i][j] = 3;
        }
      }
  }
}
/* 打印最长公共子序列 */
void print(int i, int j) {
  if (i == 0 || j == 0) {
    return;
  }
  if (stratege[i][j] == 1) {
    print(i - 1, j - 1);
    cout << s1[i - 1];
  } else if (stratege[i][j] == 2) {
    print(i, j - 1);
  } else {
    print(i - 1, j);
  }
}
int main() {
  cin >> s1;
  cin >> s2;
  len1 = strlen(s1);
  len2 = strlen(s2);
  for (int i = 0; i <= len1; i++) {
    length[i][0] = 0;
  }
  for (int i = 0; i <= len2; i++) {
    length[0][i] = 0;
  }
  LCS();
  cout << length[len1][len2] << endl;
  print(len1, len2);
  system("pause");
  return 0;
}