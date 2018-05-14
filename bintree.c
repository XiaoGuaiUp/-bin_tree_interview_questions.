#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "seqstack.h"

//FOR_QUEUE
#define SeqQueueMaxSize 1000

//FOR_BINTREE
typedef char TreeNodeType;

typedef struct TreeNode{
    struct TreeNode* lchild;
    struct TreeNode* rchild;
    TreeNodeType data;
} TreeNode;

typedef TreeNode*  SeqQueueType;

typedef struct SeqQueue{
    SeqQueueType data[SeqQueueMaxSize];
    size_t head;//队首元素的下标
    size_t tail;//队尾元素的下标
    size_t size;//顺序表的长度
} SeqQueue;


////////////////////////////////////////////////////////////////
//以下是队列的功能函数
///////////////////////////////////////////////////////////////

//初始化
void SeqQueueInit(SeqQueue* q)
{
    if(q==NULL)
    {
        return;
    }
    q->size=0;
    q->head=0;
    q->tail=0;
    return;
}

//销毁
void SeqQueueDestroy(SeqQueue* q)
{
    if(q==NULL)
    {
        return;
    }
    q->size=0;
    q->head=0;
    q->tail=0;
    return;
}

//入队列(尾插)
void SeqQueuePush(SeqQueue* q,SeqQueueType value)
{
    if(q==NULL)
    {
        return;
    }
    if(q->size>=SeqQueueMaxSize)
    {//满了
        return;
    }
    q->data[q->tail++]=value;
    //加完元素之后，需要再次判断顺序表的长度是否满了
    if(q->tail>=SeqQueueMaxSize)
    {
        q->tail=0;
    }
    //此时入栈一个元素后，需要更新size
    ++q->size;
    return;
}

//出队列（头删）
void SeqQueuePop(SeqQueue* q)
{
    if(q==NULL)
    {
        return;
    }
    if(q->size==0)
    {
        return;
    }
    //出队列：删队首元素，头删
    ++q->head;
    if(q->head>=SeqQueueMaxSize)
    {
        q->head=0;
    }
    --q->size;
    return;
}

//取队首元素
int SeqQueueFront(SeqQueue* q,SeqQueueType* value)
{
    if(q==NULL||value==NULL)
    {
        return 0;
    }
    if(q->size==0)
    {
        return 0;
    }
    *value=q->data[q->head];
    return 1;
}


/////////////////////////////////////////////////////////////////
//以下是二叉树的操作
////////////////////////////////////////////////////////////////

void TreeInit(TreeNode** proot)
{
    if(proot==NULL)
    {
        //非法输入
        return;
    }
    *proot=NULL;//空树
    return;
}

//先序遍历
void TreePreOrder(TreeNode* root)
{
    if(root==NULL)
    {
        //空树
        printf("#");
        return;
    }
    //先访问根节点
    printf("%c",root->data);
    //再遍历左子树
    TreePreOrder(root->lchild);
    //最后遍历右子树
    TreePreOrder(root->rchild);
    return;
}

//中序遍历
void TreeInOrder(TreeNode* root)
{
    if(root==NULL)
    {
        //空树
        return;
    }
    //先左子树
    TreeInOrder(root->lchild);
    //再打印根节点
    printf("%c ",root->data);
    //最后右子树
    TreeInOrder(root->rchild);
    return;
}

//后序遍历
void TreePostOrder(TreeNode* root)
{
    if(root==NULL)
    {
        //空树
        return;
    }
    //先左子树
    TreePostOrder(root->lchild);
    //最后右子树
    TreePostOrder(root->rchild);
    //再打印根节点
    printf("%c ",root->data);
    return;
}

//层序遍历
void TreeLevelOrder(TreeNode* root)
{
    if(root==NULL)
    {
        //空树
        return;
    }
    SeqQueue q;
    SeqQueueInit(&q);
    //循环取队首元素、打印、出队列、再把左、右子节点依次入队列
    //根节点入队列
    SeqQueuePush(&q,root);
    while(1)
    {
        SeqQueueType front;
        int ret=SeqQueueFront(&q,&front);
        if(ret==0)
        {
            break;
        }
        //打印队首元素
        printf("%c ",front->data);
        //出队列
        SeqQueuePop(&q);
        if(front->lchild!=NULL)
        {
            //左子树入队列
             SeqQueuePush(&q,front->lchild);
        }
        if(front->rchild!=NULL)
        {
            //右子树入队列
             SeqQueuePush(&q,front->rchild);
        }
    }
    printf("\n");
    return;
}

