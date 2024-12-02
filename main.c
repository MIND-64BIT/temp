/*
Rizvi Bus Reservation System

This Project is developed by

PRAJAPATI NITESH ANILKUMAR [ Team Leader ]
KHAN ISTIYAQ AHMED ASGARALI
PATADE SOHAM SANDEEP
GUPTA UTSAV RAMPRAVESH
SHAIKH REYAAN MEHTABSAB

*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


// Bus Structure
struct bus{
    int busNum;
    char route[64];
    int fare;
    int seatAvailable;
    int filledSeat[40];
};


// Passenger Structure
struct passengers{
    char name[32];
    int age;
    char contact[10];
    int seatNum;
    int busNum;
    int isDeleted;
};

// Creating Buses
struct bus busStructArr[]={
    {51,"Worli to Santacruz",20,40,0},
    {56,"Mahim to Borivali",40,40,0},
    {220,"Bandra Station to Khar",10,40,0},
    {222,"Bandra StationSantacruz",25,40,0}
};


struct passengers psngrArr[1000]={}; // Array of Passengers Struct
int lastPsngr = 0;    // Passenger Array



// Bus Fetch Function
struct bus *fetchBus(int busNo){
    int numofBus = sizeof(busStructArr)/sizeof(busStructArr[0]);
    for(int i = 0;i<numofBus;i++){
        if(busStructArr[i].busNum == busNo){
            return &busStructArr[i];
        }
    }
    return NULL;
}


// Fuction to get detail of passenger
struct passengers *getPsngrDetails(){
    char name[32],phoneNo[10];
    int age;

    printf("Enter Passenger Name:");
    scanf("%s",name);

    printf("Enter Age:");
    scanf("%d",&age);

    printf("Enter Phone Number:");
    scanf("%s",phoneNo);

    struct passengers psngr;
    strcpy(psngr.name,name);
    psngr.age = age;
    strcpy(psngr.contact,phoneNo);
    psngr.isDeleted = 0;

    psngrArr[lastPsngr] = psngr;
    lastPsngr++;

    return &psngrArr[lastPsngr-1];
}

// alloting seats to passengers
void allotSeat(struct bus *selectedBus, struct passengers *passenger) {
    for (int i = 0; i < 40; i++) {

        int seat = selectedBus->filledSeat[i];
        if (seat == 0) {
            selectedBus->filledSeat[i] = 1;
            selectedBus->seatAvailable -= 1;
            passenger->busNum = selectedBus->busNum;
            passenger->seatNum = i+1;
            break;
        }
    }
}

// saving reservation to a file
int saveReservation(){

    FILE *record = fopen("passengers.txt","w+");
    FILE *sysRecord = fopen("record.txt","w+");

    if (record == NULL || sysRecord == NULL) {
        printf("?File Creation Error\n");
        return -1;
    }

    fprintf(record,"----------- Passengers DataBase RBRS -----------\n");

    for(int i = 0; i < lastPsngr; i++){

        struct passengers passenger = psngrArr[i];

        if(passenger.isDeleted == 1){
            continue;
        }

        //passengers.txt
        fprintf(record,"Passenger %d\n",i+1);
        fprintf(record,"Name: %s\nAge: %d\nContact: %s\n",passenger.name,passenger.age,passenger.contact);
        fprintf(record, "Bus Number: %d\tSeat Number: %d\n\n", passenger.busNum, passenger.seatNum);

        //record.txt
        fprintf(sysRecord,"%d,%d,%d,%s,%s.\n",passenger.busNum, passenger.seatNum,passenger.age,passenger.contact,passenger.name);

    }

    fclose(record);
    fclose(sysRecord);
}



// Function to Check Bus Available
void checkAvailabeBus() {

    printf("\nAvailable Buses: \n");
    for (int i = 0; i < 4; i++)
    {
        struct bus selectedBus = busStructArr[i];
        printf("Bus Number: %d\n",selectedBus.busNum);
        printf("Route: %s\n",selectedBus.route);
        printf("Single Fare: %d\n\n",selectedBus.fare);
    }
}


// Function to Check Available Seat in a inputed bus
void checkAvailableSeat() {
    int busNo;
    printf("\nEnter the bus number to check seat availability: ");
    scanf("%d", &busNo);

    struct bus *selectedBus = fetchBus(busNo);

        if (selectedBus == NULL) {
        printf("\nInvalid bus number.\n");
        return;
    }

    printf("\nBus Number: %d", selectedBus->busNum);
    printf("\nRoute:%s", selectedBus->route);
    printf("\nFare: Rs %d", selectedBus->fare);
    printf("\nSeats Available: %d\n", selectedBus->seatAvailable);

}

// seat booking
void bookSeat(int busNo, int totalSeats) {
    struct bus *selectedBus = fetchBus(busNo);
    struct passengers temp[100]={};

    if (selectedBus == NULL) {
        printf("?Invalid Bus Number\n\n");
    }
    else if (totalSeats > 5) {
        printf("You can't Book seats more than 5\n");
    }
    else if (selectedBus->seatAvailable == 0){
        printf("Sorry for Inconveninence, All seats are Booked");
    }
    else if (selectedBus->seatAvailable < totalSeats){
        printf("%d seats are left",selectedBus->seatAvailable);
    }
    else {
        for(int i=0; i<totalSeats; i++){
            printf("\n\nEnter Details of Passenger %d: \n",i+1);
            struct passengers *passenger = getPsngrDetails();
            allotSeat(selectedBus, passenger);
            temp[i] = *passenger;
        }
        int chk = saveReservation();
        if(chk == -1) return;
        printf("\nSuccessfully Seats are Booked\n\nTicket:\n");
        for(int i=0; i<totalSeats; i++){

            printf("Name: %s\nBus Number: %d\tSeat Number: %d\n\n",temp[i].name,temp[i].busNum,temp[i].seatNum);

        }
    }
}

// Cancelling a seat
void cancelSeat() {
    int busNo, seatNo;
    char name[32];

    printf("\nEnter Your Name (as on Ticket): ");
    scanf("%s", name);

    printf("Enter Bus Number: ");
    scanf("%d", &busNo);

    printf("Enter Seat Number: ");
    scanf("%d", &seatNo);

    if (seatNo < 1 || seatNo > 40) {
        printf("\nInvalid seat number.\n");
        return;
    }

    struct bus *selectedBus = fetchBus(busNo);

    if (selectedBus == NULL) {
        printf("\nInvalid Bus Number.\n");
        return;
    }

    struct passengers passenger;

    for(int i = 0; i <= lastPsngr; i++){
        if (psngrArr[i].name == name && psngrArr[i].busNum == busNo && psngrArr[i].seatNum == seatNo) {
            passenger = psngrArr[i];
            break;
        }
        else{
            if(i+1 > lastPsngr){
                printf("We couldn't found your seats. Pls check entered detail.");
                return;
            }
        }
    }

    passenger.isDeleted == 1;
    selectedBus->filledSeat[seatNo - 1] = 0;
    selectedBus->seatAvailable++;
    saveReservation();

    printf("\nSeat %d on Bus %d has been successfully canceled.\n",seatNo,busNo);

}


int main(){


    int choice;
    int busNo,noSeat;



    printf("\n\n||-------- Welcome to Rizvi Bus Revservation System (RBRS) --------||\n\n");


    while (1){
        printf("\n--------------------------------------------------------------------\n");
        printf("1. Check Availabe Buses\n2. Check Seat Available\n3. Book Seats\n4. Cancel a Seat\n5. Exit\n");
        printf("Select: ");
        scanf("%d",&choice);

        switch (choice){

        case 1:
            checkAvailabeBus();
            break;

        case 2:
            checkAvailableSeat();
            break;

        case 3:

            printf("\nEnter Bus Number: ");
            scanf("%d",&busNo);

            printf("Enter number of Seat you want to book: ");
            scanf("%d",&noSeat);

            bookSeat(busNo,noSeat);
            break;

        case 4:
            cancelSeat();
            break;

        case 5:
            exit(0);
            break;

        default:
            printf("\n?Invalid Choice\n");
            break;
        }

    }


    printf("\n||-------- Thank You For Using Rizvi Bus Revservation System (RBRS) --------||\n");

    return 0;
}
