#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 100
#define NUMBER_OF_SONGS 25
struct song_details
{
 char name[SIZE];
 char singer[SIZE];
 char lyricist[SIZE];
 char album[SIZE];
 char composer[SIZE];
 char genre[SIZE];
 char duration[5];
};

typedef struct playlist_tag
{
    struct song_details song;
    struct playlist_tag *prev;
    struct playlist_tag *next;
}playlist;

//Helper function
void printDetails(playlist* ptr)
{
  if(ptr != NULL)
  {
    printf("Name : %s",ptr->song.name);
    printf("Singer : %s",ptr->song.singer);
    printf("Lyricist : %s",ptr->song.lyricist);
    printf("Album : %s",ptr->song.album);
    printf("Composer : %s",ptr->song.composer);
    printf("Genre : %s",ptr->song.genre);
    printf("Duration : %s",ptr->song.duration);
  }
  printf("\n");
}

//Helper function
void printPlaylist(playlist *firstSong)
{
    playlist *currSong = firstSong;
    int i=1;
    while(currSong != NULL)
    {
    printf("%d\n",i++);
    printDetails(currSong);
    currSong = currSong->next;
    }
}

//Helper function
playlist* createNode_file(FILE *fptr)
{
      playlist *newSong;
      newSong = (playlist*) malloc(sizeof(playlist));
      newSong->prev=NULL;
      newSong->next=NULL;
      fgets(newSong->song.name,SIZE,fptr);
      fgets(newSong->song.singer,SIZE,fptr);
      fgets(newSong->song.lyricist,SIZE,fptr);
      fgets(newSong->song.album,SIZE,fptr);
      fgets(newSong->song.composer,SIZE,fptr);
      fgets(newSong->song.genre,SIZE,fptr);
      fgets(newSong->song.duration,SIZE,fptr);
      return newSong;
}

//Helper function
playlist* initializePlaylist()
{
    playlist *head = NULL;
    FILE *fptr;
    fptr = fopen("dspd_input.txt","r");
    if(fptr == NULL)
    {
        printf("file doesn't exist\n");
    }
    else
    {
    playlist *tail;
    tail = NULL;
    for(int i=0; i<NUMBER_OF_SONGS; i++)
    {
      playlist *newSong = createNode_file(fptr);
      if(head == NULL)
      {
        head = tail = newSong;
      }
      else
      {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
      }
    }
    }
    return head;
}
//Helper function
playlist* createNode()
{
      playlist* newSong = NULL; 
      newSong = (playlist*) malloc(sizeof(playlist));
      newSong->prev=NULL;
      newSong->next=NULL;
      fflush(stdin);
      printf("Enter name of the song : ");
      fgets(newSong->song.name,SIZE,stdin);
      printf("Enter name of the singer : ");
      fgets(newSong->song.singer,SIZE,stdin);
      printf("Enter name of the lyricist: ");
      fgets(newSong->song.lyricist,SIZE,stdin);
      printf("Enter name of the album : ");
      fgets(newSong->song.album,SIZE,stdin);
      printf("Enter name of the composer: ");
      fgets(newSong->song.composer,SIZE,stdin);
      printf("Enter genre of the song : ");
      fgets(newSong->song.genre,SIZE,stdin);
      printf("Enter duration of the song : ");
      fgets(newSong->song.duration,SIZE,stdin);
      return newSong; 
}

//1st question
playlist* insertSong(playlist* head)
{
   playlist *newSong = createNode(); 
   if(head == NULL)
      {
        head = newSong;
      }
      else
      {
       playlist *ptr = head;
       while(ptr->next != NULL)
       {
        ptr = ptr->next;
       }
       newSong->prev = ptr;
       ptr->next = newSong;
      }
      return head;
}

//2nd question
void removeDuplicates(playlist* head)
{
 if(head != NULL && head->next != NULL)
 {
   playlist *prev,*curr;
   prev = head;
   curr = head->next;
   while(curr != NULL)
   {
    if((strcmp(head->song.name,curr->song.name)==0) && (strcmp(head->song.singer,curr->song.singer)==0) && (strcmp(head->song.lyricist,curr->song.lyricist)==0) && (strcmp(head->song.album,curr->song.album)==0) && (strcmp(head->song.composer,curr->song.composer)==0) && (strcmp(head->song.genre,curr->song.genre)==0) && (strcmp(head->song.duration,curr->song.duration)==0))
    {
      prev->next = curr->next;
      if(curr->next != NULL)
      {
        curr->next->prev = prev;
      }
      playlist *temp = curr;
      curr = curr->next;
      free(temp);
    }
    prev = curr;
    if(curr != NULL)
    {
    curr = curr->next; 
    }   
   }

   removeDuplicates(head->next);
 }
}