TreeNode* CreateNode(TreeNodeType  value);
//创建一个树的递归辅助函数
TreeNode* _TreeCreate(TreeNodeType data[],size_t size,size_t* index,char null_node)
{
    if(index==NULL)
    {
        //非法输入
        return NULL;
    }
    if(*index>=size)
    {
        //数组遍历完成
        return NULL;
    }
    if(data[*index]==null_node)
    {
        //遇到空节点了
        return NULL;
    }
    TreeNode* new_node=CreateNode(data[*index]);
    ++(*index);//取下一个节点
    new_node->lchild=_TreeCreate(data,size,index,null_node);
    ++(*index);
    new_node->rchild=_TreeCreate(data,size,index,null_node);
    return new_node;
}

//创建一棵树
TreeNode* TreeCreate(TreeNodeType data[],size_t size,char null_node)
{
    //index表示当前取数组的哪个元素
    size_t index=0;
    return _TreeCreate(data,size,&index,null_node);
}

//树的拷贝
TreeNode* TreeClone(TreeNode* root)
{
    if(root==NULL)
    {
        return NULL;
    }
    //按照先序来拷贝
    TreeNode* new_node=CreateNode(root->data);
    new_node->lchild=TreeClone(root->lchild);
    new_node->rchild=TreeClone(root->rchild);
    return new_node;
}
void DestroyNode(TreeNode* root);
//销毁树
void DestroyTree(TreeNode* root)
{
    if(root==NULL)
    {
        return ;
    }
    //按照后序遍历来销毁 左右根
    DestroyTree(root->lchild);
    DestroyTree(root->rchild);
    DestroyNode(root);
    return;
}

//二叉树中节点个数
//方法一

void _TreeSize(TreeNode* root,size_t* size)
{
    if(root==NULL)
    {
        return ;
    }
    ++(*size);
    _TreeSize(root->lchild,size);
    _TreeSize(root->rchild,size);
}

int TreeSize(TreeNode* root)
{
    size_t size=0;
    _TreeSize(root,&size);
    return size;
}

//方法二
size_t TreeSize2(TreeNode* root)
{
    if(root==NULL)
    {
        return 0;
    }
    return 1+TreeSize2(root->lchild)+TreeSize2(root->rchild);
}

//求二叉树中叶子节点的个数
//方法一

void _TreeLeafSize(TreeNode* root,size_t* size)
{
    if(root==NULL)
    {
        return ;
    }
    if(root->lchild==NULL&&root->rchild==NULL)
    {
        ++(*size);
    }
    _TreeLeafSize(root->lchild,size);
    _TreeLeafSize(root->rchild,size);
}
size_t TreeLeafSize(TreeNode* root)
{
    size_t size=0;
    _TreeLeafSize(root,&size);
    return size;

}

//方法二
size_t TreeLeafSize2(TreeNode* root)
{
    if(root==NULL)
    {
        return 0;
    }
    if(root->lchild==NULL&&root->rchild==NULL)
    {
        return 1;
    }
    return TreeLeafSize2(root->lchild)+TreeLeafSize2(root->rchild);
}

//求出二叉树第K层节点的个数
size_t TreeKLevelSize(TreeNode* root,int k)
{
    if(root==NULL)
    {
        return 0;
    }
    if(k==1)
    {
        return 1;
    }
    return TreeKLevelSize(root->lchild,k-1)+TreeKLevelSize(root->rchild,k-1);
}

//求出二叉树的高度，也就是深度
size_t TreeHeight(TreeNode* root)
{
    if(root==NULL)
    {
        return 0;
    }
    if(root->lchild==NULL&&root->rchild==NULL)
    {
        return 1;
    }

    size_t lheight=TreeHeight(root->lchild);
    size_t rheight=TreeHeight(root->rchild);
    return 1+(lheight>rheight?lheight:rheight);
}

//给定值，在二叉树中找到相应的节点
TreeNode* TreeFind(TreeNode* root,TreeNodeType to_find)
{
    //遍历
    //访问操作：比较
    if(root==NULL)
    {
        return NULL;
    }
    if(root->data==to_find)
    {
        return root;
    }
    TreeNode* lresult=TreeFind(root->lchild,to_find);
    TreeNode* rresult=TreeFind(root->rchild,to_find);
    return lresult !=NULL ? lresult:rresult;
}

