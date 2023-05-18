/*
*****************************************************************************
						Milestone 2
Group Number 1
Group memeber 1 Name  : Chi Man Law 
Group memeber 2 Name  : Hamza Teli 
Group memeber 3 Name  : Abdirahman Osman
Section				: DBS211NBB
Date				: 2023-04-02
*****************************************************************************
*/

#include <iostream>
#include <occi.h>
#include <string>



using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;

using namespace std;

#define EXIT 13
//OCCI Variables - Hamza Teli
Environment* env = nullptr;
Connection* conn = nullptr;

//User variables
string str;
string usr = "dbs211_231nbb38";
string pass = "22673218";
string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";

//Global Structs
//Chi Man Law
struct Patient {
	int patientid;
	string firstname;
	string lastname;
	string phone;
	string address;
	string gender;
	string dateofbirth;
	int weightlbs;
	int heightcm;
	string bloodtype;
};

//Hamza Teli
struct Appointment {
	int appointmentID;
	int patientID;
	int doctorID;
	string appDescription;
	string status;
	string startDate;
	string endDate;
	string startTime;
	string endTime;
	string comments;
};

//Abdirahman Osman
struct Medication {
	int medicationid;
	string name;
	string brand;
	int quantityinstore;
	int mgperdose;
	int patientID;
	string firstName;
	string lastName;
	string status;
};

//Declare global struct
struct Patient patient;
struct Appointment appStruct;
struct Medication medStruct;


//Function declarations ------------------------------------------------------------------
int menu(void); //Displays a menu and returns an integer value based on the selection 
int findPatient(Connection* conn, int PatientNumber); //Find a patient by patient id - Chi Man Law
void displayPatient(Connection* conn, struct Patient patient); //Display one patient row - Chi Man Law
void displayAllPatient(Connection* conn); //Display all patients in table - Chi Man Law
void displayPatientWardStay(Connection* conn, struct Patient patient); //isplayPatientWardStay record - Chi Man Law
int findAppointment(Connection* conn, int appointment_id); //Finds an appoinment and returns 1 if exists, else 0 - Hamza Teli
void displayAppointment(Connection* conn, struct Appointment app); //Display one appointment - Hamza Teli
void displayAllAppointments(Connection* conn); //Display all appointments - Hamza Teli
void displayAppointmentByPatientID(Connection* conn, Appointment app); //Display appointment based on patient ID - Hamza Teli (Join table)
int findMEDICATION(Connection* conn, int medication_ID);// Find medeication by medicationid - Abdirahman Osman
void displayMedication(Connection* conn, struct Medication med); //Display one medication row - Abdirahman Osman
void displayallMedication(Connection* conn); //Display all medications - Abdirahman Osman
void medicationPatientsHistory(Connection* conn, struct Medication med); // displays the  patients using a specific medication based on its medication ID.  - Abdirahman Osman


int main(void)
{
	try {
		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(usr, pass, srv);
		//cout << "Connection is Successful!" << endl;
		Statement* stmt = conn->createStatement();
		printf("Group number : 01\n");
		printf("Group Application : Hospital Patient Management System\n");
		printf("Group memeber 1 Name  : Chi Man Law\n");
		printf("Group memeber 2 Name  : Hamza Teli\n");
		printf("Group memeber 3 Name  : Abdirahman Osman\n");



		while (menu() != EXIT);

		env->terminateConnection(conn);
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp)
	{
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}


	return 0;
}

