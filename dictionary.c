// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
#define N 26

// Hash table
node* table[N];//创建包含26个头节点的数组
//下次我打算用前两个字母加起来作为hash值 比如aa就是 0+0 这样的话最大是25+25=50
//不行 感觉才50的话还是很容易冲突 如果改成乘积呢 那a就最好不要是0 如果a是0那a开头的就全是0了 a如果是1 z26 就可以让table有26*26
//实际上会空很多 比如zz好像就没什么单词 难道这就是空间换时间？
unsigned int word_count=0;

bool strcasecmp(const char* word1, const char* word2) {
    int len1=strlen(word1);
    int len2=strlen(word2);
    if (len1!=len2) {
        return false;
    }
    for (int i=0;i<len1;i++) {
        if (toupper(word1[i])!=toupper(word2[i])) {
            return false;
        }
    }
    return true;
}
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index=hash(word);
    node* tmp=table[index];
    while (tmp!=NULL) {
        if (strcasecmp(word,tmp->word)) {
            return true;
        }else {
            tmp=tmp->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    if (dict==NULL) {
        printf("无法加载字典 %s\n",dictionary);
        return false;
    }
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    char new_word[LENGTH+1];
    while (fscanf(dict,"%s",new_word)!=EOF) {

        //通过单词的第一个字母计算序号 A代表0 Z代表25
        node* n= malloc(sizeof(node));

        if (n==NULL){
            unload();
            fclose(dict);
            return false;
        }

        n->next=NULL;
        strcpy(n->word,new_word);
        unsigned int index=hash(new_word);
        //创建好新节点了！是时候让table[n]指向这个节点了！ X
        //上面那个想法错了 我们应该把节点插入在头部以提升效率
        //在头部插入节点1.新节点的指针指向原本头节点 2.table[index]的指针指向新节点
        n->next=table[index];
        table[index]=n;
        word_count++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    //要free掉load的所有链表 包括table[N] 还有table指下去的每一个东西
    for (int i=0;i<N;i++) {
        node* tmp=table[i];
        while (tmp!=NULL) {
            node* tmp2=tmp;
            tmp=tmp->next;
            free(tmp2);
        }
    }
    return true;
}
