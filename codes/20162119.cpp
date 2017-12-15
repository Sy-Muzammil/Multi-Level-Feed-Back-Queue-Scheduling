#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <stdio.h>
#include <fstream>
#include <string>
#include <stdlib.h>
//#include <algorithms>
using namespace std;
//set <long int> s;
#define quantum 4	
#define maxsize 1000
long int cr_tm = 0,p,s[maxsize];
long int max_at = 0;
long int max_pid = 0,l=0;
long int p_s = 0,nxt_time,p_cnt=0;
queue < struct node > rr_q;
queue <struct node> in_rr_q;
long int switch_time = 0,flag_switch1 = 0,flag_switch2=0;
struct node
{
	long int pid;
	long int a_t;
	long int b_t;
	long int pr;
	long int f_t;
	long int f_s;

};
struct node prior[maxsize];
struct node temp[maxsize];
struct node last[maxsize]; 
struct node b[maxsize];
struct node c[maxsize];
struct node d;
struct node run_pro;
struct node runpro;	

struct final_node
{
	
	long int pid;
	long int r_t;
	long int b_t;
	long int a_t;
	long int f_t;
	long int w_t;
	long int f_s;
};
struct final_node value[maxsize];
struct final_node ff[maxsize];

void pid_merging(int low, int mid, int high) 
{
   int l1, l2, i;
l1 = low;
l2 = mid + 1;
   for( i = low; l1 <= mid && l2 <= high; i++) {
      if(value[l1].pid <= value[l2].pid)
        ff[i] = value[l1++];
      else
        ff[i] = value[l2++];
   }

   while(l1 <= mid)    
      ff[i++] = value[l1++];

   while(l2 <= high)   
     ff[i++] = value[l2++];

   for(i = low; i <= high; i++)
      value[i] = ff[i];
}


void pid_mergesort(int low, int high) {
   int mid;
   
   if(low < high) 
   {
	mid = (low + high) / 2;
	pid_mergesort(low, mid);
	pid_mergesort(mid+1, high);
	pid_merging(low, mid, high);
   }
   else 
    return;  
}


void pr_merging(int low, int mid, int high) 
{
   int l1, l2, i;
	l1 = low;
	l2 = mid + 1;
   for( i = low; l1 <= mid && l2 <= high; i++) 
   {
      if(temp[l1].pr <= temp[l2].pr)
         c[i] = temp[l1++];
      else
         c[i] = temp[l2++];
   }

   while(l1 <= mid)    
      c[i++] = temp[l1++];

   while(l2 <= high)   
      c[i++] = temp[l2++];

   for(i = low; i <= high; i++)
      temp[i] = c[i];
}


void pr_mergesort(int low, int high) 
{
   int mid;
   
   if(low < high) 
   {
	mid = (low + high) / 2;
	pr_mergesort(low, mid);
	pr_mergesort(mid+1, high);
	pr_merging(low, mid, high);
   }
   else 
    return;  
}

								/******* Round Robin Scheduling Starts ********/

void round_robin_sc(long int visited[])
{
	long int rp_cnt,i;
	flag_switch2 = 1;
	if(p_cnt == p)
	{
		while (!rr_q.empty())
	  	{
	    run_pro = rr_q.front();
	    					
	    rr_q.pop();
	    rp_cnt = 0;
	    	while(rp_cnt < quantum && run_pro.b_t != 0)
	    	{
	    		
	    		cr_tm++;
	    		if(run_pro.b_t != 0)
	    		{
	    									
			    	for(i=0;i<p;i++)
			    	{
			    		if(run_pro.pid == value[i].pid)
			    			value[i].f_t = cr_tm;
			    	}
		    	}
		    	run_pro.b_t--;
	    		rp_cnt++;
	    		
	    	}
	    	if(run_pro.b_t != 0)
	    		rr_q.push(run_pro);
	    												
	    	
	  	}
	}
	if(p_cnt != p)
	{
		
		run_pro = rr_q.front();
	   				
	    rp_cnt = 0;
	    
	    if(rr_q.front().b_t != 0 && switch_time <= quantum)
	    {
	    	
	    	if(rr_q.front().b_t!=0)
	    	{
		    	for(i=0;i<p;i++)
		    	{
		    		if(run_pro.pid == value[i].pid)
		    			value[i].f_t = cr_tm+1;
		    		
		    	}	
		    }
	    	rr_q.front().b_t--;
	    	switch_time++;
	    		
	    		if(switch_time == quantum)
	    		{
			    	switch_time = 0;
			    	runpro  = rr_q.front();
			    	rr_q.pop();
			    	rr_q.push(runpro);
				}
				
				if(rr_q.front().b_t == 0)
				{
					visited[rr_q.front().pid] = 2;
					rr_q.pop();
				}
	    }
	    
	}
}


					/********** priority scheduling starts *****************/


