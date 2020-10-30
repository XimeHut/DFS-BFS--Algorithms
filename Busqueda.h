/*
	Busqueda.h es un programa que busca el camino entre nodos 
	y su costo de un grafo NO DIRIGIDO. 
	Para su funcionamiento es necesario que reciba el nodo inicial
	el nodo final y el nombre del archivo txt.
	
	Autor: Ximena Hutchinson 
	
*/
#include <iostream> // Para el manejo de datos cin y cout 
#include <fstream> //Para el manejo de archivos
#include <vector> //Para el manejo de vectores
#include <stack> // Para el manejo de Pilas
#include <queue> // Para el manjeo de Colas

#define MAX 200 //Se utilizará para el numero de elementos max que puede tener un arreglo.
// A un arreglo no se le pude modificar el tamaño por eso es importante establecerlo desde un principio. 
//Si se quiere trabajar con más elementos se modificaría esta parte.
using namespace std;
//Declaracion de vectores
vector < vector <int> > Lista; //Vector de vectores para el Grafo  *Estos se usaran para guardar los datos del txt
vector < vector <int> > Costo; // Vector de vectores para el Grafo con costos

int n , a ; // Declaracion de enteros n-> numero de nodos   a-> numero de aristas

class Busqueda{
	
	public: //Todos los métodos son publicos para poder usarlos
		
	//Imprimir los datos que tiene la lista de adyacencia Lista
	void imprimir()
	{
	  for ( int i = 0; i < Lista.size(); i++ ) //Este for es para que pase por todos los nodos del vector
		{
		   for (int j = 0; j < Lista[i].size(); j++ ) //Este for es para que pase por todos los conexiones  que tenga un nodo
		   {
		   	  
		      cout << Lista[i][j]<<" "; //Se imprime el numero de la poscion correspondiente y un espacio para separar los nuemeros
		   }
		   cout << "\n"; //Salto de linea para separar todos los datos de un nodo de otro
		}
	}
	//Imprimir los datos que tiene la lista de adyacencia con costos Costo
	void imprimir2()
	{
		for ( int i = 0; i < Costo.size(); i++ ) //Este for es para que pase por todos los nodos del vector
		{
		   for (int j = 0; j < Costo[i].size(); j++ )  //Este for es para que pase por todos los conexiones  que tenga un nodo
		   {
		   	  
		      cout << Costo[i][j]<<" "; //Se imprime el numero de la poscion correspondiente y un espacio para separar los nuemeros
		   }
		   cout << "\n"; //Salto de linea Salto de linea para separar todos los datos de un nodo de otro
		}	
	}

	//Calcular costo camino
	void costo (vector<int> camino) //Recibe un vector como parametro
	{
		int c, resultado; //Declaramos variables de tipo entero 
	
		cout <<endl<< "Costo: "; //Se imprime esto , con cout << *endl es para el salto de linea
		   for( int i = camino.size() - 1 ; i >= 0 ;i--) //Este for pasa por todos los datos del camino 
		   													//Va desde el camino.size()-1  hasta  0 para imprimir los numeros de inicio a fin
		   {
			for ( int j = 0; j < Costo.size(); j++ ) //Esto for hace que se pasen por todos los nodos
			{
			   for (int k = 0; k < Costo[j].size(); k++ ) //Este for hace que se pase por todas las nodos que estan conectados 
			   { 													   //CONDICION: En el vector Costo pongo la pos del numero del camino que estoy buscando  												
			   	  if(Costo[camino[i]][k]==camino[i-1] && !(k-1)% 2==0 ) //y k para recorrer todas las aritas de ese nodo y tiene que ser igual al numero siguiente de mi camino
				  {														//Tambien la posicion anterior a k NO puede ser PAR 
			   	  														//por si hay numeros repetidos que no se confundan los costos de los nodos
			   	  
			   	  	c = Costo[camino[i]][k+1]; //Como los costos de las aristas estan a lado de los nodos , se mueve una posicion a la derecha para imprimir el costo
			   	    cout << c << "+"; // Esto es para imprimir el costo que tiene casa arista 
			   	  	resultado = resultado + c; //Se sumnas los costos finales 
			   	
			   	  	i--; //Para que vaya al siguiente elemento del camino 
				  }
			   }
			}
		  }
		  cout<<endl<<"="<<resultado; //Imprime el resultado
	}

	// Lectura del grafo 

	void leeGrafo(string archivo)
	{
		int x,y,z; //Declaracion de variables enteras que se utulizaran 	
		ifstream miArchivo(archivo); //Obtener el string del nombre del archivo que se desea abrir
		miArchivo >> n >> a; //En la primera linea del txt se encuentra el numero de nodos y de aristas 
							//que se guardaran en estas variables respectivamente
	
		Lista.resize(n); //Se asigna el tamaño al vector dependiendo de cuantos nodos tendra al grafo
		Costo.resize(n); //resize() es para eso
		if (miArchivo.is_open())
		{
			for(int i = 0; i<a ; i++) // Este for va desde 0 hasta el numero de aristas para leer los datos
									 //siguientes de archivo.txt
			{
				miArchivo >> x >> y >> z; // x-> nodo 1 , y -> nodo 2 , z -> costo
		     	//cout << x << y << z <<endl; //Para ver que numeros se estan manipulando
		     	
		     	//Como los vectores ya tiene el size de n , se ocupa el valor del x para indiciar la posicion 
		     	//en la que guardara y , o sea los nodos con los que se conecta
				Lista[x].push_back(y); //push_back sirve para insertar un elemento al final del vector
				Lista[y].push_back(x);  //Como el grafo es no dirigido se tiene que guardar tambien el nodo al reves	
				//Vector donde estan las aristas con su costo
				//Mismo proceso de arriba pero ahora si tomoas en cuenta el costo para guardarlo
				Costo[x].push_back(y);
				Costo[x].push_back(z);
				Costo[y].push_back(x);
				Costo[y].push_back(z);	 
			}
			miArchivo.close(); //Cerramos el archivo.txt
		}
		else
		{
			cout<< "Error al abrir el archivo"<<endl; //Si el archivo no se encuentra en la misma o hay 
													 //Un error en el archivo se mostrara este mensaje
		}
		//Estos métodos se comentados son para verificar que los datos del vector sean los mismos del txt , se puden usar o no
		//imprimir(); 
		//imprimir2();
	}

