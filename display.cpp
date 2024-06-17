void display_admin_login(){
	cout<<"+++++++++++++++++++++++++++++++"<<endl;
	cout<<"|                             |"<<endl;
	cout<<"|         Admin Login         |"<<endl;
	cout<<"|                             |"<<endl;
	cout<<"+++++++++++++++++++++++++++++++"<<endl;
}

void title(){
	cout<<"+++++++++++++++++++++++++++++++++"<<endl;
	cout<<"|                               |"<<endl;
	cout<<"| VV CLAMING SYSTEM ADMIN PANEL |"<<endl;
	cout<<"|                               |"<<endl;
	cout<<"+++++++++++++++++++++++++++++++++"<<endl;
}
void admin_menu(){
	title();
	cout<<"<--------------------------->"<<endl;
	cout<<"1.Check Request Claim"<<endl;
	cout<<"2.View Provided Claim"<<endl;
	cout<<"3.View Claim History"<<endl;
	cout<<"4.Admin List"<<endl;
	cout<<"5.Logout"<<endl;
	cout<<"<--------------------------->"<<endl;
}

int case2choice(){
	int c;
			do{
				
				cout<<"1.Sort by A-Z"<<endl;
				cout<<"2.Search claim by name"<<endl;
				cout<<"3.Add a new claim"<<endl;
				cout<<"4.Edit claim information"<<endl;
				cout<<"5.Back to Main"<<endl;
				cout<<"<--------------------------->"<<endl;
				cout<<"Enter Your Choice : ";
				cin>>c;
				cin.ignore();
			}while(c<1||c>5);
			return c;
}

int case1choice(){
	int c;
	do{
		check_claim_request();
		cout<<"<--------------------------->"<<endl;
		cout<<"1.Sort by claim type"<<endl;
		cout<<"2.Search by claim type name"<<endl;
		cout<<"3.Proceed to approvement"<<endl;
		cout<<"4.Back"<<endl;
		cout<<"<--------------------------->"<<endl;
		cout<<"Enter Your Choice : ";
		cin>>c;
		
	}while(c<1||c>4);
	return c;
}

int case3choice(){
	int c;
	do{
		check_claim_history();
		cout<<"<--------------------------->"<<endl;
		cout<<"1.Sort by claim type"<<endl;
		cout<<"2.Search by claim name"<<endl;
		cout<<"3.Search by Request ID"<<endl;
		cout<<"4.Back"<<endl;
		cout<<"<--------------------------->"<<endl;
		cout<<"Enter Your Choice : ";
		cin>>c;
		
	}while(c<1||c>4);
	return c;
}

int case4choice(){
	int c;
	
	do{
		admin_detail a;
		a.get_all_admin();
		cout<<"<--------------------------->"<<endl;
		cout<<"1.Add New Admin"<<endl;
		cout<<"2.Admin Delete"<<endl;
		cout<<"3.Back"<<endl;
		cout<<"<--------------------------->"<<endl;
		cout<<"Enter Your Choice : ";
		cin>>c;
		
	}while(c<1||c>3);
	return c;
}



