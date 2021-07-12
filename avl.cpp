#include<bits/stdc++.h>
using namespace std;
struct avlnode{
	public:
	int data;
	int height;
	avlnode *left;
	avlnode *right;

};



	void preorder(avlnode *node)
	{
		if(node==NULL)return ;
		cout<<node->data<<" ";
		if(node->left!=NULL)
		preorder(node->left);
		if(node->right!=NULL)
		preorder(node->right);
	}
	
	void inorder(avlnode *node)
	{
		if(node==NULL)return ;
		if(node->left!=NULL)
		inorder(node->left);
		cout<<node->data;
		if(node->right!=NULL)
		inorder(node->right);
	}
	void postorder(avlnode *node)
	{
		if(node==NULL)return ;
		if(node->left!=NULL)
		postorder(node->left);
		if(node->right!=NULL)
		postorder(node->right);
		cout<<node->data;
	}
	void levelorder(avlnode *root){
		queue<avlnode*>q;
		q.push(root);
		while(!q.empty()){
			avlnode *front=q.front();
			q.pop();

			cout<<front->data<<endl;
			
			if(front->left!=NULL)
				q.push(front->left);
			if(front->right!=NULL)
				q.push(front->right);
		}
	}
//get height
  int getheight(avlnode *node)
  {
	  if(node==NULL)return 0;
	  return node->height;
  }
  //get balance
  int getbalance(avlnode *node)
  {
	  if(node==NULL)return 0;
	  return (getheight(node->left)-getheight(node->right));
  }

  //rotate right
           struct  avlnode* rotateright(avlnode *dbn)
	    {
		    avlnode *newnode=dbn->left;
		    dbn->left=dbn->left->right;
		    newnode->right=dbn;
		 dbn->height=1+max(getheight(dbn->left),getheight(dbn->right));
                newnode->height=1+max(getheight(newnode->left),getheight(newnode->right));
		    return newnode;
	    }	 
	    // rotate left
          struct avlnode* rotateleft(avlnode *dbn)
	        {
		    avlnode *newnode=dbn->right;
		    dbn->right=dbn->right->left;
		    newnode->left=dbn;
		    dbn->height=1+max(getheight(dbn->left),getheight(dbn->right));
               newnode->height=1+max(getheight(newnode->left),getheight(newnode->right));
		    return newnode;
	    }	 					
	avlnode* insert(avlnode *node ,int value)
	{
		if(node==NULL){
			avlnode *newnode=new avlnode();
			newnode->data=value;
			newnode->height=1;
			return newnode;
		}
		else if(value<node->data){
			node->left=insert(node->left,value);
		}
		else if(value>node->data){
			node->right=insert(node->right,value);
		}
		node->height=1+max(getheight(node->left),getheight(node->right));
		int balance =getbalance(node);


		// left left condition 
		if(balance>1 and value<node->left->data)
		{
			return rotateright(node);
		}
		// right right condition
		if(balance< -1 and value > node->right->data)
		{
			return rotateleft(node);
		}
		//left right condtion 
		if (balance>1 and value>node->left->data){
			node->left=rotateleft(node->left);
			return rotateright(node);
		}
		//right left condtion 
		if(balance < -1 and value<node->right->data){
		       node->right=rotateright(node->right);
	               return rotateleft(node);
		}
             return node;
	}
	//get minimus
	avlnode* getminimun(avlnode *node)
	{
		if(node->left==NULL)return node;
		return getminimun(node->left);
	}
	//delete node
	avlnode* deletenode(avlnode *node,int value)
	{
		if(node==NULL)return node;
		else if(value<node->data)
		{
			node->left=deletenode(node->left,value);
			return node;
		}
		else if(value>node->data)
		{
			node->right=deletenode(node->right,value);
			return node;
		}
		else {
			// if there is two children of a node
			if(node->left!=NULL&&node->right!=NULL)
			{
				avlnode *temp=node;
				avlnode *getminforright=getminimun(node->right);
				node->data=getminforright->data;
				node->right=deletenode(node->right,getminforright->data);
			}
			// if there is only one children of the node left child
					else if(node->left!=NULL)
			{
				node=node->left;
			}
			// if there is only one children of node right child
			else if(node->right!=NULL)
			{
				node=node->right;
			}
			//if node is leaft node;
			else{
				node=NULL;
			}

        

			}
			 int balance=getbalance(node);
			 if(balance>1&& getbalance(node->left)>=0)
			 {
				 return rotateleft(node);

			 }
			 if(balance>1&&getbalance(node->left)<0)
			 {
				node->left=rotateleft(node->left);
				return rotateright(node);
			 }
			 if(balance<-1&&getbalance(node->right)<=0)
			 {
				 return rotateright(node);

			 }
			 if(balance<-1 && getbalance(node->right)>=0)
			 {
				 node->right=rotateright(node->right);
				 return rotateleft(node);
			 }
			 return node;
		}
	
		
	
int main()
{	
       	avlnode *root=NULL;
	root=insert(root,10);
root=insert(root,20);
root=insert(root,30);
root=insert(root,40);
preorder(root);
deletenode(root,20);
cout<<endl;
preorder(root);
//delete entire tree
root=NULL;
preorder(root);

	return 0;
}

