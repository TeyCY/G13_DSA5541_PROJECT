int case2function(int c){
	switch(c){
		case 1:
			char choice;
			
		    sort_main();
		    cout<<"continue to search [Y/N]?";
		    cin>>choice;
		    if(toupper(choice)=='Y'){
		    	get_claim_target();
			}
			cout<<"Press Any Key to continue ...";
			_getch();
			break;
			
		case 2:
			get_claim_target();
			cout<<"Press Any Key to continue ...";
			_getch();
			break;
		case 3:
			
			addnewclaim();
			return 0;
			break;
		case 4:
			
			claim_edit();
			
			return 0;
			break;
			
	
		return 6;

	}
	
}

int case1function(int c){
	int select;
	switch(c){
		case 1:
			
			system("cls");
			claim_search_sort(1);
			select=proceed_to_update();
			break;
		case 2:
			
			cin.ignore();
			claim_search_sort(0);
			select=proceed_to_update();
			break;
		case 3:
			approvement();
			break;
	
		

	}
	return 4;
}

int case3function(int c){
	int select;
	switch(c){
		case 1:
			
			system("cls");
			claim_history_search_sort(0);
			cout<<"Press Any Key to continue ...";
			_getch();
			break;
		case 2:
			cin.ignore();
			system("cls");
			claim_history_search_sort(1);
			cout<<"Press Any Key to continue ...";
			_getch();
			
			
			break;
		case 3:
			cin.ignore();
			system("cls");
			claim_history_search_sort(2);
			cout<<"Press Any Key to continue ...";
			_getch();
			break;
	
		

	}
	return 4;
}

int case4function(int c){
	if(c==1){
		admin_function af;
	af.add_new_admin();
	}else if(c==2){
		cin.ignore();
		claim_delete();
	}
	
	
	return 3;
}
