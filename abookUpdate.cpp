//Updater for canon printer address books. csv (or any plain text document) must be formated as so:
//"Lastname", "Firstname", "email"
//"Lastname2", "Firstname2", "email2"
//And so on.
//Charles Heckroth Nov. 2 2011

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(void)
{
	//Grabbing input and output for the addressbook. Users enter input name as a spreadsheet saved in csv format.
	//Users enter output name as a .ldif (lightweight data interchange format). File extensions must be included.
	string csv;
	cout << "Enter the name of the csv file (users.csv): \n";
	cin >> csv;
	cout << "Enter the desired name of the printer address book (addressbook.abk): \n";
	string abk;
	cin >> abk;
	ofstream fout(abk.c_str());
	ifstream fin(csv.c_str());

	//csv format: Last name, First name, email
	//Start at dn:320



	//While loop reads the csv file and stores the first names, last names, and emails in their respective vectors
	//for future use.
	vector<string> firstNames, lastNames, emails;
	int counter = -1;
	while(!fin.eof())
	{
		string first, last, email;
		getline(fin, last, ',');
		getline(fin, first, ',');
		getline(fin, email);
		firstNames.push_back(first);
		lastNames.push_back(last);
		emails.push_back(email);
		counter ++;
	}
	

	//For loop removes quotations from names and emails.
	for(int i=0; i<counter; i++)
	{
		lastNames[i] = lastNames[i].substr(1, lastNames[i].size() - 2);
		firstNames[i] = firstNames[i].substr(1, firstNames[i].size() - 2);
		emails[i] = emails[i].substr(1, emails[i].size() - 2);
	}

	/* FORMAT FOR ABK FILE. dn is a counter, uuid section 8000 is a counter. Increments of One.
	subdbid: 1
	dn: 320
	uuid: 00000000-612e-11e0-8000-0000854b80d6
	cn: (Name)
	cnread: (Name)
	mailaddress: (email)
	accesscode: 0
	protocol: smtp
	objectclass: top
	objectclass: extensibleobject
	objectclass: email
	*/


	//Outputs to file. Counts for dn and uuid so that it increments properly.
	int dn = 320, uuidcount = 8000;
	for(int i=0; i<counter; i++)
	{
		fout << "subdbid: 1" << endl
			<< "dn: " << dn << endl
			<< "uuid: 00000000-612e-11e0-" << uuidcount << "-0000854b80d6\n"
			<< "cn: " << firstNames[i] << " " << lastNames[i] << endl
			<< "cnread: " << firstNames[i] << " " << lastNames[i] << endl
			<< "mailaddress: " << emails[i] << endl
			<< "accesscode: 0\n"
			<< "protocol: smtp\n"
			<< "objectclass: top\n"
			<< "objectclass: extensibleobject\n"
			<< "objectclass: email\n\n";
		dn ++; uuidcount ++;
	}
		
	return 0;
}
