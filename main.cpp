// Piotr Makosiej
#include <iostream>

using namespace std;
struct id
{
    char a;
    char b;
    char c;
    void print()
    {
        cout << a << b << c << " ";
    }
    int comparison(id x)
    {
        if(a>x.a) return 1;
        else if(a<x.a) return -1;
        else if(b>x.b) return 1;
        else if(b<x.b) return -1;
        else if(c>x.c) return 1;
        else if(c<x.c) return -1;
        if(a==x.a && b==x.b && c==x.c) return 0;
        return -1;
    }
};
struct bead_binding
{
    int value;
    id identyfikator;
    bead_binding * next=NULL;
    bead_binding * prev=NULL;
    int comparison(bead_binding *b)
    {
        if(identyfikator.comparison(b->identyfikator)==1)return 1;
        if(identyfikator.comparison(b->identyfikator)==-1)return -1;
        if(value>b->value) return 1;
        if(value<b->value) return -1;
        return 0;

    }
    void print()
    {
        identyfikator.print();
        if(value<10) cout << "00";
        else if(value<100) cout << "0";
        cout << value << " ";
    }

};
struct bead
{
    int value;
    bead * next=NULL;
    bead * prev=NULL;
    bead_binding *first=NULL;
    void print()
    {
        if(value<10) cout << "00";
        else if(value<100) cout << "0";
        cout << value << " ";
        bead_binding *iterator=first;
        while(iterator!=NULL)
        {
            iterator->print();
            iterator=iterator->next;
        }
    }
    void add_binding(bead_binding *b)
    {
        if(first==NULL)
        {
            first=b;
        }
        else
        {
            if(first->comparison(b)==0)return;
            if(first->comparison(b)==1)
            {
                b->next=first;
                b->prev=NULL;
                first->prev=b;
                first=b;
                return;
            }
            bead_binding * iterator=first;
            bead_binding * previous=NULL;
            while(iterator!=NULL)
            {
                if(iterator->comparison(b)==0)return;
                if(iterator->comparison(b)==1)
                {
                    b->next=iterator;
                    b->prev=iterator->prev;
                    iterator->prev->next=b;
                    iterator->prev=b;

                    return;
                }
                previous=iterator;
                iterator=iterator->next;
            }
            previous->next=b;
            b->prev=previous;

        }
    }
    bead_binding* search(id i,int v)
    {
        bead_binding *iterator=first;
        while(iterator!=NULL)
        {
            if(iterator->identyfikator.comparison(i)==0 && iterator->value==v)
                return iterator;
            iterator=iterator->next;
        }
        return NULL;
    }
    void delete_binding(id abc,id abc1,int v,int v1)
    {
        bead_binding* b=search(abc1,v1);
        if(first==b)
        {
            first=b->next;
            if(b->next!=NULL)
            {
                b->next->prev=NULL;
            }
        }
        if(b!=NULL)
        {
            if(b->prev!=NULL)
                b->prev->next=b->next;
            if(b->next!=NULL)
                b->next->prev=b->prev;
            delete b;
        }
    }
    void delete_me()
    {
        bead_binding *iterator=first;
        bead_binding *p=first;
        while(iterator!=NULL)
        {
            p=iterator;
            iterator=iterator->next;
            delete p;
        }
    }
};
struct lace
{
    id * identifikator=NULL;
    bead * first=NULL;
    lace * next=NULL;
    lace * prev=NULL;
    int comparison(id* x)
    {
        if(identifikator->a>x->a) return 1;
        else if(identifikator->a<x->a) return -1;
        else if(identifikator->b>x->b) return 1;
        else if(identifikator->b<x->b) return -1;
        else if(identifikator->c>x->c) return 1;
        else if(identifikator->c<x->c) return -1;
        if(identifikator->a==x->a && identifikator->b==x->b && identifikator->c==x->c) return 0;
        return -1;
    }
    void add(bead* b)
    {
        if(first==NULL)
        {
            first=b;
        }
        else
        {
            if(first->value==b->value)return;
            if(first->value>b->value)
            {
                b->next=first;
                b->prev=NULL;
                first->prev=b;
                first=b;
                return;
            }
            bead * iterator=first;
            bead * previous=NULL;
            while(iterator!=NULL)
            {
                if(iterator->value==b->value)return;
                if(iterator->value>b->value)
                {
                    b->next=iterator;
                    b->prev=iterator->prev;
                    iterator->prev->next=b;
                    iterator->prev=b;

                    return;
                }
                previous=iterator;
                iterator=iterator->next;
            }
            previous->next=b;
            b->prev=previous;
        }
    }
    void print()
    {
        identifikator->print();
        bead*iterator=first;
        while(iterator!=NULL)
        {
            cout << endl;
            iterator->print();
            iterator=iterator->next;
        }
        cout << endl;
    }
    bead* search(int v)
    {
        bead *iterator=first;
        while(iterator!=NULL)
        {
            if(v==iterator->value)
                return iterator;
            iterator=iterator->next;
        }
        return NULL;
    }
    void add_binding(int v,bead_binding *be)
    {
        bead* b=search(v);
        if(b==NULL)return;
        b->add_binding(be);
    }
    void delete_bead_binding(id abc,id abc1,int v,int v1)
    {
        bead *b=search(v);
        if(b==NULL)return;
        b->delete_binding(abc,abc1,v,v1);
    }
    void delete_bead(int v)
    {
        bead *b=search(v);
        if(b==NULL)return;
        b->delete_me();
        if(b==first)
        {
            first=b->next;
        }
        if(b->next!=NULL)
        {
            b->next->prev=b->prev;
        }
        if(b->prev!=NULL)
        {
            b->prev->next=b->next;
        }
        delete b;

    }
     bead* move_bead(int v)
    {
        bead *b=search(v);
        if(b==NULL)return NULL;
        if(b==first)
        {
            first=b->next;
        }
        if(b->next!=NULL)
        {
            b->next->prev=b->prev;
        }
        if(b->prev!=NULL)
        {
            b->prev->next=b->next;
        }
        return b;
    }
    void delete_me()
    {
        if(first==NULL)return;
        bead * iterator=first;
        bead * previous=first;
        while(iterator!=NULL)
        {
            previous=iterator;
            iterator->delete_me();
            iterator=iterator->next;
            delete previous;
        }

    }

};
struct all_laces
{
    lace * first=NULL;
    void add_lace(lace* l)
    {
        //l->print();
        //first->print();
        if(first==NULL)
        {
            first=l;
        }
        else
        {
            if(first->comparison(l->identifikator)==0) return;
            if(first->comparison(l->identifikator)==1)
            {
                l->next=first;
                l->prev=NULL;
                first->prev=l;
                first=l;
                return;
            }
            lace *iterator=first->next;
            lace * previous=first;
            while(iterator!=NULL)
            {
                if(iterator->comparison(l->identifikator)==0)return;
                if(iterator->comparison(l->identifikator)==1)
                {
                    l->next=iterator;
                    l->prev=iterator->prev;
                    iterator->prev->next=l;
                    iterator->prev=l;

                    return;
                }
                previous=iterator;
                iterator=iterator->next;
            }
            previous->next=l;
            l->prev=previous;
        }
    }
    lace* search(id i)
    {

        lace *iterator=first;
        while(iterator!=NULL)
        {
            if(0==iterator->comparison(&i))
                return iterator;
            iterator=iterator->next;
        }
        return NULL;
    }
    void add_bead(id i,int x)
    {
        lace* l=search(i);
        if(l==NULL)return;
        bead * b=new bead();
        b->value=x;
        l->add(b);
    }
    void print()
    {
        lace*iterator=first;
        while(iterator!=NULL)
        {
            iterator->print();
            iterator=iterator->next;
        }
    }
    void add_bead_binding(id a,int v,bead_binding* b)
    {
        lace* l=search(a);
        if(l==NULL)return;
        l->add_binding(v,b);
    }
    void delete_bead_binding(id abc,id abc1,int v,int v1)
    {
        lace *l=search(abc);
        if(l==NULL)return;
        l->delete_bead_binding(abc,abc1,v,v1);
    }
    void delete_bead(id i,int v)
    {
        lace * l=search(i);
        if(l!=NULL) l->delete_bead( v);
    }
    void move_bead(int v,id i1, id i2)
    {
        lace * l1=search(i1);
        lace * l2=search(i2);
        if(l2==NULL || l1==NULL) return;
        bead *b=l1->move_bead(v);
        if(b==NULL)return;
        b->next=NULL;
        b->prev=NULL;
        l2->add(b);
    }
    void delete_lace(id i)
    {
        lace * l=search(i);
        if(l==NULL) return;
        if(l==first)
        {
            first=l->next;
            if(l->next!=NULL) l->next->prev=NULL;
        }else
        {
            if(l->prev!=NULL) l->prev->next=l->next;
            if(l->next!=NULL) l->next->prev=l->prev;
        }
        l->delete_me();
        delete l;
    }
};
int main()
{
    char in;
    all_laces all;
    while(cin >> in)
    {
        if(in=='F') break;
        if(in=='S')
        {
            char a,b,c;
            cin >> a >> b >> c;
            id *abc=new (id);
            abc->a=a;
            abc->b=b;
            abc->c=c;
            lace* l=new (lace);
            l->identifikator=abc;
            all.add_lace(l);
        }else if(in=='B')
        {
            int x;
            cin >> x;
            char a,b,c;
            cin >> a >> b >> c;
            id abc={a,b,c};
            all.add_bead(abc,x);
        }else if(in=='L')
        {
            int v,v1;
            char a,b,c,a1,b1,c1;
            cin >> v >> a >> b >> c;
            cin >> v1 >> a1 >> b1 >> c1;
            id abc={a,b,c};
            id abc1={a1,b1,c1};
            bead_binding *be=new (bead_binding);
            be->identyfikator=abc1;
            be->value=v1;
            all.add_bead_binding(abc,v,be);
        }else if(in=='U')
        {
            int v,v1;
            char a,b,c,a1,b1,c1;
            cin >> v >> a >> b >> c;
            cin >> v1 >> a1 >> b1 >> c1;
            id abc={a,b,c};
            id abc1={a1,b1,c1};
            all.delete_bead_binding(abc,abc1,v,v1);
        }else if(in=='D')
        {
            char a,b,c;
            int v;
            cin >> v >> a >> b >> c;
            id abc={a,b,c};
            all.delete_bead(abc,v);
        }else if(in=='M')
        {
            int v;
            cin >> v;
            char a,b,c,a1,b1,c1;
            cin >> a >> b >> c >> a1 >> b1 >> c1;
            id abc={a,b,c};
            id abc1={a1,b1,c1};
            all.move_bead(v,abc,abc1);
        }
        else if(in=='R')
        {
            char a,b,c;
            cin >> a >> b>> c;
            id abc={a,b,c};
            all.delete_lace(abc);
        }
        else if(in=='P')
        {
            all.print();
        }
    }
}
