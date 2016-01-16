//
//  main.c
//  Metro Planner
//
//  Created by Sushant Patil on 06/12/15.
//  Copyright © 2015 Sushant Patil. All rights reserved.
//

//Approach : This project impolements Djkstar's algorithm to find the shortest path between two stations.
// I first create unique IDs for every single cost mentioned in the text file. Every travel cost has an endpoint,
//e.g Every node has start & stop as points on the graph. So the node has 3 attributes :
// Name Of the Station, Name of the line colour & it's state (start or stop)

//With this approach I first create unique IDs for every cost & then I fill the cost matrix by reading the costs.

//In the end I output the file which has all the stations mentioned in the itinerary.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//IN for Infinity
#define IN 9999

//N is the total number of points, which are possible without any duplication.
#define N 292

//Structure to store node information
typedef struct station
{
    char name[100];
    char line[30];
    char state[50]; //This string has value either "start" or "stop"

} STN;

//Node Information Array
STN All_Costs[N];

//Unique cost_id for every cost
int cost_id=0;

//Global cost matrix
int cost[N][N];

//Read one word at a time
char *read_nxt_word(FILE *fp)
{

    char c = '\0';
    static char word[100];
    
    c = fscanf(fp,"%s", word);
    if (c == EOF)
    {
        printf("File complete");
        return NULL;
    }
    return word;

}

//To check if a string is line_name or not
int is_it_a_line(char *word)
{
    char *lines[] = {"green", "yellow", "blue", "silver", "orange", "red"};
    
    int i=0;
    
    for (i=0;i<6; i++)
    {
        if(strcmp(word, lines[i])==0)
        {
            return 1;
        }
        
    }
    
    return 0;
}


//Djstra's Algorithm
// source, target, file on which output is to be written, the format of output = 0 to print on the screen, 1 to write it in the file
int dijsktra(int source,int target, FILE *fp, int output_format)
{
    int dist[N],prev[N],selected[N]={0},i,m,min,start,d,j;
    int path[N]={'\0'};
    for(i=1;i< N;i++)
    {
        dist[i] = IN;
        prev[i] = -1;
    }
    start = source;
    selected[start]=1;
    dist[start] = 0;
    while(selected[target] ==0)
    {
        min = IN;
        m = 0;
        for(i=1;i< N;i++)
        {
            d = dist[start] +cost[start][i];
            if(d< dist[i]&&selected[i]==0)
            {
                dist[i] = d;
                prev[i] = start;
            }
            if(min>dist[i] && selected[i]==0)
            {
                min = dist[i];
                m = i;
            }
        }
        start = m;
        selected[start] = 1;
    }
    start = target;
    j = 0;
    while(start != -1)
    {
        
        path[j++] = start;
        start = prev[start];
    }
    
    i=j;
    j=0;
    
    int travel_station_cnt=1;
    int aInt_1 = travel_station_cnt;
    char str_3[15];
    sprintf(str_3, "%d", aInt_1);
    
    
    printf("\n");
    
    while (j<i)
    {
        
        if (j>=1)
        {
            
            if(strcmp(All_Costs[path[j]].line, All_Costs[path[j-1]].line)!=0)
            {
                
                if (output_format==0)
                    printf("\nChange the line to %s\n", All_Costs[path[j]].line);
                if (output_format==1)
                {
                    fputs("Travel ", fp);
                    
                    aInt_1 = (travel_station_cnt+1)/2;
                    sprintf(str_3, "%d", aInt_1);
                    
                    fputs(str_3, fp);
                    fputs(" stations ", fp);
                    
                    fputs("to change the line to ", fp);
                    fputs(All_Costs[path[j]].line, fp);
                    fputs(" on ", fp);
                    fputs(All_Costs[path[j]].name, fp);
                    fputs(" station", fp);
                    fputs("\n\n", fp);
                }
                
                travel_station_cnt=1;
            }
            else
                travel_station_cnt++;
        }
        
        if (output_format==0)
        {
            printf("%s ",All_Costs[path[j]].name);
            printf("%s ",All_Costs[path[j]].line);
            printf("%s ",All_Costs[path[j]].state);
            printf("\n");
        }
            
        if (output_format==1)
        {
            fputs(All_Costs[path[j]].name, fp);
            fputs(" ", fp);
            fputs(All_Costs[path[j]].line, fp);
            fputs(" ", fp);
            fputs(All_Costs[path[j]].state, fp);
            fputs(" ", fp);
            fputs("\n", fp);
         }
        
        
        
        
        j++;
    }
    
    int aInt = dist[target]/60;
    char str_1[15];
    sprintf(str_1, "%d", aInt);
    
    aInt = dist[target]- (dist[target]/60)*60;
    char str_2[15];
    sprintf(str_2, "%d", aInt);
    
    
    if (output_format==1)
    {
        fputs("\nYou will reach your destination in ", fp);
        fputs(str_1, fp);
        fputs(" minutes & ", fp);
        fputs(str_2, fp);
        fputs(" seconds", fp);
    }
    
    return dist[target];
}

