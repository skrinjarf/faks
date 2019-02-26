#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <queue>
#include <list>
#include <fstream>

using namespace std;

class TreeVertex		//cvorovi koji se dobivaju generiranjem stabla u kojima se pamti roditelj onaj koji ga je generirao i cijena do roditelja do njega
{
private:

	int broj;			//redni broj grada(cvora)
	TreeVertex* parent;	//roditelja odredujemo za vrijeme DFS-algoritma
	int weight;			//cijena od roditelja do njega
public:

	TreeVertex(int i,int w, TreeVertex* p){                  //koristi se kod expandanja roditelja onda iz tablice procitam sve susjede i kreiram cvorove od njih
		broj = i;
		weight = w;
		parent = p;
	}
	TreeVertex(int i) {                             //koristi se kod kreiranja korjena stabla pretrazivanja
		broj = i;
		parent = nullptr;
		weight=0;
	}
	TreeVertex() {
		broj = 0;			//prvi cvor ima broj 1, 0 je neinicijalizirani cvor
		parent = nullptr;
		weight=0;
	}
	TreeVertex(const TreeVertex& t):broj(t.broj),weight(t.weight)       //CCtor
	{
	    parent=t.parent;
	}
	TreeVertex& operator=(const TreeVertex& v)     //OP
	{
	    broj=v.broj; parent=v.parent; weight=v.weight;
	}
	~TreeVertex()=default;      //dest



	int index(void) const { return broj; }
	void postavi_index(int i) { broj = i; }
	int cijena(void) const { return this->weight; }
	void postavi_cijenu(int i) { weight= i; }
	TreeVertex* roditelj(void) const { return parent; }
};

bool operator<(const TreeVertex& lhs, const TreeVertex& rhs)        //treba za priorityqueue
{
	return lhs.cijena() < rhs.cijena();
}

class Graph
{
private:
		int **edges;						//edges od I i J je broj putnika koji se moze prebaciti izmedu vrhova I i J, 0 ako nema ceste
		int dim;
public:

		Graph(int _dim){
			dim=_dim;

			edges=(int **)malloc (dim*sizeof(int*));
			for(int i=0;i<dim;++i) edges[i]=(int*) malloc (dim*sizeof(int));			//alokacija matrice

			for(int i=0;i<dim;++i) for(int j=0;j<dim;++j) edges[i][j]=0;  		//postavljanje elemenata na nulu tj nema ceste izmedu gradova
		}

		~Graph(){
			for(int i=0;i<dim;++i) free(edges[i]);
			free(edges);													//dealokacija prvo redci pa zavrsni
		}


		int cijena(int a, int b)					//cijena izmedu grada 'a' i 'b'
				{
					if((a>=dim)||(b>=dim) || (a<0) || (b<0)){ throw runtime_error("indexi su izvan dimenzije"); return -1;}
					return edges[a][b];
				}
		int dimenzija(void) {return dim;}

		bool postavi_cijenu(int i, int j, int cijena)
		{
			if((i>=dim) || (j>=dim) || (i<0) || (j<0)){ throw runtime_error("indexi su izvan dimenzije"); return -1;}
			edges[j][i]=edges[i][j]=cijena;
		}
};

//_________________________funkcije za UCS____________________________

void expand(TreeVertex* n, Graph& g, list<TreeVertex>& e)
{
    int i=n->index();
    for(int j=0 ; j<g.dimenzija() ; ++j)            //odi po svim cvorovima grafa i pogledaj sa kojima n ima neku cijenu vecu od 0, tada izmedu njih postoji cesta
    {
        if(g.cijena(i,j)>0){
            int tempCijena;
            if(n->roditelj()==nullptr)tempCijena=g.cijena(i,j);
            else if(g.cijena(i,j)>=n->cijena()) {tempCijena=n->cijena(); }    //svaki cvor pamti najmanju cijenu od vrha do sebe jer je ona usko grlo na njegovom putu
            else {tempCijena= g.cijena(i,j);}

            TreeVertex temp=TreeVertex(j,tempCijena,n);

            e.push_front(temp);

        }
    }
}

void path(TreeVertex& n, list<int>& pathList)
{
    TreeVertex* p=&n ;
    while(p->index() != 0 )  {
        pathList.push_front(p->index() +1);
        p=(p->roditelj());
    }
    pathList.push_front(1);
}

int main()
{

	//___________________________inicijalizacija____________________

	int N ;		//broj vrhova

	cin>>N;

    priority_queue<TreeVertex> open;                         //lista otvorenih cvoroa za ucs
	int visited[N];		                              //lista posjecenih cvorova
    list<int> pathList;
    TreeVertex cvorovi[N];                              //lista cvorova od pocetka do cilja

	Graph graf(N);  	        	// postavljanje grafa

	//_______________________popunjavanje grafa_____________________

	int R;   //broj cesti
    cin>>R;

	for (int i=0; i<R; ++i)
		{
			int index1,index2,cijena;
			cin>>index1>>index2>>cijena;
			graf.postavi_cijenu(--index1,--index2,cijena-1);		//cijenu mozemo umanjit za jedan jer je voditelj turista uvijek prisutan
		}

	int pocetak, cilj, br_turista;
	cin>>pocetak>>cilj>>br_turista;

	pocetak-- ; cilj-- ;                    //unose se cvorovi indexa 1..N a pohranjeno je od 0..N-1

	//________________________ UCS_________________________

    int uskoGrlo,brProlaza;

	open.push(TreeVertex(pocetak));             //inicijalizacija korjena sa int pocetak i kuranje u open, koristi se konstruktor sa jednim intom
    for(int i=0;i<N;++i)visited[i]=0; //nijedan cvor nije posjecen na pocetku
	int brojac=-1;               //prati aktualnu poziciju polju cvorovi koja se obraduje
	while(!open.empty())
    {
        brojac++;
        cvorovi[brojac] = open.top();
        open.pop();             //izbaci prvi element iz prioritetnog reda


        if( cvorovi[brojac].index() == cilj) {
            uskoGrlo=cvorovi[brojac].cijena();
            br_turista%uskoGrlo==0 ? brProlaza=br_turista/uskoGrlo : brProlaza=br_turista/uskoGrlo + 1;   //ako mogu cijeli broj puta prevest preko grla onda je to br prolaza, ako imam ostatak dijeljenje daje pod pa moram jos jednom prevest mali komad
            cout<<"Broj Prolaza je "<<brProlaza;
            path(cvorovi[brojac],pathList);                   //odredi put od cvora do n i spremi u pathList
            cout<<endl<<"put od korjena do lista je: ";
            for(int x: pathList)     //ispis puta od pocetka do cvora
            {
                cout<<x<<" ";
            }

            return 0;
        }
        visited[cvorovi[brojac].index()]=1;               //posjetio sam n
        list<TreeVertex> expanded;              //lista u koju spremam expandane cvorove od n
        expand(&cvorovi[brojac],graf,expanded);                 //funkcija koja nade susjede od n u grafu i spemi u listu
        for(TreeVertex& m: expanded)
        {
            if(visited[m.index()]==0){
                open.push(m);
            }
        }
    }

return -1;      //faliure
}

