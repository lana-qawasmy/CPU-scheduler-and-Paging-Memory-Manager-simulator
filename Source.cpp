#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <sstream>
#include <ctime>
#include<cmath>


using namespace std;

pair<int, int>pairs;


/* This function to find the process and page for the frame.
   v vector of vector contains the frames of physical memory.
   k refers to the frame of physical memory.
  returns vector contains the process and the page in the frame.*/

vector<int> getProcessAndPage(vector<vector<int>>frame, int k) {
	vector<int> v; //auxiliary vector
	for (int i = 0; i < frame.size(); i++) {
		for (int j = 0; j < frame[i].size(); j++)
			if (frame[i][j] == k) {
				v.push_back(i);
				v.push_back(j);
				return v;
			}
	}
}
/* This function To find the number of spaces we need in the table of details
   param size refers to the size of the cell.
  param contain refers to the data inside the cell.
  returns  number of spaces we need in the first of cell.*/

int forDesign(int size, double contain) {
	vector <int> v;
	std::ostringstream os;
	os << contain;
	string str = os.str();
	int sum = size - str.size();
	return sum;
}


/*This function To get wating time for a process in Round Robin.
   v vector of integer contains all substitutions in Round Robin Alg.
   i refers to process number.
  returns Waiting time for the process.*/
double getWaitingTime(vector <vector<int>> v, int i) {
	vector<vector<int>>k;//auxiliary vector
	for (int j = 0; j < v.size(); j++)
		if (v[j][0] == i)
			k.push_back(v[j]);

	double sum = k[0][1];
	for (int i = k.size() - 1; i > 0; i--)
		sum += k[i][1] - k[i - 1][2];
	return sum;
}


/* This function To get the finish time for a process in Round Robin.
   param v vector of integer contains all substitutions in Round Robin Alg.
   i refers to process number.
   returns Finish time for the process.*/
double getFinishTime(vector <vector<int>> v, int i) {
	for (int j = v.size() - 1; j >= 0; j--)
		if (v[j][0] == i)
			return v[j][2];
}


/* This function To get minimum arrival time in all processes.
   parameter arr array that contains all information from the file about processes.
   returns Time of the first process arrives at the CPU.*/

int minmumValue(int arr[5][5]) {
	int min = arr[0][1];
	for (int i = 1; i < 5; i++)
		if (arr[i][1] < min)
			min = arr[i][1];
	return min;
}


/* This function To know if the process is visited or not
   param v vector of boolean contains if processes are visited or not.
   returns  true if all processes are visited and false otherwise.*/

bool ifNotAllProcessIsVisited(vector<bool>visited) {
	for (int i = 0; i < visited.size(); i++)
		if (visited[i] == 0)
			return true;
	return false;
}


/* This function To know if the vector v is sorted Ascending by Burst time for the processes.
	v vector of pair contains processes that we need to know it is sorted  by Burst time.
   returns  true if it is sorted.
   see sort() SJF() */

bool ifSort(vector<pair<int, int>> v) {
	for (int i = 0; i < v.size() - 1; i++)
		if (v[i].second > v[i + 1].second)
			return false;

	return true;
}


/* This function To sort vector v Ascending by Burst time for the processes.
  param v vector of pair contains processes that we need to sort it by Burst time by reference.
  returns  Nothing.
   see SJF()*/

void sort(vector<pair<int, int>>& v) {
	while (!ifSort(v)) {
		for (int i = 0; i < v.size() - 1; i++)
			if (v[i].second > v[i + 1].second)
				swap(v[i], v[i + 1]);
	}
}


/* This function To apply SJF algorithm .
   sjf vector of pair contains processes numbers and Burst time.
   param arr array that contains all information from the file about processes.
   param cs refer to context switch
  returns  execution time for all process in SJF Alg.*/

