#include<stdio.h>

int main(){
    int choice =0;
    int choose,fChoose;
    char fName[32],readFile[8096],cname[32];
    char newString[100];
    char aFile[100];
    FILE *file;
    FILE *cfile;                                //Declaring all of my variables and files
    while(choice == 0){
        printf("Would you like to do: 1.File operations 2.Line Operations 3. General Operations 4.Special added operations 5. Quit (Enter a number)\n");//Allow the user to enter number to choose which option
        fflush(stdin);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
        scanf("%d",&choose);
        fflush(stdin);
        if(choose==1){
            printf("What file operation would you like to do: 1. Create File 2. Copy File 3. Delete File 4. Show File\n"); // Allow the user to enter another number to decide what function they want to perform.
            scanf("%d",&fChoose);
            fflush(stdin);
            if(fChoose==1){
                printf("What would you like the file to be called? (max 32 characters)\n"); //Allow the user to decide what the file is going to be called.
                scanf("%s",&fName);
                fflush(stdin);
                file = fopen(fName,"r");
                if(file==NULL){//If the file doesnt already exist
                    fclose(file);
                    file=fopen(fName,"w");
                    fclose(file);
                    printf("Your file was successfully created\n");
                    file = fopen("Change/changeLog.txt","a");//Updating change log
                    fprintf(file,"Created file %s \n\n" , fName);

                }
                else{//If the file already exists then you can not create another one
                    fclose(file);
                    printf("Sorry that file name already exists\n");
                }
            }
            else if(fChoose==2){
                printf("Which file would you like to copy?\n");//Allows the user to copy a file
                scanf("%s", &fName);
                fflush(stdin);
                file = fopen(fName, "r");
                if(file==NULL){//if the file does not exist then you can not copy it
                    printf("Sorry that file does not exist\n");
                    fclose(file);
                }
                else{
                    printf("What would you like your new file to be called?\n");
                    scanf("%s", &cname);
                    fflush(stdin);
                    cfile = fopen(cname, "r");
                    if(cfile==NULL){
                        fclose(cfile);
                        cfile = fopen(cname,"a");
                        while(fgets(newString,100,file)){ //Goes through every line in the original file and copies it over to the new file.   
                            fprintf(cfile,"\n%s",newString);
                        }
                        fclose(cfile);
                        fclose(file);
                        file = fopen("Change/changeLog.txt","a");
                        fprintf(file,"Copied File %s into new file %s\n\n",fName,cname);//Again updates the change log
                        fclose(file);
                    }
                    else{                               //if the new file name already exisits
                        printf("Sorry that file already exists\n");
                        fclose(cfile);
                        fclose(file);
                    }

                }
            }
            else if(fChoose == 3){//Geeks for Geeks
                char delete[32];
                printf("Please select a file to delete.\n");
                scanf("%s",&delete);                        //Input to delete
                fflush(stdin);
                if(remove(delete)==0){                      // Checks to see if the file was able to be deleted
                    printf("Your file was deleted\n");
                    file = fopen("Change/changeLog.txt","a");
                    fprintf(file,"Deleted File %s\n\n",delete);
                }
                else{
                    printf("unable to delete File\n");
                }
            }
            else if(fChoose==4){
                printf("Which file would you like to show?\n");
                scanf("%s", &fName);                                 //Input to show
                fflush(stdin);
                file = fopen(fName, "r");
                if(file == NULL){                                    //Check to see if file exists
                    printf("Sorry that file was not found/cannot be shown\n");
                }
                else{
                    while(fgets(newString,100,file)){                   //Runs through the file and outputs everything
                        printf("\n%s",newString);
                    }
                }
                fclose(file);
                
            }
            else{
                printf("Sorry that is not a recognised command\n");
            }
        }
        else if(choose==2){// Case for line operations
            printf("What line operation would you like to do: 1. Append File Line 2. Delete Line 3. Insert Line 4. Show Line\n");
            scanf("%d",&fChoose);           //Input which operation to do
            fflush(stdin);
            if(fChoose==1){
                printf("Which file would you like to append to?\n");
                scanf("%s", &fName); // choose a line
                //fflush(stdin);
                file = fopen(fName, "a");
                if(file==NULL){     // if the line does  not exist
                    printf("Sorry that file name is not recognised\n");
                    fclose(file);
                }
                else{
                    printf("What would you like to append into the file?\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) { }//refrence
                    fgets(aFile, 100, stdin);                      //input the sentance you want to append
                    
                    fprintf(file, "%s\n",aFile);//input into file
                    fclose(file);
                    file = fopen("Change/changelog.txt","a");
                    fprintf(file,"Appened to end of file %s with the message '%s'\n\n",fName,aFile); // update change log
                    fclose(file);
                }
                
            }
            else if(fChoose==2){
                printf("Which File would you like to delete from\n");
                scanf("%s", &fName);                                  // choose which file to delete from
                fflush(stdin);
                file = fopen(fName, "r");
                cfile = fopen("lineDeletionTemp.txt", "a");

                if(file==NULL){                                       // If file does not exist
                    printf("Sorry that file name is not recognised\n");
                    fclose(file);
                }
                else{                                                 
                    
                    
                    printf("Which Line would you like to Delete\n");
                    int dFile,count=1,test=1;
                    scanf("%d", &dFile);                              //Choose which line to delete from the file
                    fflush(stdin);
                    char temp[1000];
                    while(fgets(temp,1000,file)){                     // Runs through every line in the file and copies the line over to a temp file. 
                        if(count!=dFile){                             // If the line is equal to the temp file then it is not copied over.
                            fprintf(cfile,"%s" ,temp);
                            test++;
                        }
                        count++;
                    }
                    fclose(file);
                    fclose(cfile);
                    if(remove(fName)==0&&rename("lineDeletionTemp.txt", fName)==0){//gfg
                        printf("Successful\n");                        // Removes the original file then immediately updates the temp file to the old fils name.
                    }
                    
                    
                    if(test!=count){
                        file = fopen("Change/changeLog.txt","a");
                        fprintf(file,"line %d deleted from %s\n\n",dFile,fName); //Updates change log if successful.
                        fclose(file);
                    }
                    
                }
                
                
                
            }
            else if(fChoose==3){
                printf("Which File would you like to insert to\n");
                scanf("%s", &fName);                                //Choose file to insert to
                fflush(stdin);
                file = fopen(fName, "r");
                cfile = fopen("lineInsertionTemp.txt", "a");

                if(file==NULL){                                     // If file does not exist
                    printf("Sorry that file name is not recognised\n");
                    fclose(file);
                }
                else{                                               
                    printf("Which Line would you like to Insert to\n");
                    int iFile,count=1,tempNum=1;
                    char insertion[100];
                    scanf("%d",&iFile);                             // Choose where to insert the line into
                    fflush(stdin);
                    printf("What would you like to insert\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) { }//refrence
                    fgets(insertion, 100, stdin);                  //Flushes the buffer and allows the user to input a statement.
                    char temp[1000];
                    while(fgets(temp,1000,file)){                  //Same technique as delete. Copy all over to temp with new line.
                        if(count!=iFile){
                            fprintf(cfile, temp);
                            
                        }
                        else{
                            fprintf(cfile,insertion);
                            fprintf(cfile,temp);
                            tempNum++;
                        }
                        count++;
                    }
                    fclose(file);
                    fclose(cfile);
                    remove(fName);//removing old file and changing name of new one.
                    rename("lineInsertionTemp.txt", fName);//gfg
                    
                    if(tempNum!=0){
                        file = fopen("Change/changeLog.txt","a");
                        fprintf(file, "line inserted at %d on file %s\n\n",iFile,fName);
                        fclose(file);
                    }
                    
                }
                
                
                
            }
            else if(fChoose==4){
                printf("Which file would you like to read from\n");
                scanf("%s", &fName);// Choose file to read from.
                fflush(stdin);
                file = fopen(fName, "r");
                if(file==NULL){     // If file does not exist
                    printf("Sorry thats not a recognised file\n");
                    fclose(file);
                }
                else{
                    printf("Which line would you like to read\n");
                    int line, count=1, test=0;
                    char temp[1000];
                    scanf("%d", &line);// Input to choose what line to read
                    fflush(stdin);
                    while(fgets(temp,1000,file)){//While loop to run through. Once it reaches the requested line it outputs it to the reader
                        if(count==line){
                            printf(temp);
                            test++;
                        }
                        count++;
                    }
                    if(test==0){
                        printf("Sorry that line was not in the file.\n");
                    }
                    fclose(file);
                }
            }
            else{
                printf("Sorry that is not a recognised command\n");
            }
        }
        else if(choose==3){
            printf("Which general operation would you like to do? 1.Show Change Log 2.Show Number of Lines\n");
            scanf("%d",&fChoose);// Allows to user to choose which general operation to do.
            fflush(stdin);
            if(fChoose==1){
                file = fopen("Change/changeLog.txt", "r"); // Open the change log
                if(file == NULL){                          //If there is an error with the change log
                    printf("Sorry that file was not found/cannot be shown\n");
                }
                else{
                    while(fgets(newString, 1000, file)){   //Outputs the file as usual
                        printf("\n%s",newString);
                    }
                }
                fclose(file);
            }
            else if(fChoose==2){
                printf("Which file would you like to know how many lines there is?\n");
                scanf("%s", &fName);                                                       //Allows the user to pick which file they would like to know how many lines there are there of
                fflush(stdin);
                file = fopen(fName, "r");
                int count=0;
                if(file == NULL){                                                          // If the file option is invalid
                    printf("Sorry that file was not found/cannot be shown\n");
                }
                else{
                    while(fgets(newString, 1000, file)){ //Same idea as printing it out. Instead of printing however it counts every line
                        count++;
                    }
                }
                printf("There are %d lines in this file\n",count);//Outputs the result to the reader
                fclose(file);
            }
        }
        else if (choose==4){
            printf("Which special operation would you like to do. 1.Copy line from file to another 2. Display the size of a File\n");
            scanf("%d",&fChoose); //Allow the user to perform a "special" operation
            fflush(stdin);
            if(fChoose==1){
                printf("Which file would you like to copy from?\n");
                scanf("%s",&fName); // The user can choose a file to copy a line from
                file = fopen(fName, "r");
                if(file == NULL){   // If the file is invalid
                    printf("Sorry that file is not recognised\n");
                }
                else{
                    printf("What line would you like to copy?\n");
                    int lineNum, count=1, test=0;
                    char cLine[100],nLine[100];
                    scanf("%d",&lineNum);//user can choose the line to copy
                    while(fgets(cLine, 100, file)){
                        if(count==lineNum){
                            for(int i=0;i<100;i++){//Copies the string over from the old file to a new character string
                                nLine[i]=cLine[i];
                            }
                            test++;
                        }
                        count++;
                    }
                    fclose(file);
                    if(test==0){//If the line inputed is not in the file
                        printf("Sorry that line is not in this file\n");
                        
                    }
                    else{
                        printf("Which file would you like to append this to?\n");
                        scanf("%s",fName); //Chosing the file to append the copied line to
                        file = fopen(fName, "r");
                        if(file == NULL){  //If file does not exist
                            printf("Sorry that file does not exist\n");
                            fclose(file);
                        }
                        else{
                            fclose(file);
                            file = fopen(fName,"a");
                            fprintf(file,"\n%s",nLine);//Prints the line to the file
                            fclose(file);
                        }
                    }
                }
            }
            else if(fChoose==2){
                printf("Which file would you like to find the size of?\n");
                scanf("%s",&fName);//File to find size of
                fflush(stdin);
                file = fopen(fName,"r");
                if(file==NULL){//If the file does not exist
                    printf("Sorry that file does not exist\n");
                    fclose(file);
                }
                else{
                    
                    int fileSize;
                    fseek(file, 0, SEEK_END);
                    fileSize = ftell(file);
                    fclose(file);
                    
                    printf("The size of this file is %d bytes\n",fileSize);//Outputs the size of the file.
                }
            }
        }
        else if (choose==5){//If the user wants to terminate the program
            choice++;
        }
        else{               //If the user did not enter a valid number.
            printf("please enter a valid Number\n");
        }
    }
}