//求出child 节点的父节点
TreeNode* Parent(TreeNode* root,TreeNode* child)
{
    if(root==NULL)
    {
        return NULL;
    }
    if(root->lchild==child||root->rchild==child)
    {
        return root;
    }
    TreeNode* lresult=Parent(root->lchild,child);
    TreeNode* rresult=Parent(root->rchild,child);
    return lresult !=NULL ? lresult:rresult;
}

//求出当前节点的左子树和右子树
TreeNode* LChild(TreeNode* root)
{
    if(root==NULL)
    {
        return NULL;
    }
    return root->lchild;
}
TreeNode* RChild(TreeNode* root)
{
    if(root==NULL)
    {
        return NULL;
    }
    return root->rchild;
}

/////////////////////////////////////////////////////////////
//二叉树常见面试题
////////////////////////////////////////////////////////////

//1.用非递归实现先序、中序、后序遍历
// 1）先序
void TreePreOrderByLoop(TreeNode* root)
{
    if(root==NULL)
    {
        return;
    }
    SeqStack stack;
    SeqStackInit(&stack);
    //根节点入栈
    SeqStackPush(&stack,root);
    TreeNode* cur=NULL;
    //取栈顶元素
    while(SeqStackTop(&stack,&cur))
    {
        //出栈
        SeqStackPop(&stack);
        //访问
        printf("%c ",cur->data);
        //入栈右子树
        if(cur->rchild!=NULL)
        {
            SeqStackPush(&stack,cur->rchild);
        }
        //入栈左子树
        if(cur->lchild!=NULL)
        {
            SeqStackPush(&stack,cur->lchild);
        }
    }
    printf("\n");
    return;
}

// 2)中序遍历
void TreeInOrderByLoop(TreeNode* root)
{
    if(root==NULL)
    {
        return;
    }
    //定义cur指向根节点root
    TreeNode* cur=root;
    SeqStack stack;
    SeqStackInit(&stack);
    while(1)
    {
        //循环判定cur是否为空
        while(cur!=NULL)
        {
            //不为空时，将cur入栈
            SeqStackPush(&stack,cur);
            cur=cur->lchild;
        }
        //此时二叉树的所有左子树以及根节点已经入栈
        //后进先出，先出的是最左侧的子树
        TreeNode* top=NULL;
        //取栈顶元素
        int ret=SeqStackTop(&stack,&top);
        if(ret==0)
        {
            return;
        }
        //打印
        printf("%c ",top->data);
        //出栈
        SeqStackPop(&stack);
        cur=top->rchild;
    }
    printf("\n");
    return;
}

//后序遍历
void TreePostOrderByLoop(TreeNode* root)
{
    if(root==NULL)
    {
        //非法输入
        return;
    }
    TreeNode* cur=root;
    TreeNode* pre=NULL;
    SeqStack stack;
    SeqStackInit(&stack);
    while(1)
    {
    //循环将cur及cur的左子树入栈
        while(cur!=NULL)
        {
            SeqStackPush(&stack,cur);
            cur=cur->lchild;
        }
        //此时取栈顶元素
        TreeNode* top=NULL;
        int ret=SeqStackTop(&stack,&top);
        if(ret==0)
        {
            printf("\n");
            return;
        }
        //判定栈顶元素：（1）有没有右子树 || （2）是不是上次访问过的元素
        //满足其一，打印、出栈
        if(top->rchild == NULL || top->rchild == pre)
        {
            printf("%c ",top->data);
            SeqStackPop(&stack);
            pre=top;
        }
        else
        {
            cur=top->rchild;
        }
    }
    return;
}

//交换函数
void Swap(TreeNode** a,TreeNode** b)
{
    TreeNode* tmp=*a;
    *a=*b;
    *b=tmp;
}
//将树镜像
void TreeMirror(TreeNode* root)
{
    //递归版本
    if(root==NULL)
    {
        return;
    }
    //核心：遍历
    Swap(&root->lchild,&root->rchild);
    TreeMirror(root->lchild);
    TreeMirror(root->rchild);
}

