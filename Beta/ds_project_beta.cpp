#include<iostream>
#include<fstream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#include<iomanip>
#include<stack>
#define Degree 3
using namespace std;
struct avl_node
{
    double data;
    string s_name;
    int s_no;
    struct avl_node *left;
    struct avl_node *right;
};

class avlTree
{
    public:
        avl_node **arr;
        int Size;
        int height(avl_node *);
        int diff(avl_node *);
        avl_node *rr_rotation(avl_node *);
        avl_node *ll_rotation(avl_node *);
        avl_node *lr_rotation(avl_node *);
        avl_node *rl_rotation(avl_node *);
        avl_node* balance(avl_node *);
        avl_node* insert_av(avl_node *, double ,string,int);
        void display(avl_node *, int);
        void inorder(avl_node *);
        void range(double start,double endi,avl_node*,int pres);
        void inorderIterative(avl_node*);
        avlTree()
        {
            Size=0;
        }
};

class state
{
    public:
    int sno;
    string name;
    string capital;
    int population;
    float growth;
    int area;
    int density;
    int sex_ratio;
    float literacy;
    string maj_rel;
    float hindu;
    float muslim;
    float christ;
    float sikh;
    float budh;
    float jain;
    float others;
    float atheist;
    void out()
    {
        cout<<"Statemplate <typename AS>te Number : "<<sno<<endl;
        cout<<"Name of State : "<<name<<endl;
        cout<<"Capital of State : "<<capital<<endl;
        cout<<"Population of State : "<<population<<endl;
        cout<<"Growth of State : "<<growth<<endl;
        cout<<"Area of State : "<<area<<endl;
        cout<<"Density of State : "<<density<<endl;
        cout<<"Sex Ratio of State : "<<sex_ratio<<endl;
        cout<<"Literacy of State : "<<literacy<<endl;
        cout<<"Majority Religion of State : "<<maj_rel<<endl;
        cout<<"Hindu Percentage of State : "<<hindu<<endl;
        cout<<"Muslim Percentage of State : "<<muslim<<endl;
        cout<<"Christian Percentage of State : "<<christ<<endl;
        cout<<"Sikh Percentage of State : "<<sikh<<endl;
        cout<<"Budh Percentage of State : "<<budh<<endl;
        cout<<"Jain Percentage of State : "<<jain<<endl;
        cout<<"Others Percentage of State : "<<others<<endl;
        cout<<"Atheist Percentage of State : "<<atheist<<endl;
    }

};
class BTreeNode
{
public:
    state *keys;
    int t;
    BTreeNode **C;
    int n;
    bool leaf;
    BTreeNode(int _t, bool _leaf);
    void insertTreeNonFull(state k);
    void splitChild(int i, BTreeNode *y);
    void traverse();
    void stateNames();
    state *searchTree(int k);
    friend class BTree;
    void traverse_and_put(avl_node*&,avlTree&);
    void traverse_and_put_area(avl_node*&rt,avlTree &av_tree);
    void traverse_and_put_literacy(avl_node*&rt,avlTree &av_tree);
};

class BTree
{
public:
    BTreeNode *root;
    int t;
    BTree(int x)
    {
        root = NULL;
        t = x;
    }

    void traverse()
    {
        if (root != NULL)
            root->traverse();
    }

    void stateNames()
    {
        if (root != NULL)
            root->stateNames();
    }

    state* searchTree(int k)
    {
        return (root == NULL)? NULL : root->searchTree(k);
    }
    void traverse_and_put(avl_node*&rt,avlTree &av_tree)
    {
        root->traverse_and_put(rt,av_tree);
    }
    void traverse_and_put_area(avl_node*&rt,avlTree &av_tree)
    {
        root->traverse_and_put_area(rt,av_tree);
    }

    void traverse_and_put_literacy(avl_node*&rt,avlTree &av_tree)
    {
        root->traverse_and_put_literacy(rt,av_tree);
    }