//Displays a menu and returns an integer value based on the selection 
int menu(void)
{
	int input = 0;
	do {
		cout << "**************************************************";
		cout << "\nHospital Patient Management System MENU\n";
		cout << "**************************************************" << endl;
		cout << "\n1. Find Patient";
		cout << "\n2. Patient Report";
		cout << "\n3. Display All Patient";
		cout << "\n4. Find Patient Ward Staying Records";
		cout << "\n5. Find Appointment";
		cout << "\n6. Display An Appointment";
		cout << "\n7. Display All Appointments";
		cout << "\n8. Find appointment with Patient ID";
		cout << "\n9. Find Medication";
		cout << "\n10. Display Medication";
		cout << "\n11. Display all Medication";
		cout << "\n12. Display patients taking specific Medication using medicationId ";
		cout << "\n" << EXIT << ". Exit";
		cout << "\n> Enter your choice: ";
		cin >> input;

		if (cin.fail() || input < 1 || input > EXIT) {
			if (cin.fail()) {
				cin.clear();
			}
			cin.ignore(1000, '\n');
			cout << "The option you entered in incorrect (must be 1 to " << EXIT << "), please enter your option again!\n";
		}
		else {
			if (input == 1) {
				cout << "\n Entering choice to find a Patient";
				int patientNum;
				cout << "\n Enter Patient Number: ";
				cin >> patientNum;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\n> Invalid Patient Number\n\n";
				}
				else {
					cin.ignore(1000, '\n');
					if (findPatient(conn, patientNum)) {
						cout << "\n> Valid Patient Number\n\n";
					}
					else {
						cout << "\n> Invalid Patient Number\n\n";
					}
				}
			}
			else if (input == 2) {
				cout << "\nEntering choice to display a Patient";
				int patientNum;
				cout << "\n Enter Patient Number: ";
				cin >> patientNum;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\n> Invalid Patient Number\n\n";
				}
				else {
					cin.ignore(1000, '\n');
					if (findPatient(conn, patientNum)) {
						cout << "\n> Valid Patient Number\n";
						cout << "\nSearch in Table\n";
						patient.patientid = patientNum;
						displayPatient(conn, patient);
						cout << endl;
					}
					else {
						cout << "\n> Patient " << patientNum << " does not exist.\n\n";
					}

				}
			}

			else if (input == 3) {
				cout << "\nEntering choice to display ALL Patients";
				displayAllPatient(conn);
				cout << endl;
			}
			else if (input == 4) {
				cout << "\nEntering choice to display";
				int patientNum;
				cout << "\n Enter Patient Number: ";
				cin >> patientNum;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\n> Invalid Patient Number\n\n";
				}
				else {
					cin.ignore(1000, '\n');
					if (findPatient(conn, patientNum)) {
						cout << "\n> Valid Patient Number\n";
						cout << "\nSearch in Table\n";
						patient.patientid = patientNum;
						displayPatientWardStay(conn, patient);
						cout << endl;
					}
					else {
						cout << "\n> Patient " << patientNum << " does not exist.\n\n";
					}

				}
			}
			else if (input == 5)
			{
				cout << "\n Entering choice to find an appointment";
				int app;
				cout << "\n Enter appointment id: ";
				cin >> app;
				if (findAppointment(conn, app) == 1)
				{
					cout << "\n> Valid Appointment ID\n\n";
				}
				else
				{
					cout << "\n> Invalid Appointment ID\n\n";
				}
			}
			else if (input == 6)
			{
				cout << "\nEntering choice to display an appointment";
				int appID;
				cout << "\n Enter appointment id: ";
				cin >> appID;
				if (findAppointment(conn, appID) == 1)
				{
					cout << "\n> Valid Appointment ID\n\n";
					appStruct.appointmentID = appID;
					displayAppointment(conn, appStruct);
					cout << endl;

				}
				else
				{
					cout << "\n> Invalid Appointment ID\n\n";
				}
			}
			else if (input == 7)
			{
				cout << "\nEntering choice to display all appointments\n";
				displayAllAppointments(conn);
				cout << endl;
			}
			else if (input == 8)
			{
				cout << "\nEntering choice to find all appointments of a patient";
				int pID;
				cout << "\n Please enter patient ID: ";
				cin >> pID;

				//Check if patient exists
				if (findPatient(conn, pID)) {
					cout << "\n> Displaying All Appointments for Patient ID: " << pID << "\n\n";
					appStruct.patientID = pID;
					displayAppointmentByPatientID(conn, appStruct);
				}
				else {
					cout << "\n> Invalid Patient Number\n\n";
				}

			}


			if (input == 9)
			{
				cout << "\n Entering choice to find an medication";
				int medication;
				cout << "\n Enter Medication id: ";
				cin >> medication;
				if (findMEDICATION(conn, medication) == 1)
				{
					cout << "\n> Valid Medication ID\n\n";
				}
				else
				{
					cout << "\n> Invalid Medication ID\n\n";
				}
			}
			else if (input == 10)
			{
				cout << "\nEntering choice to display  Medication";
				int medId;
				cout << "\n Enter Medication id: ";
				cin >> medId;
				if (findMEDICATION(conn, medId) == 1)
				{
					cout << "\n> Valid Medication ID\n";
					medStruct.medicationid = medId;
					displayMedication(conn, medStruct);
					cout << endl;
				}
				else
				{
					cout << "\n> Invalid Medication ID\n";
				}
			}
			else if (input == 11)
			{
				cout << "\nEntering choice to display all Medication\n";
				displayallMedication(conn);
				cout << endl;
			}
			else if (input == 12)
			{

				cout << "\nEntering choice to display an pateint medical History BY patientId";
				int medId;
				cout << "\n Enter Medication id: ";
				cin >> medId;
				if (findMEDICATION(conn, medId) == 1)
				{
					cout << "\n> Valid Medication ID\n\n";
					medStruct.medicationid = medId;
					medicationPatientsHistory(conn, medStruct);
					cout << endl;

				}
				else
				{
					cout << "\n> Invalid Medication ID\n\n";
				}
			}
		}

	} while (input != EXIT);

	return input;
}

