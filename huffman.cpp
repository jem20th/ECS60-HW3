//
// Operation Mafghan Victory by Harrison Ching
// hching@ucdavis.edu
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>

using namespace std;

class HeapNode {
	public:
		HeapNode *left;
		HeapNode *right;
		unsigned int weight;
		unsigned char c;
		unsigned char smallestChar;
		HeapNode(HeapNode *leftNode,HeapNode *rightNode,unsigned int nodeWeight,unsigned char firstChar) {
			left = leftNode;
			right = rightNode;
			weight = nodeWeight;
			c = firstChar;
			smallestChar = firstChar;
		}
   bool operator>(const HeapNode& input) const;
   bool operator>=(const HeapNode& input) const;
   bool operator<(const HeapNode& input) const;
   bool operator<=(const HeapNode& input) const;
   bool operator==(const HeapNode& input) const;
};

class MinHeap {
	private:
		HeapNode **heap;
		int maxSize;
		int heapSize;
	public:
		MinHeap(int cap = 20) {
			heapSize = 0;
			maxSize = cap;
			heap = new HeapNode* [maxSize+1];
		}
		void Push(HeapNode *e);
		HeapNode* Pop();
		int size() const {
			return(heapSize);
		}
		bool isEmpty() const {
			return(heapSize == 0);
		}
};

bool HeapNode::operator>(const HeapNode& input) const
{
  if (this->weight > input.weight)
    return(true);
  if (this->weight == input.weight && this->smallestChar > input.smallestChar)
    return(true);
  return(false);
}

bool HeapNode::operator>=(const HeapNode& input) const
{
  if (this->weight > input.weight)
    return(true);
  if (this->weight == input.weight && this->smallestChar > input.smallestChar)
    return(true);
  if (this->weight == input.weight && this->smallestChar == input.smallestChar)
    return(true);
  return(false);
}

bool HeapNode::operator<(const HeapNode& input) const
{
  if (this->weight < input.weight)
    return(true);
  if (this->weight == input.weight && this->smallestChar < input.smallestChar)
    return(true);
  return(false);
}

bool HeapNode::operator<=(const HeapNode& input) const
{
  if (this->weight < input.weight)
    return(true);
  if (this->weight == input.weight && this->smallestChar < input.smallestChar)
    return(true);
  if (this->weight == input.weight && this->smallestChar == input.smallestChar)
    return(true);
  return(false);
}

bool HeapNode::operator==(const HeapNode& input) const
{
  if (this->weight == input.weight)
    return(true);
  return(false);
}

void MinHeap::Push(HeapNode *e)
{
  int currentNode = ++heapSize;

  while (currentNode != 1 && (*heap[currentNode/2]) > (*e))
  {
    heap[currentNode] = heap[currentNode/2];
    currentNode /= 2;
  }
  heap[currentNode] = e;
}

HeapNode* MinHeap::Pop()
{
  HeapNode *x, *final;
  int currentNode, child;

  x = heap[1];
  final = heap[heapSize--];

  currentNode = 1;
  child = 2;
  while (child <= heapSize)
  {
    if (child < heapSize && (*heap[child]) > (*heap[child+1]))
      ++child;
    if ((*final) <= (*heap[child]))
      break;
    heap[currentNode] = heap[child];
    currentNode = child;
    child *= 2;
  }
  heap[currentNode] = final;
  return(x);
}

const int ASCII_KEY = 256;
int encode_len[ASCII_KEY];
static unsigned int frequency[ASCII_KEY]; 
static char *encode[ASCII_KEY];
static char code_string[1000];
static char bit_maskx[8] = {0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80};
static char cx;
static int count; 
static int chosenChar;
static int subChar;

HeapNode* combineTree(HeapNode *node1,HeapNode *node2,unsigned int new_weight);
void traverseTree(HeapNode *node,int temp);
void reverseTraverse(HeapNode *node);
void huffman(HeapNode *huffman_root);
void outputDecompressed(HeapNode *root,int totalChar);
void outputCompressed();
void compress();
void decompress();

HeapNode* combineTree(HeapNode *node1,HeapNode *node2,unsigned int new_weight)
{
  HeapNode *left,*right,*root;
  unsigned char smallestChar;

  if ((*node1) > (*node2)) {
    left  = node1;
    right = node2;
  }
  else {
    left  = node2;
    right = node1; 
  }

  if (node1->smallestChar > node2->smallestChar)
    smallestChar = node2->smallestChar;
  else
    smallestChar = node1->smallestChar;

  root = new HeapNode(left,right,new_weight,smallestChar);

  return(root);
}

