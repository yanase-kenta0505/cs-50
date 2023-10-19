// Implements a dictionary's functionality
#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    // 「\0」が最後に入るので+1する
    //  長さが45文字以内の単語
    char word[LENGTH + 1];
    struct node *next;
} node;

// a~zまで26文字なので26を使っている
const unsigned int N = 26 ;

// ハッシュテーブル
// 例）構造は以下のようになります
// table[0] -> {word: "abc", next: -> {word: "abcd", next: ???}}
// table[1] -> {word: "bbb", next: ???}
// table[2] -> NULL
// ...
// table[25] -> {word: "zaa", next: -> {word: "zab", next: ???}}
node *table[26];

unsigned int word_count;
unsigned int hashed_word;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    hashed_word = hash(word);

    // ハッシュテーブルのリンクリストの先頭へのポインタとなる
    // 例えば↑で書いたハッシュテーブルの構造を参考にした場合
    // table[0]の先頭は{word: "abc", next: -> {word: "abcd", next: ???}}になる
    node *cursor = table[hashed_word];

    while (cursor != 0)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        // 例）
        // {word: "abc", next: -> {word: "def", next: -> {word: "ghi", next: NULL}}}
        // 以下のコードを繰り返していくと最終的に{word: "ghi", next: NULL}に行きつき、nextがNULL（0）になる
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long total = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        // tolowerは大文字と小文字の区別をなくすため
        total += tolower(word[i]);
    }

    // totalをNで割った剰余が返される
    // 例）"abc"という単語 →　各文字の小文字のASCII値は 'a' は 97, 'b' は 98, 'c' は 99
    // 合計は 294　
    // 26（Nの値）で割った剰余は 14
    // ハッシュ値は14となり結果としてハッシュテーブル（node *table[26]）の15番目に格納される
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }

    char word[LENGTH + 1];

    // EOFとはファイルの終わり
    while (fscanf(file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));

        if (new_node == NULL)
        {
            return false;
        }

        strcpy(new_node->word, word);

        // hashed_wordが3だと仮定
        hashed_word = hash(word);
        
        // new_nodeのnextポインタにtable[3]（リンクリスト）の先頭が割り当てられる
        new_node->next = table[hashed_word];

        // new_nodeがtable[3]（リンクリスト）の先頭になる
        // ハッシュテーブルはアルファベット順などは関係なく対応するリンクリストの先頭に追加されていく
        table[hashed_word] = new_node;
        word_count++;
    }

    fclose(file);
    
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0)
    {
        return word_count;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }

        if (cursor != NULL)
        {
            return false;
        }
    }

    return true;
}