//Find a patient by patient id -- Chi Man Law
int findPatient(Connection* conn, int PatientNumber) {

	Statement* stmt = conn->createStatement();
	string temp = "SELECT patientid,firstname, lastname, phone, address, gender, to_char(dateofbirth,'YYYY-MM-DD'), weightlbs, heightcm, bloodtype from patient where patientid = " + to_string(PatientNumber);
	//cout << "SQL is " << temp << endl;
	ResultSet* rsss = stmt->executeQuery(temp);

	try {


		if (rsss->next()) {

			return 1;
		}
		else {
			return 0;
		}

	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}


}

//Display one patient row - Chi Man Law
void displayPatient(Connection* conn, struct Patient patient) {

	Statement* stmt = conn->createStatement();
	string temp = "SELECT patientid,firstname, lastname, phone, address, gender, to_char(dateofbirth,'YYYY-MM-DD'), weightlbs, heightcm, bloodtype from patient where patientid = " + to_string(patient.patientid);
	ResultSet* rsss = stmt->executeQuery(temp);


	try {

		if (rsss->next()) {
			patient.patientid = rsss->getInt(1);
			patient.firstname = rsss->getString(2);
			patient.lastname = rsss->getString(3);
			patient.phone = rsss->getString(4);
			patient.address = rsss->getString(5);
			patient.gender = rsss->getString(6);
			patient.dateofbirth = rsss->getString(7);
			patient.weightlbs = rsss->getInt(8);
			patient.heightcm = rsss->getInt(9);
			patient.bloodtype = rsss->getString(10);
		}
		cout << "\n----------" << "Patient Information" << "----------" << endl << endl;
		cout << "Patient No.: " << patient.patientid << endl;
		cout << "First Name: " << patient.firstname << endl;
		cout << "Last Name: " << patient.lastname << endl;
		cout << "Phone: " << patient.phone << endl;
		cout << "Address: " << patient.address << endl;
		cout << "Gender: " << patient.gender << endl;
		cout << "Date of Birth: " << patient.dateofbirth << endl;
		cout << "Weight(lbs): " << patient.weightlbs << endl;
		cout << "Height(cm): " << patient.heightcm << endl;
		cout << "Blood Type: " << patient.bloodtype << endl;


	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}


}

