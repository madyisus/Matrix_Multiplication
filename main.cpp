#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <string.h>
#include "matrix_mult.h"
using namespace std;

int main(int argv, char* argc[]) {
  srand(time(NULL)); 

  int n, m, k, N, n_1, i, num_of_experiments;
  string selected_algorithm;

// Se elije un algoritmo de acuerdo al indice ingresado en la terminal
  switch(atoi(argc[1])){
    case 3: selected_algorithm = "standard_mm"; break;
    case 2: selected_algorithm = "transpose_mm"; break;
    default: selected_algorithm = "strassen_mm"; break;
  }

// Si el 3er argumento es --test, realiza la multiplicacion sobre el input dado
  if((argv > 2) && (strcmp(argc[2],"--test") == 0)){
    cin>>n>>m>>k;
    vector<vector<int> > M_A(n,vector<int>(m,0)), M_B(m,vector<int>(k,0));
    read_matrix(M_A); read_matrix(M_B);

    vector<vector<int> > result;
    result = matrix_multiplication(M_A, M_B, selected_algorithm);
    print_matrix(result);
    return 0;
  }

//-------Esta sección realiza la medición de tiempo para n cada vez mayor sobre matrices de n x n----------
  
  string outfile_name = selected_algorithm + "_results.csv";
  ofstream outfile(outfile_name);
  string column_names = "n,time[ms]\n";
  outfile << column_names;

  i = 10, n_1 = 1, N = 400, num_of_experiments = 10;

// Se mide el tiempo de ejecución promedio para el algoritmo seleccionado
  for(int n = n_1; n <= N; n += i){
    cout<<n<<endl;
    double mm_total_time = 0;
    vector<vector<int> > M_A(n,vector<int>(n,0)), M_B(n,vector<int>(n,0));

    for(int j = 0; j < num_of_experiments; j++){ 
      long long single_execution_time = execution_time_ms(matrix_multiplication, M_A, M_B, selected_algorithm);
      mm_total_time += single_execution_time;
    }
    double mm_avg_time = mm_total_time / num_of_experiments;
    outfile << n << "," << mm_avg_time <<endl;
  }
  outfile.close(); 
  return 0;
}
