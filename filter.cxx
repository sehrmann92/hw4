#include <iostream> 		//Ein- und Ausgabe
#include <fstream> 			//Datein ein- und auslesen
#include <string>
#include <cstdlib>
using namespace std;

void Zeilenanzahl(const string name, int& N);									//Zeilenanzahl der eingelesenen Datei bestimmen bei unbekannter Dateilaenge (Spielerei ;))

double* Dateiauslesen(const string name, int& N); 								//Routine zum Daten auslesen
void Filtern(double* data, int& N);												//Routine zum Filtern der Daten
void Dateispeichern(const string name, int& N, double* data);					//Routine  zum Speichern von Daten
void Plot(const string nameplot, const string bild, const string namedat1, const string namedat2); //Plot erstellen

int main(void)
{
	const string dateinamein="noisy.txt"; 				//Dateiname zum Einlesen
	const string dateinameout="filtered.txt";			//Dateiname zum Speichern der Daten für die Plotübergabe
	const string dateiplot="befehlgnuplot.txt";			//Datei mit Befehlen für Gnuplot zum Plotten und anschließendes Ausführen
	const string plot="Vergleich.jpeg";					//Dateiname für Bildausgabe
	
	int N;												//Zeilenanzahl der Datei, man kann auch einfach auf N=237 setzen, weil die Zeilenanzahl hier bekannt ist
	Zeilenanzahl(dateinamein,N);
		
	double* ar=Dateiauslesen(dateinamein,N);			//ausgelesene Daten in Array speichern
	
	int iter;
	cout<<"Bitte gib die Anzahl der Filterungschritte ein:"<<endl;
	cin >> iter;
	for (int i=0;i<iter;i++)							//Iterationsschleife für Filterprozess
	{
		Filtern(ar,N);
	}
	Dateispeichern(dateinameout,N,ar);					//gefilterte Daten speichern
	Plot(dateiplot,plot,dateinamein,dateinameout);			//Daten (un)gefiltert Plotten
		
	delete[] ar;
	return 0;
}

void Zeilenanzahl(const string name, int& N)
{
	string temp;
	N=0;
	ifstream in(name.c_str());			//Datei zum lesen öffnen
	while (getline(in,temp)) N++;		//Zeilen zaehlen
	in.close();							//Datei schließen
}

double* Dateiauslesen(const string name, int& N)
{
	double* data=new double[N];			//Array zur Werte Speicherung
	
	ifstream in(name.c_str());			//Datei zum lesen öffnen
	for(int i=0; i<N; i++)
	{
		in >> data[i];					//Daten auslesen
	}
	
	in.close();							//Datei schließen
	return data;						//Daten zurückgeben
}

void Filtern(double* data, int& N)
{
	double temp=data[0];
	data[0]=(data[N-1]+data[0],data[1])/3;		//Startwert
	for(int i=1;i<N-1;i++)
	{
		data[i]=(temp+data[i]+data[i+1])/3;		//Filtervorschrift
		temp=3*data[i]-temp-data[i+1];
	}
	data[N-1]=data[0];							//periodische Randbedingung
}

void Dateispeichern(const string name, int& N, double* data)
{
	ofstream out(name.c_str());		//Datei zum Schreiben öffnen
	for(int i=0;i<N;i++)
	{
		out << data[i]<<endl;		//Daten in Datei schreiben
	}		
	out.close();					//Datei schließen
}

void Plot(const string nameplot, const string bild, const string namedat1, const string namedat2)
{
	ofstream plot(nameplot.c_str());								//Öffnen Datei für Plotbefehle
		
	plot<<"set terminal jpeg"<<endl;								//Bildausgabe auf jpeg setzen
	plot<<"set output \""<<bild<<"\""<<endl;						//Dateinamen für Bild geben
	plot<<"set st data line"<<endl;									//Plot mit Linien
	plot<<"plot \""<<namedat1<<"\", \""<<namedat2<<"\""<<endl;	//ungefiltert und gefiltert Ploten
	plot.close();													//Plotbefehldatei schließen
	
	string befehl="gnuplot ";
	befehl.append(nameplot);										//Systembefehl für Gnuplot erstellen (Eingabe wie in Konsole)
	system(befehl.c_str());											//Gnuplot ausführen
}