//3
void printPlaylist_ascending(playlist *head)
{
  if(head != NULL)
  {
    printDetails(head);
    printPlaylist_ascending(head->next);
  }
}

void printPlaylist_descending(playlist *head)
{
    
    if(head != NULL)
    {
    printPlaylist_descending(head->next);   
    printDetails(head);
    }
    
}

//4 question part 1
playlist* DeleteSong_songNameAtrribute(playlist* myPlaylist)
{
  char song_name[SIZE];
  fflush(stdin);
  printf("Enter name of the song which is to be deleted: ");
  fgets(song_name,SIZE,stdin);
  if(myPlaylist != NULL)
  {
    playlist *prev=NULL,*curr=myPlaylist;
    while(curr != NULL)
    {
      if(strcmp(curr->song.name,song_name)==0)
      {
        if(prev == NULL)
        {
          myPlaylist = myPlaylist->next;
          myPlaylist->prev=NULL;
          free(curr);
          curr = myPlaylist;
        }
        else
        {
          prev->next = curr->next;
          if(curr->next != NULL)
          {
            curr->next->prev = prev;
          }
          free(curr);
          curr=prev->next;
        }
      }
      else
      {
        prev = curr;
        curr = curr->next;
      }
    }
  }
return myPlaylist;
}

//pending
//Question 4 part 2
playlist* DeleteSong_artistAtrribute(playlist* myPlaylist)
{
  char artist_name[SIZE];
  fflush(stdin);
  printf("Enter artist name whose songs to be deleted : ");
  fgets(artist_name,SIZE,stdin);
  if(myPlaylist != NULL)
  {
    playlist *prev=NULL,*curr=myPlaylist;
    while(curr != NULL)
    {
      if((strcmp(curr->song.singer,artist_name)==0)||(strcmp(curr->song.lyricist,artist_name)==0)||(strcmp(curr->song.composer,artist_name)==0))
      {
        if(prev == NULL)
        {
          myPlaylist = myPlaylist->next;
          myPlaylist->prev=NULL;
          free(curr);
          curr = myPlaylist;
        }
        else
        {
          prev->next = curr->next;
          if(curr->next != NULL)
          {
            curr->next->prev = prev;
          }
          free(curr);
          curr=prev->next;
        }
      }
      else
      {
        prev = curr;
        curr = curr->next;
      }
    }
  }
return myPlaylist;
}

//Helper function
playlist* copyPlaylist(playlist *ptr1)
{
      char name[SIZE],singer[SIZE],lyricist[SIZE],album[SIZE],composer[SIZE],genre[SIZE],duration[SIZE];
      playlist *Node;
      Node =(playlist*) malloc(sizeof(playlist));
      strcpy(name,ptr1->song.name);
      strcpy(Node->song.name,name);
      fflush(stdin);
      strcpy(singer,ptr1->song.singer);
      strcpy(Node->song.singer,singer);
      fflush(stdin);
      strcpy(lyricist,ptr1->song.lyricist);
      strcpy(Node->song.lyricist,lyricist);
      fflush(stdin);
      strcpy(album,ptr1->song.album);
      strcpy(Node->song.album,album);
      fflush(stdin);
      strcpy(composer,ptr1->song.composer);
      strcpy(Node->song.composer,composer);
      fflush(stdin);
      strcpy(genre,ptr1->song.genre);
      strcpy(Node->song.genre,genre);
      fflush(stdin);
      strcpy(duration,ptr1->song.duration);
      strcpy(Node->song.duration,duration);
   return Node;
}

//Helper function
int lenghtOfLL(playlist* myPlaylist)
{
  int n;
  if(myPlaylist == NULL)
  {
    n=0;
  }
  else
  {
    n=lenghtOfLL(myPlaylist->next)+1;
  }
  return n;
}