int SJF(vector <pair<int, int>>& sjf, int arr[5][5], int cs) {
	vector<pair<int, int>>v;//auxiliary vector
	for (int i = 0; i < 5; i++) {
		pairs.first = i;
		pairs.second = arr[i][2];
		v.push_back(pairs);
	}
	sort(v);
	vector<bool>visited(5, 0);
	int executionTime = minmumValue(arr);
	while (ifNotAllProcessIsVisited(visited))
	{
		for (int i = 0; i < 5; i++)
		{
			if (visited[v[i].first])
				continue;
			if (arr[v[i].first][1] <= executionTime) {
				visited[v[i].first] = 1;
				pairs.first = v[i].first;
				pairs.second = executionTime;
				sjf.push_back(pairs);
				executionTime += arr[v[i].first][2] + cs;
				i = -1;
			}
		}

	}
	return executionTime;

}

int Pro(vector <pair<int, int>>& pro, int arr[5][5], int cs) {
	vector<bool>visited(5, 0);
	vector<pair<int, int>>v;//auxiliary vector
	for (int i = 0; i < 5; i++) {
		pairs.first = i;
		pairs.second = arr[i][5];
		v.push_back(pairs);
	}
	sort(v);

	int executionTime = minmumValue(arr);
	while (ifNotAllProcessIsVisited(visited))
	{
		for (int i = 0; i < 5; i++)
		{
			if (visited[v[i].first])
				continue;
			if (arr[v[i].first][1] <= executionTime) {
				visited[v[i].first] = 1;
				pairs.first = v[i].first;
				pairs.second = executionTime;
				pro.push_back(pairs);
				executionTime += arr[v[i].first][2] + cs;
				i = -1;
			}
		}

	}
	return executionTime;

}

/* This function To claculate the CPU utilization.
   param executionTime refers to execution time for the alg that we need to calculate the CPU utilization for it.
   param totalTime refers to the total time spent on the alg.
   returns  CPU utilization.*/

double cpuUtilization(double executionTime, double totalTime) {
	return(executionTime / totalTime) * 100;
}



/* This function To know if the vector v is sorted Ascending by number of processes using in the table.
   param v vector of pair contains processes that we need to know it is sorted by number of processes.
   returns  true if it is sorted.
   see sortByFirst() printDetails() */

bool ifSortByFirst(vector<pair<int, int>> v) {
	for (int i = 0; i < v.size() - 1; i++)
		if (v[i].first > v[i + 1].first)
			return false;

	return true;
}


/* This function To sort vector v Ascending by number of processes.
   param v vector of pair contains processes that we need to sort it by number of process.
   returns  Nothing.
   see printDetails()*/

void sortByFirst(vector<pair<int, int>>& v) {
	while (!ifSortByFirst(v)) {
		for (int i = 0; i < v.size() - 1; i++)
			if (v[i].first > v[i + 1].first)
				swap(v[i], v[i + 1]);
	}
}


/* This function To print the tabel contains the details of processes.
   param v vector of pair contains processes that we need to print the detailes table for it.
   param arr array that contains all information from the file about processes.
	returns  Nothing.*/

void printDetails(vector <pair<int, int>> v, int arr[5][5]) {
	int f = 13, w = 14, t = 17;
	sortByFirst(v);
	cout << "----------------------------------------------------------" << endl;
	cout << "| process | Finish time | Waiting time | Turnaround time |" << endl;
	cout << "----------------------------------------------------------" << endl;
	/*
	sumW : sum of waiting time for all processes.
	sumT:sum of Turnaround time for all processes.
	sumF :sum of finish time for all processes.
	*/
	double sumW = 0, sumT = 0, sumF = 0;
	for (int i = 0; i < v.size(); i++)
	{
		double finishTime = v[i].second + arr[i][2];
		sumF += finishTime;
		cout << "|    p" << i << "   |";
		int x = forDesign(13, finishTime);
		for (int j = 0; j < x / 2; j++)
		{
			cout << " ";
		}
		cout << finishTime;
		for (int i = 0; i < x - x / 2; i++)
		{
			cout << " ";
		}
		cout << "|";
		double waitingTime = v[i].second - arr[i][1];
		sumW += waitingTime;
		x = forDesign(14, waitingTime);
		for (int j = 0; j < x / 2; j++)
		{
			cout << " ";
		}
		cout << waitingTime;
		for (int i = 0; i < x - x / 2; i++)
		{
			cout << " ";
		}
		cout << "|";

		double turnaroundTime = waitingTime + arr[i][2];
		sumT += turnaroundTime;
		x = forDesign(17, turnaroundTime);
		for (int j = 0; j < x / 2; j++)
		{
			cout << " ";
		}
		cout << turnaroundTime;
		for (int i = 0; i < x - x / 2; i++)
		{
			cout << " ";
		}
		cout << "|" << endl;;
		cout << "----------------------------------------------------------" << endl << endl;
	}
	cout << "The Average Finish Time is : " << sumF / 5 << endl;
	cout << "The Average Waiting Time is : " << sumW / 5 << endl;
	cout << "The Average Turnaround Time is : " << sumT / 5 << endl;





}