	// Búsqueda usando DFS o BFS 
	void caminoGrafo(int inicio, int final, int algoritmo) //int algoritmo recicibe 0 para DFS o 1 para BFS
	{
		int metodo = algoritmo;
		
		if(metodo==0) //Para DFS
		{
		  stack<int> miEstructura; //Stack - Pila declara miEstructura como tipo stack (recordar agregar libreria <stack> al inicio)
		  vector<bool> visitados(n, false); //vector para guardar los nodos visitados true->visitados , false -> no visitados
		  									//es de tamaño n por que en n esta guardado el numero de nodos que tiene el grafo
		  vector<int> camino; //vector para guardar el camino
		  
		  int nodo[MAX]; //	Para el control de nodos y el recorrido que hacen
		  int actual; //Establecer el nodo actual
		
	  	   miEstructura.push(inicio); //Se mete el primer nodo a la pila , el metodo push sirve para insertar valores
	  	   
	  	   nodo[inicio] = -1; //A la posicion del nodo inicio le damos un valor de -1 
	  	   visitados[inicio] = true; // El primer nodo se marca como visitado 
	         
		   while( !miEstructura.empty() ){ //Esto se refiere que mientras la pila NO este vacia todo lo de adentro del while se hara 
		   	
	       actual = miEstructura.top(); //A actula se le asigna el valor que esta hasta arriba de la pila , osea el ultimo que entro
		   miEstructura.pop(); //.pop() sirve para eliminar el elmento de hasta arriba de la pila 
		   
	       for(int i = 0 ; i < Lista[actual].size() ; ++i ) //**Desde aqui 
		   {  
		      
	          int d = Lista[actual][i];
	          //cout << v <<endl;
	          if( !visitados[d])
				  {                   
			        visitados[d] = true;
			        nodo[d] = actual;                
			        miEstructura.push(d);
		          }
	          }
	      }
	        ///Imprimir el camino
			    actual = final;
			    while(1) // permitir la ejecución sin limite del contenido del ciclo
				{
		        camino.push_back(actual);
		        if( nodo[actual] == -1 )break; //Se sale del while 
		        actual = nodo[actual];
			    }
			    
			    if(camino.empty()) //Si en el el vector de camino no hay nada quiere decir que no hay camino 
			    				  //del nodo inicial dado al nodo final dado y se mostrara el siguiente mensaje
			    {
			    	cout << "NO HAY CAMINO";  
				}
				else
				{
					cout << "Camino DFS:\n";  
				   for( int j = camino.size() - 1 ; j >= 0 ; --j ) //Este for pasa por todos los datos del camino 
				   	{											 // y los imprime uno por uno con un "-" entre ellos	
				   		cout << camino[j] << "-";//Va desde el camino.size()-1  hasta  0 para imprimir los numeros de inicio a fin
				    }
				 costo(camino); //mando el vector de camino al metodo costo para calcular el costo del camino
				}
   
		}

		
		if(metodo == 1) //BFS
		{
		  queue<int> miEstructura; //Queue- Pila
		  vector<bool> visitados(n, false); //vector para los visitados
		  vector<int> camino; //camino
		  
		  int nodo[MAX]; //nodo guia
		  int actual;
		
	  	   miEstructura.push(inicio);
	  	   
	  	   nodo[inicio] = -1;
	  	   visitados[inicio] = true;
	       
	       
		   while( !miEstructura.empty() ){
		   	
	       actual = miEstructura.front(); 
		   miEstructura.pop();
	       for(int i = 0 ; i < Lista[actual].size() ; ++i )
		   {  
		      //cout << "Entro aqui"<<endl;
	          int v = Lista[actual][i];
	          //cout << v <<endl;
	          if( !visitados[v])
				  {                   
			        visitados[v] = true;
			        nodo[v] = actual;                
			        miEstructura.push(v);
		          }
		    
	          }
	      }
	    ///Imprimir camino
		
			    actual = final;
			    while(1)
				{
			//	cout << "Entro aqui";	
		        camino.push_back(actual);
		        if( nodo[actual] == -1 )break;
		        actual = nodo[actual];
			    }
			    
			    if(camino.empty())
			    {
			    	cout << "NO HAY CAMINO";
				}
				else
				{
					cout << "Camino BFS:\n";
		
				   for( int j = camino.size() - 1 ; j >= 0 ; --j )
				   {
				 	
				   	cout << camino[j] << "-";
				   }
				 costo(camino);
				}
			}
	}
	
};