    void insertTree(state k);
};

class vertex;

class adj
{
public:
    adj*next;
    vertex*ptr;
    double wt;
    adj(vertex*x,double w)
    {
        next=NULL;
        ptr=x;
        wt=w;
    }
};

class vertex
{
public:
    vertex*down;
    int key;
    string airport_name;
    string city;
    string state;
    string type;
    adj*head;
    bool visited;
    vertex(int al,string an,string c,string st,string tp)
    {
        key=al;
        head=NULL;
        down=NULL;
        visited=false;
        airport_name=an;
        type=tp;
        city=c;
        state=st;
    }

};
int tot_airports;
void add_to_adj(vertex*t1,vertex*t2,double w)
{
    if(t1->head==NULL)
    {
        t1->head=new adj(t2,w);
    }
    else
    {
        adj*temp=t1->head;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=new adj(t2,w);
    }
}

void add_node(vertex*f,int c1,int c2,double w)
{
    vertex*temp=f;
    vertex*t1,*t2;
    t1=NULL;
    t2=NULL;
    adj*temp2;
    while(temp!=NULL)
    {
        if(temp->key==c1)
            t1=temp;
        if(temp->key==c2)
            t2=temp;
        temp=temp->down;
    }
    add_to_adj(t1,t2,w);
    //add_to_adj(t2,t1);directed
}

void vis_reset(vertex*f)
{
    while(f!=NULL)
    {
        f->visited=false;
        f=f->down;
    }
}

void bft(vertex*f)
{
    vertex*q[tot_airports];
    int fr=0,bk=1;
    q[0]=f;
    f->visited=true;
    while(fr!=bk)
    {
        cout<<q[fr]->key<<"  "<<q[fr]->airport_name<<" "<<q[fr]->city<<endl;
        adj*temp=q[fr]->head;
        fr++;
        while(temp!=NULL)
        {
            if(!(temp->ptr->visited))
            {
                q[bk++]=temp->ptr;
                temp->ptr->visited=true;
            }
            temp=temp->next;
        }
    }
    cout<<endl<<endl;
    vis_reset(f);
}

void show_all_airports(vertex*t)
{
    string s1,s2,s3,s4;
    while(t!=NULL)
    {
        cout<<setw(2)<<setfill(' ')<<t->key<<" ";
        s1=t->state;
        s2=t->airport_name;
        s3=t->city;
        s4=t->type;
        s1.resize(26,' ');
        s2.resize(50,' ');
        s3.resize(15,' ');
        s4.resize(15,' ');
        cout<<s2<<" "<<s3<<" "<<s1;
        if(t->head==NULL)
            cout<<"NO CONNECTIVITY ";
        cout<<endl;
        t=t->down;
    }
}

double time_dif(int a,int b)
{
    int bm,am,ah,bh;
    double dm,dh;
    bm=b%100;
    am=a%100;
    bh=b/100;
    ah=a/100;
    dm=(bm-am);
    dh=(bh-ah);
    if(dm<0)
    {
        dm=60-dm;
        dh=dh-1;
    }
    if(dh<0)
    {
        dh=24-dh;
    }
    double diff;
    diff=dh+dm/60;
    return diff;
}

