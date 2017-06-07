#include<bits/stdc++.h>
using namespace std;
typedef struct trienode{
	struct trienode * children[26];
	 // isLeaf is true if the node represents
     // end of a word
	bool isleaf;
}trienode;
trienode *getnode(void){
	trienode * pnode='\0';
	pnode=(trienode*)malloc(sizeof(trienode));
	pnode->isleaf=false;
	for(int i=0;i<26;i++)
	pnode->children[i]='\0';
	return pnode;
}
int insert_find(trienode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
 
    trienode *pCrawl = root;
 int flag=0;
    for (level = 0; level < length; level++)
    {
        index = key[level]-'a';
        //string in trie is prefix for current string(len of triestring<curstring)
        if(pCrawl->isleaf)
        return -1;
        if (!pCrawl->children[index]){
            pCrawl->children[index] = getnode();
        pCrawl = pCrawl->children[index];
        flag=0;
        }
        else{
        pCrawl = pCrawl->children[index];
        //both triestring and curstr are prefixes of each other( len of triestring<curstring)
        if(pCrawl->isleaf)
        return -1;
        flag=1;
        }
    }
    //this if is for this type of test cases------
    /*
    39
hgiiccfchbeadgebc
biiga
edchgb
ccfdbeajaeid
ijgbeecjbj
bcfbbacfbfcfbhcbfjafibfhffac
ebechbfhfcijcjbcehbgbdgbh
ijbfifdbfifaidje
acgffegiihcddcdfjhhgadfjb
ggbdfdhaffhghbdh
dcjaichjejgheiaie
d
jeedfch
ahabicdffbedcbdeceed
fehgdfhdiffhegafaaaiijceijdgbb
beieebbjdgdhfjhj
ehg
fdhiibhcbecddgijdb
jgcgafgjjbg
c
fiedahb
bhfhjgcdbjdcjjhaebejaecdheh
gbfbbhdaecdjaebadcggbhbchfjg
jdjejjg
dbeedfdjaghbhgdhcedcj
decjacchhaciafafdgha
a
hcfibighgfggefghjh
ccgcgjgaghj
bfhjgehecgjchcgj
bjbhcjcbbhf
daheaggjgfdcjehidfaedjfccdafg
efejicdecgfieef
ciidfbibegfca
jfhcdhbagchjdadcfahdii
i
abjfjgaghbc
bddeejeeedjdcfcjcieceieaei
cijdgbddbceheaeececeeiebafgi

output:
BAD SET
d
    */
    //basically current string prefix of strings in trielen of triestring>curstring
    if(flag==1)
    for(int i=0;i<26;i++){
    	if(pCrawl->children[i]!='\0')
    	return -1;
	}
    // mark last node as leaf
    pCrawl->isleaf = true;
    return 0;
}
main(){
	int n,flag=0;
	cin>>n;
	trienode* root=getnode();
	for(int i=0;i<n;i++){
		char s1[65];
		cin>>s1;
		if(flag==0 && insert_find(root,s1)==-1){
			cout<<"BAD SET\n";
			cout<<s1;
			flag=1;
		}
	}
	if(flag==0){
		cout<<"GOOD SET";
	}
}