//add cost by finding src ID & destination ID in the cost matrix
void add_cost(char *src_station_name, char *src_station_line, char *src_station_state,char *dst_station_name, char *dst_station_line, char *dst_station_state, int travel_cost)

{
    
    int i=0, src_cost_id=0, dst_cost_id = 0, co;
    
    for (i=0; i<N; i++)
    {
        if (strcmp(src_station_name, All_Costs[i].name)==0)
        {
            if (strcmp(src_station_line, All_Costs[i].line)==0)
            {
                if (strcmp(src_station_state,All_Costs[i].state)==0)
                {
                    src_cost_id = i;
                    break;
                }
            }
        }
    }
    
    
    
    for (i=0; i<N; i++)
    {
        if (strcmp(dst_station_name, All_Costs[i].name)==0)
        {
            if (strcmp(dst_station_line,All_Costs[i].line)==0)
            {
                if (strcmp(dst_station_state,All_Costs[i].state)==0)
                {
                    dst_cost_id = i;
                    break;
                }
            }
        }
    }
    
    cost[src_cost_id][dst_cost_id] = cost[dst_cost_id][src_cost_id] = travel_cost;
    
    
}

//Function to ensure unique ID creation
void add_valid_cost_ID(char *station_name, char *line_colour, char *state)
{
    int i, a, b, c;
    
    if (cost_id==0)
    {
        strcpy(All_Costs[cost_id].name,station_name);
        strcpy(All_Costs[cost_id].line,line_colour);
        strcpy(All_Costs[cost_id].state,state);
        cost_id++;
    }
    
    else
    {
        for (i=0; i<cost_id; i++)
        {
            a = strcmp(station_name, All_Costs[i].name);
            b = strcmp(line_colour, All_Costs[i].line);
            c = strcmp(state,All_Costs[i].state);
            
                    if (!a && !b && !c == 1)
                    {
                        return;
                    }
            
            
        }
        
        strcpy(All_Costs[cost_id].name,station_name);
        strcpy(All_Costs[cost_id].line,line_colour);
        strcpy(All_Costs[cost_id].state,state);
        cost_id++;

    }

}