/* This function To print Gantt Chart for the algorithms .
   param name refers to the namber of algorithm
   param v vector of pair contains processes that we need to print the Gantt Chart for it.
   param executionTime refers to execution time for the alg .
   param arr array that contains all information from the file about processes.
   param cs refer to context switch
   returns  Nothing.*/

void print(string name, vector <pair<int, int>> v, int executionTime, int arr[5][5], int cs) {
	for (int i = 1; i < v.size(); i++)
		v[i].second -= cs;
	cout << "Gantt Chart for " << name << endl;
	for (int i = 0; i < v.size() * 7.3 + 1; i++)
		cout << '-';
	cout << endl;
	cout << "| p" << v[0].first << " |cs";
	for (int i = 1; i < v.size() - 1; i++)
		cout << "| p" << v[i].first << " |cs";
	cout << "| p" << v[v.size() - 1].first;
	cout << " |" << endl;
	for (int i = 0; i < v.size() * 7.3 + 1; i++)
		cout << '-';
	cout << endl;
	cout << v[0].second << "   ";
	for (int i = 1; i < v.size(); i++)
		cout << v[i].second << "  " << v[i].second + cs << "   ";
	cout << executionTime - cs << endl << endl;


}


/* This function To apply FCFS algorithm .
   param fcfs vector of pair contains processes numbers and Burst time.
   param arr array that contains all information from the file about processes.
   param cs refer to context switch
   returns  execution time for all process in FCFS Alg.*/

int FCFS(vector <pair<int, int>>& fcfs, int arr[5][5], int cs) {
	vector<bool>visited(5, 0);
	vector<pair<int, int> >v;
	for (int i = 0; i < 5; i++) {
		pairs.first = i;
		pairs.second = arr[i][1];
		v.push_back(pairs);
	}
	sort(v);
	int executionTime = minmumValue(arr);
	while (ifNotAllProcessIsVisited(visited))
	{
		for (int i = 0; i < 5; i++)
		{
			if (visited[v[i].first])
				continue;
			if (arr[v[i].first][1] <= executionTime) {
				visited[v[i].first] = 1;
				pairs.first = v[i].first;
				pairs.second = executionTime;
				fcfs.push_back(pairs);
				executionTime += arr[v[i].first][2] + cs;
				i = -1;
			}
		}

	}
	return executionTime;

}

/* This function To know if the process in ready queue or not.
   param ready vector contains all processes in ready queue.
   param k refer to the processe.
   returns  boolean if the process in ready queue or not.*/

bool notInReadyQueue(vector<int>ready, int k) {
	for (int i = 0; i < ready.size(); i++)
		if (ready[i] == k)
			return false;

	return true;
}

/* This function To apply Round Robin algorithm .
  param rr vector of vector contains processes numbers and Burst time.
  param arr array that contains all information from the file about processes.
  param Q Round Robin Quantum
  param cs refer to context switch.
  returns  execution time for all process in RR Alg.*/