//Helper function
playlist* Sort(playlist* myPlaylist)
{
 if(myPlaylist != NULL && myPlaylist->next != NULL)
 {
  int i=0;
  int n = lenghtOfLL(myPlaylist);
  while(i<=n)
  {
    playlist *prev=NULL,*curr= myPlaylist,*next = myPlaylist->next;
    while(curr != NULL && next != NULL) 
    {
      int j=0,sorted1=1,sorted2=0;
      while(curr->song.name[j] != '\0' && next->song.name[j] != '\0' && sorted1==1 && sorted2==0)
      {
        if(curr->song.name[j]-next->song.name[j] > 0 )
        {
          sorted2 = 1;
        }
        else if(curr->song.name[j]-next->song.name[j] < 0)
        {
          sorted1=0;
        }
        j++;
      }
      if(sorted2 == 1)
      {
          curr->next=next->next;
          if(next->next != NULL)
          {
            next->next->prev = curr;
          }
          curr->prev=next;
          next->next=curr;
          next->prev=prev;
          
        if(prev == NULL)
        {
         myPlaylist = next;
         prev = myPlaylist;
         next = curr->next; 
        }
        else
        {
         prev->next = next;
         prev=next;
         next=curr->next;
        }
      }
      else if(sorted1==0 || ((sorted1==1 && sorted2==0)))
      {
        prev=curr;
        curr=next;
        next=next->next;
      }
      
    }
    i++;
  }
 }
 return myPlaylist;
}

//5th question
void SortedPlaylistWithGivenAttributes(playlist *myPlaylist)
{
  int num_of_attributes;
  printf("Enter number of attributes : ");
  scanf("%d",&num_of_attributes);
  char **attribute ,**attribute_name;
  attribute= (char**) malloc(sizeof(char*)*num_of_attributes);
  attribute_name= (char**) malloc(sizeof(char*)*num_of_attributes);
  for(int i=0; i<num_of_attributes; i++)
  {
   attribute[i] = (char*) malloc(sizeof(char)*SIZE);
   attribute_name[i] = (char*) malloc(sizeof(char)*SIZE);
  }
  
  for(int i=0;i<num_of_attributes;i++)
  {
    printf("Enter attribute : ");
    fflush(stdin);
    fgets(attribute[i],SIZE,stdin);
    printf("Enter attribute name: ");
    fgets(attribute_name[i],SIZE,stdin);
  }

  playlist *ptr = myPlaylist,*head,*tail;
  head = tail = NULL;
  while(ptr != NULL)
  {
    int attributes_count = 0;
    for(int i=0; i<num_of_attributes;i++)
    {
      if((strcmp(attribute[i],"singer\n")==0) &&(strcmp(attribute_name[i],ptr->song.singer)==0))
      {
         attributes_count++;
      }
      else if((strcmp(attribute[i],"album\n")==0) &&(strcmp(attribute_name[i],ptr->song.album)==0))
      {
        attributes_count++;
      }
      else if((strcmp(attribute[i],"lyricist\n")==0) &&(strcmp(attribute_name[i],ptr->song.lyricist)==0))
      {
        attributes_count++;
      }
      else if((strcmp(attribute[i],"genre\n")==0) &&(strcmp(attribute_name[i],ptr->song.genre)==0))
      {
        attributes_count++;
      }
      else if((strcmp(attribute[i],"composer\n")==0) &&(strcmp(attribute_name[i],ptr->song.composer)==0))
      {
       attributes_count++; 
      }
    }
    if(attributes_count == num_of_attributes)
    {
      playlist *newNode = copyPlaylist(ptr);
      newNode->next = newNode->prev = NULL;
      if(head == NULL)
      {
        head = tail = newNode;
      }
      else
      {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
      }
    }
    ptr = ptr->next;
  }
  head = Sort(head);
  printPlaylist(head);
}