////Create array of all information of the nodes
void create_IDs(char *line, FILE *fp)
{
    int i,j, num, num_str;
    char no_of_station_str[3];
    char cur_station_name[100] = {'\0'};
    
    no_of_station_str[2] = '\0';
    
    int no_of_station_int = 0;
    int each_station_cost_cnt=0;
    
    char *word='\0';
    char colour[10] = {'\0'};
    int cost_cnt =0;
    
    int station_cnt=0;
    int last_hop_cost_1 = 0, last_hop_cost_2=0;
    
    
    
    
    //reach till the colour name
    do
    {
        word = read_nxt_word(fp);
    }while (!(is_it_a_line(line)));
    
    //read how many number of stations in the line
    word = read_nxt_word(fp);
    no_of_station_str[0] = word[1];
    no_of_station_str[1] = word[2];
    
    no_of_station_int = atoi(no_of_station_str);
    
    
    do
    {
        word = read_nxt_word(fp);
        num_str = atoi(word);
        
        
        if (is_it_a_line(word))
        {
            strcpy(colour,word);
        }
        
        
        if (!(is_it_a_line(word)))
        {
            
            if (strlen(word)>1 && num_str == 0)
            {
                printf("\nThe station name is : %s", word);
                strcpy(cur_station_name, word);
                
                station_cnt++;
                each_station_cost_cnt =0;
            }
            
            else
            {
                num = atoi(word);
                
                each_station_cost_cnt++;
                
                
                
                if (each_station_cost_cnt==1)
                {
                    if (station_cnt==1)
                    {
                        
                        add_valid_cost_ID(cur_station_name,line, "start");
                    }
                    
                }
                
                if (each_station_cost_cnt==2)
                {
                    
                    if (station_cnt==1)
                    {
                        add_valid_cost_ID(cur_station_name,line,"stop");
                        
                    }
                    
                    else
                    {
                        add_valid_cost_ID(cur_station_name,line,"start");
                        
                    }
                }
                
                if (each_station_cost_cnt==3)
                {
                    if (station_cnt==1)
                    {
                        add_valid_cost_ID(cur_station_name,colour,"start");
                    }
                    
                    add_valid_cost_ID(cur_station_name,line,"stop");

                }
                
                if (each_station_cost_cnt >3)
                {
                    
                    add_valid_cost_ID(cur_station_name,colour,"start");
                    
                }
                cost_cnt++;
            }
            
        }
        
    }while (station_cnt < no_of_station_int);
    
    
    //Last two costs
    word = read_nxt_word(fp);
    strcpy(All_Costs[cost_id].name,cur_station_name);
    strcpy(All_Costs[cost_id].line,line);
    
    word = read_nxt_word(fp);
    cost_id++;
    cost_cnt++;
    num = atoi(word);
    
    strcpy(All_Costs[cost_id-1].state,"start");
    
    
    strcpy(All_Costs[cost_id].name,cur_station_name);
    strcpy(All_Costs[cost_id].line,line);
    strcpy(All_Costs[cost_id].state,"stop");
    
    
}



/////////////////////End of Create IDs////////////////////////////


