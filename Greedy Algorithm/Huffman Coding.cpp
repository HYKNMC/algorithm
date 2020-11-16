#include <cstdio>
#include <iostream>
using namespace std;
/*最大编码长度*/
#define MAXBIT 100
/*最大节点值*/
#define MAXVALUE 10000
/*最大叶子结点数*/
#define MAXLEAF 30
/*最大节点数*/
#define MAXNODE MAXLEAF * 2 - 1

/*节点的权值、双亲节点、左孩子节点、有孩子节点、节点字符*/
typedef struct {
  double weight;
  int parent;
  int leftChild;
  int rightChild;
  char character;
} HuffNode;

typedef struct {
  int bit[MAXBIT];
  int start;
} HuffCode;

/*哈夫曼树中需要求哈夫曼编码的节点均为叶子节点，构建哈夫曼树会增加辅助节点*/
/*定义全局变量*/
HuffNode huffNode[MAXNODE];
HuffCode huffCode[MAXLEAF];

void HuffmanTree(HuffNode huffmanNode[MAXNODE], int n) {
  /*权值最小且无父亲节点的两个节点的索引*/
  int indexOne, indexTwo;
  /*权值最小的且无父亲节点的两个节点的权值*/
  double minWeightOne, minWeightTwo;
  /*初始化哈夫曼数组中的节点*/
  for (int i = 0; i < 2 * n - 1; i++) {
    huffmanNode[i].weight = 0;
    huffmanNode[i].parent = -1;
    huffmanNode[i].leftChild = -1;
    huffmanNode[i].rightChild = -1;
  }
  /*输入每个节点的节点值和权值*/
  for (int i = 0; i < n; i++) {
    cin >> huffmanNode[i].character >> huffmanNode[i].weight;
  }
  /*构建哈夫曼树,N棵单节点树构建一棵哈夫曼树需要N-1次,最后会形成n+i个节点*/
  for (int i = 0; i < n - 1; i++) {
    minWeightOne = minWeightTwo = MAXVALUE;
    indexOne = indexTwo = -1;
    for (int j = 0; j < n + i; j++) {
      /*始终保持minWeightTwo是最小值，minWeightOne是第二小*/
      if (minWeightOne > huffmanNode[j].weight && huffmanNode[j].parent == -1) {
        minWeightTwo = minWeightOne;
        indexTwo = indexOne;
        minWeightOne = huffmanNode[j].weight;
        indexOne = j;
      } else if (minWeightTwo > huffmanNode[j].weight &&
                 huffmanNode[j].parent == -1) {
        minWeightTwo = huffmanNode[j].weight;
        indexTwo = j;
      }
    }
    huffmanNode[n + i].weight = minWeightTwo + minWeightOne;
    huffmanNode[n + i].leftChild = indexOne;
    huffmanNode[n + i].rightChild = indexTwo;
    huffmanNode[indexTwo].parent = n + i;
    huffmanNode[indexOne].parent = n + i;
  }
}

void HuffmanCode(HuffCode huffmanCode[MAXLEAF], int n) {
  HuffCode temp;
  int child, parent;
  for (int i = 0; i < n; i++) {
    temp.start = n - 1;
    child = i;
    parent = huffNode[child].parent;
    while (parent != -1) {
      /*约定左分支为0，右分支为1*/
      if (huffNode[parent].leftChild == child) {
        temp.bit[temp.start] = 0;
      }
      if (huffNode[parent].rightChild == child) {
        temp.bit[temp.start] = 1;
      }
      temp.start--;
      child = parent;
      parent = huffNode[child].parent;
    }
    for (int j = temp.start + 1; j < n; j++) {
      huffmanCode[i].bit[j] = temp.bit[j];
    }
    huffmanCode[i].start = temp.start + 1;
  }
}

int main() {
  int n;
  cin >> n;
  HuffmanTree(huffNode, n);
  HuffmanCode(huffCode, n);
  for (int i = 0; i < n; i++) {
    cout << huffNode[i].character << "\t";
    for (int j = huffCode[i].start; j < n; j++) {
      cout << huffCode[i].bit[j];
    }
    cout << endl;
  }
  return 0;
}