void shortest_path(vertex*strt,vertex*fr,vertex*to)
{
    double dist[tot_airports+1];
    bool vis[tot_airports+1];
    string path[tot_airports+1];
    for(int i=1;i<=tot_airports;i++)
    {
        vis[i]=false;
        dist[i]=-1;
        path[i]=fr->airport_name;
    }
    vertex*temp=fr;
    double d_from_src=0;
    int tot=tot_airports;
    adj*temp2;
    while(tot--)
    {
        temp2=temp->head;
        vis[temp->key]=true;
        while(temp2!=NULL)
        {
            if((dist[temp2->ptr->key]==-1)||(dist[temp2->ptr->key]>(d_from_src+temp2->wt)))
            {
                dist[temp2->ptr->key]=d_from_src+temp2->wt;
                path[temp2->ptr->key]=path[temp->key]+" -> "+temp2->ptr->airport_name;
            }
            if(temp2->ptr==to)
            {
                cout<<"\n\nThe total time taken is :"<<dist[temp2->ptr->key]<<endl;
                cout<<"The path is :\n"<<path[temp2->ptr->key]<<endl<<endl;
                return;
            }
            temp2=temp2->next;
        }

        bool first=true;
        double s_dist;
        int s_j=1;
        for(int j=1;j<=tot_airports;j++)
        {
            if(dist[j]==-1||vis[j])
                continue;
            if(first)
            {
                first=false;
                s_dist=dist[j];
                s_j=j;
                continue;
            }
            if(dist[j]<s_dist)
            {
                s_j=j;
                s_dist=dist[j];
            }
        }
        vertex*temp3=strt;
        int s_j2=s_j;
        while(temp3!=NULL)
        {
            if(temp3->key==s_j2)
                break;
            temp3=temp3->down;
        }
        temp=temp3;
        d_from_src=dist[s_j2];
    }
}

void route(vertex * f,int a1,int a2)
{
    vertex *fr,*to;
    vertex* f2=f;
    while(f!=NULL)
    {
        if(f->key==a1)
            fr=f;
        if(f->key==a2)
            to=f;
        f=f->down;
    }
    shortest_path(f2,fr,to);
}



int avlTree::height(avl_node *temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}


int avlTree::diff(avl_node *temp)
{
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}


avl_node *avlTree::rr_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

avl_node *avlTree::ll_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}


avl_node *avlTree::lr_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->left;
    parent->left = rr_rotation (temp);
    return ll_rotation (parent);
}

avl_node *avlTree::rl_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->right;
    parent->right = ll_rotation (temp);
    return rr_rotation (parent);
}


avl_node *avlTree::balance(avl_node *temp)
{
    int bal_factor = diff (temp);
    if (bal_factor > 1)
    {
        if (diff (temp->left) > 0)
            temp = ll_rotation (temp);
        else
            temp = lr_rotation (temp);
    }
    else if (bal_factor < -1)
    {
        if (diff (temp->right) > 0)
            temp = rl_rotation (temp);
        else
            temp = rr_rotation (temp);
    }
    return temp;
}


avl_node *avlTree::insert_av(avl_node *root, double value,string sname,int sno)
{
    if (root == NULL)
    {
        root = new avl_node;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        root->s_name=sname;
        root->s_no=sno;
        Size++;
        return root;
    }
    else if (value < root->data)
    {
        root->left = insert_av(root->left, value,sname,sno);
        root = balance (root);
    }
    else if (value >= root->data)
    {
        root->right = insert_av(root->right, value,sname,sno);
        root = balance (root);
    }
    return root;
}



BTreeNode::BTreeNode(int t1, bool leaf1)
{
    t = t1;
    leaf = leaf1;
    keys = new state[2*t-1];
    C = new BTreeNode *[2*t];
    n = 0;
}

void BTreeNode::traverse()
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            C[i]->traverse();
        keys[i].out();
        cout<<endl;
    }
    if (leaf == false)
        C[i]->traverse();

}

void BTreeNode::stateNames()
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            C[i]->stateNames();
        cout<<keys[i].sno<<"\t"<<keys[i].name;
        cout<<endl;
    }
    if (leaf == false)
        C[i]->stateNames();

}

state *BTreeNode::searchTree(int k)
{
    int i = 0;
    while (i < n && k > keys[i].sno)
        i++;
    if (keys[i].sno == k)
        return this->keys+i;
    if (leaf == true)
        return NULL;
    return C[i]->searchTree(k);
}

void BTree::insertTree(state k)
{
    if (root == NULL)
    {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else
    {
        if (root->n == 2*t-1)
        {
            BTreeNode *s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0].sno < k.sno)
                i++;
            s->C[i]->insertTreeNonFull(k);
            root = s;
        }
        else
            root->insertTreeNonFull(k);
    }
}

