#include <iostream>
#include <stdexcept>
#include <cstdlib>
	
using namespace std;

class Vertex
{
private:

	int broj;			//redni broj grada(cvora)
	Vertex* roditelj;	//roditelja odredujemo za vrijeme DFS-algoritma
public:

	Vertex(int i){ 
		broj=i;
		roditelj=NULL;
	}
	Vertex(){ 
		broj=0;			//prvi cvor ima broj 1, 0 je neinicijalizirani cvor
		roditelj=NULL;
	}
	
	int index(void) {return broj;}
	void postavi_index(int i) { broj=i; }
	Vertex* parent;				
};


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
		
		
		int cijena(int a, int b)					//cijena izmedu grada 'i' i 'j'
				{
					int i,j;
					i=a-1; j=b-1;								//vani je cvor 5 u matrici na mjestu 4 jer je malloc od indeksa 0
					if((i>=dim)||(j>=dim) || (i<0) || (j<0)){ throw runtime_error("indexi su izvan dimenzije"); return -1;} 
					return edges[i][j];
				}
		int dimenzija(void) {return dim;}  
		
		bool postavi_cijenu(int a, int b, int cijena) 
		{
			int i,j;
			i=a-1; j=b-1;											//vani je cvor 5 u matrici na mjestu 4 jer je malloc od indeksa 0
			if((i>=dim) || (j>=dim) || (i<0) || (j<0)){ throw runtime_error("indexi su izvan dimenzije"); return -1;}
			edges[j][i]=edges[i][j]=cijena;
		}		
};

	
int main()
{
	
	//___________________________inicijalizacija____________________
	
	int N ;		//broj vrhova
	cin>>N;
	Vertex *open;           //lista otvorenih cvoroa za DFS
	Vertex *visited;		//lista posjecenih cvorova
	Vertex *vrhovi;			//svi vrhovi u grafu	
	
	vrhovi = (Vertex*) malloc (N*sizeof(Vertex));
	for(int i=0; i<N; ++i) vrhovi[i]=Vertex(i+1);       		//automatski sintetizirani operator pridruzivanja!!!
	
	Graph graf(N);  		// postavljanje grafa
	
	visited = new Vertex[N];
	open = new Vertex[N];
	
	//_______________________popunjavanje grafa_____________________
	
	int R;   //broj cesti
	cin>>R;
	for (int i=0; i<R; ++i)
		{
			int index1,index2,cijena;
			cin>>index1>>index2>>cijena;
			graf.postavi_cijenu(index1,index2,cijena-1);		//cijenu mozemo umanjit za jedan jer je voditelj turista uvijek prisutan 
		}
	
	int pocetak, cilj, br_turista;
	cin>>pocetak>>cilj>>br_turista;
	
	//________________________iterativni DFS_________________________ 	
return 0;		
}