//Display all patients in table - Chi Man Law
void displayAllPatient(Connection* conn) {

	Statement* stmt = conn->createStatement();
	string temp = "SELECT patientid,firstname, lastname, phone, address, gender, to_char(dateofbirth,'YYYY-MM-DD'), weightlbs, heightcm, bloodtype from patient order by patientid";
	ResultSet* rsss = stmt->executeQuery(temp);

	try {


		cout << "\n\n----------" << "All Patient Information" << "----------\n" << endl << endl;


		cout.setf(ios::left);
		cout.fill(' ');
		cout.width(15);
		cout << "Patient No.";
		cout.width(20);
		cout << "First Name";
		cout.width(20);
		cout << "Last Name";
		cout.width(20);
		cout << "Phone";
		cout.width(40);
		cout << "Address";
		cout.width(8);
		cout << "Gender";
		cout.width(16);
		cout << "Date of Birth";
		cout.width(14);
		cout << "Weight(lbs)";
		cout.width(14);
		cout << "Height(cm)";
		cout.width(5);
		cout << "Blood Type";
		cout << endl;


		while (rsss->next()) {
			patient.patientid = rsss->getInt(1);
			patient.firstname = rsss->getString(2);
			patient.lastname = rsss->getString(3);
			patient.phone = rsss->getString(4);
			patient.address = rsss->getString(5);
			patient.gender = rsss->getString(6);
			patient.dateofbirth = rsss->getString(7);
			patient.weightlbs = rsss->getInt(8);
			patient.heightcm = rsss->getInt(9);
			patient.bloodtype = rsss->getString(10);
			cout.setf(ios::left);
			cout.fill(' ');
			cout.width(15);
			cout << patient.patientid;
			cout.width(20);
			cout << patient.firstname;
			cout.width(20);
			cout << patient.lastname;
			cout.width(20);
			cout << patient.phone;
			cout.width(40);
			cout << patient.address;
			cout.width(8);
			cout << patient.gender;
			cout.width(16);
			cout << patient.dateofbirth;
			cout.width(14);
			cout << patient.weightlbs;
			cout.width(14);
			cout << patient.heightcm;
			cout.width(5);
			cout << patient.bloodtype;
			cout << endl;

		}


	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}

}

//DisplayPatientWardStay record - Chi Man Law
void displayPatientWardStay(Connection* conn, struct Patient patient) {

	Statement* stmt = conn->createStatement();
	string temp = "select t.SYMPTOMS, t.COMMENTS, to_char(w.fromdate,'YYYY-MM-DD'), to_char(w.todate,'YYYY-MM-DD'), w.STAYREASON from patient p join treatment t on p.patientID = t.patientid join patientwardstays w on t.treatmentid = w.treatmentid where p.patientID = " + to_string(patient.patientid) + "order by p.patientID, w.fromdate";
	ResultSet* rsss = stmt->executeQuery(temp);

	try {

		int count = 0;
		cout << "\n\n----------" << "Patient Ward Staying Records" << "----------\n" << endl << endl;


		while (rsss->next()) {
			count++;
			cout << "From Date       : " << rsss->getString(3) << endl;
			cout << "To Date         : " << rsss->getString(4) << endl;
			cout << "Stay Reason     : " << rsss->getString(5) << endl;
			cout << "Patient Symptoms: " << rsss->getString(1) << endl;
			cout << "Doctor Comments : " << rsss->getString(2) << endl << endl;
		}
		if (count == 0) {
			"No Ward Staying Record found for this patient!";
		}

	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}

}