void BTreeNode::insertTreeNonFull(state k)
{
    int i = n-1;
    if (leaf == true)
    {
        while (i >= 0 && keys[i].sno > k.sno)
        {
            keys[i+1] = keys[i];
            i--;
        }
        keys[i+1]=k;
        n = n+1;
    }
    else
    {
        while (i >= 0 && keys[i].sno > k.sno)
            i--;
        if (C[i+1]->n == 2*t-1)
        {
            splitChild(i+1, C[i+1]);
            if (keys[i+1].sno < k.sno)
                i++;
        }
        C[i+1]->insertTreeNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y)
{
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }
    y->n = t - 1;
    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];
    C[i+1] = z;
    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];
    keys[i] = y->keys[t-1];
    n = n + 1;
}

void BTreeNode::traverse_and_put(avl_node*&rt,avlTree &av_tree)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            C[i]->traverse_and_put(rt,av_tree);
        rt=av_tree.insert_av(rt,keys[i].population,keys[i].name,keys[i].sno);
    }
    if (leaf == false)
        C[i]->traverse_and_put(rt,av_tree);
}

avl_node* take_from_btree(BTree bt,avl_node *rt,avlTree &av_tree)
{
    bt.traverse_and_put(rt,av_tree);
    return rt;
}

void BTreeNode::traverse_and_put_area(avl_node*&rt,avlTree &av_tree)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            C[i]->traverse_and_put_area(rt,av_tree);
        rt=av_tree.insert_av(rt,keys[i].area,keys[i].name,keys[i].sno);
    }
    if (leaf == false)
        C[i]->traverse_and_put_area(rt,av_tree);
}

avl_node* take_from_btree_area(BTree bt,avl_node *rt,avlTree &av_tree)
{
    bt.traverse_and_put_area(rt,av_tree);
    return rt;
}

//literacy:
void BTreeNode::traverse_and_put_literacy(avl_node*&rt,avlTree &av_tree)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            C[i]->traverse_and_put_literacy(rt,av_tree);
        rt=av_tree.insert_av(rt,keys[i].literacy,keys[i].name,keys[i].sno);
    }
    if (leaf == false)
        C[i]->traverse_and_put_literacy(rt,av_tree);
}

avl_node* take_from_btree_literacy(BTree bt,avl_node *rt,avlTree &av_tree)
{
    bt.traverse_and_put_literacy(rt,av_tree);
    return rt;
}

void inorder(avl_node*rt,int p)
{
    if(rt==NULL)
        return;
    inorder(rt->left,p);
    cout<<fixed<<setprecision(p)<<rt->data<<" "<<rt->s_name<<endl;
    inorder(rt->right,p);
}

void air_lines()//MAIN AIRLINE FUNCTION
{
    ifstream fl;
    fl.open("air_p.txt");
    if(!fl)
        cout<<"Couldnt open\n";
    vertex*f,*temp;
    string s1,s2,s3,s4;
    bool first=true;
    int ii=1;
    while(fl>>s1)
    {
        fl>>s2>>s3>>s4;
        if(first)
        {
            first=false;
            f=new vertex(ii,s2,s3,s1,s4);
            temp=f;
            ii++;
            continue;
        }
        temp->down=new vertex(ii,s2,s3,s1,s4);
        temp=temp->down;
        ii++;
    }
    tot_airports=ii-1;
    fl.close();
    fstream fl2;
    fl2.open("27000.txt");
    string s,d;
    int fr,to;
    while(fl2>>s)
    {
        fl2>>d;
        fl2>>fr>>to;
        vertex*t1,*t2;
        int a1,a2;
        a1=a2=true;
        vertex *temp=f;
        a1=a2=0;
        double td=time_dif(fr,to);
        while(temp!=NULL)
        {
            if(s==temp->city)
                a1=temp->key;
            if(d==temp->city)
                a2=temp->key;
            temp=temp->down;
        }
        if(a1&&a2)
            add_node(f,a1,a2,td);
    }
    fl2.close();
    AA:cout<<"Enter:\n1: To show all airports and their info\n2: Shortest route(min time taken) b/w 2 airports\n3: To return to main\n\n->";
    int choice;
    cin>>choice;
    if(choice==1)
    {
        cout<<"All the airports are :\n\n";
        show_all_airports(f);
        goto AA;
    }
    else if(choice==2)
    {
        cout<<"\n\nEnter the source (airport no.) and destination (airport no.):\n->";
        int src,dest;
        cin>>src;
        cout<<"->";
        cin>>dest;
        route(f,src,dest);
        goto AA;
    }
    else
        return;
}

