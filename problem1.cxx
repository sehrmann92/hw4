#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void numbers(double* p,const int N);
void minmax(double*p,const int N, double& max, double& min);
void Ausgabe(double *p,const int N);

int main(void)
{
	//Variablendeklaration
	const int N=10;
	double ar[N];
	double min, max;
	
	//Array füllen und ausgeben über Funktionen
	numbers(ar,N);
	Ausgabe(ar,N);
	
	
	//Minimum und Maximum bestimmen inkl. Ausgabe
	minmax(ar,N,max,min);
	cout << "Minimum \t"<<min<<endl;
	cout << "Maximum \t"<<max<<endl;
		
	return 0;
}

void numbers(double* p, const int N)
{
	for(int i=0;i<N;i++)
	{
		p[i]=double(rand());
	}
}

void minmax(double* p, const int N, double& max, double& min)
{
	//Minimum und Maximum initialisieren
	max=p[0];
	min=p[0];
	
	//Vergleichen
	for(int i=1; i<N; i++)
	{
		if(max<=p[i])
		{
			max=p[i];
		}
	}
}

void Ausgabe(double *p,const int N)
{
	for(int i=0;i<N;i++)
	{
		cout<<p[i]<<endl;
	}
}