//6th question
 void DisplayASong(playlist* myPlaylist)
 {
  int serial_number;
  printf("Enter the serial number of the song: \n");
  scanf("%d",&serial_number);
  int i=1;
  playlist *ptr=myPlaylist;
  while(i != serial_number && ptr!=NULL)
  {
    i++;
    ptr=ptr->next;
  }
  if(ptr == NULL)
  {
    printf("Invalid serial number\n");
  }
  else
  {
    if(ptr->prev==NULL && ptr->next==NULL)//only one song in the playlist
    {
         printf("Your desired song is %s\n",ptr->song.name);
         printf("Details of song : \n");
         printDetails(ptr);
    }
    else if(ptr->prev==NULL && ptr->next != NULL)
    {
      printf("Enjoy listening first song in the playlist\n");
      printf("Your desired song is %s\n",ptr->song.name);
      printf("Details of song : \n");
      printDetails(ptr);
      printf("Your next song is %s\n",ptr->next->song.name);
    }
    else if(ptr->prev!=NULL && ptr->next != NULL)
    {
      printf("Enjoy listening %d song in the playlist\n",serial_number);
      printf("Your desired song is %s\n",ptr->song.name);
      printf("Details of song : \n");
      printDetails(ptr);
      printf("Your previous song is %s\n",ptr->prev->song.name);
      printf("Your next song is %s\n",ptr->next->song.name);
    }
    else
    {
      printf("Enjoy listening last song in the playlist\n");
      printf("Your desired song is %s\n",ptr->song.name);
      printf("Details of song : \n");
      printDetails(ptr);
      printf("Your previous song is %s\n",ptr->prev->song.name);
    }
  }

  if(ptr != NULL)
  {
  char option[SIZE];
  printf("Enter if you want to listen to previous or next song : ");
  scanf("%s",option);
  if(strcmp(option,"prev")==0)
  {
    if(ptr->prev != NULL)
    {
       printf("Your desired previous song is %s\n",ptr->prev->song.name);
       printf("Details of song : \n");
       printDetails(ptr->prev);
    }
    else
    {
       printf("Oops!! song not found\n");
    }
  }
  else if(strcmp(option,"next")==0)
  {
     if(ptr->next != NULL)
    {
       printf("Your desired next song is %s\n",ptr->next->song.name);
       printf("Details of song : \n");
       printDetails(ptr->next);
    }
    else
    {
       printf("Oops!! song not found\n");
    }   
  }
  else
  {
     printf("Please enter valid option\n");
  }
  }
 }

//7th question
void DisplayDetailsOfKthSong(playlist* myPlaylist)
{
  int serial_number;
  printf("Enter the serial number of the song: \n");
  scanf("%d",&serial_number);
  int i=1;
  playlist *ptr=myPlaylist;
  while(i != serial_number && ptr!=NULL)
  {
    i++;
    ptr=ptr->next;
  }

  if(ptr == NULL)
  {
    printf("Invalid serial number\n");
  }
  else
  {
    printf("%d song in playlist\n",serial_number);
    printDetails(ptr);
  }

  if(ptr != NULL)
  {
  int offset;
  char direction[SIZE];
  printf("Enter value of offset : \n");
  scanf("%d",&offset);
  printf("Enter the direction : \n");
  scanf("%s",direction);
  if(strcmp(direction,"up") == 0)
  {
   playlist *lptr = ptr->prev;
   while(lptr != NULL && offset != 1)
   {
    offset--;
    lptr = lptr->prev;
   }
   if(lptr != NULL)
   {
    printDetails(lptr);
   }
   else
   {
    printf("Invalid offset\n");
   }
  }
  else if(strcmp(direction,"down") == 0)
  {
   playlist *lptr = ptr->next;
   while(lptr != NULL && offset != 1)
   {
    offset--;
    lptr = lptr->next;
   }
   if(lptr != NULL)
   {
    printDetails(lptr);
   }
   else
   {
    printf("Invalid offset\n");
   }
  }
  else
  {
    printf("Invalid direction\n");
  }
  }
}