//非递归版本，与前面一样，只是将printf改为swap即可
void TreeMirrorByLoop(TreeNode* root)
{
    if(root==NULL)
    {
        return;
    }
    SeqStack stack;
    SeqStackInit(&stack);
    //根节点入栈
    SeqStackPush(&stack,root);
    TreeNode* cur=NULL;
    //取栈顶元素
    while(SeqStackTop(&stack,&cur))
    {
        //出栈
        SeqStackPop(&stack);
        //访问
        Swap(&cur->lchild,&cur->rchild);
        //入栈右子树
        if(cur->rchild!=NULL)
        {
            SeqStackPush(&stack,cur->rchild);
        }
        //入栈左子树
        if(cur->lchild!=NULL)
        {
            SeqStackPush(&stack,cur->lchild);
        }
    }
    printf("\n");
    return;
}

//用层序写非递归
void TreeMirrorByLoop2(TreeNode* root)
{
    if(root==NULL)
    {
        return;
    }
    SeqQueue q;
    SeqQueueInit(&q);
    SeqQueuePush(&q,root);
    TreeNode* cur=NULL;
    while(SeqQueueFront(&q,&cur))
    {
        Swap(&cur->lchild,&cur->rchild);
        SeqQueuePop(&q);
        if(cur->lchild!=NULL)
        {
            SeqQueuePush(&q,cur->lchild);
        }
        if(cur->rchild!=NULL)
        {
            SeqQueuePush(&q,cur->rchild);
        }
    }
    return;
}

//判断是否为完全二叉树
int IsCompleteTree(TreeNode* root)
{
    //利用层序遍历
    //遍历分2个阶段
    //  1.任何一个节点同时具有左右子树，若某节点不具备，进入1阶段
    //      1）当前节点只有右子树,一定不是完全二叉树
    //      2）当前节点只有左子树，进入2阶段
    //      3）无子树，进入2阶段
    //  2.任何一个节点都无子树
    //1、2走完，一定是完全二叉树
    if(root==NULL)
    {
        return 0;
    }
    SeqQueue q;
    SeqQueueInit(&q);
    TreeNode* cur=NULL;
    cur=root;
    SeqQueuePush(&q,cur);
    int flag=0;//表示当前是否进入阶段2
    while(SeqQueueFront(&q,&cur))
    {
        SeqQueuePop(&q);
        //阶段1
        if(flag==0)
        {
            if(cur->lchild!=NULL&&cur->rchild!=NULL)
            {
                SeqQueuePush(&q,cur->lchild);
                SeqQueuePush(&q,cur->rchild);
            }
            else if(cur->lchild==NULL&&cur->rchild!=NULL)
            {
                //一定不是完全二叉树
                return 0;
            }
            else if(cur->lchild!=NULL&&cur->rchild==NULL)
            {
                //进入第二阶段
                flag=1;
                SeqQueuePush(&q,cur->lchild);
            }
            else
            {
                flag=1;
            }
        }
        //2阶段
        else
        {
            if(cur->lchild==NULL&&cur->rchild==NULL)
            {
                ;
            }
            else
            {
                return 0;
            }
        }
    }
    //循环结束
    //所有节点遍历完
    return 1;
}

//Find
size_t Find(TreeNodeType arrary[],size_t left,size_t right,TreeNodeType to_find)
{
    size_t i=left;
    for(;i<right;++i)
    {
        if(arrary[i]==to_find)
        {
            return i;
        }
        return -1;
    }
}


//递归辅助函数
TreeNode* _TreeRebuild(TreeNodeType pre_order[],size_t pre_order_size,size_t* pre_order_index,\
                       TreeNodeType in_order[],size_t in_order_left,size_t in_order_right)
{
    if(in_order_left>=in_order_right)
    {
        //无效区间
        return NULL;
    }
    if(pre_order_index==NULL||*pre_order_index >= pre_order_size)
    {
        //非法输入
        return NULL;
    }
    //根据先序遍历结果取出当前值，基于这个值构建一个基点
    TreeNode* new_node=CreateNode(pre_order[*pre_order_index]);
    //new_node就是根节点
    //此时在中序遍历数组中查找new_node位置，确定左右子树区间
    size_t cur_root_in_order_index=Find(in_order,in_order_left,in_order_right,new_node->data);
    //assert(cur_root_in_order_index!=(size_t)-1);
    ++(*pre_order_index);
    //左子树区间[in_order_left,cur_root_in_order_index)
    new_node->lchild=_TreeRebuild(pre_order,pre_order_size,pre_order_index,in_order,in_order_left,cur_root_in_order_index);
    //右子树区间[cur_root_in_order_index,in_order_right)
    new_node->rchild=_TreeRebuild(pre_order,pre_order_size,pre_order_index,in_order,cur_root_in_order_index+1,in_order_right);
    return new_node;
}