//Function to fill the matrix with the costs
void fill_line_new(char *line, FILE *fp)
{
    int i,j, num, num_str;
    char no_of_station_str[3];
    char cur_station_name[100] = {'\0'};
    
    no_of_station_str[2] = '\0';
    
    int no_of_station_int = 0;
    int each_station_cost_cnt=0;
    
    char *word='\0';
    char colour[10] = {'\0'};
    int cost_cnt =0;
    
    char station_cnt=0;
    int last_hop_cost_1 = 0, last_hop_cost_2=0;
    
    char last_station_name_1[100]={'\0'}, last_station_name_2[100]={'\0'};
    
    
    //reach till the colour name
    do
    {
        word = read_nxt_word(fp);
    }while (!(is_it_a_line(line)));
    
    //read how many number of stations in the line
    word = read_nxt_word(fp);
    no_of_station_str[0] = word[1];
    no_of_station_str[1] = word[2];
    
    no_of_station_int = atoi(no_of_station_str);
    
    
    do
    {
        word = read_nxt_word(fp);
        num_str = atoi(word);
        
        
        if (is_it_a_line(word))
        {
            strcpy(colour,word);
        }
        
        
        if (!(is_it_a_line(word)))
        {
            
            if (strlen(word)>1 && num_str == 0)
            {
                strcpy(cur_station_name, word);
                
                strcpy(last_station_name_2, last_station_name_1);
                strcpy(last_station_name_1, cur_station_name);
                
                station_cnt++;
                each_station_cost_cnt =0;
            }
            
            else
            {
                num = atoi(word);
                
                each_station_cost_cnt++;
                
                
                if (each_station_cost_cnt==2)
                {
                    
                    if (station_cnt==1)
                    {
                        add_cost(cur_station_name, line, "start", cur_station_name, line, "stop", num);
                    }
                    
                    else
                    {
                        
                        last_hop_cost_2 = last_hop_cost_1;
                        last_hop_cost_1 = num;
                        
                        add_cost(last_station_name_2, line, "stop", last_station_name_1, line, "start", last_hop_cost_1 - last_hop_cost_2);
                        
                    }
                }
                
                if (each_station_cost_cnt==3)
                {
                    if (station_cnt==1)
                    {
                        
                        add_cost(cur_station_name, line, "start", cur_station_name, colour, "start", num);
                    }
                    else
                    {
                        add_cost(cur_station_name, line, "start", cur_station_name, line, "stop", num);
                    }
                    
                    
                }
                
                if (each_station_cost_cnt >3)
                {
                    
                    add_cost(cur_station_name, line, "start", cur_station_name, colour, "start", num);
                    
                }
                cost_cnt++;
            }
            
        }
        
    }while (station_cnt < no_of_station_int);
    
    
    //Last two costs
    strcpy(cur_station_name, word);
    word = read_nxt_word(fp);
    
    
    
    word = read_nxt_word(fp);
    
    cost_cnt++;
    num = atoi(word);
    last_hop_cost_2 = last_hop_cost_1;
    last_hop_cost_1 = num;
    
    
    add_cost(last_station_name_2, line, "start", cur_station_name, line, "start", last_hop_cost_1-last_hop_cost_2);
    
    add_cost(cur_station_name, line, "start", cur_station_name, line, "stop", 0);
    
}

//Function to find the cost using string inputs & not by cost_Ids
//output_format => 1 to write on file, 0 to print on the screen
int find_cost(char *src_station_name, char *src_station_line, char *src_station_state,char *dst_station_name, char *dst_station_line, char *dst_station_state, FILE *fp, int output_format)

{
    
    int i=0, src_cost_id=0, dst_cost_id = 0, co;
    
    for (i=0; i<N; i++)
    {
        if (strcmp(src_station_name, All_Costs[i].name)==0)
        {
            if (strcmp(src_station_line, All_Costs[i].line)==0)
            {
                if (strcmp(src_station_state,All_Costs[i].state)==0)
                {
                    src_cost_id = i;
                    break;
                }
            }
        }
    }
    
    
    
    for (i=0; i<N; i++)
    {
        if (strcmp(dst_station_name, All_Costs[i].name)==0)
        {
            if (strcmp(dst_station_line,All_Costs[i].line)==0)
            {
                if (strcmp(dst_station_state,All_Costs[i].state)==0)
                {
                    dst_cost_id = i;
                    break;
                }
            }
        }
    }
    
    printf("\nThe value of the source ID is : %d", src_cost_id);
    printf("\nThe value of the destination ID is : %d", dst_cost_id);
    
    
    if (src_cost_id==0)
    {
        src_cost_id=1;
    }
    
    if (dst_cost_id==0)
    {
        dst_cost_id=1;
    }
    
    co = dijsktra(src_cost_id,dst_cost_id, fp,output_format);
    printf("\nThe Shortest Path: %d",co);
    
    return co;
}

