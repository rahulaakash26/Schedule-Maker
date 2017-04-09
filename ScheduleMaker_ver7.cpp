/* Schedule Maker version 7 */ 

#include<iostream>
#include<windows.h>
using namespace std;

//class definition : Node prototype
class Node {
	public:
		int date, month, year, hour, min;
		string task, group;
		Node* link;
};

//class defintion to carry all the operations on Node
class LinkedList {
	private:
		Node *head;
	public:
		LinkedList() : head(NULL) {}		//initializing the head to NULL
		void createNode();					//function declaration to create a node
		void displayNode();					//function declaration to display nodes
		Node* getNode();					//this function will insert values into node and return node
		void taskOnDate();					//this function will show all the tasks on a specific date
		void taskInGroup();					//function to show task based on groups
		void appendNode(Node*);				//this function is used inside the createNode() to append nodes in list
		void deleteNode();					//function declaration to delete a Node
		void updateNode();					//function to update a task
        	void upcoming();                    //function for upcoming Task
		void pickGroup(string);			//function to show specific group
		bool dateValidator(Node&);			//function declaratioin to check if the date entered is valid or not
		bool timeValidator(Node&);			//function declaratioin to check if the time entered is valid or not
		~LinkedList();						//destructor to deallocate memory and prevent dangling pointers
};

int main(){
	LinkedList l1;
	int choice, viewChoice, groupChoice;
	while(1){
           system("cls");
		//Main Menu
		cout<<endl;
		cout<<"\t\t_______________________________________________\n\n";
		cout<<"\t\t\t\t SCHEDULE MAKER \n";
		cout<<"\t\t_______________________________________________\n";
		cout<<"\n \t\t\t 1. Create a New Task \n \t\t\t 2. View Tasks \n  \t\t\t 3. Update Task \n\t\t\t 4. Upcoming Tasks \n \t\t\t 5. Mark As Complete \n \t\t\t 6. Exit \n";
		cout<<"\t\t____________________________________________\n\n";
		cout<<"\t\tEnter your Choice : ";
		cin>>choice;
		system("cls");

		//switch to use different cases
		switch(choice){
			case 1:
				l1.createNode();
 				break;
			case 2:

				//view menu
				system("cls");
				cout<<"\t\t_______________________________________________\n\n";
				cout<<"\t\t\t\t VIEW TASKS\n";
				cout<<"\t\t_______________________________________________\n\n";
				cout<<"\n\t\t 1. View all Tasks \n\t\t 2. View Tasks Based on Groups \n\t\t 3. View Tasks Based on Dates\n\t\t 4. Go Back\n";
				cout<<endl<<"\t\tEnter Your Choice : ";
				cin >> viewChoice;
				switch(viewChoice){
					case 1:
						l1.displayNode();
						break;
					case 2:

						//group menu
						system("cls");
						int choice;
						cout<<"\t\t_______________________________________________\n\n";
						cout<<"\t\t\t TASKS BASED ON GROUPS "<<endl;
						cout<<"\t\t_______________________________________________\n\n\n";
						cout<<endl<<"\t\t1.Personal\n\t\t2.Family\n\t\t3.Study\n\t\t4.Travel\n\t\t5.General"<<endl;
						cout<<endl<<"\t\tEnter the group number : ";
						cin>>groupChoice;
						switch(groupChoice){
							case 1:
								l1.pickGroup("Personal");
								break;
							case 2:
								l1.pickGroup("Family");
								break;
							case 3:
								l1.pickGroup("Study");
								break;
							case 4:
								l1.pickGroup("Travel");
								break;
							case 5:
								l1.pickGroup("General");
								break;
							default:
								cout<<"\t\tInvalid Choice";
								break;
						}
						break;

					//view task menu cases
					case 3:
						l1.taskOnDate();
						break;
					case 4:
						system("cls");
						break;
					default:
						cout<<endl<<"\t\tInvalid Choice";
				}
				break;

			//main menu switch cases
			case 3:
				l1.updateNode();
				break;
            case 4:
				l1.upcoming();
				break;
			case 5:
				l1.deleteNode();
				break;
			case 6:
				exit(0);
			default:
				cout<<"\n \t\tInvalid Choice. Choose Again\n";
				break;
		}
	}
}