int RR(vector <vector<int>>& rr, int arr[5][5], int Q, int cs) {
	vector<int>v(5);//auxiliary vector
	vector<int>c;//auxiliary vector
	vector < pair<int, int> >a;
	vector<int>readyQueue;

	for (int i = 0; i < 5; i++) {
		pairs.first = i;
		pairs.second = arr[i][1];
		a.push_back(pairs);
	}
	sort(a);
	readyQueue.push_back(a[0].first);

	for (int i = 0; i < 5; i++)
		v[i] = arr[i][2];

	vector<bool>visited(5, 0);
	int numberOfCS = 0;
	int executionTime = minmumValue(arr);
	while (!readyQueue.empty())
	{
		numberOfCS++;
		if (v[readyQueue[0]] > Q) {
			c.clear();
			c.push_back(readyQueue[0]);
			c.push_back(executionTime);
			executionTime += Q + cs;
			v[readyQueue[0]] -= Q;
			c.push_back(executionTime);
			rr.push_back(c);

			for (int i = 0; i < a.size(); i++)
			{
				if (a[i].second <= executionTime && !visited[a[i].first] && a[i].first != readyQueue[0] && notInReadyQueue(readyQueue, a[i].first))
					readyQueue.push_back(a[i].first);
			}
			readyQueue.push_back(readyQueue[0]);
			readyQueue.erase(readyQueue.begin());
		}
		else {
			c.clear();
			c.push_back(readyQueue[0]);
			c.push_back(executionTime);
			executionTime += v[readyQueue[0]] + cs;
			visited[readyQueue[0]] = 1;
			c.push_back(executionTime);
			rr.push_back(c);

			for (int i = 0; i < a.size(); i++)
			{
				if (a[i].second <= executionTime && !visited[a[i].first] && a[i].first != readyQueue[0] && notInReadyQueue(readyQueue, a[i].first))
					readyQueue.push_back(a[i].first);
			}
			readyQueue.erase(readyQueue.begin());

		}

	}

	return executionTime;

}

/* This function To print the tabel contains the details of processes for RR algorithm .
  param v vector of vector contains processes that we need to print the detailes table for it.
  param arr array that contains all information from the file about processes.
  param cs refer to context switch.
  returns  Nothing.*/

void printDetailsRR(vector <vector<int>> v, int arr[5][5], int cs) {
	int f = 13, w = 14, t = 17;

	for (int i = 0; i < v.size(); i++)
		v[i][2] -= cs;

	cout << "----------------------------------------------------------" << endl;
	cout << "| process | Finish time | Waiting time | Turnaround time |" << endl;
	cout << "----------------------------------------------------------" << endl;
	double sumW = 0, sumT = 0, sumF = 0;
	for (int i = 0; i < 5; i++)
	{
		vector < pair<int, double>>f;
		double finishTime = getFinishTime(v, i);
		sumF += finishTime;
		cout << "|    p" << i << "   |";
		int x = forDesign(13, finishTime);
		for (int j = 0; j < x / 2; j++)
		{
			cout << " ";
		}
		cout << finishTime;
		for (int i = 0; i < x - x / 2; i++)
		{
			cout << " ";
		}
		cout << "|";

		double waitingTime = getWaitingTime(v, i) - arr[i][1];
		sumW += waitingTime;
		x = forDesign(14, waitingTime);
		for (int j = 0; j < x / 2; j++)
		{
			cout << " ";
		}
		cout << waitingTime;
		for (int i = 0; i < x - x / 2; i++)
		{
			cout << " ";
		}
		cout << "|";

		double turnaroundTime = waitingTime + arr[i][2];
		sumT += turnaroundTime;
		x = forDesign(17, turnaroundTime);
		for (int j = 0; j < x / 2; j++)
		{
			cout << " ";
		}
		cout << turnaroundTime;
		for (int i = 0; i < x - x / 2; i++)
		{
			cout << " ";
		}
		cout << "|" << endl;;
		cout << "----------------------------------------------------------" << endl;
	}
	cout << "The Average Finish Time is : " << sumF / 5 << endl;
	cout << "The Average Waiting Time is : " << sumW / 5 << endl;
	cout << "The Average Turnaround Time is : " << sumT / 5 << endl;





}

/*In this project,there is two parts, The first is a simulator for four algorithms that are first-come,
  first-served(FCFS), Priority , Shortest Job First (SJF) and Round Robin, we will represent the grant chart,
  and calculate the finish time, waiting time and around time for each process in all algorithm,
  & the second is a simulator for the paging in the main memory, we will represent the page table for each process,
  memory map and find any physical address by logical address.*/