void avlTree::inorderIterative(avl_node* root)
{
    int i =0;
    arr = new avl_node*[Size];
    if(root==NULL)
        return;
    stack<avl_node*>s;
    avl_node* temp = root;
    while(!s.empty() || temp!=NULL)
    {
        if(temp)
        {
            s.push(temp);
            temp = temp->left;
        }
        else
        {
            temp = s.top();
            s.pop();
            arr[i++] = temp;
            //cout<<temp->data<< " ";
            temp = temp->right;
        }
    }
}

void avlTree::range(double s,double e,avl_node*root,int p)
{
    inorderIterative(root);
    int i=0;
    while(arr[i]->data <=s)
        i++;
    while(i<Size&&arr[i]->data<=e)
    {
        cout<<fixed<<setprecision(p)<<arr[i]->data<<" "<<arr[i]->s_name<<endl;
        i++;
    }
}


    Size++;
int main()
{
    BTree t(Degree);
    state a;
    fstream stateFile;
    stateFile.open("states.txt");
    if(stateFile.fail())
        cout<<"Sorry! File Not Found.";
    while(!stateFile.eof())
    {
        stateFile>>a.sno;
        stateFile>>a.name;
        stateFile>>a.capital;
        stateFile>>a.population;
        stateFile>>a.growth;
        stateFile>>a.area;
        stateFile>>a.density;
        stateFile>>a.sex_ratio;
        stateFile>>a.literacy;
        stateFile>>a.maj_rel;
        stateFile>>a.hindu;
        stateFile>>a.muslim;
        stateFile>>a.christ;
        stateFile>>a.sikh;
        stateFile>>a.budh;
        stateFile>>a.jain;
        stateFile>>a.others;
        stateFile>>a.atheist;
        t.insertTree(a);
    }
    stateFile.close();
    //cout << "Traversal of the constucted B-Tree is : "<<endl<<endl;
    //t.traverse();
    //t.stateNames();
    int k;
    /*cout<<endl<<"Enter the State number : ";
    cin>>k;
    cout<<endl;
    state *b=NULL;
    b=t.searchTree(k);
    if(b==NULL)
        cout << "\nNot Present";
    else
        b->out();
    */
    //AVL from here
    int i=0;
    int num_states=35;
    int population[num_states];
    int density[num_states];
    int Ratio[num_states];
    string Rank[num_states],name[num_states];
    avlTree av_pop,av_area,av_literacy;
    avl_node *pop=NULL,*area=NULL,*literacy=NULL;
    pop=take_from_btree(t,pop,av_pop);
    area=take_from_btree_area(t,area,av_area);
    literacy=take_from_btree_literacy(t,literacy,av_literacy);
    cout<<"\n\nPopulation\n\n";
    inorder(pop,0);
    cout<<"\n\nArea\n\n";
    inorder(area,0);
    cout<<"\n\nLiteracy\n\n";
    inorder(literacy,2);
    av_pop.range(1000000,30000000,pop,0);
    av_area.range(100,30000,area,0);
    av_literacy.range(10,800,literacy,2);
    //airlines shortes routes and shitz
    air_lines();
    return 0;
}