//Destrcture of class Linked List to delete pointers
LinkedList :: ~LinkedList(){
	Node *temp;
	while (head != NULL){
		temp = head;
		head = head->link;
		delete temp;
	}
}

//createNode function definition
void LinkedList::createNode(){
	char choice;
	Node *newNode;
	cout<<"\t\t_______________________________________________\n\n";
	cout<<"\t\t\t\tCREATE A NEW TASK\n";
	cout<<"\t\t_______________________________________________\n\n\n";
	while(1){
		newNode = getNode();
		appendNode(newNode);
		cout<<"\t\tSchedule has been saved"<<endl<<endl;
		cout<<"\t\tDo You want to insert new task (y/n) : ";
		cin>>choice;
		if(choice == 'n' or choice == 'N'){
			system("cls");
			break;
		}
	}
}

//this function returns a node
Node* LinkedList::getNode(){
	int choice;
	Node *newNode;
	newNode = new Node;
	cout<<"\n\t\t\t\tGroups for the task";
	cout<<endl<<"\t\t 1.Personal\n\t\t 2.Family\n\t\t 3.Study\n\t\t 4.Travel\n\t\t 5.General"<<endl;
	cout<<endl<<"\t\tEnter the group number : ";
	cin>>choice;
	switch(choice){
		case 1:
			newNode->group = "Personal";
			break;
		case 2:
			newNode->group = "Family";
			break;
		case 3:
			newNode->group = "Study";
			break;
		case 4:
			newNode->group = "Travel";
			break;
		case 5:
			newNode->group = "General";
			break;
		default:
			newNode->group = "General";
			break;
	}
	cout<<"\t\tEnter Task Description : ";
	cin.ignore();
	getline(cin, newNode->task);
	while(1){
		cout<<"\t\tEnter Date (DD MM YYYY) : ";
		cin>>newNode->date>>newNode->month>>newNode->year;
		bool checkDate = dateValidator(*newNode);
		if(checkDate){
			cout<<"\t\tEnter Time (24 hour format) : ";
			cin>>newNode->hour>>newNode->min;
			bool checkTime = timeValidator(*newNode);
			if(checkTime){
				newNode->link = NULL;
				return (newNode);
				break;
			}else{
				MessageBox(0,"YOU ENTERED AN INVALID TIME","TIME WARNING!",MB_ICONSTOP);
			}
		}else{
			MessageBox(0,"YOU ENTERED AN INVALID DATE","DATE WARNING!",MB_ICONSTOP);
		}
	}
}