//Finds an appoinment and returns 1 if exists, else 0 - Hamza Teli (Join table)
int findAppointment(Connection* conn, int appointment_id)
{
	try {
		Statement* stmt = conn->createStatement();
		ResultSet* rs = stmt->executeQuery("SELECT APPOINTMENTID, PATIENTID, DOCTORID, APPDESCRIPTION, STATUS, STARTDATETIME, ENDDATETIME, COMMENTS FROM APPOINTMENTS WHERE APPOINTMENTID = " + to_string(appointment_id));

		if (rs->next())
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	catch (SQLException& sqlExcp)
	{
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}

//Display one appointment - Hamza Teli
void displayAppointment(Connection* conn, Appointment app)
{
	try {
		Statement* stmt = conn->createStatement();
		ResultSet* rs = stmt->executeQuery("SELECT APPOINTMENTID, PATIENTID, DOCTORID, APPDESCRIPTION, STATUS, STARTDATETIME, ENDDATETIME, TO_CHAR(STARTDATETIME, 'HH24:MI'), TO_CHAR(ENDDATETIME, 'HH24:MI'), COMMENTS FROM APPOINTMENTS WHERE APPOINTMENTID = " + to_string(app.appointmentID));

		while (rs->next())
		{
			appStruct.appointmentID = rs->getInt(1);
			appStruct.patientID = rs->getInt(2);
			appStruct.doctorID = rs->getInt(3);
			appStruct.appDescription = rs->getString(4);
			appStruct.status = rs->getString(5);
			appStruct.startDate = rs->getString(6);
			appStruct.endDate = rs->getString(7);
			appStruct.startTime = rs->getString(8);
			appStruct.endTime = rs->getString(9);
			appStruct.comments = rs->getString(10);
		}

		//Display appointment format
		cout << "-------------------------------------------------------------------- Appointment Viewer ---------------------------------------------------------------------" << endl;
		cout << "Appointment ID  Patient ID  Doctor ID  Description                                               Status     Start Date/Time  End Date/Time    Comments" << endl;
		cout << "--------------- ----------  ---------- --------------------------------------------------------  ---------- ---------------  ---------------  ---------------" << endl;

		//cout << "Appointment ID: ";
		cout.setf(ios::left);
		cout.width(19);
		cout << appStruct.appointmentID;

		//cout << "Patient ID: ";
		cout.width(12);
		cout << appStruct.patientID;

		//cout << "Doctor ID";
		cout.width(8);
		cout << appStruct.doctorID;

		//cout << "Description: ";
		cout.width(58);
		cout << appStruct.appDescription;

		//cout << "Status: ";
		cout.width(11);
		cout << appStruct.status;

		//cout << "Start Date/Time: ";
		cout << appStruct.startDate;
		cout << "/";
		cout.width(7);
		cout << appStruct.startTime;

		//cout << "End Date/Time";
		cout << appStruct.endDate;
		cout << "/";
		cout << appStruct.endTime;


		//cout << "Comments: ";
		cout << appStruct.comments << endl;

		cout << "--------------- ----------  ---------- --------------------------------------------------------  ---------- ---------------  ---------------  ---------------" << endl;
	}
	catch (SQLException& sqlExcp)
	{
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}
//Display all appointments - Hamza Teli
void displayAllAppointments(Connection* conn)
{
	try {
		Statement* stmt = conn->createStatement();
		ResultSet* rs = stmt->executeQuery("SELECT APPOINTMENTID, PATIENTID, DOCTORID, APPDESCRIPTION, STATUS, STARTDATETIME, ENDDATETIME, TO_CHAR(STARTDATETIME, 'HH24:MI'), TO_CHAR(ENDDATETIME, 'HH24:MI'), COMMENTS FROM APPOINTMENTS");

		//Display appointment format
		cout << "-------------------------------------------------------------------- Appointment Viewer ---------------------------------------------------------------------" << endl;
		cout << "Appointment ID  Patient ID  Doctor ID  Description                                               Status     Start Date/Time  End Date/Time    Comments" << endl;
		cout << "--------------- ----------  ---------- --------------------------------------------------------  ---------- ---------------  ---------------  ---------------" << endl;


		while (rs->next())
		{
			appStruct.appointmentID = rs->getInt(1);
			appStruct.patientID = rs->getInt(2);
			appStruct.doctorID = rs->getInt(3);
			appStruct.appDescription = rs->getString(4);
			appStruct.status = rs->getString(5);
			appStruct.startDate = rs->getString(6);
			appStruct.endDate = rs->getString(7);
			appStruct.startTime = rs->getString(8);
			appStruct.endTime = rs->getString(9);
			appStruct.comments = rs->getString(10);

			//cout << "Appointment ID: ";
			cout.setf(ios::left);
			cout.width(19);
			cout << appStruct.appointmentID;

			//cout << "Patient ID: ";
			cout.width(12);
			cout << appStruct.patientID;

			//cout << "Doctor ID";
			cout.width(8);
			cout << appStruct.doctorID;

			//cout << "Description: ";
			cout.width(58);
			cout << appStruct.appDescription;

			//cout << "Status: ";
			cout.width(11);
			cout << appStruct.status;

			//cout << "Start Date/Time: ";
			cout << appStruct.startDate;
			cout << "/";
			cout.width(7);
			cout << appStruct.startTime;

			//cout << "End Date/Time";
			cout << appStruct.endDate;
			cout << "/";
			cout << appStruct.endTime;

			//cout << "Comments: ";
			cout << appStruct.comments << endl;
		}

		cout << "--------------- ----------  ---------- --------------------------------------------------------  ---------- ---------------  ---------------  ---------------" << endl;
	}
	catch (SQLException& sqlExcp)
	{
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}

//Display appointment based on patient ID - Hamza Teli
void displayAppointmentByPatientID(Connection* conn, Appointment app)
{
	try {
		Statement* stmt = conn->createStatement();
		ResultSet* rs = stmt->executeQuery("SELECT APPOINTMENTS.APPOINTMENTID, APPOINTMENTS.PATIENTID, APPOINTMENTS.DOCTORID, APPDESCRIPTION, STATUS, STARTDATETIME, ENDDATETIME, TO_CHAR(STARTDATETIME, 'HH24:MI'), TO_CHAR(ENDDATETIME, 'HH24:MI'), COMMENTS FROM APPOINTMENTS LEFT OUTER JOIN PATIENT ON APPOINTMENTS.PATIENTID = PATIENT.PATIENTID WHERE PATIENT.PATIENTID = " + to_string(app.patientID));

		while (rs->next())
		{
			appStruct.appointmentID = rs->getInt(1);
			appStruct.patientID = rs->getInt(2);
			appStruct.doctorID = rs->getInt(3);
			appStruct.appDescription = rs->getString(4);
			appStruct.status = rs->getString(5);
			appStruct.startDate = rs->getString(6);
			appStruct.endDate = rs->getString(7);
			appStruct.startTime = rs->getString(8);
			appStruct.endTime = rs->getString(9);
			appStruct.comments = rs->getString(10);
		}

		//Display appointment format
		cout << "-------------------------------------------------------------------- Appointment Viewer ---------------------------------------------------------------------" << endl;
		cout << "Appointment ID  Patient ID  Doctor ID  Description                                               Status     Start Date/Time  End Date/Time    Comments" << endl;
		cout << "--------------- ----------  ---------- --------------------------------------------------------  ---------- ---------------  ---------------  ---------------" << endl;

		//cout << "Appointment ID: ";
		cout.setf(ios::left);
		cout.width(19);
		cout << appStruct.appointmentID;

		//cout << "Patient ID: ";
		cout.width(12);
		cout << appStruct.patientID;

		//cout << "Doctor ID";
		cout.width(8);
		cout << appStruct.doctorID;

		//cout << "Description: ";
		cout.width(58);
		cout << appStruct.appDescription;

		//cout << "Status: ";
		cout.width(11);
		cout << appStruct.status;

		//cout << "Start Date/Time: ";
		cout << appStruct.startDate;
		cout << "/";
		cout.width(7);
		cout << appStruct.startTime;

		//cout << "End Date/Time";
		cout << appStruct.endDate;
		cout << "/";
		cout << appStruct.endTime;


		//cout << "Comments: ";
		cout << appStruct.comments << endl;

		cout << "--------------- ----------  ---------- --------------------------------------------------------  ---------- ---------------  ---------------  ---------------" << endl;
	}
	catch (SQLException& sqlExcp)
	{
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}

// Find medeication by medicationid - Abdirahman Osman
int findMEDICATION(Connection* conn, int medication_ID) {

	try {

		Statement* stmt = conn->createStatement();

		ResultSet* rs = stmt->executeQuery("SELECT medicationID ,name,brand, quantityinstore,mgperdose \
			from medication WHERE medicationID = " + to_string(medication_ID));

		if (rs->next()) {

			return 1;

		}

		return 0;

	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();

	}

}
//Display one medication row - Abdirahman Osman

void displayMedication(Connection* conn, Medication med) {

	try {

		//"SELECT medicationID ,name,brand, description, quantityinstore,mgperdose

		Statement* stmt = conn->createStatement();
		ResultSet* rs = stmt->executeQuery("SELECT medicationID ,name,brand, quantityinstore,mgperdose \
			from medication WHERE medicationID = " + to_string(med.medicationid));

		cout << "\n------------------ (Medication Viewer) -------------" << endl;
		cout << "MedID      Name               Brand          Qtn    mgperdose" << endl;
		cout << "----- --------------- --------------------- ------- ---------" << endl;

		while (rs->next()) {

			medStruct.medicationid = rs->getInt(1);
			medStruct.name = rs->getString(2);
			medStruct.brand = rs->getString(3);
			medStruct.quantityinstore = rs->getInt(4);
			medStruct.mgperdose = rs->getInt(5);

			cout.width(5);
			cout.setf(ios::left);
			cout << medStruct.medicationid;
			cout << " ";
			cout.width(15);
			cout.setf(ios::left);
			cout << medStruct.name;
			cout << " ";
			cout.width(22);
			cout.setf(ios::left);
			cout << medStruct.brand;
			cout << "";
			cout.width(7);
			cout.setf(ios::left);
			cout << medStruct.quantityinstore;
			cout << "  ";
			cout.width(9);
			cout.setf(ios::left);
			cout << medStruct.mgperdose << endl;

		}

	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();

	}

}
//Display all medications - Abdirahman Osman
void displayallMedication(Connection* conn) {

	try {

		//"SELECT medicationID ,name,brand, description, quantityinstore,mgperdose

		Statement* stmt = conn->createStatement();
		ResultSet* rs = stmt->executeQuery("SELECT medicationID ,name,brand, quantityinstore,mgperdose \
			from medication");

		cout << "\n------------------ (All Medications Viewer) -------------" << endl;
		cout << "MedID      Name               Brand          Qtn    mgperdose" << endl;
		cout << "----- --------------- --------------------- ------- ---------" << endl;

		while (rs->next()) {

			medStruct.medicationid = rs->getInt(1);
			medStruct.name = rs->getString(2);
			medStruct.brand = rs->getString(3);
			medStruct.quantityinstore = rs->getInt(4);
			medStruct.mgperdose = rs->getInt(5);

			cout.width(5);
			cout.setf(ios::left);
			cout << medStruct.medicationid;
			cout << " ";
			cout.width(15);
			cout.setf(ios::left);
			cout << medStruct.name;
			cout << " ";
			cout.width(22);
			cout.setf(ios::left);
			cout << medStruct.brand;
			cout << "";
			cout.width(7);
			cout.setf(ios::left);
			cout << medStruct.quantityinstore;
			cout << "  ";
			cout.width(9);
			cout.setf(ios::left);
			cout << medStruct.mgperdose << endl;

		}

	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();

	}

}

// displays the  patients using a specific medication based on its medication ID.  - Abdirahman Osman
void medicationPatientsHistory(Connection* conn, struct Medication med) {

	try {


		Statement* stmt = conn->createStatement();
		ResultSet* rs = stmt->executeQuery("select distinct patientid,FIRSTNAME,LASTNAME,status,name, brand \
			from MEDICATION \
			inner join PRESCRIPTION using(medicationid) \
			inner join treatment using(treatmentid) \
			inner join patient using (PATIENTID)\
			where medicationID = " + to_string(medStruct.medicationid));

		cout << "\n------------------- (Patient Medical History Viewer) ---------------" << endl;
		cout << "PatID  FirstName      LastName        Status             Name            Brand" << endl;
		cout << "----- ------------- ------------- ------------------ --------------- ---------------------" << endl;

		while (rs->next()) {

			medStruct.patientID = rs->getInt(1);
			medStruct.firstName = rs->getString(2);
			medStruct.lastName = rs->getString(3);
			medStruct.status = rs->getString(4);
			medStruct.name = rs->getString(5);
			medStruct.brand = rs->getString(6);

			cout.width(5);
			cout.setf(ios::left);
			cout << medStruct.patientID;
			cout << " ";
			cout.width(13);
			cout.setf(ios::left);
			cout << medStruct.firstName;
			cout << " ";
			cout.width(13);
			cout.setf(ios::left);
			cout << medStruct.lastName;
			cout << " ";
			cout.width(19);
			cout.setf(ios::left);
			cout << medStruct.lastName;
			cout << "";
			cout.width(15);
			cout.setf(ios::left);
			cout << medStruct.name;
			cout << "  ";
			cout.width(22);
			cout.setf(ios::left);
			cout << medStruct.brand << endl;

		}

	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();

	}

}