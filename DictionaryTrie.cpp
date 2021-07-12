/**
 * TODO: File Header
 *
 * Author: Samhita Kadali
 */
#include "DictionaryTrie.hpp"
#include <iostream>
#include <queue>
protected:

   /** Pointer to the root of this TST, or 0 if the TST is empty */
   TSTNode* root;
    //i think this is bfs?
    vector<string> traverse(string pref){
        vector<string> tresult;
        queue< pair< TSTNode*, pair< string, bool>>> q;
        TSTNode* node = root;
        q.push({node, {pref, true}});
        while(!qu.empty()){
            TSTNode* node = q.front().first;
            string pref = q.front().second.first;
            bool valid = q.front().second.second;
            q.pop();
            if(node->bword==true && valid==true)
                tresult.push_back(pref);
            if(node->left) q.push({node->left, {pref, 0}});
            if(node->mid) q.push({node->mid, {pref+node->data, 1}});
            if(node->right) q.push({node->right, {pref, 0}});
        }
        return tresult;
}
public:
    /* TODO */
    DictionaryTrie::DictionaryTrie(): root(0) {}

    /* TODO */
    bool DictionaryTrie::insert(string word, unsigned int freq) {
        TSTNode* node = root;
        char letter = word[0];
        
        //loop infinitely
        while(true){
            //left child
            if (letter < node->data) {
                if(node.left)
                    node = node->left;
                else{
                    node->left = newTSTNode*(letter)
                    node = node->left;
                    for (char c: word.substr(1,word.length())){
                        node->mid = newTSTNode*(c);
                        node = node->mid;
                    }
                    node->bword = true;
                    node->fr = freq;
                    break;
                }
            }
            //right child
            else if (letter > node->data){
                if (node->right)
                    node = node->right;
                else{
                    node->right = newTSTNode*(letter);
                    node = node->right;
                    for (char c: word.substr(1,word.length())){
                        node->mid = newTSTNode*(c);
                        node = node->mid;
                    }
                    node->bword = true;
                    node->fr = freq;
                    break;
                }
            }
            //middle child
            else{
                if(letter == word.back()){
                    node->bword=true;
                    return true;
                }
                else{
                    for (char c: word.substr(1,word.length())){
                        node->mid = newTSTNode*(c);
                        node = node->mid;
                    }
                    node->bword = true;
                    node->fr = freq;
                    break;
                }
            }
        }
    }

    /* TODO */
    bool DictionaryTrie::find(string word) const {
        TSTNode* node = newTSTNode(root);
        int i = 0;
        char letter = word[i];
        while(true){
            if(letter<node.data){
                if(node->left)
                    node = node->left;
                else
                    return false;
            }
            else if( letter > node->data){
                if(node->right)
                    node = node->right;
                else
                    return false;
            }
            else{
                if(letter = word.back() && node->bword == true)
                    return true;
                else{
                    if(node->mid && letter != word.back()){
                        node = node->mid;
                        letter = word[i+1];
                    }
                    else
                        return false;
                }
            }
        }
    }

    /* TODO */
    vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                      unsigned int numCompletions) {
        vector<string> result;
        TSTNode* node = root;
        int l = prefix.length();
        int i = 0;
        while(i<prefix.length()){
            if(node==NULL) return result;
            if(node->data == prefix[i]){
                node = node->mid;
                i++;
                continue;
            }
            if(node->data < prefix[i])
                node = node->right;
            else node = node->left;
        }
        return node->traverse(prefix);
    }

    /* TODO */
    DictionaryTrie::~DictionaryTrie() {}
