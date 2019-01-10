#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

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

int main()
{
    ifstream fl;
    fl.open("air_p.txt");
    if(!fl)
        cout<<"Couldnt open\n";
    vertex*f,*temp;
    string s1,s2,s3,s4;
    bool first=true;
    int i=1;
    while(fl>>s1)
    {
        fl>>s2>>s3>>s4;
        /*s1.resize(26,' ');
        s2.resize(50,' ');
        s3.resize(15,' ');
        s4.resize(15,' ');*/
        if(first)
        {
            first=false;
            f=new vertex(i,s2,s3,s1,s4);
            temp=f;
            i++;
            continue;
        }
        temp->down=new vertex(i,s2,s3,s1,s4);
        temp=temp->down;
        i++;
    }
    tot_airports=i-1;
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
        //s.resize(15,' ');
        //d.resize(15,' ');
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
    show_all_airports(f);
    //bft(f);

    route(f,20,13);
    route(f,13,16);
    route(f,13,20);
    route(f,20,16);
    return 0;
}