//this function appends a node in a sorted manner (ascending order)
void LinkedList::appendNode(Node* newNode){
	Node *ptr = head;
	if (head == NULL){
		head = newNode;
	}else{
		//First compare years if newNode year is less than 1st node if yes, interchange them
		if(ptr->year > newNode->year){
			newNode->link = head;
			head = newNode;
		}
		//if years are same then compare months
		else if(ptr->year == newNode->year){

			//compare if newNode month is less than the 1st node in list if yes, interchange them
			if(ptr->month > newNode->month){
				newNode->link = head;
				head = newNode;
			}
			//if months of both are equal compare dates
			else if(ptr->month == newNode->month){

				//compare if date of newNode is smaller than the 1st node. If yes, interchange them
				if(ptr->date > newNode->date){
					newNode->link = head;
					head = newNode;
				}
				//if dates are same then, check time
				else if(ptr->date == newNode->date){

					//compare the hour
					if(ptr->hour > newNode->hour){
						newNode->link = head;
						head = newNode;
					}
					//if hour is same check time
					else if(ptr->hour == newNode->hour){

						//compare the minute
						if(ptr->min > newNode->min){
							newNode->link = head;
							head = newNode;
						}
						else if(ptr->min == newNode->min){
							newNode->link = head;
							head = newNode;
						}
						//if minute in newNode is greater then traverse and place it accordingly
						else{
							ptr = head;

							//traverse the link till the next node is greater than the newNode
							while(ptr->link != NULL){
								if(ptr->link->year > newNode->year)
									break;
								else if(ptr->link->year == newNode->year && ptr->link->month > newNode->month)
									break;
								else if(ptr->link->year == newNode->year && ptr->link->month > newNode->month && ptr->link->date > newNode->date)
									break;
								else if(ptr->link->year==newNode->year&&ptr->link->month>newNode->month&&ptr->link->date==newNode->date&&ptr->link->hour>newNode->hour)
									break;
								else if(ptr->link->year==newNode->year&&ptr->link->month>newNode->month&&ptr->link->date==newNode->date&&ptr->link->hour==newNode->hour&&ptr->link->min>newNode->min)
									break;
								ptr = ptr->link;
							}
							newNode->link = ptr->link;
							ptr->link = newNode;
						}
					}

					//if hour in newNode is greater then traverse and place it accordingly
					else{
						ptr = head;
						//traverse the link till the next node is greater than the newNode
						while(ptr->link != NULL){
							if(ptr->link->year > newNode->year)
								break;
							else if(ptr->link->year == newNode->year && ptr->link->month > newNode->month)
								break;
							else if(ptr->link->year == newNode->year && ptr->link->month > newNode->month && ptr->link->date > newNode->date)
								break;
							else if(ptr->link->year==newNode->year&&ptr->link->month>newNode->month&&ptr->link->date==newNode->date&&ptr->link->hour>newNode->hour)
								break;
							else if(ptr->link->year==newNode->year&&ptr->link->month>newNode->month&&ptr->link->date==newNode->date&&ptr->link->hour==newNode->hour&&ptr->link->min>newNode->min)
								break;
							ptr = ptr->link;
						}
						newNode->link = ptr->link;
						ptr->link = newNode;
					}
				}
				//else if newNode date is greater
				else{
					ptr = head;
					//traverse the link till the next node is greater than the newNode
					while(ptr->link != NULL){
						if(ptr->link->year > newNode->year)
							break;
						else if(ptr->link->year == newNode->year && ptr->link->month > newNode->month)
							break;
						else if(ptr->link->year == newNode->year && ptr->link->month > newNode->month && ptr->link->date > newNode->date)
							break;
						ptr = ptr->link;
					}
					newNode->link = ptr->link;
					ptr->link = newNode;
				}
			}
			//else if the month of newNode is greater
			else{
				ptr = head;
				//traverse the link till the next node is greater than the newNode
				while(ptr->link != NULL){
					if(ptr->link->year > newNode->year)
						break;
					else if(ptr->link->year == newNode->year && ptr->link->month > newNode->month)
						break;
					else if(ptr->link->year == newNode->year && ptr->link->month > newNode->month && ptr->link->date > newNode->date)
						break;
					ptr = ptr->link;
				}
				newNode->link = ptr->link;
				ptr->link = newNode;
			}
		}
		//else if the year of year of newNode is greater
		else{
			ptr = head;
			//traverse the link till the next node is greater than the newNode
			while(ptr->link != NULL){
				if(ptr->link->year > newNode->year)
					break;
				else if(ptr->link->year == newNode->year && ptr->link->month > newNode->month)
					break;
				else if(ptr->link->year == newNode->year && ptr->link->month > newNode->month && ptr->link->date > newNode->date)
					break;
				ptr = ptr->link;
			}
			newNode->link = ptr->link;
			ptr->link = newNode;
		}
	}
}

