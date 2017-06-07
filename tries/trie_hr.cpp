/*
root
                / \
         (d, 3)/   \(z, 1)
              /     \
          Node1     Node2
           / \          \
     (o,2)/   \(u,1)     \(e,1)
         /     \          \
   Node1.1    Node1.2     Node2.1
      /  \         \            \
(g,1)/    \ (t,1)   \(c,1)       \(b,1)
    /      \         \            \ 
   Leaf   Leaf       Node1.2.1     Node2.1.1
   (dog)  (dot)        \               \
                         \(k, 1)          \(r, 1)
                          \                \   
                          Leaf           Node2.1.1.1
                          (duck)              \
                                                \(a,1)
                                                 \
                                                 Leaf
                                                 (zebra)
*/
#include<bits/stdc++.h>
using namespace std;
typedef struct trienode{
	struct trienode * children[26];
	 // isLeaf is true if the node represents
     // end of a word
	bool isleaf;
	int freq; //nof times char has occured in given words
}trienode;
trienode *getnode(void){
	trienode * pnode='\0';
	pnode=(trienode*)malloc(sizeof(trienode));
	pnode->isleaf=false;
	for(int i=0;i<26;i++)
	pnode->children[i]='\0';
	pnode->freq=1;
	return pnode;
}
void insert(trienode * root,string str){
	int len=str.length();
	trienode * pcrawl=root;
	for(int i=0;i<len;i++){
		int index=str[i]-'a';
		if(!pcrawl->children[index])
		pcrawl->children[index]=getnode();
		else
		(pcrawl->children[index]->freq)++;
		pcrawl=pcrawl->children[index];
	}
}
int search(trienode* root,string str){
	int len=str.length();
	trienode * pcrawl=root;
	for(int i=0;i<len;i++){
	  int index=str[i]-'a';
		if(!pcrawl->children[index])
		return -1;
		pcrawl=pcrawl->children[index];
	}
	if(pcrawl=='\0')
	return -1;
	else
	return pcrawl->freq;
}
main(){
	int n;
	cin>>n;
	trienode* root=getnode();
	for(int i=0;i<n;i++){
		string s1,s2;
		cin>>s1>>s2;
	//	cout<<s1<<s2;
		if(!s1.compare("add")){
		insert(root,s2);
	//	cout<<"hell";
	}
		else{
			int x;
			if((x=search(root,s2))==-1)
			cout<<"0\n";
			else
			cout<<x<<"\n";
		}
	}
}