//还原二叉树;先序和后序不可以还原出来
TreeNode* TreeRebuild(TreeNodeType pre_order[],TreeNodeType in_order[],size_t size)
{
    size_t pre_order_index=0;
    size_t in_order_left=0;
    size_t in_order_right=size;
    return _TreeRebuild(pre_order,size,&pre_order_index,in_order,in_order_left,in_order_right);
}

//////////////////////////////////////////////////////////////
//测试函数
/////////////////////////////////////////////////////////////

TreeNode* CreateNode(TreeNodeType value)
{
    TreeNode* new_node=(TreeNode* )malloc(sizeof(TreeNode));
    new_node->data=value;
    new_node->lchild=NULL;
    new_node->rchild=NULL;
    return new_node;
    return new_node;
}

//销毁节点
void DestroyNode(TreeNode* root)
{
    root=NULL;
    free(root);
}

void TestInit()
{
    printf("================= %s ==============\n",__FUNCTION__);
    TreeNode* root;
    TreeInit(&root);
    printf("root理论值为NULL，实际为 %p\n",root);
}

void TestPreOrder()
{
    printf("================= %s ==============\n",__FUNCTION__);
    TreeNode* root;
    TreeInit(&root);
    TreeNode* a=CreateNode('a');
    TreeNode* b=CreateNode('b');
    TreeNode* c=CreateNode('c');
    TreeNode* d=CreateNode('d');
    TreeNode* e=CreateNode('e');
    TreeNode* f=CreateNode('f');
    TreeNode* g=CreateNode('g');
    root=a;
    a->lchild=b;
    a->rchild=c;
    b->lchild=d;
    b->rchild=e;
    c->rchild=f;
    e->lchild=g;

    printf("-------- 递归先序遍历 -------------\n");
    TreePreOrder(root);
    printf("\n");
    printf("-------- 非递归先序遍历 -------------\n");
    TreePreOrderByLoop(root);
    printf("\n");
}

void TestInOrder()
{
    printf("================= %s ==============\n",__FUNCTION__);
    TreeNode* root;
    TreeInit(&root);
    TreeNode* a=CreateNode('a');
    TreeNode* b=CreateNode('b');
    TreeNode* c=CreateNode('c');
    TreeNode* d=CreateNode('d');
    TreeNode* e=CreateNode('e');
    TreeNode* f=CreateNode('f');
    TreeNode* g=CreateNode('g');
    root=a;
    a->lchild=b;
    a->rchild=c;
    b->lchild=d;
    b->rchild=e;
    c->rchild=f;
    e->lchild=g;

    printf("-------- 递归先序遍历 -------------\n");
    TreeInOrder(root);
    printf("\n");
    printf("-------- 非递归先序遍历 -------------\n");
    TreeInOrderByLoop(root);
    printf("\n");
}

void TestPostOrder()
{
    printf("================= %s ==============\n",__FUNCTION__);
    TreeNode* root;
    TreeInit(&root);
    TreeNode* a=CreateNode('a');
    TreeNode* b=CreateNode('b');
    TreeNode* c=CreateNode('c');
    TreeNode* d=CreateNode('d');
    TreeNode* e=CreateNode('e');
    TreeNode* f=CreateNode('f');
    TreeNode* g=CreateNode('g');
    root=a;
    a->lchild=b;
    a->rchild=c;
    b->lchild=d;
    b->rchild=e;
    c->rchild=f;
    e->lchild=g;

    TreePostOrder(root);
    printf("\n");
}

void TestLevelOrder()
{
    printf("================= %s ==============\n",__FUNCTION__);
    TreeNode* root;
    TreeInit(&root);
    TreeNode* a=CreateNode('a');
    TreeNode* b=CreateNode('b');
    TreeNode* c=CreateNode('c');
    TreeNode* d=CreateNode('d');
    TreeNode* e=CreateNode('e');
    TreeNode* f=CreateNode('f');
    TreeNode* g=CreateNode('g');
    root=a;
    a->lchild=b;
    a->rchild=c;
    b->lchild=d;
    b->rchild=e;
    c->rchild=f;
    e->lchild=g;

    TreeLevelOrder(a);
}

void TestCreateTree()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    TreePreOrder(node);
    printf("\n");
}

void TestClone()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    TreePreOrder(node);
    printf("\n");
    TreeNode* new_root=TreeClone(node);
    TreePreOrder(new_root);
    printf("\n");
}