//this function displays all the nodes in the linked list
void LinkedList::displayNode(){
	system("cls");
	Node *temp = head;
	int count = 1;
	cout<<"\t\t_______________________________________________\n\n";
	cout<<"\t\t\t\tLIST OF ALL THE TASK\n";
	cout<<"\t\t_______________________________________________\n\n\n";
	if(temp == NULL){
		cout<<"\t\tThe List is Empty";
	}else{
		while(temp != NULL){
			cout<<"\n\n\t\tTask "<< count << " Description : "<<temp->task;
			cout<<"\n\t\tTask Due Date : "<<temp->date<<"-"<<temp->month<<"-"<<temp->year<<" at "<<temp->hour<<":"<<temp->min;
			cout<<"\n\t\tGroup Associated : "<<temp->group;
			temp = temp->link;
			count++;
		}
	}
	cout<<endl;
	system("pause");
}

//upcoming() function definition
void LinkedList::upcoming(){
    Node *temp;
    temp=head;
    cout<<"\t\t_______________________________________________\n\n";
    cout<<"\n \t\t\t UPCOMING TASKS \n";
    cout<<"\t\t_______________________________________________\n\n";
    for(int i=1;i<=5;i++){
    	if(i==1 && temp==NULL ){
    		cout<<"There is no task in the list";
            break;
        }else{
        	cout<<"\t\t"<<"Task No : "<<i<<" is "<<temp->task<<" on Date "<<temp->date<<"-"<<temp->month<<"-"<<temp->year<<" at "<<temp->hour<<":"<<temp->min<<endl;
        	if(temp->link==NULL){
            	break;
        	}
        	temp=temp->link;

    	}	
    }
    cout<<"\n\n";
    system("pause");
}

//this function is called when user selects the option "Mark as done"
void LinkedList::deleteNode(){
	Node *curr, *temp, *prev, *temp2;
	int count = 1,n, flag = 1, position,ch;
	cout<<"\t\t_______________________________________________\n\n";
	cout<<"\t\t\t\t MARK AS DONE \n";
	cout<<"\t\t_______________________________________________\n\n\n";
    cout<<"\n\n\t\t\t\t Enter your Choice\n\n\t\t\t\t 1. Mark with task no \n\n\t\t\t\t 2. Mark by Date \n\n\t\t\t\t 3. Back to Previous Menu \n\n\t\t\t\t ";
    cout<<"ENTER CHIOCE=";
    cin>>ch;
    switch(ch){
        case 1:
    		cout<<endl<<"Enter Task Number : ";
			cin>>position;
			temp = head;
			if(temp==NULL){
		        cout<<"Your Schedule is Empty so There is no task for MarK\n";
		    }else{
				if (position == 1){
		        	head=temp->link;
				}else{
					while(count != position){
						prev= temp;
						temp=temp->link;
						if(temp== NULL){
							flag = 0;
							break;
						}
						count++;
						temp=prev->link;
					}
				}
				if(flag == 1){
	                if(position !=1){
	                	prev->link=temp->link;
	                }
					cout<<endl<<"Task has been marked as completed"<<"\n\n";
					cout<<"\t \t \tPress 1 to Undo\n\t \t \tPress 2 to Continue ";
					cin>>n;
	         		if(n==1){
	                	if(position==1){
	                    	temp->link=head;
	                    	head=temp;
	                	}else{
	            			temp->link = prev->link;
	            			prev->link= temp;
	                	}
	            	}
	            	else if(n==2){
	                	delete temp;
	            	}
	            	else{
	            		cout<<"Wrong input";
	            	}
				}else{
				cout<<endl<<"There is no Task on the task number you specified";
				}
	    	}
	    	break;
		case 2:
	     	temp2=new Node;
	     	cout<<"\n\n\t\tEnter date of the task=";
	    	cin>>temp2->date>>temp2->month>>temp2->year;
	    	temp=head;
	    	if(temp==NULL){
	         	cout<<"\n \t\tYour Schedule is Empty so ";
	     	}else{
	    		while(temp != NULL){
	    			if((temp2->date==temp->date)&&(temp2->month=temp->month)&&(temp2->year==temp->year)){
	    				flag=0;
	    				if(head==temp){
	        				head=temp->link;
	    				}else{
	        				prev->link=temp->link;
	    				}
					}
					prev=temp;
					temp=temp->link;
				}
			}
			if(flag==1){
	    		cout<<"There is NO Task to Mark\n";
			}
			if(flag==0){
	    		cout<<"\nTask marks Successfully\n";
			}
	    	system("pause");
		case 3: break;
		default:cout<<"\t wrong choice \n";
		system("pause");
	}
}

