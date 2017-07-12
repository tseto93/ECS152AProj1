#include "e.h"

#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

double nedt(double rate)//packets arrive at rate lambda
{
    double u;
    u = drand48();
    return((-1/rate) * log(1-u));
}

double nedt2()//packets depart at rate 1 which is why rate no longer plays a factor
{
    double u;
    u = drand48();
    return((-1) * log(1-u));
}

int main()
{
  //int num_packets = 100000;
  double MAXBUFFER;
  int packs_dropped = 0;
  double p_in_queue = 0;
  double total_time;
  double arriv_time;
  double depart_time;
  double prev_time = 0;
  double idle_time = 0;
  double idle_start = 0;
  double lambda;
  Event GEL;

  cout<< "Lambda: ";
  cin >> lambda;
  cout << "Maximum buffer: ";
  cin >> MAXBUFFER;

  Data Queue(MAXBUFFER);

  for(int i = 0; i < 100000; i++)
  {
    arriv_time = nedt(lambda) + prev_time;
    GEL.insert(arriv_time, 0);
    prev_time = arriv_time;
  }
  Event_node testing_node;
  int i = 0;
  while(GEL.check_front() != 1)
  {
    testing_node = GEL.front_return();
    if(testing_node.type == 0)
    {
      p_in_queue = p_in_queue + Queue.length;
      if(Queue.length == 0)
      {
        (Queue.length)++;
        idle_time = (testing_node.time - idle_start) + idle_time;
        (Queue.queue[(Queue.length) - 1]).time = testing_node.time;
        depart_time = testing_node.time + nedt2();
        GEL.insert(depart_time, 1); //change
      }
      else if(((Queue.length) < MAXBUFFER) && (Queue.length > 0))
      {
        (Queue.length)++;
        (Queue.queue[(Queue.length) - 1]).time = testing_node.time;
      }
      else
      {
        ++packs_dropped;
      }
    }
    else
    {
      if(Queue.length > 0)
      {
        Queue.length = Queue.length - 1;
        if(Queue.length == 0)
          idle_start = testing_node.time;
        depart_time = Queue.rmv_head(); //change
        if(depart_time != 0)
        {
          depart_time = depart_time + nedt2();
          GEL.insert(depart_time, 1); //change
          total_time = depart_time;
        }
      }
    }
    GEL.deleting();
    i++;
  }
  cout <<"Packets dropped: " <<packs_dropped<<"\n";
  cout <<"Average packets in queue: "<<(p_in_queue/total_time)<< endl;
  cout <<"Utilization: " <<(total_time - idle_time)/total_time<< endl;
}