//8th question
void PlaylistWithAttributesOfGivenSong(playlist* myPlaylist)
{
  int serial_number;
  printf("Enter serial number: ");
  scanf("%d",&serial_number);
  playlist *lptr = myPlaylist;
  while(lptr != NULL && serial_number != 1)
  {
    serial_number--;
    lptr = lptr->next;
  }
  if(lptr == NULL)
  {
    printf("Invalid serial number\nCannot create playlist\n");
  }
  else
  {
  printDetails(lptr);
  int num_of_attributes;
  printf("Enter number of attributes : ");
  scanf("%d",&num_of_attributes);
  char **attribute ,**attribute_name;
  attribute= (char**) malloc(sizeof(char*)*num_of_attributes);
  attribute_name= (char**) malloc(sizeof(char*)*num_of_attributes);
  for(int i=0; i<num_of_attributes; i++)
  {
   attribute[i] = (char*) malloc(sizeof(char)*SIZE);
   attribute_name[i] = (char*) malloc(sizeof(char)*SIZE);
  }
  
  for(int i=0;i<num_of_attributes;i++)
  {
    printf("Enter attribute : ");
    fflush(stdin);
    fgets(attribute[i],SIZE,stdin);

      if((strcmp(attribute[i],"singer\n")==0) )
      {
        fflush(stdin);
         strcpy(attribute_name[i],lptr->song.singer);
      }
      else if((strcmp(attribute[i],"album\n")==0))
      {
        fflush(stdin);
        strcpy(attribute_name[i],lptr->song.album);
      }
      else if((strcmp(attribute[i],"lyricist\n")==0))
      {
        fflush(stdin);
        strcpy(attribute_name[i],lptr->song.lyricist);
      }
      else if((strcmp(attribute[i],"genre\n")==0))
      {
        fflush(stdin);
        strcpy(attribute_name[i],lptr->song.genre);
      }
      else if((strcmp(attribute[i],"composer\n")==0))
      {
        fflush(stdin);
       strcpy(attribute_name[i],lptr->song.composer); 
      }
  }

  playlist *ptr = myPlaylist,*head,*tail;
  head = tail = NULL;
  while(ptr != NULL)
  {
    int attributes_count = 0;
    for(int i=0; i<num_of_attributes;i++)
    {
      if((strcmp(attribute[i],"singer\n")==0) &&(strcmp(attribute_name[i],ptr->song.singer)==0))
      {
         attributes_count++;
      }
      else if((strcmp(attribute[i],"album\n")==0) &&(strcmp(attribute_name[i],ptr->song.album)==0))
      {
        attributes_count++;
      }
      else if((strcmp(attribute[i],"lyricist\n")==0) &&(strcmp(attribute_name[i],ptr->song.lyricist)==0))
      {
        attributes_count++;
      }
      else if((strcmp(attribute[i],"genre\n")==0) &&(strcmp(attribute_name[i],ptr->song.genre)==0))
      {
        attributes_count++;
      }
      else if((strcmp(attribute[i],"composer\n")==0) &&(strcmp(attribute_name[i],ptr->song.composer)==0))
      {
       attributes_count++; 
      }
    }
    if(attributes_count == num_of_attributes)
    {
      playlist *newNode = copyPlaylist(ptr);
      newNode->next = newNode->prev = NULL;
      if(head == NULL)
      {
        head = tail = newNode;
      }
      else
      {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
      }
    }
    ptr = ptr->next;
  }
 printPlaylist(head);
  }
}

