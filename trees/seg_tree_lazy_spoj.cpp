/*Lazt propagation for range update*/
#include<bits/stdc++.h>
using namespace std;
long long int a[100005]; //0-based index
long long int lazy[5*100005]; 
long long int tree[5*100005]; //1-based index
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
void update_range_lazy(int node, int start, int end, int l, int r,long long  int val)
{
    if(lazy[node] != 0)
    { 
        // This node needs to be updated
        tree[node] += (end - start + 1) * lazy[node];    // Update it
        if(start != end)
        {
            lazy[node*2] += lazy[node];                  // Mark child as lazy
            lazy[node*2+1] += lazy[node];                // Mark child as lazy
        }
        lazy[node] = 0;                                  // Reset it
    }
    if(start > end or start > r or end < l)              // Current segment is not within range [l, r]
        return;
    if(start >= l and end <= r)
    {
        // Segment is fully within range
        tree[node] += (end - start + 1) * val;
        if(start != end)
        {
            // Not leaf node
            lazy[node*2] += val;
            lazy[node*2+1] += val;
        }
        return;
    }
    int mid = (start + end) / 2;
    update_range_lazy(node*2, start, mid, l, r, val);        // Updating left child
    update_range_lazy(node*2 + 1, mid + 1, end, l, r, val);   // Updating right child
    tree[node] = tree[node*2] + tree[node*2+1];        // Updating root with max value 
}

int query_lazy(int node, int start, int end, int l, int r)
{
    if(start > end or start > r or end < l)
        return 0;         // Out of range
    if(lazy[node] != 0)
    {
        // This node needs to be updated
        tree[node] += (end - start + 1) * lazy[node];            // Update it
        if(start != end)
        {
            lazy[node*2] += lazy[node];         // Mark child as lazy
            lazy[node*2+1] += lazy[node];    // Mark child as lazy
        }
        lazy[node] = 0;                 // Reset it
    }
    if(start >= l and end <= r)             // Current segment is totally within range [l, r]
        return tree[node];
    int mid = (start + end) / 2;
    long long int p1 = query_lazy(node*2, start, mid, l, r);         // Query left child
    long long int p2 = query_lazy(node*2 + 1, mid + 1, end, l, r); // Query right child
    return (p1 + p2);
}
main(){
	int t;
	cin>>t;
	
	for(int e=0;e<t;e++){
		int n;
		cin>>n;
		for(int i=0;i<n;i++)
		a[i]=0;
		for(int i=0;i<=4*n;i++){
		tree[i]=0;
	    lazy[i]=0;
		}
		int q;
		cin>>q;
		build(1,0,n-1);
		//for(int i=1;i<=4*n;i++)
		//cout<<tree[i]<<" ";
		for(int w_t=0;w_t<q;w_t++){
			int which;
			cin>>which;
			if(which==0){
				int l,r;
				long long int v;
				cin>>l>>r>>v;
				update_range_lazy(1,0,n-1,l-1,r-1,v);
			}
			else{
				int l,r;
				cin>>l>>r;
				cout<<query_lazy(1,0,n-1,l-1,r-1)<<"\n";
			}
		}
	}
}
