//including required headers
#include <bits/stdc++.h>
#include <iostream>
#include <string>
using namespace std;

//defines
#define V 1000
#define beta 0.8

//declaring variables
vector<int> adj[V];
double** M;
double* R;
double** A;
double* previous;
int user[V];

// adds an edge to the adjacency list
void addEdge(vector<int> adj[], int u, int v){
    adj[u].push_back(v);
}

//prints the adjacency list to a file named "AdjacencyList.txt"
void print_to_file(){
    ofstream outfile;
    outfile.open("AdjacencyList.txt");
    outfile<<"Node\tConnected nodes\n";
    for(int u =0; u<V; u++){
        if(adj[u].size()!=0)
            outfile<<u<<"\t";
    for (int i=0; i<adj[u].size(); i++)
        outfile<<adj[u][i]<<" ";
        if(adj[u].size()!=0)
            outfile<<"\n";

    }
    outfile.close();
}

//prints a matrix to file
void print_to_file_matrix(){
    ofstream outfile;
    outfile.open("test_A.txt");
    for(int u =0; u<V; u++){
    	for (int i=0; i<V; i++)
        	outfile<<A[u][i]<<" ";
        outfile<<"\n";
    }
    outfile.close();
}

//matrix multiplication between A matrix and R matrix(Rank matrix)
void matrix_multiplication(){
	double temp[V];
	memset(temp,sizeof(temp),0.00);
	for(int i=0;i<V;i++){
		temp[i]=0.00;
		for(int j=0;j<V;j++){
			temp[i]+=(A[i][j]*R[j]);
		}
	}
	for(int i=0;i<V;i++){
		R[i]=temp[i];
	}
}

//copies the rank matrix into previous for error calculation
void copy_array(){
	for(int i=0;i<V;i++){
		previous[i]=R[i];
	}
}

//calculating error using rmse
double error(){
	double rmse = 0.0;
	for(int i=0;i<V;i++){
		rmse+=pow(abs(R[i]-previous[i]),1);
	}
	return (rmse);
}

//prints the rank matrix(purely for testing purpose)
void print_r(){
	for(int i=0;i<12;i++){
		cout<<R[i]<<" ";
	}
	cout<<endl;
}

//adds back the leak in rank to handle deadend
void addleak_r(){
	double sum=0.00;
	for(int i=0;i<V;i++){
		sum+=R[i];
	}
	//cout<<sum<<endl;
	double cons = (double)(1-sum)/V;
	for(int i=0;i<V;i++){
		R[i]+=cons;
	}
}

//executes page rank algo using power method
void power_method(){
	int counter=0;
	while(counter<35){
		matrix_multiplication();
		//print_r();
		addleak_r();
		cout<<"Iteration "<<counter<<" "<<error()<<endl;
		copy_array();
		counter++;
	}
}

//writes the page ranks to a file
void print_page_rank(){
	ofstream outfile;
    outfile.open("Page_Rank_rg.txt");
	for(int i=0;i<V;i++){
		outfile<<i<<" "<<R[i]<<endl;
	}
}

int main()
{
	double constant = 1.00/V;  //equal probability constant
	for(int i=0;i<V;i++)	user[i]=0;

    string line;
    ifstream myfile ("rg.txt"); //reading the graph from file

    if (myfile.is_open()){
        while (getline(myfile,line)){
            istringstream iss(line);
            string token;
            string nodes[2];
            int i=0;
            while(getline(iss, token, ' ')){
                nodes[i]=token;
                i++;
            }
            int leftNode=stoi(nodes[0]);
            int rightNode=stoi(nodes[1]);
            auto it = find(adj[leftNode-1].begin(),adj[leftNode-1].end(),rightNode-1);
    		if(it==adj[leftNode-1].end()) //checking if edge already exist
    		{
	            addEdge(adj,leftNode-1,rightNode-1);   //adding the read edge into adj list
	            user[leftNode-1]=1;
	            user[rightNode-1]=1;
        	}
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    //initializing M
    M = new double*[V];
    for(int i = 0; i < V; ++i)
        M[i] = new double[V];
    for(int i=0;i<V;i++)	for(int j=0;j<V;j++)	M[i][j]=0.00;

    //performing Mij/dij where dij is the no of outlinks of ith node
    long length;
    for(int j=0;j<V;j++){
    	for(int i=0;i<V;i++){
    		length = adj[i].size();
    		auto it = find(adj[i].begin(),adj[i].end(),j);
    		if(it!=adj[i].end() && length!=0)
    			M[j][i]=1.00/length;
    		else if(length==0){
    			M[j][i]=constant;
    		}else{
    			M[j][i]=0.0;
    		}
    	}
    }

    //checking if the probability distribution was proper sigma(probability)=1
    try{
    	double sum;
	    for(int i=0;i<V;i++){
	    	sum=0.00;
	    	for(int j=0;j<V;j++){
	    		sum+=M[j][i];
	    	}
	    	if(abs(1-sum)>0.001 && sum!=0){
	    		cout<<"Total Error!\n";
	    	}
	    }
	}catch(exception &e){
		cout<<e.what()<<endl;
	}

    //initializing A
	A = new double*[V];
	for(int i = 0; i < V; ++i)
        A[i] = new double[V];
    memset(A,sizeof(A),0.00);

    //performing Aij = (b*Mij) + ((1-b)/N)
	for(int i=0;i<V;i++){
		for(int j=0;j<V;j++){
				A[i][j] = (beta*M[i][j]) + ((1-beta)*constant);
		}
	}

    //initializing R and previous
	R = new double[V];
	previous = new double[V];
	for(int i=0;i<V;i++){
		if(user[i]==1){
			R[i]=constant;
			previous[i] = R[i];
		}else{
			R[i]=0;
			previous[i] = R[i];
		}
	}
	
	clock_t t;
	t = clock();
	power_method();    //performing power method
	t = clock() - t;
	printf ("It took me %f seconds.\n",((float)t)/CLOCKS_PER_SEC);
	
	print_page_rank(); //writing the results to a file

    //deallocating allocated dynamic memory to avoid leaks
	free(A);
	free(M);
	free(R);
	free(previous);

    return 0;
}