//9th question
void FilterPlaylist(playlist *myPlaylist)
{
  int num_of_attributes = 2;
  char **attribute ,**attribute_name;
  attribute= (char**) malloc(sizeof(char*)*num_of_attributes);
  attribute_name= (char**) malloc(sizeof(char*)*num_of_attributes);
  for(int i=0; i<num_of_attributes; i++)
  {
   attribute[i] = (char*) malloc(sizeof(char)*SIZE);
   attribute_name[i] = (char*) malloc(sizeof(char)*SIZE);
  }
  
  for(int i=0;i<num_of_attributes;i++)
  {
    printf("Enter attribute : ");
    fflush(stdin);
    fgets(attribute[i],SIZE,stdin);
    printf("Enter attribute name: ");
    fgets(attribute_name[i],SIZE,stdin);
  }

  playlist *ptr1 = myPlaylist,*head1,*tail1;
  head1 = tail1 = NULL;
  while(ptr1 != NULL)
  {
      int attributes_count=0;
      if((strcmp(attribute[0],"singer\n")==0) &&(strcmp(attribute_name[0],ptr1->song.singer)==0))
      {
         attributes_count++;
      }
      else if((strcmp(attribute[0],"album\n")==0) &&(strcmp(attribute_name[0],ptr1->song.album)==0))
      {
        attributes_count++;
      }
      else if((strcmp(attribute[0],"lyricist\n")==0) &&(strcmp(attribute_name[0],ptr1->song.lyricist)==0))
      {
        attributes_count++;
      }
      else if((strcmp(attribute[0],"genre\n")==0) &&(strcmp(attribute_name[0],ptr1->song.genre)==0))
      {
        attributes_count++;
      }
      else if((strcmp(attribute[0],"composer\n")==0) &&(strcmp(attribute_name[0],ptr1->song.composer)==0))
      {
       attributes_count++; 
      }
      if(attributes_count == 1)
      {
      playlist *newNode = copyPlaylist(ptr1);
      newNode->next = newNode->prev = NULL;
      if(head1 == NULL)
      {
        head1 = tail1 = newNode;
      }
      else
      {
        tail1->next = newNode;
        newNode->prev = tail1;
        tail1 = newNode;
      }
    }
    ptr1 = ptr1->next;
    }

  playlist *ptr2 = head1,*head2,*tail2;
  head2 = tail2 = NULL;
  while(ptr2 != NULL)
  {
      int attributes_count=0;
      if((strcmp(attribute[1],"singer\n")==0) &&(strcmp(attribute_name[1],ptr2->song.singer)==0))
      {
         attributes_count++;
      }
      else if((strcmp(attribute[1],"album\n")==0) &&(strcmp(attribute_name[1],ptr2->song.album)==0))
      {
        attributes_count++;
      }
      else if((strcmp(attribute[1],"lyricist\n")==0) &&(strcmp(attribute_name[1],ptr2->song.lyricist)==0))
      {
        attributes_count++;
      }
      else if((strcmp(attribute[1],"genre\n")==0) &&(strcmp(attribute_name[1],ptr2->song.genre)==0))
      {
        attributes_count++;
      }
      else if((strcmp(attribute[1],"composer\n")==0) &&(strcmp(attribute_name[1],ptr2->song.composer)==0))
      {
       attributes_count++; 
      }
      if(attributes_count == 1)
      {
      playlist *newNode = copyPlaylist(ptr2);
      newNode->next = newNode->prev = NULL;
      if(head2 == NULL)
      {
        head2 = tail2 = newNode;
      }
      else
      {
        tail2->next = newNode;
        newNode->prev = tail2;
        tail2 = newNode;
      }
    }
    ptr2 = ptr2->next;
    }
    printPlaylist(head2);
}

//10th question
void printKTimes(playlist* myPlaylist)
{
  int k;
  printf("Enter value of k : ");
  scanf("%d",&k);

  while(k != 0)
  {
    printf("Enjoying listening the songs\n");
    playlist *ptr = myPlaylist;
    while(ptr != NULL)
    {
      printDetails(ptr);
      ptr = ptr->next;
    }
    k--;
     printf("Thank you for listening\n");
  }
 
}