void traverseTree(HeapNode *node,int temp)
{
  int length;

  if (node->left == 0 && node->right == 0) {
    code_string[temp] = '\0';
    length = strlen(code_string);
    encode_len[node->c] = length;
    encode[node->c] = new char [length+1];
    strcpy(encode[node->c],code_string);
    return;
  }
  if (node->left != 0) {
    code_string[temp] = '0';
    traverseTree(node->left,temp+1);
  }
  if (node->right != 0) {
    code_string[temp] = '1';
    traverseTree(node->right,temp+1);
  }
}

void reverseTraverse(HeapNode *node)
{
  if (chosenChar)
    return;
  if (node->left == 0 && node->right == 0) {
    cout << char(node->c);
    ++subChar;
    chosenChar = 1;
    return;
  }
  if ((cx & bit_maskx[count]) == 0) {
    if (count == 7) {
      count = 0;
      cx = cin.get();
    }
    else
      ++count;
    reverseTraverse(node->left);
  }
  else {
    if (count == 7) {
      count = 0;
      cx = cin.get();
    }
    else
      ++count;
    reverseTraverse(node->right);
  }
}

void huffman(HeapNode *huffman_root)
{
  int temp = 0;

  traverseTree(huffman_root,temp);
}

void outputDecompressed(HeapNode *root,int totalChar)
{
  subChar = 0;
  count = 0;
  cx = cin.get();
  cx = cin.get();
  if (cin.good()) {
    while (1) {
      chosenChar = 0;
      reverseTraverse(root);
      if (subChar >= totalChar)
        break;
    }
  }
}

void outputCompressed()
{
  char str1[] = "HUFFMA4";
  char byte_data; 
  unsigned char c;
  char bit_mask[8] = {0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80};
  char *encode_str,len,*sp;
  int bit;

  cout.write(str1,8);
  for (int i = 0; i < ASCII_KEY; ++i) {
    cout.write((char*)&frequency[i],4);
  }

  bit = 0;
  byte_data = 0x0;
  while (cin.good()) {
    c = cin.get();
    if (cin.good()) {
      encode_str = encode[c];
      len = encode_len[c];
      for (int code_bit_idx = 0; code_bit_idx < len; ++code_bit_idx) {
        if (encode_str[code_bit_idx] == '1')
          byte_data |= bit_mask[bit];
        if (bit == 7) {
          cout.write(&byte_data,1);
          byte_data = 0x0;
          bit = 0;
        }
        else
          ++bit;
      }
    }
  }
  if (bit != 0) {
    cout.write(&byte_data,1);

  }
}

void compress()
{
  unsigned int new_weight; 
  unsigned char c; 
  HeapNode *x,*y,*node1,*node2,*huffman_root;
  MinHeap heap(300);

  for (int i = 0; i < ASCII_KEY; ++i)
    frequency[i] = 0;

  while (cin.good()) {
    c = cin.get();
    if (cin.good())
      ++frequency[c];
  }

  cin.clear();
  cin.seekg(0,ios_base::beg);

  
  for (int i = 0; i < ASCII_KEY; ++i) {
    if (frequency[i] > 0) {
      x = new HeapNode(0,0,frequency[i],i);
      heap.Push(x);
    }
  }

  while (heap.size() > 1) {
    node1 = heap.Pop();
    node2 = heap.Pop();
    new_weight = node1->weight + node2->weight;
    y = combineTree(node1,node2,new_weight);
    heap.Push(y);
  }

  huffman_root = heap.Pop();

  huffman(huffman_root);

  outputCompressed();
}

void decompress()
{
  unsigned int new_weight; 
  char str1[9];
  unsigned char c; 
  HeapNode *x,*y,*node1,*node2,*huffman_root;
  MinHeap heap(300);
  int totalChar;

  cin.get(str1,9);
  cin.get((char*)frequency,ASCII_KEY*4);

  totalChar = 0;
  for (int i = 0; i < ASCII_KEY; ++i) {
    if (frequency[i] > 0) {
      totalChar += frequency[i];
      x = new HeapNode(0,0,frequency[i],i);
      heap.Push(x);
    }
  }

  while (heap.size() > 1) {
    node1 = heap.Pop();
    node2 = heap.Pop();
    new_weight = node1->weight + node2->weight;
    y = combineTree(node1,node2,new_weight);
    heap.Push(y);
  }

  huffman_root = heap.Pop();

  outputDecompressed(huffman_root,totalChar);
}

int main(int x,char **y)
{

  if (x > 1 && !strcmp(y[1],"-d"))
    decompress();
  else
    compress();

  return(0);
} 
