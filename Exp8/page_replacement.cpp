
#include<iostream>
#include<vector>
#include<queue>
#include<ctime>
struct page_slot{
	int page;
	int age;//aging counter
	page_slot(int page)
	:page(page),age(0){}
};

int page_faults_FIFO(int *pages, int n, int capacity){
	int fault_num = 0;
	std::queue<int> fifo_queue;
	std::vector<int> to_access_element_in_queue;
	for(int i = 0; i<n;i++){
		//std::cout<<pages[i]<<" - ";
		bool page_fault = true;
		for(size_t j = 0; j<fifo_queue.size(); j++){
			if(pages[i] == to_access_element_in_queue[j]){
				page_fault = false;
				//std::cout<<"page hit\n";
				break;
			}				
		}
		if(page_fault){
			//std::cout<<"page fault\n";
			fault_num++;
			if((int)fifo_queue.size()<capacity){
				fifo_queue.push(pages[i]);
				to_access_element_in_queue.push_back(pages[i]);
			}else{
				fifo_queue.push(pages[i]);
				int p = fifo_queue.front();
				fifo_queue.pop();
				for(size_t j = 0; j<fifo_queue.size(); j++)
					if(p == to_access_element_in_queue[j])
						to_access_element_in_queue[j] = pages[i];
			}
		}
	}
	return fault_num;
}
int page_faults_LRU(int *pages, int n, int capacity){
	int fault_num = 0;
	std::vector<page_slot> page_holder; 
	for(int i = 0; i < n; i++){
		//std::cout<<pages[i]<<" - ";
		if((int)page_holder.size()<capacity){
			bool page_fault = true;
			for(size_t j = 0; j<page_holder.size();j++){
				if(pages[i]==page_holder[j].page){
					page_fault = false;
					page_holder[j].age = 0;
					//std::cout<<"page hit\n";
					break;
				}
			}
			if(page_fault){
				page_holder.push_back(page_slot(pages[i]));
				fault_num++;
				//std::cout<<"page fault\n";
			}
		}else{
			bool page_fault = true;
			int oldest = 0, oldest_index = 0;
			for(size_t j = 0; j<page_holder.size();j++){
				if(pages[i]==page_holder[j].page){
					page_fault = false;
					page_holder[j].age = 0;
					//std::cout<<"page hit\n";
					break;
				}
				if(oldest<page_holder[j].age){
					oldest = page_holder[j].age;
					oldest_index = j;
				}
			}
			if(page_fault){//this is where page fault occurs. 
				//replace the current page with the oldest page
				page_holder[oldest_index].page = pages[i];
				page_holder[oldest_index].age = 0;
				fault_num++;			
				//std::cout<<"page fault\n";
			}
		}

		//aging all the pages inside the page holder
		for(size_t j = 0; j<page_holder.size();j++)
			page_holder[j].age++;
	}
	return fault_num;
}
int main(){
	std::cout<<"Hello FIFO and LRU\n";

	int n = 20;
	int pages[20];

	//generate random pages reference
	srand(time(0));
	for(int i = 0; i<n; i++){
		pages[i] = (rand()%10000)%8; //0-8
		std::cout<<pages[i]<<", ";
	}
	int capacity = 2;
	for(;capacity<10; capacity++)
	std::cout<<"\nFIFO: "
		<<page_faults_FIFO(pages,n,capacity)
		<<"\nLRU: "
		<<page_faults_LRU(pages,n,capacity)<<"\n";

	return 0;
}