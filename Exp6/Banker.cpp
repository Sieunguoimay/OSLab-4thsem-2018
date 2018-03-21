
//Program to emulate banker's algorithm
//input is 2 matrix of size mxn namely: Allocated and Max Request
//calculate the Need matrix and then run the algorithm 
//to find out the safe sequence of processes

//there are m processes and n resource types
#include<stdio.h>
#include<iostream>
#include<vector>
struct Matrix{
	Matrix(std::vector< std::vector<int> >container):container(container){
		printf("Created Matrix (%ix%i)\n",GetRow(),GetColumn());
	}
	Matrix(){}
	std::vector< std::vector<int> >container;
	size_t GetRow()const{return container.size();}
	size_t GetColumn()const{return container[0].size();}
	int GetElement(int i, int j)const{
		return container[i][j];
	}
	void EnterInput(int row, int col){
		int itemp;
		for(int i = 0; i<row; i++){
			std::vector<int>vtemp;
			for(int j =0; j<col;j++){
				printf("[%i,%i]=",i,j);
				std::cin>>itemp;
				vtemp.push_back(itemp);
			}	
			container.push_back(vtemp);
		}
	}
	void Display(){
		for(size_t i = 0; i<container.size();i++){
			for(size_t j = 0; j<container[i].size();j++)
				printf("%i ",container	[i][j]);
			printf("\n");
		}
	}
	std::vector<int>GetRowElement(int i){
		return container[i];
	}
	friend Matrix operator-(const Matrix&a, const Matrix&b);//subtract two same size matrix
};

Matrix operator-(const Matrix&a,const Matrix&b){
	std::vector< std::vector<int> >container;
	int itemp;
	for(size_t i = 0; i<a.GetRow();i++){
		std::vector<int>vtemp;
		for(size_t j = 0; j<a.GetColumn();j++){
			itemp = a.GetElement(i,j) - b.GetElement(i,j);
			vtemp.push_back(itemp);
		}
		container.push_back(vtemp);
	}
	return Matrix(container);
}
bool compare(std::vector<int>a, std::vector<int>b){
	for(size_t i = 0; i<a.size(); i++)
		if(a[i]>b[i])return false;
	return true;
}
void add(std::vector<int>&a,std::vector<int>b){//add to a
	for(size_t i = 0; i<a.size(); i++)
		a[i]+=b[i];
}
void RunBankerAlgorithm(Matrix&Allocated,Matrix&MaxRequest, std::vector<int>Available){
	int process_number = Allocated.GetRow();
	std::vector<bool> Finish(Allocated.GetRow());
	for(int i = 0; i<process_number;i++)
		Finish.push_back(false);
	Matrix Need = MaxRequest - Allocated;
	Need.Display();
	bool running = true;
	int count = 0;
	while(running){
		running = false;
		for(int i = 0; i<process_number;i++){
			if(!Finish[i]){
				if(compare(Need.GetRowElement(i),Available)){//compare 2 vectors
					add(Available,Allocated.GetRowElement(i));//add 2 vectors
					Finish[i]=true;
					std::cout<<"P"<<i<<" ";
					//if no Need's vector is select in one complete loop
					running = true;
					count++;
				}
			}
		}
		if(count == (int)Finish.size())
			break;
	}
	printf("\n");
	for(int i = 0; i<process_number;i++)
		if(!Finish[i]){
			std::cout<<"Not A Safe State\n";
			return;
		}
	std::cout<<"Safe State\n";
}
int main(){
	printf("Banker's Algorithm\n");
	std::cout<<"Enter allocated matrix:\n";
	std::cout<<"Enter size mxn: ";
	int row, col;
	std::cin>>row>>col;
	
	Matrix Allocated;
	Allocated.EnterInput(row, col);
	Allocated.Display();
	
	Matrix MaxRequest;
	MaxRequest.EnterInput(row,col);
	MaxRequest.Display();
	
	printf("Enter Available Matrix\n");
	std::vector<int> Available;	
	int t;
	for(int i = 0; i<col;i++){
		std::cin>>t;
		Available.push_back(t);
	}
	
	
	RunBankerAlgorithm(Allocated, MaxRequest, Available);


	return 0;
}