//function to update any task description
void LinkedList::updateNode(){
	Node *temp,*update,*prev;
	temp = head;
	int viewChoice, taskChoice;
	string newTaskDesc;
	int count = 1, flag = 1, position, times = 0;
	cout<<"\t\t_______________________________________________\n\n";
	cout<<"\t\t\t UPDATE A TASK DESCRIPTION \n";
	cout<<"\t\t_______________________________________________\n\n\n";
    cout<<"\n\t\t1. Update task by task no \n\t\t2. Update task by date \n\t\t3. Go Back\n";
    cout<<"\t\tEnter Your Choice : ";
    cin >> viewChoice;
    switch(viewChoice){
		case 1:
			cout<<"\t\t_______________________________________________\n\n";
			cout<<"\t\t UPDATE TASK BASED ON TASK NUMBER \n";
			cout<<"\t\t_______________________________________________\n\n\n";
	    	cout<<endl<<"\t\tEnter Task Number : ";
			cin>>position;
			if (position == 1){
				cout<<endl<<"\t\tPrevious Task Description is : "<<head->task;
				cout<<endl<<"\t\tEnter new Task Description : ";
				cin.ignore();
				getline(cin,newTaskDesc);
				head->task = newTaskDesc;
				cout<<endl<<"\t\tTask has been successfully updated"<<endl;
			}else{
				while(count != position-1){
					temp = temp->link;
					if(temp == NULL){
						flag = 0;
						break;
					}
					count++;
				}
				if(flag == 1){
					cout<<"\n\t\t\Previous Task Description is : "<<head->task;
					cout<<endl<<"\t\tEnter new Task Description : ";
					cin.ignore();
					getline(cin,newTaskDesc);
					temp->link->task = newTaskDesc;
					cout<<endl<<"\t\tTask has been successfully updated"<<endl;
				}
				else
					cout<<"\t\tTask not found"<<endl;	
			}
			break;
			
	//	case 2 for updating task on a particular date
		case 2:
			system("cls");
			cout<<"\t\t_______________________________________________\n\n";
			cout<<"\t\t\t UPDATE TASK BASED ON DATE \n";
			cout<<"\t\t_______________________________________________\n\n\n";
			int d, m, y; 
			cout<<"\t\tEnter Date : ";
			cin>>d>>m>>y;
			
			//counting the number of task on the given date
			temp = head;
			while (temp != NULL){
				if(temp->date == d && temp->month == m && temp->year == y)
					times++;
			temp = temp->link;
			}
			
			//if there is only one task in the list on the given date
			if(times == 1){
				temp = head;
				while(temp != NULL){
					if(temp->date == d && temp->month == m && temp->year == y){
						cout<<endl<<"\t\tPrevious Task Description is : "<<temp->task;
						cout<<endl<<"\t\tEnter new Task Description : ";
						cin.ignore();
						getline(cin,newTaskDesc);
						temp->task = newTaskDesc;
						cout<<endl<<"\n\t\tTask has been successfully updated"<<endl;
					}
					temp = temp->link;
				}
			}
			
			//else if there are more than one task on the given date
			else if (times > 1){
				cout<<"\n\t\tThere are More than One Tasks on date : "<<d<<"-"<<m<<"-"<<y;
				cout<<"\n\t\tSelect one of these Tasks to Update\n";
				int i = 1;
				temp = head;
				
				//displaying all the task on the given date
				while(temp != NULL){
					if(temp->date == d && temp->month == m && temp->year == y){
						cout<<endl;
						cout<<"\t\tTask Number "<<i<<" : "<<temp->task<<" at "<<temp->hour<<":"<<temp->min<<endl;
						i++;
					}
					temp = temp->link;
				}
				
				//updating a particular task specified by user
				cout<<"\n\t\tEnter Your Choice : ";
				cin >> taskChoice;
				temp = head;
				times = 0;
				while(temp != NULL){
					if(temp->date == d && temp->month == m && temp->year == y)
						times++;
					if(times == taskChoice)
						break;						
				temp = temp->link;
				}
				cout<<endl<<"\t\tPrevious Task Description is : "<<temp->task;
				cout<<endl<<"\t\tEnter new Task Description : ";
				cin.ignore();
				getline(cin,newTaskDesc);
				temp->task = newTaskDesc;
				cout<<endl<<"\n\t\tTask has been successfully updated"<<endl;
			}
			
			//if there are no task on the given date
			else if (times == 0)
				cout<<"\n\t\tThere are no Tasks on date : "<<d<<"-"<<m<<"-"<<y;	
	        break;
		
		//case 3 to go back to previous menu
		case 3: 
			break;
		default:
			cout<<"\t\t Wrong Choice \n";
	}
	cout<<endl;
	system("pause");
}