//11th Question
playlist* shuffle(playlist* myPlaylist)
{
  printf("Enter number of attributes\n");
  int num_of_attributes;
  scanf("%d",&num_of_attributes);
  char **attributes,**attribute_name;
  attributes =(char**)malloc(sizeof(char*)*num_of_attributes);
  attribute_name =(char**)malloc(sizeof(char*)*num_of_attributes);
  for(int i=0; i<num_of_attributes; i++)
  {
    attributes[i] = (char*)malloc(sizeof(char)*SIZE);
    attribute_name[i] =(char*)malloc(sizeof(char)*SIZE);
  }
  for(int i=0; i<num_of_attributes; i++)
  {
    fflush(stdin);
    printf("Enter attribute : ");
    fgets(attributes[i],SIZE,stdin);
    fflush(stdin);
    printf("Enter attribute name : ");
    fgets(attribute_name[i],SIZE,stdin);
  }

  int flag = 0;
  playlist *ptr = myPlaylist,*prev=NULL;
  playlist *randomListHead,*randomListTail,*randomPrev;
  randomListHead = randomListTail = randomPrev = NULL;
  while(ptr != NULL && ptr->next != NULL)
  {
    int count=0;
    for(int i=0; i<num_of_attributes; i++)
    {
      if((strcmp(attributes[i],"name\n")==0)&&strcmp(ptr->song.name,attribute_name[i])==0)
      {
       count++;
      }
      else if((strcmp(attributes[i],"singer\n")==0)&&strcmp(ptr->song.singer,attribute_name[i])==0)
      {
       count++;
      }
      else if((strcmp(attributes[i],"lyricist\n")==0)&&strcmp(ptr->song.lyricist,attribute_name[i])==0)
      {
       count++;
      }
      else if((strcmp(attributes[i],"album\n")==0)&&strcmp(ptr->song.album,attribute_name[i])==0)
      {
       count++;
      }
      else if((strcmp(attributes[i],"composer\n")==0)&&strcmp(ptr->song.composer,attribute_name[i])==0)
      {
       count++;
      }
      else if((strcmp(attributes[i],"genre\n")==0)&&strcmp(ptr->song.genre,attribute_name[i])==0)
      {
       count++;
      }
      else if((strcmp(attributes[i],"duration\n")==0)&&strcmp(ptr->song.duration,attribute_name[i])==0)
      {
       count++;
      }
    }
    if(count == num_of_attributes && flag==0)
    {
      randomPrev = prev;
      randomListHead = randomListTail = ptr;
      flag = 1;
    }
    prev=ptr;
    ptr = ptr->next;
  }
  if(randomPrev == NULL)
  {
    myPlaylist = randomListHead->next;
    myPlaylist->prev = NULL;
  }
  else
  {
    
    if(randomListHead->next != NULL)
    {
    randomPrev->next = randomListHead->next;
    randomListHead->next->prev = randomPrev;
    }
  }
  if(randomListHead->next != NULL)
  {
  ptr->next = randomListHead;
  randomListHead->prev = ptr;
  randomListHead->next = NULL;
  }

 int upper = NUMBER_OF_SONGS-1,lower=1;
 srand(time(0));
 for(int i=1; i<NUMBER_OF_SONGS; i++)
 { 
  int num = rand();
  int random_num = (num%(upper-lower+1))+1;
  playlist *ptr=myPlaylist,*prev=NULL;
  int j=1;
  while(ptr != NULL && j<random_num)
  {
   prev = ptr;
   ptr = ptr->next;
   j++;
  }
  if(ptr != NULL && j == random_num)
  {
    if(prev == NULL)
    {
      myPlaylist = ptr->next;
      myPlaylist->prev=NULL;
    }
    else
    {     
      if(ptr->next != NULL)
      {
        prev->next = ptr->next;
        ptr->next->prev = prev;
      }
    }
    ptr->prev = randomListTail;
    ptr->next=NULL;
    randomListTail = randomListTail->next = ptr;   
  }
  upper--;
 }
  return randomListHead;
}
int main ()
{
 playlist *myPlaylist = initializePlaylist();

 int question;
 printf("Enter question number to be checked : ");
 scanf("%d",&question);

 switch(question)
 {
  case 1 :
  {
    myPlaylist = insertSong(myPlaylist);
    printPlaylist(myPlaylist);
    break;
  }
  case 2 :
  {
    removeDuplicates(myPlaylist);
    printPlaylist(myPlaylist);
    break;
  }
  case 3 :
  {
   myPlaylist = Sort(myPlaylist);
   printf("Hey I am playing your songs in ascending order\n");
   printPlaylist_ascending(myPlaylist);
   printf("Hey I am playing your songs in descending order\n");
   printPlaylist_descending(myPlaylist); 
   break;
  }
  case 4 :
  {
    myPlaylist = DeleteSong_songNameAtrribute(myPlaylist);
     printPlaylist(myPlaylist);
    myPlaylist = DeleteSong_artistAtrribute(myPlaylist);
     printPlaylist(myPlaylist);
     break;
  }
  case 5:
  {
    SortedPlaylistWithGivenAttributes(myPlaylist);
    break;
  }
  case 6:
  {
    printPlaylist(myPlaylist);
    DisplayASong(myPlaylist);
    break;
  }
  case 7:
  {
    DisplayDetailsOfKthSong(myPlaylist);
    break;
  }
  case 8:
  {
    PlaylistWithAttributesOfGivenSong(myPlaylist);
    break;
  }
  case 9:
  {
    FilterPlaylist(myPlaylist);
    break;
  }
  case 10:
  {
    printKTimes(myPlaylist);
    break;
  }
  case 11:
  {
    myPlaylist = shuffle(myPlaylist);
    printPlaylist_ascending(myPlaylist);
    break;
  }
 }
}
