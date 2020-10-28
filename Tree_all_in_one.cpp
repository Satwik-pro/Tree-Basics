#include<bits/stdc++.h>
using namespace std;
int ans=0,ans2=0,ans3=0,f=0;
struct tree
{
    int data;
    tree *left,*right,*prev;
};
tree *newnode(int val)
{
    tree *node=new tree;
    node->data=val;
    node->left=node->right=node->prev=0;
    return node;
}
tree *insert(int arr[], tree *root, int i, int n)
{
    if(i<n)
    {
        tree *node=newnode(arr[i]);
        root=node;
        root->left=insert(arr,root->left,2*i+1,n);
        root->right=insert(arr,root->right,2*i+2,n);
    }
    return root;
}
tree *makeprev(tree *root)
{
    if(root->left)
    {
        root->left->prev=root;
        makeprev(root->left);
    }
    if(root->right)
    {
        root->right->prev=root;
        makeprev(root->right);
    }
}
void dfs(tree *root, int depth)
{
    ans+=depth;
    if(root->left)
    dfs(root->left,depth+1);
    if(root->right)
    dfs(root->right,depth+1);
}
void dfs2(tree *root, int depth)
{
    ans2+=depth;
    if(root->left)
    dfs2(root->left,depth+1);
    if(root->right)
    dfs2(root->right,depth+1);
}
void dfs3(tree *node, int depth)
{
    ans3+=depth;
    if(node->prev && f==0)
    {
        f=-1;
        dfs3(node->prev,depth+1);
    }
    if(node->left)
    dfs3(node->left,depth+1);
    if(node->right)
    dfs3(node->right,depth+1);
}
int sumdepth(tree *root)
{
    ans=0;
    dfs(root,0);
    return ans;
}
int sumsubtreedepth(tree *root)
{
    dfs2(root,0);
    if(root->left)
    sumsubtreedepth(root->left);
    if(root->right)
    sumsubtreedepth(root->right);
    return ans2;
}
int sumdists(tree *target)
{
    ans3=0;
    dfs3(target,0);
    return ans3;
}
tree *turnitup(tree *target)
{
    if(target->prev != 0)
    {
        if(target->prev->left == target)
        target->prev->left = target->prev->prev;
        if(target->prev->right == target)
        target->prev->right = target->prev->prev;
        turnitup(target->prev);
    }
}
tree *findref(tree *root,int value)
{
    if(root->data==value)
    {
        turnitup(root);
        cout<<sumdists(root);
    }
    if(root->left)
    findref(root->left,value);
    if(root->right)
    findref(root->right,value);
}
int main()
{
    int n,target;
    cin>>n;
    int arr[n]={0},i;
    for(i=0;i<n;i++)
    cin>>arr[i];
    tree *root=insert(arr,root,0,n);
    cout<<sumdepth(root)<<"\n";
    cout<<sumsubtreedepth(root)<<"\n";
    makeprev(root);
    cin>>target;
    findref(root,target);
    return 0;
}