void schedule(long int j,long int visited[])
{
	long int cnt=0,i,k,y;
	long int flag = 0,flag1=0;	
	switch_time = 0;
	
	for(i = 0;i < j; i++)
	{
		
		flag1=0;
		
		if(visited[temp[i].pid] == 1 || visited[temp[i].pid] == 2)
		{
			continue;
			
		}
		
		else
		{
		cnt=0;
			while(cnt < quantum && temp[i].b_t > 0)
			{
				for(k=0;k<p;k++)
				{
						if(temp[i].pid == prior[k].pid)
							continue;
						
						if(visited[prior[k].pid]!=1 && visited[prior[k].pid]!=2 && prior[k].a_t <= cr_tm && prior[k].pr < temp[i].pr)
						{
							flag=1;
							break;
						}

				}
				
				if(flag == 1)
					break;
				
				cr_tm+=1;
				cnt++;
				if(temp[i].b_t != 0)
				{
					for(k=0;k<p;k++)
					{
						if(value[k].pid == temp[i].pid)
							value[k].f_t = cr_tm;
					}
				}
				temp[i].b_t-=1;
				
				if(temp[i].b_t == 0)
					visited[temp[i].pid] = 2;

				for(y=0;y<p;y++)
				{
					if(temp[i].pid == prior[y].pid)
					{
						if((prior[y].b_t - temp[i].b_t) == 1)
						{
							prior[y].f_s = cr_tm-1;
										
						}
					}
				}
						
			flag1=1;
			}
			if(flag1==1)
			{
				if(visited[temp[i].pid]!=2 && flag_switch2 == 1)
				{
					d=rr_q.front();
					rr_q.pop();
					rr_q.push(d);
				}

				if(visited[temp[i].pid]!=2)
				{
					
					rr_q.push(temp[i]);
				}
			visited[temp[i].pid] = 1;
			p_cnt++;
			}
			
		}
	}
	
}

void pr_sc(long int n,long int visited[])
{
	long int i = 0,k;
	long int j =0,count = 0,x;
	cr_tm = prior[i].a_t;
	while(count < n && p_cnt < n)
	{
		
		if(prior[i].a_t <= cr_tm )
		{
			while(prior[i].a_t <= cr_tm && i<n)
			{
				temp[j] = prior[i];
				j++;
				i++;
				count++;
			}

		}
		
		else
		{
			int flag_rr = 1;	
			while(prior[i].a_t > cr_tm )
			{
				for(k=0;k<j;k++)
				{
					if(visited[temp[k].pid] == 0)
					{
						flag_rr = 0;	
						break;
					}
					
				}
				if(flag_rr == 1)
				{
					round_robin_sc(visited);
				}
			cr_tm++;

			}
			temp[j] = prior[i];
			j++;
			i++;
			count++;
		}
		
		pr_mergesort(0,j-1);
		
		schedule(j,visited);
	}
							
	
	round_robin_sc(visited);
	

}

							/****** Sort According to the Arrival Time ******/


void merging(int low, int mid, int high) {
   int l1, l2, i;
l1 = low;
l2 = mid + 1;
   for( i = low; l1 <= mid && l2 <= high; i++) {
      if(prior[l1].a_t <= prior[l2].a_t)
         b[i] = prior[l1++];
      else
         b[i] = prior[l2++];
   }

   while(l1 <= mid)    
      b[i++] = prior[l1++];

   while(l2 <= high)   
      b[i++] = prior[l2++];

   for(i = low; i <= high; i++)
      prior[i] = b[i];
}


void mergesort(int low, int high) {
   int mid;
   
   if(low < high) 
   {
	mid = (low + high) / 2;
	mergesort(low, mid);
	mergesort(mid+1, high);
	merging(low, mid, high);
   }
   else 
    return;  
}

									/***** Program Start ******/

int main(int argc, char *argv[])
{
if(argc < 3)
	cout << "input format: "<<"./a.out"<<"Input file"<<"output file"<<endl;
long int i,j;
//scanf("%ld",&p);
long int N,temp;
ifstream in(argv[1]);
ofstream out(argv[2]);
//file.open(argv[1]);
string word;

in>>word; 
N = atoi(word.c_str());
//cout << N<<endl;
//temp = N;
p = N;
	for(i = 0; i < p; i++)
	{
		in>>prior[i].pid>>prior[i].a_t>>prior[i].b_t>>prior[i].pr;
		//cout << prior[i].pid << prior[i].a_t<<prior[i].b_t<<prior[i].pr;
		value[i].pid = prior[i].pid;
		value[i].b_t = prior[i].b_t;
		value[i].a_t = prior[i].a_t;
		if(max_at < prior[i].a_t)
			max_at = prior[i].a_t;
		if(max_pid < prior[i].pid)
			max_pid = prior[i].pid;
	}
	

	long int visited[max_pid+1];

	for(i=0; i <= max_pid ; i++)
		visited[i]=0;
	mergesort(0,p-1);
	
	pr_sc(p,visited);
	for(i=0;i<p;i++)
	{
		value[i].w_t = value[i].f_t - value[i].a_t - value[i].b_t;
		for(j=0;j<p;j++)
		{
			if(prior[i].pid == value[j].pid)
			{
				value[j].f_s = prior[i].f_s;
				break;
			}
		}
	}
	for(i=0;i<p;i++)
	{
		value[i].r_t = value[i].f_s - value[i].a_t;
	}
	pid_mergesort(0,p-1);
	//printf("\n");
	for (i = 0; i < p; ++i)
	{
		out<<value[i].pid<<" "<<value[i].r_t<<" "<<value[i].f_t<<" "<<value[i].w_t<<endl;
	}
}