void TestSize()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    TreePreOrder(node);
    printf("\n");
    size_t len1=TreeSize(node);
    size_t len2=TreeSize2(node);
    printf("len1= %lu,len2=%lu \n",len1,len2);
}
void TestLeafSize()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    TreePreOrder(node);
    printf("\n");
    size_t leaf1=TreeLeafSize(node);
    size_t leaf2=TreeLeafSize2(node);
    printf("leaf1= %lu,leaf2=%lu \n",leaf1,leaf2);
}

void TestKLevel()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    TreePreOrder(node);
    printf("\n");
    size_t klen=TreeKLevelSize(node,2);
    printf("klen = %lu \n",klen);
}

void TestHeight()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    TreePreOrder(node);
    printf("\n");
    size_t kh=TreeHeight(node);
    printf("kh = %lu \n",kh);
}

void TestFind()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    TreePreOrder(node);
    printf("\n");
    TreeNodeType to_find='a';
    TreeNode* find=TreeFind(node,to_find);
    printf("find = %p\n",find);
    printf("find.data = %c\n",find->data);
}

void TestParent()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    TreePreOrder(node);
    printf("\n");
    TreeNode* parent=Parent(node,node->lchild->rchild);
    printf("parent= %c\n",parent->data);

}

void LRChild()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    TreePreOrder(node);
    printf("\n");
    TreeNode* lc=LChild(node->lchild);
    TreeNode* rc=RChild(node->rchild);
    printf("lc=%p ,rc=%p\n",lc,rc);

}

////////////////////////////////////////////////
//以下是面试题测试函数
///////////////////////////////////////////////
void TestOrderByLoop()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    printf("-------------------------  preorder  ------------------------\n");
    printf("\n");
    TreePreOrder(node);
    printf("\n");
    TreePreOrderByLoop(node);
    printf("\n");
    printf("-------------------------  inorder  ------------------------\n");
    printf("\n");
    TreeInOrder(node);
    printf("\n");
    TreeInOrderByLoop(node);
    printf("\n");
    printf("-------------------------  postorder  ------------------------\n");
    printf("\n");
    TreePostOrder(node);
    printf("\n");
    TreePostOrderByLoop(node);
    printf("\n");
}

void TestMrirro()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    printf("原树\n");
    TreePreOrder(node);
    printf("\n");
    printf("\n");
    printf("镜像一次：\n");
    TreeMirror(node);
    TreePreOrder(node);
    printf("\n");
    printf("\n");
    printf("再镜像一次，相当于原树：\n");
    TreeMirror(node);
    TreePreOrder(node);
    printf("\n");

}

void TestMrirro2()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    printf("原树\n");
    TreePreOrder(node);
    printf("\n");
    printf("\n");
    printf("镜像一次：\n");
    TreeMirrorByLoop(node);
    TreePreOrder(node);
    printf("\n");
    printf("\n");
    printf("再镜像一次，相当于原树：\n");
    TreeMirrorByLoop(node);
    TreePreOrder(node);
    printf("\n");

}
void TestMrirro3()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    printf("原树\n");
    TreePreOrder(node);
    printf("\n");
    printf("\n");
    printf("镜像一次：\n");
    TreeMirrorByLoop2(node);
    TreePreOrder(node);
    printf("\n");
    printf("\n");
    printf("再镜像一次，相当于原树：\n");
    TreeMirrorByLoop2(node);
    TreePreOrder(node);
    printf("\n");

}

void TestIsCompleteTree()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    int ret=IsCompleteTree(node);
    printf("ret=%d\n",ret);
}

void TestRebuild()
{
    printf("================ %s ==============\n",__FUNCTION__);
    TreeNodeType pre_order[]="abdegcf";
    TreeNodeType in_order[]="dbgeacf";
    size_t size=7;
    TreeNode* new_node=TreeRebuild(pre_order,in_order,size);
    TreePreOrder(new_node);
    printf("\n");
}

int main()
{
    TestInit();
    TestPreOrder();
    TestInOrder();
    TestPostOrder();
    TestLevelOrder();
    TestCreateTree();
    TestClone();
    TestSize();
    TestLeafSize();
    TestKLevel();
    TestHeight();
    TestHeight();
    TestFind();
    TestParent();
    LRChild();
    TestOrderByLoop();
    TestMrirro();
    TestMrirro2();
    TestMrirro3();
    TestIsCompleteTree();
    TestRebuild();

}