int main() {

	ifstream file;
	//contains the processes details
	int arr[5][5];
	//using when chooce the random nubmers to chooce different numbers 
	srand((int)time(0));
	//open files
	file.open("process.txt");

	if (!file) {
		cout << "The file doesn't exist !!!" << endl;
		return 1;
	}
	int physicalMemorySize, pageSize, roundRobinQuantum, contextSwitch;
	file >> physicalMemorySize;
	file >> pageSize;
	file >> roundRobinQuantum;
	file >> contextSwitch;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			file >> arr[i][j];
	file.close();


	cout << endl;
	cout << "************************* welcome to our project  ************************** " << endl << endl;
	cout << "This project done By : \n Lana Qawasmy \n                                  " << endl << endl;
	cout << "************************* welcome to Part one  ************************** " << endl << endl;

	//-----------------------------------------------------------------

	cout << "1. FCFS : \n\n";

	vector<pair<int, int>>fcfs; //to keep the fcfs data 
	int executionTime = FCFS(fcfs, arr, contextSwitch);
	print("FCFS", fcfs, executionTime, arr, contextSwitch);
	printDetails(fcfs, arr);
	double totalTime = executionTime - contextSwitch;
	executionTime = totalTime - (fcfs.size() - 1) * contextSwitch;
	cout << "Total time : " << totalTime << endl;
	cout << "The CPU Utilization :" << cpuUtilization(executionTime, totalTime) << "%" << endl << endl << endl;

	//-----------------------------------------------------------------

	cout << "2. Priority : \n\n";

	vector<pair<int, int>>pro;
	int executionTime1 = Pro(pro, arr, contextSwitch);
	print("pro", pro, executionTime1, arr, contextSwitch);
	printDetails(pro, arr);
	double totalTime1 = executionTime1 - contextSwitch;
	executionTime1 = totalTime1 - (pro.size() - 1) * contextSwitch;
	cout << "Total time : " << totalTime1 << endl;
	cout << "The CPU Utilization :" << cpuUtilization(executionTime1, totalTime1) << "%" << endl << endl << endl;

	//-----------------------------------------------------------------

	cout << "3. SJF :\n\n";

	vector<pair<int, int>>sjf;//to keep the sjf data 
	int executionTime2 = SJF(sjf, arr, contextSwitch);
	print("SJF", sjf, executionTime2, arr, contextSwitch);
	printDetails(sjf, arr);
	double totalTime2 = executionTime2 - contextSwitch;
	executionTime2 = totalTime2 - (sjf.size() - 1) * contextSwitch;
	cout << "Total time : " << totalTime2 << endl;
	cout << "The CPU Utilization :" << cpuUtilization(executionTime2, totalTime2) << "%" << endl << endl << endl;

	//-------------------------------------------------------------------

	cout << "4. Round Robin :\n\n";

	vector<vector<int>>rr;//to keep the RR data 
	vector<pair<int, int>>rrp;//to keep RR  data 
	int executionTime3 = RR(rr, arr, roundRobinQuantum, contextSwitch);
	for (int i = 0; i < rr.size(); i++)
	{
		pairs.first = rr[i][0];
		pairs.second = rr[i][1];
		rrp.push_back(pairs);
	}
	print("RR", rrp, executionTime3, arr, contextSwitch);
	printDetailsRR(rr, arr, contextSwitch);
	double totalTime3 = executionTime3 - contextSwitch;
	executionTime3 = totalTime3 - (rr.size() - 1) * contextSwitch;
	cout << "Total time : " << totalTime3 << endl;
	cout << "The CPU Utilization :" << cpuUtilization(executionTime3, totalTime3) << "%" << endl << endl << endl;
	//--------------------------------------------------------------------------------------------------------------------------------------

	cout << " *********************** welcome to Part 2  *********************** " << endl << endl;

	long int sum = 0;
	int numberOfPages = physicalMemorySize / pageSize;
	vector<bool>visited(numberOfPages, 0);

	//contains the processes and how many pages need
	vector< vector<int>> v;

	//the frame for each process
	vector< vector<int>> frame;

	for (int i = 0; i < 5; i++)
	{
		int x = ceil(arr[i][3] * 1.0 / pageSize);
		vector<int>c;
		if (x <= numberOfPages) {
			for (int i = 0; i < x; i++) {
				c.push_back(i);
			}
			v.push_back(c);
		}
		else {
			c.push_back(-99);
			v.push_back(c);
		}
	}
	int counter = numberOfPages;
	for (int i = 0; i < v.size(); i++)
	{
		vector<int>c;
		if (v[i][0] == -99)
			c.push_back(-99);
		else if (v[i].size() > counter)
			c.push_back(-99);
		else {
			for (int j = 0; j < v[i].size(); j++)
			{

				bool is = 1;
				while (is)
				{
					int y = rand() % numberOfPages;
					if (!visited[y]) {
						visited[y] = 1;
						c.push_back(y);
						is = 0;
					}
				}
			}
			counter -= v[i].size();
		}
		frame.push_back(c);
	}


	cout << "1. the page table of each processes : \n\n";
	for (int i = 0; i < v.size(); i++)
	{
		//It is wrong If the process is larger than memory size
		if (v[i][0] == -99) {
			cout << "Process number " << i << " is bigger than physical memory !" << endl;
			continue;
		}
		//if the main memory is full, the other process that can't find a space is waiting
		if (frame[i][0] == -99) {
			cout << "Process number " << i << " is waiting !" << endl;
			continue;
		}

		/* every process has the table based on the size, it contains the pages and frames, pages start from 0, and the frame is a random location in
			the memory for each page	 */

		cout << endl << "Page Table for process number " << i << endl;
		cout << "--------------------" << endl;
		for (int j = 0; j < v[i].size(); j++) {
			cout << "| page " << v[i][j] << " | " << "frame " << frame[i][j] << " |" << endl;
			cout << "--------------------" << endl;
		}
		cout << endl << endl;

	}


	//------------------------------------------------------------------
	cout << "2.The memory map of the physical memory : \n\n";

	cout << "The memory map of the physical memory " << endl;
	cout << "    ---------------------------" << endl;
	for (int k = 0; k < numberOfPages; k++)
	{
		if (!visited[k]) {
			cout << k << "   |                         |" << endl;
		}
		else {
			vector<int>processAndPage;
			processAndPage = getProcessAndPage(frame, k);
			int process = v[processAndPage[0]][0];
			int page = v[processAndPage[0]][processAndPage[1]];
			cout << k << "   |   page " << page << " from process " << processAndPage[0] << " |" << endl;
		}
		cout << "    ---------------------------" << endl << endl;

	}
	//-------------------------------------------------------------------
	cout << "3. find physical address by your logical address :\n\n";

	long int logicalAddress, page, process;
	cout << "Enter Your Logical Address To find physical address : ";
	cin >> logicalAddress;
	cout << "Enter the process number : ";
	cin >> process;
	cout << "Enter the page number : ";
	cin >> page;

	if (process >= v.size()) {
		cout << "The process doesn't exist" << endl;
	}
	else if (page >= v[process].size()) {
		cout << "The page doesn't exist" << endl;
	}
	else if (v[process][0] == -99)
		cout << "Process is begger than Physical Memory size!!!" << endl;
	else if (frame[process][0] == -99)
		cout << "The process is waiting!!!" << endl;


	else {
		int physicalAddress = frame[process][page] * pageSize + logicalAddress % pageSize;
		if (physicalAddress > numberOfPages * pageSize)
			cout << "The Logical Address is wrong " << endl;
		else {
			cout << endl;
			cout << "The Logical Address is :" << logicalAddress << endl;
			cout << "Process number is : " << process << endl;
			cout << "Page number is : " << page << endl;
			cout << endl;
			cout << "Frame number is :" << frame[process][page] << endl;
			cout << "The Displacement is : " << logicalAddress % pageSize << endl;
			cout << "The Physical Address is : " << physicalAddress << endl;
		}
	}

	system("pause");
	return 0;
}