/*Normal range update which times out...*/
#include<bits/stdc++.h>
using namespace std;
int a[100005]; //0-based index
int tree[4*100005]; //1-based index
build(int node,int start,int end){
	if(start==end){
		tree[node]=a[start];
	}
	else{
		int mid=(start+end)/2;
		build(2*node,start,mid);
		build(2*node+1,mid+1,end);
		tree[node]=tree[2*node]+tree[2*node+1];
	}
}
int query(int node,int start,int end,int l,int r){
	if(r<start || end<l)
	return 0; //node outside the range
	if(l<=start && end<=r)
	return tree[node]; //node completely inside the range
	int mid=(start+end)/2;
	int p1=query(2*node,start,mid,l,r);
	int p2=query(2*node+1,mid+1,end,l,r);
	return (p1+p2);
}
void update_range(int node,int start,int end,int l,int r,int val){
	if(start>end || start>r || end<l)
	return;
	if(start==end){
		tree[node]=tree[node]+val;
		return;
	}
	int mid=(start+end)/2;
	update_range(2*node,start,mid,l,r,val);
	update_range(2*node+1,mid+1,end,l,r,val);
	tree[node]=tree[2*node]+tree[2*node+1];
}
main(){
	int t;
	cin>>t;
	
	for(int e=0;e<t;e++){
		int n;
		cin>>n;
		for(int i=0;i<n;i++)
		a[i]=0;
		for(int i=0;i<4*n;i++)
		tree[i]=-1;
		int q;
		cin>>q;
		build(1,0,n-1);
		//for(int i=1;i<=4*n;i++)
		//cout<<tree[i]<<" ";
		for(int w_t=0;w_t<q;w_t++){
			int which;
			cin>>which;
			if(which==0){
				int l,r,v;
				cin>>l>>r>>v;
				update_range(1,0,n-1,l-1,r-1,v);
			}
			else{
				int l,r;
				cin>>l>>r;
				cout<<query(1,0,n-1,l-1,r-1)<<"\n";
			}
		}
	}
}