//taskOnDate() function definition
void LinkedList::taskOnDate(){
	int d, m, y, flag = 1;
	cout<<endl<<"\t\tEnter Date : ";
	cin>>d>>m>>y;
	cout<<"\t\t_______________________________________________\n\n";
	cout<<"\t\t\tTASKS ON DATE : "<<d<<"-"<<m<<"-"<<y<<endl;
	cout<<"\t\t_______________________________________________\n\n\n";
	Node *ptr = head;
	while(ptr != NULL){
		if(ptr->date == d && ptr->month == m && ptr->year == y){
			cout<<endl;
			cout<<"\t\tTask Description : "<<ptr->task<<" at "<<ptr->hour<<":"<<ptr->min<<endl;
			flag = 0;
		}
		ptr = ptr->link;
	}
	if(flag)
		cout<<endl<<"\t\tNo Pending Tasks on This Date"<<endl;
	system("pause");
}

//fucntion to display task based on groups
void LinkedList::pickGroup(string groupName){
	system("cls");
	int flag = 1;
	cout<<"\t\t_______________________________________________\n\n";
	cout<<"\t\t\t\t	"<<groupName<<endl;
	cout<<"\t\t_______________________________________________\n\n\n";
	Node *ptr = head;
	while(ptr != NULL){
		if(ptr->group == groupName){
			cout<<endl;
			cout<<"\t\tTask Description : "<<ptr->task<<" at "<<ptr->hour<<":"<<ptr->min<<endl;
			flag = 0;
		}
		ptr = ptr->link;
	}
	if(flag)
		cout<<endl<<"\t\tNo Pending Tasks on This Date"<<endl;
	cout<<endl;
	system("pause");
}

//dateValidator() function defintion
bool LinkedList::dateValidator(Node& d){
	if (d.year < 1800)
		return false;
	if (! (1 <= d.month && d.month <= 12) )
    	return false;
	if (! (1 <= d.date && d.date <= 31) )
    	return false;
	if ( (d.date == 31) && (d.month == 2 || d.month == 4 || d.month == 6 || d.month == 9 || d.month == 11) )
    	return false;
	if ( (d.date == 30) && (d.month == 2) )
    	return false;
	if ( (d.month == 2) && (d.date == 29) && (d.year%4 != 0) )
    	return false;
	if ( (d.month == 2) && (d.date == 29) && (d.year%400 == 0) )
		return true;
	if ( (d.month == 2) && (d.date == 29) && (d.year%100 == 0) )
    	return false;
	if ( (d.month == 2) && (d.date == 29) && (d.year%4 == 0)  )
    	return true;
	return true;
}

//fucntion to check time
bool LinkedList::timeValidator(Node& d){
	if (! (0 <= d.hour && d.hour < 24) )
    	return false;
	if (! (0 <= d.min && d.min < 60) )
    	return false;
    return true;
}