int main(int argc, const char * argv[])
{
    
    FILE *f = fopen("metro.txt", "r");
    FILE *fp_output = fopen(argv[1], "w");
    
    int i,j,k,co;
    
    
    char possible_origin_lines[6][30]= {'\0'};
    
    char source[100], destination[100];
    
    
    char *word;
    
    
    //initialize the matrix
    
    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {
            cost[i][j] = IN;
            if (i==j)
            {
                cost[i][j] = 0;
            }
        }
        
    }
    
    
    rewind(f);
    printf("\n");
    
    
    
    create_IDs("green", f);
    cost_id++;
    create_IDs("yellow", f);
    cost_id++;
    create_IDs("blue", f);
    cost_id++;
    create_IDs("silver", f);
    cost_id++;
    create_IDs("orange", f);
    cost_id++;
    create_IDs("red", f);
    
    
    
    //print all costs objects
    
    printf("\n");
    
    for (i=0; i<N; i++)
    
    {
        printf("\nThe cost ID is %d", i);
        printf("\nThe name of the station is %s", All_Costs[i].name);
        printf("\nThe name of the station is %s", All_Costs[i].line);
        printf("\nThe name of the station is %s", All_Costs[i].state);
        printf("\n");
    
    }

    
    rewind(f);
    fill_line_new("green", f);
    fill_line_new("yellow", f);
    fill_line_new("blue", f);
    fill_line_new("silver", f);
    fill_line_new("orange", f);
    fill_line_new("red", f);
    
    printf("\n");
    
    
    printf("\nPlz Enter the source: ");
    scanf("%s", source);
    
    printf("\nEnter the destination: ");
    scanf("%s", destination);
    
    
    //Calculate possible origins
    k=0;
    
    for (i=0; i<N; i++)
    {
        if (strcmp(All_Costs[i].name, source)==0)
        {
            //Add the line if none of the line matches with this object's one
            for (j=0; j<6; j++)
            {
                if (strcmp(All_Costs[i].line, possible_origin_lines[j])==0)
                    break;
                else
                    continue;
            }
            
            if (j==6)
            {
                strcpy(possible_origin_lines[k],All_Costs[i].line);
                k++;
            }
            
        }
    }
    
    int possible_origin_lines_cnt = k;
    
    //Possible destination lines
    char possible_destination_lines[6][50];
    
    k=0;
    j=0;
    
    for (i=0; i<N; i++)
    {
        if (strcmp(All_Costs[i].name, destination)==0)
        {
            //Add the line if none of the line matches with this object's one
            for (j=0; j<6; j++)
            {
                if (strcmp(All_Costs[i].line, possible_destination_lines[j])==0)
                    break;
                else
                    continue;
            }
            
            if (j==6)
            {
                strcpy(possible_destination_lines[k],All_Costs[i].line);
                k++;
            }
            
        }
    }
    
    int possible_destination_lines_cnt = k;
    
    //////////////////////////////////////
    
    
    int min_cost = 1000000;
    int min_cost_origin=0;
    int min_cost_destination = 0;
    
   
   //Finding the minimum cost path from all possible lines
    
    for (i=0; i<possible_origin_lines_cnt; i++)
    {
        for (j=0; j<possible_destination_lines_cnt; j++)
        {
            co = find_cost(source, possible_origin_lines[i], "stop",destination, possible_destination_lines[j], "start", fp_output, 0);
            
            if (co<min_cost)
            {
                min_cost_origin = i;
                min_cost_destination=j;
            }
            
        }
    }
    
    printf("\nMinimum Cost Origin line is %s",possible_origin_lines[min_cost_origin] );
    printf("\nMinimum Cost DEstination line is %s",possible_destination_lines[min_cost_destination] );
    

    fputs("Take ", fp_output);
    fputs(possible_origin_lines[min_cost_origin], fp_output);
    fputs(" line from ", fp_output);
    fputs(source, fp_output);
    fputs("\n", fp_output);
    
    
    find_cost(destination, possible_destination_lines[min_cost_destination], "start", source, possible_origin_lines[min_cost_origin], "start", fp_output, 1);
    

    // insert code here...
    printf("\nHello, World!\n");
    return 0;
}
